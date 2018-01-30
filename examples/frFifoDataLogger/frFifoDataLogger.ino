// Data logger based on a FIFO to decouple SD write latency from data
// acquisition.

// The FIFO uses two semaphores to synchronize between tasks.

#include <SPI.h>
#include <STM32FreeRTOS.h>
#include <SD.h>

// interval between points in units of 1000 usec
const uint16_t intervalTicks = 1;
//------------------------------------------------------------------------------
// SD file definitions
const uint8_t sdChipSelect = SS;
File file;
//------------------------------------------------------------------------------
// Fifo definitions

// size of fifo in records
const size_t FIFO_SIZE = 200;

// count of data records in fifo
SemaphoreHandle_t fifoData;

// count of free buffers in fifo
SemaphoreHandle_t fifoSpace;

// data type for fifo item
struct FifoItem_t {
  uint32_t usec;
  int value;
  int error;
};
// array of data items
FifoItem_t fifoArray[FIFO_SIZE];
//------------------------------------------------------------------------------
// handle for sensor task
TaskHandle_t sens;
static void Task1(void *arg) {
  // index of record to be filled
  size_t fifoHead = 0;

  // count of overrun errors
  int error = 0;

  // dummy data
  int count = 0;

  // initialise the ticks variable with the current time.
  TickType_t ticks = xTaskGetTickCount();

  while (1) {
    // wait until time for next data point
    vTaskDelayUntil(&ticks, intervalTicks);

    // get a buffer
    if (xSemaphoreTake(fifoSpace, 0) != pdTRUE) {
      // fifo full - indicate missed point
      error++;
      continue;
    }
    FifoItem_t* p = &fifoArray[fifoHead];
    p->usec = micros();

    // replace next line with data read from sensor
    // f
    p->value = count++;

    p->error = error;
    error = 0;

    // signal new data
    xSemaphoreGive(fifoData);

    // advance FIFO index
    fifoHead = fifoHead < (FIFO_SIZE - 1) ? fifoHead + 1 : 0;
  }
}
//------------------------------------------------------------------------------
// SD write task
static void Task2(void *arg) {
  // FIFO index for record to be written
  size_t fifoTail = 0;

  // time in micros of last point
  uint32_t last = 0;

  while(1) {
    // wait for next data record
    xSemaphoreTake(fifoData, portMAX_DELAY);

    FifoItem_t* p = &fifoArray[fifoTail];

    // print interval between points
    if (last) {
      file.print(p->usec - last);
    } else {
      file.write("NA");
    }
    last = p->usec;
    file.write(',');
    file.print(p->value);
    file.write(',');
    file.println(p->error);

    // release record
    xSemaphoreGive(fifoSpace);

    // advance FIFO index
    fifoTail = fifoTail < (FIFO_SIZE - 1) ? fifoTail + 1 : 0;

    // check for end run
    if (Serial.available()) {
      // close file to insure data is saved correctly
      file.close();

      // print messages
      Serial.println(F("Done"));
      Serial.print(F("Task1 unused stack entries: "));
      Serial.println(uxTaskGetStackHighWaterMark(sens));
      Serial.print(F("Task2 unused stack entries: "));
      Serial.println(uxTaskGetStackHighWaterMark(0));
 //     ARM free heap not implemented yet
 //     Serial.print(F("Free heap (bytes): "));
 //     Serial.println(freeHeap());
      while(1);
    }
  }
}
//------------------------------------------------------------------------------
void setup() {
  // task creation status
  portBASE_TYPE s1, s2;

  Serial.begin(9600);
  while(!Serial);
  Serial.println(F("Type any character to begin"));
  while(!Serial.available());

  // open file
  if (!SD.begin(sdChipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while(1);
  }
  Serial.println("card initialized.");

  file = SD.open("DATA.CSV", FILE_WRITE);
  if(!file) {
    Serial.println("error opening DATA.CSV");
    while(1);
  }
  // initialize fifoData semaphore to no data available
  fifoData = xSemaphoreCreateCounting(FIFO_SIZE, 0);

  // initialize fifoSpace semaphore to FIFO_SIZE free records
  fifoSpace = xSemaphoreCreateCounting(FIFO_SIZE, FIFO_SIZE);

  // create sensor task at priority two
  s1 = xTaskCreate(Task1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, &sens);

  // create SD write task at priority one
  s2 = xTaskCreate(Task2, NULL, configMINIMAL_STACK_SIZE + 200, NULL, 1, NULL);

  // check for creation errors
  if (fifoData == NULL || fifoSpace == NULL || s1 != pdPASS || s2 != pdPASS ) {
    Serial.println(F("Creation problem"));
    while(1);
  }
  // throw away serial input
  while (Serial.available()) Serial.read();
  Serial.println(F("Type any character to end"));

  // start scheduler
  vTaskStartScheduler();
  Serial.println(F("Insufficient RAM"));
  while(1);
}
//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // not used
}

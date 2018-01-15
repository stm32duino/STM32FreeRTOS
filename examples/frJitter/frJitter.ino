// test of jitter in sleep for one tick
//
// idle loop prints min and max time between sleep calls
//
// Note: access to shared variables tmin and tmax is not atomic
// so glitches are possible if context switch happens during idle loop
// access to these variables.
//
#include <STM32FreeRTOS.h>

volatile  uint16_t tmax = 0;
volatile  uint16_t tmin = 0XFFFF;
//------------------------------------------------------------------------------
static void vJitter(void *pvParameters) {
  // initialize tlast
  vTaskDelay(1);
  uint32_t tlast = micros();
  while (true) {
    vTaskDelay(1);
    // get wake time
    uint32_t tmp = micros();
    uint16_t diff = tmp - tlast;
    if (diff < tmin) tmin = diff;
    if (diff > tmax) tmax = diff;
    tlast = tmp;
  }
}
//------------------------------------------------------------------------------
uint8_t np = 10;
static void vPrintTask(void *pvParameters) {
  for (;;) {
    // delay one second
    vTaskDelay(configTICK_RATE_HZ);
    Serial.print(tmin);
    Serial.write(',');
    Serial.println(tmax);
    if (np++ >= 10) {
      np = 0;
      tmin = 0XFFFF;
      tmax = 0;
      Serial.write("clear\r\n");
    }
  }
}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(1000);

  // create high priority thread
  xTaskCreate(vJitter,
    "Task1",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 2,
    NULL);

  // create print task
  xTaskCreate(vPrintTask,
    "Task2",
    configMINIMAL_STACK_SIZE + 100,
    NULL,
    tskIDLE_PRIORITY + 1,
    NULL);

  // start FreeRTOS
  vTaskStartScheduler();

  // should never return
  Serial.println("Die");
  while(1);
}
//------------------------------------------------------------------------------
void loop() {
  // Not used - idle loop has a very small, configMINIMAL_STACK_SIZE, stack
  // loop must never block
}

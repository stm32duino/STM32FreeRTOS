// Test to determine context switch time with a semaphore
// Connect a scope to LED_BUILTIN pin
// Measure difference in time between first pulse with no context switch
// and second pulse started in ledControl and ended in ledOffTask.
// This is the time for the semaphore and a context switch.
#include <STM32FreeRTOS.h>

#define LED_PIN LED_BUILTIN
// Semaphore to trigger context switch
SemaphoreHandle_t xSemaphore;
//------------------------------------------------------------------------------
// high priority thread to set pin low
static void ledOffTask(void *pvParameters) {
  for (;;) {
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    digitalWrite(LED_PIN, LOW);
  }
}
//------------------------------------------------------------------------------
// lower priority thread to toggle LED and trigger thread 1
static void ledControl(void *pvParameters) {
  for (;;) {
    // first pulse to get time with no context switch
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);

    // start second pulse
    digitalWrite(LED_PIN, HIGH);

    // trigger context switch for task that ends pulse
    xSemaphoreGive(xSemaphore);

    // sleep until next tick
    vTaskDelay(1);
  }
}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  // create high priority thread
  xTaskCreate(ledOffTask,
    "Task1",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 2,
    NULL);

  // create lower priority thread
  xTaskCreate(ledControl,
    "Task2",
    configMINIMAL_STACK_SIZE,
    NULL,
    tskIDLE_PRIORITY + 1,
    NULL);

  // create semaphore
  vSemaphoreCreateBinary(xSemaphore);

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

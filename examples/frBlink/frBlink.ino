/*
 * Example to demonstrate thread definition, semaphores, and thread sleep.
 */
#include <STM32FreeRTOS.h>

// Define the LED pin is attached
const uint8_t LED_PIN = LED_BUILTIN;

// Declare a semaphore handle.
SemaphoreHandle_t sem;
//------------------------------------------------------------------------------
/*
 * Thread 1, turn the LED off when signalled by thread 2.
 */
// Declare the thread function for thread 1.
static void Thread1(void* arg) {
  UNUSED(arg);
  while (1) {

    // Wait for signal from thread 2.
    xSemaphoreTake(sem, portMAX_DELAY);

    // Turn LED off.
    digitalWrite(LED_PIN, LOW);
  }
}
//------------------------------------------------------------------------------
/*
 * Thread 2, turn the LED on and signal thread 1 to turn the LED off.
 */
// Declare the thread function for thread 2.
static void Thread2(void* arg) {
  UNUSED(arg);
  pinMode(LED_PIN, OUTPUT);

  while (1) {
    // Turn LED on.
    digitalWrite(LED_PIN, HIGH);

    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);

    // Signal thread 1 to turn LED off.
    xSemaphoreGive(sem);

    // Sleep for 200 milliseconds.
    vTaskDelay((200L * configTICK_RATE_HZ) / 1000L);
  }
}
//------------------------------------------------------------------------------
void setup() {
  portBASE_TYPE s1, s2;

  Serial.begin(9600);

  // initialize semaphore
  sem = xSemaphoreCreateCounting(1, 0);

  // create task at priority two
  s1 = xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);

  // create task at priority one
  s2 = xTaskCreate(Thread2, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  // check for creation errors
  if (sem== NULL || s1 != pdPASS || s2 != pdPASS ) {
    Serial.println(F("Creation problem"));
    while(1);
  }

  // start scheduler
  vTaskStartScheduler();
  Serial.println("Insufficient RAM");
  while(1);
}

//------------------------------------------------------------------------------
// WARNING idle loop has a very small stack (configMINIMAL_STACK_SIZE)
// loop must never block
void loop() {
  // Not used.
}

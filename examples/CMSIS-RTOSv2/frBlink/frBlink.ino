/* --------------------------------------------------------------------------
  Simple LED blink example using CMS-RTOSv2
  ---------------------------------------------------------------------------*/

#include <STM32FreeRTOS.h>

osThreadId_t tid_ledOn;  /* Thread id of thread: ledOn */
osThreadId_t tid_ledOff; /* Thread id of thread: ledOff */

//Thread 1
void ledOn(void */*argument*/) {
  for (;;) {
    digitalToggle(LED_BUILTIN);
    osThreadFlagsSet(tid_ledOff, 0x0001);
    //signal ledOffthread
    osDelay(500);
  }
}

// Thread  2
void ledOff(void */*argument*/) {
  for (;;) {
    // wait for signal from ledOnthread
    osThreadFlagsWait(0x0001, osFlagsWaitAny,  osWaitForever) ;
    osDelay(1000);
    digitalToggle(LED_BUILTIN);
  }
}

/*----------------------------------------------------------------------------
        Main: Initialize and start the application
  ---------------------------------------------------------------------------*/
void app_main (void */*argument*/) {

  tid_ledOn = osThreadNew(ledOn, NULL, NULL);
  tid_ledOff = osThreadNew(ledOff, NULL, NULL);

  osDelay(osWaitForever);
  while (1);
}

/*----------------------------------------------------------------------------
        Main: Initialize and start the RTOS2 Kernel
  ---------------------------------------------------------------------------*/
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  osKernelInitialize();                 // Initialize CMSIS-RTOS
  osThreadNew(app_main, NULL, NULL);    // Create application main thread
  if (osKernelGetState() == osKernelReady) {
    osKernelStart();                    // Start thread execution
  }

  while (1);
}

//------------------------------------------------------------------------------
// loop must never block
void loop() {
}

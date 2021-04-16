/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_DEFAULT_H
#define FREERTOS_CONFIG_DEFAULT_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * These parameters and more are described within the 'configuration' section of the
 * FreeRTOS API documentation available on the FreeRTOS.org web site.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/* Begin custom definitions for STM32 */
/* Define memory allocation implementations to use:
 * 1 to 5 for heap_[1-5].c
 * -1 for heap_useNewlib_ST.c
 * Default -1 see heap.c
 */
/*#define configMEMMANG_HEAP_NB             3*/

/* configUSE_CMSIS_RTOS_V2 has to be defined and set to 1 to use CMSIS-RTOSv2 */
/*#define configUSE_CMSIS_RTOS_V2           1*/

/* End custom definitions for STM32 */

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
 #include <stdint.h>
 extern uint32_t SystemCoreClock;
#endif

#if defined(configUSE_CMSIS_RTOS_V2) && (configUSE_CMSIS_RTOS_V2 == 1)
/*------------- CMSIS-RTOS V2 specific defines -----------*/
/* When using CMSIS-RTOSv2 set configSUPPORT_STATIC_ALLOCATION to 1
 * is mandatory to avoid compile errors.
 * CMSIS-RTOS V2 implmentation requires the following defines
 */
/* cmsis_os threads are created using xTaskCreateStatic() API */
#define configSUPPORT_STATIC_ALLOCATION   1
/*  CMSIS-RTOSv2 defines 56 levels of priorities. To be able to use them
 *  all and avoid application misbehavior, configUSE_PORT_OPTIMISED_TASK_SELECTION
 *  must be set to 0 and configMAX_PRIORITIES to 56
 *
 */
#define configMAX_PRIORITIES              (56)
/*
 * When set to 1, configMAX_PRIORITIES can't be more than 32
 * which is not suitable for the new CMSIS-RTOS v2 priority range
 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
/* Require to be a value as used in cmsis_os2.c as array size */
#ifndef configMINIMAL_STACK_SIZE
#define configMINIMAL_STACK_SIZE          ((uint16_t)128)
#endif

#if !defined(CMSIS_device_header)
/* CMSIS_device_header defined to stm32_def.h by default, which include <device.h> like stm32f1xx.h */
#define CMSIS_device_header  "stm32_def.h"
#endif /* CMSIS_device_header */
#else
#define configMAX_PRIORITIES              (7)
#endif /* configUSE_CMSIS_RTOS_V2 */

extern char _end; /* Defined in the linker script */
extern char _estack; /* Defined in the linker script */
extern char _Min_Stack_Size; /* Defined in the linker script */
/*
 * _Min_Stack_Size is often set to 0x400 in the linker script
 * Use it divided by 8 to set minmimal stack size of a task to 128 by default.
 * End user will have to properly configure those value depending to their needs.
 */
#ifndef configMINIMAL_STACK_SIZE
#define configMINIMAL_STACK_SIZE          ((uint16_t)((uint32_t)&_Min_Stack_Size/8))
#endif
#ifndef configTOTAL_HEAP_SIZE
#define configTOTAL_HEAP_SIZE             ((size_t)((uint32_t)&_estack - (uint32_t)&_Min_Stack_Size - (uint32_t)&_end))
#endif
#ifndef configISR_STACK_SIZE_WORDS
#define configISR_STACK_SIZE_WORDS        ((uint32_t)&_Min_Stack_Size/4)
#endif

#define configUSE_PREEMPTION              1
#define configUSE_IDLE_HOOK               1
#define configUSE_TICK_HOOK               1
#define configCPU_CLOCK_HZ                (SystemCoreClock)
#define configTICK_RATE_HZ                ((TickType_t)1000)
#define configMAX_TASK_NAME_LEN           (16)
#define configUSE_TRACE_FACILITY          1
#define configUSE_16_BIT_TICKS            0
#define configIDLE_SHOULD_YIELD           1
#define configUSE_MUTEXES                 1
#define configQUEUE_REGISTRY_SIZE         8
#define configCHECK_FOR_STACK_OVERFLOW    0
#define configUSE_RECURSIVE_MUTEXES       1
#define configUSE_MALLOC_FAILED_HOOK      0
#define configUSE_APPLICATION_TASK_TAG    0
#define configUSE_COUNTING_SEMAPHORES     1
#define configGENERATE_RUN_TIME_STATS     0
/*
 * If configUSE_NEWLIB_REENTRANT is set to 1 then a newlib reent structure
 * will be allocated for each created task.
 *
 * Note Newlib support has been included by popular demand, but is not used
 * by the FreeRTOS maintainers themselves. FreeRTOS is not responsible for
 * resulting newlib operation. User must be familiar with newlib and must
 * provide system-wide implementations of the necessary stubs.
 * Be warned that (at the time of writing) the current newlib design implements
 * a system-wide malloc() that must be provided with locks.
 */
#define configUSE_NEWLIB_REENTRANT        1

/* Set configENABLE_MPU to 1 to enable MPU support and 0 to disable it. This is
currently used in ARMv8M ports. */
#define configENABLE_MPU                  0
/* Set configENABLE_FPU to 1 to enable FPU support and 0 to disable it. This is
currently used in ARMv8M ports. */
#define configENABLE_FPU                  1
/* Set configENABLE_TRUSTZONE to 1 enable TrustZone support and 0 to disable it.
This is currently used in ARMv8M ports. */
#define configENABLE_TRUSTZONE            0

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES             0
#define configMAX_CO_ROUTINE_PRIORITIES  (2)

/* Software timer definitions. */
#define configUSE_TIMERS                  1
#define configTIMER_TASK_PRIORITY        (2)
#define configTIMER_QUEUE_LENGTH         10
#define configTIMER_TASK_STACK_DEPTH    (configMINIMAL_STACK_SIZE * 2)

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet          1
#define INCLUDE_uxTaskPriorityGet         1
#define INCLUDE_vTaskDelete               1
#define INCLUDE_vTaskCleanUpResources     1
#define INCLUDE_vTaskSuspend              1
#define INCLUDE_vTaskDelayUntil           1
#define INCLUDE_vTaskDelay                1
#define INCLUDE_xTaskGetSchedulerState    1
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#define INCLUDE_xTaskGetIdleTaskHandle    1

#if defined(configUSE_CMSIS_RTOS_V2) && (configUSE_CMSIS_RTOS_V2 == 1)
#define INCLUDE_xSemaphoreGetMutexHolder  1
#define INCLUDE_eTaskGetState             1
#define INCLUDE_xTimerPendFunctionCall    1
#define INCLUDE_xTaskGetCurrentTaskHandle 1
#endif

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
 /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
 #define configPRIO_BITS                  __NVIC_PRIO_BITS
#else
 #define configPRIO_BITS                  4        /* 15 priority levels */
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   0xf

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY   ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY  ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
   standard names. */
#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler

/*
 * IMPORTANT:
 * SysTick_Handler() from stm32duino core is calling weak osSystickHandler().
 * Both CMSIS-RTOSv2 and CMSIS-RTOS override osSystickHandler() 
 * which is calling xPortSysTickHandler(), defined in respective CortexM-x port
 */
/* #define xPortSysTickHandler SysTick_Handler */

#endif /* FREERTOS_CONFIG_DEFAULT_H */


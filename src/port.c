/*
 * @file    port.c
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include source of FreeRTOS portable layer file to match Arduino library format
 */
#include <Arduino.h>

#ifndef __CORTEX_M
#pragma GCC error  "no \"__CORTEX_M\" definition"
#endif

#if (__CORTEX_M == 0x00U)
#include "../portable/GCC/ARM_CM0/port.c"
#endif

#if (__CORTEX_M == 0x03U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM3_MPU/port.c"
#else
#include "../portable/GCC/ARM_CM3/port.c"
#endif
#endif

#if (__CORTEX_M == 0x04U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM4_MPU/port.c"
#else
#include "../portable/GCC/ARM_CM4F/port.c"
#endif
#endif

#if (__CORTEX_M == 0x07U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM7_MPU/r0p1/port.c"
#else
#include "../portable/GCC/ARM_CM7/r0p1/port.c"
#endif
#endif

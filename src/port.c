/*
 * @file    port.c
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include source of FreeRTOS portable layer file to match Arduino library format
 */
#include <Arduino.h>

#ifndef __CORTEX_M
#pragma GCC error  "no \"__CORTEX_M\" definition"
#endif

#if (__CORTEX_M == 0U)
#include "../portable/GCC/ARM_CM0/port.c"
#endif

#if (__CORTEX_M == 3U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM3_MPU/port.c"
#else
#include "../portable/GCC/ARM_CM3/port.c"
#endif
#endif

#if (__CORTEX_M == 4U)
#if (__FPU_PRESENT == 0)
/* Fallback to CM3 port as there is no FPU */
#include "../portable/GCC/ARM_CM3/port.c"
#else
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM4_MPU/port.c"
#else
#include "../portable/GCC/ARM_CM4F/port.c"
#endif
#endif
#endif

#if (__CORTEX_M == 7U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM7_MPU/r0p1/port.c"
#else
#include "../portable/GCC/ARM_CM7/r0p1/port.c"
#endif
#endif

#if (__CORTEX_M == 33U)
/* TZ = 0 */
#include "../portable/GCC/ARM_CM33_NTZ/non_secure/port.c"
#endif

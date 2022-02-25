/*
 * @file    portmacro.h
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include header of FreeRTOS portable layer file to match Arduino library format
 */

#ifndef _PORTMACRO_H_
#define _PORTMACRO_H_
#include "stm32_def.h"

#ifndef __CORTEX_M
#pragma GCC error  "no \"__CORTEX_M\" definition"
#endif

#if (__CORTEX_M == 0U)
#include "../portable/GCC/ARM_CM0/portmacro.h"
/* Stub for heap_useNewlib_ST */
inline __attribute__(( always_inline )) static BaseType_t xPortIsInsideInterrupt( void ) { return pdFALSE; }
#endif

#if (__CORTEX_M == 3U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM3_MPU/portmacro.h"
#else
#include "../portable/GCC/ARM_CM3/portmacro.h"
#endif
#endif

#if (__CORTEX_M == 4U)
#if (__FPU_PRESENT == 0)
/* Fallback to CM3 port as there is no FPU */
#include "../portable/GCC/ARM_CM3/portmacro.h"
#else
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM4_MPU/portmacro.h"
#else
#include "../portable/GCC/ARM_CM4F/portmacro.h"
#endif
#endif
#endif

#if (__CORTEX_M == 7U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM7_MPU/r0p1/portmacro.h"
#else
#include "../portable/GCC/ARM_CM7/r0p1/portmacro.h"
#endif
#endif

#if (__CORTEX_M == 33U)
#include "../portable/GCC/ARM_CM33_NTZ/non_secure/portmacro.h"
#endif

#endif //_PORTMACRO_H_

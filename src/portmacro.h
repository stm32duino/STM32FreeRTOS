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

#if (__CORTEX_M == 0x00U)
#include "../portable/GCC/ARM_CM0/portmacro.h"
#endif

#if (__CORTEX_M == 0x03U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM3_MPU/portmacro.h"
#else
#include "../portable/GCC/ARM_CM3/portmacro.h"
#endif
#endif

#if (__CORTEX_M == 0x04U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM4_MPU/portmacro.h"
#else
#include "../portable/GCC/ARM_CM4F/portmacro.h"
#endif
#endif

#if (__CORTEX_M == 0x07U)
/* MPU not supported */
#if 0 /*(__MPU_PRESENT == 1)*/
#include "../portable/GCC/ARM_CM7_MPU/r0p1/portmacro.h"
#else
#include "../portable/GCC/ARM_CM7/r0p1/portmacro.h"
#endif
#endif

#endif //_PORTMACRO_H_

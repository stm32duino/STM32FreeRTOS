/*
 * @file    portasm.h
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include header of FreeRTOS portable layer file to match Arduino library format
 */

#ifndef _PORTASM_H_
#define _PORTASM_H_
#include "stm32_def.h"

#ifndef __CORTEX_M
#pragma GCC error  "no \"__CORTEX_M\" definition"
#endif

#if (__CORTEX_M == 33U)
/* TZ = 0 */
#include "../portable/GCC/ARM_CM33_NTZ/non_secure/portasm.h"
#endif

#endif //_PORTASM_H_

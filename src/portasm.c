/*
 * @file    portasm.c
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include source of FreeRTOS portable layer file to match Arduino library format
 */
#include <Arduino.h>

#ifndef __CORTEX_M
#pragma GCC error  "no \"__CORTEX_M\" definition"
#endif

#if (__CORTEX_M == 33U)
/* TZ = 0 */
#include "../portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c"
#endif

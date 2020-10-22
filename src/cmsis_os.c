/*
 * @file    cmsis_os.c
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include source of FreeRTOS portable layer file to match Arduino library format
 */
#include "FreeRTOS.h"

#if !defined(configUSE_CMSIS_RTOS_V2) || (configUSE_CMSIS_RTOS_V2 == 0)
#include "../portable/CMSIS_RTOS/cmsis_os.c"
#else
#include "../portable/CMSIS_RTOS_V2/cmsis_os2.c"
#endif


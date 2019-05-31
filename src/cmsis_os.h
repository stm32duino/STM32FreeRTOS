/*
 * @file    cmsis_os.h
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include header file to match Arduino library format
 */
#ifndef _ARDUINO_CMSIS_OS_H_
#define _ARDUINO_CMSIS_OS_H_

#include "FreeRTOS.h"

#if !defined(configUSE_CMSIS_RTOS_V2) || (configUSE_CMSIS_RTOS_V2 == 0)
#include "../portable/CMSIS_RTOS/cmsis_os.h"
#else
#include "../portable/CMSIS_RTOS_V2/cmsis_os.h"
#endif

#endif //_ARDUINO_CMSIS_OS_H_

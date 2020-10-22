/*
 * @file    FreeRTOSConfig.h
 * @author  Frederic Pillon <frederic.pillon@st.com> for STMicroelectronics.
 * @brief   Include header file to match Arduino library format
 */

#ifndef _ARDUINO_FREERTOS_CONFIG_H
#define _ARDUINO_FREERTOS_CONFIG_H

/* Application specific configuration options. */
#if __has_include("STM32FreeRTOSConfig.h")
#include "STM32FreeRTOSConfig.h"
#else
#if __has_include("STM32FreeRTOSConfig_extra.h")
#include "STM32FreeRTOSConfig_extra.h"
#endif
#include "FreeRTOSConfig_Default.h"
#endif

#endif /* _ARDUINO_FREERTOS_CONFIG_H */


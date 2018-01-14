# STM32 FreeRTOS Library for Arduino

This is a port of FreeRTOS for STM32 as Arduino libraries.

For more information about FreeRTOS, visit the [FreeRTOS Web Site](http://www.freertos.org/ "FreeRTOS").
Also, See the very useful [Getting Started](http://www.freertos.org/FreeRTOS-quick-start-guide.html "Quick Start Guide") page.

Current FreeRTOS version used for this library is [9.0.0](http://www.freertos.org/FreeRTOS-V9.html) and has been modified by ST (See st_readme.txt in FreeRTOS Source).

This is the current one provided with the [STM32Cube MCU Packages](http://www.st.com/en/embedded-software/stm32cube-mcu-packages.html)

## Configuration

FreeRTOS has several configuration options, which can be specified from within the FreeRTOSConfig.h file.

This library provides a default FreeRTOS configuration file named `FreeRTOSConfig_Default.h`.

User can provide his own FreeRTOS configuration file at sketch level by adding his configuration in a file named `STM32FreeRTOSConfig.h`.

Heap allocation schemes are provided by FreeRTOS, see [Memory allocation implementations included in the RTOS source](https://www.freertos.org/a00111.html).
By default, the `heap_3.c` is used. It can be changed thanks a define in the configuration file:
```
/* Default (3) Memory allocation implementations (heap_[1-5].c) */
/*#define configMEMMANG_HEAP_NB             3*/
```

## Limitations

* MPU: not supported.

## Files & Configuration

* STM32FreeRTOS.h : Must always be #include first. It references required include files.
* STM32FreeRTOSConfig.h : If exist at sketch level, it contains the FreeRTOS configurations.
* FreeRTOSConfig_Default.h : Contains the default FreeRTOS configurations for this STM32 port if `STM32FreeRTOSConfig.h` doesn't exist.
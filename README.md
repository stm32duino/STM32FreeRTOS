# STM32 FreeRTOS Library for Arduino

This is a port of FreeRTOS for STM32 as Arduino libraries.

For more information about FreeRTOS, visit the [FreeRTOS Web Site](http://www.freertos.org/ "FreeRTOS").
Also, See the very useful [Getting Started](http://www.freertos.org/FreeRTOS-quick-start-guide.html "Quick Start Guide") page.

This library provides 2 FreeRTOS versions:
 * [9.x](http://www.freertos.org/FreeRTOS-V9.html)
 * [10.x](http://www.freertos.org/FreeRTOS-V10.html):
   * [10.0.1](https://github.com/STMicroelectronics/stm32_mw_freertos/releases/tag/v10.0.1) 
   * [10.2.1](https://github.com/STMicroelectronics/stm32_mw_freertos/releases/tag/v10.2.1)
   * [10.3.1](https://github.com/STMicroelectronics/stm32_mw_freertos/releases/tag/v10.3.1)

Each have been modified by ST (See st_readme.txt in FreeRTOS Source).

These are the same provided with the [STM32Cube MCU Packages](http://www.st.com/en/embedded-software/stm32cube-mcu-packages.html).
Or thanks to [STMicroelectronics GitHub organization](https://github.com/STMicroelectronics): [stm32_mw_freertos](https://github.com/STMicroelectronics/stm32_mw_freertos).

## Configuration

FreeRTOS has several configuration options, which can be specified from within the FreeRTOSConfig.h file.

This library provides a default FreeRTOS configuration file named `FreeRTOSConfig_Default.h`.

User can provide his own FreeRTOS configuration file at sketch level by adding his configuration in a file named `STM32FreeRTOSConfig.h`.

Or add extra FreeRTOS configuration to the default at sketch level by adding an extra configuration in a file named `STM32FreeRTOSConfig_extra.h`.

Heap allocation schemes are provided by FreeRTOS, see [Memory allocation implementations included in the RTOS source](https://www.freertos.org/a00111.html).
To extend those schemes a thread-safe heap allocation using C runtime (Newlib) has been added based on Dave Nadler work:

http://www.nadler.com/embedded/newlibAndFreeRTOS.html

By default, the `heap_useNewlib.c` is used. It can be changed thanks a define in the configuration file:
```
/* Define memory allocation implementations to use:
 * 1 to 5 for heap_[1-5].c
 * -1 for heap_useNewlib_ST.c
 * Default -1 see heap.c
 */
```

Since v10.0.1, CMSIS-RTOSv2 can be used instead of default CMSIS-RTOS.

`configUSE_CMSIS_RTOS_V2` has to be defined and set to `1` to use
CMSIS-RTOSv2.


## Limitations

* MPU: not supported.
* No CMSIS-RTOSv2 support provided. It is provided as example.
* On Cortex-M0 and Cortex-M0+, all IT are disabled between xTaskCreate() and vTaskStartScheduler().
  So it is not possible to use IT inbetween, like Serial.print() ...
  This is the reason why, in example "frLiyLayland", between xTaskCreate() and vTaskStartScheduler(),
  we use direct printf(), which will access directly USART without interrupt

## Files & Configuration

* STM32FreeRTOS.h : Must always be #include first. It references required include files.
* STM32FreeRTOSConfig.h : If exist at sketch level, it contains the FreeRTOS configurations.
* STM32FreeRTOSConfig_extra.h : If exist at sketch level, it contains extra FreeRTOS configurations.
* FreeRTOSConfig_Default.h : Contains the default FreeRTOS configurations for this STM32 port if `STM32FreeRTOSConfig.h` doesn't exist.

## Test results (using [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32))

### STM32FreeRTOS v9.0.x
| Board | AnalogRead_DigitalRead | Blink_AnalogRead | frBlink | frBlinkPrint | frJitter | frLiuLayland |
| --- | :---: | :---: | :---: | :---: | :---: | :---: |
| [Nucleo F091RC](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html) | PASSED | PASSED | PASSED | PASSED | PASSED | FAILED |
| [Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) | PASSED | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo F303RE](http://www.st.com/en/evaluation-tools/nucleo-f303re.html) | PASSED | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo F429ZI](http://www.st.com/en/evaluation-tools/nucleo-f429zi.html) | PASSED | PASSED | PASSED | PASSED | PASSED | PASSED |
| [STM32F746G-DISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) | PASSED | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo L053R8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html) | PASSED* | PASSED* | PASSED* | PASSED* | PASSED* | FAILED |
| [Nucleo L152RE](http://www.st.com/en/evaluation-tools/nucleo-l152re.html) | PASSED | PASSED | PASSED | PASSED | PASSED | PASSED |
| [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) | PASSED | PASSED | PASSED | PASSED | PASSED | PASSED |

### STM32FreeRTOS v10.0.x
| Board | AnalogRead_DigitalRead | frBlinkPrint | frLiuLayland | frBlink (CMSIS-RTOSv2) | Blinky (CMSIS-RTOSv2) |
| --- | :---: | :---: | :---: | :---: | :---: |
| [Nucleo F091RC](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html) | PASSED | PASSED | FAILED | PASSED | PASSED |
| [Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo F303RE](http://www.st.com/en/evaluation-tools/nucleo-f303re.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo F429ZI](http://www.st.com/en/evaluation-tools/nucleo-f429zi.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [STM32F746G-DISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo-G071RB](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html) | PASSED | PASSED | FAILED | PASSED | PASSED |
| [Nucleo H743ZI](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo L053R8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html) | PASSED* | PASSED* | FAILED | PASSED | PASSED |
| [Nucleo L152RE](http://www.st.com/en/evaluation-tools/nucleo-l152re.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [P-Nucleo-WB55RG](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html) | PASSED | PASSED | FAILED | PASSED | PASSED |

\* PASSED with `configUSE_NEWLIB_REENTRANT` set to 0 due to small RAM.

### STM32FreeRTOS v10.2.x
| Board | AnalogRead_DigitalRead | frBlinkPrint | frLiuLayland | frBlink (CMSIS-RTOSv2) | Blinky (CMSIS-RTOSv2) |
| --- | :---: | :---: | :---: | :---: | :---: |
| [Nucleo F091RC](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html) | PASSED | PASSED | FAILED | PASSED | PASSED |
| [Nucleo F103RB](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo F303RE](http://www.st.com/en/evaluation-tools/nucleo-f303re.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo F411RE](http://www.st.com/en/evaluation-tools/nucleo-f411re.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [STM32F746G-DISCOVERY](http://www.st.com/en/evaluation-tools/32f746gdiscovery.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo-G071RB](https://www.st.com/en/evaluation-tools/nucleo-g071rb.html) | PASSED | PASSED | FAILED | PASSED | PASSED |
| [Nucleo-G474RE](https://www.st.com/en/evaluation-tools/nucleo-g474re.html) | PASSED | PASSED | FAILED | PASSED | PASSED |
| [Nucleo H743ZI](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo L053R8](http://www.st.com/en/evaluation-tools/nucleo-l053r8.html) | PASSED* | PASSED* | FAILED | PASSED | PASSED |
| [Nucleo L152RE](http://www.st.com/en/evaluation-tools/nucleo-l152re.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [B-L475E-IOT01A](http://www.st.com/en/evaluation-tools/b-l475e-iot01a.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [P-Nucleo-WB55RG](https://www.st.com/en/evaluation-tools/p-nucleo-wb55.html) | PASSED | PASSED | FAILED | PASSED | PASSED |

\* PASSED with `configUSE_NEWLIB_REENTRANT` set to 0 due to small RAM.

### STM32FreeRTOS v10.3.1
| Board | AnalogRead_DigitalRead | frBlinkPrint | frLiuLayland | frBlink (CMSIS-RTOSv2) | Blinky (CMSIS-RTOSv2) |
| --- | :---: | :---: | :---: | :---: | :---: |
| [Nucleo F091RC (Cortex-M0)](http://www.st.com/en/evaluation-tools/nucleo-f091rc.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo G071RB (Cortex-M0+)](http://www.st.com/en/evaluation-tools/nucleo-g071rb.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo F103RB (Cortex-M3)](http://www.st.com/en/evaluation-tools/nucleo-f103rb.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo L476RG (Cortex-M4)](http://www.st.com/en/evaluation-tools/nucleo-l476rg.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo H743ZI (Cortex-M7)](https://www.st.com/en/evaluation-tools/nucleo-h743zi.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo L552ZE-Q (Cortex-M33)](https://www.st.com/en/evaluation-tools/nucleo-l552ze-q.html) | PASSED | PASSED | PASSED | PASSED | PASSED |
| [Nucleo U575ZI-Q (Cortex-M33)](https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html) | PASSED | PASSED | PASSED | PASSED | PASSED |

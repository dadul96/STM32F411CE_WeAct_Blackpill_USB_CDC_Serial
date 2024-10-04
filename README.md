# STM32F411CE_WeAct_Blackpill_USB_CDC_Serial
Boilerplate for USB CDC VCOM serial communication with STM32F411CE-based WeAct Studio Blackpill. 

### Folder Structure
```
--STM32F411CE_WeAct_Blackpill_USB_CDC_Serial
  |
  |--lib
  |  |
  |  |--usb_serial_lib
  |     |
  |     |- delay.c
  |     |- delay.h
  |     |- usb_serial.c
  |     |- usb_serial.h
  |     |- usbcdc.c
  |     |- usbcdc.h
  |
  |--src
  |   |
  |   |- main.c
  |
  |- platformio.ini
```

### Code Dependency
```
            [main.c]
               |
               +------------+
               |            |
         [usb_serial.*]     |
               |            |
               |            |
      +---------------------+
      |                     |
      |                     |
  [usbcdc.*]            [delay.*]
```

### Built With
* [PlatformIO IDE](https://platformio.org/platformio-ide) - IDE used for programming
* [libopencm3](https://github.com/libopencm3/libopencm3) - Open-source low-level hardware library for ARM Cortex-M microcontrollers

### Author
**Daniel Duller** - [dadul96](https://github.com/dadul96)

### License
This project is licensed under the GPL-3.0 License - see the [LICENSE](LICENSE) file for details

### Based on my existing project for the STM32F103CB_Maple_Mini_Clone:
[STM32F103CB_Maple_Mini_Clone_USB_CDC_Serial](https://github.com/dadul96/STM32F103CB_Maple_Mini_Clone_USB_CDC_Serial/blob/main/README.md)


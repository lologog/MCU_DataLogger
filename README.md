# MCU Data Logger

## Project description
In many embedded systems, there is often a lack of non-volatile or a dedicated mechanism for long-term data logging. Sensor readings, digital signals or communication data are frequently lost or must be transmitted in real time, which can be inconvenient or require constant infrastructure.

To address this limitation, I developed a compact data logger that acts as an independent module capable of storing data for later analysis. The device can capture data from digital or receive custom data frames sent by other devices via a communication bus.

## Project Goals and Scope 
- Design and build a complete embedded data-logging system including hardware, firmware and mechanical dasign.
- Capture data from digital inputs or communication frames transmitted over a bus.
- Store data safely in non-volatile memory (using internal CPU EEPROM or two external I<sup>2</sup>C chips).
- Provide a user interface for operation control and system status.
- Include a custom 3D-printed enclosure to protect the electronics and ensure ease of installation.

## Hardware desing
The hardware is build around an ATmega328p microcontroller running with an external 16MHz crystal oscillator, ensuring stable and precise timing for all operations.
Data may be stored in two external 24LC1025 I<sup>2</sup>C EEPROM chips, which provide a large amount of non-volatile memory for long-term data logging. An additional DS1337S+ RTC module keeps accurate time for timestamping logged events.

The board includes two LEDs: one serves as a power indicator, while the second is user-programmable and can be freely controlled by the firmware for signaling various system states.
Externam connection are provided for 5 V power input, six digital inputs and accompanying +5 V and GND rails for convienient sensor or signal wiring. Communication and programming interfaces are also available through UART, II<sup>2</sup>C and SPI/ICSP headers.

The PCB has been designed with mechanical integration in mind.
It can be easily mounted inside the custom 3D-printed enclosure, with precisely aligned M2 mounting holes and standoff positions that provide a secure fit between the base and the upper part of the case.

![](Images/PCB-3D-Render.png)
*3D render of the PCB board made in KiCad software*

---

![](Images/board.jpg)
*Finished PCB board*

---

![](Images/board-with-bottom.jpg)
*PCB board with bottom part of the enclosure*

---

![](Images/finished-cover.jpg)
*Assembled device*

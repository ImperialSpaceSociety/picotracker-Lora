# Pico Ballon Tracker using LoRaWAN


## Objectives
This Pico balloon tracker is a new version to be designed by Imperial College Space Society. It is intended to offer an easy to build and low cost entry for people who want to launch small Helium filled balloons with a small tracking payload while using the Things Network LoRaWAN Network to receive the telemetry data from the balloon.

 implentation objective is to fly a small ballon around the world and to track it using the Things Network and HabHub.

## Major components
As of now, 19/10/19, we have settled on the following components to go on the tracker solution

### Tracker

* Murata ABZ LoRa Module MCU with 868MHz LoRaWAN Radio and 32 Bit ARM CPU
* Ublox Max M8Q GPS module
* MS8607 Pressure temp humidity sensor
* Solar Power Management
* Peripheral Power Control to minimise power consumption
* Possible small Energy storage by battery or super capacitor
* Reset Manager to ensure no corruption in case of brown outs
The moto: KEEP IT SIMPLE

### TTN2HabHub Bridge

* Subscribe to Things Network Application for data from trackers
* Store Tracker data and meta data showing gateway information
* Forward tracking data to HabHub
* Possibly send data back to tracker

### Launch Gateway

* Portable Things Network LoRaWAN Gateway
* Cellular Internet Access to Things Network
* GPS
* Local Gateway Status Display
* Local Payload Data display

### Balloon

* Low cost 36 inch super pressure balloon
* Prestressed
* Helium Filled


# Flights
* ICSPACE15: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/01/long-range-lora-balloon-tracker-launch-from-london/)
* ICSPACE16: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/02/balloon-flights-to-austria-and-slovakia/)
* ICSPACE17: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/02/balloon-flights-to-austria-and-slovakia/)
* ICSPACE18: Was lost after launch
* ICSPACE19: Pure solar tracker to be launched 16/3/20


# Design Files
The PCBs are designed with Kicad and the latest designs can be found in the [hardware folder]("Current%20Tracker%20Prototype/hardware/Kicad/"). We have two designs, the V1.2a and the V1.2b. V1.2a is a fully solar powered tracker with no power storage. The solar cells are directly wired to VCC and GND to power all components. V1.2b has a 50mAh lipo on board for power storage. The MPPT IC on board, the SPV1040, extracts maximum current from the cells to charge the battery.


# Software
We use the KEIL IDE to program the tracker. KEIL can be downloaded and used free of charge for the STM32L0 series of microcontrollers. You will be able to download Keil from [here](https://www2.keil.com/stmicroelectronics-stm32/mdk). Make sure you activate it so that you can compile files greater than 30kb of flash.

The software on the latest tracker can be found in the [Software folder](Software). You need to navigate to ``Software/Projects/B-L072Z-LRWAN1/Applications/LoRa/End_Node/MDK-ARM/`` and you can open the KEIL project by clicking ``Lora.uvprojx``

# Photos
These are photos of ICSPACE19 before launch, during testing in the sun. It is a 1.1a variant, with no power storage.

![In the sun](/Photos/20200316_124231.jpg "In the sun")
![In the sun](/Photos/20200316_124347.jpg "In the sun")
![In the sun](/Photos/20200316_125523.jpg "In the sun")
![In the sun](/Photos/20200316_130210.jpg "In the sun")


## License

Hardware is Licensed under CERN OHL v.1.2 or later https://www.ohwr.org/documents/294 No warranty is provided for this documentation implied or otherwise.

Software is licensed under MIT License.

MIT License

Copyright (c) 2018 Imperial College Space Society

Derived Software  Copyright (c) 2014  Richard Meadows <richardeoin>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

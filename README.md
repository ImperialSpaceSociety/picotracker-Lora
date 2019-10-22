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



## License

Hardware is Licensed under CERN OHL v.1.2 or later https://www.ohwr.org/documents/294 No warranty is provided for this documentation implied or otherwise.

Software is licensed under MIT License.

MIT License

Copyright (c) 2018 Imperial College Space Society

Derived Software  Copyright (c) 2014  Richard Meadows <richardeoin>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.




























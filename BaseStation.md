# Ideas for Imperial College HAB Ground Station



The HAB base station is proposed to be installed on the roof of the 10 story Electrical Engineering Building at Imperial College South Kensington. 
It will be used to receive and transmit telemetry with high altitude balloons. 

## Objectives
* Safe, secure,  and College Approved installation
* High reliability - 12 month preventative maintenance cycle
* Remote controlled and managed
* Improve logistics for Wormwood Scrubs launches.  Reduce need for launch site tracking
* Support of Open HAB community by tracking balloons in UK near-space
* Establish Imperial College Base Station as a high quality and trusted monitoring station for near space activity in the UK Region.

## Applications
* To track balloons launched by the Imperial College Space Society, especially during launches from London
* To track radiosondes launched by the Meterological service and add to a central database, [sondehub.org](https://tracker.sondehub.org)

## Frequencies and Modes

### Receive
* 70cm Amateur Band
* License exempt  433.05 - 434.79 MHz. All Modes, including  LoRa.
*  ??? 2m Amateur band, APRS mode
*  ??? License exempt 868 MHz
### Transmit
* License exempt  434.040– 434.790 MHz 10 mW ERP 25 kHz bandwidth and 433.05 - 434.79 MHz 1mW ERP 25kHz bandwidth. All Modes, including  LoRa.
* No transmission in Amateur Bands



## Radio Hardware
* SDR Radio on Raspberry Pi
* LoRa shield on Raspberry Pi

## Radio Firmware
* Multi channel RTTY reception
* Remote tuning
* Interface to HAB Hub

## Antenna
* 434MHz colinear
* ??? one or two, amplifier and splitter? Front end SAW filters ? TX/RX switching?
* ??? 2m
* ??? 868MHz
* Do we need lightening protection ?


## Utilities
* Power over Ethernet
* 10/100 Mbps Ethernet on IC network

## Physical
* IP68 Enclosure
* ??? Cabling
* ??Mounting hardware



## License

Hardware is Licensed under CERN OHL v.1.2 or later https://www.ohwr.org/documents/294 No warranty is provided for this documentation implied or otherwise.

Software is licensed under MIT License.

MIT License

Copyright (c) 2018 Imperial College Space Society

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.





























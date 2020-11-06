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
* ICSPACE19: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/03/launch-of-icspace19/)
* ICSPACE20 & 21: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/10/icspace21-flight-to-japan-and-icspace20/)


# Design Files
The PCBs are designed with Kicad and the latest designs can be found in the [hardware folder](Current%20Tracker%20Prototype/hardware/Kicad/). We have two designs, the V1.2a and the V1.2b. V1.2a is a fully solar powered tracker with no power storage. The solar cells are directly wired to VCC and GND to power all components. V1.2b has a 50mAh lipo on board for power storage. The MPPT IC on board, the SPV1040, extracts maximum current from the cells to charge the battery.


# Software
We use the KEIL IDE to program the tracker. KEIL can be downloaded and used free of charge for the STM32L0 series of microcontrollers. You will be able to download Keil from [here](https://www2.keil.com/stmicroelectronics-stm32/mdk). Make sure you activate it so that you can compile files greater than 30kb of flash.

The software on the latest tracker can be found in the [Software folder](Software). You need to navigate to ``Software/Projects/B-L072Z-LRWAN1/Applications/LoRa/End_Node/MDK-ARM/`` and you can open the KEIL project by clicking ``Lora.uvprojx``

# Photos
These are photos of ICSPACE19 before launch, during testing in the sun. It is a 1.1a variant, with no power storage.

![In the sun](/Photos/20200316_124231.jpg "In the sun")
![In the sun](/Photos/20200316_124347.jpg "In the sun")
![In the sun](/Photos/20200316_125523.jpg "In the sun")
![In the sun](/Photos/20200316_130210.jpg "In the sun")

# Instructions for special tests of multiregion Lorawan

In this test, I want to test if the tracker will work properly over US915. We have had issues where some packets over Canada contained no payload data. I don't know the root cause. Could be power supply issues. To narrow down causes, I have created this test, to be run on the B-L072Z-LRWAN1.

This test will:
1. transmit every 2 minutes
2. a packet the size of our typical message
3. on US915 frequencies.

I want to find out if we receive any empty packets.

## How to run the program

Clone this project and switch to branch `multi-region-tests`. All tests on multi region lorawan will be here.
Navigate to `picotracker-Lora/Software/Projects/B-L072Z-LRWAN1/Applications/LoRa/End_Node/MDK-ARM/` and run `Lora.uvprojx` with Keil.

After opening the Keil project, switch the firmware config to work on the B-L072Z-LRWAN1 dev board. This can be done as follows: ![image](https://user-images.githubusercontent.com/26815217/98421499-5a224f00-2081-11eb-8eb2-aedb4195027d.png)

Now compile and upload the code into the dev board.

The board will output debug information at `20000000` baud. I normally use the Arduino editor's inbuilt terminal. ![image](https://user-images.githubusercontent.com/26815217/98421622-a5d4f880-2081-11eb-9401-e1e49dbddd8e.png)


An expected output on the terminal will look like this. It will initialise, and transmit a packet every 2 minutes. This packet will be the same size as the ones transmitted over Canada on ICSPACE22 and will be transmitting on US915 freqencies. This will replicate the same parameters of ICSPACE22 over Canada, where we saw that some packets did not contain any data at all. Note that this program will not need any peripherals(GPS, sensors etc).
```


************************************ 
* Picotracker Lora                 * 
* Imperial College Space Society   * 
************************************ 

SELFTEST: Initialising Hardware
SELFTEST: LED should blink now
SELFTEST: Now initing sensors
SELFTEST: Initialisng ms5607
SELFTEST: Now the radio should transmit
APP DUTY CYCLE(TX INTERVAL maybe longer depending on message length and datarate) : 12000
ABP
DevEui= 00-AB-DF-8A-62-F5-C1-81
DevAdd=  26011673
NwkSKey= D1 21 88 24 49 F6 0C 62 C0 C1 EF 4E FC 24 EC E4
AppSKey= 8F 3C F3 ED 51 FE 03 64 EC 0E 1A 06 6D 41 FC 9D

READING SENSOR AND GPS
================================================================
SENSOR AND GPS VALUES
================================================================
Temperature degrees C: 0.000000
Pressure mBar: 0.000000
Longitude: 0.000000 Latitude: 0.000000 altitude: 0
Solar voltage no load: 3
Solar voltage with GPS load: 0
================================================================
TX on freq 904600000 Hz at DR 4
⸮  1s615ms: PHY txDone
⸮RX on freq 923900000 Hz at DR 13
⸮  2s646ms: PHY rxTimeOut
⸮RX on freq 923300000 Hz at DR 8
⸮  3s698ms: PHY rxTimeOut
  3s707ms: APP> McpsConfirm STATUS: OK

  3s707ms: #= U/L FRAME 6640 =# Class A, Port 99, data size 26, pwr 2, Channel Mask FF00 

⸮READING SENSOR AND GPS

================================================================
SENSOR AND GPS VALUES
================================================================
Temperature degrees C: 0.000000
Pressure mBar: 0.000000
Longitude: 0.000000 Latitude: 0.000000 altitude: 0
Solar voltage no load: 3
Solar voltage with GPS load: 0
================================================================
TX on freq 904600000 Hz at DR 4
⸮ 13s642ms: PHY txDone
⸮RX on freq 923900000 Hz at DR 13
⸮ 14s673ms: PHY rxTimeOut
⸮RX on freq 923300000 Hz at DR 8
⸮ 15s726ms: PHY rxTimeOut
 15s735ms: APP> McpsConfirm STATUS: OK

 15s735ms: #= U/L FRAME 6641 =# Class A, Port 99, data size 26, pwr 2, Channel Mask FF00 
```
### Speed up debugging tips
If you want to speed up the process for debugging, in `main.h`, you can set `APP_TX_DUTYCYCLE` to a lower value to increase the frequency of transmissions.
```c
#define APP_TX_DUTYCYCLE                           120000
```

For debugging, you can switch the end node to transmit on EU868 frequencies by making the following changes to `geofence.c`
```c
LoRaMacRegion_t current_loramac_region = LORAMAC_REGION_EU868;  // Loramac region EU868
Polygon_t curr_poly_region = EU863870_EUROPE_polygon; // Europe is in this polygon
```


### Verify the data(the actual test)
Now if everything is working on the end node side, it is time to see what is appearing on the TTN console. 
You should be able to see packets of data that look something like this. The important thing is, in order to pass this test, every packet should have a `payload_raw` and `payload_fields` section. During ICSPACE22's flight over Canada, we found that some packets did not contain the `payload_fields` section. I want to find out if it is a software issue that causes it.

Note, that every single piece of MQTT data is archived [here](http://medadnewman.co.uk/wp-content/uploads/2020/10/mqtt_log_data-1.txt) for reference. 
```json
{
  "app_id": "icss_lora_tracker",
  "dev_id": "icspace23",
  "hardware_serial": "0093BECA9134091B",
  "port": 99,
  "counter": 6603,
  "payload_raw": "AHN2YwFnERICiAAAAAAAAAAAAAMCAAAEAQA=",
  "payload_fields": {
    "analog_in_3": 0,
    "barometric_pressure_0": 3030.7,
    "digital_out_4": 0,
    "gps_2": {
      "altitude": 0,
      "latitude": 0,
      "longitude": 0
    },
    "temperature_1": 437
  },
  "metadata": {
    "time": "2020-11-06T22:20:03.034197954Z",
    "frequency": 868.5,
    "modulation": "LORA",
    "data_rate": "SF8BW125",
    "airtime": 154112000,
    "coding_rate": "4/5",
    "gateways": [
      {
        "gtw_id": "eui-58a0cbfffe800f4d",
        "timestamp": 3440028508,
        "time": "2020-11-06T22:20:03.082736968Z",
        "channel": 0,
        "rssi": -67,
        "snr": 8.5,
        "rf_chain": 0
      }
    ]
  }
}

```

## License

Hardware is Licensed under CERN OHL v.1.2 or later https://www.ohwr.org/documents/294 No warranty is provided for this documentation implied or otherwise.

Software is licensed under MIT License.

MIT License

Copyright (c) 2018 Imperial College Space Society

Derived Software  Copyright (c) 2014  Richard Meadows <richardeoin>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# Pico Ballon Tracker using LoRaWAN


## Objectives
This Pico balloon tracker is a new version to be designed by Imperial College Space Society. It is intended to offer an easy to build and low cost entry for people who want to launch small Helium filled balloons with a small tracking payload while using the Things Network LoRaWAN Network to receive the telemetry data from the balloon.

 implentation objective is to fly a small balloon around the world and to track it using the Things Network and HabHub.

## Major components
We have settled on the following components to go on the tracker solution. 

### Tracker

* Murata ABZ LoRa Module MCU with 868MHz LoRaWAN Radio and 32 Bit ARM CPU
* Ublox Max M8Q GPS module
* MS8607 Pressure temp humidity sensor
* Solar Power Management
* Possible small Energy storage by battery or super capacitor
The moto: KEEP IT SIMPLE

### TTN2HabHub Bridge

* Subscribe to Things Network Application for data from trackers
* Store Tracker data and meta data showing gateway information
* Forward tracking data to HabHub
* Possibly send data back to tracker
The bridge can be found in a seperate repo: [link](https://github.com/ImperialSpaceSociety/ttnhabbridge)

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

### Tracker Firmware
All firmware used in the trackers can be found here: https://github.com/ImperialSpaceSociety/LoRaMac-node. Its a fork of the Semtech Loramac-node reference firmware.
Note that the code in the current repo is no longer used and is used for reference only.


# Flights
* ICSPACE15: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/01/long-range-lora-balloon-tracker-launch-from-london/)
* ICSPACE16: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/02/balloon-flights-to-austria-and-slovakia/)
* ICSPACE17: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/02/balloon-flights-to-austria-and-slovakia/)
* ICSPACE18: Was lost after launch
* ICSPACE19: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/03/launch-of-icspace19/)
* ICSPACE20 & 21: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/10/icspace21-flight-to-japan-and-icspace20/)
* ICSPACE22: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/12/first-unconfirmed-circumnavigation-of-the-earth-by-ic-space-society-balloon-icspace22/)
* ICSPACE23: [Flight report](https://www.union.ic.ac.uk/guilds/icseds/2020/12/icspace23-launch/)


Past flight paths may be viewed on the [map](https://charts.mongodb.com/charts-project-0-wlibw/public/dashboards/487e7641-c649-4822-abc5-f70eb2e155c7).

# Design Files
The PCBs are designed with Kicad and the latest designs can be found in the [hardware folder](hardware/Kicad/). We have two designs, the a and the b variant. a variant is a fully solar powered tracker with no power storage. The solar cells are directly wired to VCC and GND to power all components. b variant has a 50mAh lipo on board for power storage. The MPPT IC on board, the SPV1040, extracts maximum current from the cells to charge the battery.

As of 29/12/2020, the latest flight proven design is V1.3a. The b variant has not been flown yet.

The schematic of v1.3a is here:
![image](https://user-images.githubusercontent.com/26815217/106533760-9f241900-64ea-11eb-973e-2e89387200ad.png)

Assembled tracker:
![image](https://www.union.ic.ac.uk/guilds/icseds/wp-content/uploads/2020/02/image-1.png)
PCB top layer(v1.3a): 
![image](https://user-images.githubusercontent.com/26815217/106533861-cc70c700-64ea-11eb-835c-9b979e27da77.png)

PCB bottom layer(v1.3a):
![image](https://user-images.githubusercontent.com/26815217/106533954-f6c28480-64ea-11eb-96bf-7d412425363a.png)

# Software
We use the KEIL IDE to program the tracker. KEIL can be downloaded and used free of charge for the STM32L0 series of microcontrollers. You will be able to download Keil from [here](https://www2.keil.com/stmicroelectronics-stm32/mdk). Make sure you activate the licence so that you can compile files greater than 30kb of flash. There is no cost for the licence.

We use the ST link to program the STM32L0 microncontroller. You will likely need the ST-link Driver, which can be downloaded from their website: [link]( https://www.st.com/en/development-tools/stsw-link009.html#get-software)



To get the picotracker firmware, run the following to clone the repo. Useful tip: Ensure the repo is cloned to the root folder e.g. `C:\` because there have been issues with the path lengths of the files getting too long for Windows to handle. The repo has very very long paths, a legacy of the LoRaWAN firmware stack by STMicroelectronics.
```bash
git clone https://github.com/ImperialSpaceSociety/picotracker-Lora.git
```
The software on the latest tracker can be found in the [Software folder](Software). You need to navigate to ``Software/Projects/B-L072Z-LRWAN1/Applications/LoRa/End_Node/MDK-ARM/`` and you can open the KEIL project by clicking ``Lora.uvprojx``

Once you open Keil, it should look like this. Ensure that the 1.3a_variant of the code is selected(highlighted in picture): ![image](https://user-images.githubusercontent.com/26815217/103182972-58b61b80-48a7-11eb-9189-2644d05e65e5.png)

You will have to tell Keil that you are using the ST-link programmer. To do that, go to the `flash` drop down menu and select `Configure Flash Tools`. Then switch to the `debug` tab and ensure the drop down menu is set to `St-Link Debugger` as shown in the picture below. Then click the `settings` button.
![image](https://user-images.githubusercontent.com/26815217/116629594-75dc2300-a949-11eb-9cd3-9d6b046c3bca.png)

When you open up the settings menu, it should look like this: 
![image](https://user-images.githubusercontent.com/26815217/116629664-9e641d00-a949-11eb-9dad-fd3ef9710a46.png)

Now that your st-link debugger is setup, its time to compile and program. Ensure the ST-link programmer is connected to the tracker, and hit compile and then upload or debug. Note: Its necessary to compile before uploading, or it will not have the latest hex file to flash to the tracker.
![image](https://user-images.githubusercontent.com/26815217/116326533-962aa700-a7bc-11eb-8606-af7147ce3ca0.png)


# Software overview
The picotracker state machine is as follows: 
It gets a GPS fix every 2 minutes and transmits it to ground

![image](https://user-images.githubusercontent.com/26815217/98449495-002a9380-212c-11eb-80c6-c811061492fa.png)

### Edits done over the reference version by STMicroelectronics
* Switching LoRaMAC regional settings depending on where it is
* Reduce tx power over US915/AU915
* Prevent sending empty frame after boot
* Use subband of 8 channels for US915/AU915
* Seperate credentials for each region of the world. 
* Prevent sticky uplinks after receiving channel change requests. Actually prevent any uplinks to test channel change requests. Wait till the next scheduled uplink.
* Different datarate for each region
* Polling specific date ranges for eeprom records
* 
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

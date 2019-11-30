/**
  @page FP-ATR-LORA1 Readme file
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  Central Labs
  * @version V2.1.1
  * @date    10-Oct-2019
  * @brief   This application is an IoT tracker node with LoRa connectivity, 
  *          GNSS and sensors 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
   @endverbatim

@par Application Description 

FP-ATR-LORA1 is an STM32Cube function pack which lets you read data from environmental and motion sensors, 
retrieve geo-position from GNSS and send collected data via LoRaWAN connectivity.

The package supports STEVAL-STRKT01 evaluation board.
It implements low power profiles and related transitions to ensure long battery autonomy.

Data acquired are The GPS coordinates as well as temperature, humidity, pressure and accelerometer data.

The application connects to LoRaWAN network by an external gateway, e.g. a MultiTech Conduit LoRa gateway
model.

The data are sent to the LoRaWAN network server and then forwarded to application server to be displayed
on a web dashboard. In order to exploit these services, the user needs to register to the services and to properly
configure the accounts and the application, which needs to be recompiled and flashed.

In detail, the file inc/Commissioning.h needs to be updated with the following information:
- Device EUI code goes after #define LORAWAN_DEVICE_EUI
- Join EUI code goes after #define LORAWAN_JOIN_EUI
- Application Key code goes after #define LORAWAN_APP_KEY
- Network Key code goes after #define LORAWAN_NWK_KEY

As an alternative, you can provision the board using the USB connection: type "?" and hit <ENTER> for information
and refer to FP-ATR-LORA1 user manual for details.

The software application works as a state machine with the following states: Run, Read, Send, Low Power and
Ultra Low Power.
- in Run state, the application monitors environmental sensors values and switches to Send state in case 
  of accelerometer wake up event, or switches to Low Power state in case accelerometer inactivity event.
- in Low Power state, the MCU enters in Sleep mode waiting for accelerometer interrupt
- in Ultra Low Power state, the MCU enters in Stop mode waiting for interrupt
- in Read state, the application gathers data from environmental, accelerometer and GNSS
- in Send state, the application sends data to the LoRaWAN network packed in a single message

@par Hardware and Software environment

  - STEVAL-STRKT01 evaluation board.

  - an ST-LINKv2 (you can use a Nucleo board (e.g. NUCLEO-F401RE), connect CN4(SWD) to CN501 of STEVAL-STRKT01

  - A LoRaWAN gateway is required.

  - Network and application server free user accounts are required.

  - A development PC for building the application, programming through ST-Link, and running the virtual console.


@par How to use it ? 

Application build and flash
  - Open and build the project with one of the supported development toolchains (see the release note
    for detailed information about the version requirements).

  - Choose the right settings, according to your region: the application is configured to run EU868 region,
    you can change this setting in the compiler preprocessor options (e.g. to use in US915 region)
	
  - Program the firmware on STEVAL-STRKT01 board: you can copy (or drag and drop) the generated .bin
    file to the USB mass storage location created when you plug the board to your PC. 
    If the host is a Linux PC, the STM32 device can be found in 
    the /media folder with the name e.g. "DIS_L4IOT". For example, if the created mass 
    storage location is "/media/DIS_L4IOT", then the command to program the board 
    with a binary file named "my_firmware.bin" is simply: cp my_firmware.bin 
    /media/DIS_L4IOT. 

   Alternatively, you can program the STEVAL-STRKT01 board directly through one of the 
   supported development toolchains.
 

Application first launch

  - Connect the board to your development PC through USB (STEVAL-STRKT01 USB port).
    Open the console through serial terminal emulator (e.g. TeraTerm), select the ST-LINK COM port of your
    board and configure it with 8N1, 115200 bauds, no HW flow control.


Application runtime 
  - After reset the application runs the state machine, switching from one state to another as explained.
  
  - The data are sent to the LoRa gateway and then to the network server, where they are forwarded to the application server.
  
  - The user can connect to the application server web site to see the data displayed on a dashboard.
  

@par STM32Cube packages:
  - STM32L0xx drivers from STM32CubeL0 V1.8.1
@par X-CUBE packages:
  - X-CUBE-LRWAN1 V1.2.1
  - X-CUBE-GNSS1 V2.0.0
  - X-CUBE-MEMS1 V5.0.0 


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */


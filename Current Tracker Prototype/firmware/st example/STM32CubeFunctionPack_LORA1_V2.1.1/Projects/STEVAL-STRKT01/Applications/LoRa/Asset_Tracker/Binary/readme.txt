In these folders, compiled images of the firmware are provided, in order to allow the user to test the application in a quick and easy way.

STEVAL_STRKT01_868.bin contains the entire FP-ATR-LORA1 application for EU868 region (use REGION_EU868 define in the compiler preprocessor)
STEVAL_STRKT01_915.bin contains the entire FP-ATR-LORA1 application for US915 region (use REGION_US915 define in the compiler preprocessor)
STEVAL_STRKT01_GetDevEui.bin contains a simple application to get the device EUI using USB virtual com connection. See FP-ATR-LORA1 user manual (UM2487) for details.

- Install ST-LINK drivers: http://www.st.com/web/catalog/tools/FM147/SC1887/PF260219
- Connect STEVAL-STRKT01 to an ST-LINK on an STM32 Nucleo board (e.g. NUCLEO-F401RE)
Connect CN4(SWD) to CN501 of STEVAL-STRKT01 (by 5 poles cable or by plugging directly on the STlink connector. (Pin1 CON4 of ST-LINKV2 has to be connected to Pin5 CON 501 of STEVAL-STRKT01).
Connect a USB A-to-TypeC adapter to the PC. Connect the typeC cable to the adapter.
Remove NUCLEO-F401RE CN2 jumpers
Connect the NUCLEO-F401RE BOARD to the PC through a USB A-to-miniB cable. 
Download the firmware.


The binaries can be flashed into the micro-controller flash memory using one of the procedures described below. 

- Procedure 1

1 - Plug the Nucleo Board to the host PC using a micro USB cable. If the ST-LINK driver is correctly installed, it will be recognize as an external memory device called "NUCLEO"
2 - Drag and drop or copy the binary file into the "NUCLEO" device you see in Computer
3 - Wait until flashing is complete.

- Procedure 2

1 - Install ST-LINK Utility: http://www.st.com/content/st_com/en/products/embedded-software/development-tool-software/stsw-link004.html.
2 - Plug the Nucleo Board to the host PC using a micro USB cable.
3 - Open the ST-LINK utility.
4 - Connect to the board selecting "Target -> Connect" from the menu or pressing the corresponding button.
5 - Open the binary file selecting "File -> Open File..." and choose the one you want to flash.
6 - From the menu choose: "Target -> Program"
7 - Check the Start address, it must be equal to 0x08000000.
8 - Click Start.
9 - Wait until flashing is complete.

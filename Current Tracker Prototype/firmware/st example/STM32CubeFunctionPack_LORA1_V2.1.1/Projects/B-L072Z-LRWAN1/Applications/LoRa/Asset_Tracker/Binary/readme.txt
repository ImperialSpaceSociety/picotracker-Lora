In these folders, compiled images of the firmware are provided, in order to allow the user to test the application in a quick and easy way.

mlm32l07x01_868.bin contains the entire FP-ATR-LORA1 application for EU868 region (use REGION_EU868 define in the compiler preprocessor)
mlm32l07x01_915.bin contains the entire FP-ATR-LORA1 application for US915 region (use REGION_US915 define in the compiler preprocessor)

- Install ST-LINK drivers: http://www.st.com/web/catalog/tools/FM147/SC1887/PF260219
- On the Nucleo board put JP5 jumper in U5V position 

The binaries are provided in both .bin and .hex format and can be flashed into the micro-controller flash memory using one of the procedures described below. 

- Procedure 1 (.bin only) -

1 - Plug the Nucleo Board to the host PC using a micro USB cable. If the ST-LINK driver is correctly installed, it will be recognize as an external memory device called "NUCLEO"
2 - Drag and drop or copy the binary file into the "NUCLEO" device you see in Computer
3 - Wait until flashing is complete.

- Procedure 2 (.hex and .bin) -

1 - Install ST-LINK Utility: http://www.st.com/content/st_com/en/products/embedded-software/development-tool-software/stsw-link004.html.
2 - Plug the Nucleo Board to the host PC using a micro USB cable.
3 - Open the ST-LINK utility.
4 - Connect to the board selecting "Target -> Connect" from the menu or pressing the corresponding button.
5 - Open the binary file selecting "File -> Open File..." and choose the one you want to flash.
6 - From the menu choose: "Target -> Program"
7 - Check the Start address, it must be equal to 0x08000000.
8 - Click Start.
9 - Wait until flashing is complete.




 
EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title ""
Date "2019-09-09"
Rev "1.0"
Comp "Imperial College Space Society"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6250 1700 6250 3500
Wire Wire Line
	6250 3500 6650 3500
$Comp
L power:GND #PWR0103
U 1 1 5D79E558
P 3050 3800
F 0 "#PWR0103" H 3050 3550 50  0001 C CNN
F 1 "GND" H 3055 3627 50  0000 C CNN
F 2 "" H 3050 3800 50  0001 C CNN
F 3 "" H 3050 3800 50  0001 C CNN
	1    3050 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5D79E562
P 2650 3500
F 0 "J4" H 2568 3717 50  0000 C CNN
F 1 "Conn_01x02" H 2568 3626 50  0000 C CNN
F 2 "Connector_JST:JST_PH_B2B-PH-K_1x02_P2.00mm_Vertical" H 2650 3500 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/1347/0900766b81347511.pdf" H 2650 3500 50  0001 C CNN
F 4 "0.38" H 2650 3500 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/pcb-headers/8201422/" H 2650 3500 50  0001 C CNN "Purchase link"
F 6 "5" H 2650 3500 50  0001 C CNN "min_quantity"
	1    2650 3500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3050 3800 3050 3600
Wire Wire Line
	3050 3600 2850 3600
$Comp
L power:PWR_FLAG #FLG0105
U 1 1 5D79E586
P 3300 3500
F 0 "#FLG0105" H 3300 3575 50  0001 C CNN
F 1 "PWR_FLAG" H 3300 3673 50  0000 C CNN
F 2 "" H 3300 3500 50  0001 C CNN
F 3 "~" H 3300 3500 50  0001 C CNN
	1    3300 3500
	1    0    0    -1  
$EndComp
Connection ~ 6250 3500
Wire Wire Line
	5600 1700 6150 1700
Text Notes 4400 3000 0    50   ~ 0
1A Ideal Diode with Ultra-Low Voltage Drop.\n43mV drop at 500mA draw
$Comp
L flight-computer:DFLS130L D3
U 1 1 5D72ADDD
P 5450 1700
F 0 "D3" H 5450 1484 50  0000 C CNN
F 1 "DFLS130L" H 5450 1575 50  0000 C CNN
F 2 "Diode_SMD:D_PowerDI-123" H 5450 1700 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30492.pdf" H 5450 1700 50  0001 C CNN
F 4 "0.36" H 5450 1700 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/diodes-inc/dfls130l-7/diode-schottky-30v-1a-powerdi123/dp/1843673?st=DFLS130L" H 5450 1700 50  0001 C CNN "Purchase link"
F 6 "5" H 5450 1700 50  0001 C CNN "min_quantity"
	1    5450 1700
	-1   0    0    1   
$EndComp
$Comp
L Regulator_Linear:LD3985G33R_TSOT23 U15
U 1 1 5D72F6F6
P 7250 3600
F 0 "U15" H 7250 3942 50  0000 C CNN
F 1 "LD3985M33R_TSOT23" H 7250 3851 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-5" H 7250 3925 50  0001 C CIN
F 3 "https://docs-emea.rs-online.com/webdocs/13e4/0900766b813e471a.pdf" H 7250 3650 50  0001 C CNN
F 4 "0.472" H 7250 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/low-dropout-voltage-regulators/6868802/" H 7250 3600 50  0001 C CNN "Purchase link"
F 6 "5" H 7250 3600 50  0001 C CNN "min_quantity"
	1    7250 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D71C023
P 5450 4300
F 0 "#PWR04" H 5450 4050 50  0001 C CNN
F 1 "GND" H 5455 4127 50  0000 C CNN
F 2 "" H 5450 4300 50  0001 C CNN
F 3 "" H 5450 4300 50  0001 C CNN
	1    5450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3900 5450 4300
$Comp
L power:GND #PWR0107
U 1 1 5D7321DF
P 7250 4300
F 0 "#PWR0107" H 7250 4050 50  0001 C CNN
F 1 "GND" H 7255 4127 50  0000 C CNN
F 2 "" H 7250 4300 50  0001 C CNN
F 3 "" H 7250 4300 50  0001 C CNN
	1    7250 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3900 7250 4300
$Comp
L Device:C C34
U 1 1 5D740EF6
P 7700 4000
F 0 "C34" H 7815 4046 50  0000 L CNN
F 1 "10nF" H 7815 3955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7738 3850 50  0001 C CNN
F 3 "~" H 7700 4000 50  0001 C CNN
F 4 "0.031" H 7700 4000 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8391727/" H 7700 4000 50  0001 C CNN "Purchase link"
F 6 "100" H 7700 4000 50  0001 C CNN "min_quantity"
	1    7700 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3600 7700 3600
Wire Wire Line
	7700 3600 7700 3850
$Comp
L power:GND #PWR0108
U 1 1 5D74339C
P 7700 4300
F 0 "#PWR0108" H 7700 4050 50  0001 C CNN
F 1 "GND" H 7705 4127 50  0000 C CNN
F 2 "" H 7700 4300 50  0001 C CNN
F 3 "" H 7700 4300 50  0001 C CNN
	1    7700 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 4300 7700 4150
Wire Wire Line
	6950 3600 6750 3600
Wire Wire Line
	6750 3600 6750 3500
Connection ~ 6750 3500
Wire Wire Line
	6750 3500 6950 3500
Wire Wire Line
	9100 3500 9100 3250
$Comp
L power:+3.3V #PWR0109
U 1 1 5D752620
P 9100 3250
F 0 "#PWR0109" H 9100 3100 50  0001 C CNN
F 1 "+3.3V" H 9115 3423 50  0000 C CNN
F 2 "" H 9100 3250 50  0001 C CNN
F 3 "" H 9100 3250 50  0001 C CNN
	1    9100 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3350 4650 3500
$Comp
L Analog_Switch:MAX40200AUK U14
U 1 1 5D719001
P 5450 3600
F 0 "U14" H 5450 3967 50  0000 C CNN
F 1 "MAX40200AUK" H 5450 3876 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 5450 4100 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX40200.pdf" H 5450 4100 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/node_under_construction/1697573/" H 5450 3600 50  0001 C CNN "Purchase link"
F 5 "0.729" H 5450 3600 50  0001 C CNN "Cost"
F 6 "10" H 5450 3600 50  0001 C CNN "min_quantity"
	1    5450 3600
	1    0    0    -1  
$EndComp
$Comp
L power:Vdrive #PWR045
U 1 1 5D722627
P 4650 3350
F 0 "#PWR045" H 4450 3200 50  0001 C CNN
F 1 "Vdrive" H 4667 3523 50  0000 C CNN
F 2 "" H 4650 3350 50  0001 C CNN
F 3 "" H 4650 3350 50  0001 C CNN
	1    4650 3350
	1    0    0    -1  
$EndComp
Connection ~ 4650 3500
Wire Wire Line
	4650 3500 4800 3500
Wire Wire Line
	5850 3500 6250 3500
Wire Wire Line
	4800 3500 4800 3700
Wire Wire Line
	4800 3700 5050 3700
Connection ~ 4800 3500
Wire Wire Line
	4800 3500 5050 3500
$Comp
L power:PWR_FLAG #FLG0107
U 1 1 5D773D0D
P 6150 1700
F 0 "#FLG0107" H 6150 1775 50  0001 C CNN
F 1 "PWR_FLAG" H 6150 1873 50  0000 C CNN
F 2 "" H 6150 1700 50  0001 C CNN
F 3 "~" H 6150 1700 50  0001 C CNN
	1    6150 1700
	1    0    0    -1  
$EndComp
Connection ~ 6150 1700
Wire Wire Line
	6150 1700 6250 1700
Connection ~ 8100 3500
Wire Wire Line
	8100 3500 9100 3500
Wire Wire Line
	7550 3500 8100 3500
Wire Wire Line
	8100 4300 8100 4150
$Comp
L power:GND #PWR059
U 1 1 5D79609B
P 8100 4300
F 0 "#PWR059" H 8100 4050 50  0001 C CNN
F 1 "GND" H 8105 4127 50  0000 C CNN
F 2 "" H 8100 4300 50  0001 C CNN
F 3 "" H 8100 4300 50  0001 C CNN
	1    8100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3500 8100 3850
$Comp
L Device:C C36
U 1 1 5D796090
P 8100 4000
F 0 "C36" H 8215 4046 50  0000 L CNN
F 1 "1uF" H 8215 3955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8138 3850 50  0001 C CNN
F 3 "~" H 8100 4000 50  0001 C CNN
F 4 "0.01" H 8100 4000 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/1358359/" H 8100 4000 50  0001 C CNN "Purchase link"
F 6 "250" H 8100 4000 50  0001 C CNN "min_quantity"
	1    8100 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4300 6650 4150
$Comp
L power:GND #PWR057
U 1 1 5D7A133A
P 6650 4300
F 0 "#PWR057" H 6650 4050 50  0001 C CNN
F 1 "GND" H 6655 4127 50  0000 C CNN
F 2 "" H 6650 4300 50  0001 C CNN
F 3 "" H 6650 4300 50  0001 C CNN
	1    6650 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3500 6650 3850
$Comp
L Device:C C35
U 1 1 5D7A1345
P 6650 4000
F 0 "C35" H 6765 4046 50  0000 L CNN
F 1 "1uF" H 6765 3955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6688 3850 50  0001 C CNN
F 3 "~" H 6650 4000 50  0001 C CNN
F 4 "0.01" H 6650 4000 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/1358359/" H 6650 4000 50  0001 C CNN "Purchase link"
F 6 "250" H 6650 4000 50  0001 C CNN "min_quantity"
	1    6650 4000
	1    0    0    -1  
$EndComp
Connection ~ 6650 3500
Wire Wire Line
	6650 3500 6750 3500
Connection ~ 3300 3500
Wire Wire Line
	2850 3500 3300 3500
Text Notes 8450 4100 0    50   ~ 0
May have to increase \nthe smoothing caps to 10uF \nfor stronger effect.
Text Notes 2300 3150 0    50   ~ 0
3.6V-4.2V Li-po input. Needs to be\nregulated down to 3.3V cmos
Text Notes 6700 3100 0    50   ~ 0
Ultra low drop out voltage regulator.\n140mV drop at max current of 150mA.
Text Notes 7350 5200 0    50   ~ 0
The maximum possible voltage drop(from 3.6V input) due to diode \nand LDO regulator is 173mV, leaving plenty of \nleeway to bring it down to 3.3V CMOS level.
Wire Wire Line
	4150 3500 4650 3500
Connection ~ 4150 3500
Wire Wire Line
	3300 3500 4150 3500
$Comp
L Connector:USB_B_Micro J?
U 1 1 5D941F3D
P 1900 1800
AR Path="/5D5B15F7/5D941F3D" Ref="J?"  Part="1" 
AR Path="/5D5B1705/5D941F3D" Ref="J2"  Part="1" 
F 0 "J2" H 1957 2267 50  0000 C CNN
F 1 "USB_B_Micro" H 1957 2176 50  0000 C CNN
F 2 "flight-computer:USB_Micro-B_Molex-105017-0001" H 2050 1750 50  0001 C CNN
F 3 "https://www.molex.com/webdocs/datasheets/pdf/en-us/1050170001_IO_CONNECTORS.pdf" H 2050 1750 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/micro-usb-connectors/8486764/?relevancy-data=636F3D3126696E3D4931384E53656172636847656E65726963266C753D656E266D6D3D6D61746368616C6C7061727469616C26706D3D5E5B5C707B4C7D5C707B4E647D2D2C2F255C2E5D2B2426706F3D31333326736E3D592673723D2673743D4B4559574F52445F53494E474C455F414C5048415F4E554D455249432673633D592677633D4E4F4E45267573743D3130353031372D30303031267374613D3130353031372D3030303126&searchHistory=%7B%22enabled%22%3Atrue%7D" H 1900 1800 50  0001 C CNN "Purchase link"
F 5 "0.694" H 1900 1800 50  0001 C CNN "Cost"
F 6 "5" H 1900 1800 50  0001 C CNN "min_quantity"
	1    1900 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 2350 1900 2500
Connection ~ 1900 2350
Wire Wire Line
	1800 2350 1900 2350
Wire Wire Line
	1800 2200 1800 2350
$Comp
L power:GND #PWR?
U 1 1 5D941F37
P 1900 2500
AR Path="/5D5B15F7/5D941F37" Ref="#PWR?"  Part="1" 
AR Path="/5D5B1705/5D941F37" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 1900 2250 50  0001 C CNN
F 1 "GND" H 1905 2327 50  0000 C CNN
F 2 "" H 1900 2500 50  0001 C CNN
F 3 "" H 1900 2500 50  0001 C CNN
	1    1900 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 2200 1900 2350
NoConn ~ 2200 2000
$Comp
L flight-computer:STF202-22T1G U9
U 1 1 5D8361E1
P 3450 2050
F 0 "U9" H 3450 1485 50  0000 C CNN
F 1 "STF202-22T1G" H 3450 1576 50  0000 C CNN
F 2 "Package_SO:TSOP-6_1.65x3.05mm_P0.95mm" H 3400 2500 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/STF202-22T1-D.PDF" H 3350 2050 50  0001 C CNN
F 4 "0.5" H 3450 2050 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/on-semiconductor/stf202-22t1g/active-analog-filter/dp/1651958?st=STF202-22T1G" H 3450 2050 50  0001 C CNN "Purchase link"
F 6 "1" H 3450 2050 50  0001 C CNN "min_quantity"
	1    3450 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4250 1800 3900 1800
Wire Wire Line
	3900 1900 4250 1900
Text HLabel 4250 1900 2    50   Input ~ 0
USB_DM
Text HLabel 4250 1800 2    50   Input ~ 0
USB_DP
Wire Wire Line
	3000 2100 2900 2100
Wire Wire Line
	2900 2100 2900 2450
$Comp
L power:GND #PWR?
U 1 1 5D85B471
P 2900 2450
AR Path="/5D5B15F7/5D85B471" Ref="#PWR?"  Part="1" 
AR Path="/5D5B1705/5D85B471" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 2900 2200 50  0001 C CNN
F 1 "GND" H 2905 2277 50  0000 C CNN
F 2 "" H 2900 2450 50  0001 C CNN
F 3 "" H 2900 2450 50  0001 C CNN
	1    2900 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 1600 2550 1600
Wire Wire Line
	4850 2100 4850 1700
Wire Wire Line
	4850 1700 5300 1700
Wire Wire Line
	2550 1600 2550 1250
$Comp
L power:VBUS #PWR0119
U 1 1 5D87B12F
P 4850 1350
F 0 "#PWR0119" H 4850 1200 50  0001 C CNN
F 1 "VBUS" H 4865 1523 50  0000 C CNN
F 2 "" H 4850 1350 50  0001 C CNN
F 3 "" H 4850 1350 50  0001 C CNN
	1    4850 1350
	1    0    0    -1  
$EndComp
Connection ~ 4850 1700
Wire Wire Line
	4850 1700 4850 1350
$Comp
L power:VBUS #PWR0120
U 1 1 5D87DB4D
P 2550 1250
F 0 "#PWR0120" H 2550 1100 50  0001 C CNN
F 1 "VBUS" H 2565 1423 50  0000 C CNN
F 2 "" H 2550 1250 50  0001 C CNN
F 3 "" H 2550 1250 50  0001 C CNN
	1    2550 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3500 4150 4650
Wire Wire Line
	2500 5000 4150 5000
Connection ~ 4150 5000
Wire Wire Line
	4150 5000 4150 5150
Wire Wire Line
	4150 4950 4150 5000
Text HLabel 2500 5000 0    50   Output ~ 0
PWR_BVOLTS
$Comp
L Device:R R28
U 1 1 5D759625
P 4150 4800
F 0 "R28" H 4220 4846 50  0000 L CNN
F 1 "120K" H 4220 4755 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4080 4800 50  0001 C CNN
F 3 "~" H 4150 4800 50  0001 C CNN
F 4 "0.035" H 4150 4800 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6789715/" H 4150 4800 50  0001 C CNN "Purchase link"
F 6 "50" H 4150 4800 50  0001 C CNN "min_quantity"
	1    4150 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R29
U 1 1 5D75961B
P 4150 5300
F 0 "R29" H 4220 5346 50  0000 L CNN
F 1 "120K" H 4220 5255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4080 5300 50  0001 C CNN
F 3 "~" H 4150 5300 50  0001 C CNN
F 4 "0.035" H 4150 5300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6789715/" H 4150 5300 50  0001 C CNN "Purchase link"
F 6 "50" H 4150 5300 50  0001 C CNN "min_quantity"
	1    4150 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5D759611
P 4150 5550
F 0 "#PWR0111" H 4150 5300 50  0001 C CNN
F 1 "GND" H 4155 5377 50  0000 C CNN
F 2 "" H 4150 5550 50  0001 C CNN
F 3 "" H 4150 5550 50  0001 C CNN
	1    4150 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 5550 4150 5450
Wire Wire Line
	3900 2100 4850 2100
Wire Wire Line
	2200 1900 3000 1900
Wire Wire Line
	3000 1800 2200 1800
$EndSCHEMATC

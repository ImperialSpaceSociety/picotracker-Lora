EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Pico lora tracker"
Date "2020-08-19"
Rev "1.3"
Comp "Imperial College Space Society"
Comment1 "Based on the Picotracker MK II and Project mach one flight computer"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC84019
P 6250 5750
AR Path="/5D5B15F7/5DC84019" Ref="#PWR?"  Part="1" 
AR Path="/5DC84019" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 6250 5500 50  0001 C CNN
F 1 "GND" H 6255 5577 50  0000 C CNN
F 2 "" H 6250 5750 50  0001 C CNN
F 3 "" H 6250 5750 50  0001 C CNN
	1    6250 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5750 6250 5400
Wire Wire Line
	5350 5200 5000 5200
Wire Wire Line
	5000 5200 5000 5300
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC84030
P 5000 5750
AR Path="/5D5B15F7/5DC84030" Ref="#PWR?"  Part="1" 
AR Path="/5DC84030" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 5000 5500 50  0001 C CNN
F 1 "GND" H 5005 5577 50  0000 C CNN
F 2 "" H 5000 5750 50  0001 C CNN
F 3 "" H 5000 5750 50  0001 C CNN
	1    5000 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5600 5000 5750
Wire Wire Line
	5350 4000 4450 4000
Wire Wire Line
	1350 1750 1650 1750
Wire Wire Line
	1350 1850 1650 1850
Text Label 4450 4100 0    50   ~ 0
SWCLK
Wire Wire Line
	4450 4100 5350 4100
Text Label 1650 1750 2    50   ~ 0
SWCLK
Text Label 1650 1850 2    50   ~ 0
SWDIO
Wire Notes Line
	550  700  550  3050
Wire Notes Line
	550  3050 2500 3050
Text Notes 700  2900 0    50   ~ 0
Debugging and programming\ninterface
Wire Wire Line
	1350 1950 1650 1950
Text Label 1650 1950 2    50   ~ 0
RESET
Text Label 3500 4300 0    50   ~ 0
RESET
Wire Wire Line
	6150 1350 6150 2250
Wire Wire Line
	6250 2250 6150 2250
Connection ~ 6150 2250
Wire Wire Line
	6150 1350 6450 1350
Wire Wire Line
	6450 1350 6450 1450
Wire Wire Line
	6450 1700 7200 1700
Connection ~ 6450 1350
Wire Wire Line
	6450 1350 7200 1350
Wire Wire Line
	7200 1350 7200 1450
Wire Wire Line
	6450 1650 6450 1700
Connection ~ 7200 1350
Connection ~ 7200 1700
Wire Wire Line
	7200 1700 7900 1700
Wire Wire Line
	7200 1350 7900 1350
Connection ~ 7900 1350
Wire Wire Line
	7900 1350 7900 1450
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DC8408D
P 7900 1050
AR Path="/5D5B15F7/5DC8408D" Ref="#PWR?"  Part="1" 
AR Path="/5DC8408D" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 7900 900 50  0001 C CNN
F 1 "+3.3V" H 7915 1223 50  0000 C CNN
F 2 "" H 7900 1050 50  0001 C CNN
F 3 "" H 7900 1050 50  0001 C CNN
	1    7900 1050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7900 1350 7900 1050
Wire Wire Line
	7200 1650 7200 1700
Wire Wire Line
	7900 1650 7900 1700
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC840A2
P 7900 1850
AR Path="/5D5B15F7/5DC840A2" Ref="#PWR?"  Part="1" 
AR Path="/5DC840A2" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 7900 1600 50  0001 C CNN
F 1 "GND" H 7905 1677 50  0000 C CNN
F 2 "" H 7900 1850 50  0001 C CNN
F 3 "" H 7900 1850 50  0001 C CNN
	1    7900 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 1850 7900 1700
Connection ~ 7900 1700
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC840FF
P 14650 3850
AR Path="/5D5B1586/5DC840FF" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC840FF" Ref="#PWR?"  Part="1" 
AR Path="/5DC840FF" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 14650 3600 50  0001 C CNN
F 1 "GND" H 14655 3677 50  0000 C CNN
F 2 "" H 14650 3850 50  0001 C CNN
F 3 "" H 14650 3850 50  0001 C CNN
	1    14650 3850
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC84105
P 14050 3850
AR Path="/5D5B1586/5DC84105" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84105" Ref="#PWR?"  Part="1" 
AR Path="/5DC84105" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 14050 3600 50  0001 C CNN
F 1 "GND" H 14055 3677 50  0000 C CNN
F 2 "" H 14050 3850 50  0001 C CNN
F 3 "" H 14050 3850 50  0001 C CNN
	1    14050 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	14650 3700 14650 3850
Wire Wire Line
	14250 3500 14050 3500
Wire Wire Line
	14050 3500 14050 3850
Wire Wire Line
	14250 3400 13950 3400
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC84110
P 15100 3000
AR Path="/5D5B1586/5DC84110" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84110" Ref="#PWR?"  Part="1" 
AR Path="/5DC84110" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 15100 2750 50  0001 C CNN
F 1 "GND" H 15105 2827 50  0000 C CNN
F 2 "" H 15100 3000 50  0001 C CNN
F 3 "" H 15100 3000 50  0001 C CNN
	1    15100 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	14650 2700 14650 2750
Wire Wire Line
	15100 2950 15100 3000
Wire Wire Line
	15100 2750 14650 2750
Connection ~ 14650 2750
Wire Wire Line
	14650 2750 14650 2900
Wire Wire Line
	14150 3100 14150 2750
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DC84121
P 14650 2700
AR Path="/5D5B1586/5DC84121" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84121" Ref="#PWR?"  Part="1" 
AR Path="/5DC84121" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 14650 2550 50  0001 C CNN
F 1 "+3.3V" H 14665 2873 50  0000 C CNN
F 2 "" H 14650 2700 50  0001 C CNN
F 3 "" H 14650 2700 50  0001 C CNN
	1    14650 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	14050 2100 14050 3300
Wire Wire Line
	12700 1050 12700 1400
Connection ~ 12700 2100
Wire Wire Line
	13000 2200 13000 1700
Connection ~ 13000 2200
Wire Wire Line
	13000 2200 13400 2200
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DC84141
P 12700 1050
AR Path="/5D5B1586/5DC84141" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84141" Ref="#PWR?"  Part="1" 
AR Path="/5DC84141" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 12700 900 50  0001 C CNN
F 1 "+3.3V" H 12715 1223 50  0000 C CNN
F 2 "" H 12700 1050 50  0001 C CNN
F 3 "" H 12700 1050 50  0001 C CNN
	1    12700 1050
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DC84147
P 13000 1050
AR Path="/5D5B1586/5DC84147" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84147" Ref="#PWR?"  Part="1" 
AR Path="/5DC84147" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 13000 900 50  0001 C CNN
F 1 "+3.3V" H 13015 1223 50  0000 C CNN
F 2 "" H 13000 1050 50  0001 C CNN
F 3 "" H 13000 1050 50  0001 C CNN
	1    13000 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12700 1700 12700 2100
Wire Wire Line
	13000 1400 13000 1050
Wire Wire Line
	12000 2200 13000 2200
Wire Wire Line
	12000 2100 12700 2100
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC84165
P 14050 8350
AR Path="/5D5B165E/5DC84165" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84165" Ref="#PWR?"  Part="1" 
AR Path="/5DC84165" Ref="#PWR0119"  Part="1" 
F 0 "#PWR0119" H 14050 8100 50  0001 C CNN
F 1 "GND" H 14055 8177 50  0000 C CNN
F 2 "" H 14050 8350 50  0001 C CNN
F 3 "" H 14050 8350 50  0001 C CNN
	1    14050 8350
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DC841BA
P 13850 5200
AR Path="/5D5B165E/5DC841BA" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC841BA" Ref="#PWR?"  Part="1" 
AR Path="/5DC841BA" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 13850 5050 50  0001 C CNN
F 1 "+3.3V" H 13865 5373 50  0000 C CNN
F 2 "" H 13850 5200 50  0001 C CNN
F 3 "" H 13850 5200 50  0001 C CNN
	1    13850 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	13300 6500 13300 6400
Wire Wire Line
	13650 6400 13650 6500
Wire Wire Line
	13650 6100 13300 6100
Wire Wire Line
	13650 6200 13650 6100
Wire Wire Line
	13300 6100 13300 6200
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DC841DF
P 13300 6600
AR Path="/5D5B17D8/5DC841DF" Ref="#PWR?"  Part="1" 
AR Path="/5D5B165E/5DC841DF" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC841DF" Ref="#PWR?"  Part="1" 
AR Path="/5DC841DF" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 13300 6350 50  0001 C CNN
F 1 "GND" H 13305 6427 50  0000 C CNN
F 2 "" H 13300 6600 50  0001 C CNN
F 3 "" H 13300 6600 50  0001 C CNN
	1    13300 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	13300 6600 13300 6500
Connection ~ 13300 6500
Wire Wire Line
	13300 6500 13650 6500
Wire Wire Line
	15300 7500 15300 7350
Text Notes 11200 4850 0    50   ~ 0
Pressure temperature humidity sensor\n
Text Notes 11200 9100 0    50   ~ 0
GPS circuit\n
Wire Notes Line
	500  11200 6950 11200
Wire Notes Line
	6950 11200 6950 6850
Wire Notes Line
	500  6850 500  11200
Text Notes 650  11100 0    50   ~ 0
Power supply\n
Wire Wire Line
	8600 5200 8600 5050
Text Label 12000 2100 0    50   ~ 0
I2C1_SDA
Text Label 12000 2200 0    50   ~ 0
I2C1_SCL
$Comp
L circuit-board-design-rescue:GND-power #PWR0102
U 1 1 5DEE121A
P 1450 9550
F 0 "#PWR0102" H 1450 9300 50  0001 C CNN
F 1 "GND" H 1455 9377 50  0000 C CNN
F 2 "" H 1450 9550 50  0001 C CNN
F 3 "" H 1450 9550 50  0001 C CNN
	1    1450 9550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 8350 5400 7850
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR0120
U 1 1 5DEE8C89
P 5400 7850
F 0 "#PWR0120" H 5400 7700 50  0001 C CNN
F 1 "+3.3V" H 5415 8023 50  0000 C CNN
F 2 "" H 5400 7850 50  0001 C CNN
F 3 "" H 5400 7850 50  0001 C CNN
	1    5400 7850
	1    0    0    -1  
$EndComp
Text Notes 3000 8400 0    50   ~ 0
6 x 0.5V solar cells
Wire Wire Line
	6450 2400 6450 2250
Wire Wire Line
	6250 2400 6250 2250
Wire Wire Line
	6150 2250 6150 2400
Wire Wire Line
	13950 6750 13850 6750
Connection ~ 13850 6750
Wire Wire Line
	13950 6750 14050 6750
Connection ~ 13950 6750
Wire Wire Line
	7150 3700 7800 3700
Text Label 12750 7700 0    50   ~ 0
GPS_EXTINT
Text Label 7800 3700 2    50   ~ 0
GPS_EXTINT
NoConn ~ 7150 4100
NoConn ~ 7150 4200
NoConn ~ 7150 4300
NoConn ~ 7150 4500
NoConn ~ 7150 4600
NoConn ~ 7150 4700
NoConn ~ 7150 4800
NoConn ~ 7150 4900
NoConn ~ 7150 5000
NoConn ~ 5350 3500
NoConn ~ 5350 3000
Wire Wire Line
	13850 6750 13850 6800
Wire Wire Line
	13950 6800 13950 6750
Wire Wire Line
	14050 6750 14050 6800
Wire Wire Line
	13450 7700 12750 7700
NoConn ~ 14250 6800
Wire Wire Line
	14650 7500 15300 7500
Wire Wire Line
	14050 8200 14050 8350
Wire Wire Line
	14650 7800 15500 7800
Text Label 15500 7800 2    50   ~ 0
GPS_TIMEPULSE
Wire Wire Line
	7150 3800 7800 3800
Text Label 7800 3800 2    50   ~ 0
GPS_TIMEPULSE
NoConn ~ 5350 4800
NoConn ~ 5350 4700
NoConn ~ 5350 4500
Wire Notes Line
	2500 650  2500 6850
Wire Notes Line
	500  6850 11100 6850
Wire Notes Line
	550  650  16050 650 
Wire Notes Line
	11100 650  11100 9150
Text Notes 3050 6550 0    50   ~ 0
Main Microcontroller + Lora tranceiver\n
$Comp
L circuit-board-design-rescue:MAX-M8C-RF_GPS U1
U 1 1 5DDCC018
P 14050 7500
F 0 "U1" H 13650 6700 50  0000 C CNN
F 1 "MAX-M8C" H 13650 6600 50  0000 C CNN
F 2 "RF_GPS:ublox_MAX" H 14450 6850 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/MAX-M8-FW3_DataSheet_%28UBX-15031506%29.pdf" H 14050 7500 50  0001 C CNN
	1    14050 7500
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:Antenna-Device AE1
U 1 1 5DE442FF
P 8600 4850
F 0 "AE1" H 8680 4839 50  0000 L CNN
F 1 "Lora Antenna" H 8680 4748 50  0000 L CNN
F 2 "pico_tracker:SolderWirePad_1x01_Drill0.8mm_square" H 8600 4850 50  0001 C CNN
F 3 "~" H 8600 4850 50  0001 C CNN
	1    8600 4850
	1    0    0    -1  
$EndComp
$Comp
L flight-computer:GPS_Antenna AE2
U 1 1 5DDA946B
P 15300 7150
F 0 "AE2" H 15380 7139 50  0000 L CNN
F 1 "GPS Antenna" H 15380 7048 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 15300 7150 50  0001 C CNN
F 3 "~" H 15300 7150 50  0001 C CNN
	1    15300 7150
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:C_Small-Device C?
U 1 1 5DC841D3
P 13650 6300
AR Path="/5D5B17D8/5DC841D3" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5DC841D3" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC841D3" Ref="C?"  Part="1" 
AR Path="/5DC841D3" Ref="C13"  Part="1" 
F 0 "C13" H 13558 6346 50  0000 R CNN
F 1 "10uF" H 13558 6255 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 13650 6300 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 13650 6300 50  0001 C CNN
F 4 "0.07" H 13650 6300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 13650 6300 50  0001 C CNN "Purchase link"
F 6 "100" H 13650 6300 50  0001 C CNN "min_quantity"
	1    13650 6300
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:C_Small-Device C?
U 1 1 5DC841CA
P 13300 6300
AR Path="/5D5B17D8/5DC841CA" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5DC841CA" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC841CA" Ref="C?"  Part="1" 
AR Path="/5DC841CA" Ref="C12"  Part="1" 
F 0 "C12" H 13208 6346 50  0000 R CNN
F 1 "100nF" H 13208 6255 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 13300 6300 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 13300 6300 50  0001 C CNN
F 4 "0.01" H 13300 6300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 13300 6300 50  0001 C CNN "Purchase link"
F 6 "50" H 13300 6300 50  0001 C CNN "min_quantity"
	1    13300 6300
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:R-Device R?
U 1 1 5DC8415A
P 13000 1550
AR Path="/5D5B1586/5DC8415A" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC8415A" Ref="R?"  Part="1" 
AR Path="/5DC8415A" Ref="R5"  Part="1" 
F 0 "R5" H 13070 1596 50  0000 L CNN
F 1 "4.7K" H 13070 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 12930 1550 50  0001 C CNN
F 3 "~" H 13000 1550 50  0001 C CNN
F 4 "0.01" H 13000 1550 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408877/" H 13000 1550 50  0001 C CNN "Purchase link"
F 6 "50" H 13000 1550 50  0001 C CNN "min_quantity"
	1    13000 1550
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:R-Device R?
U 1 1 5DC84150
P 12700 1550
AR Path="/5D5B1586/5DC84150" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC84150" Ref="R?"  Part="1" 
AR Path="/5DC84150" Ref="R4"  Part="1" 
F 0 "R4" H 12770 1596 50  0000 L CNN
F 1 "4.7K" H 12770 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 12630 1550 50  0001 C CNN
F 3 "~" H 12700 1550 50  0001 C CNN
F 4 "0.01" H 12700 1550 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408877/" H 12700 1550 50  0001 C CNN "Purchase link"
F 6 "50" H 12700 1550 50  0001 C CNN "min_quantity"
	1    12700 1550
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:C_Small-Device C?
U 1 1 5DC84133
P 15100 2850
AR Path="/5D5B1586/5DC84133" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC84133" Ref="C?"  Part="1" 
AR Path="/5DC84133" Ref="C14"  Part="1" 
F 0 "C14" H 15192 2896 50  0000 L CNN
F 1 "220nF" H 15192 2805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 15100 2850 50  0001 C CNN
F 3 "~" H 15100 2850 50  0001 C CNN
F 4 "0.003" H 15100 2850 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/0391135/" H 15100 2850 50  0001 C CNN "Purchase link"
F 6 "50" H 15100 2850 50  0001 C CNN "min_quantity"
	1    15100 2850
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:C_Small-Device C?
U 1 1 5DC8409B
P 7900 1550
AR Path="/5D5B15F7/5DC8409B" Ref="C?"  Part="1" 
AR Path="/5DC8409B" Ref="C10"  Part="1" 
F 0 "C10" H 7992 1596 50  0000 L CNN
F 1 "10uF" H 7992 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7900 1550 50  0001 C CNN
F 3 "~" H 7900 1550 50  0001 C CNN
	1    7900 1550
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:C_Small-Device C?
U 1 1 5DC84094
P 7200 1550
AR Path="/5D5B15F7/5DC84094" Ref="C?"  Part="1" 
AR Path="/5DC84094" Ref="C7"  Part="1" 
F 0 "C7" H 7292 1596 50  0000 L CNN
F 1 "1uF" H 7292 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7200 1550 50  0001 C CNN
F 3 "~" H 7200 1550 50  0001 C CNN
	1    7200 1550
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:C_Small-Device C?
U 1 1 5DC84080
P 6450 1550
AR Path="/5D5B15F7/5DC84080" Ref="C?"  Part="1" 
AR Path="/5DC84080" Ref="C5"  Part="1" 
F 0 "C5" H 6542 1596 50  0000 L CNN
F 1 "100nF" H 6542 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6450 1550 50  0001 C CNN
F 3 "~" H 6450 1550 50  0001 C CNN
	1    6450 1550
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:R-Device R?
U 1 1 5DC84036
P 5000 5450
AR Path="/5D5B15F7/5DC84036" Ref="R?"  Part="1" 
AR Path="/5DC84036" Ref="R3"  Part="1" 
F 0 "R3" H 5070 5496 50  0000 L CNN
F 1 "10K" H 5070 5405 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4930 5450 50  0001 C CNN
F 3 "~" H 5000 5450 50  0001 C CNN
	1    5000 5450
	1    0    0    -1  
$EndComp
NoConn ~ 5350 5000
Connection ~ 13650 6100
Wire Wire Line
	13850 6100 13850 6550
Wire Wire Line
	13850 6100 13650 6100
$Comp
L circuit-board-design-rescue:PWR_FLAG-power #FLG0101
U 1 1 5DBC451E
P 5200 8350
F 0 "#FLG0101" H 5200 8425 50  0001 C CNN
F 1 "PWR_FLAG" H 5200 8523 50  0000 C CNN
F 2 "" H 5200 8350 50  0001 C CNN
F 3 "~" H 5200 8350 50  0001 C CNN
	1    5200 8350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 8350 5400 8350
Text Label 4450 4000 0    50   ~ 0
SWDIO
Wire Wire Line
	6050 1350 6050 2400
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DC840B0
P 4750 1050
AR Path="/5D5B15F7/5DC840B0" Ref="#PWR?"  Part="1" 
AR Path="/5DC840B0" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 4750 900 50  0001 C CNN
F 1 "+3.3V" H 4765 1223 50  0000 C CNN
F 2 "" H 4750 1050 50  0001 C CNN
F 3 "" H 4750 1050 50  0001 C CNN
	1    4750 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1350 4750 1050
$Comp
L circuit-board-design-rescue:Conn_01x01-Connector_Generic J3
U 1 1 5DC8A70A
P 5900 8350
F 0 "J3" H 5980 8392 50  0000 L CNN
F 1 "3.3V" H 5980 8301 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 5900 8350 50  0001 C CNN
F 3 "~" H 5900 8350 50  0001 C CNN
	1    5900 8350
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:Conn_01x01-Connector_Generic J2
U 1 1 5DC8B635
P 1050 8350
F 0 "J2" H 968 8125 50  0000 C CNN
F 1 "GND" H 968 8216 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 1050 8350 50  0001 C CNN
F 3 "~" H 1050 8350 50  0001 C CNN
	1    1050 8350
	-1   0    0    1   
$EndComp
Wire Wire Line
	1450 9550 1450 8350
Wire Wire Line
	1250 8350 1450 8350
$Comp
L circuit-board-design-rescue:Conn_01x01-Connector_Generic SolarCellMount1
U 1 1 5DCBAB7A
P 9150 7650
F 0 "SolarCellMount1" H 9230 7692 50  0000 L CNN
F 1 "Unconnected" H 9230 7601 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 9150 7650 50  0001 C CNN
F 3 "~" H 9150 7650 50  0001 C CNN
	1    9150 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 8350 5400 8700
Connection ~ 5400 8350
$Comp
L circuit-board-design-rescue:GND-power #PWR01
U 1 1 5DCCDF86
P 5400 9600
F 0 "#PWR01" H 5400 9350 50  0001 C CNN
F 1 "GND" H 5405 9427 50  0000 C CNN
F 2 "" H 5400 9600 50  0001 C CNN
F 3 "" H 5400 9600 50  0001 C CNN
	1    5400 9600
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:R-Device R1
U 1 1 5DCCF4D3
P 5400 8850
F 0 "R1" H 5470 8896 50  0000 L CNN
F 1 "100K" H 5470 8805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5330 8850 50  0001 C CNN
F 3 "~" H 5400 8850 50  0001 C CNN
	1    5400 8850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 9000 5400 9100
$Comp
L circuit-board-design-rescue:R-Device R2
U 1 1 5DCD0192
P 5400 9350
F 0 "R2" H 5470 9396 50  0000 L CNN
F 1 "100K" H 5470 9305 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5330 9350 50  0001 C CNN
F 3 "~" H 5400 9350 50  0001 C CNN
	1    5400 9350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 9500 5400 9600
Wire Wire Line
	5400 9100 6050 9100
Connection ~ 5400 9100
Wire Wire Line
	5400 9100 5400 9200
Text Label 6050 9100 2    50   ~ 0
V_SOLAR
Wire Notes Line
	6950 9150 16050 9150
Text Notes 7700 7850 0    50   ~ 0
Structural plated throughole to hold the guitar wire solar cell structure
Wire Wire Line
	4750 1350 6050 1350
NoConn ~ 8950 7650
Wire Wire Line
	5350 3300 4450 3300
Wire Wire Line
	10850 3900 10850 4250
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DBBC44F
P 10850 4250
AR Path="/5D5B15F7/5DBBC44F" Ref="#PWR?"  Part="1" 
AR Path="/5DBBC44F" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 10850 4000 50  0001 C CNN
F 1 "GND" H 10855 4077 50  0000 C CNN
F 2 "" H 10850 4250 50  0001 C CNN
F 3 "" H 10850 4250 50  0001 C CNN
	1    10850 4250
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:LED-Device D1
U 1 1 5DBC4B62
P 10450 3900
F 0 "D1" H 10443 3645 50  0000 C CNN
F 1 "LED" H 10443 3736 50  0000 C CNN
F 2 "LED_SMD:LED_0402_1005Metric" H 10450 3900 50  0001 C CNN
F 3 "~" H 10450 3900 50  0001 C CNN
	1    10450 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	10600 3900 10850 3900
$Comp
L circuit-board-design-rescue:R-Device R6
U 1 1 5DBC5657
P 10150 3900
F 0 "R6" V 9943 3900 50  0000 C CNN
F 1 "1K" V 10034 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10080 3900 50  0001 C CNN
F 3 "~" H 10150 3900 50  0001 C CNN
	1    10150 3900
	0    1    1    0   
$EndComp
Wire Notes Line
	9350 4900 16050 4900
Wire Notes Line
	9350 650  9350 6850
Text Label 4450 3300 0    50   ~ 0
LED
Text Label 9550 3900 0    50   ~ 0
LED
Wire Wire Line
	10000 3900 9550 3900
Wire Notes Line
	11100 3250 9350 3250
Text Notes 9700 4700 0    50   ~ 0
LED indicator\n
$Comp
L circuit-board-design-rescue:Conn_01x01-Connector_Generic StringHole1
U 1 1 5DB85E84
P 9150 8150
F 0 "StringHole1" H 9230 8192 50  0000 L CNN
F 1 "Unconnected" H 9230 8101 50  0000 L CNN
F 2 "flight-computer:SolderWirePad_1x01_Drill0.8mm" H 9150 8150 50  0001 C CNN
F 3 "~" H 9150 8150 50  0001 C CNN
	1    9150 8150
	1    0    0    -1  
$EndComp
NoConn ~ 8950 8150
Text Notes 8950 8400 0    50   ~ 0
Hole to tie string\n
Text Notes 7100 9100 0    50   ~ 0
Structural holes\n
Text Label 4450 3900 0    50   ~ 0
TCXO_EN
Wire Wire Line
	5350 3900 4450 3900
$Comp
L circuit-board-design-rescue:Conn_01x01-Connector_Generic J4
U 1 1 5DBBDDA8
P 14000 9550
F 0 "J4" H 14080 9592 50  0000 L CNN
F 1 "ICSS Logo" H 14080 9501 50  0000 L CNN
F 2 "flight-computer:ICSS_Logo" H 14000 9550 50  0001 C CNN
F 3 "~" H 14000 9550 50  0001 C CNN
	1    14000 9550
	1    0    0    -1  
$EndComp
Text Notes 13700 9850 0    50   ~ 0
ICSS Logo placeholder\n
Wire Notes Line
	11800 9200 11800 9950
Wire Notes Line
	11800 9950 16050 9950
NoConn ~ 13800 9550
Text Label 4450 3400 0    50   ~ 0
V_SOLAR
Wire Wire Line
	5350 3400 4450 3400
NoConn ~ 7150 3900
NoConn ~ 13450 7800
NoConn ~ 7150 3600
Wire Wire Line
	5000 5200 4050 5200
Connection ~ 5000 5200
Text Label 4050 5200 0    50   ~ 0
BOOT0
Text Label 1650 2050 2    50   ~ 0
BOOT0
Wire Wire Line
	1350 2050 1650 2050
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DDA80AF
P 1800 1650
AR Path="/5D5B15F7/5DDA80AF" Ref="#PWR?"  Part="1" 
AR Path="/5DDA80AF" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 1800 1400 50  0001 C CNN
F 1 "GND" H 1805 1477 50  0000 C CNN
F 2 "" H 1800 1650 50  0001 C CNN
F 3 "" H 1800 1650 50  0001 C CNN
	1    1800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1250 1750 1250
Wire Wire Line
	1350 1150 1750 1150
Text Label 1750 1250 2    50   ~ 0
USART1_TX
Text Label 1750 1150 2    50   ~ 0
USART1_RX
Wire Wire Line
	1350 1450 2050 1450
Wire Wire Line
	1350 1350 2050 1350
Wire Wire Line
	2050 1350 2050 1250
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DE093CE
P 2050 1250
AR Path="/5D5B15F7/5DE093CE" Ref="#PWR?"  Part="1" 
AR Path="/5DE093CE" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 2050 1100 50  0001 C CNN
F 1 "+3.3V" H 2065 1423 50  0000 C CNN
F 2 "" H 2050 1250 50  0001 C CNN
F 3 "" H 2050 1250 50  0001 C CNN
	1    2050 1250
	-1   0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:Conn_01x10-Connector_Generic J1
U 1 1 5DDA3148
P 1150 1550
F 0 "J1" H 1068 2167 50  0000 C CNN
F 1 "Conn_01x10" H 1068 2076 50  0000 C CNN
F 2 "pico_tracker:10Pad" H 1150 1550 50  0001 C CNN
F 3 "~" H 1150 1550 50  0001 C CNN
	1    1150 1550
	-1   0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5DE45B73
P 2350 1250
AR Path="/5D5B15F7/5DE45B73" Ref="#PWR?"  Part="1" 
AR Path="/5DE45B73" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 2350 1100 50  0001 C CNN
F 1 "+3.3V" H 2365 1423 50  0000 C CNN
F 2 "" H 2350 1250 50  0001 C CNN
F 3 "" H 2350 1250 50  0001 C CNN
	1    2350 1250
	-1   0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5DE4BDB5
P 2050 1450
AR Path="/5D5B15F7/5DE4BDB5" Ref="#PWR?"  Part="1" 
AR Path="/5DE4BDB5" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 2050 1200 50  0001 C CNN
F 1 "GND" H 2055 1277 50  0000 C CNN
F 2 "" H 2050 1450 50  0001 C CNN
F 3 "" H 2050 1450 50  0001 C CNN
	1    2050 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1650 1800 1650
Wire Wire Line
	5400 8350 5700 8350
Wire Wire Line
	1350 1550 1950 1550
Wire Wire Line
	1950 1550 1950 1700
Wire Wire Line
	1950 1700 2350 1700
Wire Wire Line
	2350 1250 2350 1700
NoConn ~ 14650 7300
Wire Wire Line
	7150 5200 8600 5200
Wire Wire Line
	13850 5200 13850 5300
Wire Wire Line
	13850 6100 13850 6000
Connection ~ 13850 6100
Text Label 12500 5800 0    50   ~ 0
GPS_MOSFET_GATE
Wire Wire Line
	12500 5800 13350 5800
Text Label 4450 3800 0    50   ~ 0
GPS_MOSFET_GATE
Wire Wire Line
	5350 3800 4450 3800
$Comp
L circuit-board-design-rescue:Conn_01x01-Connector_Generic J5
U 1 1 5E49A628
P 8800 5350
F 0 "J5" H 8880 5392 50  0000 L CNN
F 1 "Conn_01x01" H 8880 5301 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8800 5350 50  0001 C CNN
F 3 "~" H 8800 5350 50  0001 C CNN
	1    8800 5350
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:GND-power #PWR?
U 1 1 5E4A7592
P 8600 5950
AR Path="/5D5B15F7/5E4A7592" Ref="#PWR?"  Part="1" 
AR Path="/5E4A7592" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 8600 5700 50  0001 C CNN
F 1 "GND" H 8605 5777 50  0000 C CNN
F 2 "" H 8600 5950 50  0001 C CNN
F 3 "" H 8600 5950 50  0001 C CNN
	1    8600 5950
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:R-Device R8
U 1 1 5E4D040B
P 13350 5550
F 0 "R8" H 13420 5596 50  0000 L CNN
F 1 "4.7K" H 13420 5505 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 13280 5550 50  0001 C CNN
F 3 "~" H 13350 5550 50  0001 C CNN
	1    13350 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	13350 5400 13350 5300
Wire Wire Line
	13350 5300 13850 5300
Connection ~ 13850 5300
Wire Wire Line
	13850 5300 13850 5600
Wire Wire Line
	13350 5800 13350 5700
Connection ~ 13350 5800
Wire Wire Line
	13350 5800 13550 5800
$Comp
L circuit-board-design-rescue:IRLML6402-Transistor_FET Q1
U 1 1 5E4BFDEA
P 13750 5800
F 0 "Q1" H 13956 5846 50  0000 L CNN
F 1 "IRLML6402" H 13956 5755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 13950 5725 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/irlml6402pbf.pdf?fileId=5546d462533600a401535668d5c2263c" H 13750 5800 50  0001 L CNN
F 4 "https://uk.rs-online.com/web/p/mosfets/0301322/" H 13750 5800 50  0001 C CNN "Purchase link"
	1    13750 5800
	1    0    0    1   
$EndComp
Wire Wire Line
	6450 2250 6750 2250
$Comp
L circuit-board-design-rescue:CMWX1ZZABZ-078-RF_Module U?
U 1 1 5DC84013
P 6250 3900
AR Path="/5D5B15F7/5DC84013" Ref="U?"  Part="1" 
AR Path="/5DC84013" Ref="U3"  Part="1" 
F 0 "U3" H 5550 5500 50  0000 C CNN
F 1 "CMWX1ZZABZ-078" H 5550 5350 50  0000 C CNN
F 2 "pico_tracker:CMWX1ZZABZ_custom" H 6250 3900 50  0001 C CNN
F 3 "https://wireless.murata.com/RFM/data/type_abz.pdf" H 8700 2400 50  0001 C CNN
	1    6250 3900
	1    0    0    -1  
$EndComp
Text Label 4450 3700 0    50   ~ 0
USART1_RX
Wire Wire Line
	5350 3700 4450 3700
Wire Wire Line
	5350 3600 4450 3600
Text Label 4450 3600 0    50   ~ 0
USART1_TX
Text Label 4450 3100 0    50   ~ 0
USART2_TX
Wire Wire Line
	5350 3100 4450 3100
Wire Wire Line
	5350 3200 4450 3200
Text Label 4450 3200 0    50   ~ 0
USART2_RX
Wire Wire Line
	13450 7100 12750 7100
Wire Wire Line
	13450 7200 12650 7200
Text Label 11900 7200 2    50   ~ 0
USART2_RX
Wire Wire Line
	3500 4300 4000 4300
Wire Wire Line
	6350 2400 6350 2100
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5E3AF5DA
P 6350 2100
AR Path="/5D5B15F7/5E3AF5DA" Ref="#PWR?"  Part="1" 
AR Path="/5E3AF5DA" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 6350 1950 50  0001 C CNN
F 1 "+3.3V" H 6365 2273 50  0000 C CNN
F 2 "" H 6350 2100 50  0001 C CNN
F 3 "" H 6350 2100 50  0001 C CNN
	1    6350 2100
	1    0    0    -1  
$EndComp
Text Label 6750 2250 2    50   ~ 0
TCXO_EN
$Comp
L circuit-board-design-rescue:+3.3V-power #PWR?
U 1 1 5F45EF07
P 4000 3700
AR Path="/5D5B15F7/5F45EF07" Ref="#PWR?"  Part="1" 
AR Path="/5F45EF07" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 4000 3550 50  0001 C CNN
F 1 "+3.3V" H 4015 3873 50  0000 C CNN
F 2 "" H 4000 3700 50  0001 C CNN
F 3 "" H 4000 3700 50  0001 C CNN
	1    4000 3700
	1    0    0    -1  
$EndComp
$Comp
L circuit-board-design-rescue:R-Device R?
U 1 1 5F466C77
P 4000 3850
AR Path="/5D5B15F7/5F466C77" Ref="R?"  Part="1" 
AR Path="/5F466C77" Ref="R9"  Part="1" 
F 0 "R9" H 4070 3896 50  0000 L CNN
F 1 "10K" H 4070 3805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3930 3850 50  0001 C CNN
F 3 "~" H 4000 3850 50  0001 C CNN
	1    4000 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4000 4000 4300
Connection ~ 4000 4300
Wire Wire Line
	4000 4300 5350 4300
NoConn ~ 13450 7900
Wire Wire Line
	12700 2100 13850 2100
Connection ~ 13400 2200
Wire Wire Line
	13400 2200 13950 2200
Connection ~ 13850 2100
$Comp
L Connector:TestPoint TP2
U 1 1 5F4B0820
P 12750 7000
F 0 "TP2" H 12808 7118 50  0000 L CNN
F 1 "TestPoint" H 12808 7027 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 12950 7000 50  0001 C CNN
F 3 "~" H 12950 7000 50  0001 C CNN
	1    12750 7000
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 5F4B0EE1
P 12650 6800
F 0 "TP1" H 12708 6918 50  0000 L CNN
F 1 "TestPoint" H 12708 6827 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 12850 6800 50  0001 C CNN
F 3 "~" H 12850 6800 50  0001 C CNN
	1    12650 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	12650 6800 12650 7200
Connection ~ 12650 7200
Wire Wire Line
	12650 7200 12200 7200
Wire Wire Line
	12750 7000 12750 7100
Connection ~ 12750 7100
Wire Wire Line
	12750 7100 12200 7100
Wire Wire Line
	13850 2100 14050 2100
Wire Wire Line
	13950 2200 13950 3400
$Comp
L circuit-board-design-rescue:MS5607-02BA-Sensor_Pressure U?
U 1 1 5DC8412A
P 14650 3300
AR Path="/5D5B1586/5DC8412A" Ref="U?"  Part="1" 
AR Path="/5D5B15F7/5DC8412A" Ref="U?"  Part="1" 
AR Path="/5DC8412A" Ref="U6"  Part="1" 
F 0 "U6" H 14980 3346 50  0000 L CNN
F 1 "MS5607-02BA" H 14980 3255 50  0000 L CNN
F 2 "Package_LGA:LGA-8_3x5mm_P1.25mm" H 14650 3300 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5607-02BA03%7FB2%7Fpdf%7FEnglish%7FENG_DS_MS5607-02BA03_B2.pdf%7FCAT-BLPS0035" H 14650 3300 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/absolute-pressure-sensor-ics/8937095/" H 14650 3300 50  0001 C CNN "Purchase link"
F 5 "2.86" H 14650 3300 50  0001 C CNN "Cost"
F 6 "1" H 14650 3300 50  0001 C CNN "min_quantity"
	1    14650 3300
	1    0    0    -1  
$EndComp
NoConn ~ 14250 3200
Wire Wire Line
	14150 2750 14650 2750
Wire Wire Line
	14250 3100 14150 3100
Wire Wire Line
	14250 3300 14050 3300
Wire Wire Line
	13850 2100 13850 1950
Wire Wire Line
	13400 1950 13400 2200
$Comp
L Connector:TestPoint TP3
U 1 1 5F4986F2
P 13400 1950
F 0 "TP3" H 13458 2068 50  0000 L CNN
F 1 "TestPoint" H 13450 2000 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 13600 1950 50  0001 C CNN
F 3 "~" H 13600 1950 50  0001 C CNN
	1    13400 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP4
U 1 1 5F496F33
P 13850 1950
F 0 "TP4" H 13908 2068 50  0000 L CNN
F 1 "TestPoint" H 13900 2000 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 14050 1950 50  0001 C CNN
F 3 "~" H 14050 1950 50  0001 C CNN
	1    13850 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP5
U 1 1 5F50BCC5
P 7450 2600
F 0 "TP5" H 7508 2718 50  0000 L CNN
F 1 "TestPoint" H 7500 2650 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 7650 2600 50  0001 C CNN
F 3 "~" H 7650 2600 50  0001 C CNN
	1    7450 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP6
U 1 1 5F50BCCF
P 7900 2600
F 0 "TP6" H 7958 2718 50  0000 L CNN
F 1 "TestPoint" H 7950 2650 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 8100 2600 50  0001 C CNN
F 3 "~" H 8100 2600 50  0001 C CNN
	1    7900 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3000 7450 3000
Wire Wire Line
	7450 2600 7450 3000
Wire Wire Line
	7150 3100 7900 3100
Wire Wire Line
	7900 2600 7900 3100
$Comp
L Connector:TestPoint TP7
U 1 1 5F52664F
P 8400 2600
F 0 "TP7" H 8458 2718 50  0000 L CNN
F 1 "TestPoint" H 8450 2650 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 8600 2600 50  0001 C CNN
F 3 "~" H 8600 2600 50  0001 C CNN
	1    8400 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP8
U 1 1 5F52DCD2
P 8900 2600
F 0 "TP8" H 8958 2718 50  0000 L CNN
F 1 "TestPoint" H 8950 2650 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 9100 2600 50  0001 C CNN
F 3 "~" H 9100 2600 50  0001 C CNN
	1    8900 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3200 8400 3200
Wire Wire Line
	8400 2600 8400 3200
Wire Wire Line
	7150 3300 8900 3300
Wire Wire Line
	8900 2600 8900 3300
$Comp
L Connector:TestPoint TP9
U 1 1 5F57EBA2
P 14500 6350
F 0 "TP9" H 14558 6468 50  0000 L CNN
F 1 "TestPoint" H 14550 6400 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.0mm" H 14700 6350 50  0001 C CNN
F 3 "~" H 14700 6350 50  0001 C CNN
	1    14500 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	13850 6550 14500 6550
Wire Wire Line
	14500 6550 14500 6350
Connection ~ 13850 6550
Wire Wire Line
	13850 6550 13850 6750
Text Label 7800 3500 2    50   ~ 0
I2C1_SDA
Text Label 7800 3400 2    50   ~ 0
I2C1_SCL
Wire Wire Line
	7150 3400 7800 3400
Wire Wire Line
	7150 3500 7800 3500
Wire Wire Line
	13450 7400 12750 7400
Wire Wire Line
	13450 7500 12750 7500
Text Label 12750 7500 0    50   ~ 0
I2C1_SCL
Text Label 12750 7400 0    50   ~ 0
I2C1_SDA
$Comp
L Jumper:SolderJumper_2_Open JP1
U 1 1 5F7E23E4
P 12050 7100
F 0 "JP1" H 12050 7500 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 12050 7300 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 12050 7100 50  0001 C CNN
F 3 "~" H 12050 7100 50  0001 C CNN
	1    12050 7100
	1    0    0    -1  
$EndComp
Text Label 11900 7100 2    50   ~ 0
USART2_TX
$Comp
L Jumper:SolderJumper_2_Open JP2
U 1 1 5F80485F
P 12050 7200
F 0 "JP2" H 12050 7100 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 12050 7000 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 12050 7200 50  0001 C CNN
F 3 "~" H 12050 7200 50  0001 C CNN
	1    12050 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 5350 8600 5950
$EndSCHEMATC

EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title ""
Date "2019-09-09"
Rev "1.0"
Comp "Imperial College Space Society"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 6800 4350 2    50   Output ~ 0
GPS_1PPS
Text Notes 3800 6200 0    50   ~ 0
http://www.explorelabs.com/blog/designing-a-gps-receiver/#ref-ublox-datasheet\n\nImportant info on why we use the components\n
$Comp
L power:GND #PWR011
U 1 1 5D67FE0F
P 6050 4900
F 0 "#PWR011" H 6050 4650 50  0001 C CNN
F 1 "GND" H 6055 4727 50  0000 C CNN
F 2 "" H 6050 4900 50  0001 C CNN
F 3 "" H 6050 4900 50  0001 C CNN
	1    6050 4900
	1    0    0    -1  
$EndComp
Text HLabel 5150 3750 0    50   Output ~ 0
GPS_TXD
Text HLabel 5150 3650 0    50   Input ~ 0
GPS_RXD
Text HLabel 5150 4050 0    50   BiDi ~ 0
GPS_SCL
Text HLabel 5150 3950 0    50   BiDi ~ 0
GPS_SDA
Text HLabel 5150 4350 0    50   Input ~ 0
GPS_NSAFEBOOT
Text HLabel 5150 4450 0    50   Input ~ 0
GPS_NRES
$Comp
L Connector:Conn_Coaxial J?
U 1 1 5D772D40
P 8450 4050
AR Path="/5D5B17D8/5D772D40" Ref="J?"  Part="1" 
AR Path="/5D5B165E/5D772D40" Ref="J6"  Part="1" 
F 0 "J6" H 8550 4025 50  0000 L CNN
F 1 "Conn_Coaxial" H 8550 3934 50  0000 L CNN
F 2 "Connector_Coaxial:U.FL_Hirose_U.FL-R-SMT-1_Vertical" H 8450 4050 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/185/U.FL_catalog-939761.pdf" H 8450 4050 50  0001 C CNN
F 4 "0.617" H 8450 4050 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/coaxial-plugs-sockets/7025425/" H 8450 4050 50  0001 C CNN "Purchase link"
F 6 "10" H 8450 4050 50  0001 C CNN "min_quantity"
	1    8450 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 4800 8450 4250
$Comp
L power:GND #PWR0114
U 1 1 5D7B7248
P 8450 4800
F 0 "#PWR0114" H 8450 4550 50  0001 C CNN
F 1 "GND" H 8455 4627 50  0000 C CNN
F 2 "" H 8450 4800 50  0001 C CNN
F 3 "" H 8450 4800 50  0001 C CNN
	1    8450 4800
	1    0    0    -1  
$EndComp
Connection ~ 7650 4050
Wire Wire Line
	7650 4050 8250 4050
$Comp
L Device:L L2
U 1 1 5D7B7FB8
P 7650 3650
F 0 "L2" H 7703 3696 50  0000 L CNN
F 1 "27nH" H 7703 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 7650 3650 50  0001 C CNN
F 3 "~" H 7650 3650 50  0001 C CNN
F 4 "0.08" H 7650 3650 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/wire-wound-surface-mount-inductors/7254923/" H 7650 3650 50  0001 C CNN "Purchase link"
F 6 "10" H 7650 3650 50  0001 C CNN "min_quantity"
	1    7650 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 3800 7650 4050
Wire Wire Line
	6250 3100 6800 3100
Wire Wire Line
	7650 3100 7650 3500
$Comp
L Device:R R2
U 1 1 5D7B91DB
P 6950 3100
F 0 "R2" V 6743 3100 50  0000 C CNN
F 1 "10 Ohm" V 6834 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6880 3100 50  0001 C CNN
F 3 "~" H 6950 3100 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6788703/" H 6950 3100 50  0001 C CNN "Purchase link"
F 5 "50" H 6950 3100 50  0001 C CNN "min_quantity"
F 6 "0.002" H 6950 3100 50  0001 C CNN "Cost"
	1    6950 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 3100 7650 3100
Wire Wire Line
	7650 3100 7650 2500
Connection ~ 7650 3100
$Comp
L power:GND #PWR0116
U 1 1 5D7B9CCD
P 8400 3100
F 0 "#PWR0116" H 8400 2850 50  0001 C CNN
F 1 "GND" H 8405 2927 50  0000 C CNN
F 2 "" H 8400 3100 50  0001 C CNN
F 3 "" H 8400 3100 50  0001 C CNN
	1    8400 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2500 8400 2650
Wire Wire Line
	7650 2500 8400 2500
$Comp
L Device:C_Small C8
U 1 1 5D7BADC4
P 8400 2750
F 0 "C8" H 8492 2796 50  0000 L CNN
F 1 "10nF" H 8492 2705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8400 2750 50  0001 C CNN
F 3 "~" H 8400 2750 50  0001 C CNN
F 4 "0.031" H 8400 2750 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8391727/" H 8400 2750 50  0001 C CNN "Purchase link"
F 6 "100" H 8400 2750 50  0001 C CNN "min_quantity"
	1    8400 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 2850 8400 3100
Text Notes 7500 5350 0    50   ~ 0
Connected to active antenna, likely 2066400001 \nMolex active antenna. UFL connector\n
Text Notes 7000 1150 0    50   ~ 0
Layout according to MAX-8 / MAX-M8, \nHardware Integration Manual,\nSection 2.4.2 Antenna design with active antenna.
NoConn ~ 5450 4250
Wire Wire Line
	6650 4350 6800 4350
Wire Wire Line
	6250 3350 6250 3100
NoConn ~ 6650 3850
Wire Wire Line
	6650 4050 7650 4050
Wire Wire Line
	6050 4750 6050 4900
Wire Wire Line
	5950 3350 5950 3300
Wire Wire Line
	5850 2650 5850 3350
Connection ~ 5850 2650
Wire Wire Line
	5950 2650 5850 2650
Wire Wire Line
	5850 2100 5850 2650
$Comp
L power:+3.3V #PWR010
U 1 1 5D692740
P 5850 2100
F 0 "#PWR010" H 5850 1950 50  0001 C CNN
F 1 "+3.3V" H 5865 2273 50  0000 C CNN
F 2 "" H 5850 2100 50  0001 C CNN
F 3 "" H 5850 2100 50  0001 C CNN
	1    5850 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3050 5300 2950
Wire Wire Line
	5650 2950 5650 3050
Wire Wire Line
	5650 2650 5300 2650
Connection ~ 5650 2650
Wire Wire Line
	5650 2750 5650 2650
Wire Wire Line
	5300 2650 5300 2750
Wire Wire Line
	5850 2650 5650 2650
$Comp
L Device:C_Small C?
U 1 1 5D99D571
P 5300 2850
AR Path="/5D5B17D8/5D99D571" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5D99D571" Ref="C11"  Part="1" 
F 0 "C11" H 5208 2896 50  0000 R CNN
F 1 "100nF" H 5208 2805 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5300 2850 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 5300 2850 50  0001 C CNN
F 4 "0.01" H 5300 2850 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 5300 2850 50  0001 C CNN "Purchase link"
F 6 "50" H 5300 2850 50  0001 C CNN "min_quantity"
	1    5300 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5D99D56B
P 5650 2850
AR Path="/5D5B17D8/5D99D56B" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5D99D56B" Ref="C12"  Part="1" 
F 0 "C12" H 5558 2896 50  0000 R CNN
F 1 "10uF" H 5558 2805 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5650 2850 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 5650 2850 50  0001 C CNN
F 4 "0.07" H 5650 2850 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 5650 2850 50  0001 C CNN "Purchase link"
F 6 "100" H 5650 2850 50  0001 C CNN "min_quantity"
	1    5650 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 4450 5450 4450
Wire Wire Line
	5450 4350 5150 4350
Wire Wire Line
	5150 4050 5450 4050
Wire Wire Line
	5450 3950 5150 3950
Wire Wire Line
	5150 3750 5450 3750
Wire Wire Line
	5450 3650 5150 3650
$Comp
L power:GND #PWR?
U 1 1 5D99D57F
P 5300 3150
AR Path="/5D5B17D8/5D99D57F" Ref="#PWR?"  Part="1" 
AR Path="/5D5B165E/5D99D57F" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 5300 2900 50  0001 C CNN
F 1 "GND" H 5305 2977 50  0000 C CNN
F 2 "" H 5300 3150 50  0001 C CNN
F 3 "" H 5300 3150 50  0001 C CNN
	1    5300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3150 5300 3050
Connection ~ 5300 3050
Wire Wire Line
	5300 3050 5650 3050
Wire Wire Line
	6050 3350 6050 3300
Wire Wire Line
	6050 3300 5950 3300
Connection ~ 5950 3300
Wire Wire Line
	5950 3300 5950 2650
$Comp
L RF_GPS:MAX-M8Q U4
U 1 1 5D91C1E4
P 6050 4050
F 0 "U4" H 6050 3261 50  0000 C CNN
F 1 "MAX-M8Q" H 5600 3200 50  0000 C CNN
F 2 "RF_GPS:ublox_MAX" H 6450 3400 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/MAX-M8-FW3_DataSheet_%28UBX-15031506%29.pdf" H 6050 4050 50  0001 C CNN
F 4 "11.99" H 6050 4050 50  0001 C CNN "Cost"
F 5 "https://store.uputronics.com/index.php?route=product/product&product_id=71&search=ublox" H 6050 4050 50  0001 C CNN "Purchase link"
F 6 "1" H 6050 4050 50  0001 C CNN "min_quantity"
	1    6050 4050
	1    0    0    -1  
$EndComp
$EndSCHEMATC

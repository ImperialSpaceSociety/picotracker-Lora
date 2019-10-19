EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
Title "Silabs radio chip for telemetry to ground"
Date "2019-09-09"
Rev "1.0"
Comp "Imperial College Space Society"
Comment1 "Arranged according to Silabs AN904."
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3050 4850 3400 4850
Text HLabel 3050 4850 0    50   Input ~ 0
RF_SCLK
Wire Wire Line
	3050 4950 3400 4950
Text HLabel 3050 4950 0    50   Input ~ 0
RF_MOSI
Wire Wire Line
	3050 5050 3400 5050
Text HLabel 3050 5050 0    50   Output ~ 0
RF_MISO
Wire Wire Line
	3050 5150 3400 5150
Text HLabel 3050 5150 0    50   Input ~ 0
RF_NSEL
Wire Wire Line
	3800 4050 3800 3900
$Comp
L power:+3.3V #PWR0101
U 1 1 5D62941F
P 3800 3300
F 0 "#PWR0101" H 3800 3150 50  0001 C CNN
F 1 "+3.3V" H 3815 3473 50  0000 C CNN
F 2 "" H 3800 3300 50  0001 C CNN
F 3 "" H 3800 3300 50  0001 C CNN
	1    3800 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5D5CDCF8
P 3800 5550
F 0 "#PWR09" H 3800 5300 50  0001 C CNN
F 1 "GND" H 3805 5377 50  0000 C CNN
F 2 "" H 3800 5550 50  0001 C CNN
F 3 "" H 3800 5550 50  0001 C CNN
	1    3800 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5450 3800 5550
Wire Wire Line
	3900 4050 3900 3900
Wire Wire Line
	3900 3900 3800 3900
Wire Wire Line
	3050 4250 3400 4250
Text HLabel 3050 4250 0    50   Input ~ 0
RF_SDN
NoConn ~ 4200 4450
$Comp
L power:+3.3V #PWR032
U 1 1 5D6B5C3D
P 1550 2900
F 0 "#PWR032" H 1550 2750 50  0001 C CNN
F 1 "+3.3V" H 1565 3073 50  0000 C CNN
F 2 "" H 1550 2900 50  0001 C CNN
F 3 "" H 1550 2900 50  0001 C CNN
	1    1550 2900
	1    0    0    -1  
$EndComp
NoConn ~ 1250 3600
$Comp
L power:GND #PWR033
U 1 1 5D6BDDD0
P 1550 4100
F 0 "#PWR033" H 1550 3850 50  0001 C CNN
F 1 "GND" H 1555 3927 50  0000 C CNN
F 2 "" H 1550 4100 50  0001 C CNN
F 3 "" H 1550 4100 50  0001 C CNN
	1    1550 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 4450 2300 4450
Text HLabel 3050 5250 0    50   Input ~ 0
RF_NIRQ
Wire Wire Line
	3400 5250 3050 5250
Wire Wire Line
	800  3150 800  3400
Wire Wire Line
	1550 2900 1550 3150
Wire Wire Line
	1550 3900 1550 4000
Wire Wire Line
	800  3150 1550 3150
Connection ~ 1550 3150
Wire Wire Line
	1550 3150 1550 3300
Wire Wire Line
	800  3600 800  4000
Wire Wire Line
	800  4000 1550 4000
Connection ~ 1550 4000
Wire Wire Line
	1550 4000 1550 4100
Wire Wire Line
	1850 3600 2300 3600
Wire Wire Line
	2300 3600 2300 3800
Wire Wire Line
	2300 4000 2300 4450
Wire Wire Line
	4700 2150 4700 2350
Connection ~ 4700 2150
Wire Wire Line
	3700 2350 3700 2150
Wire Wire Line
	4700 1950 4700 2150
$Comp
L power:+3.3V #PWR031
U 1 1 5D6CE7B6
P 4700 1950
F 0 "#PWR031" H 4700 1800 50  0001 C CNN
F 1 "+3.3V" H 4715 2123 50  0000 C CNN
F 2 "" H 4700 1950 50  0001 C CNN
F 3 "" H 4700 1950 50  0001 C CNN
	1    4700 1950
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR030
U 1 1 5D6CBC88
P 3700 2800
F 0 "#PWR030" H 3700 2550 50  0001 C CNN
F 1 "GND" H 3705 2627 50  0000 C CNN
F 2 "" H 3700 2800 50  0001 C CNN
F 3 "" H 3700 2800 50  0001 C CNN
	1    3700 2800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3800 3300 3800 3400
Connection ~ 3800 3900
Wire Wire Line
	3800 3400 4000 3400
Wire Wire Line
	4350 3400 4350 3500
Connection ~ 3800 3400
Wire Wire Line
	3800 3400 3800 3900
Wire Wire Line
	4000 3500 4000 3400
Connection ~ 4000 3400
Wire Wire Line
	4000 3400 4350 3400
Wire Wire Line
	4000 3700 4000 3800
Wire Wire Line
	4350 3800 4350 3700
Wire Wire Line
	4000 3800 4150 3800
$Comp
L power:GND #PWR015
U 1 1 5D7F10E1
P 4150 3900
F 0 "#PWR015" H 4150 3650 50  0001 C CNN
F 1 "GND" H 4155 3727 50  0000 C CNN
F 2 "" H 4150 3900 50  0001 C CNN
F 3 "" H 4150 3900 50  0001 C CNN
	1    4150 3900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4150 3900 4150 3800
Connection ~ 4150 3800
Wire Wire Line
	4150 3800 4350 3800
Wire Notes Line
	2950 1700 5000 1700
Wire Notes Line
	5000 1700 5000 3050
Wire Notes Line
	2950 1700 2950 3050
Text Notes 3650 1900 2    50   ~ 0
TX Bias
NoConn ~ 3400 4650
Wire Wire Line
	4200 4250 4700 4250
Wire Wire Line
	4700 2650 4700 4250
Wire Wire Line
	4700 4250 5950 4250
Connection ~ 4700 4250
Wire Wire Line
	4200 4650 5950 4650
Wire Wire Line
	4200 4750 5950 4750
Wire Wire Line
	6750 4450 6900 4450
Wire Wire Line
	6900 4450 6900 4550
Wire Wire Line
	6750 4550 6900 4550
Connection ~ 6900 4550
Wire Wire Line
	6900 4550 6900 4650
Wire Wire Line
	6750 4650 6900 4650
Connection ~ 6900 4650
Wire Wire Line
	6900 4650 6900 4750
Wire Wire Line
	6750 4750 6900 4750
Connection ~ 6900 4750
Wire Wire Line
	6900 4750 6900 5200
Wire Notes Line
	2950 3050 5000 3050
$Comp
L power:GND #PWR016
U 1 1 5D78B4ED
P 6900 5200
F 0 "#PWR016" H 6900 4950 50  0001 C CNN
F 1 "GND" H 6905 5027 50  0000 C CNN
F 2 "" H 6900 5200 50  0001 C CNN
F 3 "" H 6900 5200 50  0001 C CNN
	1    6900 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 4250 7700 4250
Wire Wire Line
	3700 2150 4700 2150
Wire Wire Line
	3700 2550 3700 2800
Text HLabel 4450 4950 2    50   Input ~ 0
RF_GPIO0
Wire Wire Line
	4450 4950 4200 4950
Text HLabel 4450 5050 2    50   Input ~ 0
RF_GPIO1
Wire Wire Line
	4450 5050 4200 5050
NoConn ~ 4200 5250
NoConn ~ 4200 5150
Text Notes 4550 6100 0    50   ~ 0
Arranged according to Silabs AN904
Wire Notes Line
	9750 2900 9750 4200
Wire Notes Line
	8400 2900 9750 2900
Wire Notes Line
	8400 4200 8400 2900
Wire Notes Line
	9750 4200 8400 4200
Wire Wire Line
	8200 3300 8500 3300
Text Notes 8650 4350 0    50   ~ 0
Antenna matching options\n
Wire Wire Line
	9250 3300 9350 3300
Connection ~ 9250 3300
Wire Wire Line
	9250 3300 9250 3500
$Comp
L power:GND #PWR07
U 1 1 5D7EC7E0
P 9250 3950
F 0 "#PWR07" H 9250 3700 50  0001 C CNN
F 1 "GND" H 9250 3800 50  0000 C CNN
F 2 "" H 9250 3950 50  0001 C CNN
F 3 "" H 9250 3950 50  0001 C CNN
	1    9250 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 3700 9250 3950
Wire Wire Line
	8200 3300 8200 4250
Wire Wire Line
	8800 3300 9250 3300
Wire Wire Line
	8200 4850 8200 5100
$Comp
L power:GND #PWR028
U 1 1 5D7A6387
P 8700 5900
F 0 "#PWR028" H 8700 5650 50  0001 C CNN
F 1 "GND" H 8705 5727 50  0000 C CNN
F 2 "" H 8700 5900 50  0001 C CNN
F 3 "" H 8700 5900 50  0001 C CNN
	1    8700 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8700 5300 8700 5900
Wire Wire Line
	8400 5300 8700 5300
Connection ~ 8200 4250
Wire Wire Line
	8200 4250 8200 4550
Wire Wire Line
	7900 4250 8200 4250
$Comp
L Connector:Conn_Coaxial J7
U 1 1 5D7A2CE8
P 8200 5300
F 0 "J7" H 8300 5182 50  0000 L CNN
F 1 "Conn_Coaxial" H 8300 5273 50  0000 L CNN
F 2 "Connector_Coaxial:U.FL_Hirose_U.FL-R-SMT-1_Vertical" H 8200 5300 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/185/U.FL_catalog-939761.pdf" H 8200 5300 50  0001 C CNN
F 4 "0.617" H 8200 5300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/coaxial-plugs-sockets/7025425/" H 8200 5300 50  0001 C CNN "Purchase link"
F 6 "10" H 8200 5300 50  0001 C CNN "min_quantity"
	1    8200 5300
	0    -1   1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 5D7AB0E5
P 8200 4700
F 0 "R7" H 8270 4746 50  0000 L CNN
F 1 "NF" H 8270 4655 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 8130 4700 50  0001 C CNN
F 3 "~" H 8200 4700 50  0001 C CNN
	1    8200 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C10
U 1 1 5D7EC7D6
P 9250 3600
F 0 "C10" H 9158 3646 50  0000 R CNN
F 1 "NF" H 9158 3555 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9250 3600 50  0001 C CNN
F 3 "~" H 9250 3600 50  0001 C CNN
	1    9250 3600
	-1   0    0    -1  
$EndComp
$Comp
L Device:L L3
U 1 1 5D7F0545
P 8650 3300
F 0 "L3" V 8469 3300 50  0000 C CNN
F 1 "0R" V 8560 3300 50  0000 C CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 8650 3300 50  0001 C CNN
F 3 "~" H 8650 3300 50  0001 C CNN
	1    8650 3300
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C9
U 1 1 5D796ABE
P 7800 4250
F 0 "C9" V 7892 4296 50  0000 L CNN
F 1 "270pF" V 8050 4200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7800 4250 50  0001 C CNN
F 3 "~" H 7800 4250 50  0001 C CNN
F 4 "0.01" H 7800 4250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/9155553/" H 7800 4250 50  0001 C CNN "Purchase link"
F 6 "200" H 7800 4250 50  0001 C CNN "min_quantity"
	1    7800 4250
	0    1    -1   0   
$EndComp
$Comp
L circuit-board-design-rescue:0433BM41A0019E-0433BM41A0019E U2
U 1 1 5D767292
P 6350 4450
AR Path="/5D767292" Ref="U2"  Part="1" 
AR Path="/5D5B17D8/5D767292" Ref="U2"  Part="1" 
F 0 "U2" H 6350 4967 50  0000 C CNN
F 1 "0433BM41A0019E" H 6350 4876 50  0000 C CNN
F 2 "Johanson_frontend:BALUN_0433BM41A0019E" H 5850 5100 50  0001 L BNN
F 3 "https://www.johansontechnology.com/datasheets/0433BM41A0019/0433BM41A0019.pdf" H 5850 5100 50  0001 L BNN
F 4 "0.745" H 6350 4450 50  0001 C CNN "Cost"
F 5 "https://www.mouser.co.uk/ProductDetail/Johanson-Technology/0433BM41A0019E?qs=cgWa3jCOTNkHeQmiwnsqmQ==" H 6350 4450 50  0001 C CNN "Purchase link"
F 6 "1" H 6350 4450 50  0001 C CNN "min_quantity"
	1    6350 4450
	1    0    0    -1  
$EndComp
$Comp
L flight-computer:TM-32.000-AF3-33-S-Oscillator X1
U 1 1 5D703E49
P 1550 3600
F 0 "X1" H 1500 4800 50  0000 L CNN
F 1 "TM-32.000-AF3-33-S-Oscillator" H 1000 4700 50  0000 L CNN
F 2 "flight-computer:Crystal_SMD_2520-4Pin_2.5x2.0mm" H 2000 3250 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/15dc/0900766b815dc7d9.pdf" H 1450 3600 50  0001 C CNN
F 4 "3.43" H 1550 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/tcxo-oscillators/1442366/" H 1550 3600 50  0001 C CNN "Purchase link"
F 6 "2" H 1550 3600 50  0001 C CNN "min_quantity"
	1    1550 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C19
U 1 1 5D6CDD9C
P 3700 2450
F 0 "C19" H 3608 2496 50  0000 R CNN
F 1 "270pF" H 3608 2405 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3700 2450 50  0001 C CNN
F 3 "~" H 3700 2450 50  0001 C CNN
F 4 "0.01" H 3700 2450 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/9155553/" H 3700 2450 50  0001 C CNN "Purchase link"
F 6 "200" H 3700 2450 50  0001 C CNN "min_quantity"
	1    3700 2450
	-1   0    0    -1  
$EndComp
$Comp
L Device:L L8
U 1 1 5D6CE249
P 4700 2500
F 0 "L8" H 4656 2454 50  0000 R CNN
F 1 "220nH" H 4656 2545 50  0000 R CNN
F 2 "Inductor_SMD:L_0603_1608Metric" H 4700 2500 50  0001 C CNN
F 3 "~" H 4700 2500 50  0001 C CNN
F 4 "0.126" H 4700 2500 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/multilayer-surface-mount-inductors/6041209/" H 4700 2500 50  0001 C CNN "Purchase link"
F 6 "10" H 4700 2500 50  0001 C CNN "min_quantity"
	1    4700 2500
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C23
U 1 1 5D7EC4A3
P 4350 3600
F 0 "C23" H 4258 3646 50  0000 R CNN
F 1 "100nF" H 4258 3555 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4350 3600 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 4350 3600 50  0001 C CNN
F 4 "0.01" H 4350 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 4350 3600 50  0001 C CNN "Purchase link"
F 6 "50" H 4350 3600 50  0001 C CNN "min_quantity"
	1    4350 3600
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C22
U 1 1 5D7EB85A
P 4000 3600
F 0 "C22" H 3908 3646 50  0000 R CNN
F 1 "1uF" H 3908 3555 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4000 3600 50  0001 C CNN
F 3 "~" H 4000 3600 50  0001 C CNN
F 4 "0.01" H 4000 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/1358359/" H 4000 3600 50  0001 C CNN "Purchase link"
F 6 "250" H 4000 3600 50  0001 C CNN "min_quantity"
	1    4000 3600
	-1   0    0    -1  
$EndComp
$Comp
L Device:C_Small C21
U 1 1 5D6BC5E2
P 800 3500
F 0 "C21" H 1050 3500 50  0000 C CNN
F 1 "33nF" H 1050 3400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 800 3500 50  0001 C CNN
F 3 "~" H 800 3500 50  0001 C CNN
F 4 "0.008" H 800 3500 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8392805/" H 800 3500 50  0001 C CNN "Purchase link"
F 6 "100" H 800 3500 50  0001 C CNN "min_quantity"
	1    800  3500
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C20
U 1 1 5D6C2DE3
P 2300 3900
F 0 "C20" H 2550 3900 50  0000 C CNN
F 1 "10nF" H 2550 3800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2300 3900 50  0001 C CNN
F 3 "~" H 2300 3900 50  0001 C CNN
F 4 "0.031" H 2300 3900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8391727/" H 2300 3900 50  0001 C CNN "Purchase link"
F 6 "100" H 2300 3900 50  0001 C CNN "min_quantity"
	1    2300 3900
	1    0    0    1   
$EndComp
$Comp
L RF:Si4463 U3
U 1 1 5D5CB5C3
P 3800 4750
F 0 "U3" H 3550 5450 50  0000 C CNN
F 1 "Si4463" H 3550 5550 50  0000 C CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_4x4mm_P0.5mm_EP2.6x2.6mm_ThermalVias" H 3800 5950 50  0001 C CNN
F 3 "https://www.silabs.com/documents/public/data-sheets/Si4464-63-61-60.pdf" H 3500 4650 50  0001 C CNN
F 4 "2.20" H 3800 4750 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/rf-transceivers/8196950/" H 3800 4750 50  0001 C CNN "Purchase link"
F 6 "2" H 3800 4750 50  0001 C CNN "min_quantity"
	1    3800 4750
	1    0    0    -1  
$EndComp
$Comp
L flight-computer:Yageo434_ANT1204F002R0433A ANT1
U 1 1 5DB119FE
P 9850 2350
F 0 "ANT1" H 9800 2615 50  0000 C CNN
F 1 "Yageo434" H 9800 2524 50  0000 C CNN
F 2 "flight-computer:Yageo434" H 9850 2350 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/447/An_SMD_UHF_433_1204_0-595178.pdf" H 9850 2350 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/smt-antennas/1766834/" H 9850 2350 50  0001 C CNN "Purchase link"
F 5 "2.67" H 9850 2350 50  0001 C CNN "Cost"
F 6 "1" H 9850 2350 50  0001 C CNN "min_quantity"
	1    9850 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 2350 9450 2350
Wire Wire Line
	9350 2350 9350 3300
$EndSCHEMATC

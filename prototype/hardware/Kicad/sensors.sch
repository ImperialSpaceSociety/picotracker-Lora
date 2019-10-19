EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title ""
Date "2019-09-09"
Rev "1.0"
Comp "Imperial College Space Society"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR0110
U 1 1 5D87FF4B
P 9450 5900
F 0 "#PWR0110" H 9450 5650 50  0001 C CNN
F 1 "GND" H 9455 5727 50  0000 C CNN
F 2 "" H 9450 5900 50  0001 C CNN
F 3 "" H 9450 5900 50  0001 C CNN
	1    9450 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5D880718
P 8850 5900
F 0 "#PWR0113" H 8850 5650 50  0001 C CNN
F 1 "GND" H 8855 5727 50  0000 C CNN
F 2 "" H 8850 5900 50  0001 C CNN
F 3 "" H 8850 5900 50  0001 C CNN
	1    8850 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 5750 9450 5900
Wire Wire Line
	9050 5550 8850 5550
Wire Wire Line
	8850 5550 8850 5900
Wire Wire Line
	9050 5350 8850 5350
Wire Wire Line
	9050 5450 8700 5450
$Comp
L power:GND #PWR0115
U 1 1 5D883873
P 9900 5050
F 0 "#PWR0115" H 9900 4800 50  0001 C CNN
F 1 "GND" H 9905 4877 50  0000 C CNN
F 2 "" H 9900 5050 50  0001 C CNN
F 3 "" H 9900 5050 50  0001 C CNN
	1    9900 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 4750 9450 4800
Wire Wire Line
	9900 5000 9900 5050
Wire Wire Line
	9900 4800 9450 4800
Connection ~ 9450 4800
Wire Wire Line
	9450 4800 9450 4950
Wire Wire Line
	9050 5150 8950 5150
Wire Wire Line
	8950 5150 8950 4800
Wire Wire Line
	8950 4800 9450 4800
NoConn ~ 9050 5250
Text HLabel 1300 4400 0    50   BiDi ~ 0
SENS_SCL
Text HLabel 1300 4150 0    50   BiDi ~ 0
SENS_SDA
$Comp
L power:+3.3V #PWR013
U 1 1 5D6AE039
P 9450 4750
F 0 "#PWR013" H 9450 4600 50  0001 C CNN
F 1 "+3.3V" H 9465 4923 50  0000 C CNN
F 2 "" H 9450 4750 50  0001 C CNN
F 3 "" H 9450 4750 50  0001 C CNN
	1    9450 4750
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Pressure:MS5607-02BA U8
U 1 1 5D36B493
P 9450 5350
F 0 "U8" H 9780 5396 50  0000 L CNN
F 1 "MS5607-02BA" H 9780 5305 50  0000 L CNN
F 2 "Package_LGA:LGA-8_3x5mm_P1.25mm" H 9450 5350 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5607-02BA03%7FB2%7Fpdf%7FEnglish%7FENG_DS_MS5607-02BA03_B2.pdf%7FCAT-BLPS0035" H 9450 5350 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/absolute-pressure-sensor-ics/8937095/" H 9450 5350 50  0001 C CNN "Purchase link"
F 5 "2.86" H 9450 5350 50  0001 C CNN "Cost"
F 6 "1" H 9450 5350 50  0001 C CNN "min_quantity"
	1    9450 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C77
U 1 1 5D88305F
P 9900 4900
F 0 "C77" H 9992 4946 50  0000 L CNN
F 1 "220nF" H 9992 4855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9900 4900 50  0001 C CNN
F 3 "~" H 9900 4900 50  0001 C CNN
F 4 "0.003" H 9900 4900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/0391135/" H 9900 4900 50  0001 C CNN "Purchase link"
F 6 "50" H 9900 4900 50  0001 C CNN "min_quantity"
	1    9900 4900
	1    0    0    -1  
$EndComp
Connection ~ 1650 4400
Connection ~ 1750 4150
Wire Wire Line
	4400 3250 4400 3450
Wire Wire Line
	4400 3450 4600 3450
Wire Wire Line
	4600 3450 4600 3250
Wire Wire Line
	4600 3450 4600 3550
Connection ~ 4600 3450
$Comp
L power:GND #PWR0105
U 1 1 5D917D13
P 4600 3550
F 0 "#PWR0105" H 4600 3300 50  0001 C CNN
F 1 "GND" H 4605 3377 50  0000 C CNN
F 2 "" H 4600 3550 50  0001 C CNN
F 3 "" H 4600 3550 50  0001 C CNN
	1    4600 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 6350 4000 6550
Wire Wire Line
	4000 6550 4100 6550
Wire Wire Line
	4400 6550 4400 6350
Wire Wire Line
	4200 6550 4200 6800
Connection ~ 4200 6550
Wire Wire Line
	4200 6550 4300 6550
$Comp
L power:GND #PWR012
U 1 1 5D92E3B0
P 4200 6800
F 0 "#PWR012" H 4200 6550 50  0001 C CNN
F 1 "GND" H 4205 6627 50  0000 C CNN
F 2 "" H 4200 6800 50  0001 C CNN
F 3 "" H 4200 6800 50  0001 C CNN
	1    4200 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 6350 4100 6550
Connection ~ 4100 6550
Wire Wire Line
	4100 6550 4200 6550
Wire Wire Line
	4200 6350 4200 6550
Wire Wire Line
	4300 6350 4300 6550
Connection ~ 4300 6550
Wire Wire Line
	4300 6550 4400 6550
Wire Wire Line
	8700 4400 8700 5450
Wire Wire Line
	1650 4400 3400 4400
Wire Wire Line
	8850 4150 8850 5350
Wire Wire Line
	1750 4150 3250 4150
Wire Wire Line
	3450 5550 3400 5550
Wire Wire Line
	3400 5550 3400 4400
Connection ~ 3400 4400
Wire Wire Line
	3400 4400 7800 4400
Wire Wire Line
	3450 5650 3250 5650
Wire Wire Line
	3250 5650 3250 4150
Connection ~ 3250 4150
Wire Wire Line
	3250 4150 7500 4150
Wire Wire Line
	4850 5550 5200 5550
Wire Wire Line
	5200 5550 5200 5450
Wire Wire Line
	4850 5650 5200 5650
Wire Wire Line
	5200 5650 5200 5550
Connection ~ 5200 5550
$Comp
L power:+3.3V #PWR014
U 1 1 5D949DAF
P 5200 4700
F 0 "#PWR014" H 5200 4550 50  0001 C CNN
F 1 "+3.3V" H 5215 4873 50  0000 C CNN
F 2 "" H 5200 4700 50  0001 C CNN
F 3 "" H 5200 4700 50  0001 C CNN
	1    5200 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5D94C24A
P 5900 6300
F 0 "#PWR017" H 5900 6050 50  0001 C CNN
F 1 "GND" H 5905 6127 50  0000 C CNN
F 2 "" H 5900 6300 50  0001 C CNN
F 3 "" H 5900 6300 50  0001 C CNN
	1    5900 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C13
U 1 1 5D94EBA2
P 5550 5200
F 0 "C13" V 5400 5300 50  0000 L CNN
F 1 "10uF" V 5400 5050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5550 5200 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 5550 5200 50  0001 C CNN
F 4 "0.07" H 5550 5200 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 5550 5200 50  0001 C CNN "Purchase link"
F 6 "100" H 5550 5200 50  0001 C CNN "min_quantity"
	1    5550 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 5200 5450 5200
Connection ~ 5200 5200
Wire Wire Line
	5650 5200 5900 5200
Wire Wire Line
	5900 5200 5900 5450
$Comp
L Device:C_Small C14
U 1 1 5D951B11
P 5550 5450
F 0 "C14" V 5400 5550 50  0000 L CNN
F 1 "100nF" V 5400 5300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5550 5450 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 5550 5450 50  0001 C CNN
F 4 "0.01" H 5550 5450 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 5550 5450 50  0001 C CNN "Purchase link"
F 6 "50" H 5550 5450 50  0001 C CNN "min_quantity"
	1    5550 5450
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 5450 5450 5450
Connection ~ 5200 5450
Wire Wire Line
	5200 5450 5200 5200
Wire Wire Line
	5650 5450 5900 5450
Connection ~ 5900 5450
Wire Wire Line
	5900 5450 5900 6300
Text Notes 5500 4900 0    50   ~ 0
Power supply decoupling capacitors \n(100 nF ceramic, 10 μF aluminum) should be \nplaced as near as possible to pin 14 of the \ndevice (common design practice).
Wire Wire Line
	3450 5950 2850 5950
Wire Wire Line
	2850 5950 2850 5850
$Comp
L power:+3.3V #PWR026
U 1 1 5D95E33C
P 2850 5200
F 0 "#PWR026" H 2850 5050 50  0001 C CNN
F 1 "+3.3V" H 2865 5373 50  0000 C CNN
F 2 "" H 2850 5200 50  0001 C CNN
F 3 "" H 2850 5200 50  0001 C CNN
	1    2850 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 5850 2850 5850
Connection ~ 2850 5850
Wire Wire Line
	2850 5850 2850 5200
Text Notes 1750 6300 0    50   ~ 0
The slave address(SAD) is dress 0011001b.\nSA0 is connected to voltage supply.
Wire Wire Line
	4850 5450 4950 5450
Text HLabel 5200 5750 2    50   Input ~ 0
H_ACCL_INT1
Wire Wire Line
	4850 5750 5200 5750
Text HLabel 5200 5850 2    50   Input ~ 0
H_ACCL_INT2
Wire Wire Line
	5200 5850 4850 5850
Wire Wire Line
	5200 2550 5350 2550
Wire Wire Line
	5350 2550 5350 2650
Wire Wire Line
	5350 3450 4600 3450
Wire Wire Line
	5200 2650 5350 2650
Connection ~ 5350 2650
Wire Wire Line
	5350 2650 5350 2750
Wire Wire Line
	5200 2750 5350 2750
Connection ~ 5350 2750
Wire Wire Line
	5350 2750 5350 2850
Wire Wire Line
	5200 2850 5350 2850
Connection ~ 5350 2850
Wire Wire Line
	5350 2850 5350 2950
Wire Wire Line
	5200 2950 5350 2950
Connection ~ 5350 2950
Wire Wire Line
	5350 2950 5350 3450
Wire Wire Line
	4500 1650 4500 950 
Wire Wire Line
	4500 950  3900 950 
Wire Wire Line
	4600 1650 4600 950 
Wire Wire Line
	4600 950  4500 950 
Connection ~ 4500 950 
Wire Wire Line
	3900 950  3900 800 
$Comp
L power:+3.3V #PWR027
U 1 1 5D986091
P 3900 800
F 0 "#PWR027" H 3900 650 50  0001 C CNN
F 1 "+3.3V" H 3915 973 50  0000 C CNN
F 2 "" H 3900 800 50  0001 C CNN
F 3 "" H 3900 800 50  0001 C CNN
	1    3900 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 950  3900 1100
Connection ~ 3900 950 
$Comp
L power:GND #PWR034
U 1 1 5D98A13F
P 3900 1350
F 0 "#PWR034" H 3900 1100 50  0001 C CNN
F 1 "GND" H 3905 1177 50  0000 C CNN
F 2 "" H 3900 1350 50  0001 C CNN
F 3 "" H 3900 1350 50  0001 C CNN
	1    3900 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C15
U 1 1 5D98BC07
P 3900 1200
F 0 "C15" H 3992 1246 50  0000 L CNN
F 1 "100nF" H 3992 1155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3900 1200 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 3900 1200 50  0001 C CNN
F 4 "0.01" H 3900 1200 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 3900 1200 50  0001 C CNN "Purchase link"
F 6 "50" H 3900 1200 50  0001 C CNN "min_quantity"
	1    3900 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 1300 3900 1350
Wire Wire Line
	5200 4700 5200 5200
$Comp
L power:+3.3V #PWR036
U 1 1 5D994103
P 4950 4700
F 0 "#PWR036" H 4950 4550 50  0001 C CNN
F 1 "+3.3V" H 4965 4873 50  0000 C CNN
F 2 "" H 4950 4700 50  0001 C CNN
F 3 "" H 4950 4700 50  0001 C CNN
	1    4950 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4800 4750 4800
Wire Wire Line
	4750 4800 4750 4850
Connection ~ 4950 4800
Wire Wire Line
	4950 4800 4950 4700
$Comp
L power:GND #PWR035
U 1 1 5D998947
P 4750 5100
F 0 "#PWR035" H 4750 4850 50  0001 C CNN
F 1 "GND" H 4755 4927 50  0000 C CNN
F 2 "" H 4750 5100 50  0001 C CNN
F 3 "" H 4750 5100 50  0001 C CNN
	1    4750 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C16
U 1 1 5D99969F
P 4750 4950
F 0 "C16" H 4550 5050 50  0000 L CNN
F 1 "100nF" H 4500 4850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4750 4950 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 4750 4950 50  0001 C CNN
F 4 "0.01" H 4750 4950 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 4750 4950 50  0001 C CNN "Purchase link"
F 6 "50" H 4750 4950 50  0001 C CNN "min_quantity"
	1    4750 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 5050 4750 5100
Wire Wire Line
	4950 4800 4950 5450
Wire Wire Line
	4800 1650 4800 1500
$Comp
L power:+3.3V #PWR037
U 1 1 5D9A80EC
P 4800 800
F 0 "#PWR037" H 4800 650 50  0001 C CNN
F 1 "+3.3V" H 4815 973 50  0000 C CNN
F 2 "" H 4800 800 50  0001 C CNN
F 3 "" H 4800 800 50  0001 C CNN
	1    4800 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1650 4900 1500
Wire Wire Line
	4900 1500 4800 1500
Connection ~ 4800 1500
Wire Wire Line
	4800 1500 4800 950 
Wire Wire Line
	4800 950  5300 950 
Wire Wire Line
	5300 950  5300 1050
Connection ~ 4800 950 
Wire Wire Line
	4800 950  4800 800 
$Comp
L power:GND #PWR038
U 1 1 5D9AF04C
P 5300 1350
F 0 "#PWR038" H 5300 1100 50  0001 C CNN
F 1 "GND" H 5305 1177 50  0000 C CNN
F 2 "" H 5300 1350 50  0001 C CNN
F 3 "" H 5300 1350 50  0001 C CNN
	1    5300 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 950  5750 1050
$Comp
L power:GND #PWR039
U 1 1 5D9B4503
P 5750 1350
F 0 "#PWR039" H 5750 1100 50  0001 C CNN
F 1 "GND" H 5755 1177 50  0000 C CNN
F 2 "" H 5750 1350 50  0001 C CNN
F 3 "" H 5750 1350 50  0001 C CNN
	1    5750 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C17
U 1 1 5D9BAB69
P 5300 1150
F 0 "C17" H 5392 1196 50  0000 L CNN
F 1 "100nF" H 5392 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5300 1150 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 5300 1150 50  0001 C CNN
F 4 "0.01" H 5300 1150 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 5300 1150 50  0001 C CNN "Purchase link"
F 6 "50" H 5300 1150 50  0001 C CNN "min_quantity"
	1    5300 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1250 5300 1350
$Comp
L Device:C_Small C18
U 1 1 5D9BB0A6
P 5750 1150
F 0 "C18" H 5842 1196 50  0000 L CNN
F 1 "10uF" H 5842 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5750 1150 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 5750 1150 50  0001 C CNN
F 4 "0.07" H 5750 1150 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 5750 1150 50  0001 C CNN "Purchase link"
F 6 "100" H 5750 1150 50  0001 C CNN "min_quantity"
	1    5750 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 1250 5750 1350
Wire Wire Line
	5300 950  5750 950 
Connection ~ 5300 950 
Text Notes 5150 850  0    50   ~ 0
Power supply decoupling capacitors \n(100 nF ceramic,10 μF Al) should be placed \nas near as possible to the supply pin of the \ndevice (common design practice). 
Wire Wire Line
	3050 3400 3050 3600
$Comp
L Device:C_Small C24
U 1 1 5D9CF4D4
P 3050 3300
F 0 "C24" H 3142 3346 50  0000 L CNN
F 1 "10nF" H 3142 3255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3050 3300 50  0001 C CNN
F 3 "~" H 3050 3300 50  0001 C CNN
F 4 "0.031" H 3050 3300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8391727/" H 3050 3300 50  0001 C CNN "Purchase link"
F 6 "100" H 3050 3300 50  0001 C CNN "min_quantity"
	1    3050 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR040
U 1 1 5D9CF122
P 3050 3600
F 0 "#PWR040" H 3050 3350 50  0001 C CNN
F 1 "GND" H 3055 3427 50  0000 C CNN
F 2 "" H 3050 3600 50  0001 C CNN
F 3 "" H 3050 3600 50  0001 C CNN
	1    3050 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 2950 3050 3200
Wire Wire Line
	3800 2950 3050 2950
Wire Wire Line
	3450 3400 3450 3600
$Comp
L Device:C_Small C25
U 1 1 5D9D48A7
P 3450 3300
F 0 "C25" H 3542 3346 50  0000 L CNN
F 1 "100nF" H 3542 3255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3450 3300 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 3450 3300 50  0001 C CNN
F 4 "0.01" H 3450 3300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 3450 3300 50  0001 C CNN "Purchase link"
F 6 "50" H 3450 3300 50  0001 C CNN "min_quantity"
	1    3450 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR041
U 1 1 5D9D48B1
P 3450 3600
F 0 "#PWR041" H 3450 3350 50  0001 C CNN
F 1 "GND" H 3455 3427 50  0000 C CNN
F 2 "" H 3450 3600 50  0001 C CNN
F 3 "" H 3450 3600 50  0001 C CNN
	1    3450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3050 3450 3200
Wire Wire Line
	3800 3050 3450 3050
Text Notes 3500 4050 0    50   ~ 0
Capacitor C1 (100 nF) should be a \ncapacitor with low ESR value and should \nbe placed as near as possible to the C1 pin.
Text Notes 2200 4100 0    50   ~ 0
C24(10nF) must guarantee \n1 nF value under 11 V bias \ncondition
$Comp
L flight-computer:H3LIS100DL U5
U 1 1 5D9FB40D
P 4150 5750
F 0 "U5" H 4150 6315 50  0000 C CNN
F 1 "H3LIS100DL" H 4150 6224 50  0000 C CNN
F 2 "flight-computer:TFLGA-16_3x3mm" H 3550 6550 50  0001 L BNN
F 3 "https://docs-emea.rs-online.com/webdocs/14da/0900766b814da09a.pdf" H 3550 6550 50  0001 L BNN
F 4 "2.47" H 4150 5750 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/accelerometer-sensors/1116448/" H 4150 5750 50  0001 C CNN "Purchase link"
F 6 "2" H 4150 5750 50  0001 C CNN "min_quantity"
	1    4150 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4150 1750 4150
Wire Wire Line
	1300 4400 1650 4400
$Comp
L Sensor_Motion:LSM9DS1 U1
U 1 1 5D90FFF3
P 4500 2450
F 0 "U1" H 4100 1600 50  0000 C CNN
F 1 "LSM9DS1" H 4100 1450 50  0000 C CNN
F 2 "Package_LGA:LGA-24L_3x3.5mm_P0.43mm" H 6000 3200 50  0001 C CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/1e/3f/2a/d6/25/eb/48/46/DM00103319.pdf/files/DM00103319.pdf/jcr:content/translations/en.DM00103319.pdf" H 4500 2550 50  0001 C CNN
F 4 "5.52" H 4500 2450 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/stmicroelectronics/lsm9ds1tr/mems-accelero-gyroscope-magneto/dp/2532383?st=LSM9DS1" H 4500 2450 50  0001 C CNN "Purchase link"
F 6 "1" H 4500 2450 50  0001 C CNN "min_quantity"
	1    4500 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2350 3350 2350
Wire Wire Line
	3350 2350 3350 2300
$Comp
L power:+3.3V #PWR046
U 1 1 5DA31C3E
P 3350 2300
F 0 "#PWR046" H 3350 2150 50  0001 C CNN
F 1 "+3.3V" H 3365 2473 50  0000 C CNN
F 2 "" H 3350 2300 50  0001 C CNN
F 3 "" H 3350 2300 50  0001 C CNN
	1    3350 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2050 3700 2050
Wire Wire Line
	3700 2050 3700 1400
Wire Wire Line
	3700 1400 1650 1400
Wire Wire Line
	1650 1400 1650 4400
Wire Wire Line
	3800 2150 3600 2150
Wire Wire Line
	3600 2150 3600 1500
Wire Wire Line
	3600 1500 1750 1500
Wire Wire Line
	1750 1500 1750 4150
Wire Wire Line
	5200 2050 5400 2050
Wire Wire Line
	5400 2050 5400 1900
$Comp
L power:+3.3V #PWR047
U 1 1 5DA4DC9B
P 5400 1900
F 0 "#PWR047" H 5400 1750 50  0001 C CNN
F 1 "+3.3V" H 5415 2073 50  0000 C CNN
F 2 "" H 5400 1900 50  0001 C CNN
F 3 "" H 5400 1900 50  0001 C CNN
	1    5400 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2450 3350 2450
Wire Wire Line
	3350 2450 3350 2350
Connection ~ 3350 2350
Wire Wire Line
	5200 2150 5400 2150
Wire Wire Line
	5400 2150 5400 2050
Connection ~ 5400 2050
Text Notes 2100 2000 0    50   ~ 0
The slave address for accl/gyro is \n11010111b(D7h) for Read and \n11010110b (D6h) for Write.
Text Notes 5600 2050 0    50   ~ 0
The slave address for mag is \n00111101b (3Dh) for Read and \n00111100b (3Ch) for Write.
NoConn ~ 3800 2750
Text HLabel 3350 2550 0    50   Input ~ 0
ACCL_RDY
Wire Wire Line
	3800 2550 3350 2550
Text HLabel 3350 2650 0    50   Input ~ 0
GYRO_RDY
Wire Wire Line
	3800 2650 3350 2650
Text HLabel 5650 2250 2    50   Input ~ 0
MAG_RDY
Wire Wire Line
	5200 2250 5650 2250
NoConn ~ 5200 2350
Wire Wire Line
	7500 3100 7500 3450
Connection ~ 7500 4150
Wire Wire Line
	7500 4150 8850 4150
Wire Wire Line
	7800 4400 7800 3750
Connection ~ 7800 4400
Wire Wire Line
	7800 4400 8700 4400
$Comp
L power:+3.3V #PWR048
U 1 1 5D93D3F3
P 7500 3100
F 0 "#PWR048" H 7500 2950 50  0001 C CNN
F 1 "+3.3V" H 7515 3273 50  0000 C CNN
F 2 "" H 7500 3100 50  0001 C CNN
F 3 "" H 7500 3100 50  0001 C CNN
	1    7500 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR049
U 1 1 5D93D8A4
P 7800 3100
F 0 "#PWR049" H 7800 2950 50  0001 C CNN
F 1 "+3.3V" H 7815 3273 50  0000 C CNN
F 2 "" H 7800 3100 50  0001 C CNN
F 3 "" H 7800 3100 50  0001 C CNN
	1    7800 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5D93DCCD
P 7500 3600
F 0 "R4" H 7570 3646 50  0000 L CNN
F 1 "4.7K" H 7570 3555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7430 3600 50  0001 C CNN
F 3 "~" H 7500 3600 50  0001 C CNN
F 4 "0.01" H 7500 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408877/" H 7500 3600 50  0001 C CNN "Purchase link"
F 6 "50" H 7500 3600 50  0001 C CNN "min_quantity"
	1    7500 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3750 7500 4150
$Comp
L Device:R R8
U 1 1 5D93E817
P 7800 3600
F 0 "R8" H 7870 3646 50  0000 L CNN
F 1 "4.7K" H 7870 3555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7730 3600 50  0001 C CNN
F 3 "~" H 7800 3600 50  0001 C CNN
F 4 "0.01" H 7800 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408877/" H 7800 3600 50  0001 C CNN "Purchase link"
F 6 "50" H 7800 3600 50  0001 C CNN "min_quantity"
	1    7800 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3450 7800 3100
$EndSCHEMATC

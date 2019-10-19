EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 5
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
Wire Wire Line
	8700 4400 8700 5450
Wire Wire Line
	8850 4150 8850 5350
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
Wire Wire Line
	1300 4400 7800 4400
Wire Wire Line
	1300 4150 7500 4150
$EndSCHEMATC

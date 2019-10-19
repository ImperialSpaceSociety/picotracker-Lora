EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
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
L power:GND #PWR0106
U 1 1 5D8CC1E1
P 10900 5600
F 0 "#PWR0106" H 10900 5350 50  0001 C CNN
F 1 "GND" H 10905 5427 50  0000 C CNN
F 2 "" H 10900 5600 50  0001 C CNN
F 3 "" H 10900 5600 50  0001 C CNN
	1    10900 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 5300 10900 5600
Connection ~ 10900 5300
Wire Wire Line
	10900 4900 10900 5300
Wire Wire Line
	10050 4900 9700 4900
Wire Wire Line
	10050 5300 9700 5300
Text Label 9700 5300 0    50   ~ 0
LED_BLUE
Text Label 9700 4900 0    50   ~ 0
LED_RED
Wire Wire Line
	10350 5300 10450 5300
Wire Wire Line
	10750 5300 10900 5300
Wire Wire Line
	10350 4900 10450 4900
Wire Wire Line
	10750 4900 10900 4900
Wire Notes Line
	9550 6150 11050 6150
Text Notes 9600 6100 0    50   ~ 0
Two indicator LEDs
$Comp
L Device:R R25
U 1 1 5D84A9D3
P 10200 4900
F 0 "R25" V 10100 5000 50  0000 C CNN
F 1 "1K" V 10100 4850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10130 4900 50  0001 C CNN
F 3 "~" H 10200 4900 50  0001 C CNN
F 4 "0.035" H 10200 4900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/2132266/" H 10200 4900 50  0001 C CNN "Purchase link"
F 6 "50" H 10200 4900 50  0001 C CNN "min_quantity"
	1    10200 4900
	0    1    1    0   
$EndComp
$Comp
L Device:LED D1
U 1 1 5D84CD91
P 10600 4900
F 0 "D1" H 10593 4645 50  0000 C CNN
F 1 "RED_LED" H 10593 4736 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 10600 4900 50  0001 C CNN
F 3 "~" H 10600 4900 50  0001 C CNN
F 4 "0.038" H 10600 4900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/leds/0450711/" H 10600 4900 50  0001 C CNN "Purchase link"
F 6 "50" H 10600 4900 50  0001 C CNN "min_quantity"
	1    10600 4900
	-1   0    0    1   
$EndComp
$Comp
L Device:R R26
U 1 1 5D8A257E
P 10200 5300
F 0 "R26" V 10100 5400 50  0000 C CNN
F 1 "1K" V 10100 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10130 5300 50  0001 C CNN
F 3 "~" H 10200 5300 50  0001 C CNN
F 4 "0.035" H 10200 5300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/2132266/" H 10200 5300 50  0001 C CNN "Purchase link"
F 6 "50" H 10200 5300 50  0001 C CNN "min_quantity"
	1    10200 5300
	0    1    1    0   
$EndComp
$Comp
L Device:LED D2
U 1 1 5D8A258A
P 10600 5300
F 0 "D2" H 10593 5045 50  0000 C CNN
F 1 "BLUE_LED" H 10593 5136 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 10600 5300 50  0001 C CNN
F 3 "~" H 10600 5300 50  0001 C CNN
	1    10600 5300
	-1   0    0    1   
$EndComp
Wire Notes Line
	9550 4500 11050 4500
Wire Notes Line
	11050 6150 11050 4500
Wire Notes Line
	9550 6150 9550 4500
$Comp
L RF_Module:CMWX1ZZABZ-078 U?
U 1 1 5DB27A2E
P 5250 3600
F 0 "U?" H 4700 1750 50  0000 C CNN
F 1 "CMWX1ZZABZ-078" H 4750 2000 50  0000 C CNN
F 2 "RF_Module:CMWX1ZZABZ" H 5250 3600 50  0001 C CNN
F 3 "https://wireless.murata.com/RFM/data/type_abz.pdf" H 7700 2100 50  0001 C CNN
	1    5250 3600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 5DB45FE9
P 7250 1300
F 0 "J?" H 7330 1292 50  0000 L CNN
F 1 "Conn_01x06" H 7330 1201 50  0000 L CNN
F 2 "" H 7250 1300 50  0001 C CNN
F 3 "~" H 7250 1300 50  0001 C CNN
	1    7250 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DB48751
P 5250 5450
F 0 "#PWR?" H 5250 5200 50  0001 C CNN
F 1 "GND" H 5255 5277 50  0000 C CNN
F 2 "" H 5250 5450 50  0001 C CNN
F 3 "" H 5250 5450 50  0001 C CNN
	1    5250 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 5450 5250 5100
$EndSCHEMATC

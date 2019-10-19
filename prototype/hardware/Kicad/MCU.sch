EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
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
L power:GND #PWR03
U 1 1 5D291249
P 3850 2600
F 0 "#PWR03" H 3850 2350 50  0001 C CNN
F 1 "GND" H 3855 2427 50  0000 C CNN
F 2 "" H 3850 2600 50  0001 C CNN
F 3 "" H 3850 2600 50  0001 C CNN
	1    3850 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5D29204A
P 4000 1600
F 0 "#PWR02" H 4000 1350 50  0001 C CNN
F 1 "GND" H 4005 1427 50  0000 C CNN
F 2 "" H 4000 1600 50  0001 C CNN
F 3 "" H 4000 1600 50  0001 C CNN
	1    4000 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2600 3850 2500
Wire Wire Line
	3850 2400 3850 2500
Connection ~ 3850 2500
Wire Wire Line
	4000 1600 4000 1500
Wire Wire Line
	4550 1400 4550 1500
Wire Wire Line
	3850 2100 3850 1900
Wire Wire Line
	4400 2100 4400 1900
Wire Wire Line
	4550 1100 4550 950 
Wire Wire Line
	4000 950  4000 1100
Wire Wire Line
	4000 1400 4000 1500
Connection ~ 4000 1500
$Comp
L power:GND #PWR08
U 1 1 5D2B6380
P 1600 5350
F 0 "#PWR08" H 1600 5100 50  0001 C CNN
F 1 "GND" H 1605 5177 50  0000 C CNN
F 2 "" H 1600 5350 50  0001 C CNN
F 3 "" H 1600 5350 50  0001 C CNN
	1    1600 5350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1650 4550 1350 4550
Wire Wire Line
	1600 4650 1350 4650
Wire Wire Line
	1650 3600 1650 3750
Wire Wire Line
	2000 3900 2000 3750
Wire Wire Line
	2000 3750 1650 3750
Connection ~ 1650 3750
Wire Wire Line
	1650 3750 1650 4550
Wire Wire Line
	2000 4200 2000 4350
Wire Wire Line
	2000 4350 1350 4350
Wire Wire Line
	1950 4550 1650 4550
Connection ~ 1650 4550
Wire Wire Line
	1950 5100 1950 5200
Wire Wire Line
	1950 5200 1600 5200
Wire Wire Line
	1600 5200 1600 5350
Wire Wire Line
	1950 4800 1950 4550
Wire Wire Line
	4000 950  4550 950 
Wire Wire Line
	4000 1500 4550 1500
Wire Wire Line
	3850 1900 4400 1900
Wire Wire Line
	3850 2500 4400 2500
Wire Wire Line
	4400 2400 4400 2500
Wire Wire Line
	3450 1900 3750 1900
Wire Wire Line
	7600 950  7600 750 
Connection ~ 7050 950 
Wire Wire Line
	7050 950  7600 950 
Wire Wire Line
	7050 950  7050 1100
Wire Wire Line
	6650 950  7050 950 
Wire Wire Line
	6650 950  6650 1100
Wire Wire Line
	7050 1550 7050 1650
Connection ~ 7050 1550
Wire Wire Line
	6650 1550 7050 1550
Wire Wire Line
	6650 1400 6650 1550
Wire Wire Line
	7050 1400 7050 1550
Wire Wire Line
	1600 4650 1600 5200
Connection ~ 1600 5200
$Comp
L power:GND #PWR050
U 1 1 5DEA12DE
P 8100 2750
F 0 "#PWR050" H 8100 2500 50  0001 C CNN
F 1 "GND" H 8105 2577 50  0000 C CNN
F 2 "" H 8100 2750 50  0001 C CNN
F 3 "" H 8100 2750 50  0001 C CNN
	1    8100 2750
	1    0    0    -1  
$EndComp
Connection ~ 10250 2150
Wire Wire Line
	10250 2150 10800 2150
Wire Wire Line
	10250 2150 10250 2300
Wire Wire Line
	9850 2150 10250 2150
Wire Wire Line
	9850 2150 9850 2300
Wire Wire Line
	10250 2750 10250 2850
Connection ~ 10250 2750
Wire Wire Line
	9850 2750 10250 2750
Wire Wire Line
	9850 2600 9850 2750
Wire Wire Line
	10250 2600 10250 2750
$Comp
L power:GND #PWR091
U 1 1 5D640690
P 10250 2850
F 0 "#PWR091" H 10250 2600 50  0001 C CNN
F 1 "GND" H 10255 2677 50  0000 C CNN
F 2 "" H 10250 2850 50  0001 C CNN
F 3 "" H 10250 2850 50  0001 C CNN
	1    10250 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR090
U 1 1 5D649194
P 6000 6600
F 0 "#PWR090" H 6000 6350 50  0001 C CNN
F 1 "GND" H 6005 6427 50  0000 C CNN
F 2 "" H 6000 6600 50  0001 C CNN
F 3 "" H 6000 6600 50  0001 C CNN
	1    6000 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 6600 6000 6450
Wire Wire Line
	6000 6450 6200 6450
Wire Wire Line
	6200 6450 6200 6300
Connection ~ 6000 6450
Wire Wire Line
	6000 6450 6000 6300
Text Label 4250 4300 2    50   ~ 0
XIN
Text Label 4250 4400 2    50   ~ 0
XOUT
Text Label 4250 5700 2    50   ~ 0
SWDIO
$Comp
L power:GND #PWR089
U 1 1 5D6856C6
P 5400 1600
F 0 "#PWR089" H 5400 1350 50  0001 C CNN
F 1 "GND" H 5405 1427 50  0000 C CNN
F 2 "" H 5400 1600 50  0001 C CNN
F 3 "" H 5400 1600 50  0001 C CNN
	1    5400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 1600 5400 1500
Wire Wire Line
	5950 1400 5950 1500
Wire Wire Line
	5950 1100 5950 950 
Wire Wire Line
	5400 950  5400 1100
Wire Wire Line
	5400 1400 5400 1500
Connection ~ 5400 1500
Wire Wire Line
	5400 950  5950 950 
Wire Wire Line
	5400 1500 5950 1500
NoConn ~ 6300 2500
Wire Wire Line
	6400 950  6650 950 
Connection ~ 6650 950 
Wire Wire Line
	6200 950  6050 950 
Connection ~ 5950 950 
Connection ~ 4550 950 
Wire Wire Line
	4550 950  4550 750 
Wire Wire Line
	4850 5900 5100 5900
Wire Wire Line
	6400 950  6400 2500
Wire Wire Line
	6200 950  6200 2500
Connection ~ 3850 1900
Wire Wire Line
	4400 1900 5100 1900
Wire Wire Line
	5100 1900 5100 2350
Wire Wire Line
	5100 2350 5800 2350
Wire Wire Line
	5800 2350 5800 2500
Connection ~ 4400 1900
Wire Wire Line
	6000 2500 6000 2100
Wire Wire Line
	6000 2100 5200 2100
Wire Wire Line
	5200 2100 5200 950 
Wire Wire Line
	4550 950  5200 950 
Wire Wire Line
	2400 5600 2400 4350
Wire Wire Line
	2400 4350 2000 4350
Wire Wire Line
	2400 5600 5100 5600
Connection ~ 2000 4350
Wire Wire Line
	2250 4450 1350 4450
$Comp
L power:GND #PWR083
U 1 1 5D6EF8B0
P 2800 4850
F 0 "#PWR083" H 2800 4600 50  0001 C CNN
F 1 "GND" H 2805 4677 50  0000 C CNN
F 2 "" H 2800 4850 50  0001 C CNN
F 3 "" H 2800 4850 50  0001 C CNN
	1    2800 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4400 2800 4500
Wire Wire Line
	2800 4850 2800 4800
Wire Wire Line
	2800 4400 2800 4050
Connection ~ 2800 4400
$Comp
L power:GND #PWR087
U 1 1 5D70CF68
P 4450 7450
F 0 "#PWR087" H 4450 7200 50  0001 C CNN
F 1 "GND" H 4455 7277 50  0000 C CNN
F 2 "" H 4450 7450 50  0001 C CNN
F 3 "" H 4450 7450 50  0001 C CNN
	1    4450 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 7350 4450 7450
Wire Wire Line
	5100 5700 2250 5700
Wire Wire Line
	2250 5700 2250 4450
Wire Wire Line
	5100 5200 4550 5200
Wire Wire Line
	5100 5100 4550 5100
Wire Wire Line
	5100 3100 4550 3100
Text HLabel 4550 5100 0    50   BiDi ~ 0
MCU_SDA3
Text HLabel 4550 5200 0    50   BiDi ~ 0
MCU_SCL3
Wire Wire Line
	5100 3900 4550 3900
Wire Wire Line
	5100 4000 4550 4000
Text HLabel 4550 4500 0    50   Output ~ 0
GPS_TXD0
Text HLabel 4550 4600 0    50   Input ~ 0
GPS_RXD0
Text HLabel 4550 3100 0    50   Input ~ 0
MCU_PA02
Wire Wire Line
	8950 2150 9100 2150
Connection ~ 9850 2150
Wire Wire Line
	8200 2600 8100 2600
Wire Wire Line
	8100 2600 8100 2750
Wire Wire Line
	7100 3500 7650 3500
Wire Wire Line
	8100 1750 9100 1750
Wire Wire Line
	9100 1750 9100 2150
Connection ~ 9100 2150
Wire Wire Line
	8200 2450 8100 2450
Wire Wire Line
	8100 2450 8100 1750
Wire Wire Line
	8950 2300 9100 2300
Wire Wire Line
	9100 2300 9100 2150
Text Label 7650 3500 2    50   ~ 0
MCU_MOSI4
Text Label 7650 3600 2    50   ~ 0
MCU_SCLK4
Text Label 9450 2450 2    50   ~ 0
MCU_SCLK4
Wire Wire Line
	9100 2150 9850 2150
Wire Wire Line
	8200 2150 7500 2150
Wire Wire Line
	8200 2300 7500 2300
Wire Wire Line
	8950 2600 9450 2600
Text Label 7500 2300 0    50   ~ 0
MCU_MISO4
Text Label 7500 2150 0    50   ~ 0
MCU_NSEL4
Text Label 9450 2600 2    50   ~ 0
MCU_MOSI4
$Comp
L power:GND #PWR021
U 1 1 5D659D89
P 10450 4000
F 0 "#PWR021" H 10450 3750 50  0001 C CNN
F 1 "GND" H 10455 3827 50  0000 C CNN
F 2 "" H 10450 4000 50  0001 C CNN
F 3 "" H 10450 4000 50  0001 C CNN
	1    10450 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 4000 10450 3700
Wire Wire Line
	10450 3700 10500 3700
$Comp
L power:+3.3V #PWR022
U 1 1 5D667177
P 10800 1750
F 0 "#PWR022" H 10800 1600 50  0001 C CNN
F 1 "+3.3V" H 10815 1923 50  0000 C CNN
F 2 "" H 10800 1750 50  0001 C CNN
F 3 "" H 10800 1750 50  0001 C CNN
	1    10800 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 2150 10800 1750
$Comp
L power:+3.3V #PWR020
U 1 1 5D699E9A
P 7600 750
F 0 "#PWR020" H 7600 600 50  0001 C CNN
F 1 "+3.3V" H 7615 923 50  0000 C CNN
F 2 "" H 7600 750 50  0001 C CNN
F 3 "" H 7600 750 50  0001 C CNN
	1    7600 750 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR019
U 1 1 5D6A08FD
P 4550 750
F 0 "#PWR019" H 4550 600 50  0001 C CNN
F 1 "+3.3V" H 4565 923 50  0000 C CNN
F 2 "" H 4550 750 50  0001 C CNN
F 3 "" H 4550 750 50  0001 C CNN
	1    4550 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1500 3000 1900
$Comp
L power:+3.3V #PWR06
U 1 1 5D6AE562
P 3000 1500
F 0 "#PWR06" H 3000 1350 50  0001 C CNN
F 1 "+3.3V" H 3015 1673 50  0000 C CNN
F 2 "" H 3000 1500 50  0001 C CNN
F 3 "" H 3000 1500 50  0001 C CNN
	1    3000 1500
	1    0    0    -1  
$EndComp
Wire Notes Line
	550  3200 2550 3200
Wire Notes Line
	2550 6100 550  6100
Text Notes 700  3300 0    50   ~ 0
Programming interface\n
$Comp
L power:+3.3V #PWR0102
U 1 1 5D6C8291
P 1650 3600
F 0 "#PWR0102" H 1650 3450 50  0001 C CNN
F 1 "+3.3V" H 1665 3773 50  0000 C CNN
F 2 "" H 1650 3600 50  0001 C CNN
F 3 "" H 1650 3600 50  0001 C CNN
	1    1650 3600
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D6D0649
P 3750 1900
F 0 "#FLG0101" H 3750 1975 50  0001 C CNN
F 1 "PWR_FLAG" H 3750 2073 50  0000 C CNN
F 2 "" H 3750 1900 50  0001 C CNN
F 3 "~" H 3750 1900 50  0001 C CNN
	1    3750 1900
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5D6D0FB6
P 6050 950
F 0 "#FLG0102" H 6050 1025 50  0001 C CNN
F 1 "PWR_FLAG" H 6050 1123 50  0000 C CNN
F 2 "" H 6050 950 50  0001 C CNN
F 3 "~" H 6050 950 50  0001 C CNN
	1    6050 950 
	1    0    0    -1  
$EndComp
Connection ~ 6050 950 
Wire Wire Line
	6050 950  5950 950 
Connection ~ 3750 1900
Wire Wire Line
	3750 1900 3850 1900
Wire Wire Line
	3000 1900 3150 1900
Text HLabel 4550 4900 0    50   Input ~ 0
MCU_PA20
Wire Wire Line
	4550 4900 5100 4900
Text HLabel 4550 5000 0    50   Input ~ 0
MCU_PA21
Wire Wire Line
	4550 5000 5100 5000
Wire Notes Line
	7450 1500 7450 3100
Wire Notes Line
	7450 3100 11050 3100
Wire Notes Line
	11050 1500 7450 1500
Text Notes 7500 3050 0    50   ~ 0
SPI flash chip
Wire Wire Line
	7100 3600 7650 3600
Text Label 7650 3400 2    50   ~ 0
MCU_NSEL4
Wire Wire Line
	8950 2450 9450 2450
Wire Wire Line
	7650 4500 7100 4500
Text Label 9850 3500 0    50   ~ 0
BUZZER
Wire Wire Line
	9850 3500 10500 3500
Text Notes 9600 4450 0    50   ~ 0
Buzzer\n
Wire Wire Line
	7100 4600 7650 4600
Wire Wire Line
	7100 4700 7650 4700
Wire Wire Line
	7100 4800 7650 4800
Text Label 4250 5600 2    50   ~ 0
SWCLK
Wire Notes Line
	11050 1500 11050 6150
Text Label 7650 5100 2    50   ~ 0
LED_RED
Wire Wire Line
	7100 5100 7650 5100
Text Label 7650 5200 2    50   ~ 0
LED_BLUE
Wire Wire Line
	7100 5200 7650 5200
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
Text HLabel 4550 5400 0    50   Input ~ 0
USB_DP
Text HLabel 4550 5300 0    50   Input ~ 0
USB_DM
Wire Wire Line
	4550 5400 5100 5400
Wire Wire Line
	4550 5300 5100 5300
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
Wire Wire Line
	1000 1150 900  1150
Wire Wire Line
	900  1150 900  1350
Wire Wire Line
	1000 1350 900  1350
Connection ~ 900  1350
Wire Wire Line
	900  1350 900  1550
Wire Wire Line
	1000 1550 900  1550
Connection ~ 900  1550
Wire Wire Line
	900  1550 900  1750
Wire Wire Line
	1000 1750 900  1750
Connection ~ 900  1750
Wire Wire Line
	900  1750 900  2000
$Comp
L power:GND #PWR01
U 1 1 5D815831
P 900 2000
F 0 "#PWR01" H 900 1750 50  0001 C CNN
F 1 "GND" H 905 1827 50  0000 C CNN
F 2 "" H 900 2000 50  0001 C CNN
F 3 "" H 900 2000 50  0001 C CNN
	1    900  2000
	1    0    0    -1  
$EndComp
Wire Notes Line
	550  700  550  2400
Wire Notes Line
	550  2400 2150 2400
Wire Notes Line
	2150 2400 2150 700 
Wire Notes Line
	2150 700  550  700 
Text Notes 1000 2350 0    50   ~ 0
Mechanical mounting holes
Wire Wire Line
	1350 4750 1450 4750
Wire Wire Line
	4450 6350 4450 6450
$Comp
L power:+3.3V #PWR0117
U 1 1 5D7A484D
P 4450 6350
F 0 "#PWR0117" H 4450 6200 50  0001 C CNN
F 1 "+3.3V" H 4400 6500 50  0000 C CNN
F 2 "" H 4450 6350 50  0001 C CNN
F 3 "" H 4450 6350 50  0001 C CNN
	1    4450 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 6750 4450 6900
Wire Wire Line
	4450 6900 4850 6900
Wire Wire Line
	4850 5900 4850 6900
Connection ~ 4450 6900
Wire Wire Line
	4450 6900 4450 7050
Wire Wire Line
	4850 5900 1450 5900
Wire Wire Line
	1450 4750 1450 5900
Connection ~ 4850 5900
Wire Wire Line
	3900 4050 2800 4050
Wire Wire Line
	3900 4300 5100 4300
Wire Wire Line
	3900 4300 3900 4050
Wire Notes Line
	9550 3100 9550 6150
$Comp
L power:GND #PWR085
U 1 1 5D6EF8BA
P 3750 4850
F 0 "#PWR085" H 3750 4600 50  0001 C CNN
F 1 "GND" H 3755 4677 50  0000 C CNN
F 2 "" H 3750 4850 50  0001 C CNN
F 3 "" H 3750 4850 50  0001 C CNN
	1    3750 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 4850 3750 4800
Wire Wire Line
	3750 4400 5100 4400
Connection ~ 3750 4400
Wire Wire Line
	3750 4500 3750 4400
$Comp
L power:GND #PWR018
U 1 1 5D9449AE
P 3300 4850
F 0 "#PWR018" H 3300 4600 50  0001 C CNN
F 1 "GND" H 3305 4677 50  0000 C CNN
F 2 "" H 3300 4850 50  0001 C CNN
F 3 "" H 3300 4850 50  0001 C CNN
	1    3300 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5D2924BD
P 7050 1650
F 0 "#PWR05" H 7050 1400 50  0001 C CNN
F 1 "GND" H 7055 1477 50  0000 C CNN
F 2 "" H 7050 1650 50  0001 C CNN
F 3 "" H 7050 1650 50  0001 C CNN
	1    7050 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C88
U 1 1 5D6EF89C
P 3750 4650
F 0 "C88" H 3865 4696 50  0000 L CNN
F 1 "15pF" H 3865 4605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3788 4500 50  0001 C CNN
F 3 "~" H 3750 4650 50  0001 C CNN
F 4 "0.043" H 3750 4650 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/3936659/" H 3750 4650 50  0001 C CNN "Purchase link"
F 6 "25" H 3750 4650 50  0001 C CNN "min_quantity"
	1    3750 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 5D70BAB2
P 4450 6600
F 0 "R12" H 4520 6646 50  0000 L CNN
F 1 "1K" H 4520 6555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 6600 50  0001 C CNN
F 3 "~" H 4450 6600 50  0001 C CNN
F 4 "0.035" H 4450 6600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/2132266/" H 4450 6600 50  0001 C CNN "Purchase link"
F 6 "50" H 4450 6600 50  0001 C CNN "min_quantity"
	1    4450 6600
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 5D3DC905
P 1150 4550
F 0 "J1" H 1230 4542 50  0000 L CNN
F 1 "Conn_01x05" H 1230 4451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 1150 4550 50  0001 C CNN
F 3 "~" H 1150 4550 50  0001 C CNN
	1    1150 4550
	-1   0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5D7F8445
P 1100 1750
F 0 "H4" V 1054 1900 50  0000 L CNN
F 1 "MountingHole_Pad" V 1145 1900 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1100 1750 50  0001 C CNN
F 3 "~" H 1100 1750 50  0001 C CNN
F 4 "0.0" H 1100 1750 50  0001 C CNN "Cost"
	1    1100 1750
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5D7F817E
P 1100 1550
F 0 "H3" V 1054 1700 50  0000 L CNN
F 1 "MountingHole_Pad" V 1145 1700 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1100 1550 50  0001 C CNN
F 3 "~" H 1100 1550 50  0001 C CNN
F 4 "0.0" H 1100 1550 50  0001 C CNN "Cost"
	1    1100 1550
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5D7F7FA5
P 1100 1350
F 0 "H2" V 1054 1500 50  0000 L CNN
F 1 "MountingHole_Pad" V 1145 1500 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1100 1350 50  0001 C CNN
F 3 "~" H 1100 1350 50  0001 C CNN
F 4 "0.0" H 1100 1350 50  0001 C CNN "Cost"
	1    1100 1350
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5D7F142B
P 1100 1150
F 0 "H1" V 1054 1300 50  0000 L CNN
F 1 "MountingHole_Pad" V 1145 1300 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1100 1150 50  0001 C CNN
F 3 "~" H 1100 1150 50  0001 C CNN
F 4 "0.0" H 1100 1150 50  0001 C CNN "Cost"
	1    1100 1150
	0    1    1    0   
$EndComp
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
$Comp
L Device:L_Core_Ferrite L1
U 1 1 5D298AE9
P 3300 1900
F 0 "L1" V 3525 1900 50  0000 C CNN
F 1 "L_Core_Ferrite" V 3450 1900 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" H 3300 1900 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/07a1/0900766b807a1caf.pdf" H 3300 1900 50  0001 C CNN
F 4 "0.05" H 3300 1900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/ferrite-beads/7926299/" H 3300 1900 50  0001 C CNN "Purchase link"
F 6 "25" H 3300 1900 50  0001 C CNN "min_quantity"
	1    3300 1900
	0    -1   -1   0   
$EndComp
$Comp
L Device:Buzzer BZ1
U 1 1 5D650F14
P 10600 3600
F 0 "BZ1" H 10752 3629 50  0000 L CNN
F 1 "Buzzer" H 10752 3538 50  0000 L CNN
F 2 "Buzzer_Beeper:Buzzer_12x9.5RM7.6" V 10575 3700 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/1581/0900766b815810c5.pdf" V 10575 3700 50  0001 C CNN
F 4 "1.05" H 10600 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/magnetic-buzzer-components/6173081/?searchTerm=6173081&relevancy-data=636F3D3126696E3D4931384E525353746F636B4E756D6265724D504E266C753D656E266D6D3D6D61746368616C6C26706D3D5E5C647B367D247C5E5C647B377D247C5E5C647B31307D2426706F3D313426736E3D592673743D52535F53544F434B5F4E554D4245522677633D4E4F4E45267573743D3631373330383126" H 10600 3600 50  0001 C CNN "Purchase link"
F 6 "1" H 10600 3600 50  0001 C CNN "min_quantity"
	1    10600 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C89
U 1 1 5D70C5B6
P 4450 7200
F 0 "C89" H 4565 7246 50  0000 L CNN
F 1 "100nF" H 4565 7155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4488 7050 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 4450 7200 50  0001 C CNN
F 4 "0.01" H 4450 7200 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 4450 7200 50  0001 C CNN "Purchase link"
F 6 "50" H 4450 7200 50  0001 C CNN "min_quantity"
	1    4450 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C86
U 1 1 5D6EF8A6
P 2800 4650
F 0 "C86" H 2915 4696 50  0000 L CNN
F 1 "15pF" H 2915 4605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2838 4500 50  0001 C CNN
F 3 "~" H 2800 4650 50  0001 C CNN
F 4 "0.043" H 2800 4650 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/3936659/" H 2800 4650 50  0001 C CNN "Purchase link"
F 6 "25" H 2800 4650 50  0001 C CNN "min_quantity"
	1    2800 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C90
U 1 1 5D6856DD
P 5400 1250
F 0 "C90" H 5515 1296 50  0000 L CNN
F 1 "1uF" H 5515 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5438 1100 50  0001 C CNN
F 3 "~" H 5400 1250 50  0001 C CNN
F 4 "0.01" H 5400 1250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/1358359/" H 5400 1250 50  0001 C CNN "Purchase link"
F 6 "250" H 5400 1250 50  0001 C CNN "min_quantity"
	1    5400 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C91
U 1 1 5D6856D0
P 5950 1250
F 0 "C91" H 6065 1296 50  0000 L CNN
F 1 "100nF" H 6065 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5988 1100 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 5950 1250 50  0001 C CNN
F 4 "0.01" H 5950 1250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 5950 1250 50  0001 C CNN "Purchase link"
F 6 "50" H 5950 1250 50  0001 C CNN "min_quantity"
	1    5950 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C92
U 1 1 5D6406A4
P 9850 2450
F 0 "C92" H 9965 2496 50  0000 L CNN
F 1 "10uF" H 9965 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9888 2300 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 9850 2450 50  0001 C CNN
F 4 "0.07" H 9850 2450 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 9850 2450 50  0001 C CNN "Purchase link"
F 6 "100" H 9850 2450 50  0001 C CNN "min_quantity"
	1    9850 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C93
U 1 1 5D64069A
P 10250 2450
F 0 "C93" H 10365 2496 50  0000 L CNN
F 1 "100nF" H 10365 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10288 2300 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 10250 2450 50  0001 C CNN
F 4 "0.01" H 10250 2450 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 10250 2450 50  0001 C CNN "Purchase link"
F 6 "50" H 10250 2450 50  0001 C CNN "min_quantity"
	1    10250 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5D28F904
P 6650 1250
F 0 "C5" H 6765 1296 50  0000 L CNN
F 1 "10uF" H 6765 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6688 1100 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 6650 1250 50  0001 C CNN
F 4 "0.07" H 6650 1250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 6650 1250 50  0001 C CNN "Purchase link"
F 6 "100" H 6650 1250 50  0001 C CNN "min_quantity"
	1    6650 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5D29095F
P 7050 1250
F 0 "C6" H 7165 1296 50  0000 L CNN
F 1 "100nF" H 7165 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7088 1100 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 7050 1250 50  0001 C CNN
F 4 "0.01" H 7050 1250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 7050 1250 50  0001 C CNN "Purchase link"
F 6 "50" H 7050 1250 50  0001 C CNN "min_quantity"
	1    7050 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5D2C83ED
P 1950 4950
F 0 "C7" H 2065 4996 50  0000 L CNN
F 1 "100nF" H 2065 4905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1988 4800 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 1950 4950 50  0001 C CNN
F 4 "0.01" H 1950 4950 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 1950 4950 50  0001 C CNN "Purchase link"
F 6 "50" H 1950 4950 50  0001 C CNN "min_quantity"
	1    1950 4950
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D2BB0F2
P 2000 4050
F 0 "R1" H 2070 4096 50  0000 L CNN
F 1 "1K" H 2070 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1930 4050 50  0001 C CNN
F 3 "~" H 2000 4050 50  0001 C CNN
F 4 "0.035" H 2000 4050 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/2132266/" H 2000 4050 50  0001 C CNN "Purchase link"
F 6 "50" H 2000 4050 50  0001 C CNN "min_quantity"
	1    2000 4050
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5D29D963
P 4000 1250
F 0 "C1" H 4115 1296 50  0000 L CNN
F 1 "10uF" H 4115 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4038 1100 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 4000 1250 50  0001 C CNN
F 4 "0.07" H 4000 1250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 4000 1250 50  0001 C CNN "Purchase link"
F 6 "100" H 4000 1250 50  0001 C CNN "min_quantity"
	1    4000 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5D292B82
P 4550 1250
F 0 "C3" H 4665 1296 50  0000 L CNN
F 1 "100nF" H 4665 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4588 1100 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 4550 1250 50  0001 C CNN
F 4 "0.01" H 4550 1250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 4550 1250 50  0001 C CNN "Purchase link"
F 6 "50" H 4550 1250 50  0001 C CNN "min_quantity"
	1    4550 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5D28EA5A
P 3850 2250
F 0 "C2" H 3965 2296 50  0000 L CNN
F 1 "10uF" H 3965 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3888 2100 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 3850 2250 50  0001 C CNN
F 4 "0.07" H 3850 2250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 3850 2250 50  0001 C CNN "Purchase link"
F 6 "100" H 3850 2250 50  0001 C CNN "min_quantity"
	1    3850 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5D28DF10
P 4400 2250
F 0 "C4" H 4515 2296 50  0000 L CNN
F 1 "100nF" H 4515 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4438 2100 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 4400 2250 50  0001 C CNN
F 4 "0.01" H 4400 2250 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 4400 2250 50  0001 C CNN "Purchase link"
F 6 "50" H 4400 2250 50  0001 C CNN "min_quantity"
	1    4400 2250
	1    0    0    -1  
$EndComp
Text HLabel 7650 4700 2    50   Output ~ 0
MCU_MISO1
Text HLabel 7650 4800 2    50   Input ~ 0
MCU_NSEL1
Wire Wire Line
	3300 4700 3300 4850
Connection ~ 3300 4700
Text Label 7650 3300 2    50   ~ 0
MCU_MISO4
Text Label 4550 2900 0    50   ~ 0
BUZZER
Wire Wire Line
	7100 3300 7650 3300
Wire Wire Line
	7100 3400 7650 3400
Wire Wire Line
	4550 2900 5100 2900
Text HLabel 4550 3900 0    50   BiDi ~ 0
MCU_PA10
Text HLabel 4550 4000 0    50   BiDi ~ 0
MCU_PA11
NoConn ~ 7100 4900
NoConn ~ 7100 4200
Wire Wire Line
	4550 4500 5100 4500
Wire Wire Line
	4550 4600 5100 4600
Wire Wire Line
	3300 4600 3300 4700
Wire Wire Line
	3450 4400 3750 4400
Wire Wire Line
	3300 4200 3300 4150
Wire Wire Line
	3150 4400 2800 4400
$Comp
L Device:Crystal_GND24 Y3
U 1 1 5D6EF892
P 3300 4400
F 0 "Y3" H 3300 4850 50  0000 C CNN
F 1 "16MHz" H 3300 4950 50  0000 C CNN
F 2 "flight-computer:Crystal_SMD_2520-4Pin_2.5x2.0mm" H 3300 4400 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/15dc/0900766b815dc75d.pdf" H 3300 4400 50  0001 C CNN
F 4 "0.651" H 3300 4400 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/crystal-units/1442292/" H 3300 4400 50  0001 C CNN "Purchase link"
F 6 "10" H 3300 4400 50  0001 C CNN "min_quantity"
	1    3300 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 4150 3550 4700
Wire Wire Line
	3300 4700 3550 4700
Wire Wire Line
	3300 4150 3550 4150
Wire Wire Line
	7100 4100 7650 4100
Text HLabel 4550 3400 0    50   BiDi ~ 0
MCU_PA05
Wire Wire Line
	5100 3400 4550 3400
Wire Wire Line
	5100 3300 4550 3300
Text HLabel 4550 3300 0    50   BiDi ~ 0
MCU_PA04
Wire Wire Line
	5100 4100 4550 4100
Wire Wire Line
	5100 4200 4550 4200
Text HLabel 4550 4100 0    50   BiDi ~ 0
MCU_PA12
Text HLabel 4550 4200 0    50   BiDi ~ 0
MCU_PA13
Wire Wire Line
	7100 4400 7650 4400
Wire Wire Line
	7100 5000 7650 5000
Text HLabel 7650 5000 2    50   Input ~ 0
MCU_PB17
Wire Wire Line
	5100 3000 4550 3000
Text HLabel 4550 3000 0    50   Input ~ 0
MCU_PA01
Wire Wire Line
	5100 3200 4550 3200
Text HLabel 4550 3200 0    50   Input ~ 0
MCU_PA03
NoConn ~ 7100 5400
NoConn ~ 7100 5300
Wire Wire Line
	7100 4300 7650 4300
NoConn ~ 5100 5500
Text HLabel 7650 4300 2    50   Input ~ 0
MCU_PB10
Text HLabel 7650 4400 2    50   Input ~ 0
MCU_PB11
Text HLabel 7650 4100 2    50   Input ~ 0
MCU_PB08
Text HLabel 7650 4500 2    50   Output ~ 0
MCU_MOSI1
Text HLabel 7650 4600 2    50   Output ~ 0
MCU_SCLK1
NoConn ~ 7100 3800
NoConn ~ 7100 3700
NoConn ~ 7100 4000
NoConn ~ 7100 3900
Wire Notes Line
	9550 4500 11050 4500
$Comp
L flight-computer:W25Q64JVSSIM U11
U 1 1 5D850B8A
P 8300 2650
F 0 "U11" H 8575 3375 50  0000 C CNN
F 1 "W25Q64JVSSIM" H 8575 3284 50  0000 C CNN
F 2 "Package_SO:SOIC-8_5.23x5.23mm_P1.27mm" H 8300 2650 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/1703/0900766b81703f87.pdf" H 8300 2650 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/flash-memory/1882666/" H 8300 2650 50  0001 C CNN "Purchase link"
F 5 "0.718" H 8300 2650 50  0001 C CNN "Cost"
F 6 "10" H 8300 2650 50  0001 C CNN "min_quantity"
	1    8300 2650
	1    0    0    -1  
$EndComp
NoConn ~ 5100 3600
NoConn ~ 5100 3500
Text HLabel 4550 4700 0    50   Input ~ 0
MCU_PA18
Wire Wire Line
	4550 4700 5100 4700
Text HLabel 4550 4800 0    50   Input ~ 0
MCU_PA19
Wire Wire Line
	4550 4800 5100 4800
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5D96BBFC
P 950 6800
F 0 "J5" H 868 7117 50  0000 C CNN
F 1 "Conn_01x04" H 868 7026 50  0000 C CNN
F 2 "flight-computer:NS-Tech_Grove_1x04_P2mm_Vertical" H 950 6800 50  0001 C CNN
F 3 "~" H 950 6800 50  0001 C CNN
	1    950  6800
	-1   0    0    -1  
$EndComp
$Comp
L flight-computer:ATSAMD21J18A-AU U7
U 1 1 5D8A9F24
P 6100 4400
F 0 "U7" H 6100 2411 50  0000 C CNN
F 1 "ATSAMD21J18A-AU" H 6400 2250 50  0000 C CNN
F 2 "Package_QFP:TQFP-64_10x10mm_P0.5mm" H 7300 6200 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/166e/0900766b8166eb12.pdf" H 6100 4400 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/microcontrollers/1773862/" H 6100 4400 50  0001 C CNN "Purchase link"
F 5 "2" H 6100 4400 50  0001 C CNN "min_quantity"
F 6 "2.54" H 6100 4400 50  0001 C CNN "Cost"
	1    6100 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 6800 1750 6800
Wire Notes Line
	550  7450 2550 7450
Wire Notes Line
	2550 3200 2550 7450
Wire Notes Line
	550  3200 550  7450
Text Label 4550 3700 0    50   ~ 0
SDA_PA08
Text Label 4550 3800 0    50   ~ 0
SCL_PA09
Wire Wire Line
	4550 3700 5100 3700
Wire Wire Line
	4550 3800 5100 3800
Text Label 1750 6800 2    50   ~ 0
SDA_PA08
Text Label 1750 6700 2    50   ~ 0
SCL_PA09
Wire Wire Line
	1150 6700 1750 6700
Wire Wire Line
	2100 6900 2100 6550
Wire Wire Line
	1150 6900 2100 6900
$Comp
L power:+3.3V #PWR0121
U 1 1 5DA417EA
P 2100 6550
F 0 "#PWR0121" H 2100 6400 50  0001 C CNN
F 1 "+3.3V" H 2115 6723 50  0000 C CNN
F 2 "" H 2100 6550 50  0001 C CNN
F 3 "" H 2100 6550 50  0001 C CNN
	1    2100 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 7000 2100 7000
Wire Wire Line
	2100 7000 2100 7150
$Comp
L power:GND #PWR0122
U 1 1 5DA4D92B
P 2100 7150
F 0 "#PWR0122" H 2100 6900 50  0001 C CNN
F 1 "GND" H 2105 6977 50  0000 C CNN
F 2 "" H 2100 7150 50  0001 C CNN
F 3 "" H 2100 7150 50  0001 C CNN
	1    2100 7150
	1    0    0    -1  
$EndComp
$EndSCHEMATC

EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
Title "Pyro drivers"
Date "2019-09-09"
Rev "1.0"
Comp "Imperial College Space Society"
Comment1 "Pyro drivers based on the Telementrum design"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR024
U 1 1 5D69AE81
P 5850 2250
F 0 "#PWR024" H 5850 2000 50  0001 C CNN
F 1 "GND" H 5855 2077 50  0000 C CNN
F 2 "" H 5850 2250 50  0001 C CNN
F 3 "" H 5850 2250 50  0001 C CNN
	1    5850 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2250 5850 2000
Wire Wire Line
	6650 1600 6950 1600
Wire Wire Line
	6950 1900 6950 1600
Wire Wire Line
	6950 2250 6950 2200
$Comp
L power:GND #PWR025
U 1 1 5D6A67BF
P 6950 2250
F 0 "#PWR025" H 6950 2000 50  0001 C CNN
F 1 "GND" H 6955 2077 50  0000 C CNN
F 2 "" H 6950 2250 50  0001 C CNN
F 3 "" H 6950 2250 50  0001 C CNN
	1    6950 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 1600 6150 1600
Wire Wire Line
	5950 1500 6150 1500
Wire Wire Line
	6150 1600 6150 1500
Connection ~ 6150 1600
Wire Wire Line
	6150 1600 6350 1600
Connection ~ 6150 1500
Wire Wire Line
	6150 1500 7450 1500
Connection ~ 6950 1600
Wire Wire Line
	6950 1600 7450 1600
Text HLabel 7450 1600 2    50   Output ~ 0
SENSE_FET_A
Wire Wire Line
	4450 1800 4450 1950
Connection ~ 4450 1800
Wire Wire Line
	4450 1800 3700 1800
$Comp
L power:GND #PWR023
U 1 1 5D6AF664
P 4450 2350
F 0 "#PWR023" H 4450 2100 50  0001 C CNN
F 1 "GND" H 4455 2177 50  0000 C CNN
F 2 "" H 4450 2350 50  0001 C CNN
F 3 "" H 4450 2350 50  0001 C CNN
	1    4450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2250 4450 2350
$Comp
L power:GND #PWR043
U 1 1 5D743B8B
P 5850 3500
F 0 "#PWR043" H 5850 3250 50  0001 C CNN
F 1 "GND" H 5855 3327 50  0000 C CNN
F 2 "" H 5850 3500 50  0001 C CNN
F 3 "" H 5850 3500 50  0001 C CNN
	1    5850 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 2850 6950 2850
Wire Wire Line
	6950 3150 6950 2850
Wire Wire Line
	6950 3500 6950 3450
$Comp
L power:GND #PWR044
U 1 1 5D743BAD
P 6950 3500
F 0 "#PWR044" H 6950 3250 50  0001 C CNN
F 1 "GND" H 6955 3327 50  0000 C CNN
F 2 "" H 6950 3500 50  0001 C CNN
F 3 "" H 6950 3500 50  0001 C CNN
	1    6950 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2850 6150 2850
Wire Wire Line
	5950 2750 6150 2750
Wire Wire Line
	6150 2850 6150 2750
Connection ~ 6150 2850
Wire Wire Line
	6150 2850 6350 2850
Connection ~ 6150 2750
Wire Wire Line
	6150 2750 7450 2750
Connection ~ 6950 2850
Wire Wire Line
	6950 2850 7450 2850
Text HLabel 7450 2850 2    50   Output ~ 0
SENSE_FET_B
Wire Wire Line
	5850 3500 5850 3250
Wire Wire Line
	4450 3050 4450 3200
Connection ~ 4450 3050
Wire Wire Line
	4450 3050 3700 3050
$Comp
L power:GND #PWR042
U 1 1 5D743BCA
P 4450 3600
F 0 "#PWR042" H 4450 3350 50  0001 C CNN
F 1 "GND" H 4455 3427 50  0000 C CNN
F 2 "" H 4450 3600 50  0001 C CNN
F 3 "" H 4450 3600 50  0001 C CNN
	1    4450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 3500 4450 3600
Text Label 7450 1500 2    50   ~ 0
FET_A
Text Label 7450 2750 2    50   ~ 0
FET_B
Wire Wire Line
	4450 1800 5550 1800
Wire Wire Line
	4450 3050 5550 3050
$Comp
L Device:R R13
U 1 1 5D743BD4
P 4450 3350
F 0 "R13" H 4520 3396 50  0000 L CNN
F 1 "3.3K" H 4520 3305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 3350 50  0001 C CNN
F 3 "~" H 4450 3350 50  0001 C CNN
F 4 "0.002" H 4450 3350 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/8306410/" H 4450 3350 50  0001 C CNN "Purchase link"
F 6 "10" H 4450 3350 50  0001 C CNN "min_quantity"
	1    4450 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 5D743BA0
P 6950 3300
F 0 "R16" H 7020 3346 50  0000 L CNN
F 1 "22K" H 7020 3255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6880 3300 50  0001 C CNN
F 3 "~" H 6950 3300 50  0001 C CNN
F 4 "0.028" H 6950 3300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408855/" H 6950 3300 50  0001 C CNN "Purchase link"
F 6 "50" H 6950 3300 50  0001 C CNN "min_quantity"
	1    6950 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5D743B96
P 6500 2850
F 0 "R15" V 6700 2850 50  0000 C CNN
F 1 "120K" V 6600 2850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6430 2850 50  0001 C CNN
F 3 "~" H 6500 2850 50  0001 C CNN
F 4 "0.035" H 6500 2850 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6789715/" H 6500 2850 50  0001 C CNN "Purchase link"
F 6 "50" H 6500 2850 50  0001 C CNN "min_quantity"
	1    6500 2850
	0    1    1    0   
$EndComp
$Comp
L flight-computer:Si7232DN U?
U 2 1 5D743B81
P 5850 2600
AR Path="/5D743B81" Ref="U?"  Part="1" 
AR Path="/5D6468D5/5D743B81" Ref="U6"  Part="2" 
F 0 "U6" H 5956 2146 50  0000 L CNN
F 1 "Si7232DN" H 5956 2055 50  0000 L CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Dual" H 5700 2850 50  0001 C CNN
F 3 "https://www.vishay.com/docs/68986/si7232dn.pdf" H 5850 2600 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/mosfets/8181396/" H 5850 2600 50  0001 C CNN "Purchase link"
F 5 "0.729" H 5850 2600 50  0001 C CNN "Cost"
F 6 "20" H 5850 2600 50  0001 C CNN "min_quantity"
	2    5850 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D6AFE1F
P 4450 2100
F 0 "R3" H 4520 2146 50  0000 L CNN
F 1 "3.3K" H 4520 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 2100 50  0001 C CNN
F 3 "~" H 4450 2100 50  0001 C CNN
F 4 "0.002" H 4450 2100 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/8306410/" H 4450 2100 50  0001 C CNN "Purchase link"
F 6 "10" H 4450 2100 50  0001 C CNN "min_quantity"
	1    4450 2100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5D6A6316
P 6950 2050
F 0 "R6" H 7020 2096 50  0000 L CNN
F 1 "22K" H 7020 2005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6880 2050 50  0001 C CNN
F 3 "~" H 6950 2050 50  0001 C CNN
F 4 "0.028" H 6950 2050 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408855/" H 6950 2050 50  0001 C CNN "Purchase link"
F 6 "50" H 6950 2050 50  0001 C CNN "min_quantity"
	1    6950 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5D6A50BE
P 6500 1600
F 0 "R5" V 6700 1600 50  0000 C CNN
F 1 "120K" V 6600 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6430 1600 50  0001 C CNN
F 3 "~" H 6500 1600 50  0001 C CNN
F 4 "0.035" H 6500 1600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6789715/" H 6500 1600 50  0001 C CNN "Purchase link"
F 6 "50" H 6500 1600 50  0001 C CNN "min_quantity"
	1    6500 1600
	0    1    1    0   
$EndComp
$Comp
L flight-computer:Si7232DN U6
U 1 1 5D696EFB
P 5850 1350
AR Path="/5D696EFB" Ref="U6"  Part="1" 
AR Path="/5D6468D5/5D696EFB" Ref="U6"  Part="1" 
F 0 "U6" H 5956 896 50  0000 L CNN
F 1 "Si7232DN" H 5956 805 50  0000 L CNN
F 2 "Package_SO:Vishay_PowerPAK_1212-8_Dual" H 5700 1600 50  0001 C CNN
F 3 "https://www.vishay.com/docs/68986/si7232dn.pdf" H 5850 1350 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/mosfets/8181396/" H 5850 1350 50  0001 C CNN "Purchase link"
F 5 "0.729" H 5850 1350 50  0001 C CNN "Cost"
F 6 "20" H 5850 1350 50  0001 C CNN "min_quantity"
	1    5850 1350
	1    0    0    -1  
$EndComp
Text Label 10050 3050 2    50   ~ 0
FET_A
Wire Wire Line
	10050 3250 9750 3250
Text Notes 8850 2350 0    50   ~ 0
Goes to a Double Pole Single Throw switch\n
Wire Wire Line
	9750 3150 10450 3150
Text Label 10050 3250 2    50   ~ 0
FET_B
Wire Wire Line
	9750 3050 10050 3050
Wire Wire Line
	10450 3350 10450 3150
Wire Wire Line
	9750 3350 10450 3350
Wire Wire Line
	10450 3150 10450 3000
$Comp
L power:Vdrive #PWR0112
U 1 1 5D7E2F36
P 10450 3000
F 0 "#PWR0112" H 10250 2850 50  0001 C CNN
F 1 "Vdrive" H 10467 3173 50  0000 C CNN
F 2 "" H 10450 3000 50  0001 C CNN
F 3 "" H 10450 3000 50  0001 C CNN
	1    10450 3000
	1    0    0    -1  
$EndComp
Text HLabel 3700 3050 0    50   Output ~ 0
FIRE_B
Text HLabel 3700 1800 0    50   Output ~ 0
FIRE_A
Connection ~ 10450 3150
$Comp
L Connector:Screw_Terminal_01x04 J3
U 1 1 5D9DD6B6
P 9550 3250
F 0 "J3" H 9468 2825 50  0000 C CNN
F 1 "Screw_Terminal_01x04" H 9468 2916 50  0000 C CNN
F 2 "flight-computer:TerminalBlock_TE_282834-4_1x04_P2.54mm_Horizontal" H 9550 3250 50  0001 C CNN
F 3 "~" H 9550 3250 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/pcb-terminal-blocks/9097615/" H 9550 3250 50  0001 C CNN "Purchase link"
F 5 "2.45" H 9550 3250 50  0001 C CNN "Cost"
F 6 "1" H 9550 3250 50  0001 C CNN "min_quantity"
	1    9550 3250
	-1   0    0    1   
$EndComp
$EndSCHEMATC

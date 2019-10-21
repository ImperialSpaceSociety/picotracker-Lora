EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Pico lora tracker"
Date "2019-10-21"
Rev "1.0"
Comp "Imperial College Space Society"
Comment1 "Based on the Picotracker MK II and Project mach one flight computer"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:CMWX1ZZABZ-078 U?
U 1 1 5DC84013
P 6250 3900
AR Path="/5D5B15F7/5DC84013" Ref="U?"  Part="1" 
AR Path="/5DC84013" Ref="U3"  Part="1" 
F 0 "U3" H 5550 5500 50  0000 C CNN
F 1 "CMWX1ZZABZ-078" H 5550 5350 50  0000 C CNN
F 2 "RF_Module:CMWX1ZZABZ" H 6250 3900 50  0001 C CNN
F 3 "https://wireless.murata.com/RFM/data/type_abz.pdf" H 8700 2400 50  0001 C CNN
	1    6250 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
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
	7150 5200 7550 5200
$Comp
L Connector:Conn_Coaxial J?
U 1 1 5DC84021
P 8750 5200
AR Path="/5D5B15F7/5DC84021" Ref="J?"  Part="1" 
AR Path="/5DC84021" Ref="J4"  Part="1" 
F 0 "J4" H 8850 5175 50  0000 L CNN
F 1 "Conn_Coaxial" H 8850 5084 50  0000 L CNN
F 2 "" H 8750 5200 50  0001 C CNN
F 3 " ~" H 8750 5200 50  0001 C CNN
	1    8750 5200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC84027
P 8750 5700
AR Path="/5D5B15F7/5DC84027" Ref="#PWR?"  Part="1" 
AR Path="/5DC84027" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 8750 5450 50  0001 C CNN
F 1 "GND" H 8755 5527 50  0000 C CNN
F 2 "" H 8750 5700 50  0001 C CNN
F 3 "" H 8750 5700 50  0001 C CNN
	1    8750 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 5700 8750 5400
Wire Wire Line
	5350 5200 5000 5200
Wire Wire Line
	5000 5200 5000 5300
$Comp
L power:GND #PWR?
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
$Comp
L Device:R R?
U 1 1 5DC84036
P 5000 5450
AR Path="/5D5B15F7/5DC84036" Ref="R?"  Part="1" 
AR Path="/5DC84036" Ref="R3"  Part="1" 
F 0 "R3" H 5070 5496 50  0000 L CNN
F 1 "10K 0402" H 5070 5405 50  0000 L CNN
F 2 "" V 4930 5450 50  0001 C CNN
F 3 "~" H 5000 5450 50  0001 C CNN
	1    5000 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 5600 5000 5750
Wire Wire Line
	1350 1550 1750 1550
Wire Wire Line
	1750 1550 1750 1250
$Comp
L power:+3.3V #PWR?
U 1 1 5DC8403F
P 1750 1250
AR Path="/5D5B15F7/5DC8403F" Ref="#PWR?"  Part="1" 
AR Path="/5DC8403F" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 1750 1100 50  0001 C CNN
F 1 "+3.3V" H 1765 1423 50  0000 C CNN
F 2 "" H 1750 1250 50  0001 C CNN
F 3 "" H 1750 1250 50  0001 C CNN
	1    1750 1250
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J?
U 1 1 5DC84045
P 1150 1750
AR Path="/5D5B15F7/5DC84045" Ref="J?"  Part="1" 
AR Path="/5DC84045" Ref="J1"  Part="1" 
F 0 "J1" H 1068 2167 50  0000 C CNN
F 1 "Conn_01x06" H 1068 2076 50  0000 C CNN
F 2 "" H 1150 1750 50  0001 C CNN
F 3 "~" H 1150 1750 50  0001 C CNN
	1    1150 1750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5350 4000 4900 4000
Text Label 4900 4000 0    50   ~ 0
SWDIO
Wire Wire Line
	1350 1650 1650 1650
Wire Wire Line
	1350 1750 1750 1750
Wire Wire Line
	1750 1750 1750 2250
Wire Wire Line
	1350 1850 1650 1850
NoConn ~ 1350 2050
Text Label 4900 4100 0    50   ~ 0
SWCLK
Wire Wire Line
	4900 4100 5350 4100
Text Label 1650 1650 2    50   ~ 0
SWCLK
Text Label 1650 1850 2    50   ~ 0
SWDIO
$Comp
L power:GND #PWR?
U 1 1 5DC84056
P 1750 2250
AR Path="/5D5B15F7/5DC84056" Ref="#PWR?"  Part="1" 
AR Path="/5DC84056" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 1750 2000 50  0001 C CNN
F 1 "GND" H 1755 2077 50  0000 C CNN
F 2 "" H 1750 2250 50  0001 C CNN
F 3 "" H 1750 2250 50  0001 C CNN
	1    1750 2250
	1    0    0    -1  
$EndComp
Wire Notes Line
	550  700  550  3050
Wire Notes Line
	550  3050 2500 3050
Wire Notes Line
	2500 3050 2500 650 
Wire Notes Line
	2500 650  550  650 
Text Notes 700  2900 0    50   ~ 0
Debugging and programming\ninterface
Wire Wire Line
	1350 1950 1650 1950
Text Label 1650 1950 2    50   ~ 0
RESET
Wire Wire Line
	5350 4300 4550 4300
Text Label 4250 4300 0    50   ~ 0
RESET
Wire Wire Line
	4550 4300 4550 4550
Connection ~ 4550 4300
Wire Wire Line
	4550 4300 4250 4300
$Comp
L power:GND #PWR?
U 1 1 5DC84068
P 4550 4900
AR Path="/5D5B15F7/5DC84068" Ref="#PWR?"  Part="1" 
AR Path="/5DC84068" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 4550 4650 50  0001 C CNN
F 1 "GND" H 4555 4727 50  0000 C CNN
F 2 "" H 4550 4900 50  0001 C CNN
F 3 "" H 4550 4900 50  0001 C CNN
	1    4550 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC8406E
P 4550 4650
AR Path="/5D5B15F7/5DC8406E" Ref="C?"  Part="1" 
AR Path="/5DC8406E" Ref="C1"  Part="1" 
F 0 "C1" H 4642 4696 50  0000 L CNN
F 1 "0.1uF 0402" H 4642 4605 50  0000 L CNN
F 2 "" H 4550 4650 50  0001 C CNN
F 3 "~" H 4550 4650 50  0001 C CNN
	1    4550 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 4750 4550 4900
Wire Wire Line
	6150 1350 6150 2250
Wire Wire Line
	6250 2400 6250 2250
Wire Wire Line
	6250 2250 6150 2250
Connection ~ 6150 2250
Wire Wire Line
	6150 2250 6150 2400
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
$Comp
L Device:C_Small C?
U 1 1 5DC84080
P 6450 1550
AR Path="/5D5B15F7/5DC84080" Ref="C?"  Part="1" 
AR Path="/5DC84080" Ref="C5"  Part="1" 
F 0 "C5" H 6542 1596 50  0000 L CNN
F 1 "0.1uF 0402" H 6542 1505 50  0000 L CNN
F 2 "" H 6450 1550 50  0001 C CNN
F 3 "~" H 6450 1550 50  0001 C CNN
	1    6450 1550
	1    0    0    -1  
$EndComp
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
L power:+3.3V #PWR?
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
$Comp
L Device:C_Small C?
U 1 1 5DC84094
P 7200 1550
AR Path="/5D5B15F7/5DC84094" Ref="C?"  Part="1" 
AR Path="/5DC84094" Ref="C7"  Part="1" 
F 0 "C7" H 7292 1596 50  0000 L CNN
F 1 "1uF 0603" H 7292 1505 50  0000 L CNN
F 2 "" H 7200 1550 50  0001 C CNN
F 3 "~" H 7200 1550 50  0001 C CNN
	1    7200 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1650 7200 1700
$Comp
L Device:C_Small C?
U 1 1 5DC8409B
P 7900 1550
AR Path="/5D5B15F7/5DC8409B" Ref="C?"  Part="1" 
AR Path="/5DC8409B" Ref="C10"  Part="1" 
F 0 "C10" H 7992 1596 50  0000 L CNN
F 1 "10uF 0603" H 7992 1505 50  0000 L CNN
F 2 "" H 7900 1550 50  0001 C CNN
F 3 "~" H 7900 1550 50  0001 C CNN
	1    7900 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 1650 7900 1700
$Comp
L power:GND #PWR?
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
Wire Wire Line
	5450 1350 5450 1450
Connection ~ 5450 1350
Wire Wire Line
	5450 1700 4750 1700
Wire Wire Line
	5450 1350 4750 1350
Connection ~ 4750 1350
Wire Wire Line
	4750 1350 4750 1450
$Comp
L power:+3.3V #PWR?
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
L Device:C_Small C?
U 1 1 5DC840B7
P 5450 1550
AR Path="/5D5B15F7/5DC840B7" Ref="C?"  Part="1" 
AR Path="/5DC840B7" Ref="C3"  Part="1" 
F 0 "C3" H 5358 1596 50  0000 R CNN
F 1 "0.1uF 0402" H 5358 1505 50  0000 R CNN
F 2 "" H 5450 1550 50  0001 C CNN
F 3 "~" H 5450 1550 50  0001 C CNN
	1    5450 1550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5450 1650 5450 1700
$Comp
L Device:C_Small C?
U 1 1 5DC840BE
P 4750 1550
AR Path="/5D5B15F7/5DC840BE" Ref="C?"  Part="1" 
AR Path="/5DC840BE" Ref="C2"  Part="1" 
F 0 "C2" H 4842 1596 50  0000 L CNN
F 1 "10uF 0603" H 4842 1505 50  0000 L CNN
F 2 "" H 4750 1550 50  0001 C CNN
F 3 "~" H 4750 1550 50  0001 C CNN
	1    4750 1550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 1650 4750 1700
$Comp
L power:GND #PWR?
U 1 1 5DC840C5
P 4750 1850
AR Path="/5D5B15F7/5DC840C5" Ref="#PWR?"  Part="1" 
AR Path="/5DC840C5" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 4750 1600 50  0001 C CNN
F 1 "GND" H 4755 1677 50  0000 C CNN
F 2 "" H 4750 1850 50  0001 C CNN
F 3 "" H 4750 1850 50  0001 C CNN
	1    4750 1850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 1850 4750 1700
Connection ~ 4750 1700
Wire Wire Line
	6050 1350 6050 2400
Wire Wire Line
	5450 1350 6050 1350
Wire Wire Line
	6450 2400 6450 2250
Wire Wire Line
	6450 2250 6900 2250
Text Label 6900 2250 2    50   ~ 0
VDD_TCXO
Text Label 4900 3900 0    50   ~ 0
VDD_TCXO
Wire Wire Line
	5350 3900 4900 3900
Wire Wire Line
	7550 5200 7550 5400
Connection ~ 7550 5200
Wire Wire Line
	7550 5200 7650 5200
$Comp
L power:GND #PWR?
U 1 1 5DC840D7
P 7550 5750
AR Path="/5D5B15F7/5DC840D7" Ref="#PWR?"  Part="1" 
AR Path="/5DC840D7" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 7550 5500 50  0001 C CNN
F 1 "GND" H 7555 5577 50  0000 C CNN
F 2 "" H 7550 5750 50  0001 C CNN
F 3 "" H 7550 5750 50  0001 C CNN
	1    7550 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 5200 8100 5400
$Comp
L power:GND #PWR?
U 1 1 5DC840DE
P 8100 5750
AR Path="/5D5B15F7/5DC840DE" Ref="#PWR?"  Part="1" 
AR Path="/5DC840DE" Ref="#PWR0112"  Part="1" 
F 0 "#PWR0112" H 8100 5500 50  0001 C CNN
F 1 "GND" H 8105 5577 50  0000 C CNN
F 2 "" H 8100 5750 50  0001 C CNN
F 3 "" H 8100 5750 50  0001 C CNN
	1    8100 5750
	1    0    0    -1  
$EndComp
Connection ~ 8100 5200
Wire Wire Line
	8100 5200 8550 5200
$Comp
L Device:C_Small C?
U 1 1 5DC840E6
P 7550 5500
AR Path="/5D5B15F7/5DC840E6" Ref="C?"  Part="1" 
AR Path="/5DC840E6" Ref="C9"  Part="1" 
F 0 "C9" H 7642 5546 50  0000 L CNN
F 1 "NF 0603" H 7642 5455 50  0000 L CNN
F 2 "" H 7550 5500 50  0001 C CNN
F 3 "~" H 7550 5500 50  0001 C CNN
	1    7550 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 5600 7550 5750
$Comp
L Device:C_Small C?
U 1 1 5DC840ED
P 8100 5500
AR Path="/5D5B15F7/5DC840ED" Ref="C?"  Part="1" 
AR Path="/5DC840ED" Ref="C11"  Part="1" 
F 0 "C11" H 8192 5546 50  0000 L CNN
F 1 "NF 0603" H 8192 5455 50  0000 L CNN
F 2 "" H 8100 5500 50  0001 C CNN
F 3 "~" H 8100 5500 50  0001 C CNN
	1    8100 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 5600 8100 5750
$Comp
L Device:L L?
U 1 1 5DC840F4
P 7800 5200
AR Path="/5D5B15F7/5DC840F4" Ref="L?"  Part="1" 
AR Path="/5DC840F4" Ref="L1"  Part="1" 
F 0 "L1" V 7619 5200 50  0000 C CNN
F 1 "NF 0603" V 7710 5200 50  0000 C CNN
F 2 "" H 7800 5200 50  0001 C CNN
F 3 "~" H 7800 5200 50  0001 C CNN
	1    7800 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 5200 8100 5200
Wire Wire Line
	7150 3400 7800 3400
Wire Wire Line
	7150 3500 7800 3500
Text HLabel 7800 3400 2    50   Input ~ 0
I2C1_SCL
Text HLabel 7800 3500 2    50   Input ~ 0
I2C1_SDA
$Comp
L power:GND #PWR?
U 1 1 5DC840FF
P 14150 4200
AR Path="/5D5B1586/5DC840FF" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC840FF" Ref="#PWR?"  Part="1" 
AR Path="/5DC840FF" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 14150 3950 50  0001 C CNN
F 1 "GND" H 14155 4027 50  0000 C CNN
F 2 "" H 14150 4200 50  0001 C CNN
F 3 "" H 14150 4200 50  0001 C CNN
	1    14150 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC84105
P 13550 4200
AR Path="/5D5B1586/5DC84105" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84105" Ref="#PWR?"  Part="1" 
AR Path="/5DC84105" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 13550 3950 50  0001 C CNN
F 1 "GND" H 13555 4027 50  0000 C CNN
F 2 "" H 13550 4200 50  0001 C CNN
F 3 "" H 13550 4200 50  0001 C CNN
	1    13550 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	14150 4050 14150 4200
Wire Wire Line
	13750 3850 13550 3850
Wire Wire Line
	13550 3850 13550 4200
Wire Wire Line
	13750 3650 13550 3650
Wire Wire Line
	13750 3750 13400 3750
$Comp
L power:GND #PWR?
U 1 1 5DC84110
P 14600 3350
AR Path="/5D5B1586/5DC84110" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84110" Ref="#PWR?"  Part="1" 
AR Path="/5DC84110" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 14600 3100 50  0001 C CNN
F 1 "GND" H 14605 3177 50  0000 C CNN
F 2 "" H 14600 3350 50  0001 C CNN
F 3 "" H 14600 3350 50  0001 C CNN
	1    14600 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	14150 3050 14150 3100
Wire Wire Line
	14600 3300 14600 3350
Wire Wire Line
	14600 3100 14150 3100
Connection ~ 14150 3100
Wire Wire Line
	14150 3100 14150 3250
Wire Wire Line
	13750 3450 13650 3450
Wire Wire Line
	13650 3450 13650 3100
Wire Wire Line
	13650 3100 14150 3100
NoConn ~ 13750 3550
Text HLabel 11800 2700 0    50   BiDi ~ 0
SENS_SCL
Text HLabel 11800 2450 0    50   BiDi ~ 0
SENS_SDA
$Comp
L power:+3.3V #PWR?
U 1 1 5DC84121
P 14150 3050
AR Path="/5D5B1586/5DC84121" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84121" Ref="#PWR?"  Part="1" 
AR Path="/5DC84121" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 14150 2900 50  0001 C CNN
F 1 "+3.3V" H 14165 3223 50  0000 C CNN
F 2 "" H 14150 3050 50  0001 C CNN
F 3 "" H 14150 3050 50  0001 C CNN
	1    14150 3050
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Pressure:MS5607-02BA U?
U 1 1 5DC8412A
P 14150 3650
AR Path="/5D5B1586/5DC8412A" Ref="U?"  Part="1" 
AR Path="/5D5B15F7/5DC8412A" Ref="U?"  Part="1" 
AR Path="/5DC8412A" Ref="U6"  Part="1" 
F 0 "U6" H 14480 3696 50  0000 L CNN
F 1 "MS5607-02BA" H 14480 3605 50  0000 L CNN
F 2 "Package_LGA:LGA-8_3x5mm_P1.25mm" H 14150 3650 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5607-02BA03%7FB2%7Fpdf%7FEnglish%7FENG_DS_MS5607-02BA03_B2.pdf%7FCAT-BLPS0035" H 14150 3650 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/absolute-pressure-sensor-ics/8937095/" H 14150 3650 50  0001 C CNN "Purchase link"
F 5 "2.86" H 14150 3650 50  0001 C CNN "Cost"
F 6 "1" H 14150 3650 50  0001 C CNN "min_quantity"
	1    14150 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC84133
P 14600 3200
AR Path="/5D5B1586/5DC84133" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC84133" Ref="C?"  Part="1" 
AR Path="/5DC84133" Ref="C14"  Part="1" 
F 0 "C14" H 14692 3246 50  0000 L CNN
F 1 "220nF" H 14692 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 14600 3200 50  0001 C CNN
F 3 "~" H 14600 3200 50  0001 C CNN
F 4 "0.003" H 14600 3200 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/0391135/" H 14600 3200 50  0001 C CNN "Purchase link"
F 6 "50" H 14600 3200 50  0001 C CNN "min_quantity"
	1    14600 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	13400 2700 13400 3750
Wire Wire Line
	13550 2450 13550 3650
Wire Wire Line
	12200 1400 12200 1750
Connection ~ 12200 2450
Wire Wire Line
	12200 2450 13550 2450
Wire Wire Line
	12500 2700 12500 2050
Connection ~ 12500 2700
Wire Wire Line
	12500 2700 13400 2700
$Comp
L power:+3.3V #PWR?
U 1 1 5DC84141
P 12200 1400
AR Path="/5D5B1586/5DC84141" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84141" Ref="#PWR?"  Part="1" 
AR Path="/5DC84141" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 12200 1250 50  0001 C CNN
F 1 "+3.3V" H 12215 1573 50  0000 C CNN
F 2 "" H 12200 1400 50  0001 C CNN
F 3 "" H 12200 1400 50  0001 C CNN
	1    12200 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DC84147
P 12500 1400
AR Path="/5D5B1586/5DC84147" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84147" Ref="#PWR?"  Part="1" 
AR Path="/5DC84147" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 12500 1250 50  0001 C CNN
F 1 "+3.3V" H 12515 1573 50  0000 C CNN
F 2 "" H 12500 1400 50  0001 C CNN
F 3 "" H 12500 1400 50  0001 C CNN
	1    12500 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC84150
P 12200 1900
AR Path="/5D5B1586/5DC84150" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC84150" Ref="R?"  Part="1" 
AR Path="/5DC84150" Ref="R4"  Part="1" 
F 0 "R4" H 12270 1946 50  0000 L CNN
F 1 "4.7K" H 12270 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 12130 1900 50  0001 C CNN
F 3 "~" H 12200 1900 50  0001 C CNN
F 4 "0.01" H 12200 1900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408877/" H 12200 1900 50  0001 C CNN "Purchase link"
F 6 "50" H 12200 1900 50  0001 C CNN "min_quantity"
	1    12200 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	12200 2050 12200 2450
$Comp
L Device:R R?
U 1 1 5DC8415A
P 12500 1900
AR Path="/5D5B1586/5DC8415A" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC8415A" Ref="R?"  Part="1" 
AR Path="/5DC8415A" Ref="R5"  Part="1" 
F 0 "R5" H 12570 1946 50  0000 L CNN
F 1 "4.7K" H 12570 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 12430 1900 50  0001 C CNN
F 3 "~" H 12500 1900 50  0001 C CNN
F 4 "0.01" H 12500 1900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/7408877/" H 12500 1900 50  0001 C CNN "Purchase link"
F 6 "50" H 12500 1900 50  0001 C CNN "min_quantity"
	1    12500 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	12500 1750 12500 1400
Wire Wire Line
	11800 2700 12500 2700
Wire Wire Line
	11800 2450 12200 2450
Text HLabel 13100 8300 2    50   Output ~ 0
GPS_1PPS
Text Notes 11400 9650 0    50   ~ 0
http://www.explorelabs.com/blog/designing-a-gps-receiver/#ref-ublox-datasheet\n\nImportant info on why we use the components\n
$Comp
L power:GND #PWR?
U 1 1 5DC84165
P 12350 8850
AR Path="/5D5B165E/5DC84165" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84165" Ref="#PWR?"  Part="1" 
AR Path="/5DC84165" Ref="#PWR0119"  Part="1" 
F 0 "#PWR0119" H 12350 8600 50  0001 C CNN
F 1 "GND" H 12355 8677 50  0000 C CNN
F 2 "" H 12350 8850 50  0001 C CNN
F 3 "" H 12350 8850 50  0001 C CNN
	1    12350 8850
	1    0    0    -1  
$EndComp
Text HLabel 11450 7700 0    50   Output ~ 0
GPS_TXD
Text HLabel 11450 7600 0    50   Input ~ 0
GPS_RXD
Text HLabel 11450 8000 0    50   BiDi ~ 0
GPS_SCL
Text HLabel 11450 7900 0    50   BiDi ~ 0
GPS_SDA
Text HLabel 11450 8300 0    50   Input ~ 0
GPS_NSAFEBOOT
Text HLabel 11450 8400 0    50   Input ~ 0
GPS_NRES
$Comp
L Connector:Conn_Coaxial J?
U 1 1 5DC84174
P 14750 8000
AR Path="/5D5B17D8/5DC84174" Ref="J?"  Part="1" 
AR Path="/5D5B165E/5DC84174" Ref="J?"  Part="1" 
AR Path="/5D5B15F7/5DC84174" Ref="J?"  Part="1" 
AR Path="/5DC84174" Ref="J5"  Part="1" 
F 0 "J5" H 14850 7975 50  0000 L CNN
F 1 "Conn_Coaxial" H 14850 7884 50  0000 L CNN
F 2 "Connector_Coaxial:U.FL_Hirose_U.FL-R-SMT-1_Vertical" H 14750 8000 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/185/U.FL_catalog-939761.pdf" H 14750 8000 50  0001 C CNN
F 4 "0.617" H 14750 8000 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/coaxial-plugs-sockets/7025425/" H 14750 8000 50  0001 C CNN "Purchase link"
F 6 "10" H 14750 8000 50  0001 C CNN "min_quantity"
	1    14750 8000
	1    0    0    -1  
$EndComp
Wire Wire Line
	14750 8750 14750 8200
$Comp
L power:GND #PWR?
U 1 1 5DC8417B
P 14750 8750
AR Path="/5D5B165E/5DC8417B" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC8417B" Ref="#PWR?"  Part="1" 
AR Path="/5DC8417B" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 14750 8500 50  0001 C CNN
F 1 "GND" H 14755 8577 50  0000 C CNN
F 2 "" H 14750 8750 50  0001 C CNN
F 3 "" H 14750 8750 50  0001 C CNN
	1    14750 8750
	1    0    0    -1  
$EndComp
Connection ~ 13950 8000
Wire Wire Line
	13950 8000 14550 8000
$Comp
L Device:L L?
U 1 1 5DC84186
P 13950 7600
AR Path="/5D5B165E/5DC84186" Ref="L?"  Part="1" 
AR Path="/5D5B15F7/5DC84186" Ref="L?"  Part="1" 
AR Path="/5DC84186" Ref="L2"  Part="1" 
F 0 "L2" H 14003 7646 50  0000 L CNN
F 1 "27nH" H 14003 7555 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 13950 7600 50  0001 C CNN
F 3 "~" H 13950 7600 50  0001 C CNN
F 4 "0.08" H 13950 7600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/wire-wound-surface-mount-inductors/7254923/" H 13950 7600 50  0001 C CNN "Purchase link"
F 6 "10" H 13950 7600 50  0001 C CNN "min_quantity"
	1    13950 7600
	1    0    0    -1  
$EndComp
Wire Wire Line
	13950 7750 13950 8000
Wire Wire Line
	12550 7050 13100 7050
Wire Wire Line
	13950 7050 13950 7450
$Comp
L Device:R R?
U 1 1 5DC84192
P 13250 7050
AR Path="/5D5B165E/5DC84192" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC84192" Ref="R?"  Part="1" 
AR Path="/5DC84192" Ref="R6"  Part="1" 
F 0 "R6" V 13043 7050 50  0000 C CNN
F 1 "10 Ohm" V 13134 7050 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 13180 7050 50  0001 C CNN
F 3 "~" H 13250 7050 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6788703/" H 13250 7050 50  0001 C CNN "Purchase link"
F 5 "50" H 13250 7050 50  0001 C CNN "min_quantity"
F 6 "0.002" H 13250 7050 50  0001 C CNN "Cost"
	1    13250 7050
	0    1    1    0   
$EndComp
Wire Wire Line
	13400 7050 13950 7050
Wire Wire Line
	13950 7050 13950 6450
Connection ~ 13950 7050
$Comp
L power:GND #PWR?
U 1 1 5DC8419B
P 14700 7050
AR Path="/5D5B165E/5DC8419B" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC8419B" Ref="#PWR?"  Part="1" 
AR Path="/5DC8419B" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 14700 6800 50  0001 C CNN
F 1 "GND" H 14705 6877 50  0000 C CNN
F 2 "" H 14700 7050 50  0001 C CNN
F 3 "" H 14700 7050 50  0001 C CNN
	1    14700 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	14700 6450 14700 6600
Wire Wire Line
	13950 6450 14700 6450
$Comp
L Device:C_Small C?
U 1 1 5DC841A6
P 14700 6700
AR Path="/5D5B165E/5DC841A6" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC841A6" Ref="C?"  Part="1" 
AR Path="/5DC841A6" Ref="C15"  Part="1" 
F 0 "C15" H 14792 6746 50  0000 L CNN
F 1 "10nF" H 14792 6655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 14700 6700 50  0001 C CNN
F 3 "~" H 14700 6700 50  0001 C CNN
F 4 "0.031" H 14700 6700 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8391727/" H 14700 6700 50  0001 C CNN "Purchase link"
F 6 "100" H 14700 6700 50  0001 C CNN "min_quantity"
	1    14700 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	14700 6800 14700 7050
Text Notes 13800 9300 0    50   ~ 0
Connected to active antenna, likely 2066400001 \nMolex active antenna. UFL connector\n
Text Notes 11300 5500 0    50   ~ 0
Layout according to MAX-8 / MAX-M8, \nHardware Integration Manual,\nSection 2.4.2 Antenna design with active antenna.
NoConn ~ 11750 8200
Wire Wire Line
	12950 8300 13100 8300
Wire Wire Line
	12550 7300 12550 7050
NoConn ~ 12950 7800
Wire Wire Line
	12950 8000 13950 8000
Wire Wire Line
	12350 8700 12350 8850
Wire Wire Line
	12250 7300 12250 7250
Wire Wire Line
	12150 6600 12150 7300
Connection ~ 12150 6600
Wire Wire Line
	12250 6600 12150 6600
Wire Wire Line
	12150 6050 12150 6600
$Comp
L power:+3.3V #PWR?
U 1 1 5DC841BA
P 12150 6050
AR Path="/5D5B165E/5DC841BA" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC841BA" Ref="#PWR?"  Part="1" 
AR Path="/5DC841BA" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 12150 5900 50  0001 C CNN
F 1 "+3.3V" H 12165 6223 50  0000 C CNN
F 2 "" H 12150 6050 50  0001 C CNN
F 3 "" H 12150 6050 50  0001 C CNN
	1    12150 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	11600 7000 11600 6900
Wire Wire Line
	11950 6900 11950 7000
Wire Wire Line
	11950 6600 11600 6600
Connection ~ 11950 6600
Wire Wire Line
	11950 6700 11950 6600
Wire Wire Line
	11600 6600 11600 6700
Wire Wire Line
	12150 6600 11950 6600
$Comp
L Device:C_Small C?
U 1 1 5DC841CA
P 11600 6800
AR Path="/5D5B17D8/5DC841CA" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5DC841CA" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC841CA" Ref="C?"  Part="1" 
AR Path="/5DC841CA" Ref="C12"  Part="1" 
F 0 "C12" H 11508 6846 50  0000 R CNN
F 1 "100nF" H 11508 6755 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 11600 6800 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 11600 6800 50  0001 C CNN
F 4 "0.01" H 11600 6800 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983251/" H 11600 6800 50  0001 C CNN "Purchase link"
F 6 "50" H 11600 6800 50  0001 C CNN "min_quantity"
	1    11600 6800
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC841D3
P 11950 6800
AR Path="/5D5B17D8/5DC841D3" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5DC841D3" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC841D3" Ref="C?"  Part="1" 
AR Path="/5DC841D3" Ref="C13"  Part="1" 
F 0 "C13" H 11858 6846 50  0000 R CNN
F 1 "10uF" H 11858 6755 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 11950 6800 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 11950 6800 50  0001 C CNN
F 4 "0.07" H 11950 6800 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 11950 6800 50  0001 C CNN "Purchase link"
F 6 "100" H 11950 6800 50  0001 C CNN "min_quantity"
	1    11950 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	11450 8400 11750 8400
Wire Wire Line
	11750 8300 11450 8300
Wire Wire Line
	11450 8000 11750 8000
Wire Wire Line
	11750 7900 11450 7900
Wire Wire Line
	11450 7700 11750 7700
Wire Wire Line
	11750 7600 11450 7600
$Comp
L power:GND #PWR?
U 1 1 5DC841DF
P 11600 7100
AR Path="/5D5B17D8/5DC841DF" Ref="#PWR?"  Part="1" 
AR Path="/5D5B165E/5DC841DF" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC841DF" Ref="#PWR?"  Part="1" 
AR Path="/5DC841DF" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 11600 6850 50  0001 C CNN
F 1 "GND" H 11605 6927 50  0000 C CNN
F 2 "" H 11600 7100 50  0001 C CNN
F 3 "" H 11600 7100 50  0001 C CNN
	1    11600 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	11600 7100 11600 7000
Connection ~ 11600 7000
Wire Wire Line
	11600 7000 11950 7000
Wire Wire Line
	12350 7300 12350 7250
Wire Wire Line
	12350 7250 12250 7250
Connection ~ 12250 7250
Wire Wire Line
	12250 7250 12250 6600
$Comp
L RF_GPS:MAX-M8Q U?
U 1 1 5DC841EF
P 12350 8000
AR Path="/5D5B165E/5DC841EF" Ref="U?"  Part="1" 
AR Path="/5D5B15F7/5DC841EF" Ref="U?"  Part="1" 
AR Path="/5DC841EF" Ref="U5"  Part="1" 
F 0 "U5" H 12350 7211 50  0000 C CNN
F 1 "MAX-M8Q" H 11900 7150 50  0000 C CNN
F 2 "RF_GPS:ublox_MAX" H 12750 7350 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/MAX-M8-FW3_DataSheet_%28UBX-15031506%29.pdf" H 12350 8000 50  0001 C CNN
F 4 "11.99" H 12350 8000 50  0001 C CNN "Cost"
F 5 "https://store.uputronics.com/index.php?route=product/product&product_id=71&search=ublox" H 12350 8000 50  0001 C CNN "Purchase link"
F 6 "1" H 12350 8000 50  0001 C CNN "min_quantity"
	1    12350 8000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 7000 5650 8800
Wire Wire Line
	5650 8800 6050 8800
$Comp
L power:GND #PWR?
U 1 1 5DC841F7
P 2450 9100
AR Path="/5D5B1705/5DC841F7" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC841F7" Ref="#PWR?"  Part="1" 
AR Path="/5DC841F7" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 2450 8850 50  0001 C CNN
F 1 "GND" H 2455 8927 50  0000 C CNN
F 2 "" H 2450 9100 50  0001 C CNN
F 3 "" H 2450 9100 50  0001 C CNN
	1    2450 9100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5DC84200
P 2050 8800
AR Path="/5D5B1705/5DC84200" Ref="J?"  Part="1" 
AR Path="/5D5B15F7/5DC84200" Ref="J?"  Part="1" 
AR Path="/5DC84200" Ref="J3"  Part="1" 
F 0 "J3" H 1968 9017 50  0000 C CNN
F 1 "Conn_01x02" H 1968 8926 50  0000 C CNN
F 2 "Connector_JST:JST_PH_B2B-PH-K_1x02_P2.00mm_Vertical" H 2050 8800 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/1347/0900766b81347511.pdf" H 2050 8800 50  0001 C CNN
F 4 "0.38" H 2050 8800 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/pcb-headers/8201422/" H 2050 8800 50  0001 C CNN "Purchase link"
F 6 "5" H 2050 8800 50  0001 C CNN "min_quantity"
	1    2050 8800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2450 9100 2450 8900
Wire Wire Line
	2450 8900 2250 8900
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5DC84208
P 2700 8800
AR Path="/5D5B1705/5DC84208" Ref="#FLG?"  Part="1" 
AR Path="/5D5B15F7/5DC84208" Ref="#FLG?"  Part="1" 
AR Path="/5DC84208" Ref="#FLG0101"  Part="1" 
F 0 "#FLG0101" H 2700 8875 50  0001 C CNN
F 1 "PWR_FLAG" H 2700 8973 50  0000 C CNN
F 2 "" H 2700 8800 50  0001 C CNN
F 3 "~" H 2700 8800 50  0001 C CNN
	1    2700 8800
	1    0    0    -1  
$EndComp
Connection ~ 5650 8800
Wire Wire Line
	5000 7000 5550 7000
Text Notes 3800 8300 0    50   ~ 0
1A Ideal Diode with Ultra-Low Voltage Drop.\n43mV drop at 500mA draw
$Comp
L flight-computer:DFLS130L D?
U 1 1 5DC84214
P 4850 7000
AR Path="/5D5B1705/5DC84214" Ref="D?"  Part="1" 
AR Path="/5D5B15F7/5DC84214" Ref="D?"  Part="1" 
AR Path="/5DC84214" Ref="D1"  Part="1" 
F 0 "D1" H 4850 6784 50  0000 C CNN
F 1 "DFLS130L" H 4850 6875 50  0000 C CNN
F 2 "Diode_SMD:D_PowerDI-123" H 4850 7000 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30492.pdf" H 4850 7000 50  0001 C CNN
F 4 "0.36" H 4850 7000 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/diodes-inc/dfls130l-7/diode-schottky-30v-1a-powerdi123/dp/1843673?st=DFLS130L" H 4850 7000 50  0001 C CNN "Purchase link"
F 6 "5" H 4850 7000 50  0001 C CNN "min_quantity"
	1    4850 7000
	-1   0    0    1   
$EndComp
$Comp
L Regulator_Linear:LD3985G33R_TSOT23 U?
U 1 1 5DC8421D
P 6650 8900
AR Path="/5D5B1705/5DC8421D" Ref="U?"  Part="1" 
AR Path="/5D5B15F7/5DC8421D" Ref="U?"  Part="1" 
AR Path="/5DC8421D" Ref="U4"  Part="1" 
F 0 "U4" H 6650 9242 50  0000 C CNN
F 1 "LD3985M33R_TSOT23" H 6650 9151 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TSOT-23-5" H 6650 9225 50  0001 C CIN
F 3 "https://docs-emea.rs-online.com/webdocs/13e4/0900766b813e471a.pdf" H 6650 8950 50  0001 C CNN
F 4 "0.472" H 6650 8900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/low-dropout-voltage-regulators/6868802/" H 6650 8900 50  0001 C CNN "Purchase link"
F 6 "5" H 6650 8900 50  0001 C CNN "min_quantity"
	1    6650 8900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC84223
P 4850 9600
AR Path="/5D5B1705/5DC84223" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84223" Ref="#PWR?"  Part="1" 
AR Path="/5DC84223" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 4850 9350 50  0001 C CNN
F 1 "GND" H 4855 9427 50  0000 C CNN
F 2 "" H 4850 9600 50  0001 C CNN
F 3 "" H 4850 9600 50  0001 C CNN
	1    4850 9600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 9200 4850 9600
$Comp
L power:GND #PWR?
U 1 1 5DC8422A
P 6650 9600
AR Path="/5D5B1705/5DC8422A" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC8422A" Ref="#PWR?"  Part="1" 
AR Path="/5DC8422A" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 6650 9350 50  0001 C CNN
F 1 "GND" H 6655 9427 50  0000 C CNN
F 2 "" H 6650 9600 50  0001 C CNN
F 3 "" H 6650 9600 50  0001 C CNN
	1    6650 9600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 9200 6650 9600
$Comp
L Device:C C?
U 1 1 5DC84234
P 7100 9300
AR Path="/5D5B1705/5DC84234" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC84234" Ref="C?"  Part="1" 
AR Path="/5DC84234" Ref="C6"  Part="1" 
F 0 "C6" H 7215 9346 50  0000 L CNN
F 1 "10nF" H 7215 9255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7138 9150 50  0001 C CNN
F 3 "~" H 7100 9300 50  0001 C CNN
F 4 "0.031" H 7100 9300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8391727/" H 7100 9300 50  0001 C CNN "Purchase link"
F 6 "100" H 7100 9300 50  0001 C CNN "min_quantity"
	1    7100 9300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 8900 7100 8900
Wire Wire Line
	7100 8900 7100 9150
$Comp
L power:GND #PWR?
U 1 1 5DC8423C
P 7100 9600
AR Path="/5D5B1705/5DC8423C" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC8423C" Ref="#PWR?"  Part="1" 
AR Path="/5DC8423C" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 7100 9350 50  0001 C CNN
F 1 "GND" H 7105 9427 50  0000 C CNN
F 2 "" H 7100 9600 50  0001 C CNN
F 3 "" H 7100 9600 50  0001 C CNN
	1    7100 9600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 9600 7100 9450
Wire Wire Line
	6350 8900 6150 8900
Wire Wire Line
	6150 8900 6150 8800
Connection ~ 6150 8800
Wire Wire Line
	6150 8800 6350 8800
Wire Wire Line
	8500 8800 8500 8550
$Comp
L power:+3.3V #PWR?
U 1 1 5DC84248
P 8500 8550
AR Path="/5D5B1705/5DC84248" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84248" Ref="#PWR?"  Part="1" 
AR Path="/5DC84248" Ref="#PWR0128"  Part="1" 
F 0 "#PWR0128" H 8500 8400 50  0001 C CNN
F 1 "+3.3V" H 8515 8723 50  0000 C CNN
F 2 "" H 8500 8550 50  0001 C CNN
F 3 "" H 8500 8550 50  0001 C CNN
	1    8500 8550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 8650 4050 8800
$Comp
L Analog_Switch:MAX40200AUK U?
U 1 1 5DC84252
P 4850 8900
AR Path="/5D5B1705/5DC84252" Ref="U?"  Part="1" 
AR Path="/5D5B15F7/5DC84252" Ref="U?"  Part="1" 
AR Path="/5DC84252" Ref="U2"  Part="1" 
F 0 "U2" H 4850 9267 50  0000 C CNN
F 1 "MAX40200AUK" H 4850 9176 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 4850 9400 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX40200.pdf" H 4850 9400 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/node_under_construction/1697573/" H 4850 8900 50  0001 C CNN "Purchase link"
F 5 "0.729" H 4850 8900 50  0001 C CNN "Cost"
F 6 "10" H 4850 8900 50  0001 C CNN "min_quantity"
	1    4850 8900
	1    0    0    -1  
$EndComp
$Comp
L power:Vdrive #PWR?
U 1 1 5DC84258
P 4050 8650
AR Path="/5D5B1705/5DC84258" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84258" Ref="#PWR?"  Part="1" 
AR Path="/5DC84258" Ref="#PWR0129"  Part="1" 
F 0 "#PWR0129" H 3850 8500 50  0001 C CNN
F 1 "Vdrive" H 4067 8823 50  0000 C CNN
F 2 "" H 4050 8650 50  0001 C CNN
F 3 "" H 4050 8650 50  0001 C CNN
	1    4050 8650
	1    0    0    -1  
$EndComp
Connection ~ 4050 8800
Wire Wire Line
	4050 8800 4200 8800
Wire Wire Line
	5250 8800 5650 8800
Wire Wire Line
	4200 8800 4200 9000
Wire Wire Line
	4200 9000 4450 9000
Connection ~ 4200 8800
Wire Wire Line
	4200 8800 4450 8800
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5DC84265
P 5550 7000
AR Path="/5D5B1705/5DC84265" Ref="#FLG?"  Part="1" 
AR Path="/5D5B15F7/5DC84265" Ref="#FLG?"  Part="1" 
AR Path="/5DC84265" Ref="#FLG0102"  Part="1" 
F 0 "#FLG0102" H 5550 7075 50  0001 C CNN
F 1 "PWR_FLAG" H 5550 7173 50  0000 C CNN
F 2 "" H 5550 7000 50  0001 C CNN
F 3 "~" H 5550 7000 50  0001 C CNN
	1    5550 7000
	1    0    0    -1  
$EndComp
Connection ~ 5550 7000
Wire Wire Line
	5550 7000 5650 7000
Connection ~ 7500 8800
Wire Wire Line
	7500 8800 8500 8800
Wire Wire Line
	6950 8800 7500 8800
Wire Wire Line
	7500 9600 7500 9450
$Comp
L power:GND #PWR?
U 1 1 5DC84271
P 7500 9600
AR Path="/5D5B1705/5DC84271" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84271" Ref="#PWR?"  Part="1" 
AR Path="/5DC84271" Ref="#PWR0130"  Part="1" 
F 0 "#PWR0130" H 7500 9350 50  0001 C CNN
F 1 "GND" H 7505 9427 50  0000 C CNN
F 2 "" H 7500 9600 50  0001 C CNN
F 3 "" H 7500 9600 50  0001 C CNN
	1    7500 9600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 8800 7500 9150
$Comp
L Device:C C?
U 1 1 5DC8427B
P 7500 9300
AR Path="/5D5B1705/5DC8427B" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC8427B" Ref="C?"  Part="1" 
AR Path="/5DC8427B" Ref="C8"  Part="1" 
F 0 "C8" H 7615 9346 50  0000 L CNN
F 1 "1uF" H 7615 9255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7538 9150 50  0001 C CNN
F 3 "~" H 7500 9300 50  0001 C CNN
F 4 "0.01" H 7500 9300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/1358359/" H 7500 9300 50  0001 C CNN "Purchase link"
F 6 "250" H 7500 9300 50  0001 C CNN "min_quantity"
	1    7500 9300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 9600 6050 9450
$Comp
L power:GND #PWR?
U 1 1 5DC84282
P 6050 9600
AR Path="/5D5B1705/5DC84282" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC84282" Ref="#PWR?"  Part="1" 
AR Path="/5DC84282" Ref="#PWR0131"  Part="1" 
F 0 "#PWR0131" H 6050 9350 50  0001 C CNN
F 1 "GND" H 6055 9427 50  0000 C CNN
F 2 "" H 6050 9600 50  0001 C CNN
F 3 "" H 6050 9600 50  0001 C CNN
	1    6050 9600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 8800 6050 9150
$Comp
L Device:C C?
U 1 1 5DC8428C
P 6050 9300
AR Path="/5D5B1705/5DC8428C" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC8428C" Ref="C?"  Part="1" 
AR Path="/5DC8428C" Ref="C4"  Part="1" 
F 0 "C4" H 6165 9346 50  0000 L CNN
F 1 "1uF" H 6165 9255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6088 9150 50  0001 C CNN
F 3 "~" H 6050 9300 50  0001 C CNN
F 4 "0.01" H 6050 9300 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/1358359/" H 6050 9300 50  0001 C CNN "Purchase link"
F 6 "250" H 6050 9300 50  0001 C CNN "min_quantity"
	1    6050 9300
	1    0    0    -1  
$EndComp
Connection ~ 6050 8800
Wire Wire Line
	6050 8800 6150 8800
Connection ~ 2700 8800
Wire Wire Line
	2250 8800 2700 8800
Text Notes 7850 9400 0    50   ~ 0
May have to increase \nthe smoothing caps to 10uF \nfor stronger effect.
Text Notes 1700 8450 0    50   ~ 0
3.6V-4.2V Li-po input. Needs to be\nregulated down to 3.3V cmos
Text Notes 6100 8400 0    50   ~ 0
Ultra low drop out voltage regulator.\n140mV drop at max current of 150mA.
Text Notes 6750 10500 0    50   ~ 0
The maximum possible voltage drop(from 3.6V input) due to diode \nand LDO regulator is 173mV, leaving plenty of \nleeway to bring it down to 3.3V CMOS level.
Wire Wire Line
	3550 8800 4050 8800
Connection ~ 3550 8800
Wire Wire Line
	2700 8800 3550 8800
$Comp
L Connector:USB_B_Micro J?
U 1 1 5DC842A0
P 1300 7100
AR Path="/5D5B15F7/5DC842A0" Ref="J?"  Part="1" 
AR Path="/5D5B1705/5DC842A0" Ref="J?"  Part="1" 
AR Path="/5DC842A0" Ref="J2"  Part="1" 
F 0 "J2" H 1357 7567 50  0000 C CNN
F 1 "USB_B_Micro" H 1357 7476 50  0000 C CNN
F 2 "flight-computer:USB_Micro-B_Molex-105017-0001" H 1450 7050 50  0001 C CNN
F 3 "https://www.molex.com/webdocs/datasheets/pdf/en-us/1050170001_IO_CONNECTORS.pdf" H 1450 7050 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/micro-usb-connectors/8486764/?relevancy-data=636F3D3126696E3D4931384E53656172636847656E65726963266C753D656E266D6D3D6D61746368616C6C7061727469616C26706D3D5E5B5C707B4C7D5C707B4E647D2D2C2F255C2E5D2B2426706F3D31333326736E3D592673723D2673743D4B4559574F52445F53494E474C455F414C5048415F4E554D455249432673633D592677633D4E4F4E45267573743D3130353031372D30303031267374613D3130353031372D3030303126&searchHistory=%7B%22enabled%22%3Atrue%7D" H 1300 7100 50  0001 C CNN "Purchase link"
F 5 "0.694" H 1300 7100 50  0001 C CNN "Cost"
F 6 "5" H 1300 7100 50  0001 C CNN "min_quantity"
	1    1300 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 7650 1300 7800
Connection ~ 1300 7650
Wire Wire Line
	1200 7650 1300 7650
Wire Wire Line
	1200 7500 1200 7650
$Comp
L power:GND #PWR?
U 1 1 5DC842AA
P 1300 7800
AR Path="/5D5B15F7/5DC842AA" Ref="#PWR?"  Part="1" 
AR Path="/5D5B1705/5DC842AA" Ref="#PWR?"  Part="1" 
AR Path="/5DC842AA" Ref="#PWR0132"  Part="1" 
F 0 "#PWR0132" H 1300 7550 50  0001 C CNN
F 1 "GND" H 1305 7627 50  0000 C CNN
F 2 "" H 1300 7800 50  0001 C CNN
F 3 "" H 1300 7800 50  0001 C CNN
	1    1300 7800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 7500 1300 7650
NoConn ~ 1600 7300
$Comp
L flight-computer:STF202-22T1G U?
U 1 1 5DC842B5
P 2850 7350
AR Path="/5D5B1705/5DC842B5" Ref="U?"  Part="1" 
AR Path="/5D5B15F7/5DC842B5" Ref="U?"  Part="1" 
AR Path="/5DC842B5" Ref="U1"  Part="1" 
F 0 "U1" H 2850 6785 50  0000 C CNN
F 1 "STF202-22T1G" H 2850 6876 50  0000 C CNN
F 2 "Package_SO:TSOP-6_1.65x3.05mm_P0.95mm" H 2800 7800 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/STF202-22T1-D.PDF" H 2750 7350 50  0001 C CNN
F 4 "0.5" H 2850 7350 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/on-semiconductor/stf202-22t1g/active-analog-filter/dp/1651958?st=STF202-22T1G" H 2850 7350 50  0001 C CNN "Purchase link"
F 6 "1" H 2850 7350 50  0001 C CNN "min_quantity"
	1    2850 7350
	-1   0    0    1   
$EndComp
Wire Wire Line
	3650 7100 3300 7100
Wire Wire Line
	3300 7200 3650 7200
Text HLabel 3650 7200 2    50   Input ~ 0
USB_DM
Text HLabel 3650 7100 2    50   Input ~ 0
USB_DP
Wire Wire Line
	2400 7400 2300 7400
Wire Wire Line
	2300 7400 2300 7750
$Comp
L power:GND #PWR?
U 1 1 5DC842C1
P 2300 7750
AR Path="/5D5B15F7/5DC842C1" Ref="#PWR?"  Part="1" 
AR Path="/5D5B1705/5DC842C1" Ref="#PWR?"  Part="1" 
AR Path="/5DC842C1" Ref="#PWR0133"  Part="1" 
F 0 "#PWR0133" H 2300 7500 50  0001 C CNN
F 1 "GND" H 2305 7577 50  0000 C CNN
F 2 "" H 2300 7750 50  0001 C CNN
F 3 "" H 2300 7750 50  0001 C CNN
	1    2300 7750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 6900 1950 6900
Wire Wire Line
	4250 7400 4250 7000
Wire Wire Line
	4250 7000 4700 7000
Wire Wire Line
	1950 6900 1950 6550
$Comp
L power:VBUS #PWR?
U 1 1 5DC842CB
P 4250 6650
AR Path="/5D5B1705/5DC842CB" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC842CB" Ref="#PWR?"  Part="1" 
AR Path="/5DC842CB" Ref="#PWR0134"  Part="1" 
F 0 "#PWR0134" H 4250 6500 50  0001 C CNN
F 1 "VBUS" H 4265 6823 50  0000 C CNN
F 2 "" H 4250 6650 50  0001 C CNN
F 3 "" H 4250 6650 50  0001 C CNN
	1    4250 6650
	1    0    0    -1  
$EndComp
Connection ~ 4250 7000
Wire Wire Line
	4250 7000 4250 6650
$Comp
L power:VBUS #PWR?
U 1 1 5DC842D3
P 1950 6550
AR Path="/5D5B1705/5DC842D3" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC842D3" Ref="#PWR?"  Part="1" 
AR Path="/5DC842D3" Ref="#PWR0135"  Part="1" 
F 0 "#PWR0135" H 1950 6400 50  0001 C CNN
F 1 "VBUS" H 1965 6723 50  0000 C CNN
F 2 "" H 1950 6550 50  0001 C CNN
F 3 "" H 1950 6550 50  0001 C CNN
	1    1950 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 8800 3550 9950
Wire Wire Line
	1900 10300 3550 10300
Connection ~ 3550 10300
Wire Wire Line
	3550 10300 3550 10450
Wire Wire Line
	3550 10250 3550 10300
Text HLabel 1900 10300 0    50   Output ~ 0
PWR_BVOLTS
$Comp
L Device:R R?
U 1 1 5DC842E2
P 3550 10100
AR Path="/5D5B1705/5DC842E2" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC842E2" Ref="R?"  Part="1" 
AR Path="/5DC842E2" Ref="R1"  Part="1" 
F 0 "R1" H 3620 10146 50  0000 L CNN
F 1 "120K" H 3620 10055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3480 10100 50  0001 C CNN
F 3 "~" H 3550 10100 50  0001 C CNN
F 4 "0.035" H 3550 10100 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6789715/" H 3550 10100 50  0001 C CNN "Purchase link"
F 6 "50" H 3550 10100 50  0001 C CNN "min_quantity"
	1    3550 10100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC842EB
P 3550 10600
AR Path="/5D5B1705/5DC842EB" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC842EB" Ref="R?"  Part="1" 
AR Path="/5DC842EB" Ref="R2"  Part="1" 
F 0 "R2" H 3620 10646 50  0000 L CNN
F 1 "120K" H 3620 10555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3480 10600 50  0001 C CNN
F 3 "~" H 3550 10600 50  0001 C CNN
F 4 "0.035" H 3550 10600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6789715/" H 3550 10600 50  0001 C CNN "Purchase link"
F 6 "50" H 3550 10600 50  0001 C CNN "min_quantity"
	1    3550 10600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC842F1
P 3550 10850
AR Path="/5D5B1705/5DC842F1" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC842F1" Ref="#PWR?"  Part="1" 
AR Path="/5DC842F1" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 3550 10600 50  0001 C CNN
F 1 "GND" H 3555 10677 50  0000 C CNN
F 2 "" H 3550 10850 50  0001 C CNN
F 3 "" H 3550 10850 50  0001 C CNN
	1    3550 10850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 10850 3550 10750
Wire Wire Line
	3300 7400 4250 7400
Wire Wire Line
	1600 7200 2400 7200
Wire Wire Line
	2400 7100 1600 7100
$EndSCHEMATC

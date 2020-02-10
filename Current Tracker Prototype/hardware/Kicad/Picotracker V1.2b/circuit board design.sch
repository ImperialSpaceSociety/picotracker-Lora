EESchema Schematic File Version 4
LIBS:circuit board design-cache
EELAYER 29 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Pico lora tracker"
Date "2019-10-21"
Rev "1.0b"
Comp "Imperial College Space Society"
Comment1 "Based on the Picotracker MK II and Project mach one flight computer"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR?
U 1 1 5DC84019
P 5800 5800
AR Path="/5D5B15F7/5DC84019" Ref="#PWR?"  Part="1" 
AR Path="/5DC84019" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 5800 5550 50  0001 C CNN
F 1 "GND" H 5805 5627 50  0000 C CNN
F 2 "" H 5800 5800 50  0001 C CNN
F 3 "" H 5800 5800 50  0001 C CNN
	1    5800 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5800 5800 5450
Wire Wire Line
	4900 5250 4550 5250
Wire Wire Line
	4550 5250 4550 5350
$Comp
L power:GND #PWR?
U 1 1 5DC2E511
P 4550 5800
AR Path="/5D5B15F7/5DC2E511" Ref="#PWR?"  Part="1" 
AR Path="/5DC2E511" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 4550 5550 50  0001 C CNN
F 1 "GND" H 4555 5627 50  0000 C CNN
F 2 "" H 4550 5800 50  0001 C CNN
F 3 "" H 4550 5800 50  0001 C CNN
	1    4550 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 5650 4550 5800
Wire Wire Line
	4900 4050 4100 4050
Wire Wire Line
	1350 1750 1650 1750
Wire Wire Line
	1350 1650 1750 1650
Wire Wire Line
	1750 1650 1750 2150
Wire Wire Line
	1350 1850 1650 1850
Text Label 4100 4150 0    50   ~ 0
SWCLK
Wire Wire Line
	4100 4150 4900 4150
Text Label 1650 1750 2    50   ~ 0
SWCLK
Text Label 1650 1850 2    50   ~ 0
SWDIO
$Comp
L power:GND #PWR?
U 1 1 5DC84056
P 1750 2150
AR Path="/5D5B15F7/5DC84056" Ref="#PWR?"  Part="1" 
AR Path="/5DC84056" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 1750 1900 50  0001 C CNN
F 1 "GND" H 1755 1977 50  0000 C CNN
F 2 "" H 1750 2150 50  0001 C CNN
F 3 "" H 1750 2150 50  0001 C CNN
	1    1750 2150
	1    0    0    -1  
$EndComp
Text Notes 700  2900 0    50   ~ 0
Debugging and programming\ninterface
Wire Wire Line
	1350 1950 1650 1950
Text Label 1650 1950 2    50   ~ 0
RESET
Wire Wire Line
	4900 4350 4100 4350
Text Label 3550 4350 0    50   ~ 0
RESET
Wire Wire Line
	4100 4350 4100 4600
Connection ~ 4100 4350
Wire Wire Line
	4100 4350 3550 4350
$Comp
L power:GND #PWR?
U 1 1 5DC84068
P 4100 4950
AR Path="/5D5B15F7/5DC84068" Ref="#PWR?"  Part="1" 
AR Path="/5DC84068" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 4100 4700 50  0001 C CNN
F 1 "GND" H 4105 4777 50  0000 C CNN
F 2 "" H 4100 4950 50  0001 C CNN
F 3 "" H 4100 4950 50  0001 C CNN
	1    4100 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4800 4100 4950
Wire Wire Line
	5700 1400 5700 2300
Wire Wire Line
	5800 2300 5700 2300
Connection ~ 5700 2300
Wire Wire Line
	5700 1400 6000 1400
Wire Wire Line
	6000 1400 6000 1500
Wire Wire Line
	6000 1750 6750 1750
Connection ~ 6000 1400
Wire Wire Line
	6000 1400 6750 1400
Wire Wire Line
	6750 1400 6750 1500
Wire Wire Line
	6000 1700 6000 1750
Connection ~ 6750 1400
Connection ~ 6750 1750
Wire Wire Line
	6750 1750 7450 1750
Wire Wire Line
	6750 1400 7450 1400
Connection ~ 7450 1400
Wire Wire Line
	7450 1400 7450 1500
Wire Wire Line
	7450 1400 7450 1100
Wire Wire Line
	6750 1700 6750 1750
Wire Wire Line
	7450 1700 7450 1750
$Comp
L power:GND #PWR?
U 1 1 5DC2E51C
P 7450 1900
AR Path="/5D5B15F7/5DC2E51C" Ref="#PWR?"  Part="1" 
AR Path="/5DC2E51C" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 7450 1650 50  0001 C CNN
F 1 "GND" H 7455 1727 50  0000 C CNN
F 2 "" H 7450 1900 50  0001 C CNN
F 3 "" H 7450 1900 50  0001 C CNN
	1    7450 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1900 7450 1750
Connection ~ 7450 1750
$Comp
L power:GND #PWR?
U 1 1 5DC840FF
P 1500 4600
AR Path="/5D5B1586/5DC840FF" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC840FF" Ref="#PWR?"  Part="1" 
AR Path="/5DC840FF" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 1500 4350 50  0001 C CNN
F 1 "GND" H 1505 4427 50  0000 C CNN
F 2 "" H 1500 4600 50  0001 C CNN
F 3 "" H 1500 4600 50  0001 C CNN
	1    1500 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC2E524
P 900 4600
AR Path="/5D5B1586/5DC2E524" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC2E524" Ref="#PWR?"  Part="1" 
AR Path="/5DC2E524" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 900 4350 50  0001 C CNN
F 1 "GND" H 905 4427 50  0000 C CNN
F 2 "" H 900 4600 50  0001 C CNN
F 3 "" H 900 4600 50  0001 C CNN
	1    900  4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4450 1500 4600
Wire Wire Line
	1100 4250 900  4250
Wire Wire Line
	900  4250 900  4600
$Comp
L power:GND #PWR?
U 1 1 5DC2E525
P 1950 3750
AR Path="/5D5B1586/5DC2E525" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DC2E525" Ref="#PWR?"  Part="1" 
AR Path="/5DC2E525" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 1950 3500 50  0001 C CNN
F 1 "GND" H 1955 3577 50  0000 C CNN
F 2 "" H 1950 3750 50  0001 C CNN
F 3 "" H 1950 3750 50  0001 C CNN
	1    1950 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3450 1500 3500
Wire Wire Line
	1950 3700 1950 3750
Wire Wire Line
	1950 3500 1500 3500
Connection ~ 1500 3500
Wire Wire Line
	1500 3500 1500 3650
Wire Wire Line
	1100 3850 1000 3850
Wire Wire Line
	1000 3850 1000 3500
Wire Wire Line
	1000 3500 1500 3500
NoConn ~ 1100 3950
Text Notes 800  5150 0    50   ~ 0
Pressure temperature humidity sensor\n
Text Notes 11200 9100 0    50   ~ 0
GPS circuit\n
Text Notes 7250 10950 0    50   ~ 0
Solar Connection\n\n
Wire Wire Line
	8150 5250 8150 5100
Text Label 600  4050 0    50   ~ 0
I2C1_SDA
Text Label 600  4150 0    50   ~ 0
I2C1_SCL
Wire Wire Line
	6000 2450 6000 2300
Wire Wire Line
	5800 2450 5800 2300
Wire Wire Line
	5700 2300 5700 2450
NoConn ~ 6700 3050
NoConn ~ 6700 4150
NoConn ~ 6700 4250
NoConn ~ 6700 4350
NoConn ~ 6700 4550
NoConn ~ 6700 4650
NoConn ~ 6700 4750
NoConn ~ 6700 4850
NoConn ~ 6700 4950
NoConn ~ 6700 5050
NoConn ~ 4900 3050
NoConn ~ 4900 4850
NoConn ~ 4900 4750
NoConn ~ 4900 4550
Wire Notes Line
	500  6850 11100 6850
Wire Notes Line
	16050 650  16050 9150
Text Notes 3050 6550 0    50   ~ 0
Main Microcontroller + Lora tranceiver\n
$Comp
L RF_Module:CMWX1ZZABZ-078 U?
U 1 1 5DC84013
P 5800 3950
AR Path="/5D5B15F7/5DC84013" Ref="U?"  Part="1" 
AR Path="/5DC84013" Ref="U3"  Part="1" 
F 0 "U3" H 5100 5550 50  0000 C CNN
F 1 "CMWX1ZZABZ-078" H 5100 5400 50  0000 C CNN
F 2 "RF_Module:CMWX1ZZABZ" H 5800 3950 50  0001 C CNN
F 3 "https://wireless.murata.com/RFM/data/type_abz.pdf" H 8250 2450 50  0001 C CNN
F 4 "13.32" H 5800 3950 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/radio-frequency-development-kits/1442713/" H 5800 3950 50  0001 C CNN "Purchase link"
F 6 "1" H 5800 3950 50  0001 C CNN "min_quantity"
	1    5800 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:Antenna AE1
U 1 1 5DE442FF
P 8150 4900
F 0 "AE1" H 8230 4889 50  0000 L CNN
F 1 "Lora Antenna" H 8230 4798 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8150 4900 50  0001 C CNN
F 3 "~" H 8150 4900 50  0001 C CNN
	1    8150 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC2E52C
P 1550 5900
AR Path="/5D5B1586/5DC2E52C" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC2E52C" Ref="R?"  Part="1" 
AR Path="/5DC2E52C" Ref="R5"  Part="1" 
F 0 "R5" H 1620 5946 50  0000 L CNN
F 1 "4.7K" H 1620 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1480 5900 50  0001 C CNN
F 3 "~" H 1550 5900 50  0001 C CNN
F 4 "0.0002" H 1550 5900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/3715086/" H 1550 5900 50  0001 C CNN "Purchase link"
F 6 "50" H 1550 5900 50  0001 C CNN "min_quantity"
	1    1550 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC84150
P 1250 5900
AR Path="/5D5B1586/5DC84150" Ref="R?"  Part="1" 
AR Path="/5D5B15F7/5DC84150" Ref="R?"  Part="1" 
AR Path="/5DC84150" Ref="R4"  Part="1" 
F 0 "R4" H 1320 5946 50  0000 L CNN
F 1 "4.7K" H 1320 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 1180 5900 50  0001 C CNN
F 3 "~" H 1250 5900 50  0001 C CNN
F 4 "0.0002" H 1250 5900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/3715086/" H 1250 5900 50  0001 C CNN "Purchase link"
F 6 "50" H 1250 5900 50  0001 C CNN "min_quantity"
	1    1250 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC2E528
P 1950 3600
AR Path="/5D5B1586/5DC2E528" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DC2E528" Ref="C?"  Part="1" 
AR Path="/5DC2E528" Ref="C14"  Part="1" 
F 0 "C14" H 2042 3646 50  0000 L CNN
F 1 "220nF" H 2042 3555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1950 3600 50  0001 C CNN
F 3 "~" H 1950 3600 50  0001 C CNN
F 4 "0.003" H 1950 3600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/0391135/" H 1950 3600 50  0001 C CNN "Purchase link"
F 6 "50" H 1950 3600 50  0001 C CNN "min_quantity"
	1    1950 3600
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Pressure:MS5607-02BA U?
U 1 1 5DC8412A
P 1500 4050
AR Path="/5D5B1586/5DC8412A" Ref="U?"  Part="1" 
AR Path="/5D5B15F7/5DC8412A" Ref="U?"  Part="1" 
AR Path="/5DC8412A" Ref="U6"  Part="1" 
F 0 "U6" H 1830 4096 50  0000 L CNN
F 1 "MS5607-02BA" H 1830 4005 50  0000 L CNN
F 2 "Package_LGA:LGA-8_3x5mm_P1.25mm" H 1500 4050 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=showdoc&DocId=Data+Sheet%7FMS5607-02BA03%7FB2%7Fpdf%7FEnglish%7FENG_DS_MS5607-02BA03_B2.pdf%7FCAT-BLPS0035" H 1500 4050 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/absolute-pressure-sensor-ics/8937095/" H 1500 4050 50  0001 C CNN "Purchase link"
F 5 "2.86" H 1500 4050 50  0001 C CNN "Cost"
F 6 "1" H 1500 4050 50  0001 C CNN "min_quantity"
	1    1500 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC8409B
P 7450 1600
AR Path="/5D5B15F7/5DC8409B" Ref="C?"  Part="1" 
AR Path="/5DC8409B" Ref="C10"  Part="1" 
F 0 "C10" H 7542 1646 50  0000 L CNN
F 1 "10uF" H 7542 1555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7450 1600 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 7450 1600 50  0001 C CNN
F 4 "0.07" H 7450 1600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 7450 1600 50  0001 C CNN "Purchase link"
F 6 "100" H 7450 1600 50  0001 C CNN "min_quantity"
	1    7450 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC84094
P 6750 1600
AR Path="/5D5B15F7/5DC84094" Ref="C?"  Part="1" 
AR Path="/5DC84094" Ref="C7"  Part="1" 
F 0 "C7" H 6842 1646 50  0000 L CNN
F 1 "1uF" H 6842 1555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6750 1600 50  0001 C CNN
F 3 "~" H 6750 1600 50  0001 C CNN
	1    6750 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC84080
P 6000 1600
AR Path="/5D5B15F7/5DC84080" Ref="C?"  Part="1" 
AR Path="/5DC84080" Ref="C5"  Part="1" 
F 0 "C5" H 6092 1646 50  0000 L CNN
F 1 "100nF" H 6092 1555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6000 1600 50  0001 C CNN
F 3 "~" H 6000 1600 50  0001 C CNN
F 4 "0.017" H 6000 1600 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983207/" H 6000 1600 50  0001 C CNN "Purchase link"
F 6 "100" H 6000 1600 50  0001 C CNN "min_quantity"
	1    6000 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DC8406E
P 4100 4700
AR Path="/5D5B15F7/5DC8406E" Ref="C?"  Part="1" 
AR Path="/5DC8406E" Ref="C1"  Part="1" 
F 0 "C1" H 4192 4746 50  0000 L CNN
F 1 "100nF" H 4192 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4100 4700 50  0001 C CNN
F 3 "~" H 4100 4700 50  0001 C CNN
F 4 "0.017" H 4100 4700 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983207/" H 4100 4700 50  0001 C CNN "Purchase link"
F 6 "100" H 4100 4700 50  0001 C CNN "min_quantity"
	1    4100 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DC2E512
P 4550 5500
AR Path="/5D5B15F7/5DC2E512" Ref="R?"  Part="1" 
AR Path="/5DC2E512" Ref="R3"  Part="1" 
F 0 "R3" H 4620 5546 50  0000 L CNN
F 1 "10K" H 4620 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4480 5500 50  0001 C CNN
F 3 "~" H 4550 5500 50  0001 C CNN
F 4 "0.033" H 4550 5500 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6784697/" H 4550 5500 50  0001 C CNN "Purchase link"
F 6 "50" H 4550 5500 50  0001 C CNN "min_quantity"
	1    4550 5500
	1    0    0    -1  
$EndComp
NoConn ~ 4900 5050
NoConn ~ 4900 3850
Text Label 4100 4050 0    50   ~ 0
SWDIO
Wire Wire Line
	5600 1400 5600 2450
Wire Wire Line
	4300 1400 4300 1100
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 5DC2E52D
P 7400 10100
F 0 "J3" H 7480 10142 50  0000 L CNN
F 1 "+SOL" H 7480 10051 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7400 10100 50  0001 C CNN
F 3 "~" H 7400 10100 50  0001 C CNN
	1    7400 10100
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5DC8B635
P 7400 10300
F 0 "J2" H 7550 10350 50  0000 C CNN
F 1 "GND" H 7550 10250 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7400 10300 50  0001 C CNN
F 3 "~" H 7400 10300 50  0001 C CNN
	1    7400 10300
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 SolarCellMount1
U 1 1 5DC2E52F
P 10000 1550
F 0 "SolarCellMount1" H 10080 1592 50  0000 L CNN
F 1 "Unconnected" H 10080 1501 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 10000 1550 50  0001 C CNN
F 3 "~" H 10000 1550 50  0001 C CNN
	1    10000 1550
	1    0    0    -1  
$EndComp
Text Notes 9650 2000 0    50   ~ 0
Structural plated throughole to \nhold the guitar wire solar \ncell structure
Wire Wire Line
	4900 3450 4100 3450
Wire Wire Line
	4300 1400 5600 1400
NoConn ~ 9800 1550
Wire Wire Line
	4900 3150 4100 3150
Wire Wire Line
	10850 3900 10850 4250
$Comp
L power:GND #PWR?
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
L Device:LED D1
U 1 1 5DBC4B62
P 10450 3900
F 0 "D1" H 10443 3645 50  0000 C CNN
F 1 "LED" H 10443 3736 50  0000 C CNN
F 2 "LED_SMD:LED_0402_1005Metric" H 10450 3900 50  0001 C CNN
F 3 "~" H 10450 3900 50  0001 C CNN
F 4 "0.155" H 10450 3900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/leds/4663649/" H 10450 3900 50  0001 C CNN "Purchase link"
F 6 "20" H 10450 3900 50  0001 C CNN "min_quantity"
	1    10450 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	10600 3900 10850 3900
$Comp
L Device:R R6
U 1 1 5DBC5657
P 10150 3900
F 0 "R6" V 9943 3900 50  0000 C CNN
F 1 "1K" V 10034 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10080 3900 50  0001 C CNN
F 3 "~" H 10150 3900 50  0001 C CNN
F 4 "0.0114" H 10150 3900 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw04021k00fked/res-1k-1-0-063w-0402-thick-film/dp/1469662RL?st=1k%200402" H 10150 3900 50  0001 C CNN "Purchase link"
F 6 "150" H 10150 3900 50  0001 C CNN "min_quantity"
	1    10150 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	10150 5850 9900 5850
Text Label 9500 5850 0    50   ~ 0
SWITCH
Wire Wire Line
	9900 5850 9900 6000
Connection ~ 9900 5850
Wire Wire Line
	9900 5850 9500 5850
$Comp
L power:GND #PWR?
U 1 1 5DC2E50B
P 9900 6400
AR Path="/5D5B15F7/5DC2E50B" Ref="#PWR?"  Part="1" 
AR Path="/5DC2E50B" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 9900 6150 50  0001 C CNN
F 1 "GND" H 9905 6227 50  0000 C CNN
F 2 "" H 9900 6400 50  0001 C CNN
F 3 "" H 9900 6400 50  0001 C CNN
	1    9900 6400
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5DC04C37
P 10350 5850
F 0 "SW1" H 10350 6135 50  0000 C CNN
F 1 "SW_Push" H 10350 6044 50  0000 C CNN
F 2 "flight-computer:EVPAWCD4A" H 10350 6050 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/1568/0900766b81568e09.pdf" H 10350 6050 50  0001 C CNN
F 4 "0.207" H 10350 5850 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/tactile-switches/1250189/?relevancy-data=636F3D3126696E3D4931384E53656172636847656E65726963266C753D656E266D6D3D6D61746368616C6C7061727469616C26706D3D5E5B5C707B4C7D5C707B4E647D2D2C2F255C2E5D2B2426706F3D31333326736E3D592673723D2673743D4B4559574F52445F53494E474C455F414C5048415F4E554D455249432673633D592677633D4E4F4E45267573743D455650415743443441267374613D45565041574344344126&searchHistory=%7B%22enabled%22%3Atrue%7D" H 10350 5850 50  0001 C CNN "Purchase link"
F 6 "10" H 10350 5850 50  0001 C CNN "min_quantity"
	1    10350 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 5850 10750 5850
$Comp
L Device:R R7
U 1 1 5DC0F569
P 9900 6150
F 0 "R7" H 9970 6196 50  0000 L CNN
F 1 "100K" H 9970 6105 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 9830 6150 50  0001 C CNN
F 3 "~" H 9900 6150 50  0001 C CNN
F 4 "0.0114" H 9900 6150 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw0402100kfked/res-100k-1-0-063w-0402-thick-film/dp/1469671RL?st=100k%200402" H 9900 6150 50  0001 C CNN "Purchase link"
F 6 "150" H 9900 6150 50  0001 C CNN "min_quantity"
	1    9900 6150
	1    0    0    -1  
$EndComp
Text Notes 9700 6750 0    50   ~ 0
User interface button\n
Wire Wire Line
	9900 6300 9900 6400
Wire Wire Line
	10750 5300 10750 5850
Wire Notes Line
	9350 650  9350 6850
Text Label 4100 3150 0    50   ~ 0
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
L Connector_Generic:Conn_01x01 StringHole1
U 1 1 5DB85E84
P 10000 2350
F 0 "StringHole1" H 10080 2392 50  0000 L CNN
F 1 "Unconnected" H 10080 2301 50  0000 L CNN
F 2 "flight-computer:SolderWirePad_1x01_Drill0.8mm" H 10000 2350 50  0001 C CNN
F 3 "~" H 10000 2350 50  0001 C CNN
	1    10000 2350
	1    0    0    -1  
$EndComp
NoConn ~ 9800 2350
Text Notes 9800 2600 0    50   ~ 0
Hole to tie string\n
Text Notes 9550 3150 0    50   ~ 0
Structural holes\n
Wire Wire Line
	7600 10100 7650 10100
Wire Notes Line
	6250 11200 6250 6850
$Comp
L pecanpico:SPV1040 IC?
U 1 1 5DD9B510
P 13050 2250
AR Path="/5DD2F7AA/5DD9B510" Ref="IC?"  Part="1" 
AR Path="/5DD9B510" Ref="IC7"  Part="1" 
F 0 "IC7" H 12700 2800 60  0000 L CNN
F 1 "SPV1040" H 13400 2000 60  0000 R CNN
F 2 "Package_SO:TSSOP-8_4.4x3mm_P0.65mm" H 13050 2250 60  0001 C CNN
F 3 "" H 13050 2250 60  0000 C CNN
F 4 "2.95" H 13050 2250 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/stmicroelectronics/spv1040t/battery-charger-1-8a-tssop-8/dp/2762710?scope=partnumberlookahead&ost=SPV1040T&searchref=searchlookahead&exaMfpn=true&ddkey=https%3Aen-GB%2FElement14_United_Kingdom%2Fw%2Fsearch" H 13050 2250 50  0001 C CNN "Purchase link"
F 6 "1" H 13050 2250 50  0001 C CNN "min_quantity"
	1    13050 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	12200 2750 12200 2650
Wire Wire Line
	6700 3350 7350 3350
Text Label 7350 3350 2    50   ~ 0
SENSOR_EN
NoConn ~ 6700 3250
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5E0E0060
P 7650 10100
F 0 "#FLG0101" H 7650 10175 50  0001 C CNN
F 1 "PWR_FLAG" H 7650 10273 50  0000 C CNN
F 2 "" H 7650 10100 50  0001 C CNN
F 3 "~" H 7650 10100 50  0001 C CNN
	1    7650 10100
	1    0    0    -1  
$EndComp
Connection ~ 7650 10100
Wire Wire Line
	7650 10100 8150 10100
Wire Wire Line
	7600 10300 8150 10300
Wire Wire Line
	8150 10550 8150 10300
$Comp
L power:GND #PWR0102
U 1 1 5DC2E531
P 8150 10550
F 0 "#PWR0102" H 8150 10300 50  0001 C CNN
F 1 "GND" H 8155 10377 50  0000 C CNN
F 2 "" H 8150 10550 50  0001 C CNN
F 3 "" H 8150 10550 50  0001 C CNN
	1    8150 10550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 5E15E5A3
P 10450 8750
F 0 "#PWR0119" H 10450 8500 50  0001 C CNN
F 1 "GND" H 10455 8577 50  0000 C CNN
F 2 "" H 10450 8750 50  0001 C CNN
F 3 "" H 10450 8750 50  0001 C CNN
	1    10450 8750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E16906A
P 10450 8200
AR Path="/5D5B15F7/5E16906A" Ref="R?"  Part="1" 
AR Path="/5E16906A" Ref="R2"  Part="1" 
F 0 "R2" H 10520 8246 50  0000 L CNN
F 1 "100K" H 10520 8155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10380 8200 50  0001 C CNN
F 3 "~" H 10450 8200 50  0001 C CNN
F 4 "0.0114" H 10450 8200 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw0402100kfked/res-100k-1-0-063w-0402-thick-film/dp/1469671RL?st=100k%200402" H 10450 8200 50  0001 C CNN "Purchase link"
F 6 "150" H 10450 8200 50  0001 C CNN "min_quantity"
	1    10450 8200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E1696E7
P 10450 8600
AR Path="/5D5B15F7/5E1696E7" Ref="R?"  Part="1" 
AR Path="/5E1696E7" Ref="R9"  Part="1" 
F 0 "R9" H 10520 8646 50  0000 L CNN
F 1 "100K" H 10520 8555 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 10380 8600 50  0001 C CNN
F 3 "~" H 10450 8600 50  0001 C CNN
F 4 "0.0114" H 10450 8600 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw0402100kfked/res-100k-1-0-063w-0402-thick-film/dp/1469671RL?st=100k%200402" H 10450 8600 50  0001 C CNN "Purchase link"
F 6 "150" H 10450 8600 50  0001 C CNN "min_quantity"
	1    10450 8600
	1    0    0    -1  
$EndComp
Text Label 9450 8400 0    50   ~ 0
SOLAR_VOLTS
Wire Wire Line
	9450 8400 10450 8400
Wire Notes Line
	11100 650  11100 11200
Wire Notes Line
	500  11200 11100 11200
Text Notes 11650 3300 0    50   ~ 0
MPPT + boost converter to charge battery
Wire Wire Line
	600  4050 1100 4050
Wire Wire Line
	1100 4150 600  4150
Text Label 1250 6500 1    50   ~ 0
I2C1_SDA
Text Label 1550 6500 1    50   ~ 0
I2C1_SCL
Wire Wire Line
	1250 6050 1250 6500
Wire Wire Line
	1550 6050 1550 6500
$Comp
L Device:C_Small C?
U 1 1 5DC1391C
P 12200 2550
AR Path="/5D5B15F7/5DC1391C" Ref="C?"  Part="1" 
AR Path="/5DC1391C" Ref="C4"  Part="1" 
F 0 "C4" H 12292 2596 50  0000 L CNN
F 1 "1nF" H 12292 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 12200 2550 50  0001 C CNN
F 3 "~" H 12200 2550 50  0001 C CNN
F 4 "0.011" H 12200 2550 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983131/" H 12200 2550 50  0001 C CNN "Purchase link"
F 6 "100" H 12200 2550 50  0001 C CNN "min_quantity"
	1    12200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	12200 2450 12200 2350
Wire Wire Line
	11900 1850 11900 2450
Wire Wire Line
	11900 1850 12200 1850
Wire Wire Line
	11900 2750 12200 2750
Connection ~ 12200 1850
Wire Wire Line
	12200 1850 12300 1850
Wire Wire Line
	12200 2350 12400 2350
$Comp
L Device:C_Small C?
U 1 1 5DC6EDAC
P 11900 2550
AR Path="/5D5B15F7/5DC6EDAC" Ref="C?"  Part="1" 
AR Path="/5DC6EDAC" Ref="C3"  Part="1" 
F 0 "C3" H 11992 2596 50  0000 L CNN
F 1 "4.7uF" H 11950 2450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 11900 2550 50  0001 C CNN
F 3 "~" H 11900 2550 50  0001 C CNN
F 4 "0.074" H 11900 2550 50  0001 C CNN "Cost"
F 5 "50" H 11900 2550 50  0001 C CNN "min_quantity"
F 6 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/7661037/" H 11900 2550 50  0001 C CNN "Purchase link"
	1    11900 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	11900 2650 11900 2750
$Comp
L Device:R R8
U 1 1 5DC723E7
P 12200 2050
F 0 "R8" H 12270 2096 50  0000 L CNN
F 1 "1K" H 12270 2005 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 12130 2050 50  0001 C CNN
F 3 "~" H 12200 2050 50  0001 C CNN
F 4 "0.0114" H 12200 2050 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw04021k00fked/res-1k-1-0-063w-0402-thick-film/dp/1469662RL?st=1k%200402" H 12200 2050 50  0001 C CNN "Purchase link"
F 6 "150" H 12200 2050 50  0001 C CNN "min_quantity"
	1    12200 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12200 1900 12200 1850
Wire Wire Line
	12600 2200 12500 2200
$Comp
L power:GND #PWR?
U 1 1 5DC7C9E7
P 12500 2200
AR Path="/5D5B15F7/5DC7C9E7" Ref="#PWR?"  Part="1" 
AR Path="/5DC7C9E7" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 12500 1950 50  0001 C CNN
F 1 "GND" H 12500 2250 50  0000 C CNN
F 2 "" H 12500 2200 50  0001 C CNN
F 3 "" H 12500 2200 50  0001 C CNN
	1    12500 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	13500 1850 14200 1850
Wire Wire Line
	14200 2000 14200 1850
Connection ~ 14200 1850
Wire Wire Line
	14200 1850 14200 1550
Wire Wire Line
	14200 1550 14100 1550
Wire Wire Line
	13850 1550 13850 1600
Wire Wire Line
	12200 2750 13400 2750
Connection ~ 12200 2750
$Comp
L pecanpico:GND #PWR?
U 1 1 5DCF13EF
P 13850 1600
AR Path="/5DD2F7AA/5DCF13EF" Ref="#PWR?"  Part="1" 
AR Path="/5DCF13EF" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 13850 1350 50  0001 C CNN
F 1 "GND" H 13850 1450 50  0000 C CNN
F 2 "" H 13850 1600 50  0001 C CNN
F 3 "" H 13850 1600 50  0001 C CNN
	1    13850 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DCF9C49
P 14000 1550
AR Path="/5D5B15F7/5DCF9C49" Ref="C?"  Part="1" 
AR Path="/5DCF9C49" Ref="C17"  Part="1" 
F 0 "C17" V 14250 1500 50  0000 L CNN
F 1 "22uF" V 14150 1500 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 14000 1550 50  0001 C CNN
F 3 "" H 14000 1550 50  0001 C CNN
F 4 "0.0107" H 14000 1550 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/7883023/" H 14000 1550 50  0001 C CNN "Purchase link"
F 6 "10" H 14000 1550 50  0001 C CNN "min_quantity"
	1    14000 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	13900 1550 13850 1550
Connection ~ 14650 1850
Wire Wire Line
	14650 1850 14950 1850
Connection ~ 14650 2750
Wire Wire Line
	14650 2750 14950 2750
Wire Wire Line
	14950 1850 14950 2200
Connection ~ 14950 1850
Connection ~ 14500 1850
Wire Wire Line
	14500 1850 14650 1850
Wire Wire Line
	13500 2350 13650 2350
$Comp
L Device:C_Small C?
U 1 1 5DD284B0
P 13650 2100
AR Path="/5D5B15F7/5DD284B0" Ref="C?"  Part="1" 
AR Path="/5DD284B0" Ref="C15"  Part="1" 
F 0 "C15" H 13742 2146 50  0000 L CNN
F 1 "1uF" H 13742 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 13650 2100 50  0001 C CNN
F 3 "~" H 13650 2100 50  0001 C CNN
	1    13650 2100
	1    0    0    -1  
$EndComp
Connection ~ 12200 2350
Wire Wire Line
	12200 2200 12200 2350
Connection ~ 14650 2350
Wire Wire Line
	14650 2350 14650 2400
Wire Wire Line
	14650 1850 14650 1950
Wire Wire Line
	14500 1850 14500 2200
Wire Wire Line
	13650 2350 13650 2450
$Comp
L Device:C_Small C?
U 1 1 5DD6FE15
P 13650 2550
AR Path="/5D5B15F7/5DD6FE15" Ref="C?"  Part="1" 
AR Path="/5DD6FE15" Ref="C16"  Part="1" 
F 0 "C16" H 13742 2596 50  0000 L CNN
F 1 "1nF" H 13742 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 13650 2550 50  0001 C CNN
F 3 "~" H 13650 2550 50  0001 C CNN
F 4 "0.011" H 13650 2550 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983131/" H 13650 2550 50  0001 C CNN "Purchase link"
F 6 "100" H 13650 2550 50  0001 C CNN "min_quantity"
	1    13650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	13650 2650 13650 2750
Wire Wire Line
	13500 2000 13650 2000
Wire Wire Line
	13500 2200 13650 2200
Connection ~ 13650 2000
Connection ~ 13650 2200
Wire Wire Line
	13650 2000 13850 2000
Wire Wire Line
	13650 2200 13850 2200
Connection ~ 13650 2750
Wire Wire Line
	13650 2750 14650 2750
Connection ~ 13650 2350
Wire Wire Line
	13650 2350 14650 2350
$Comp
L Device:R R10
U 1 1 5DD9A304
P 14000 2000
F 0 "R10" V 13900 2000 50  0000 C CNN
F 1 "1K" V 14000 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 13930 2000 50  0001 C CNN
F 3 "~" H 14000 2000 50  0001 C CNN
F 4 "0.0114" H 14000 2000 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw04021k00fked/res-1k-1-0-063w-0402-thick-film/dp/1469662RL?st=1k%200402" H 14000 2000 50  0001 C CNN "Purchase link"
F 6 "150" H 14000 2000 50  0001 C CNN "min_quantity"
	1    14000 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	14150 2000 14200 2000
$Comp
L Device:R R11
U 1 1 5DD9AD1B
P 14000 2200
F 0 "R11" V 13900 2200 50  0000 C CNN
F 1 "1K" V 14000 2200 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 13930 2200 50  0001 C CNN
F 3 "~" H 14000 2200 50  0001 C CNN
F 4 "0.0114" H 14000 2200 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw04021k00fked/res-1k-1-0-063w-0402-thick-film/dp/1469662RL?st=1k%200402" H 14000 2200 50  0001 C CNN "Purchase link"
F 6 "150" H 14000 2200 50  0001 C CNN "min_quantity"
	1    14000 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	14150 2200 14500 2200
$Comp
L Device:R R13
U 1 1 5DD9B019
P 14650 2100
F 0 "R13" V 14443 2100 50  0000 C CNN
F 1 "10M" V 14534 2100 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 14580 2100 50  0001 C CNN
F 3 "~" H 14650 2100 50  0001 C CNN
F 4 "0.02" H 14650 2100 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6788709/" H 14650 2100 50  0001 C CNN "Purchase link"
F 6 "50" H 14650 2100 50  0001 C CNN "min_quantity"
	1    14650 2100
	-1   0    0    1   
$EndComp
Wire Wire Line
	14650 2250 14650 2350
$Comp
L Device:R R14
U 1 1 5DD9B414
P 14650 2550
F 0 "R14" V 14443 2550 50  0000 C CNN
F 1 "5.1M" V 14534 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 14580 2550 50  0001 C CNN
F 3 "~" H 14650 2550 50  0001 C CNN
F 4 "0.0137" H 14650 2550 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/yageo/rc0402fr-075m1l/res-5m1-1-0-063w-0402-thick-film/dp/1458808" H 14650 2550 50  0001 C CNN "Purchase link"
F 6 "10" H 14650 2550 50  0001 C CNN "min_quantity"
	1    14650 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	14650 2700 14650 2750
$Comp
L Device:R R12
U 1 1 5DD9BA91
P 14350 1850
F 0 "R12" V 14450 1850 50  0000 C CNN
F 1 "1Ohm" V 14350 1850 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 14280 1850 50  0001 C CNN
F 3 "~" H 14350 1850 50  0001 C CNN
F 4 "0.0004" H 14350 1850 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/0430284/" H 14350 1850 50  0001 C CNN "Purchase link"
F 6 "100" H 14350 1850 50  0001 C CNN "min_quantity"
	1    14350 1850
	0    -1   -1   0   
$EndComp
$Comp
L pecanpico:+SOL #PWR?
U 1 1 5DDA5AE9
P 11900 1750
AR Path="/5DD2F7AA/5DDA5AE9" Ref="#PWR?"  Part="1" 
AR Path="/5DDA5AE9" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 11900 1600 50  0001 C CNN
F 1 "+SOL" H 11915 1923 50  0000 C CNN
F 2 "" H 11900 1750 50  0000 C CNN
F 3 "" H 11900 1750 50  0000 C CNN
	1    11900 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11900 1750 11900 1850
Connection ~ 11900 1850
$Comp
L pecanpico:GND #PWR?
U 1 1 5DDD374A
P 13400 2950
AR Path="/5DD2F7AA/5DDD374A" Ref="#PWR?"  Part="1" 
AR Path="/5DDD374A" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 13400 2700 50  0001 C CNN
F 1 "GND" H 13400 2800 50  0000 C CNN
F 2 "" H 13400 2950 50  0001 C CNN
F 3 "" H 13400 2950 50  0001 C CNN
	1    13400 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	13400 2950 13400 2750
Connection ~ 13400 2750
Wire Wire Line
	13400 2750 13650 2750
$Comp
L Device:D_Schottky D2
U 1 1 5DE3137F
P 14950 2350
F 0 "D2" V 14904 2429 50  0000 L CNN
F 1 "D_Schottky" V 14800 2500 50  0000 L CNN
F 2 "Diode_SMD:D_0402_1005Metric" H 14950 2350 50  0001 C CNN
F 3 "~" H 14950 2350 50  0001 C CNN
F 4 "https://uk.rs-online.com/web/p/rectifier-diodes-schottky-diodes/1867707/" H 14950 2350 50  0001 C CNN "Purchase link"
F 5 "0.22" H 14950 2350 50  0001 C CNN "Cost"
F 6 "25" H 14950 2350 50  0001 C CNN "min_quantity"
	1    14950 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	14950 2500 14950 2750
$Comp
L pecanpico:+BATT #PWR016
U 1 1 5DE43318
P 14950 1750
F 0 "#PWR016" H 14950 1600 50  0001 C CNN
F 1 "+BATT" H 14965 1923 50  0000 C CNN
F 2 "" H 14950 1750 50  0001 C CNN
F 3 "" H 14950 1750 50  0001 C CNN
	1    14950 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	14950 1850 14950 1750
Wire Wire Line
	3150 8950 3050 8950
Wire Wire Line
	2600 8950 2600 8650
Connection ~ 2600 8950
$Comp
L power:GND #PWR05
U 1 1 5DF52CB4
P 2600 9900
F 0 "#PWR05" H 2600 9650 50  0001 C CNN
F 1 "GND" H 2605 9727 50  0000 C CNN
F 2 "" H 2600 9900 50  0001 C CNN
F 3 "" H 2600 9900 50  0001 C CNN
	1    2600 9900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 8950 2600 9350
$Comp
L power:GND #PWR06
U 1 1 5DF751EA
P 2900 9900
F 0 "#PWR06" H 2900 9650 50  0001 C CNN
F 1 "GND" H 2905 9727 50  0000 C CNN
F 2 "" H 2900 9900 50  0001 C CNN
F 3 "" H 2900 9900 50  0001 C CNN
	1    2900 9900
	1    0    0    -1  
$EndComp
Connection ~ 3050 8950
Wire Wire Line
	3050 8950 2600 8950
Wire Wire Line
	3150 9050 3050 9050
Wire Wire Line
	3050 9050 3050 8950
$Comp
L Device:C_Small C?
U 1 1 5DFD1A5E
P 2600 9450
AR Path="/5D5B15F7/5DFD1A5E" Ref="C?"  Part="1" 
AR Path="/5DFD1A5E" Ref="C2"  Part="1" 
F 0 "C2" H 2692 9496 50  0000 L CNN
F 1 "10uF" H 2692 9405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2600 9450 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 2600 9450 50  0001 C CNN
F 4 "0.07" H 2600 9450 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 2600 9450 50  0001 C CNN "Purchase link"
F 6 "100" H 2600 9450 50  0001 C CNN "min_quantity"
	1    2600 9450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 9550 2600 9900
$Comp
L power:GND #PWR?
U 1 1 5DBDE5AC
P 13600 8200
AR Path="/5D5B165E/5DBDE5AC" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DBDE5AC" Ref="#PWR?"  Part="1" 
AR Path="/5DBDE5AC" Ref="#PWR013"  Part="1" 
AR Path="/5E01805B/5DBDE5AC" Ref="#PWR?"  Part="1" 
F 0 "#PWR013" H 13600 7950 50  0001 C CNN
F 1 "GND" H 13605 8027 50  0000 C CNN
F 2 "" H 13600 8200 50  0001 C CNN
F 3 "" H 13600 8200 50  0001 C CNN
	1    13600 8200
	1    0    0    -1  
$EndComp
Wire Wire Line
	12850 6350 12850 6250
Wire Wire Line
	13200 6250 13200 6350
Wire Wire Line
	13200 5950 12850 5950
Wire Wire Line
	13200 6050 13200 5950
Wire Wire Line
	12850 5950 12850 6050
$Comp
L power:GND #PWR?
U 1 1 5DBDE5BD
P 12850 6450
AR Path="/5D5B17D8/5DBDE5BD" Ref="#PWR?"  Part="1" 
AR Path="/5D5B165E/5DBDE5BD" Ref="#PWR?"  Part="1" 
AR Path="/5D5B15F7/5DBDE5BD" Ref="#PWR?"  Part="1" 
AR Path="/5DBDE5BD" Ref="#PWR010"  Part="1" 
AR Path="/5E01805B/5DBDE5BD" Ref="#PWR?"  Part="1" 
F 0 "#PWR010" H 12850 6200 50  0001 C CNN
F 1 "GND" H 12855 6277 50  0000 C CNN
F 2 "" H 12850 6450 50  0001 C CNN
F 3 "" H 12850 6450 50  0001 C CNN
	1    12850 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	12850 6450 12850 6350
Connection ~ 12850 6350
Wire Wire Line
	12850 6350 13200 6350
Wire Wire Line
	14850 7350 14850 7200
Text Label 12300 7250 0    50   ~ 0
I2C1_SDA
Text Label 12300 7350 0    50   ~ 0
I2C1_SCL
Wire Wire Line
	13500 6600 13400 6600
Connection ~ 13400 6600
Wire Wire Line
	11800 7750 11800 7350
Wire Wire Line
	13400 6600 13400 6650
Wire Wire Line
	13500 6650 13500 6600
NoConn ~ 13000 6950
NoConn ~ 13000 7050
Wire Wire Line
	12300 7350 13000 7350
Wire Wire Line
	13000 7250 12300 7250
NoConn ~ 13800 6650
Wire Wire Line
	14200 7350 14850 7350
Wire Wire Line
	13600 8050 13600 8200
Wire Wire Line
	14200 7650 15050 7650
Text Label 15050 7650 2    50   ~ 0
GPS_TIMEPULSE
$Comp
L RF_GPS:MAX-M8C U?
U 1 1 5DBDE5E5
P 13600 7350
AR Path="/5E01805B/5DBDE5E5" Ref="U?"  Part="1" 
AR Path="/5DBDE5E5" Ref="U4"  Part="1" 
F 0 "U4" H 13200 6550 50  0000 C CNN
F 1 "MAX-M8C" H 13200 6450 50  0000 C CNN
F 2 "RF_GPS:ublox_MAX" H 14000 6700 50  0001 C CNN
F 3 "https://www.u-blox.com/sites/default/files/MAX-M8-FW3_DataSheet_%28UBX-15031506%29.pdf" H 13600 7350 50  0001 C CNN
	1    13600 7350
	1    0    0    -1  
$EndComp
$Comp
L flight-computer:GPS_Antenna AE?
U 1 1 5DBDE5EB
P 14850 7000
AR Path="/5E01805B/5DBDE5EB" Ref="AE?"  Part="1" 
AR Path="/5DBDE5EB" Ref="AE3"  Part="1" 
F 0 "AE3" H 14930 6989 50  0000 L CNN
F 1 "GPS Antenna" H 14930 6898 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 14850 7000 50  0001 C CNN
F 3 "~" H 14850 7000 50  0001 C CNN
	1    14850 7000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DBDE5F4
P 13200 6150
AR Path="/5D5B17D8/5DBDE5F4" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5DBDE5F4" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DBDE5F4" Ref="C?"  Part="1" 
AR Path="/5DBDE5F4" Ref="C8"  Part="1" 
AR Path="/5E01805B/5DBDE5F4" Ref="C?"  Part="1" 
F 0 "C8" H 13108 6196 50  0000 R CNN
F 1 "10uF" H 13108 6105 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 13200 6150 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 13200 6150 50  0001 C CNN
F 4 "0.07" H 13200 6150 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 13200 6150 50  0001 C CNN "Purchase link"
F 6 "100" H 13200 6150 50  0001 C CNN "min_quantity"
	1    13200 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5DBDE5FD
P 12850 6150
AR Path="/5D5B17D8/5DBDE5FD" Ref="C?"  Part="1" 
AR Path="/5D5B165E/5DBDE5FD" Ref="C?"  Part="1" 
AR Path="/5D5B15F7/5DBDE5FD" Ref="C?"  Part="1" 
AR Path="/5DBDE5FD" Ref="C6"  Part="1" 
AR Path="/5E01805B/5DBDE5FD" Ref="C?"  Part="1" 
F 0 "C6" H 12758 6196 50  0000 R CNN
F 1 "100nF" H 12758 6105 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 12850 6150 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/0dc2/0900766b80dc2409.pdf" H 12850 6150 50  0001 C CNN
F 4 "0.017" H 12850 6150 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983207/" H 12850 6150 50  0001 C CNN "Purchase link"
F 6 "100" H 12850 6150 50  0001 C CNN "min_quantity"
	1    12850 6150
	1    0    0    -1  
$EndComp
Connection ~ 13200 5950
Wire Wire Line
	13400 5400 13400 5950
Wire Wire Line
	13400 5950 13400 6600
Connection ~ 13400 5950
Wire Wire Line
	13400 5950 13200 5950
Text Label 7350 3450 2    50   ~ 0
I2C1_SCL
Text Label 7350 3550 2    50   ~ 0
I2C1_SDA
Wire Wire Line
	4900 3250 4100 3250
Text Label 4100 3250 0    50   ~ 0
SWITCH
Wire Wire Line
	6700 3550 7350 3550
Wire Wire Line
	6700 3450 7350 3450
Wire Wire Line
	3900 9450 4400 9450
Text Label 4400 9450 2    50   ~ 0
SENSOR_EN
Wire Wire Line
	3900 9550 4300 9550
Wire Wire Line
	4300 9550 4300 9850
Wire Wire Line
	3900 8950 4050 8950
Wire Wire Line
	4550 8950 4550 9050
Wire Wire Line
	4550 9050 3900 9050
Wire Wire Line
	4550 9050 4550 9350
$Comp
L power:GND #PWR019
U 1 1 5DCA4D78
P 4550 9950
F 0 "#PWR019" H 4550 9700 50  0001 C CNN
F 1 "GND" H 4555 9777 50  0000 C CNN
F 2 "" H 4550 9950 50  0001 C CNN
F 3 "" H 4550 9950 50  0001 C CNN
	1    4550 9950
	1    0    0    -1  
$EndComp
Connection ~ 4550 9050
$Comp
L Device:L L2
U 1 1 5DCB8AA3
P 4200 8950
F 0 "L2" V 4019 8950 50  0000 C CNN
F 1 "2.2uH" V 4110 8950 50  0000 C CNN
F 2 "flight-computer:L_Coilcraft_LPS3015" H 4200 8950 50  0001 C CNN
F 3 "~" H 4200 8950 50  0001 C CNN
F 4 "1.41" H 4200 8950 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/coilcraft/lps3015-222mrb/inductor-2-2uh-20-1-1a-shld-smd/dp/2408020?st=LPS3015" H 4200 8950 50  0001 C CNN "Purchase link"
F 6 "1" H 4200 8950 50  0001 C CNN "min_quantity"
	1    4200 8950
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 8950 4550 8950
Wire Wire Line
	4050 9850 4300 9850
$Comp
L Device:C_Small C?
U 1 1 5DCF62B4
P 4550 9450
AR Path="/5D5B15F7/5DCF62B4" Ref="C?"  Part="1" 
AR Path="/5DCF62B4" Ref="C12"  Part="1" 
F 0 "C12" H 4642 9496 50  0000 L CNN
F 1 "10uF" H 4642 9405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4550 9450 50  0001 C CNN
F 3 "https://docs-emea.rs-online.com/webdocs/13b3/0900766b813b3e64.pdf" H 4550 9450 50  0001 C CNN
F 4 "0.07" H 4550 9450 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/8467293/" H 4550 9450 50  0001 C CNN "Purchase link"
F 6 "100" H 4550 9450 50  0001 C CNN "min_quantity"
	1    4550 9450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 9550 4550 9950
$Comp
L flight-computer:SENSOR_VCC #PWR01
U 1 1 5E03CB4D
P 1400 5550
F 0 "#PWR01" H 1400 5400 50  0001 C CNN
F 1 "SENSOR_VCC" H 1400 5700 50  0000 C CNN
F 2 "" H 1400 5550 50  0001 C CNN
F 3 "" H 1400 5550 50  0001 C CNN
	1    1400 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 5750 1250 5650
Wire Wire Line
	1250 5650 1400 5650
Wire Wire Line
	1400 5650 1400 5550
Wire Wire Line
	1550 5750 1550 5650
Wire Wire Line
	1550 5650 1400 5650
Connection ~ 1400 5650
$Comp
L flight-computer:SENSOR_VCC #PWR04
U 1 1 5E06CE4F
P 1500 3450
F 0 "#PWR04" H 1500 3300 50  0001 C CNN
F 1 "SENSOR_VCC" H 1500 3600 50  0000 C CNN
F 2 "" H 1500 3450 50  0001 C CNN
F 3 "" H 1500 3450 50  0001 C CNN
	1    1500 3450
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR020
U 1 1 5E08AF07
P 4300 1100
F 0 "#PWR020" H 4300 950 50  0001 C CNN
F 1 "VCC" H 4317 1273 50  0000 C CNN
F 2 "" H 4300 1100 50  0001 C CNN
F 3 "" H 4300 1100 50  0001 C CNN
	1    4300 1100
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR022
U 1 1 5E096DD9
P 7450 1100
F 0 "#PWR022" H 7450 950 50  0001 C CNN
F 1 "VCC" H 7467 1273 50  0000 C CNN
F 2 "" H 7450 1100 50  0001 C CNN
F 3 "" H 7450 1100 50  0001 C CNN
	1    7450 1100
	1    0    0    -1  
$EndComp
Wire Notes Line
	2500 650  2500 6850
$Comp
L power:VCC #PWR012
U 1 1 5E0C64C4
P 2050 1200
F 0 "#PWR012" H 2050 1050 50  0001 C CNN
F 1 "VCC" H 2067 1373 50  0000 C CNN
F 2 "" H 2050 1200 50  0001 C CNN
F 3 "" H 2050 1200 50  0001 C CNN
	1    2050 1200
	1    0    0    -1  
$EndComp
Wire Notes Line
	9350 4900 16050 4900
$Comp
L power:VCC #PWR023
U 1 1 5E107F8F
P 10750 5300
F 0 "#PWR023" H 10750 5150 50  0001 C CNN
F 1 "VCC" H 10767 5473 50  0000 C CNN
F 2 "" H 10750 5300 50  0001 C CNN
F 3 "" H 10750 5300 50  0001 C CNN
	1    10750 5300
	1    0    0    -1  
$EndComp
$Comp
L pecanpico:+BATT #PWR017
U 1 1 5E147183
P 2600 8650
F 0 "#PWR017" H 2600 8500 50  0001 C CNN
F 1 "+BATT" H 2615 8823 50  0000 C CNN
F 2 "" H 2600 8650 50  0001 C CNN
F 3 "" H 2600 8650 50  0001 C CNN
	1    2600 8650
	1    0    0    -1  
$EndComp
Text Notes 2100 10550 0    50   ~ 0
Buck coverter to bring battery voltage down to voltage for GPS and ABZ module
Connection ~ 4550 8950
$Comp
L power:VCC #PWR021
U 1 1 5E172F29
P 4550 8650
F 0 "#PWR021" H 4550 8500 50  0001 C CNN
F 1 "VCC" H 4567 8823 50  0000 C CNN
F 2 "" H 4550 8650 50  0001 C CNN
F 3 "" H 4550 8650 50  0001 C CNN
	1    4550 8650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 8650 4550 8950
NoConn ~ 3900 9350
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5E1C29C2
P 9800 10100
F 0 "J4" H 9880 10142 50  0000 L CNN
F 1 "Batt connection" H 9880 10051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9800 10100 50  0001 C CNN
F 3 "~" H 9800 10100 50  0001 C CNN
	1    9800 10100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 10100 9550 10100
Wire Wire Line
	9250 10200 9600 10200
$Comp
L Device:L L3
U 1 1 5E24769B
P 12450 1850
F 0 "L3" V 12269 1850 50  0000 C CNN
F 1 "10uH" V 12360 1850 50  0000 C CNN
F 2 "flight-computer:L_Coilcraft_LPS3015" H 12450 1850 50  0001 C CNN
F 3 "https://www.mouser.co.uk/datasheet/2/597/lps3015-270734.pdf" H 12450 1850 50  0001 C CNN
F 4 "1.42" H 12450 1850 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/coilcraft/lps3015-103mrb/inductor-10uh-20-0-55a-shld-smd/dp/2408024?st=LPS3015" H 12450 1850 50  0001 C CNN "Purchase link"
F 6 "1" H 12450 1850 50  0001 C CNN "min_quantity"
	1    12450 1850
	0    1    1    0   
$EndComp
$Comp
L flight-computer:TPS62740 U2
U 1 1 5DEFEDB4
P 3550 8900
F 0 "U2" H 3550 9115 50  0000 C CNN
F 1 "TPS62740" H 3550 9024 50  0000 C CNN
F 2 "Package_SON:WSON-12-1EP_3x2mm_P0.5mm_EP1x2.65" H 3550 8900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tps62742.pdf" H 3550 8900 50  0001 C CNN
F 4 "1.575" H 3550 8900 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/buck-converters/8257018/" H 3550 8900 50  0001 C CNN "Purchase link"
F 6 "2" H 3550 8900 50  0001 C CNN "min_quantity"
	1    3550 8900
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5E303014
P 9550 10100
F 0 "#FLG0102" H 9550 10175 50  0001 C CNN
F 1 "PWR_FLAG" H 9550 10273 50  0000 C CNN
F 2 "" H 9550 10100 50  0001 C CNN
F 3 "~" H 9550 10100 50  0001 C CNN
	1    9550 10100
	1    0    0    -1  
$EndComp
Connection ~ 9550 10100
Wire Wire Line
	9550 10100 9600 10100
Wire Notes Line
	500  650  500  11200
Wire Notes Line
	500  650  16050 650 
Wire Notes Line
	500  3050 2500 3050
Wire Wire Line
	6000 2300 6350 2300
Wire Wire Line
	4900 3950 4100 3950
Text Label 4100 3950 0    50   ~ 0
TCXO_EN
Text Label 6350 2300 2    50   ~ 0
TCXO_EN
$Comp
L femto-lib:+SOL #PWR027
U 1 1 5DC0234C
P 8150 9850
F 0 "#PWR027" H 8150 9700 50  0001 C CNN
F 1 "+SOL" H 8165 10023 50  0000 C CNN
F 2 "" H 8150 9850 50  0000 C CNN
F 3 "" H 8150 9850 50  0000 C CNN
	1    8150 9850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 10100 8150 9850
$Comp
L femto-lib:+SOL #PWR028
U 1 1 5DC214AB
P 10450 7200
F 0 "#PWR028" H 10450 7050 50  0001 C CNN
F 1 "+SOL" H 10465 7373 50  0000 C CNN
F 2 "" H 10450 7200 50  0000 C CNN
F 3 "" H 10450 7200 50  0000 C CNN
	1    10450 7200
	1    0    0    -1  
$EndComp
Text Notes 6300 9100 0    50   ~ 0
Ultra Low current Solar and Battery voltage measurment
Wire Wire Line
	10450 8350 10450 8400
Connection ~ 10450 8400
Wire Wire Line
	10450 8400 10450 8450
Wire Notes Line
	6250 9150 16050 9150
$Comp
L power:GND #PWR026
U 1 1 5DDA9C37
P 8050 8750
F 0 "#PWR026" H 8050 8500 50  0001 C CNN
F 1 "GND" H 8055 8577 50  0000 C CNN
F 2 "" H 8050 8750 50  0001 C CNN
F 3 "" H 8050 8750 50  0001 C CNN
	1    8050 8750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DDA9C41
P 8050 8200
AR Path="/5D5B15F7/5DDA9C41" Ref="R?"  Part="1" 
AR Path="/5DDA9C41" Ref="R15"  Part="1" 
F 0 "R15" H 8120 8246 50  0000 L CNN
F 1 "100K" H 8120 8155 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7980 8200 50  0001 C CNN
F 3 "~" H 8050 8200 50  0001 C CNN
F 4 "0.0114" H 8050 8200 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw0402100kfked/res-100k-1-0-063w-0402-thick-film/dp/1469671RL?st=100k%200402" H 8050 8200 50  0001 C CNN "Purchase link"
F 6 "150" H 8050 8200 50  0001 C CNN "min_quantity"
	1    8050 8200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DDA9C4B
P 8050 8600
AR Path="/5D5B15F7/5DDA9C4B" Ref="R?"  Part="1" 
AR Path="/5DDA9C4B" Ref="R16"  Part="1" 
F 0 "R16" H 8120 8646 50  0000 L CNN
F 1 "100K" H 8120 8555 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7980 8600 50  0001 C CNN
F 3 "~" H 8050 8600 50  0001 C CNN
F 4 "0.0114" H 8050 8600 50  0001 C CNN "Cost"
F 5 "https://uk.farnell.com/vishay/crcw0402100kfked/res-100k-1-0-063w-0402-thick-film/dp/1469671RL?st=100k%200402" H 8050 8600 50  0001 C CNN "Purchase link"
F 6 "150" H 8050 8600 50  0001 C CNN "min_quantity"
	1    8050 8600
	1    0    0    -1  
$EndComp
Text Label 7050 8400 0    50   ~ 0
BATT_VOLTS
Wire Wire Line
	7050 8400 8050 8400
Wire Wire Line
	7650 7300 7650 7350
$Comp
L Device:C_Small C?
U 1 1 5DDA9C62
P 7350 7800
AR Path="/5D5B15F7/5DDA9C62" Ref="C?"  Part="1" 
AR Path="/5DDA9C62" Ref="C13"  Part="1" 
F 0 "C13" V 7100 7800 50  0000 L CNN
F 1 "100nF" V 7200 7750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7350 7800 50  0001 C CNN
F 3 "~" H 7350 7800 50  0001 C CNN
F 4 "0.017" H 7350 7800 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/mlccs-multilayer-ceramic-capacitors/6983207/" H 7350 7800 50  0001 C CNN "Purchase link"
F 6 "100" H 7350 7800 50  0001 C CNN "min_quantity"
	1    7350 7800
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5DDA9C6C
P 7650 7500
F 0 "R1" H 7720 7546 50  0000 L CNN
F 1 "10K" H 7720 7455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7580 7500 50  0001 C CNN
F 3 "~" H 7650 7500 50  0001 C CNN
F 4 "0.033" H 7650 7500 50  0001 C CNN "Cost"
F 5 "https://uk.rs-online.com/web/p/surface-mount-fixed-resistors/6784697/" H 7650 7500 50  0001 C CNN "Purchase link"
F 6 "50" H 7650 7500 50  0001 C CNN "min_quantity"
	1    7650 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 7200 8050 7300
Wire Wire Line
	8050 8000 8050 8050
Wire Wire Line
	7650 7300 8050 7300
Connection ~ 8050 7300
Wire Wire Line
	8050 7300 8050 7600
Wire Wire Line
	7450 7800 7650 7800
Wire Wire Line
	7650 7650 7650 7800
Connection ~ 7650 7800
Wire Wire Line
	7650 7800 7750 7800
Text Label 6450 7800 0    50   ~ 0
BATT_PWR_MEASURE
Wire Wire Line
	6450 7800 7250 7800
Wire Wire Line
	8050 8350 8050 8400
Connection ~ 8050 8400
Wire Wire Line
	8050 8400 8050 8450
$Comp
L pecanpico:+BATT #PWR025
U 1 1 5DDC6F2E
P 8050 7200
F 0 "#PWR025" H 8050 7050 50  0001 C CNN
F 1 "+BATT" H 8065 7373 50  0000 C CNN
F 2 "" H 8050 7200 50  0001 C CNN
F 3 "" H 8050 7200 50  0001 C CNN
	1    8050 7200
	1    0    0    -1  
$EndComp
Text Label 4100 3450 0    50   ~ 0
SOLAR_VOLTS
Wire Wire Line
	4900 3350 4100 3350
Text Label 4100 3350 0    50   ~ 0
BATT_VOLTS
Text Label 4100 3550 0    50   ~ 0
BATT_PWR_MEASURE
Wire Wire Line
	4900 3550 4100 3550
Wire Notes Line
	500  5200 2500 5200
Text Notes 750  6700 0    50   ~ 0
I2C pullup resistors
Wire Wire Line
	9250 10100 9250 9850
$Comp
L power:GND #PWR0104
U 1 1 5DEF8F7F
P 9250 10550
F 0 "#PWR0104" H 9250 10300 50  0001 C CNN
F 1 "GND" H 9255 10377 50  0000 C CNN
F 2 "" H 9250 10550 50  0001 C CNN
F 3 "" H 9250 10550 50  0001 C CNN
	1    9250 10550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 10200 9250 10550
$Comp
L pecanpico:+BATT #PWR0107
U 1 1 5DF19021
P 9250 9850
F 0 "#PWR0107" H 9250 9700 50  0001 C CNN
F 1 "+BATT" H 9265 10023 50  0000 C CNN
F 2 "" H 9250 9850 50  0001 C CNN
F 3 "" H 9250 9850 50  0001 C CNN
	1    9250 9850
	1    0    0    -1  
$EndComp
$Comp
L flight-computer:SENSOR_VCC #PWR0109
U 1 1 5DBE7B3F
P 13400 5400
F 0 "#PWR0109" H 13400 5250 50  0001 C CNN
F 1 "SENSOR_VCC" H 13400 5550 50  0000 C CNN
F 2 "" H 13400 5400 50  0001 C CNN
F 3 "" H 13400 5400 50  0001 C CNN
	1    13400 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 7200 10450 8050
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 5DC88318
P 13550 9450
F 0 "J6" H 13630 9492 50  0000 L CNN
F 1 "ICSS LOGO" H 13630 9401 50  0000 L CNN
F 2 "flight-computer:ICSS_Logo" H 13550 9450 50  0001 C CNN
F 3 "~" H 13550 9450 50  0001 C CNN
	1    13550 9450
	-1   0    0    1   
$EndComp
NoConn ~ 13750 9450
Text Notes 13050 9750 0    50   ~ 0
ICSS Logo placeholder\n
Wire Wire Line
	3150 9450 3050 9450
Wire Wire Line
	3050 9450 3050 9350
Connection ~ 3050 9050
Wire Wire Line
	3150 9350 3050 9350
Connection ~ 3050 9350
Wire Wire Line
	3050 9350 3050 9050
Wire Wire Line
	3150 9250 2900 9250
Wire Wire Line
	2900 9250 2900 9900
Wire Wire Line
	3150 9150 2900 9150
Wire Wire Line
	2900 9150 2900 9250
Connection ~ 2900 9250
Wire Wire Line
	3150 9550 3150 9900
$Comp
L power:GND #PWR0116
U 1 1 5DD2A631
P 3150 9900
F 0 "#PWR0116" H 3150 9650 50  0001 C CNN
F 1 "GND" H 3155 9727 50  0000 C CNN
F 2 "" H 3150 9900 50  0001 C CNN
F 3 "" H 3150 9900 50  0001 C CNN
	1    3150 9900
	1    0    0    -1  
$EndComp
Text Notes 2550 8300 0    50   ~ 0
Output voltage is set to 3V, by setting the VSEL values
Wire Wire Line
	4050 9850 4050 9800
$Comp
L flight-computer:SENSOR_VCC #PWR0110
U 1 1 5DBE4A13
P 11800 7350
F 0 "#PWR0110" H 11800 7200 50  0001 C CNN
F 1 "SENSOR_VCC" H 11800 7500 50  0000 C CNN
F 2 "" H 11800 7350 50  0001 C CNN
F 3 "" H 11800 7350 50  0001 C CNN
	1    11800 7350
	1    0    0    -1  
$EndComp
$Comp
L flight-computer:SENSOR_VCC #PWR0117
U 1 1 5DDF39D8
P 4050 9800
F 0 "#PWR0117" H 4050 9650 50  0001 C CNN
F 1 "SENSOR_VCC" H 4067 9973 50  0000 C CNN
F 2 "" H 4050 9800 50  0001 C CNN
F 3 "" H 4050 9800 50  0001 C CNN
	1    4050 9800
	1    0    0    -1  
$EndComp
NoConn ~ 13000 7650
NoConn ~ 6700 3650
NoConn ~ 6700 3950
Wire Wire Line
	13000 7750 11800 7750
Text Label 7350 3850 2    50   ~ 0
GPS_TIMEPULSE
Wire Wire Line
	6700 3850 7350 3850
NoConn ~ 6700 3150
Wire Wire Line
	4900 3650 4100 3650
Wire Wire Line
	4900 3750 4100 3750
Text Label 4100 3650 0    50   ~ 0
USART1_TX
Text Label 4100 3750 0    50   ~ 0
USART1_RX
$Comp
L Connector_Generic:Conn_01x10 J1
U 1 1 5DE48AA3
P 1150 1550
F 0 "J1" H 1068 2167 50  0000 C CNN
F 1 "Conn_01x10" H 1068 2076 50  0000 C CNN
F 2 "pico_tracker:10Pad" H 1150 1550 50  0001 C CNN
F 3 "~" H 1150 1550 50  0001 C CNN
	1    1150 1550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1350 2050 1650 2050
Wire Wire Line
	4550 5250 3600 5250
Connection ~ 4550 5250
Text Label 3600 5250 0    50   ~ 0
BOOT0
Text Label 1650 2050 2    50   ~ 0
BOOT0
Wire Wire Line
	1350 1350 1850 1350
Wire Wire Line
	1850 1350 1850 1200
$Comp
L power:VCC #PWR0118
U 1 1 5DEB26D7
P 1850 1200
F 0 "#PWR0118" H 1850 1050 50  0001 C CNN
F 1 "VCC" H 1867 1373 50  0000 C CNN
F 2 "" H 1850 1200 50  0001 C CNN
F 3 "" H 1850 1200 50  0001 C CNN
	1    1850 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1450 1900 1450
Wire Wire Line
	1900 1450 1900 1500
$Comp
L power:GND #PWR?
U 1 1 5DED958E
P 1900 1500
AR Path="/5D5B15F7/5DED958E" Ref="#PWR?"  Part="1" 
AR Path="/5DED958E" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 1900 1250 50  0001 C CNN
F 1 "GND" H 1905 1327 50  0000 C CNN
F 2 "" H 1900 1500 50  0001 C CNN
F 3 "" H 1900 1500 50  0001 C CNN
	1    1900 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 1550 1800 1750
Wire Wire Line
	1800 1750 2050 1750
Wire Wire Line
	1350 1550 1800 1550
Wire Wire Line
	2050 1200 2050 1750
Wire Wire Line
	1350 1250 1750 1250
Wire Wire Line
	1350 1150 1750 1150
Text Label 1750 1150 2    50   ~ 0
USART1_RX
Text Label 1750 1250 2    50   ~ 0
USART1_TX
NoConn ~ 13600 6650
Wire Wire Line
	5900 2450 5900 2150
$Comp
L power:VCC #PWR07
U 1 1 5E3D0D5D
P 5900 2150
F 0 "#PWR07" H 5900 2000 50  0001 C CNN
F 1 "VCC" H 5917 2323 50  0000 C CNN
F 2 "" H 5900 2150 50  0001 C CNN
F 3 "" H 5900 2150 50  0001 C CNN
	1    5900 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 5E3DC2E6
P 8450 5700
F 0 "J7" H 8530 5742 50  0000 L CNN
F 1 "Conn_01x01" H 8530 5651 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8450 5700 50  0001 C CNN
F 3 "~" H 8450 5700 50  0001 C CNN
	1    8450 5700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 5E3DCD54
P 8450 5900
F 0 "J8" H 8530 5942 50  0000 L CNN
F 1 "Conn_01x01" H 8530 5851 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8450 5900 50  0001 C CNN
F 3 "~" H 8450 5900 50  0001 C CNN
	1    8450 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 5700 8200 5700
Wire Wire Line
	8200 5700 8200 5900
Wire Wire Line
	8250 5900 8200 5900
Connection ~ 8200 5900
Wire Wire Line
	8200 5900 8200 6200
$Comp
L power:GND #PWR?
U 1 1 5E3F8BA2
P 8200 6200
AR Path="/5D5B15F7/5E3F8BA2" Ref="#PWR?"  Part="1" 
AR Path="/5E3F8BA2" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 8200 5950 50  0001 C CNN
F 1 "GND" H 8205 6027 50  0000 C CNN
F 2 "" H 8200 6200 50  0001 C CNN
F 3 "" H 8200 6200 50  0001 C CNN
	1    8200 6200
	1    0    0    -1  
$EndComp
NoConn ~ 14200 7150
NoConn ~ 8350 6850
Wire Wire Line
	6700 5250 8150 5250
Wire Wire Line
	12600 2000 12400 2000
Wire Wire Line
	12400 2000 12400 2350
Connection ~ 12400 2350
Wire Wire Line
	12400 2350 12600 2350
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 5DF9440B
P 7950 7800
F 0 "Q1" H 8156 7846 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 8156 7755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8150 7900 50  0001 C CNN
F 3 "~" H 7950 7800 50  0001 C CNN
	1    7950 7800
	1    0    0    1   
$EndComp
Text Label 7350 3750 2    50   ~ 0
GPS_EXTINT
Wire Wire Line
	7350 3750 6700 3750
Wire Wire Line
	12300 7550 13000 7550
Text Label 12300 7550 0    50   ~ 0
GPS_EXTINT
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "araBoard-ad5933"
Date "2020-01-13"
Rev "v0.1"
Comp "araCreate"
Comment1 "Open Source Hardware Impedance Analyser with Analog Devices AD5933"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ANALOG-DEVICES:AD5933YRSZ-ND U?
U 1 1 5E1C7BE9
P 4550 4050
F 0 "U?" H 4550 5017 50  0000 C CNN
F 1 "AD5933YRSZ-ND" H 4550 4926 50  0000 C CNN
F 2 "SOP65P780X200-16N" H 4550 4050 50  0001 L BNN
F 3 "Analog Devices" H 4550 4050 50  0001 L BNN
F 4 "F" H 4550 4050 50  0001 L BNN "Field4"
F 5 "IPC-7351B" H 4550 4050 50  0001 L BNN "Field5"
	1    4550 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 5E1C8BA4
P 4750 2450
F 0 "C?" H 4841 2496 50  0000 L CNN
F 1 "0.1uF" H 4841 2405 50  0000 L CNN
F 2 "" H 4750 2450 50  0001 C CNN
F 3 "~" H 4750 2450 50  0001 C CNN
	1    4750 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 5E1CA28B
P 4350 2450
F 0 "C?" H 4441 2496 50  0000 L CNN
F 1 "10uF" H 4441 2405 50  0000 L CNN
F 2 "" H 4350 2450 50  0001 C CNN
F 3 "~" H 4350 2450 50  0001 C CNN
	1    4350 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2350 4750 2300
Wire Wire Line
	4750 2300 5250 2300
Wire Wire Line
	5250 2300 5250 3350
Wire Wire Line
	5250 3350 5150 3350
Wire Wire Line
	4750 2300 4350 2300
Wire Wire Line
	4350 2300 4350 2350
Connection ~ 4750 2300
Wire Wire Line
	4350 2550 4350 2650
Wire Wire Line
	4350 2650 4750 2650
Wire Wire Line
	4750 2650 4750 2550
$Comp
L Connector_Generic:Conn_01x08 J?
U 1 1 5E1F6E3A
P 2100 3250
F 0 "J?" H 2018 2625 50  0000 C CNN
F 1 "Conn_01x08" H 2018 2716 50  0000 C CNN
F 2 "" H 2100 3250 50  0001 C CNN
F 3 "~" H 2100 3250 50  0001 C CNN
	1    2100 3250
	-1   0    0    1   
$EndComp
Text GLabel 2500 2850 2    50   Input ~ 0
VCC
Wire Wire Line
	2300 2850 2400 2850
Wire Wire Line
	2300 2950 2400 2950
Wire Wire Line
	2400 2950 2400 2850
Connection ~ 2400 2850
Wire Wire Line
	2400 2850 2500 2850
Text GLabel 2500 3050 2    50   Input ~ 0
GND
Text GLabel 2500 3250 2    50   Input ~ 0
SDA
Text GLabel 2500 3450 2    50   Input ~ 0
SCL
Wire Wire Line
	2300 3050 2400 3050
Wire Wire Line
	2500 3250 2400 3250
Wire Wire Line
	2300 3450 2400 3450
Wire Wire Line
	2300 3350 2400 3350
Wire Wire Line
	2400 3350 2400 3250
Connection ~ 2400 3250
Wire Wire Line
	2400 3250 2300 3250
Wire Wire Line
	2300 3150 2400 3150
Wire Wire Line
	2400 3150 2400 3050
Connection ~ 2400 3050
Wire Wire Line
	2400 3050 2500 3050
Wire Wire Line
	2300 3550 2400 3550
Wire Wire Line
	2400 3550 2400 3450
Connection ~ 2400 3450
Wire Wire Line
	2400 3450 2500 3450
Text GLabel 4100 2300 0    50   Input ~ 0
VCC
Wire Wire Line
	4100 2300 4350 2300
Connection ~ 4350 2300
Text GLabel 4100 2650 0    50   Input ~ 0
GND
Wire Wire Line
	4100 2650 4350 2650
Connection ~ 4350 2650
$Comp
L Device:CP1_Small C?
U 1 1 5E1FA959
P 5800 3050
F 0 "C?" H 5891 3096 50  0000 L CNN
F 1 "0.1uF" H 5891 3005 50  0000 L CNN
F 2 "" H 5800 3050 50  0001 C CNN
F 3 "~" H 5800 3050 50  0001 C CNN
	1    5800 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C?
U 1 1 5E1FBDFD
P 6300 3050
F 0 "C?" H 6391 3096 50  0000 L CNN
F 1 "10uF" H 6391 3005 50  0000 L CNN
F 2 "" H 6300 3050 50  0001 C CNN
F 3 "~" H 6300 3050 50  0001 C CNN
	1    6300 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3450 5400 3450
Wire Wire Line
	5400 3450 5400 2850
Wire Wire Line
	5400 2850 5550 2850
Wire Wire Line
	5150 3550 5550 3550
Wire Wire Line
	5550 3550 5550 2850
Wire Wire Line
	5800 3150 5800 3250
Wire Wire Line
	5800 3250 6300 3250
Wire Wire Line
	6300 3250 6300 3150
Wire Wire Line
	5800 2950 5800 2850
Wire Wire Line
	5800 2850 5550 2850
Connection ~ 5550 2850
Wire Wire Line
	5800 2850 6300 2850
Wire Wire Line
	6300 2850 6300 2950
Connection ~ 5800 2850
Text GLabel 6700 3250 2    50   Input ~ 0
GND
Wire Wire Line
	6700 3250 6300 3250
Connection ~ 6300 3250
Text GLabel 6700 2850 2    50   Input ~ 0
VCC3V0
Wire Wire Line
	6300 2850 6700 2850
Connection ~ 6300 2850
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "2021-08-19"
Rev "0.1.0"
Comp "Breaz"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 611ED4E7
P 9400 5000
F 0 "J1" H 9428 4976 50  0000 L CNN
F 1 "ssd1306-oled" H 9428 4885 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 9400 5000 50  0001 C CNN
F 3 "~" H 9400 5000 50  0001 C CNN
	1    9400 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 611F0609
P 7250 3850
F 0 "R1" H 7309 3896 50  0000 L CNN
F 1 "10K" H 7309 3805 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7250 3850 50  0001 C CNN
F 3 "~" H 7250 3850 50  0001 C CNN
	1    7250 3850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 611EB16E
P 7250 3450
F 0 "SW1" V 7296 3402 50  0000 R CNN
F 1 "button" V 7205 3402 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 7250 3650 50  0001 C CNN
F 3 "~" H 7250 3650 50  0001 C CNN
	1    7250 3450
	0    1    1    0   
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 6120A00A
P 8100 3850
F 0 "A1" H 8100 2761 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 8100 2670 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 8100 3850 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 8100 3850 50  0001 C CNN
	1    8100 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3650 7600 3650
Wire Wire Line
	8300 2850 8300 2600
Wire Wire Line
	8300 2600 7250 2600
Wire Wire Line
	7250 2600 7250 3250
Wire Wire Line
	7250 3650 7250 3750
Connection ~ 7250 3650
Wire Wire Line
	7250 3950 7250 5200
Wire Wire Line
	7250 5200 8100 5200
Wire Wire Line
	8100 5200 8100 4850
Connection ~ 8100 5200
Wire Wire Line
	9200 5100 9000 5100
Wire Wire Line
	9000 5100 9000 2600
Wire Wire Line
	9000 2600 8300 2600
Connection ~ 8300 2600
Wire Wire Line
	8600 4250 9100 4250
Wire Wire Line
	9100 4250 9100 5000
Wire Wire Line
	9200 4350 8600 4350
NoConn ~ 8000 2850
NoConn ~ 8200 2850
NoConn ~ 8600 3250
NoConn ~ 8600 3350
NoConn ~ 8600 3650
NoConn ~ 8600 3850
NoConn ~ 8600 3950
NoConn ~ 8600 4050
NoConn ~ 8600 4150
NoConn ~ 8600 4450
NoConn ~ 8600 4550
NoConn ~ 7600 4550
NoConn ~ 7600 4450
NoConn ~ 7600 4350
NoConn ~ 7600 4250
NoConn ~ 7600 4150
NoConn ~ 7600 4050
NoConn ~ 7600 3950
NoConn ~ 7600 3850
NoConn ~ 7600 3750
NoConn ~ 7600 3550
NoConn ~ 7600 3450
NoConn ~ 7600 3350
NoConn ~ 7600 3250
Wire Wire Line
	8200 4850 8200 5200
Connection ~ 8200 5200
Wire Wire Line
	8200 5200 9200 5200
Wire Wire Line
	9100 5000 9200 5000
Wire Wire Line
	8100 5200 8200 5200
Wire Wire Line
	9200 4350 9200 4900
$Comp
L power:+5V #PWR0101
U 1 1 6121C563
P 8300 2400
F 0 "#PWR0101" H 8300 2250 50  0001 C CNN
F 1 "+5V" H 8315 2573 50  0000 C CNN
F 2 "" H 8300 2400 50  0001 C CNN
F 3 "" H 8300 2400 50  0001 C CNN
	1    8300 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 2600 8300 2400
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 612222DB
P 8100 5400
F 0 "#FLG0101" H 8100 5475 50  0001 C CNN
F 1 "PWR_FLAG" H 8100 5573 50  0000 C CNN
F 2 "" H 8100 5400 50  0001 C CNN
F 3 "~" H 8100 5400 50  0001 C CNN
	1    8100 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 5400 8100 5200
$EndSCHEMATC
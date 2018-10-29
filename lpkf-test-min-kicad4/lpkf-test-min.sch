EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr User 5906 5906
encoding utf-8
Sheet 1 1
Title "LPKF Test Min"
Date "2018-07-18"
Rev "v0.1"
Comp "www.aravinth.info"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Conn_01x04 J2
U 1 1 5B4F5827
P 3800 2500
F 0 "J2" H 3800 2700 50  0000 C CNN
F 1 "RIGHT" H 3800 2200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm_SMD_Pin1Left" H 3800 2500 50  0001 C CNN
F 3 "" H 3800 2500 50  0001 C CNN
	1    3800 2500
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J1
U 1 1 5B4F5873
P 2100 2600
F 0 "J1" H 2100 2800 50  0000 C CNN
F 1 "LEFT" H 2100 2300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 2100 2600 50  0001 C CNN
F 3 "" H 2100 2600 50  0001 C CNN
	1    2100 2600
	-1   0    0    1   
$EndComp
$Comp
L R_Small R1
U 1 1 5B4F59A9
P 2900 2400
F 0 "R1" H 2930 2420 50  0000 L CNN
F 1 "1K" H 2930 2360 50  0000 L CNN
F 2 "Resistors_SMD:R_0201" H 2900 2400 50  0001 C CNN
F 3 "" H 2900 2400 50  0001 C CNN
	1    2900 2400
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R2
U 1 1 5B4F59F6
P 2900 2500
F 0 "R2" H 2930 2520 50  0000 L CNN
F 1 "1K" H 2930 2460 50  0000 L CNN
F 2 "Resistors_SMD:R_0402" H 2900 2500 50  0001 C CNN
F 3 "" H 2900 2500 50  0001 C CNN
	1    2900 2500
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R3
U 1 1 5B4F5A10
P 2900 2600
F 0 "R3" H 2930 2620 50  0000 L CNN
F 1 "1K" H 2930 2560 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" H 2900 2600 50  0001 C CNN
F 3 "" H 2900 2600 50  0001 C CNN
	1    2900 2600
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R4
U 1 1 5B4F5A2F
P 2900 2700
F 0 "R4" H 2930 2720 50  0000 L CNN
F 1 "1K" H 2930 2660 50  0000 L CNN
F 2 "Resistors_SMD:R_0805" H 2900 2700 50  0001 C CNN
F 3 "" H 2900 2700 50  0001 C CNN
	1    2900 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2300 2400 2800 2400
Wire Wire Line
	2800 2500 2300 2500
Wire Wire Line
	2300 2600 2800 2600
Wire Wire Line
	2300 2700 2800 2700
Wire Wire Line
	3000 2400 3600 2400
Wire Wire Line
	3600 2500 3000 2500
Wire Wire Line
	3000 2600 3600 2600
Wire Wire Line
	3600 2700 3000 2700
$EndSCHEMATC

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
LIBS:nrf24-schematic-lib
LIBS:nrf24-breakout-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "nRF24 Breakout"
Date "2016-11-27"
Rev "0.1"
Comp "AravInfoways"
Comment1 "Aravinth"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X08 P1
U 1 1 583B2DE2
P 4150 3550
F 0 "P1" H 4150 4000 50  0000 C CNN
F 1 "CONN_01X08" V 4250 3550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 4150 3550 50  0001 C CNN
F 3 "" H 4150 3550 50  0000 C CNN
	1    4150 3550
	1    0    0    -1  
$EndComp
$Comp
L nRF24 U1
U 1 1 583B49F4
P 2550 3500
F 0 "U1" H 2550 2850 60  0000 C CNN
F 1 "nRF24" H 2550 3500 60  0000 C CNN
F 2 "nrf24-footprint:nrf24" H 2500 3400 60  0001 C CNN
F 3 "" H 2500 3400 60  0001 C CNN
	1    2550 3500
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 588E615B
P 3550 4200
F 0 "C1" H 3575 4300 50  0000 L CNN
F 1 "10uF" H 3575 4100 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D10.0mm_P5.00mm" H 3550 4200 50  0001 C CNN
F 3 "" H 3550 4200 50  0000 C CNN
	1    3550 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 3200 3950 3200
Wire Wire Line
	3950 3300 3150 3300
Wire Wire Line
	3150 3400 3950 3400
Wire Wire Line
	3150 3500 3950 3500
Wire Wire Line
	3150 3600 3950 3600
Wire Wire Line
	3150 3700 3950 3700
Wire Wire Line
	3150 3800 3950 3800
Wire Wire Line
	3150 3900 3950 3900
Wire Wire Line
	3400 4200 3300 4200
Wire Wire Line
	3300 4200 3300 3200
Connection ~ 3300 3200
Wire Wire Line
	3700 4200 3850 4200
Wire Wire Line
	3850 4200 3850 3900
Connection ~ 3850 3900
$EndSCHEMATC

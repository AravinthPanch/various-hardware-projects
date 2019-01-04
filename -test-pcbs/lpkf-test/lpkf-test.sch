EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5C2CDECA
P 5550 3750
F 0 "J1" H 5630 3742 50  0000 L CNN
F 1 "Conn_01x04" H 5630 3651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5550 3750 50  0001 C CNN
F 3 "~" H 5550 3750 50  0001 C CNN
	1    5550 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5C2CDFAB
P 5000 3650
F 0 "R1" V 5000 3100 50  0000 C CNN
F 1 "R_Small" V 5000 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5000 3650 50  0001 C CNN
F 3 "~" H 5000 3650 50  0001 C CNN
	1    5000 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5C2CDFE1
P 5000 3750
F 0 "R2" V 5000 3200 50  0000 C CNN
F 1 "R_Small" V 5000 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5000 3750 50  0001 C CNN
F 3 "~" H 5000 3750 50  0001 C CNN
	1    5000 3750
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5C2CDFF5
P 5000 3850
F 0 "R3" V 5000 3300 50  0000 C CNN
F 1 "R_Small" V 5000 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 5000 3850 50  0001 C CNN
F 3 "~" H 5000 3850 50  0001 C CNN
	1    5000 3850
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5C2CE00D
P 5000 3950
F 0 "R4" V 5000 3400 50  0000 C CNN
F 1 "R_Small" V 5000 3650 50  0000 C CNN
F 2 "Resistor_SMD:R_0201_0603Metric" H 5000 3950 50  0001 C CNN
F 3 "~" H 5000 3950 50  0001 C CNN
	1    5000 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 3650 5350 3650
Wire Wire Line
	5100 3750 5350 3750
Wire Wire Line
	5100 3850 5350 3850
Wire Wire Line
	5100 3950 5350 3950
$EndSCHEMATC

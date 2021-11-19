EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 7874 7874
encoding utf-8
Sheet 1 1
Title "ECE398AA Midterm Project"
Date "2021-11-19"
Rev ""
Comp "UIUC ECE398AA"
Comment1 "Gally Huang"
Comment2 "Zhuxuan Liu"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L HD44780:HD44780 LCD1
U 1 1 61999A25
P 4800 1150
F 0 "LCD1" V 5467 100 50  0000 C CNN
F 1 "HD44780" V 5376 100 50  0000 C CNN
F 2 "Display:RC1602A" H 4800 1150 50  0001 L BNN
F 3 "" H 4800 1150 50  0001 L BNN
F 4 "5V" H 4800 1150 50  0001 L BNN "VOLTAGE"
F 5 "N/A" H 4800 1150 50  0001 L BNN "MGF#"
	1    4800 1150
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_POT_US LCDResistor1
U 1 1 619AA62E
P 4850 1550
F 0 "LCDResistor1" H 4783 1596 50  0000 R CNN
F 1 "R_POT_US" H 4783 1505 50  0000 R CNN
F 2 "Resistor_THT:R_Array_SIP4" H 4850 1550 50  0001 C CNN
F 3 "~" H 4850 1550 50  0001 C CNN
	1    4850 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2100 6300 2100
Wire Wire Line
	6300 2100 6300 1250
Wire Wire Line
	6200 1250 6200 2200
Wire Wire Line
	6200 2200 4350 2200
Wire Wire Line
	6100 1250 6100 2300
Wire Wire Line
	6100 2300 4350 2300
Wire Wire Line
	4350 2400 6000 2400
Wire Wire Line
	6000 2400 6000 1250
Wire Wire Line
	6800 1800 6800 1250
Wire Wire Line
	6700 1250 6700 1900
Wire Wire Line
	6700 1900 6400 1900
Wire Wire Line
	4350 2500 5400 2500
Wire Wire Line
	5400 2500 5400 1250
Wire Wire Line
	4350 2600 5200 2600
Wire Wire Line
	5200 2600 5200 1250
Wire Wire Line
	5300 1250 5300 1900
Connection ~ 5300 1900
Wire Wire Line
	4850 1700 4850 1900
Connection ~ 4850 1900
Wire Wire Line
	4850 1900 4350 1900
Wire Wire Line
	5000 1550 6500 1550
Wire Wire Line
	6500 1550 6500 1250
Wire Wire Line
	5300 1900 5100 1900
Wire Wire Line
	5000 1250 5000 1400
Wire Wire Line
	5000 1400 5100 1400
Connection ~ 5100 1900
Wire Wire Line
	5100 1900 4850 1900
Wire Wire Line
	4900 1250 4900 1400
Wire Wire Line
	4900 1400 4850 1400
Wire Wire Line
	4850 1400 4350 1400
Connection ~ 4850 1400
$Comp
L Device:LED D1
U 1 1 619B9407
P 1250 2400
F 0 "D1" H 1243 2617 50  0000 C CNN
F 1 "Yellow (House Lights)" H 1243 2526 50  0000 C CNN
F 2 "LED_THT:LED_D1.8mm_W1.8mm_H2.4mm_Horizontal_O1.27mm_Z1.6mm" H 1250 2400 50  0001 C CNN
F 3 "~" H 1250 2400 50  0001 C CNN
	1    1250 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 619C13C4
P 1250 2750
F 0 "D2" H 1243 2967 50  0000 C CNN
F 1 "Yellow (House Lights)" H 1243 2876 50  0000 C CNN
F 2 "LED_THT:LED_D1.8mm_W1.8mm_H2.4mm_Horizontal_O1.27mm_Z1.6mm" H 1250 2750 50  0001 C CNN
F 3 "~" H 1250 2750 50  0001 C CNN
	1    1250 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 619C1DC9
P 1250 3100
F 0 "D3" H 1250 3300 50  0000 C CNN
F 1 "Yellow (House Lights)" H 1243 3226 50  0000 C CNN
F 2 "LED_THT:LED_D1.8mm_W1.8mm_H2.4mm_Horizontal_O1.27mm_Z1.6mm" H 1250 3100 50  0001 C CNN
F 3 "~" H 1250 3100 50  0001 C CNN
	1    1250 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 619C54B5
P 1900 2400
F 0 "R1" V 1695 2400 50  0000 C CNN
F 1 "330 Ω" V 1786 2400 50  0000 C CNN
F 2 "Resistor_THT:R_Array_SIP4" V 1940 2390 50  0001 C CNN
F 3 "~" H 1900 2400 50  0001 C CNN
	1    1900 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 2400 1750 2400
Wire Wire Line
	2100 2500 2100 2750
Wire Wire Line
	2100 2750 2050 2750
Wire Wire Line
	2200 2600 2200 3100
Wire Wire Line
	2200 3100 2050 3100
Wire Wire Line
	1750 2750 1400 2750
Wire Wire Line
	1400 3100 1750 3100
Wire Wire Line
	1100 3100 550  3100
Wire Wire Line
	550  3100 550  2750
Wire Wire Line
	1100 2400 550  2400
Connection ~ 550  2400
Wire Wire Line
	550  2400 550  1900
Wire Wire Line
	1100 2750 550  2750
Connection ~ 550  2750
Wire Wire Line
	550  2750 550  2400
Wire Wire Line
	4350 2700 4400 2700
Wire Wire Line
	2600 2600 2200 2600
Wire Wire Line
	2600 2500 2100 2500
Wire Wire Line
	2600 2400 2050 2400
$Comp
L 4N32:4N32 U2
U 1 1 619F044B
P 5200 3150
F 0 "U2" H 5200 3620 50  0000 C CNN
F 1 "H11B1" H 5200 3529 50  0000 C CNN
F 2 "DIP762W50P254L730H410Q6" H 5200 3150 50  0001 L BNN
F 3 "" H 5200 3150 50  0001 L BNN
F 4 "vishay" H 5200 3150 50  0001 L BNN "MANUFACTURER"
	1    5200 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2700 4400 2950
Wire Wire Line
	4400 2950 4600 2950
Wire Wire Line
	4600 3250 4000 3250
Wire Wire Line
	4000 3250 4000 3000
Wire Wire Line
	5800 3450 5800 3850
Wire Wire Line
	5800 3850 4000 3850
Wire Wire Line
	4000 3850 4000 3250
Connection ~ 4000 3250
$Comp
L Motor:Fan DCMotor1
U 1 1 619D0D7F
P 6000 3150
F 0 "DCMotor1" V 5705 3200 50  0000 C CNN
F 1 "Fan1" V 5796 3200 50  0000 C CNN
F 2 "Crystal:Crystal_AT310_D3.0mm_L10.0mm_Horizontal" H 6000 3160 50  0001 C CNN
F 3 "~" H 6000 3160 50  0001 C CNN
	1    6000 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 3000 4100 3950
Wire Wire Line
	4100 3950 6300 3950
Wire Wire Line
	6300 3950 6300 3150
NoConn ~ 5800 2950
NoConn ~ 4600 3450
$Comp
L Device:LED D4
U 1 1 61A3E1D0
P 1250 1200
F 0 "D4" H 1243 1417 50  0000 C CNN
F 1 "Door Open (Green)" H 1243 1326 50  0000 C CNN
F 2 "LED_THT:LED_D1.8mm_W1.8mm_H2.4mm_Horizontal_O1.27mm_Z1.6mm" H 1250 1200 50  0001 C CNN
F 3 "~" H 1250 1200 50  0001 C CNN
	1    1250 1200
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 61A3FDCB
P 1250 1600
F 0 "D5" H 1243 1817 50  0000 C CNN
F 1 "Door Close (Red)" H 1243 1726 50  0000 C CNN
F 2 "LED_THT:LED_D1.8mm_W1.8mm_H2.4mm_Horizontal_O1.27mm_Z1.6mm" H 1250 1600 50  0001 C CNN
F 3 "~" H 1250 1600 50  0001 C CNN
	1    1250 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 61A44B66
P 1900 2750
F 0 "R2" V 1695 2750 50  0000 C CNN
F 1 "330 Ω" V 1786 2750 50  0000 C CNN
F 2 "Resistor_THT:R_Array_SIP4" V 1940 2740 50  0001 C CNN
F 3 "~" H 1900 2750 50  0001 C CNN
	1    1900 2750
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R3
U 1 1 61A45E98
P 1900 3100
F 0 "R3" V 1695 3100 50  0000 C CNN
F 1 "330 Ω" V 1786 3100 50  0000 C CNN
F 2 "Resistor_THT:R_Array_SIP4" V 1940 3090 50  0001 C CNN
F 3 "~" H 1900 3100 50  0001 C CNN
	1    1900 3100
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R4
U 1 1 61A47DC5
P 1900 1200
F 0 "R4" V 1695 1200 50  0000 C CNN
F 1 "330 Ω" V 1786 1200 50  0000 C CNN
F 2 "Resistor_THT:R_Array_SIP4" V 1940 1190 50  0001 C CNN
F 3 "~" H 1900 1200 50  0001 C CNN
	1    1900 1200
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R5
U 1 1 61A492D5
P 1900 1600
F 0 "R5" V 1695 1600 50  0000 C CNN
F 1 "330 Ω" V 1786 1600 50  0000 C CNN
F 2 "Resistor_THT:R_Array_SIP4" V 1940 1590 50  0001 C CNN
F 3 "~" H 1900 1600 50  0001 C CNN
	1    1900 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	2050 1200 2300 1200
Wire Wire Line
	2300 1200 2300 2200
Wire Wire Line
	2300 2200 2600 2200
Wire Wire Line
	2150 2300 2150 1600
Wire Wire Line
	2150 1600 2050 1600
Wire Wire Line
	2150 2300 2600 2300
Wire Wire Line
	1750 1200 1400 1200
Wire Wire Line
	1400 1600 1750 1600
Wire Wire Line
	550  1600 550  1900
Connection ~ 550  1900
Wire Wire Line
	550  1600 1100 1600
Wire Wire Line
	1100 1200 550  1200
Wire Wire Line
	550  1200 550  1600
Connection ~ 550  1600
$Comp
L Motor:Motor_Servo Door1
U 1 1 61A5C086
P 7050 2600
F 0 "Door1" H 7382 2665 50  0000 L CNN
F 1 "Motor_Servo" H 7382 2574 50  0000 L CNN
F 2 "Crystal:Crystal_AT310_D3.0mm_L10.0mm_Horizontal" H 7050 2410 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 7050 2410 50  0001 C CNN
	1    7050 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 3950 6600 3950
Wire Wire Line
	6500 2050 6500 2000
Wire Wire Line
	6500 2000 4350 2000
Connection ~ 6300 3950
Wire Wire Line
	6600 3950 6600 2150
Wire Wire Line
	6400 2250 6400 1900
Connection ~ 6400 1900
Wire Wire Line
	6400 1900 5300 1900
$Comp
L Midterm~Project:MSP__432 u1
U 1 1 61993804
P 2950 1850
F 0 "u1" H 3450 1900 50  0001 C CNN
F 1 "MSP__432" H 3475 2023 50  0000 C CNN
F 2 "ECE398AA Midterm Project:MSP430FR5994IPM" H 2400 1500 50  0001 C CNN
F 3 "" H 2400 1500 50  0001 C CNN
	1    2950 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 1400 5100 1900
Wire Wire Line
	4350 1800 6800 1800
Wire Wire Line
	4350 1400 4350 1800
Connection ~ 4350 1800
Wire Wire Line
	2900 3000 2900 3300
Wire Wire Line
	3000 3000 3000 3400
Wire Wire Line
	3100 3000 3100 3500
Wire Wire Line
	3200 3000 3200 3600
Wire Wire Line
	3300 3000 3300 3700
Wire Wire Line
	3400 3000 3400 3800
Wire Wire Line
	3500 3000 3500 3900
$Comp
L Switch:SW_Push SW7
U 1 1 61B120B1
P 700 4700
F 0 "SW7" H 700 4985 50  0000 C CNN
F 1 "7" H 700 4894 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 700 4900 50  0001 C CNN
F 3 "~" H 700 4900 50  0001 C CNN
	1    700  4700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW8
U 1 1 61B25620
P 1300 4700
F 0 "SW8" H 1300 4985 50  0000 C CNN
F 1 "8" H 1300 4894 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1300 4900 50  0001 C CNN
F 3 "~" H 1300 4900 50  0001 C CNN
	1    1300 4700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW9
U 1 1 61B29A69
P 1900 4700
F 0 "SW9" H 1900 4985 50  0000 C CNN
F 1 "9" H 1900 4894 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1900 4900 50  0001 C CNN
F 3 "~" H 1900 4900 50  0001 C CNN
	1    1900 4700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW#1
U 1 1 61B29A6F
P 1900 5200
F 0 "SW#1" H 1900 5485 50  0000 C CNN
F 1 "#" H 1900 5394 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1900 5400 50  0001 C CNN
F 3 "~" H 1900 5400 50  0001 C CNN
	1    1900 5200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW0
U 1 1 61B25626
P 1300 5200
F 0 "SW0" H 1300 5485 50  0000 C CNN
F 1 "0" H 1300 5394 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1300 5400 50  0001 C CNN
F 3 "~" H 1300 5400 50  0001 C CNN
	1    1300 5200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW*1
U 1 1 61B14F6C
P 700 5200
F 0 "SW*1" H 700 5485 50  0000 C CNN
F 1 "*" H 700 5394 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 700 5400 50  0001 C CNN
F 3 "~" H 700 5400 50  0001 C CNN
	1    700  5200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 61B59F3D
P 700 3700
F 0 "SW1" H 700 3985 50  0000 C CNN
F 1 "1" H 700 3894 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 700 3900 50  0001 C CNN
F 3 "~" H 700 3900 50  0001 C CNN
	1    700  3700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 61B59F43
P 1300 3700
F 0 "SW2" H 1300 3985 50  0000 C CNN
F 1 "2" H 1300 3894 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1300 3900 50  0001 C CNN
F 3 "~" H 1300 3900 50  0001 C CNN
	1    1300 3700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 61B59F49
P 1900 3700
F 0 "SW3" H 1900 3985 50  0000 C CNN
F 1 "3" H 1900 3894 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1900 3900 50  0001 C CNN
F 3 "~" H 1900 3900 50  0001 C CNN
	1    1900 3700
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW6
U 1 1 61B59F4F
P 1900 4200
F 0 "SW6" H 1900 4485 50  0000 C CNN
F 1 "6" H 1900 4394 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1900 4400 50  0001 C CNN
F 3 "~" H 1900 4400 50  0001 C CNN
	1    1900 4200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 61B59F55
P 1300 4200
F 0 "SW5" H 1300 4485 50  0000 C CNN
F 1 "5" H 1300 4394 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 1300 4400 50  0001 C CNN
F 3 "~" H 1300 4400 50  0001 C CNN
	1    1300 4200
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 61B59F5B
P 700 4200
F 0 "SW4" H 700 4485 50  0000 C CNN
F 1 "4" H 700 4394 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 700 4400 50  0001 C CNN
F 3 "~" H 700 4400 50  0001 C CNN
	1    700  4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3700 2100 3850
Connection ~ 2100 4200
Wire Wire Line
	2100 4200 2100 4350
Connection ~ 2100 4700
Connection ~ 2100 5200
Wire Wire Line
	2100 5200 2100 5350
Wire Wire Line
	2100 5350 1700 5350
Wire Wire Line
	500  5200 500  5350
Wire Wire Line
	1100 5200 1100 5350
Connection ~ 1100 5350
Wire Wire Line
	1100 5350 900  5350
Wire Wire Line
	1700 5200 1700 5350
Connection ~ 1700 5350
Wire Wire Line
	1700 5350 1100 5350
Wire Wire Line
	2100 4850 1700 4850
Connection ~ 2100 4850
Wire Wire Line
	2100 4850 2100 5200
Wire Wire Line
	2100 4700 2100 4850
Wire Wire Line
	2100 4350 1700 4350
Connection ~ 2100 4350
Wire Wire Line
	2100 4350 2100 4700
Connection ~ 2100 3850
Wire Wire Line
	2100 3850 2100 4200
Wire Wire Line
	500  3700 500  3850
Wire Wire Line
	500  3850 900  3850
Wire Wire Line
	500  4200 500  4350
Wire Wire Line
	500  4700 500  4850
Wire Wire Line
	1100 4700 1100 4850
Connection ~ 1100 4850
Wire Wire Line
	1100 4850 500  4850
Wire Wire Line
	1700 4700 1700 4850
Connection ~ 1700 4850
Wire Wire Line
	1700 4850 1100 4850
Wire Wire Line
	1700 4200 1700 4350
Connection ~ 1700 4350
Wire Wire Line
	1700 4350 1100 4350
Wire Wire Line
	1100 4200 1100 4350
Connection ~ 1100 4350
Wire Wire Line
	1100 4350 500  4350
Wire Wire Line
	1100 3700 1100 3850
Connection ~ 1100 3850
Wire Wire Line
	1700 3700 1700 3850
Wire Wire Line
	1100 3850 1500 3850
Connection ~ 1700 3850
Wire Wire Line
	1700 3850 2100 3850
Wire Wire Line
	900  3850 900  3700
Wire Wire Line
	1100 3850 900  3850
Connection ~ 900  3850
Wire Wire Line
	900  4200 900  3850
Connection ~ 900  5350
Wire Wire Line
	900  5350 500  5350
Connection ~ 900  4200
Wire Wire Line
	900  4200 900  4700
Connection ~ 900  4700
Wire Wire Line
	900  4700 900  5200
Connection ~ 900  5200
Wire Wire Line
	900  5200 900  5350
Wire Wire Line
	1700 5350 1700 5800
Wire Wire Line
	2100 3850 2200 3850
Wire Wire Line
	2200 3850 2200 3300
Wire Wire Line
	2200 3300 2900 3300
Wire Wire Line
	2300 3400 2300 4350
Wire Wire Line
	2300 4350 2100 4350
Wire Wire Line
	2300 3400 3000 3400
Wire Wire Line
	3100 3500 2400 3500
Wire Wire Line
	2400 3500 2400 4850
Wire Wire Line
	2400 4850 2100 4850
Wire Wire Line
	2100 5350 2500 5350
Wire Wire Line
	2500 5350 2500 3600
Wire Wire Line
	2500 3600 3200 3600
Connection ~ 2100 5350
Wire Wire Line
	2650 3700 2650 5500
Wire Wire Line
	2800 5650 2800 3800
Wire Wire Line
	2800 3800 3400 3800
Wire Wire Line
	2950 5800 2950 3900
Wire Wire Line
	2950 3900 3500 3900
NoConn ~ 3550 5100
Wire Wire Line
	2650 3700 3300 3700
Wire Wire Line
	3600 4100 3600 3000
$Comp
L Sensor_Temperature:TMP36xS U1
U 1 1 61C50B44
P 3550 4600
F 0 "U1" H 4094 4646 50  0000 L CNN
F 1 "TMP36xS" H 4094 4555 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 3550 4150 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf" H 3550 4600 50  0001 C CNN
	1    3550 4600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R6
U 1 1 61D55090
P 4100 4100
F 0 "R6" H 4168 4146 50  0000 L CNN
F 1 "300 Ω" H 4168 4055 50  0000 L CNN
F 2 "Resistor_THT:R_Array_SIP4" V 4140 4090 50  0001 C CNN
F 3 "~" H 4100 4100 50  0001 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
Connection ~ 4100 3950
Wire Wire Line
	4100 4250 4100 5250
Wire Wire Line
	3150 5250 3150 4600
$Comp
L Switch:SW_Push LightToggle1
U 1 1 61D81EB5
P 4600 4400
F 0 "LightToggle1" H 4600 4685 50  0000 C CNN
F 1 "SW_Push" H 4600 4594 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 4600 4600 50  0001 C CNN
F 3 "~" H 4600 4600 50  0001 C CNN
	1    4600 4400
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push FanToggle1
U 1 1 61D83D59
P 4600 4850
F 0 "FanToggle1" H 4600 5135 50  0000 C CNN
F 1 "SW_Push" H 4600 5044 50  0000 C CNN
F 2 "Button_Switch_THT:Push_E-Switch_KS01Q01" H 4600 5050 50  0001 C CNN
F 3 "~" H 4600 5050 50  0001 C CNN
	1    4600 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3850 3950 4400
Connection ~ 3950 4400
Wire Wire Line
	3950 4400 3950 4500
Wire Wire Line
	3950 4850 3950 4600
Connection ~ 3950 4600
Wire Wire Line
	4800 4400 5000 4400
Wire Wire Line
	5000 4400 5000 3750
Wire Wire Line
	5000 3750 3700 3750
Wire Wire Line
	3700 3750 3700 3000
Wire Wire Line
	3800 3700 5100 3700
Wire Wire Line
	5100 3700 5100 4850
Wire Wire Line
	5100 4850 4800 4850
Wire Wire Line
	3800 3000 3800 3700
$Comp
L Device:Buzzer PiezzoSounder1
U 1 1 61DEA1B9
P 5550 4400
F 0 "PiezzoSounder1" H 5703 4429 50  0000 L CNN
F 1 "Buzzer" H 5703 4338 50  0000 L CNN
F 2 "Buzzer_Beeper:Buzzer_12x9.5RM7.6" V 5525 4500 50  0001 C CNN
F 3 "~" V 5525 4500 50  0001 C CNN
	1    5550 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3000 3900 3650
Wire Wire Line
	3900 3650 5450 3650
Wire Wire Line
	5450 3650 5450 4300
Wire Wire Line
	5400 4500 3950 4500
Connection ~ 3950 4500
Wire Wire Line
	3950 4500 3950 4600
Wire Wire Line
	1500 3700 1500 3850
Connection ~ 1500 3850
Wire Wire Line
	1500 3850 1700 3850
Wire Wire Line
	2800 3000 2800 3250
Wire Wire Line
	2800 3250 4000 3250
NoConn ~ 5600 1250
NoConn ~ 5700 1250
NoConn ~ 5800 1250
NoConn ~ 5900 1250
Wire Wire Line
	3150 5250 4100 5250
Wire Wire Line
	3950 4850 4400 4850
Wire Wire Line
	3950 4400 4400 4400
Wire Wire Line
	3950 3850 4000 3850
Connection ~ 4000 3850
Wire Wire Line
	3600 4100 3550 4100
Text GLabel 2550 1500 2    50   Input ~ 0
USB
Wire Wire Line
	2550 1500 2400 1500
Wire Wire Line
	2400 1500 2400 2700
Wire Wire Line
	2400 2700 2600 2700
$Comp
L power:+5V #PWR0101
U 1 1 61EC5CE4
P 2600 1350
F 0 "#PWR0101" H 2600 1200 50  0001 C CNN
F 1 "+5V" H 2615 1523 50  0000 C CNN
F 2 "" H 2600 1350 50  0001 C CNN
F 3 "" H 2600 1350 50  0001 C CNN
	1    2600 1350
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 61ED0E7F
P 2600 1200
F 0 "#PWR0102" H 2600 1050 50  0001 C CNN
F 1 "+3.3V" V 2615 1328 50  0000 L CNN
F 2 "" H 2600 1200 50  0001 C CNN
F 3 "" H 2600 1200 50  0001 C CNN
	1    2600 1200
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR0103
U 1 1 61ED20E1
P 2600 1000
F 0 "#PWR0103" H 2600 750 50  0001 C CNN
F 1 "GNDREF" V 2605 872 50  0000 R CNN
F 2 "" H 2600 1000 50  0001 C CNN
F 3 "" H 2600 1000 50  0001 C CNN
	1    2600 1000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 1000 2350 1900
Wire Wire Line
	550  1900 2350 1900
Connection ~ 2350 1900
Wire Wire Line
	2350 1900 2600 1900
Wire Wire Line
	2350 1000 2600 1000
Wire Wire Line
	2600 1200 2450 1200
Wire Wire Line
	2450 1200 2450 2100
Wire Wire Line
	2450 2100 2600 2100
Wire Wire Line
	2600 2000 2500 2000
Wire Wire Line
	2500 2000 2500 1350
Wire Wire Line
	2500 1350 2600 1350
Connection ~ 1700 5800
Wire Wire Line
	1700 5800 2950 5800
Wire Wire Line
	6950 2250 6950 2300
Wire Wire Line
	6400 2250 6950 2250
Wire Wire Line
	7050 2150 7050 2300
Wire Wire Line
	6600 2150 7050 2150
Wire Wire Line
	7150 2050 7150 2300
Wire Wire Line
	6500 2050 7150 2050
Wire Wire Line
	900  5350 900  5800
Wire Wire Line
	900  5800 1700 5800
Wire Wire Line
	1500 3850 1500 4200
Wire Wire Line
	1500 5650 2800 5650
Connection ~ 1500 4200
Wire Wire Line
	1500 4200 1500 4700
Connection ~ 1500 4700
Wire Wire Line
	1500 4700 1500 5200
Connection ~ 1500 5200
Wire Wire Line
	1500 5200 1500 5650
Wire Wire Line
	2650 5500 2100 5500
Wire Wire Line
	2100 5500 2100 5350
$EndSCHEMATC

EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 8 8
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
L MCU_ST_STM32L4:STM32L452RETxP U?
U 1 1 5CCD8CCC
P 4300 3400
F 0 "U?" H 4250 1514 50  0000 C CNN
F 1 "STM32L452RETxP" H 4250 1423 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 3600 1700 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00340549.pdf" H 4300 3400 50  0001 C CNN
	1    4300 3400
	1    0    0    -1  
$EndComp
Text HLabel 8050 1650 0    50   BiDi ~ 0
SDA1
Text HLabel 8050 1750 0    50   Output ~ 0
SCL1
Text HLabel 8050 1850 0    50   BiDi ~ 0
SDA2
Text HLabel 8050 1950 0    50   Output ~ 0
SCL2
Text HLabel 8050 2050 0    50   BiDi ~ 0
SDA3
Text HLabel 8050 2150 0    50   Output ~ 0
SCL3
Text HLabel 8050 2250 0    50   BiDi ~ 0
SDA4
Text HLabel 8050 2350 0    50   Output ~ 0
SCL4
Text HLabel 10350 1750 2    50   Output ~ 0
I2C_RESET
Text HLabel 10350 2450 2    50   Output ~ 0
DATA_IN
Text HLabel 10350 2150 2    50   Output ~ 0
CLK
Text HLabel 10350 2250 2    50   Output ~ 0
LATCH
Text HLabel 10350 2350 2    50   Output ~ 0
OUTPUT_ENABLE
Text HLabel 10350 2050 2    50   Output ~ 0
ROW_RESET
Text HLabel 10050 1750 2    50   UnSpc ~ 0
3V3
Text HLabel 10050 2450 2    50   UnSpc ~ 0
GND
Wire Wire Line
	5000 2700 5250 2700
Wire Wire Line
	5000 2800 5250 2800
Text Label 5000 2700 0    50   ~ 0
SCL1
Text Label 5000 2800 0    50   ~ 0
SDA1
Entry Wire Line
	5250 2800 5350 2700
Entry Wire Line
	5250 2700 5350 2600
$Comp
L conn:CONN_02X08 P?
U 1 1 5CCF9078
P 9650 2100
F 0 "P?" H 9650 2665 50  0000 C CNN
F 1 "CONN_02X08" H 9650 2574 50  0000 C CNN
F 2 "" H 9650 900 50  0000 C CNN
F 3 "" H 9650 900 50  0000 C CNN
	1    9650 2100
	-1   0    0    1   
$EndComp
Text Label 9400 1750 2    50   ~ 0
SDA1
Text Label 9400 1850 2    50   ~ 0
SCL1
Entry Wire Line
	8050 1650 8150 1750
Entry Wire Line
	8050 1750 8150 1850
Text Label 5000 4600 0    50   ~ 0
SDA2
Text Label 5000 4500 0    50   ~ 0
SCL2
Text Label 9400 1950 2    50   ~ 0
SDA2
Text Label 9400 2050 2    50   ~ 0
SCL2
Entry Wire Line
	8050 1850 8150 1950
Entry Wire Line
	8050 1950 8150 2050
Entry Wire Line
	8050 2050 8150 2150
Entry Wire Line
	8050 2150 8150 2250
Entry Wire Line
	8050 2250 8150 2350
Entry Wire Line
	8050 2350 8150 2450
Text Label 9400 2150 2    50   ~ 0
SDA3
Text Label 9400 2250 2    50   ~ 0
SCL3
Text Label 9400 2350 2    50   ~ 0
SDA4
Text Label 9400 2450 2    50   ~ 0
SCL4
Entry Wire Line
	5250 4600 5350 4500
Entry Wire Line
	5250 4500 5350 4400
Wire Wire Line
	5000 4500 5250 4500
Wire Wire Line
	5000 4600 5250 4600
Entry Wire Line
	5250 4100 5350 4000
Entry Wire Line
	5250 4200 5350 4100
Wire Wire Line
	5000 4100 5250 4100
Wire Wire Line
	5000 4200 5250 4200
Text Label 5000 4100 0    50   ~ 0
SCL4
Text Label 5000 4200 0    50   ~ 0
SDA4
Entry Wire Line
	10250 1850 10350 1750
Wire Wire Line
	9900 1750 10000 1750
Wire Wire Line
	10000 1750 10000 1600
Wire Wire Line
	10050 1750 10000 1750
Connection ~ 10000 1750
$Comp
L power:+3.3V #PWR?
U 1 1 5CCFDD22
P 10000 1600
F 0 "#PWR?" H 10000 1450 50  0001 C CNN
F 1 "+3.3V" H 10015 1773 50  0000 C CNN
F 2 "" H 10000 1600 50  0001 C CNN
F 3 "" H 10000 1600 50  0001 C CNN
	1    10000 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 1850 9900 1850
Text Label 3500 4100 2    50   ~ 0
RST
Entry Wire Line
	3200 4000 3300 4100
Wire Wire Line
	3300 4100 3500 4100
Wire Bus Line
	3200 750  5350 750 
Connection ~ 5350 750 
Entry Wire Line
	3200 3500 3300 3600
Entry Wire Line
	3200 3600 3300 3700
Wire Wire Line
	3300 3600 3500 3600
Wire Wire Line
	3300 3700 3500 3700
Text Label 9900 1850 0    50   ~ 0
RST
Text Label 3500 3600 2    50   ~ 0
SCL3
Text Label 3500 3700 2    50   ~ 0
SDA3
Wire Wire Line
	9900 2450 10000 2450
Wire Wire Line
	10000 2450 10000 2550
Connection ~ 10000 2450
Wire Wire Line
	10000 2450 10050 2450
$Comp
L power:GND #PWR?
U 1 1 5CD009E2
P 10000 2550
F 0 "#PWR?" H 10000 2300 50  0001 C CNN
F 1 "GND" H 10005 2377 50  0000 C CNN
F 2 "" H 10000 2550 50  0001 C CNN
F 3 "" H 10000 2550 50  0001 C CNN
	1    10000 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4200 3300 4200
Wire Wire Line
	3500 4300 3300 4300
Wire Wire Line
	3500 4400 3300 4400
Wire Wire Line
	5000 4900 5250 4900
Wire Wire Line
	5000 5000 5250 5000
Entry Wire Line
	3200 4300 3300 4200
Entry Wire Line
	3200 4400 3300 4300
Entry Wire Line
	3200 4500 3300 4400
Entry Wire Line
	5250 4900 5350 5000
Entry Wire Line
	5250 5000 5350 5100
Wire Bus Line
	3200 5600 5350 5600
Connection ~ 5350 5600
Wire Bus Line
	5350 5600 10350 5600
Text Label 3500 4200 2    50   ~ 0
DATA_IN
Text Label 3500 4300 2    50   ~ 0
CLOCK
Text Label 3500 4400 2    50   ~ 0
LATCH
Text Label 5000 4900 0    50   ~ 0
OE
Text Label 5000 5000 0    50   ~ 0
RESET
Entry Wire Line
	10250 2350 10350 2450
Entry Wire Line
	10250 2250 10350 2350
Entry Wire Line
	10250 2150 10350 2250
Entry Wire Line
	10250 2050 10350 2150
Entry Wire Line
	10250 1950 10350 2050
Wire Wire Line
	10250 1950 9900 1950
Wire Wire Line
	9900 2050 10250 2050
Wire Wire Line
	10250 2150 9900 2150
Wire Wire Line
	9900 2250 10250 2250
Wire Wire Line
	10250 2350 9900 2350
Text Label 9900 1950 0    50   ~ 0
RESET
Text Label 9900 2050 0    50   ~ 0
CLOCK
Text Label 9900 2150 0    50   ~ 0
LATCH
Text Label 9900 2250 0    50   ~ 0
OE
Text Label 9900 2350 0    50   ~ 0
DATA_IN
$Comp
L device:R_Small R?
U 1 1 5CD08941
P 8250 1550
F 0 "R?" H 8150 1650 50  0000 L CNN
F 1 "4k7" V 8250 1500 39  0000 L CNN
F 2 "" H 8250 1550 50  0000 C CNN
F 3 "" H 8250 1550 50  0000 C CNN
	1    8250 1550
	1    0    0    -1  
$EndComp
$Comp
L device:R_Small R?
U 1 1 5CD089E5
P 8350 1550
F 0 "R?" H 8250 1650 50  0000 L CNN
F 1 "4k7" V 8350 1500 39  0000 L CNN
F 2 "" H 8350 1550 50  0000 C CNN
F 3 "" H 8350 1550 50  0000 C CNN
	1    8350 1550
	1    0    0    -1  
$EndComp
$Comp
L device:R_Small R?
U 1 1 5CD08A01
P 8450 1550
F 0 "R?" H 8350 1650 50  0000 L CNN
F 1 "4k7" V 8450 1500 39  0000 L CNN
F 2 "" H 8450 1550 50  0000 C CNN
F 3 "" H 8450 1550 50  0000 C CNN
	1    8450 1550
	1    0    0    -1  
$EndComp
$Comp
L device:R_Small R?
U 1 1 5CD08A1F
P 8550 1550
F 0 "R?" H 8450 1650 50  0000 L CNN
F 1 "4k7" V 8550 1500 39  0000 L CNN
F 2 "" H 8550 1550 50  0000 C CNN
F 3 "" H 8550 1550 50  0000 C CNN
	1    8550 1550
	1    0    0    -1  
$EndComp
$Comp
L device:R_Small R?
U 1 1 5CD08A3B
P 8650 1550
F 0 "R?" H 8550 1650 50  0000 L CNN
F 1 "4k7" V 8650 1500 39  0000 L CNN
F 2 "" H 8650 1550 50  0000 C CNN
F 3 "" H 8650 1550 50  0000 C CNN
	1    8650 1550
	1    0    0    -1  
$EndComp
$Comp
L device:R_Small R?
U 1 1 5CD08A5D
P 8750 1550
F 0 "R?" H 8650 1650 50  0000 L CNN
F 1 "4k7" V 8750 1500 39  0000 L CNN
F 2 "" H 8750 1550 50  0000 C CNN
F 3 "" H 8750 1550 50  0000 C CNN
	1    8750 1550
	1    0    0    -1  
$EndComp
$Comp
L device:R_Small R?
U 1 1 5CD08A7F
P 8850 1550
F 0 "R?" H 8750 1650 50  0000 L CNN
F 1 "4k7" V 8850 1500 39  0000 L CNN
F 2 "" H 8850 1550 50  0000 C CNN
F 3 "" H 8850 1550 50  0000 C CNN
	1    8850 1550
	1    0    0    -1  
$EndComp
$Comp
L device:R_Small R?
U 1 1 5CD09612
P 8950 1550
F 0 "R?" H 8850 1650 50  0000 L CNN
F 1 "4k7" V 8950 1500 39  0000 L CNN
F 2 "" H 8950 1550 50  0000 C CNN
F 3 "" H 8950 1550 50  0000 C CNN
	1    8950 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 1450 8250 1400
Wire Wire Line
	8250 1400 8350 1400
Wire Wire Line
	8950 1400 8950 1450
Wire Wire Line
	8350 1400 8350 1450
Connection ~ 8350 1400
Wire Wire Line
	8350 1400 8450 1400
Wire Wire Line
	8450 1450 8450 1400
Connection ~ 8450 1400
Wire Wire Line
	8450 1400 8550 1400
Wire Wire Line
	8550 1400 8550 1450
Connection ~ 8550 1400
Wire Wire Line
	8650 1450 8650 1400
Wire Wire Line
	8550 1400 8600 1400
Connection ~ 8650 1400
Wire Wire Line
	8650 1400 8750 1400
Wire Wire Line
	8750 1400 8750 1450
Connection ~ 8750 1400
Wire Wire Line
	8750 1400 8850 1400
Wire Wire Line
	8850 1450 8850 1400
Connection ~ 8850 1400
Wire Wire Line
	8850 1400 8950 1400
Wire Wire Line
	8600 1400 8600 1350
Connection ~ 8600 1400
Wire Wire Line
	8600 1400 8650 1400
$Comp
L power:+3.3V #PWR?
U 1 1 5CD113EB
P 8600 1350
F 0 "#PWR?" H 8600 1200 50  0001 C CNN
F 1 "+3.3V" H 8615 1523 50  0000 C CNN
F 2 "" H 8600 1350 50  0001 C CNN
F 3 "" H 8600 1350 50  0001 C CNN
	1    8600 1350
	1    0    0    -1  
$EndComp
Wire Bus Line
	10350 750  10350 1750
Wire Bus Line
	5350 750  8050 750 
Connection ~ 8050 750 
Wire Bus Line
	8050 750  10350 750 
Wire Wire Line
	8150 1750 8950 1750
Wire Wire Line
	8150 1850 8850 1850
Wire Wire Line
	8150 1950 8750 1950
Wire Wire Line
	8150 2050 8650 2050
Wire Wire Line
	8150 2150 8550 2150
Wire Wire Line
	8150 2250 8450 2250
Wire Wire Line
	8150 2350 8350 2350
Wire Wire Line
	8150 2450 8250 2450
Wire Wire Line
	8250 1650 8250 2450
Connection ~ 8250 2450
Wire Wire Line
	8250 2450 9400 2450
Wire Wire Line
	8350 2350 8350 1650
Connection ~ 8350 2350
Wire Wire Line
	8350 2350 9400 2350
Wire Wire Line
	8450 1650 8450 2250
Connection ~ 8450 2250
Wire Wire Line
	8450 2250 9400 2250
Wire Wire Line
	8550 2150 8550 1650
Connection ~ 8550 2150
Wire Wire Line
	8550 2150 9400 2150
Wire Wire Line
	8650 1650 8650 2050
Connection ~ 8650 2050
Wire Wire Line
	8650 2050 9400 2050
Wire Wire Line
	8750 1950 8750 1650
Connection ~ 8750 1950
Wire Wire Line
	8750 1950 9400 1950
Wire Wire Line
	8850 1650 8850 1850
Connection ~ 8850 1850
Wire Wire Line
	8850 1850 9400 1850
Wire Wire Line
	8950 1750 8950 1650
Wire Bus Line
	5350 5000 5350 5600
Wire Bus Line
	3200 750  3200 4000
Wire Bus Line
	3200 4300 3200 5600
Wire Bus Line
	5350 750  5350 4500
Wire Bus Line
	10350 2050 10350 5600
Wire Bus Line
	8050 750  8050 2350
Connection ~ 8950 1750
Wire Wire Line
	8950 1750 9400 1750
$Comp
L Sensor_Motion:LSM9DS1 U?
U 1 1 5CD31D6F
P 6400 1950
F 0 "U?" H 6400 1064 50  0000 C CNN
F 1 "LSM9DS1" H 6400 973 50  0000 C CNN
F 2 "Package_LGA:LGA-24L_3x3.5mm_P0.43mm" H 7900 2700 50  0001 C CNN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/1e/3f/2a/d6/25/eb/48/46/DM00103319.pdf/files/DM00103319.pdf/jcr:content/translations/en.DM00103319.pdf" H 6400 2050 50  0001 C CNN
	1    6400 1950
	1    0    0    -1  
$EndComp
$EndSCHEMATC

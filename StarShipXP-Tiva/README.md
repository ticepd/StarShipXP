#StarShipXP - Tiva LaunchPad Pin Mapping

##Tiva LaunchPad Peripherals

###Onboard RGB LED

|Function   |Pin |Remarks |
|-----------|----|--------|
|LED Red    |PF_1|T0CCP1  |
|LED Blue 	|PF_2|T1CCP0  |
|LED Green  |PF_3|T1CCP1  |

###Onboard User Switch

|Function   |Pin |Remarks |
|-----------|----|--------|
|Switch 1   |PF_0|NMI     |
|Switch 2 	|PF_4|        |

###Virtual Serial Port

|Function   |Pin |Remarks |
|-----------|----|--------|
|UART RX    |PA_0|U0      |
|UART TX    |PA_1|        |

##StarShipXP Peripherals

###RGB LED

|Function   |Pin |Remarks |
|-----------|----|--------|
|LED Red    |PB_3|T3CCP1  |
|LED Green  |PC_4|WT0CCP0 |
|LED Blue 	|PC_5|WT0CCP1 |

###Sensors

|Function   |Pin |Remarks |
|-----------|----|--------|
|LDR/NTC    |PE_5|AIN 8   |
|POT        |PB_5|AIN 11  |
|NAVI KEYS  |PE_1|AIN 2   |
|MICROPHONE |PE_2|AIN 1   |
|DHT11      |PB_2|Digital |
|LM75       |I2C |0x48    |
|PCF8583    |I2C |0x51    |

###16x2 Character LCD

|Function   |Pin |Remarks |
|-----------|----|--------|
|LCD D4 		|PE_4|        |
|LCD D5 		|PA_5|        |
|LCD D6 		|PE_3|        |
|LCD D7 		|PC_6|        |
|LCD EN 		|PE_0|        |
|LCD RS     |PF_1|        |

###Audio

|Function     |Pin |Remarks |
|-------------|----|--------|
|AUDIO IN (L) |PD_2|AIN 5   |
|AUDIO IN (R) |PD_3|AIN 4   |
|             |    |        |
|AUDIO OUT (L)|PF_2|T1CCP0  |
|AUDIO OUT (R)|PF_3|TICCP1  |

###4x4 Matrix Keypad

|Function   |Pin |Remarks |
|-----------|----|--------|
|KEYPAD COL1|PE_4|        |
|KEYPAD COL2|PA_5|        |
|KEYPAD COL3|PE_3|        |
|KEYPAD COL4|PC_6|        |
|           |    |        |
|KEYPAD ROW1|PC_7|        |
|KEYPAD ROW2|PD_6|        |
|KEYPAD ROW3|PD_7|        |
|KEYPAD ROW4|PF_4|        |

###Communication Interfaces

|Function   |Pin |Remarks |
|-----------|----|--------|
|I2C SCL 		|PA_6|I2C1    |
|I2C SDA 		|PA_7|        |
|           |    |        |
|SPI MOSI   |PB_7|SSI2    |
|SPI MISO 	|PB_6|        |
|SPI CLK 		|PB_4|        |
|SPI CS_A 	|PA_3|        |
|SPI CS_B 	|PA_2|        |
|           |    |        |
|UART TX 		|PB_1|U0      |
|UART RX 		|PB_0|        |

####SPI Chip Select

|CS_A |CS_B |Device         |
|:---:|:---:|---------------|
|0    |0    |Shift Register |
|0    |1    |SD Card        |
|1    |0    |Graphics LCD   |
|1    |1    |External       |

###Miscellaneous

|Function   |Pin |Remarks |
|-----------|----|--------|
|Buzzer     |PF_2|T1CCP0  |
|GLCD Reset |PB_6|        |
|GLCD D/C   |PA_4|        |
|BT/WiFi/INT|PF_0|        |


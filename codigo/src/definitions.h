#ifndef definitions_h
#define definitions_h


//Definicion de pines
//Digital I/O
#define POWER_GOOD_PIN 3
#define POWER_ON_PIN 2
#define RELAY_PIN 5
#define FAN_ON_PIN 7
#define PSU_ON_PIN 6
#define LED_CARGANDO_PIN 11
#define LED_CARGADO_PIN 12
#define LED_DESCARGANDO_PIN 13

//Analog Inputs
#define BAT_VOLT_PIN A0
#define ISENS1_PIN A1 //Sensor de corriente en serie con la bateria  negativo significa descarga positivo significa carga
#define ISENS2_PIN A2 //Sensor de corriente en serie con la carga
#define BAT_TEMP_PIN A3

//Communication I/O

#define RX_PIN 0
#define TX_PIN 1
#define SDA_PIN A4
#define SCL_PIN A5

//Definiciones del programa

#define SENS_CORRIENTE_SENSIBILIDAD (double)0.06717094
#define SENS_CORRIENTE_VOLTAGE_ZEROA (float)2.495
#define SENS_CORRIENTE_CORRECCION (float)0.07432

#define RELAY_AC_CONECTADO 1
#define RELAY_BAT_CONECTADO 0

#define ESTADO_STANDBY 0
#define ESTADO_CARGANDO 1
#define ESTADO_DESCARGANDO 2


//Macros

#define GET_BAT_CURR getCorriente(ISENS1_PIN) //Negativo: bateria descargandose Positivo: bateria cargandose con el cargador
#define GET_LOAD_CURR -getCorriente(ISENS2_PIN) //Positivo: Carga consumiendo Negativo: ???
#define GET_LOAD_WATT (GET_LOAD_CURR * 12.5)

#define GET_PSU_POWER_GOOD !digitalRead(POWER_GOOD_PIN)
#define GET_PSU_POWER_ON !digitalRead(POWER_ON_PIN)

#define GET_BAT_ISCHARGING (GET_BAT_CURR > 0)







//EEPROM

//Tiempo estimado de vida util de la memoria: 57 a�os

#define EEPROM_ADDR_TOTALTIME 0x0
#define EEPROM_ADDR_TOTALWATTHOURS 0x4


#endif
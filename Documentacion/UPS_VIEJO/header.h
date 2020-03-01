#include <EEPROM.h>

//Definicion de pines
//Digital I/O
#define POWER_GOOD_PIN 2
#define POWER_ON_PIN 3
#define RELAY_PIN 5
#define CHARGER_ON_PIN 6
#define PSU_ON_PIN 7
#define LED_CARGANDO_PIN 11
#define LED_CARGADO_PIN 12
#define LED_DESCARGANDO_PIN 13

//Analog Inputs
#define BAT_VOLT_PIN A0
#define ISENS1_PIN A1 //Corriente consumida  lado de los leds
#define ISENS2_PIN A2 //Corriente de carga  lado del rele
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

#define RELAY_AC_CONECTADO 0
#define RELAY_BAT_CONECTADO 1

#define ESTADO_STANDBY 0
#define ESTADO_CARGANDO 1
#define ESTADO_DESCARGANDO 2



//Bateria

#define BATT_VOLTAGE_INICIO 11.5
#define BATT_VOLTAGE_FINALIZAR 13.2
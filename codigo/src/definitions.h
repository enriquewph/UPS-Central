#ifndef definitions_h
#define definitions_h


//Definicion de pines
//Digital I/O
#define POWER_GOOD_PIN 3
#define POWER_ON_PIN 2
#define RELAY_PIN 5
//Estados para RELAY_PIN
#define RELAY_AC_CONECTADO 1
#define RELAY_BAT_CONECTADO 0

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

#define BAT_MAX_TEMP 50.0
#define BAT_MIN_VOLT 11.1


#define HISTORIAL_SIZE 15



//Macros

#define BAT_CURR_PIN ISENS1_PIN
#define LOAD_CURR_PIN ISENS2_PIN

#define GET_BAT_CURR bat_curr //Negativo: bateria descargandose Positivo: bateria cargandose con el cargador
#define GET_LOAD_CURR load_curr //Positivo: Carga consumiendo Negativo: ???

#define GET_PSU_POWER_GOOD !digitalRead(POWER_GOOD_PIN)
#define GET_PSU_POWER_ON !digitalRead(POWER_ON_PIN)

#define GET_BAT_ISCHARGING (GET_BAT_CURR > 0)
#define GET_WATTS ((float) (historial.totalWattHours / 100.0)) //W a ala salida

#define BAT_DESCARGADA (bateria.voltaje >= BAT_MIN_VOLT)
#define GET_OVERHEATING (bateria.temperatura <= BAT_MAX_TEMP)

#define BAT_HEALTHY (GET_OVERHEATING && BAT_DESCARGADA)


//EEPROM

//Tiempo estimado de vida util de la memoria: 57 years
#define EEPROM_UINT32_T_SIZE 4u

#define EEPROM_ADDR_START 0u

#define EEPROM_ADDR_totalTime EEPROM_ADDR_START
#define EEPROM_ADDR_totalAmpHours (EEPROM_ADDR_totalTime + (1 * EEPROM_UINT32_T_SIZE))
#define EEPROM_ADDR_totalWattHours (EEPROM_ADDR_totalAmpHours + (1 * EEPROM_UINT32_T_SIZE))

#define EEPROM_ADDR_bat_charge_lastFull (EEPROM_ADDR_totalWattHours + (1 * EEPROM_UINT32_T_SIZE))
#define EEPROM_ADDR_bat_charge_current ((EEPROM_ADDR_bat_charge_lastFull + (2 * (1 * EEPROM_UINT32_T_SIZE))))
#define EEPROM_ADDR_bat_charge_last ((EEPROM_ADDR_bat_charge_current + (2 * (1 * EEPROM_UINT32_T_SIZE))))

#define EEPROM_ADDR_bat_discharge_lastFull ((EEPROM_ADDR_bat_charge_last + (2 * (HISTORIAL_SIZE * EEPROM_UINT32_T_SIZE))))
#define EEPROM_ADDR_bat_discharge_current ((EEPROM_ADDR_bat_discharge_lastFull + (2 * (1 * EEPROM_UINT32_T_SIZE))))
#define EEPROM_ADDR_bat_discharge_last ((EEPROM_ADDR_bat_discharge_current + (2 * (1 * EEPROM_UINT32_T_SIZE))))

#define EEPROM_ADDR_NEXTFREE ((EEPROM_ADDR_bat_discharge_last + (2 * (HISTORIAL_SIZE * EEPROM_UINT32_T_SIZE))))

#endif
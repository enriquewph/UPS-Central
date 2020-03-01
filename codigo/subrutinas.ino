#include "src/include.h"

void system_init()
{
    pinMode(POWER_GOOD_PIN, INPUT);
    pinMode(POWER_ON_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(FAN_ON_PIN, OUTPUT);
    pinMode(PSU_ON_PIN, OUTPUT);
    pinMode(LED_CARGANDO_PIN, OUTPUT);
    pinMode(LED_CARGADO_PIN, OUTPUT);
    pinMode(LED_DESCARGANDO_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(FAN_ON_PIN, LOW);
    digitalWrite(PSU_ON_PIN, LOW);
    digitalWrite(LED_CARGANDO_PIN, LOW);
    digitalWrite(LED_CARGADO_PIN, LOW);
    digitalWrite(LED_DESCARGANDO_PIN, LOW);
}

float get_ADC_voltage(uint8_t entrada, uint16_t n_muestras)
{
    float voltage = 0;

    for (uint16_t i = 0; i < n_muestras; i++)
    {
        voltage = voltage + analogRead(entrada) * (5.0 / 1023.0);
    }

    voltage = voltage / n_muestras;

    return (voltage);
}

float get_voltageBateria()
{
    float millivolts = get_ADC_voltage(BAT_VOLT_PIN, 25);
    return (millivolts / 0.327 * 1.0227); //Correccion aplicada
}

float get_temperatura_bateria()
{
    float millivolts = get_ADC_voltage(BAT_TEMP_PIN, 25);
    return (millivolts * 100);
}

float getCorriente(uint8_t sensor)
{
    float adcVolts = get_ADC_voltage(sensor, 25);
    float corriente = ((adcVolts - SENS_CORRIENTE_VOLTAGE_ZEROA) / SENS_CORRIENTE_SENSIBILIDAD) + SENS_CORRIENTE_CORRECCION;

    return (corriente);
}


void debugPrint()
{
    Serial.print("T bat:");
    Serial.print(bateria.temperatura);
    Serial.print(" - V bat:");
    Serial.print(bateria.voltaje);
    Serial.print(" - I bat:");
    Serial.print(GET_BAT_CURR);
    Serial.print(" - I load:");
    Serial.println(GET_LOAD_CURR);
    Serial.print("ESTADO: ");
    Serial.println(getSystemState_c_str(_getSystemState(false)));
    Serial.print("POWER: ON: ");
    Serial.print(GET_PSU_POWER_ON);
    Serial.print(" | GOOD: ");
    Serial.println(GET_PSU_POWER_ON);
}
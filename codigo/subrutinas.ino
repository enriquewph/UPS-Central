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

    return (-corriente);
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void setLed(uint8_t led_pin, uint8_t mode)
{
    switch (led_pin)
    {
    case LED_OFF:
        digitalWrite(led_pin, 0);
        break;
    case LED_ON:
        digitalWrite(led_pin, 1);
        break;
    case LED_FLASH:
        digitalWrite(led_pin, flash_helper);
        break;
    }
}
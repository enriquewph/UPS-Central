#include "src/include.h"

void setSystemState(uint8_t state)
{
    switch (state)
    {
    case ESTADO_STANDBY:
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
        digitalWrite(FAN_ON_PIN, HIGH);

        digitalWrite(LED_CARGADO_PIN, HIGH);
        digitalWrite(LED_CARGANDO_PIN, LOW);
        digitalWrite(LED_DESCARGANDO_PIN, LOW);

        break;
    case ESTADO_CARGANDO:
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
        digitalWrite(FAN_ON_PIN, HIGH);

        digitalWrite(LED_CARGADO_PIN, LOW);
        digitalWrite(LED_CARGANDO_PIN, HIGH);
        digitalWrite(LED_DESCARGANDO_PIN, LOW);
        break;
    case ESTADO_DESCARGANDO:
        digitalWrite(RELAY_PIN, RELAY_BAT_CONECTADO);
        digitalWrite(FAN_ON_PIN, HIGH);

        digitalWrite(LED_CARGADO_PIN, LOW);
        digitalWrite(LED_CARGANDO_PIN, LOW);
        digitalWrite(LED_DESCARGANDO_PIN, HIGH);
        break;
    }
}

uint8_t _getSystemState(bool fast)
{
    if (fast) //No va a revisar si la bateria se esta cargando o no.
        if (GET_PSU_POWER_GOOD && GET_PSU_POWER_ON)
            return ESTADO_STANDBY;
        else
            return ESTADO_DESCARGANDO;

    if (GET_PSU_POWER_GOOD && GET_PSU_POWER_ON)
        if (GET_BAT_ISCHARGING)
            return ESTADO_CARGANDO;
        else
            return ESTADO_STANDBY;
    else
        return ESTADO_DESCARGANDO;
}

char *getSystemState_c_str(uint8_t state)
{
    switch (state)
    {
    case ESTADO_STANDBY:
        return ("STANDBY");
        break;
    case ESTADO_CARGANDO:
        return ("CARGANDO");
        break;
    case ESTADO_DESCARGANDO:
        return ("DESCARGANDO");
        break;
    default:
        return ("???");
        break;
    }
}
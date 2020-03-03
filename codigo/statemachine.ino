#include "src/include.h"

void setSystemState(estado_t estado)
{
    switch (estado)
    {
    case estado_e::ESTADO_STANDBY:
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
        digitalWrite(FAN_ON_PIN, HIGH);

        setLed(LED_CARGADO_PIN, LED_ON);
        setLed(LED_CARGANDO_PIN, LED_OFF);
        setLed(LED_DESCARGANDO_PIN, LED_OFF);

        break;
    case estado_e::ESTADO_CARGANDO:
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
        digitalWrite(FAN_ON_PIN, HIGH);

        setLed(LED_CARGADO_PIN, LED_OFF);
        setLed(LED_CARGANDO_PIN, LED_ON);
        setLed(LED_DESCARGANDO_PIN, LED_OFF);
        break;
    case estado_e::ESTADO_DESCARGANDO:
        digitalWrite(RELAY_PIN, RELAY_BAT_CONECTADO);
        digitalWrite(FAN_ON_PIN, HIGH);

        setLed(LED_CARGADO_PIN, LED_OFF);
        setLed(LED_CARGANDO_PIN, LED_OFF);
        setLed(LED_DESCARGANDO_PIN, LED_ON);
        break;
    case estado_e::ESTADO_BATDESCARGADA: //Entrar en modo de bajo consumo. Bateria descargada.
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
        digitalWrite(FAN_ON_PIN, LOW);

        setLed(LED_CARGADO_PIN, LED_OFF);
        setLed(LED_CARGANDO_PIN, LED_OFF);
        setLed(LED_DESCARGANDO_PIN, LED_FLASH); //Hacer led intermitente?
        break;
    case estado_e::ESTADO_OVERHEATING: //Temperatura demasiada alta.
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
        digitalWrite(FAN_ON_PIN, LOW);

        setLed(LED_CARGADO_PIN, LED_OFF);
        setLed(LED_CARGANDO_PIN, LED_FLASH);
        setLed(LED_DESCARGANDO_PIN, LED_OFF); //Hacer led intermitente?
        break;
    }
}

estado_t _getSystemState()
{
    if (GET_OVERHEATING)
    {
        return estado_e::ESTADO_OVERHEATING;
    }

    if (GET_PSU_POWER_GOOD && GET_PSU_POWER_ON) //Si hay corriente electrica
    {
        if (GET_BAT_ISCHARGING)
            return estado_e::ESTADO_CARGANDO;
        else
            return estado_e::ESTADO_STANDBY;
    }
    else
    {
        if (BAT_DESCARGADA)
            return estado_e::ESTADO_DESCARGANDO;
        else
            return estado_e::ESTADO_BATDESCARGADA;
    }
}

char *getSystemState_c_str(estado_t estado)
{
    switch (estado)
    {
    case estado_e::ESTADO_STANDBY:
        return ("STANDBY");
        break;
    case estado_e::ESTADO_CARGANDO:
        return ("CARGANDO");
        break;
    case estado_e::ESTADO_DESCARGANDO:
        return ("DESCARGANDO");
        break;
    case estado_e::ESTADO_BATDESCARGADA:
        return ("BATDESCARGADA");
        break;
    case estado_e::ESTADO_OVERHEATING:
        return ("OVERHEATING");
        break;
    default:
        return ("???");
        break;
    }
}

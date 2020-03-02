#include "src/include.h"

struct
{
    uint32_t psu_on;
    uint32_t debug;
    uint32_t timer5min;
    uint32_t timer1min;
} lastMillis;

void timerManagement_init()
{
    lastMillis.psu_on = millis();
    lastMillis.debug = millis();
    lastMillis.timer1min = millis();
    lastMillis.timer5min = millis();
}

void timerManagement_tick()
{
    //Debug print
    if ((uint32_t)(millis() - lastMillis.debug) > 2000U)
    {
        lastMillis.debug = millis();
        debugPrint();
    }

    //Si se está desconectada la corriente, tratar de activar la fuente de 12v!
    if ((uint32_t)(millis() - lastMillis.psu_on) > 4000U && _getSystemState() == ESTADO_DESCARGANDO)
    {
        //Se togglea el pin de PSU_ON cada 4 segundos SI ES QUE LA FUENTE ESTA APAGADA!, cuando encienda este togleo se detiene.
        lastMillis.psu_on = millis();
        digitalWrite(PSU_ON_PIN, !digitalRead(PSU_ON_PIN));
    }

    //Timer 1 min para actualizar uptime
    if ((uint32_t)(millis() - lastMillis.timer1min) > 60000U)
    {
        lastMillis.timer1min = millis();
        timer1minTick();
    }

    //Timer 5 min para guardar datos en el EEPROM
    if ((uint32_t)(millis() - lastMillis.timer5min) > 300000U)
    {
        lastMillis.timer5min = millis();
        eeprom_writeVars();
    }
}
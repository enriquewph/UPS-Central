#include "header.h"

struct
{
    long psu_on;
    long timer5min;
    long timer1min;
    bool rollOverWatch;
} lastMillis;

void timerManagement_init()
{
    lastMillis.psu_on = millis();
    lastMillis.timer1min = millis();
    lastMillis.timer5min = millis();
    lastMillis.rollOverWatch = false;
}

void timerManagement_tick()
{
    //Timer 1 min para actualizar uptime
    if (lastMillis.timer1min + 60000U <= millis())
    {
        lastMillis.timer1min = millis();
        historial.upTime++;
        historial.totalTime++;

        Serial.print("UPTIME: ");
        Serial.print(historial.upTime);
        Serial.println("min");

        Serial.print("UPTIME Total: ");
        Serial.print(historial.totalTime);
        Serial.println("min");

        //wattimetros:

        if (ESTADO != ESTADO_DESCARGANDO)
        {
            historial.wattMinutosSalidaAC += 12.2 * CORRIENTE_CONSUMIDA;
            if (historial.wattMinutosSalidaAC >= 60.0)
            {
                historial.wattMinutosSalidaAC -= 60.0;
                historial.wattHorasSalidaAC++;
            }
        }

        if (ESTADO == ESTADO_CARGANDO)
        {
            historial.bateria.wattMinutosCarga = bateria.voltaje * bateria.corriente_carga;
            if (historial.bateria.wattMinutosCarga >= 60.0)
            {
                historial.bateria.wattMinutosCarga -= 60.0;
                historial.bateria.wattHorasCarga++;
                historial.bateria.wattHorasCarga_Actual++;
            }
        }

        if (ESTADO == ESTADO_DESCARGANDO)
        {
            historial.bateria.wattMinutosDescarga = bateria.voltaje * CORRIENTE_CONSUMIDA;
            if (historial.bateria.wattMinutosDescarga >= 60.0)
            {
                historial.bateria.wattMinutosDescarga -= 60.0;
                historial.bateria.wattHorasDescarga++;
                historial.bateria.wattHorasDescarga_Actual++;
            }
        }
    }

    //Timer 5 min para guardar datos en el EEPROM
    if (lastMillis.timer5min + 300000U <= millis())
    {
        lastMillis.timer5min = millis();
        historial.upTime++;
        historial.totalTime++;

        eeprom_writeVars();
    }

    //Rollover watch
    if (millis() >= 0xFFFFBF69) // 49 dias transcurridos.
        lastMillis.rollOverWatch = true;
    if (lastMillis.rollOverWatch && millis() <= 600000U)
    {
        lastMillis.psu_on = millis();
        lastMillis.timer1min = millis();
        lastMillis.timer5min = millis();
        lastMillis.rollOverWatch = false;
    }

    //Tratar de activar la fuente de 12v!
    if (lastMillis.psu_on + 4000U <= millis() && ESTADO == ESTADO_DESCARGANDO)
    {
        lastMillis.psu_on = millis();
        digitalWrite(PSU_ON_PIN, !digitalRead(PSU_ON_PIN));
    }
}
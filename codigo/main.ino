#include "src/include.h"

/* TODO:
 * - Comandos ya sean UART o por I2C
 * - Determinar carga por Wh totales!
 * - Integrar tiempo restante para carga y decarga.
 * - Integrar modo de bajo consumo!
 * - Integrar led flasheando cuando la bateria esta descargada.
 * - Integrar reinicio de carga por comando.
 * - Proteccion por sobrecarga. (exceso de amperaje en la salida)
 */

void setup()
{
    Serial.begin(115200);

    system_init();

    //Inicializar int externa
    attachInterrupt(digitalPinToInterrupt(POWER_ON_PIN), interrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(POWER_GOOD_PIN), interrupt, CHANGE);
    interrupt();

    //Inicializar timerManagement
    timerManagement_init();

    //Inicializar variables desde la EEPROM
    eeprom_readVars();

    //Iniciar variables
}

void loop()
{
    bateria.temperatura = get_temperatura_bateria();
    bateria.voltaje = get_voltageBateria();
    bateria.carga = determinarCarga();
    load_curr = getCorriente(LOAD_CURR_PIN);
    bat_curr = getCorriente(BAT_CURR_PIN);

    estadoActual = _getSystemState();
    setSystemState(estadoActual);

    rutinasCambioDeEstado();

    timerManagement_tick();
}

void interrupt() //actualizar inmediatamente el estado del sistema!
{
    estadoActual = _getSystemState();
    setSystemState(estadoActual);
}

void timer1minTick()
{
    //Incrementar Uptimes
    historial.currentTime++;
    historial.totalTime++;
    //Incrementar Wattimetro
    historial.totalAmpHours += GET_LOAD_CURR * (100 / 60);
    historial.totalWattHours += (GET_LOAD_CURR * 12.5) * (100 / 60); //Toma una instantanea de cuantos watts se consume ahora, y lo divide por 60. Multiplicamos por 100 para guardar 2 decimales

    historial.currentAmpHours += GET_LOAD_CURR * (100 / 60);
    historial.currentWattHours += (GET_LOAD_CURR * 12.5) * (100 / 60); //Toma una instantanea de cuantos watts se consume ahora, y lo divide por 60. Multiplicamos por 100 para guardar 2 decimales

    switch (estadoActual)
    {
    case estado_e::ESTADO_CARGANDO: //Estado CARGANDO
        historial.bat.charge.current.time++;
        historial.bat.charge.current.ampHours += GET_BAT_CURR * (100 / 60);
        break;
    case estado_e::ESTADO_DESCARGANDO: //Estado DESCARGANDO
        historial.bat.discharge.current.time++;
        historial.bat.discharge.current.ampHours += -GET_BAT_CURR * (100 / 60);
        break;
    }
}

float determinarCarga()
{
    float carga = mapFloat(bateria.voltaje, BAT_MIN_VOLT, 12.65, 0, 100);
    if (carga >= 100.0)
        carga = 100.0;
    return carga;
}

void rutinasCambioDeEstado()
{
    if (estadoActual != estadoAnterior)
    {
        switch (estadoActual)
        {
        case estado_e::ESTADO_STANDBY: //Se paso al estado STANDBY
            if (estadoAnterior == estado_e::ESTADO_CARGANDO)
            {
                historial.bat.charge.lastFull.time = historial.bat.charge.current.time;
                historial.bat.charge.lastFull.ampHours = historial.bat.charge.current.ampHours;
            }
            break;
        case estado_e::ESTADO_CARGANDO: //Se paso al estado CARGANDO
            ciclarHistorial(historial.bat.charge.last);

            historial.bat.charge.last[0].time = historial.bat.charge.current.time;
            historial.bat.charge.last[0].ampHours = historial.bat.charge.current.ampHours;

            historial.bat.charge.current.time = 0;
            historial.bat.charge.current.ampHours = 0;
            break;
        case estado_e::ESTADO_DESCARGANDO: //Se paso al estado DESCARGANDO
            ciclarHistorial(historial.bat.discharge.last);

            historial.bat.discharge.last[0].time = historial.bat.discharge.current.time;
            historial.bat.discharge.last[0].ampHours = historial.bat.discharge.current.ampHours;

            historial.bat.discharge.current.time = 0;
            historial.bat.discharge.current.ampHours = 0;
            break;
        case estado_e::ESTADO_BATDESCARGADA: //Se paso al estado BATDESCARGADA
            historial.bat.discharge.lastFull.time = historial.bat.discharge.current.time;
            historial.bat.discharge.lastFull.ampHours = historial.bat.discharge.current.ampHours;
            eeprom_writeVars();
            break;
        case estado_e::ESTADO_OVERHEATING: //Se paso al estado OVERHEATING

            break;
        }
    }

    estadoAnterior = estadoActual;
}
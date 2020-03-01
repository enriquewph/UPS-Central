#include "src/include.h"

/* TODO:
 * - Proteccion por temperatura
 * - Proteccion por sobredescarga
 * - Wattimetro a la salida
 * - Wh a la salida
 * - Comandos ya sean UART o por I2C
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

    setSystemState(_getSystemState(false)); //Va a detectar si se esta cargando o no...

    timerManagement_tick();
}

void interrupt() //actualizar inmediatamente el estado del sistema!
{
    setSystemState(_getSystemState(true));
}

void timer1minTick()
{
    //Incrementar Uptimes
    historial.upTime++;
    historial.totalTime++;
    //Incrementar Wattimetro
    historial.totalWattHours += GET_LOAD_WATT / 60;  //Toma una instantanea de cuantos watts se consume ahora, y lo divide por 60.

}

#include "header.h"

struct
{
    float temperatura;
    float voltaje;
    float corriente_carga;
    float carga;
    bool cargando;
} bateria;

struct
{
    struct
    {
        uint32_t wattHorasCarga;                      //EEPROM ADDR: 1
        uint32_t wattHorasDescarga;                   //EEPROM ADDR: 101
        uint32_t wattHorasCarga_ultimoHastaAcabar;    //EEPROM ADDR: 501
        uint32_t wattHorasDescarga_ultimoHastaAcabar; //EEPROM ADDR: 601
        uint32_t wattHorasCarga_Actual;               //NO EN EEPROM
        uint32_t wattHorasDescarga_Actual;            //NO EN EEPROM
        float wattMinutosCarga;
        float wattMinutosDescarga;
    } bateria;
    uint32_t wattHorasSalidaAC; //EEPROM ADDR: 201
    double wattMinutosSalidaAC;
    uint32_t upTime;    //EEPROM ADDR: 301  Cuenta cada 5 minutos
    uint32_t totalTime; //EEPROM ADDR: 401
} historial;

uint8_t ESTADO = ESTADO_STANDBY;
bool AC_DESCONECTADO = false;
float CORRIENTE_CONSUMIDA;

void setup()
{
    //Inicializar pinout
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
    historial.bateria.wattHorasCarga_Actual = 0;
    historial.bateria.wattHorasDescarga_Actual = 0;
    historial.bateria.wattMinutosCarga = 0;
    historial.bateria.wattMinutosDescarga = 0;
    historial.wattMinutosSalidaAC = 0;
    bateria.cargando = false;

    //Inicializar comunicaciones
    Serial.begin(9600);
}

void loop()
{
    timerManagement_tick();

    bateria.temperatura = get_temperatura_bateria();
    bateria.voltaje = get_voltageBateria();
    CORRIENTE_CONSUMIDA = getCorriente(ISENS1_PIN);

    /*  Implementar:
        Wattimetro de salida LISTO
        Watts/Hora de carga en la bateria LISTO
        Medicion de carga LISTO
        Schmitt Trigger para la carga de la bateria LISTO
		Control de sobredescarga
        Interfaz Serie/I2C
    */

    //schmitt trigger  11.5 - 13.2
    schmitt_trigger_carga();

    //Medicion de carga
    bat_determinarCarga();

    switch (ESTADO)
    {
    case ESTADO_STANDBY:
        digitalWrite(LED_CARGADO_PIN, HIGH);
        digitalWrite(LED_CARGANDO_PIN, LOW);
        digitalWrite(LED_DESCARGANDO_PIN, LOW);
        digitalWrite(CHARGER_ON_PIN, LOW);

        break;
    case ESTADO_CARGANDO:
        digitalWrite(LED_CARGADO_PIN, LOW);
        digitalWrite(LED_CARGANDO_PIN, HIGH);
        digitalWrite(LED_DESCARGANDO_PIN, LOW);
        bateria.corriente_carga = getCorriente(ISENS2_PIN);
        digitalWrite(CHARGER_ON_PIN, HIGH);
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);

        break;
    case ESTADO_DESCARGANDO:
        digitalWrite(LED_CARGADO_PIN, LOW);
        digitalWrite(LED_CARGANDO_PIN, LOW);
        digitalWrite(LED_DESCARGANDO_PIN, HIGH);
        digitalWrite(CHARGER_ON_PIN, LOW);

        //control sobredescarga
        controlSobredescarga();

        break;
    }
}

void interrupt()
{
    AC_DESCONECTADO = digitalRead(POWER_ON_PIN) + digitalRead(POWER_GOOD_PIN);
    if (AC_DESCONECTADO)
    {
        digitalWrite(RELAY_PIN, RELAY_BAT_CONECTADO);
        ESTADO = ESTADO_DESCARGANDO;
    }
    else
    {
        digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
        if (ESTADO == ESTADO_DESCARGANDO)
            ESTADO = ESTADO_STANDBY;
    }
}

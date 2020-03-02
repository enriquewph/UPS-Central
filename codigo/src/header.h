#ifndef header_h
#define header_h

typedef struct bateria_s
{
    float temperatura;
    float voltaje;
    float carga; //Porcentaje de carga...
} bateria_t;

typedef struct ampHours_s
{
    uint32_t ampHours;
    uint32_t time;
} ampHours_t;

typedef struct charge_discharge_s
{
    ampHours_t lastFull;
    ampHours_t last[10];
    ampHours_t current;
} charge_discharge_t;

typedef struct historial_s
{
    uint32_t currentTime; //Minutos desde que se reinicio el micro...
    uint32_t currentAmpHours;
    uint32_t currentWattHours;
    uint32_t totalTime;      //Minutos totales de funcionamiento del software.
    uint32_t totalAmpHours;  //DIVIDIR POR 100 PARA TENER EL VALOR REAL!. a cada minuto se le incrementa los (AmpMinuto / 60)
    uint32_t totalWattHours; //DIVIDIR POR 100 PARA TENER EL VALOR REAL!. a cada minuto se le incrementa los (WattMinuto / 60)
    struct bat_s
    {
        charge_discharge_t charge;
        charge_discharge_t discharge;
    } bat;
} historial_t;

typedef enum estado_e
{
    ESTADO_reserved,
    ESTADO_STANDBY,
    ESTADO_CARGANDO,
    ESTADO_DESCARGANDO,
    ESTADO_BATDESCARGADA,
    ESTADO_OVERHEATING
} estado_t;

historial_t historial;
bateria_t bateria;
float load_curr;
float bat_curr;

estado_t estadoActual;
estado_t estadoAnterior = ESTADO_reserved;

#endif
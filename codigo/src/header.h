#ifndef header_h
#define header_h

struct bateria_s
{
    float temperatura;
    float voltaje;
    float carga; //Porcentaje de carga...
} bateria;

struct historial_s
{
    uint32_t upTime; //Minutos desde que se reinicio el micro...
    uint32_t totalTime; //Minutos totales de funcionamiento del software.
    uint32_t totalWattHours; //a cada minuto se le incrementa los (WattMinuto / 60)
    uint32_t totalWattHours_dec; //a cada minuto se le incrementa los (WattMinuto / 60)
} historial;

#endif
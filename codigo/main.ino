#include "C:\Users\quiqu\Documents\GitHub\UPS-Central\header.h"


void setup()
{
    system_init();
    Serial.begin(9600);
    digitalWrite(RELAY_PIN, RELAY_BAT_CONECTADO);
}

void loop()
{
    Serial.print("T bat:");
    Serial.print(get_temperatura_bateria());
    Serial.print(" - V bat:");
    Serial.print(get_voltageBateria());
    Serial.print(" - I bat:");
    Serial.print(getCorriente(ISENS1_PIN));
    Serial.print(" - I load:");
    Serial.println(getCorriente(ISENS2_PIN));
    delay(1500);
}
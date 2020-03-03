#include "src/include.h"

void serialEvent()
{
    String inputString = Serial.readStringUntil('\n');
    Serial.println(inputString);
    printVars();
    inputString = "";
}

void printVars()
{
    const size_t capacity = 2 * JSON_ARRAY_SIZE(HISTORIAL_SIZE) + 26 * JSON_OBJECT_SIZE(2) + 2 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(7);
    DynamicJsonDocument doc(capacity);

    JsonObject j_bateria = doc.createNestedObject("bateria");
    j_bateria["t"] = bateria.temperatura;
    j_bateria["v"] = bateria.voltaje;
    j_bateria["c"] = bateria.carga;
    j_bateria["r"] = bateria.remainingTime;

    JsonObject j_historial = doc.createNestedObject("historial");
    j_historial["cT"] = historial.currentTime;
    j_historial["cAh"] = historial.currentAmpHours;
    j_historial["cWh"] = historial.currentWattHours;
    j_historial["tT"] = historial.totalTime;
    j_historial["tAh"] = historial.totalAmpHours;
    j_historial["tWh"] = historial.totalWattHours;

    JsonObject historial_bat = j_historial.createNestedObject("bat");

    JsonObject historial_bat_charge = historial_bat.createNestedObject("charge");

    JsonObject historial_bat_charge_lastFull = historial_bat_charge.createNestedObject("lastFull");
    historial_bat_charge_lastFull["Ah"] = historial.bat.charge.lastFull.ampHours;
    historial_bat_charge_lastFull["t"] = historial.bat.charge.lastFull.time;

    JsonObject historial_bat_charge_current = historial_bat_charge.createNestedObject("current");

    historial_bat_charge_current["Ah"] = historial.bat.charge.current.ampHours;
    historial_bat_charge_current["t"] = historial.bat.charge.current.time;

    JsonArray historial_bat_charge_last = historial_bat_charge.createNestedArray("last");

    for (uint8_t i = 0; i < HISTORIAL_SIZE; i++)
    {
        JsonObject historial_bat_charge_last_0 = historial_bat_charge_last.createNestedObject();
        historial_bat_charge_last_0["Ah"] = historial.bat.charge.last[i].ampHours;
        historial_bat_charge_last_0["t"] = historial.bat.charge.last[i].time;
    }

    JsonObject historial_bat_discharge = historial_bat.createNestedObject("discharge");

    JsonObject historial_bat_discharge_lastFull = historial_bat_discharge.createNestedObject("lastFull");
    historial_bat_discharge_lastFull["Ah"] = historial.bat.discharge.lastFull.ampHours;
    historial_bat_discharge_lastFull["t"] = historial.bat.discharge.lastFull.time;

    JsonObject historial_bat_discharge_current = historial_bat_discharge.createNestedObject("current");

    historial_bat_discharge_current["Ah"] = historial.bat.discharge.current.ampHours;
    historial_bat_discharge_current["t"] = historial.bat.discharge.current.time;

    JsonArray historial_bat_discharge_last = historial_bat_discharge.createNestedArray("last");

    for (uint8_t i = 0; i < HISTORIAL_SIZE; i++)
    {
        JsonObject historial_bat_discharge_last_0 = historial_bat_discharge_last.createNestedObject();
        historial_bat_discharge_last_0["Ah"] = historial.bat.discharge.last[i].ampHours;
        historial_bat_discharge_last_0["t"] = historial.bat.discharge.last[i].time;
    }

    serializeJson(doc, Serial);
    doc.clear();
}
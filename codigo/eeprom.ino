#include "src/include.h"

void EEPROMWritelong(int address, uint32_t value)
{
    //Decomposition from a long to 4 bytes by using bitshift.
    //One = Most significant -> Four = Least significant byte
    byte four = (value & 0xFF);
    byte three = ((value >> 8) & 0xFF);
    byte two = ((value >> 16) & 0xFF);
    byte one = ((value >> 24) & 0xFF);

    //Write the 4 bytes into the eeprom memory.
    EEPROM.update(address, four);
    EEPROM.update(address + 1, three);
    EEPROM.update(address + 2, two);
    EEPROM.update(address + 3, one);
}

uint32_t EEPROMReadlong(int address)
{
    //Read the 4 bytes from the eeprom memory.
    byte four = EEPROM.read(address);
    byte three = EEPROM.read(address + 1);
    byte two = EEPROM.read(address + 2);
    byte one = EEPROM.read(address + 3);

    //Return the recomposed long by using bitshift.
    return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void eeprom_readVars()
{
    historial.currentTime = 0;
    historial.totalTime = EEPROMReadlong(EEPROM_ADDR_totalTime);
    historial.totalAmpHours = EEPROMReadlong(EEPROM_ADDR_totalAmpHours);
    historial.totalWattHours = EEPROMReadlong(EEPROM_ADDR_totalWattHours);
    historial.bat.charge.lastFull.ampHours = EEPROMReadlong(EEPROM_ADDR_bat_charge_lastFull);
    historial.bat.charge.lastFull.time = EEPROMReadlong(EEPROM_ADDR_bat_charge_lastFull + EEPROM_UINT32_T_SIZE);
    historial.bat.charge.current.ampHours = EEPROMReadlong(EEPROM_ADDR_bat_charge_current);
    historial.bat.charge.current.time = EEPROMReadlong(EEPROM_ADDR_bat_charge_current + EEPROM_UINT32_T_SIZE);
    historial.bat.discharge.lastFull.ampHours = EEPROMReadlong(EEPROM_ADDR_bat_discharge_lastFull);
    historial.bat.discharge.lastFull.time = EEPROMReadlong(EEPROM_ADDR_bat_discharge_lastFull + EEPROM_UINT32_T_SIZE);
    historial.bat.discharge.current.ampHours = EEPROMReadlong(EEPROM_ADDR_bat_discharge_current);
    historial.bat.discharge.current.time = EEPROMReadlong(EEPROM_ADDR_bat_discharge_current + EEPROM_UINT32_T_SIZE);

    for (uint8_t i = 0; i < HISTORIAL_SIZE; i++)
    {
        //leer historial:
        historial.bat.charge.last[i].ampHours = EEPROMReadlong(EEPROM_ADDR_bat_charge_last + (2 * EEPROM_UINT32_T_SIZE * i));
        historial.bat.charge.last[i].time = EEPROMReadlong(EEPROM_ADDR_bat_charge_last + (2 * EEPROM_UINT32_T_SIZE * i) + EEPROM_UINT32_T_SIZE);
        historial.bat.discharge.last[i].ampHours = EEPROMReadlong(EEPROM_ADDR_bat_discharge_last + (2 * EEPROM_UINT32_T_SIZE * i));
        historial.bat.discharge.last[i].time = EEPROMReadlong(EEPROM_ADDR_bat_discharge_last + (2 * EEPROM_UINT32_T_SIZE * i) + EEPROM_UINT32_T_SIZE);
    }
}

void eeprom_writeVars()
{
    EEPROMWritelong(EEPROM_ADDR_totalTime, historial.totalTime);
    EEPROMWritelong(EEPROM_ADDR_totalAmpHours, historial.totalAmpHours);
    EEPROMWritelong(EEPROM_ADDR_totalWattHours, historial.totalWattHours);
    EEPROMWritelong(EEPROM_ADDR_bat_charge_lastFull, historial.bat.charge.lastFull.ampHours);
    EEPROMWritelong(EEPROM_ADDR_bat_charge_lastFull + EEPROM_UINT32_T_SIZE, historial.bat.charge.lastFull.time);
    EEPROMWritelong(EEPROM_ADDR_bat_charge_current, historial.bat.charge.current.ampHours);
    EEPROMWritelong(EEPROM_ADDR_bat_charge_current + EEPROM_UINT32_T_SIZE, historial.bat.charge.current.time);
    EEPROMWritelong(EEPROM_ADDR_bat_discharge_lastFull, historial.bat.discharge.lastFull.ampHours);
    EEPROMWritelong(EEPROM_ADDR_bat_discharge_lastFull + EEPROM_UINT32_T_SIZE, historial.bat.discharge.lastFull.time);
    EEPROMWritelong(EEPROM_ADDR_bat_discharge_current, historial.bat.discharge.current.ampHours);
    EEPROMWritelong(EEPROM_ADDR_bat_discharge_current + EEPROM_UINT32_T_SIZE, historial.bat.discharge.current.time);

    for (uint8_t i = 0; i < HISTORIAL_SIZE; i++)
    {
        //leer historial:
        EEPROMWritelong(EEPROM_ADDR_bat_charge_last + (2 * EEPROM_UINT32_T_SIZE * i), historial.bat.charge.last[i].ampHours);
        EEPROMWritelong(EEPROM_ADDR_bat_charge_last + (2 * EEPROM_UINT32_T_SIZE * i) + EEPROM_UINT32_T_SIZE, historial.bat.charge.last[i].time);
        EEPROMWritelong(EEPROM_ADDR_bat_discharge_last + (2 * EEPROM_UINT32_T_SIZE * i), historial.bat.discharge.last[i].ampHours);
        EEPROMWritelong(EEPROM_ADDR_bat_discharge_last + (2 * EEPROM_UINT32_T_SIZE * i) + EEPROM_UINT32_T_SIZE, historial.bat.discharge.last[i].time);
    }
}

void eeprom_resetVars()
{
    for (int i = 0; i < EEPROM.length(); i++)
        EEPROM.write(i, 0);
}

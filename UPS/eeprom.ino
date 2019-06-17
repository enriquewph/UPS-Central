#include "header.h"

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
    historial.bateria.wattHorasCarga = EEPROMReadlong(EEPROM_ADDR_WATTHORASCARGA_BAT);
    historial.bateria.wattHorasDescarga = EEPROMReadlong(EEPROM_ADDR_WATTHORASDESCARGA_BAT);
    historial.wattHorasSalidaAC = EEPROMReadlong(EEPROM_ADDR_WATTHORASSALIDA);
    historial.upTime = 0;
    historial.totalTime = EEPROMReadlong(EEPROM_ADDR_TOTALTIME);
    historial.bateria.wattHorasCarga_ultimoHastaAcabar = EEPROMReadlong(EEPROM_ADDR_WATTHORASCARGA_ULT_BAT);
    historial.bateria.wattHorasDescarga_ultimoHastaAcabar = EEPROMReadlong(EEPROM_ADDR_WATTHORASDESCARGA_ULT_BAT);
}

void eeprom_writeVars()
{
    EEPROMWritelong(EEPROM_ADDR_WATTHORASCARGA_BAT, historial.bateria.wattHorasCarga);
    EEPROMWritelong(EEPROM_ADDR_WATTHORASDESCARGA_BAT, historial.bateria.wattHorasDescarga);
    EEPROMWritelong(EEPROM_ADDR_WATTHORASSALIDA, historial.wattHorasSalidaAC);
    EEPROMWritelong(EEPROM_ADDR_UPTIME, historial.upTime);
    EEPROMWritelong(EEPROM_ADDR_TOTALTIME, historial.totalTime);
}

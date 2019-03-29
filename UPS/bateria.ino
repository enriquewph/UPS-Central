#include "header.h"

void schmitt_trigger_carga()
{
	if (bateria.voltaje <= BATT_VOLTAGE_INICIO && !bateria.cargando)
	{
		bateria.cargando = true;
		cargaComenzada();
	}
	if (bateria.voltaje >= BATT_VOLTAGE_FINALIZAR && bateria.cargando)
	{
		bateria.cargando = false;
		cargaTerminada();
	}

	if (bateria.cargando)
	{
		if (ESTADO == ESTADO_STANDBY)
		{
			ESTADO = ESTADO_CARGANDO;
		}
	}
	else
	{
		if (ESTADO == ESTADO_CARGANDO)
		{
			ESTADO = ESTADO_STANDBY;
		}
	}
}

void bat_determinarCarga()
{
	if (ESTADO == ESTADO_CARGANDO)
	{
		bateria.carga = (historial.bateria.wattHorasCarga_Actual / historial.bateria.wattHorasCarga_ultimoHastaAcabar) * 100;
	}
	else if (ESTADO == ESTADO_DESCARGANDO)
	{
		bateria.carga = 100.0 - (historial.bateria.wattHorasDescarga_Actual / historial.bateria.wattHorasDescarga_ultimoHastaAcabar) * 100;
	}
}

void controlSobredescarga()
{
	if (bateria.voltaje <= 11.1)
	{
		digitalWrite(RELAY_PIN, RELAY_AC_CONECTADO);
	}
}

void cargaComenzada()
{
	historial.bateria.wattHorasCarga_Actual = 0;
	EEPROMWritelong(EEPROM_ADDR_WATTHORASDESCARGA_ULT_BAT, historial.bateria.wattHorasDescarga_Actual);
	historial.bateria.wattHorasDescarga_ultimoHastaAcabar = historial.bateria.wattHorasDescarga_Actual;
}

void cargaTerminada()
{

	//Actualizar valores de uso estadistico
	EEPROMWritelong(EEPROM_ADDR_WATTHORASCARGA_ULT_BAT, historial.bateria.wattHorasCarga_Actual);
	historial.bateria.wattHorasCarga_ultimoHastaAcabar = historial.bateria.wattHorasCarga_Actual;
	historial.bateria.wattHorasDescarga_Actual = 0;
}
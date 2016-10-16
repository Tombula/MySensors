/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Marcelo Aquino <marceloaqno@gmail.org>
 * Copyright (C) 2016 Marcelo Aquino
 * Full contributor list: https://github.com/mysensors/MySensors/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#include "MyHwRPi.h"

#include <stdarg.h>
#include <time.h>
#include "SoftEeprom.h"
#include "log.h"

static SoftEeprom eeprom = SoftEeprom(MY_LINUX_CONFIG_FILE, 1024);	// ATMega328 has 1024 bytes

void hwInit()
{
	if (!bcm2835_init()) {
		mys_log(LOG_ERR, "Failed to initialized bcm2835.\n");
		exit(1);
	}

#ifdef MY_GATEWAY_SERIAL
	MY_SERIALDEVICE.begin(MY_BAUD_RATE);
	#ifdef MY_LINUX_SERIAL_GROUPNAME
		if (!MY_SERIALDEVICE.setGroupPerm(MY_LINUX_SERIAL_GROUPNAME)) {
			mys_log(LOG_ERR, "Unable to change permission for serial port device.\n");
			exit(1);
		}
	#endif
#endif
}

void hwReadConfigBlock(void* buf, void* adr, size_t length)
{
	eeprom.readBlock(buf, adr, length);
}

void hwWriteConfigBlock(void* buf, void* adr, size_t length)
{
	eeprom.writeBlock(buf, adr, length);
}

uint8_t hwReadConfig(int adr)
{
	return eeprom.readByte(adr);
}

void hwWriteConfig(int adr, uint8_t value)
{
	eeprom.writeByte(adr, value);
}

void hwRandomNumberInit()
{
	randomSeed(time(NULL));
}

unsigned long hwMillis()
{
	return millis();
}

// Not supported!
int8_t hwSleep(unsigned long ms)
{
	(void)ms;

	return MY_SLEEP_NOT_POSSIBLE;
}

// Not supported!
int8_t hwSleep(uint8_t interrupt, uint8_t mode, unsigned long ms)
{
	(void)interrupt;
	(void)mode;
	(void)ms;

	return MY_SLEEP_NOT_POSSIBLE;
}

// Not supported!
int8_t hwSleep(uint8_t interrupt1, uint8_t mode1, uint8_t interrupt2, uint8_t mode2, unsigned long ms)
{
	(void)interrupt1;
	(void)mode1;
	(void)interrupt2;
	(void)mode2;
	(void)ms;
	
	return MY_SLEEP_NOT_POSSIBLE;
}

#if defined(MY_DEBUG) || defined(MY_SPECIAL_DEBUG)
	uint16_t hwCPUVoltage()
	{
		// TODO: Not supported!
		return 0;
	}
	 
	uint16_t hwCPUFrequency()
	{
		// TODO: Not supported!
		return 0;
	}
	 
	uint16_t hwFreeMem()
	{
		// TODO: Not supported!
		return 0;
	}
#endif

#ifdef MY_DEBUG
	void hwDebugPrint(const char *fmt, ...)
	{
		va_list args;

		va_start(args, fmt);
		mys_log_v(LOG_DEBUG, fmt, args);
		va_end(args);
	}
#endif

void hwDigitalWrite(uint8_t pin, uint8_t value)
{
	digitalWrite(pin, value);
}

int hwDigitalRead(uint8_t pin)
{
	return digitalRead(pin);
}

void hwPinMode(uint8_t pin, uint8_t mode)
{
	pinMode(pin, mode);
}
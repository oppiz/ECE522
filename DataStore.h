#ifndef DATASTORE_H
#define DATASTORE_H

#include <modbus.h>
#include "ModbusComm.h"

int Datastore_init(); 

int Datastore_insert(Modbus_Read p);

void Datastore_Close();

#endif
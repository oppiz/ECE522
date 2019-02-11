#include <stdio.h>

#include "ModbusComm.h"

int main(int argc, char **argv) {
	
	int a = Modbus_init();
	int b = Datastore_init();

	Modbus_Read p = Modbus_read();
	int c = Datastore_insert(p);

	//printf("%f\n%f\n",p.Temp,p.Humid);
	
	Datastore_Close();
	Modbus_Close();

}
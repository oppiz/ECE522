#include <stdio.h>
#include <unistd.h>

#include "ModbusComm.h"

int main(int argc, char **argv) {
	
	int a = Modbus_init();
	int b = Datastore_init();

	printf("%d %d\n", a, b);

	for(int i = 0; i < 100; i++){
		printf("%d \n", i);
		Modbus_Read p = Modbus_read();
		int c = Datastore_insert(p);
		sleep(3);
	}

	Datastore_Close();
	Modbus_Close();

}
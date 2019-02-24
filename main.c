#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include "ModbusComm.h"
#include "DataStore.h"

volatile sig_atomic_t done = 0;
 
void term(int signum)
{
    done = 1;
}


int main(int argc, char **argv) {

	//Enter parms
	char IP_Addr[] = "192.168.2.250";	
	char DB_Path[] = "test.db";
	uint16_t delay = 10;

	uint16_t a = Modbus_init(IP_Addr);
	uint16_t b = Datastore_init(DB_Path);

	//had signal handler to allow clean shutdown
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);

	while(!done){
		Modbus_Read p = Modbus_read();
		//If error from modbus do not write
		if (p.Error != -1){
			uint16_t c = Datastore_insert(p);
		}
		sleep(delay);
	}

	Datastore_Close();
	Modbus_Close();

	printf("Done.\n");
	return 0;

}
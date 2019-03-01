#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <assert.h>

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
	//char IP_Addr[] = "127.0.0.1"; //Use for SSH Tunnel
	char DB_Path[] = "test.db";
	uint16_t delay = 10;

	int16_t MODBUSINIT = Modbus_init(IP_Addr);
	//fail if unable to open modbus connetion
	assert(MODBUSINIT != -1);

	int16_t DataBaseINIT = Datastore_init(DB_Path);
	//fail on database init failure, close modbus conenction
	if (DataBaseINIT != -1){

		//add signal handler to allow clean shutdown
    	struct sigaction action;
    	memset(&action, 0, sizeof(struct sigaction));
    	action.sa_handler = term;
    	sigaction(SIGTERM, &action, NULL);

		//Loop until signal handler sets done
		while(!done){
			Modbus_Read p = Modbus_read();
			//If error from modbus do not write			
			if (p.Error != -1){
				int16_t DataBaseWrite = Datastore_insert(p);
				//Assert if unable to write to database
				assert(DataBaseWrite != -1);
			}

		sleep(delay);
		}

		Datastore_Close();
	}

	Modbus_Close();

	printf("Done.\n");
	return 0;

}

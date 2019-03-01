#include <modbus.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include "ModbusComm.h"


static modbus_t *ctx;
static int Modbus_error_count;

int Modbus_init(char IP_Addr[]){

	ctx = modbus_new_tcp(IP_Addr, 502);
	Modbus_error_count = 0;

    if (modbus_connect(ctx) == -1) {
	    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
	    modbus_free(ctx);
	    return -1;
	}

    return 0;

}

float float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint){
	union
	{
		float f_number;
		uint16_t uint16_arr[2];
	} union_for_conv;  
	union_for_conv.uint16_arr[0] = LSB_uint;
	union_for_conv.uint16_arr[1] = MSB_uint;
	return union_for_conv.f_number;
}

//This could be more sophisticated
void ERROR_HANDLE(){
		
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
		//try and reconnect! https://libmodbus.org/docs/v3.0.6/modbus_set_error_recovery.html
		int d = modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_LINK);
		//modbus_set_error_recovery() returns 0 on success if that didn't work try the other option
		if (d != 0){
			int e = modbus_set_error_recovery(ctx, MODBUS_ERROR_RECOVERY_PROTOCOL);
		}
		//If recovery failes 200 times, dump, is 200 the best number?
		Modbus_error_count++;
		assert(Modbus_error_count < 200);
}

void Modbus_PULL(int addr, int nd, uint8_t *dest, int8_t *Error){
  	int rc = modbus_read_input_bits(ctx, addr, nd, dest);
	if (rc == -1) {
		//Call error handle function
		ERROR_HANDLE();
		//Set read as error for datawrite
		*Error = -1;
	}else{
		//not in error
		*Error = 0;
		Modbus_error_count = 0;
	}

}


Modbus_Read Modbus_read(){
    
    Modbus_Read Store_read;

    uint16_t tab_reg[4];

	//Doubles are handled different, do not call with MODBUS_PULL    
    int rc1 = modbus_read_input_registers(ctx, 28672, 4, tab_reg);
	if (rc1 == -1) {
	    //Call error handle function
		ERROR_HANDLE();
		//Set read as error for datawrite
	    Store_read.Error = -1;
	}else{
		//not in error
		Store_read.Error = 0;
	}

	Store_read.Temp = float32_from_two_uint16(tab_reg[1],tab_reg[0]);
	Store_read.Humid = float32_from_two_uint16(tab_reg[3],tab_reg[2]);
	
	Modbus_PULL(0, 8, Store_read.regs1, &Store_read.Error);
	Modbus_PULL(8192, 6, Store_read.regs2, &Store_read.Error);
	Modbus_PULL(64, 8, Store_read.regs3, &Store_read.Error);

    return Store_read;

}

void Modbus_Close(){
    	
	modbus_close(ctx);
	modbus_free(ctx);

}
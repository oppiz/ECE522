#include <modbus.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "ModbusComm.h"


static modbus_t *ctx;

int Modbus_init(char IP_Addr[]){

	ctx = modbus_new_tcp(IP_Addr, 502);
	
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

Modbus_Read Modbus_read(){
    
    Modbus_Read Store_read;
    
    uint16_t tab_reg[4];
    int rc1, rc2, rc3, rc4;
    
    
    rc1 = modbus_read_input_registers(ctx, 28672, 4, tab_reg);
	if (rc1 == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    Store_read.Error = -1;
	}

	Store_read.Temp = float32_from_two_uint16(tab_reg[1],tab_reg[0]);
	Store_read.Humid = float32_from_two_uint16(tab_reg[3],tab_reg[2]);

    rc2 = modbus_read_input_bits(ctx, 0, 8, Store_read.regs1);
	if (rc2 == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    Store_read.Error = -1;
	}

	rc3 = modbus_read_bits(ctx, 8192, 6, Store_read.regs2);
	if (rc3 == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    Store_read.Error = -1;
	}
	
	rc4 = modbus_read_input_bits(ctx, 64, 8, Store_read.regs3);
	if (rc4 == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    Store_read.Error = -1;
	}

    return Store_read;

}

void Modbus_Close(){
    	
	modbus_close(ctx);
	modbus_free(ctx);

}
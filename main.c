#include <modbus.h>
#include <stdio.h>
#include <errno.h>


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

int main(){

	modbus_t *ctx;

	uint16_t tab_reg[64];
	uint8_t bits1[64];
	uint8_t bits2[64];
	int rc1, rc2, rc3, rc4;
	int i;

	ctx = modbus_new_tcp("192.168.2.250", 502);

	if (modbus_connect(ctx) == -1) {
	    fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
	    modbus_free(ctx);
	    return -1;
	}

	rc1 = modbus_read_input_registers(ctx, 28672, 4, tab_reg);
	if (rc1 == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    return -1;
	}

	float d = float32_from_two_uint16(tab_reg[1],tab_reg[0]);
	float e = float32_from_two_uint16(tab_reg[3],tab_reg[2]);
	printf("Temp %f \n", d);
	printf("Humid %f \n", e);

	rc2 = modbus_read_input_bits(ctx, 0, 8, bits1);
	if (rc2 == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    return -1;
	}

	for (i=0; i < rc2; i++) {
	    printf("%i \n", bits1[i]);
	}
	
	rc3 = modbus_read_input_bits(ctx, 64, 8, bits2);
	if (rc3 == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    return -1;
	}

	for (i=0; i < rc3; i++) {
	    printf("%i \n", bits2[i]);
	}

   //regs1 = c.read_discrete_inputs(0, 8)
    //        regs2 = c.read_coils(8192, 6)
    //        regs3 = c.read_discrete_inputs(64, 8)


	//for (i=0; i < rc; i++) {
	//    printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
	//}

	modbus_close(ctx);
	modbus_free(ctx);

}

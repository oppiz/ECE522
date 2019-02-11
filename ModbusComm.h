#ifndef MODBUSCOMM_H
#define MODBUSCOMM_H

#include <modbus.h>


typedef struct {
    double Temp, Humid;
    uint8_t regs1[8];
    uint8_t regs2[8];
    uint8_t regs3[6];
    uint8_t Error;
} Modbus_Read;

int Modbus_init(); 

Modbus_Read Modbus_read();

void Modbus_Close();

#endif
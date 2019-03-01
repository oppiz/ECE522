#ifndef MODBUSCOMM_H
#define MODBUSCOMM_H

#include <modbus.h>

/*! @file */

/*! \breif Modbus object and method definitions
 *
 *  A Modbus object is a struct with a temperature, denoted Temp, 
 *  Humiditiy, denoted Humid, three arrays of consecutive coil(boolean) reads, denoted by regsX. 
 *  Varions Methods that create the modbus connection, read the various registers and coils, 
 *  as well as function to correct data types.
 */
typedef struct {
    double Temp, Humid;
    uint8_t regs1[8];
    uint8_t regs2[6];
    uint8_t regs3[8];
    int8_t Error;
} Modbus_Read;


/*! \fn Modbus_init 
 *  Creates modbus connection to TCP/IP device
 *  Returns -1 on error
 * \param DB_name_path Name and path of database file.
 */
int Modbus_init(char IP_Addr[]); 


/*! \fn ERROR_HANDLE 
 *  Attempts to reconnected and correct communication errors
 *  https://libmodbus.org/docs/v3.0.6/modbus_set_error_recovery.html
 */
void ERROR_HANDLE();

/*! \fn Modbus_PULL 
 *  Read various registers/coils over Modbus TCP
 * \param Modbus coil to start reading at
 * \param How many coils to read
 * \param destination of coil info
 * \param Set error bit
 */
void Modbus_PULL(int addr, int nd, uint8_t *dest, int8_t *Error);

/*! \fn Modbus_read 
 *  Setup to Read various registers/coils over Modbus TCP
 *  Returns Type Modbus_Read
 */
Modbus_Read Modbus_read();

/*! \fn Modbus_Close 
 *  Closes connected created to TCP/IP device
 */
void Modbus_Close();

/*! \fn float32_from_two_uint16 
 *  Modbus returns two unsigned 16 bit ints. This combins them and returns the corrosponding float value
 * \param MSB_uint Most significant bit.
 * \param LSB_uint Least significant bit.
 */
float float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint);

#endif
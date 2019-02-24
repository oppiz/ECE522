#ifndef DATASTORE_H
#define DATASTORE_H

#include <modbus.h>

#include "ModbusComm.h"


/*! \fn Datastore_init
 *  Checks for and if needed creates and opens database of given name.
 *  Returns -1 on error
 * \param DB_name_path Name and path of database file.
 */
int Datastore_init(char DB_Path[]); 

/*! \fn Datastore_insert 
 *  Modbus returns two unsigned 16 bit ints. This combins them and returns the corrosponding float value
 * \param p type Modbus_read, values recieved from Modbus device.
 */
int Datastore_insert(Modbus_Read p);

/*! \fn Datastore_Close 
 *  Closes database 
 */
void Datastore_Close();

#endif
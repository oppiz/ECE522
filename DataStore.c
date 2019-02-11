#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sqlite3.h> 

#include "ModbusComm.h"

static sqlite3 *db;


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int Datastore_init(){
    
    char *sql;
    char *zErrMsg = 0;
    int rc = sqlite3_open("test.db", &db);
    
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return -1;
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   sql = "CREATE TABLE IF NOT EXISTS PLCValues(ID INTEGER PRIMARY KEY AUTOINCREMENT, TEXT DEFAULT CURRENT_TIMESTAMP, \
        x001 NUMERIC, x002 NUMERIC, x003 NUMERIC, x004 NUMERIC, x005 NUMERIC, x006 NUMERIC, x007 NUMERIC, x008 NUMERIC,\
        x201 NUMERIC, x202 NUMERIC, x203 NUMERIC, x204 NUMERIC, x205 NUMERIC, x206 NUMERIC, x207 NUMERIC, x208 NUMERIC,\
        y001 NUMERIC, y002 NUMERIC, y003 NUMERIC, y004 NUMERIC, y005 NUMERIC, y006 NUMERIC,\
        df1 REAL, df2  REAL, df3 REAL, df4 REAL)";

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      return -1;
   } else {
      fprintf(stdout, "Table created successfully\n");
   }

    return 0;

}

int Datastore_insert(Modbus_Read p){

    char sql[1024];
    char *err_msg = 0;

    char TimeStamp[20];
    time_t now = time(NULL);
    strftime(TimeStamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    printf("%s\n",TimeStamp);

    snprintf(sql, sizeof(sql), \
        "INSERT INTO PLCValues VALUES(%s, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %f, %f, %f, %f)", \
        TimeStamp, p.regs1[0], p.regs1[1], p.regs1[2], p.regs1[3], p.regs1[4], p.regs1[5], p.regs1[6], p.regs1[7],\
        p.regs2[0], p.regs2[1], p.regs2[2], p.regs2[3], p.regs2[4], p.regs2[5], p.regs2[6], p.regs2[7],\
        p.regs3[0], p.regs3[1], p.regs3[2], p.regs3[3], p.regs3[4], p.regs3[5], p.Temp, p.Humid, 0, 0);

    printf(sql);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return -1;
    } 

    return 0;

}

void Datastore_Close(){
    sqlite3_close(db);
}

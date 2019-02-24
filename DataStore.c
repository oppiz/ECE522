#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

int Datastore_init(char DB_Path[]){
    
    char *sql;
    char *zErrMsg = 0;
    int rc = sqlite3_open(DB_Path, &db);
    
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return -1;
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   sql = "CREATE TABLE IF NOT EXISTS PLCValues(ID INTEGER PRIMARY KEY AUTOINCREMENT, timestamp TEXT, \
        x001 NUMERIC, x002 NUMERIC, x003 NUMERIC, x004 NUMERIC, x005 NUMERIC, x006 NUMERIC, x007 NUMERIC, x008 NUMERIC,\
        y001 NUMERIC, y002 NUMERIC, y003 NUMERIC, y004 NUMERIC, y005 NUMERIC, y006 NUMERIC,\
        x201 NUMERIC, x202 NUMERIC, x203 NUMERIC, x204 NUMERIC, x205 NUMERIC, x206 NUMERIC, x207 NUMERIC, x208 NUMERIC,\
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

   char *err_msg = 0;
   sqlite3_stmt *res;

   //pull current time
   char TimeStamp[20];
   time_t now = time(NULL);
   strftime(TimeStamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
   printf("%s\n",TimeStamp);

   char *sql = "INSERT INTO PLCValues VALUES(null, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

   int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    
   if (rc == SQLITE_OK ) {

      //Bind the variables  
     	sqlite3_bind_text(res, 1, TimeStamp, -1, SQLITE_TRANSIENT);
      sqlite3_bind_int(res, 2, p.regs1[0]);
      sqlite3_bind_int(res, 3, p.regs1[1]);
      sqlite3_bind_int(res, 4, p.regs1[2]);
      sqlite3_bind_int(res, 5, p.regs1[3]);
      sqlite3_bind_int(res, 6, p.regs1[4]);
      sqlite3_bind_int(res, 7, p.regs1[5]);
      sqlite3_bind_int(res, 8, p.regs1[6]);
      sqlite3_bind_int(res, 9, p.regs1[7]);

      sqlite3_bind_int(res, 10, p.regs2[0]);
      sqlite3_bind_int(res, 11, p.regs2[1]);
      sqlite3_bind_int(res, 12, p.regs2[2]);
      sqlite3_bind_int(res, 13, p.regs2[3]);
      sqlite3_bind_int(res, 14, p.regs2[4]);
      sqlite3_bind_int(res, 15, p.regs2[5]);

      sqlite3_bind_int(res, 16, p.regs3[0]);
      sqlite3_bind_int(res, 17, p.regs3[1]);
      sqlite3_bind_int(res, 18, p.regs3[2]);
      sqlite3_bind_int(res, 19, p.regs3[3]);
      sqlite3_bind_int(res, 20, p.regs3[4]);
      sqlite3_bind_int(res, 21, p.regs3[5]);
      sqlite3_bind_int(res, 22, p.regs3[6]);
      sqlite3_bind_int(res, 23, p.regs3[7]);

		sqlite3_bind_double(res, 24, p.Temp);      
      sqlite3_bind_double(res, 25, p.Humid);
      sqlite3_bind_double(res, 26, 0);
      sqlite3_bind_double(res, 27, 0);
        
   }else{
        
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return -1;
   } 

   int step = sqlite3_step(res);
    
   if (step == SQLITE_ROW) {
        
      printf("%s: ", sqlite3_column_text(res, 0));
      printf("%s\n", sqlite3_column_text(res, 1));
        
   } 

   sqlite3_finalize(res);
   return 0;

}

void Datastore_Close(){
    sqlite3_close(db);
    
}

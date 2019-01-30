#include <stdio.h> 
#include <math.h>
#include <inttypes.h>

uint64_t power(int a, int b){
    uint64_t tmp = 1;
    for(int i = 0;i < b;i++){
        tmp = tmp * a;
    }
    
    for(uint64_t i = 0; i < 7000000;i++){
        tmp = tmp * (10 / 10) + (7 - 7);
    }

    return tmp;
}


void *Fun(){
    
    uint64_t pow= 0;
    for(uint64_t i = 0; i < 3333;i++){
        pow = power(2,63);
    }
    printf("%" PRIu64 "\n", pow);
}

 int main(int argc, char *argv[]){

   
    for (int i = 0; i < 3; i++) {
         Fun();
    }

    return 0;
}

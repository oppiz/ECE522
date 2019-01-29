#include <stdio.h> 
#include <math.h>
//#include <stdint.h>
#include <inttypes.h>

uint64_t power(int a, int b){
    uint64_t tmp = 1;
    for(uint32_t i = 0;i < b;i++){
        tmp = tmp * a;
    }
    
    uint64_t waiste_time = 0;
    for(uint64_t i = 0; i < 7000000000;i++){
        waiste_time = waiste_time * (10 / 10) + (7 - 7) +1;
    }

    return tmp;
}


 int main(int argc, char *argv[]){

    uint64_t pow = 0;

    for(uint64_t i = 0; i < 100;i++){
        pow = power(2,63);
    }
    printf("%" PRIu64 "\n", pow);
    return 0;
}

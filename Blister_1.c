#include <stdio.h> 
#include <math.h>
//#include <stdint.h>
#include <inttypes.h>

uint64_t power(int a, int b){
    uint64_t tmp = 1;
    for(uint32_t i = 0;i < b;i++){
        tmp = tmp * a;
    }

    return tmp;
}


 int main(int argc, char *argv[]){

    uint64_t pow = 0;

    for(uint64_t i = 0; i < 10000000;i++){
        pow = power(2,63);
    }
    printf("%" PRIu64 "\n", pow);
    return 0;
}

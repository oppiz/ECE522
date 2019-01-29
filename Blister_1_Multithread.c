#include <stdio.h> 
#include <math.h>
//#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

uint64_t power(int a, int b){
    uint64_t tmp = 1;
    for(uint32_t i = 0;i < b;i++){
        tmp = tmp * a;
    }
    
    uint64_t waiste_time = 0;
    for(uint64_t i = 0; i < 7000000;i++){
        waiste_time = waiste_time * (10 / 10) + (7 - 7) +1;
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

    pthread_t tid; 
    for (int i = 0; i < 3; i++) {
        pthread_create(&tid, NULL, Fun, (void *)&tid); 
    }
       
    pthread_exit(NULL); 

    return 0;
}

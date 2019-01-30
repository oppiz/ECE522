#include <stdio.h> 
#include <math.h>
#include <inttypes.h>
#include <pthread.h>

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

    pthread_t thread1, thread2, thread3;
    int  iret1, iret2, iret3;

    iret1 = pthread_create( &thread1, NULL, Fun, (void*) &thread1);
    if(iret1){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
        return 1;
    }
        
    iret2 = pthread_create( &thread1, NULL, Fun, (void*) &thread2);
    if(iret2){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
        return 1;
    }

    iret3 = pthread_create( &thread3, NULL, Fun, (void*) &thread3);
    if(iret3){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3);
        return 1;
    }

    pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
    pthread_join( thread3, NULL);
 
    return 0;
}

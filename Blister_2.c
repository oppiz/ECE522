#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Create 1gb array and fill with random value
int main(int argc, char *argv[]){

    srand(time(NULL));

    int * count = malloc(sizeof(int)); 
    count[0] = rand();

    for(int i = 1; i < 32000000;i++){
        count = (int*) realloc(count, (i + 1) * sizeof(int));
        count[i] = rand();
    }

    free(count);

return 0;
}
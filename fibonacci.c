#include <stdio.h>
#include <gmp.h>
#include <time.h>

int main(int argc, char *argv[]){
	mpz_t a,b,c;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);

	mpz_set_ui(a,1);
	mpz_set_ui(b,1);
	mpz_set_ui(c,0);

	clock_t start, end;
	FILE *fp;
 	fp = fopen("/tmp/test.txt", "w+");

	//int is fun to x+2 as 1,1 are the first two
	for(int i = 0; i < 10000000-2;i++){
		start = clock();
		mpz_add(c,a,b);
		mpz_swap(a,b);
		mpz_swap(c,a);
		end = clock();
		fprintf(fp, "%d %f\n", i, ((double) (end - start)) / CLOCKS_PER_SEC);

	}
	
	fclose (fp);
	mpz_out_str(stdout,1,a);

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);

	

}

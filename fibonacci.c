#include <stdio.h>
#include <gmp.h>

int main(int argc, char *argv[]){
	mpz_t a,b,c;
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);

	mpz_set_ui(a,1);
	mpz_set_ui(b,1);
	mpz_set_ui(c,0);

	//int is fun to x+2 as 1,1 are the first two
	for(int i = 0; i < 1000000-2;i++){
		mpz_add(c,a,b);
		mpz_swap(a,b);
		mpz_swap(c,a);
		//mpz_out_str(stdout,1,a);
		printf("\n");	
	}

	mpz_out_str(stdout,1,a);

	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);

}

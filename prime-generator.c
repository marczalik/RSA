/*
#include <stdio.h>
#include <gmp.h>
*/
#include "rsa.h"

int generate_prime(mpz_t candidate, int bt_len, int s) {
    // get seed for GMP
    int seed;
    srand(time(NULL));
    seed = rand();

    // seed GMP
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);

    do {
        mpz_urandomb(candidate, state, bt_len);
        mpz_setbit(candidate, 0);
    } while (!miller_rabin(candidate, s)); 

    gmp_randclear(state);

    return 0;
}

/*
int main(int argc, char *argv[]) {
    int bt_len = atoi(argv[1]);
    int s = atoi(argv[2]);
    
    mpz_t prime;
    mpz_init(prime);

    generate_prime(prime, bt_len, s);

    mpz_out_str(stdout, 10, prime);

    mpz_clear(prime);
}
*/

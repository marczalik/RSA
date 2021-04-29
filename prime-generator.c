#include "rsa.h"

/*      Randomly searches until it finds a good candidate for a prime of bt_len.
        Confidence of primality denoted by s.   */
int generate_prime(mpz_t candidate, int bt_len, int s) {
    // Get seed for GMP
    int seed;
    srand(time(NULL));
    seed = rand();

    // Seed GMP
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);

    // Find a new random integer using GMP, make sure it's odd, and test for primality until a candidate is found
    do {
        mpz_urandomb(candidate, state, bt_len);
        // Setting the LSB to 0 makes the integer odd
        mpz_setbit(candidate, 0);
    } while (!miller_rabin(candidate, s)); 

    gmp_randclear(state);

    return EXIT_SUCCESS;
}

// TEST CODE
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

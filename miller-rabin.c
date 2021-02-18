#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gmp.h>
#include <sys/random.h>
#include <time.h>

/*
mpz_t *modular_exponentation(int a, int b, mpz_t n) {
    // set c = 0
    mpz_t c;
    mpz_init(c);
    // set d = 1
    mpz_t d;
    mpz_init_set_ui(d, 1);
    // TODO: use the binary representation of b

    for (size_t i = k; i >= 0; i--) {
        // set c = 2c
        mpz_mul_ui(c, c, 2);
        // set d = (d*d) mod n
        mpz_powm_ui(d, d, 2, n);
        // TODO: if b_i == 1
        // set c = c + 1
        mpz_add_ui(c, c, 1);
        // set d = (d*a) mod n
        mpz_mul_ui(d, d, a);
        mpz_mod(d, d, n);
    }

    // return d
    return d;
}
*/

int witness(mpz_t a, mpz_t n) {
    // set t >= 1 and set u to odd int, and n-1 = 2^t u
    mpz_t t;
    mpz_t u;
    mpz_t n_1;

    mpz_init_set_ui(t, 0);
    // set u = n-1
    mpz_init_set(u, n);
    mpz_sub_ui(u, u, 1);
    // set n-1
    mpz_init_set(n_1, n);
    mpz_sub_ui(n_1, n_1, 1);

    // as long as u is even, increment t and floor divide u by 2
    while (mpz_even_p(u)) {
        mpz_add_ui(t, t, 1);
        mpz_fdiv_q_ui(u, u, 2);
    }
    // set x_0 to Modular exponentiation(a, u, n)
    mpz_t x;
    mpz_init(x);
    mpz_powm(x, a, u, n);
    /*
    mpz_out_str(stdout, 10, a); 
    mpz_out_str(stdout, 10, t); 
    mpz_out_str(stdout, 10, u); 
    mpz_out_str(stdout, 10, n_1); 
    mpz_out_str(stdout, 10, n); 
    mpz_out_str(stdout, 10, x); 
    */
    mpz_t x_prev;
    mpz_init_set(x_prev, x);
    for (size_t i = 1; mpz_cmp_ui(t, i) >= 0; i++) {
        // printf("loop\n");
        mpz_set(x_prev, x);
        // x_i = x_i-1^2 mod n
        mpz_powm_ui(x, x_prev, 2, n);
        // if x_i == 1 and x_i-1 != 1 and x_i-1 != n-1
        /*
        mpz_out_str(stdout, 10, x); 
        mpz_out_str(stdout, 10, x_prev); 
        mpz_out_str(stdout, 10, n_1); 
        */
        if (!mpz_cmp_ui(x, 1) && mpz_cmp_ui(x_prev, 1) && mpz_cmp(x_prev, n_1)) {
            mpz_clear(t);
            mpz_clear(u);
            mpz_clear(n_1);
            mpz_clear(x);
            mpz_clear(x_prev);
            //printf("inner loop\n");
            return 1;
        }
    }
    
    //mpz_out_str(stdout, 10, x); 
    // if x_t != 1
    if (mpz_cmp_ui(x, 1)) {
        mpz_clear(t);
        mpz_clear(u);
        mpz_clear(n_1);
        mpz_clear(x);
        mpz_clear(x_prev);
        //printf("test\n");
        return 1;
    }

    mpz_clear(t);
    mpz_clear(u);
    mpz_clear(n_1);
    mpz_clear(x);
    mpz_clear(x_prev);
    return 0;
}

/* n is an odd integer greater than 2, s is the number of random values to check against */
int miller_rabin(mpz_t n, int s) {
    // return early if n is even and not 2
    if (mpz_cmp_ui(n, 2) && mpz_even_p(n)) {
        //printf("returned early\n");
        return 0;
    }
    mpz_t a;
    mpz_init(a);

    int seed;
    srand(time(NULL));
    seed = rand();

    gmp_randstate_t rand;
    gmp_randinit_default(rand);
    gmp_randseed_ui(rand, seed);
    for (size_t j = 1; j <= s; j++) {
        // printf("mr\n");
        do {
        // set a to Random int between (1, n-1)
            mpz_urandomm(a, rand, n);
            //mpz_out_str(stdout, 10, a); 
            //printf("\n");
            //mpz_out_str(stdout, 10, a); 
        } while (!mpz_cmp_ui(a, 0));
        // call Witness function on (a,n), if witness, return failure
        if (witness(a, n)) {
            mpz_clear(a);
            return 0;
        }
    }
    // else, return success
    mpz_clear(a);
    gmp_randclear(rand);
    return 1;
}

int main(int argc, char *argv[]) {
    char mode;
    if (argc > 1) {
        mode = argv[2][0];
    }
    // grab a random int from C rand()
    int seed;
    srand(time(NULL));
    seed = rand();
    //printf("seed: %d\n", seed);
    
    // set up and seed GMP random
    gmp_randstate_t rand_int;
    gmp_randinit_mt(rand_int);
    gmp_randseed_ui(rand_int, seed);

    // candidate integer
    mpz_t n;
    mpz_init(n);
    
    // Use 40 rounds of Miller-Rabin, courtesy of StackOverflow # 6325576
    int s = 40;

    // randomly select int n for n > 2 until a prime number candidate is found
    do {
        mpz_urandomb(n, rand_int, 1024);
        //set LSB to 1 so that number is odd
        mpz_setbit(n, 0);
    } while (!miller_rabin(n,s));

    // print the prime number
    mpz_out_str(stdout, 10, n); 
    printf(" %s prime.\n", miller_rabin(n, s) ? "is": "is not");

    switch (mode) {
        case 'c':
            int confirm = mpz_probab_prime_p(n, 100);
            printf("probability of prime (2: definitely prime, 1: probably prime, 0: definitely composite): %d\n",
                confirm);
    }
    // free memory
    mpz_clear(n);
    gmp_randclear(rand_int);

    return 0;
}

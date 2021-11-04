#include "rsa.h"

/*
 * Given a candidate integer n and a base a, tests n to see if it is prime or 
 * composite using Fermat's Little Theorem.  
 */
int witness(mpz_t a, mpz_t n)
{
    // Set t >= 1 and set u to odd int, and n-1 = 2^t u
    mpz_t t, u, n_1;
    mpz_init_set_ui(t, 0);

    // Set u = n-1
    mpz_init_set(u, n);
    mpz_sub_ui(u, u, 1);

    // Set n-1
    mpz_init_set(n_1, n);
    mpz_sub_ui(n_1, n_1, 1);

    // As long as u is even, increment t and floor divide u by 2
    while (mpz_even_p(u))
    {
        mpz_add_ui(t, t, 1);
        mpz_fdiv_q_ui(u, u, 2);
    }

    // Set x_0 to Modular exponentiation(a, u, n)
    mpz_t x;
    mpz_init(x);
    mpz_powm(x, a, u, n);

    mpz_t x_prev;
    mpz_init_set(x_prev, x);
    for (size_t i = 1; mpz_cmp_ui(t, i) >= 0; i++)
    {
        mpz_set(x_prev, x);
        // x_i = x_i-1^2 mod n
        mpz_powm_ui(x, x_prev, 2, n);
        // If x_i == 1 and x_i-1 != 1 and x_i-1 != n-1
        if (!mpz_cmp_ui(x, 1) && mpz_cmp_ui(x_prev, 1) && mpz_cmp(x_prev, n_1))
        {
            mpz_clears(t, u, n_1, x, x_prev, NULL);

            return 1;
        }
    }
    
    // If x_t != 1
    if (mpz_cmp_ui(x, 1))
    {
        mpz_clears(t, u, n_1, x, x_prev, NULL);

        return 1;
    }

    mpz_clears(t, u, n_1, x, x_prev, NULL);

    // Leaving this as return 0 as miller_rabin relies on if (witness())
    // check to work
    return 0;
}

/* 
 * Given a candidate integer n, check it for primality by calling witness
 * function s number of times each with random base a.
 */
int miller_rabin(mpz_t n, int s)
{
    // Return early if n is even and not 2
    if (mpz_cmp_ui(n, 2) && mpz_even_p(n))
    {
        return 0;
    }
    mpz_t a;
    mpz_init(a);

    // Get seed for GMP
    int seed;
    srand(time(NULL));
    seed = rand();

    // Seed GMP
    gmp_randstate_t rand;
    gmp_randinit_default(rand);
    gmp_randseed_ui(rand, seed);
    for (size_t j = 1; j <= s; j++)
    {
        do
        {
        // Set a to Random int between (1, n-1)
            mpz_urandomm(a, rand, n);
        } while (!mpz_cmp_ui(a, 0));
        // Call Witness function on (a,n), if witness, return failure
        if (witness(a, n))
        {
            mpz_clear(a);

            return 0;
        }
    }

    // Else, return success
    mpz_clear(a);
    gmp_randclear(rand);

    // Leaving this as return 1 on success, as prime-generator function relies
    // on if (!miller_rabin()) check to work
    return 1;
}

// TEST CODE
/*
int main() {
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
    do
    {
        mpz_urandomb(n, rand_int, 1024);
        //set LSB to 1 so that number is odd
        mpz_setbit(n, 0);
    } while (!miller_rabin(n,s));

    // print the prime number
    mpz_out_str(stdout, 10, n); 
    printf(" %s prime.\n", miller_rabin(n, s) ? "is": "is not");

    // free memory
    mpz_clear(n);
    gmp_randclear(rand_int);

    return 0;
}
*/

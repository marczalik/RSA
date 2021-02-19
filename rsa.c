#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "prime-generator.c"

int rsa(int bt_len, int s) {
    mpz_t p;
    mpz_t p_1;
    mpz_t q;
    mpz_t q_1;
    mpz_t n;
    mpz_t e;
    mpz_t d;
    mpz_t phi;
    mpz_t gcd_e_phi;
    mpz_init(p);
    mpz_init(p_1);
    mpz_init(q);
    mpz_init(q_1);
    mpz_init(n);
    mpz_init(d);
    mpz_init(phi);
    mpz_init(gcd_e_phi);
    mpz_init_set_ui(e, 65537);
    
    // find suitable prime candidates for p and q    
    generate_prime(p, bt_len, s);
    do {
    generate_prime(q, bt_len, s);
    mpz_mul(n, p, q);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    mpz_mul(phi, p_1, q_1);
    mpz_gcd(gcd_e_phi, phi, e);
    } while (!mpz_cmp(p, q) || mpz_cmp_ui(gcd_e_phi, 1));
    /*
    mpz_mul(n, p, q);
    mpz_sub_ui(p_1, p, 1);
    mpz_sub_ui(q_1, q, 1);
    */
    
    // find d
    mpz_invert(d, e, phi);
}

int main() {
}

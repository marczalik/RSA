#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "prime-generator.c"

int generate_keys(mpz_t e, mpz_t d, mpz_t n, int bt_len, int s) {
    mpz_t p, p_1, q, q_1, phi, gcd_e_phi;
    mpz_inits(p, p_1, q, q_1, phi, gcd_e_phi, NULL);
    /*
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
    */
    // mpz_init_set_ui(e, 65537);
    
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

    mpz_clears(p, p_1, q, q_1, phi, gcd_e_phi, NULL);
}

int main() {
    mpz_t plaintext, cyphertext;
    mpz_inits(plaintext, cyphertext, NULL);
    mpz_set_ui(plaintext, 123456789);

    printf("Plaintext before encryption: ");
    mpz_out_str(stdout, 10, plaintext);
    printf("\n");

    mpz_t e, d, n;
    mpz_inits(d, n, NULL);
    mpz_init_set_ui(e, 65537);

    generate_keys(e, d, n, 2048, 40);

    printf("e: ");
    mpz_out_str(stdout, 10, e);
    printf("\n");
    printf("d: ");
    mpz_out_str(stdout, 10, d);
    printf("\n");
    printf("n: ");
    mpz_out_str(stdout, 10, n);
    printf("\n");

    mpz_powm(cyphertext, plaintext, e, n);

    printf("Cyphertext after encryption: ");
    mpz_out_str(stdout, 10, cyphertext);
    printf("\n");

    mpz_powm(plaintext, cyphertext, d, n);

    printf("Plaintext after decryption: ");
    mpz_out_str(stdout, 10, plaintext);
    printf("\n");

    mpz_clears(plaintext, cyphertext, e, d, n, NULL);
    
    return 0;
}

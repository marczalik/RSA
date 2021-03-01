#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "key-generator.c"

/* encrypt should take in message to encrypt plus <additional parameters> */
int encrypt(mpz_t plaintext, mpz_t cyphertext) {
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

    return 0;
}

/* decrypt should take in message to decrypt plus key */
int decrypt(mpz_t plaintext, mpz_t cyphertext, mpz_t d, mpz_t n) {
    mpz_powm(plaintext, cyphertext, d, n);

    return 0;
}

int main() {
    mpz_t plaintext, cyphertext;
    mpz_inits(plaintext, cyphertext, NULL);
    mpz_set_ui(plaintext, 123456789);

    printf("Plaintext before encryption: ");
    mpz_out_str(stdout, 10, plaintext);
    printf("\n");

    encrypt(plaintext, cyphertext);

    printf("Cyphertext after encryption: ");
    mpz_out_str(stdout, 10, cyphertext);
    printf("\n");

    decrypt(plaintext, cyphertext);

    printf("Plaintext after decryption: ");
    mpz_out_str(stdout, 10, plaintext);
    printf("\n");


    mpz_clears(plaintext, cyphertext, e, d, n, NULL);

    return 0;
}

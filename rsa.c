/*
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
*/
#include "rsa.h"

/* encrypt should take in filename of key plus <what?> */
int encrypt(char *keyfile, char *filein, char *fileout) {
    mpz_t e, n, plaintext, cyphertext;
    mpz_inits(e, n, plaintext, cyphertext, NULL);

    // Extract key
    open_key_file(e, n, keyfile);

    // Extract plaintext
    read_text_file(filein, plaintext);

    // Use key to encrypt message
    mpz_powm(cyphertext, plaintext, e, n);
    
    // Write cyphertext
    write_text_file(fileout, cyphertext);

    mpz_clears(e, n, plaintext, cyphertext, NULL);
    
    return 0;
}

/* decrypt should take in filename of key plus <what?> */
int decrypt(char *keyfile, char *filein, char *fileout) {
    mpz_t d, n, plaintext, cyphertext;
    mpz_inits(d, n, plaintext, cyphertext, NULL);

    // Extract key
    open_key_file(d, n, keyfile);

    // Extract cyphertext
    read_text_file(filein, cyphertext);

    // Use key to decrypt message
    mpz_powm(plaintext, cyphertext, d, n);

    // Write plaintext
    write_text_file(fileout, plaintext);

    mpz_clears(d, n, plaintext, cyphertext, NULL);

    return 0;
}

int open_key_file(mpz_t exponent, mpz_t n, char *filename) {
    FILE *fptr;

    fptr = fopen(filename, "r");
    
    if (!fptr) {
        return EXIT_FAILURE;
    }

    if (!mpz_inp_raw(exponent, fptr)) {
        return EXIT_FAILURE;
    }
    
    // Skip newline char
    fgetc(fptr);

    if (!mpz_inp_raw(n, fptr)) {
        return EXIT_FAILURE;
    }

    fclose(fptr);

    return 0;
}

int read_text_file(char *filename, mpz_t message) {
    FILE *fptr;

    fptr = fopen(filename, "r");

    if (!fptr) {
        return EXIT_FAILURE;
    }

    // Read text from file
    mpz_inp_str(message, fptr, 10);

    fclose(fptr);

    return 0;
}

int write_text_file(char *filename, mpz_t message) {
    FILE *fptr;

    fptr = fopen(filename, "w");

    if (!fptr) {
        return EXIT_FAILURE;
    }

    // Write text to file
    mpz_out_str(fptr, 10, message);

    fclose(fptr);

    return 0;
}

/*
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
    
    mpz_t e, d, n;
    mpz_inits(e, d, n, NULL);

    char *filename = "20210302-2057-Public-Key.txt";

    open_key_file(e, n, filename);

    mpz_out_str(stdout, 10, e);
    printf("\n");
    mpz_out_str(stdout, 10, n);
    printf("\n");

    mpz_clears(e, d, n, NULL);

    encrypt("20210302-2057-Public-Key.txt", "test-plain.txt", "test-cypher.txt");

    decrypt("20210302-2057-Secret-Key.txt", "test-cypher.txt", "test-decrypted.txt");

    return 0;
}
*/

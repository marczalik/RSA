/*
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
*/
#include "rsa.h"

/*      Given a keyfile and a message to encrypt, opens the keyfile, extracts the key
        and uses it to encrypt the message in filein. 
        Stores the encrypted result in fileout.         */
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
    
    return EXIT_SUCCESS;
}

/*      Given a keyfile and a message to decrypt, opens the keyfile, extracts the key
        and uses it to decrypt the message in filein. 
        Stores the decrypted result in fileout.         */
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

    return EXIT_SUCCESS;
}

/*      Opens a keyfile and extracts the resulting key values to exponent (e or d) and n.       */
int open_key_file(mpz_t exponent, mpz_t n, char *filename) {
    FILE *fptr;

    fptr = fopen(filename, "r");
    
    if (!fptr) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    if (!mpz_inp_raw(exponent, fptr)) {
        perror("Error: ");
        return EXIT_FAILURE;
    }
    
    // Skip newline char
    fgetc(fptr);

    if (!mpz_inp_raw(n, fptr)) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    fclose(fptr);

    return EXIT_SUCCESS;
}

/*      Reads the message from filename and stores it for encryption/decryption.        */
int read_text_file(char *filename, mpz_t message) {
    FILE *fptr;

    fptr = fopen(filename, "r");

    if (!fptr) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    // Read text from file
    mpz_inp_str(message, fptr, 10);

    fclose(fptr);

    return EXIT_SUCCESS;
}

/*      Writes the encrypted/decrypted message to filename.     */
int write_text_file(char *filename, mpz_t message) {
    FILE *fptr;

    fptr = fopen(filename, "w");

    if (!fptr) {
        perror("Error: ");
        return EXIT_FAILURE;
    }

    // Write text to file
    mpz_out_str(fptr, 10, message);

    fclose(fptr);

    return EXIT_SUCCESS;
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

# RSA with Miller-Rabin Primality Testing

## Description

RSA is an asymmetric public-key cryptosystem that allows users to securely send encrypted messages. The security of RSA is based on the inefficiency of factoring large integers, particularly when they are the product of two prime numbers. This program allows the user to generate key pairs for use in RSA, which are checked for primality using Miller-Rabin primality testing. The Miller-Rabin test is a probabilistic primality test that will determine, to a high degree of confidence, whether a given number is prime. This algorithm is based on Fermat's little theorem.

## Setup and Usage

RSA should not be used to directly encrypt messages. Instead, RSA (or any assymetric cryptographic function) should be used to encrypt a symmetric key due to speed and security. For this reason, this implementation of RSA encrypts
only keys, not messages, and enforces that the size of the to-be-encrypted key is less than the modulus used in RSA.

## Command Line Options

Option | Argument | Description
------ | -------- | -----------
-h     |          | Show usage documentation.
-g     | length   | Generate a key pair of the given length.
-e     |          | Encrypt file following -m flag.
-d     |          | Decrypt file following -m flag.
-k     | keyfile  | Use this file to encrypt/decrypt file.
-m     | filename | File to encrypt/decrypt.
-o     | filename | Destination file for output of encryption/decryption.

## TODO

Expand README, add gifs\
Replace commented out test code with debug macros\
Create Makefile
Continue adding errno/error checking\
Expand comments on miller-rabin.c
    

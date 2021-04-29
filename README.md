# RSA with Miller-Rabin Primality Testing

RSA should not be used to directly encrypt messages. Instead, RSA (or any assymetric cryptographic function) should be used to encrypt a symmetric key due to speed and security. For this reason, this implementation of RSA encrypts
only keys, not messages, and enforces that the size of the to-be-encrypted key is less than the modulus used in RSA.

TODO:  
    Continue adding errno/error checking  
    Create Makefile  
    Validate program structure sensibility  
    Expand comments on miller-rabin.c   
    

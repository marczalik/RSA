/* Header file for RSA functions */

/* Miller-Rabin functions */
int witness(mpz_t a, mpz_t n);
int miller_rabin(mpz_t n, int s);


/* Prime-Generator functions */
int generate_prime(mpz_t candidate, int bt_len, int s);


/* Key-Generator functions */
int generate_keys(mpz_t e, mpz_t d, mpz_t n, int bt_len, int s);
int save_keys(mpz_t e, mpz_t d, mpz_t n);
char *create_filename(char *timestr, char *filetype);
int create_new_keypair(int bt_len, int s);


/* RSA functions */
int encrypt(char *keyfile, char *filein, char *fileout);
int decrypt(char *keyfile, char *filein, char *fileout);
int open_key_file(mpz_t exponent, mpz_t n, char *filename);
int read_text_file(char *filename, mpz_t message);
int write_text_file(char *filename, mpz_t message);

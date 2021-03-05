/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
*/
#include "rsa.h"

#define OPTSTR "vg:edf:k:m:o:h"
#define USAGE_FMT "%s [-v] [-g length] [-e] [-d] [-k keyfile] [-m message] [-o output] [-h]\n"
#define ERR_FOPEN_KEYFILE "fopen(keyfile, r)"
#define ERR_FOPEN_MESSAGE "fopen(message, r)"
#define ERR_FOPEN_OUTPUT "fopen(output, w)"
#define ERR_EXEC_OPT "execute_option failed"
#define DEFAULT_PROGNAME "main"

extern int erro;
extern char *optarg;
extern int opterr, optind;

// struct copies from "how to write a good c main function"
typedef struct {
    int         verbose;
    char        mode;
    int         bt_len;
    char        *keyfile;
    char        *message;
    char        *output;
} options_t;

void usage(char *progname, int opt);
int execute_option(options_t *options);

/*      Handle command line arguments for RSA.  */
int main(int argc, char *argv[]) {
    int opt;
    options_t options = { 0, 0, 2048, "stdin", "stdout", "stdout" };

    opterr = 0;

    while ((opt = getopt(argc, argv, OPTSTR)) != EOF) {
        switch (opt) {
            case 'g':
                // Add functionality to generate keypair
                options.mode = opt;
                options.bt_len = atoi(optarg);
                break;
            case 'e':
                // Add encrypt functionality
                options.mode = opt;
                break;
            case 'd':
                // Add decrpy functionality
                options.mode = opt;
                break;
            case 'k':
                options.keyfile = optarg;
                break;
            case 'm':
                options.message = optarg;
                break;
            case 'o':
                options.output = optarg;
                break;
            case 'v':
                options.verbose += 1;
                break;
            case 'h':
            default:
                usage(basename(argv[0]), opt);
                break;
        }
    }

    if (execute_option(&options) != EXIT_SUCCESS) {
        perror(ERR_EXEC_OPT);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/*      Reports correct usage of main.  */
void usage(char *progname, int opt) {
    fprintf(stderr, USAGE_FMT, progname ? progname : DEFAULT_PROGNAME);
    exit(EXIT_FAILURE);
}

/*      Runs command line arguments.     */
int execute_option(options_t *options) {
    if (!options) {
        errno = EINVAL;
        return EXIT_FAILURE;
    }

    // Call functions
    if (options->mode == 'g') {
        if (!options->bt_len) {
            errno = EINVAL;
            return EXIT_FAILURE; 
        }
        create_new_keypair(options->bt_len, 40);
    }

    if (options->mode == 'e') {
        if (!options->keyfile || !options->message || !options->output) {
            errno = EINVAL;
            return EXIT_FAILURE; 
        }
        encrypt(options->keyfile, options->message, options->output);
    }

    if (options->mode == 'd') {
        if (!options->keyfile || !options->message || !options->output) {
            errno = EINVAL;
            return EXIT_FAILURE; 
        }
        decrypt(options->keyfile, options->message, options->output);
    }

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <getopt.h>

#define OPTSTR "vi:o:f:h"
#define USAGE_FMT "%s [-v] [-i inputfile] [-o outputfile] [-h]"

extern int erro;
extern char *optarg;
extern int opterr, optind;

// struct copies from "how to write a good c main function"
typedef struct {
    int         verbose;
    uint32_t    flags;
    FILE        *inputs;
    FILE        *output;
} options_t;

void usage(char *progname, int opt);

/* handle command line arguments */
int main(int argc, char *argv[]) {
    int opt;
    options_t options = { 0, 0x0, stdin, stdout };

    opterr = 0;

    while ((opt = getopt(argc, argv, OPTSTR)) != EOF) {
        switch (opt) {
            // TODO: add additional args
            case 'v':
                options.verbose += 1;
                break;
            case 'h':
            default:
                usage(basename(argv[0]), opt);
                break;
        }
    }

    return EXIT_SUCCESS;
}

void usage(char *progname, int opt) {
    fprintf(stderr, USAGE_FMT, progname ? progname : DEFAULT_PROGNAME);
    exit(EXIT_FAILURE);
}

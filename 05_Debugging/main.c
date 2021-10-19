#include <stdio.h>
#include <stdlib.h>

#include "range.h"

void argparse(int argc, char *argv[], int *start, int *stop, int *step)
{
    if (argc == 2) {
        *start = 0;
        *stop = atoi(argv[1]);
        *step = 1;
    } else if (argc == 3) {
        *start = atoi(argv[1]);
        *stop = atoi(argv[2]);
        *step = 1;
    }else if (argc == 4) {
        *start = atoi(argv[1]);
        *stop = atoi(argv[2]);
        *step = atoi(argv[3]);
    } else {
        printf("Usage:\n"
                "  %s - help\n"
                "  %s <<n>> - sequence 0, 1, ..., n\n"
                "  %s <<m>> <<n>> - sequence m, m+1, ..., n\n"
                "  %s <<m>> <<n>> <<s>> - sequence m, m+s, ..., n\n", 
                argv[0], argv[0], argv[0], argv[0]);
    } 
};

int main(int argc, char *argv[]) {
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for(range_init(&I); range_run(&I); range_next(&I))
            printf("%d\n", range_get(&I));
    return 0;
}

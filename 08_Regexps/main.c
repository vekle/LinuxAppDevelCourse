#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define POCKET_MAX_NUM 10

int main(int argc, char **argv) 
{
    if (argc < 4) {
        printf("Usage: <<regexp>> <<substitution>> <<string>>\n");
    }

    char *subst = argv[2];
    char *input = argv[3];

    regex_t preg;
    regmatch_t pmatch[POCKET_MAX_NUM];

    int errbuf_max_size = 1000;
    char errbuf[errbuf_max_size];

    int res = regcomp(&preg, argv[1], REG_EXTENDED);
    if (res != 0) {
        int errbuf_size = regerror(res, &preg, errbuf, errbuf_max_size);
        fprintf(stderr, "%s", errbuf);
        exit(EXIT_FAILURE);
    }

    res = regexec(&preg, input, POCKET_MAX_NUM, pmatch, 0);
    if (res != 0) {
        int errbuf_size = regerror(res, &preg, errbuf, errbuf_max_size);
        fprintf(stderr, "%s", errbuf);
        exit(EXIT_FAILURE);
    }

    int pocket_num = 0;
    for (int i = 0; i < POCKET_MAX_NUM; i++) {
        if (pmatch[i].rm_so != -1)
            pocket_num++;
    }

    //////////

    for (int i = 0; i < pmatch[0].rm_so; i++) {
        printf("%c", input[i]);
    }

    for (int i = 0; i < strlen(subst); i++) {
        if (subst[i] == '\\') {
            i++;
            if (isdigit(subst[i])) {
                int p_num = atoi(&subst[i]);
                if (p_num < 0 || p_num >= pocket_num) {
                    fprintf(stderr, "Nonexistent pocket %d\n", p_num);
                    printf("NE");
                } else {
                    for (int i = pmatch[p_num].rm_so; i < pmatch[p_num].rm_eo; i++) {
                        printf("%c", input[i]);
                    }
                }
                while (isdigit(subst[i+1])) {
                    i++;
                }
            } else if (subst[i] == '\\') {
                printf("\\");
            } else if (subst[i] == 'a') {
                printf("\a");
            } else if (subst[i] == 'b') {
                printf("\b");
            } else if (subst[i] == 'e') {
                printf("\e");
            } else if (subst[i] == 'f') {
                printf("\f");
            } else if (subst[i] == 'n') {
                printf("\n");
            } else if (subst[i] == 'r') {
                printf("\r");
            } else if (subst[i] == 't') {
                printf("\t");
            } else if (subst[i] == 'v') {
                printf("\v");
            } else if (subst[i] == '\'') {
                printf("\'");
            } else if (subst[i] == '\"') {
                printf("\"");
            }
            // add support for unicode, hex and octal numbers
        } else {
            printf("%c", subst[i]);
        }
    }

    for (int i = pmatch[0].rm_eo; i < strlen(input); i++) {
        printf("%c", input[i]);
    }
    printf("\n");

    regfree(&preg);
    return 0;
}
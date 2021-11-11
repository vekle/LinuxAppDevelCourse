#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#include <rhash.h>
#include <getline_cmd.h>

int get_hash(char *input, int algo_flag, int hash_base, char *output) {
    char digest[64];

    int res = 0;
    if (input[0] == '"') {
        input += 1;

        res = rhash_msg(algo_flag, input, strlen(input), digest);
        if (res < 0)
            fprintf(stderr, "Could not calculate hash of message\n");
    } else {
        res = rhash_file(algo_flag, input, digest);
        if (res < 0)
            perror("Could not calculate hash of file");
    }

    if (res >= 0)
        rhash_print_bytes(output, digest, rhash_get_digest_size(algo_flag), hash_base);

    return res;
}

int main() 
{
    rhash_library_init();
    char output[130];   

    char *cmd_line = NULL;
    unsigned cmd_line_len;
    while ((cmd_line_len = getline_cmd(&cmd_line)) != EOF) {

        char *algo_string = strtok(cmd_line, " \n");
        if (algo_string == NULL) {
            fprintf(stderr, "Input hash algorithm.\n");
            continue;
        }
        
        int algo_flag;
        if (strcasecmp(algo_string, "md5") == 0) {
            algo_flag = RHASH_MD5;
        } else if (strcasecmp(algo_string, "tth") == 0) {
            algo_flag = RHASH_TTH;
        } else if (strcasecmp(algo_string, "sha1") == 0) {
            algo_flag = RHASH_SHA1;
        } else {
            fprintf(stderr, "Supported hash algorithms: md5, sha1, tth.\n");
            continue;
        }
        
        int hash_base;    
        if (islower(algo_string[0])) {
            hash_base = RHPR_BASE64;
        } else {
            hash_base = RHPR_HEX;
        }

        char *input = strtok(NULL, " \n");
        if (input == NULL) {
            fprintf(stderr, "Input string or file name to hash.\n");
            continue;
        }

        int hash_res = get_hash(input, algo_flag, hash_base, output);
        if (hash_res < 0) {
            continue;
        } else {
            printf("%s\n", output);
        }

        if (cmd_line)
            free(cmd_line);
    }
}
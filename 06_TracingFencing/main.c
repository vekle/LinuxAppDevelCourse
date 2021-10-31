#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

enum ERROR_CODE {
    ERROR_OK = 0,
    ERROR_WRONG_ARGS,
    ERROR_INPUT_SIZE,
    ERROR_MEMORY,
    ERROR_OPEN_INPUT,
    ERROR_CLOSE_INPUT,
    ERROR_OPEN_OUTPUT,
    ERROR_CLOSE_OUTPUT,
    ERROR_DELETE_INPUT,
    ERROR_DELETE_OUTPUT,
    ERROR_READ_INPUT,
    ERROR_WRITE_OUTPUT
};

int main(int argc, char const *argv[])
{
    if (argc < 3)
        exit(ERROR_WRONG_ARGS);

    FILE *f_in = fopen(argv[1], "r");
    if (f_in == NULL) {
        perror("Could not open input file");
        exit(ERROR_OPEN_INPUT);
    }

    struct stat st;
    int ret = stat(argv[1], &st);
    if (ret < 0) {
        perror("Could not find size of input file");
        exit(ERROR_INPUT_SIZE);
    }
    long long file_size = st.st_size;

    // int ret = fseek(f_in, 0, SEEK_END);
    // if (ret) {
    //     if (ferror(f_in))
    //         perror("Could not find size of input file");
    //     else
    //         printf("Could not find size of input file\n");
    //     exit(ERROR_INPUT_SIZE);
    // } 
    // long long file_size = ftell(f_in);
    // if (file_size < 0) {
    //     perror("Could not find size of input file");
    //     exit(ERROR_INPUT_SIZE);
    // }
    // ret = fseek(f_in, 0, SEEK_SET);
    // if (ret) {
    //     if (ferror(f_in))
    //         perror("Could not find size of input file");
    //     else
    //         printf("Could not find size of input file\n");
    //     exit(ERROR_INPUT_SIZE);
    // }  

    char *file_content = malloc(sizeof(char) * file_size);
    if (file_content == NULL) {
        perror("Could not allocate memory for file content");
        exit(ERROR_MEMORY);
    }

    ret = fread(file_content, sizeof(char), file_size, f_in);
    if (ferror(f_in) || ret != file_size) {
        if (feof(f_in)) {
            printf("Error reading from input file: unexpected end of file\n");
        } else if (ferror(f_in)) {
            perror("Error reading from input file");
        } else {
            printf("Error reading from input file: unexpected error\n");
        }
        exit(ERROR_READ_INPUT);
    }

    ret = fclose(f_in);
    if (ret == EOF) {
        printf("Could not close input file\n");
        exit(ERROR_CLOSE_INPUT);
    }

    FILE *f_out = fopen(argv[2], "w");
    if (f_out == NULL) {
        perror("Could not open output file");
        exit(ERROR_OPEN_OUTPUT);
    }

    ret = fwrite(file_content, sizeof(char), file_size, f_out);
    fflush(f_out);
    if (ferror(f_out) || ret != file_size) {
        if (ferror(f_out)) {
            perror("Error writing to output file");
        } else {
            printf("Error writing to output file: unexpected error\n");
        }
        ret = remove(argv[2]);
        if (ret) {
            perror("Error deleting output file");
            exit(ERROR_DELETE_OUTPUT);
        }
        exit(ERROR_WRITE_OUTPUT);
    }

    ret = fclose(f_out);
    if (ret == EOF) {
        printf("Could not close output file\n");
        ret = remove(argv[2]);
        if (ret) {
            perror("Error deleting output file");
            exit(ERROR_DELETE_OUTPUT);
        }
        exit(ERROR_CLOSE_OUTPUT);
    }

    ret = remove(argv[1]);
    if (ret) {
        perror("Error deleting input file");
        exit(ERROR_DELETE_INPUT);
    }

    return 0;
}
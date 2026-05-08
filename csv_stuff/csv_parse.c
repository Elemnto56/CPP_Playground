#include <stdio.h>

int main(int argc, char** argv) {
    if (argc == 1) {fprintf(stderr, "No .csv was provided in args\n"); return 1;}

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {fprintf(stderr, "File not found\n"); return 1;}

    char buff[1024]={};
    if (!fgets(buff, 1024, fp)) {perror("File reading error: "); return 1;}

    
}
#include <stdio.h>
#include <string.h>

#include "io.h"
#include "funcs.h"

int main(int argc, char* argv[]){
    if (argc < 2) {
        help();
        return 0;
    }

    if (strcmp(argv[1], "-c") == 0){
        createTable(&argc, argv);
        return 0;
    }
}
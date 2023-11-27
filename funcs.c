#include <stdio.h>

#include <string.h>
#include "definitions.h"

int createTable(int* argc, char* argv[]){
    char filename[10 + NAME_SIZE + 5];
    sprintf(filename, "database/%s.txt", argv[2]);

    FILE *file;
    if(file = fopen(filename, "w")){
        fclose(file);
    } else {
        printf("Erro ao criar tabela %s\n", argv[2]);
        return 1;
    }
}
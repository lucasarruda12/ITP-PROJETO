#include <stdio.h>
#include <string.h>

#include "funcs.h"
#include "util.c"
#include "definitions.h"

#define NAME_SIZE 20

int createTable(){
    // PROMPT AO USUÁRIO
    char tableHeader[200] = {0};
    char tablename[NAME_SIZE + 1] = {0};
    char primaryKey[NAME_SIZE + 1] = {0};

    print_h_line(40);
    printf("Menu de criação de tabelas\n");
    print_h_line(40);

    printf("Nome da tabela (até %d caracteres): ", NAME_SIZE);
    getchar();
    fgets(tablename, NAME_SIZE, stdin);

    printf("Chave primária (int): ");
    fgets(primaryKey, NAME_SIZE, stdin);

    char primaryKey_type[2] = {'1','='};
    strcat(tableHeader, primaryKey_type);
    strcat(tableHeader, primaryKey);

    // MONTAR COLUNAS
    int choice = 1;

    while(choice){
        char columnName[NAME_SIZE + 1] = {0};
        int columnType = 0;

        print_h_line(40);
        printf("Nova coluna? (1. sim) (0. não) ");
        scanf("%d", &choice);
        if (choice == 0) break;

        printf("tipo de dado: (0. char) (1. int) (2. float) (3. double) (4. string): ");
        scanf("%d", &columnType);

        printf("Nome da coluna (até %d caracteres): ", NAME_SIZE);
        getchar();
        fgets(columnName, NAME_SIZE, stdin);
        columnName[strlen(columnName) - 1] = '\0';

        char columnType_string[4];

        sprintf(columnType_string, ",%d=", columnType);
        strcat(tableHeader, columnType_string);
        strcat(tableHeader, columnName);
    }

    // CRIAR ARQUIVO .txt
    char filename[NAME_SIZE + 5];
    sprintf(filename, "%s.txt", tablename);
    FILE *file;
    file = fopen(filename, "w");
    fclose(file);

    // MONTAR CABEÇALHO DA TABELA
    file = fopen(filename, "a");
    fprintf(file, tableHeader);
    fclose(file);
}
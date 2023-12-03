#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#include "definitions.h"

int isTable(char filename[NAME_SIZE]){
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL)
    {
        printf("Não foi possível encontrar a tabela %s\n", filename);
        printf("Cheque as tabelas existentes e tente novamente.\n");

        return 0;
    }

    fclose(file);
    return 1;
}

int find_next_marker(char line[256], char marker){
    for(int i = 0; i < 256; i++){
        if(line[i] == marker){
            return i;
        }
    }

    return 0;
}

int createTable(int* argc, char* argv[]){
    char filename[10 + NAME_SIZE + 5];
    char tableheader[255] = {0};

    sprintf(filename, "database/%s.txt", argv[2]);

    FILE *file;
    if(file = fopen(filename, "w")){
        fclose(file);
    } else {
        printf("Erro ao criar tabela %s\n", argv[2]);
        return 1;
    }

     // PRIVATE KEY
    strcat(tableheader, "(int)");
    strcat(tableheader, argv[3]);
    strcat(tableheader, "/;");

    for(int i = 4; i < *argc; i = i + 2){
        strcat(tableheader, "(");
        strcat(tableheader, argv[i]); // datatype
        strcat(tableheader, ")");
        strcat(tableheader, argv[i+1]); // nome da tabela
        strcat(tableheader, "/;");
    };

    if(file = fopen(filename, "a")){
        fprintf(file, "%s", tableheader);
        fclose(file);
    } else {
        printf("Erro ao adicionar cabeçalho à tabela %s\n", filename);
        return 1;
    }

    printf("Tabela %s criada com sucesso\n", filename);
    return 0;
}

int listTables(){
    DIR *directory;
    struct dirent *entry;
    char tablename[NAME_SIZE + 1];

    directory = opendir("database");

    if (directory == NULL){
        printf("Não foi possível acessar o Banco de Dados\n");
        return 1;
    }

    printf("Lista de tabelas:\n");

    while((entry = readdir(directory)) != NULL){
        if (entry->d_type == DT_REG){
            strcpy(tablename, entry->d_name);
            tablename[strlen(tablename) - 4] = '\0';

            printf("%s\n", tablename);
        }
    }

    if (closedir(directory) == -1){
        printf("Erro ao fechar diretório base");
    }
    
    return 0;
}

int dropTable(char tablename[NAME_SIZE + 1]){
    char filename[10 + NAME_SIZE + 5];
    sprintf(filename, "database/%s.txt", tablename);

    if(remove(filename) == 0){
        printf("Tabela %s apagada com sucesso.\n", tablename);
        return 0;
    } else {
        printf("Erro ao apagar a tabela %s\n", tablename);
        return 1;
    }
}

int insertInto(int* argc, char* argv[]){
    char line[256] = {0};
    char tableheader[256] = {0};
    char filename[10 + NAME_SIZE + 5];
    char newline[256] = {0};
    int pk;
    
    sprintf(filename, "database/%s.txt", argv[2]);

    if(isTable(filename) == 0) return 0;

    FILE *file;
    if(!(file = fopen(filename, "r"))){
        printf("Erro ao abrir arquivo da tabela %s\n", argv[2]);
        return 1;
    }

    fgets(tableheader, 255, file);

    printf("(Chave primária) ");
    scanf("%d", &pk);
    getchar();

    while(fgets(line, 255, file) != NULL){
        char string_pk[10] = {0};
        int i = 0;

        while(line[i] != '|'){
            string_pk[i] = line[i];
            i++;
        }

        string_pk[i] = '\0';

        if (pk == atoi(string_pk)){
            printf("Chave primária em uso.\n");
            return 1;
        }
    }

    fclose(file);

    while(strlen(tableheader) > 1){
        char datatype[15] = {0};
        char fieldname[45] = {0};
        int middle_marker = find_next_marker(tableheader, ')');
        int end_marker = find_next_marker(tableheader, '|');
        if (end_marker == 0) break;

        strncpy(datatype, tableheader + 1, middle_marker - 1);
        strncpy(fieldname, tableheader + middle_marker + 1, end_marker - middle_marker - 1);
        strcpy(tableheader, tableheader + end_marker + 1);

        printf("(%s) %s ", datatype, fieldname);

        char new_value[NAME_SIZE] = {0};

        fgets(new_value, NAME_SIZE, stdin);

        strncat(newline, new_value, strlen(new_value) - 1);
        strcat(newline, "|");
    }

    if(!(file = fopen(filename, "a"))){
        printf("Erro ao abrir arquivo da tabela %s\n", argv[2]);
        return 1;
    }

    fprintf(file, "%s\n", newline);
    fclose(file);
    printf("Tupla adicionada com Sucesso à tabela %s\n", filename);
}
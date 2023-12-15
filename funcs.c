#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>

#include "definitions.h"

bool is_table(char fname[NAME_SIZE]){
    FILE *file;
    
    if ((file = fopen(fname, "r")) == NULL)
    {
        printf("Não foi possível encontrar a tabela %s\n", fname);
        printf("Cheque as tabelas existentes e tente novamente.\n");

        return false;
    }

    fclose(file);
    return true;
}

/* Retorna o índice do primeiro (marker) em (string). */
int find_next_marker(char string[256], char marker){
    for(int i = 0; i < 256; i++){
        if(string[i] == marker){
            return i;
        }
    }

    return 0;
}

/* Retorna a quantidade de diferenças entre (string_a) e (string_b). */
int compare_strings(char string_a[], char string_b[]){
    int max = (strlen(string_a) < strlen(string_b)) ? strlen(string_a) : strlen(string_b);
    int diff = 0;

    for (int i = 0; i < max; i++){
        if(string_a[i] != string_b[i]){
            diff++;
        }
    }

    return diff;
}

/* Cria tabela a partir de argumentos da main */
int createTable(int* argc, char* argv[]){
    char fname[10 + NAME_SIZE + 5];
    char header[256] = {0};
    char col[64] = {0};

    sprintf(fname, "database/%s.txt", argv[2]);

    FILE *file;
    if(file = fopen(fname, "w")){
        fclose(file);
    } else {
        printf("Erro ao criar tabela %s\n", argv[2]);
        return 1;
    }

    /* Adc. chave primária ao cabeçalho */
    sprintf(header, "(int)%s|", argv[3]);

    /* Adc. coluna por coluna ao cabeçalho */
    for(int i = 4; i < *argc; i = i + 2){
        sprintf(col, "(%s)%s|", argv[i], argv[i+1]);
        strcat(header, col);
    };

    if(file = fopen(fname, "a")){
        fprintf(file, "%s", header);
        fclose(file);
    } else {
        printf("Erro ao adicionar cabeçalho à tabela %s\n", fname);
        return 1;
    }

    printf("Tabela %s criada com sucesso\n", fname);
    return 0;
}

/* Lista arquivos no diretório ./database */
int listTables(){
    DIR *dir;
    struct dirent *entry;

    char tname[NAME_SIZE + 1];

    dir = opendir("database");

    if (dir == NULL){
        printf("Não foi possível acessar o diretório base\n");
        return 1;
    }

    printf("Lista de tabelas:\n");

    while((entry = readdir(dir)) != NULL){
        if (entry->d_type == DT_REG){
            strcpy(tname, entry->d_name);
            tname[strlen(tname) - 4] = '\0';

            printf("%s\n", tname);
        }
    }

    if (closedir(dir) == -1){
        printf("Erro ao fechar diretório base");
    }
    
    return 0;
}


/* Apagar o arquivo ./database/(table).txt */
int dropTable(char table[NAME_SIZE + 1]){
    char fname[10 + NAME_SIZE + 5];
    sprintf(fname, "database/%s.txt", table);

    if(is_table(fname) == false) return 1;

    if(remove(fname) == 0){
        printf("Tabela %s apagada com sucesso.\n", fname);
        return 0;
    } else {
        printf("Erro ao apagar a tabela %s\n", fname);
        return 1;
    }
}


/* Insere dados na tabela */
int insertInto(int* argc, char* argv[]){
    char header[256] = {0};
    char fname[10 + NAME_SIZE + 5];
    char new_line[256] = {0};
    
    sprintf(fname, "database/%s.txt", argv[2]);

    if(is_table(fname) == false) return 0;

    FILE *file;
    if(!(file = fopen(fname, "r"))){
        printf("Erro ao abrir arquivo da tabela %s\n", argv[2]);
        return 1;
    }

    fgets(header, 255, file);
    

    /* Solicita chave primária */
    char header_copy[256];
    strcpy(header_copy, header);

    char *col = strtok(header_copy, "|");
    int new_pk = 0;

    printf("%s ", col);
    scanf("%d", &new_pk);
    getchar();

    /* Verifica chave primária */
    char line[256] = {0};
    char *pk;

    while(fgets(line, 255, file) != NULL){
        pk = strtok(line, "|");

        if(atoi(pk) == new_pk){
            printf("Chave primária já está em uso.\n");
            return 1;
        }
    }


    /* Copia a chave primária para a nova linha */
    sprintf(new_line, "%d|", new_pk);

    /* Solicita cada um dos valores */
    col = strtok(header, "|");
    char value[64] = {0};

    while(true){
        col = strtok(NULL, "|");

        if(col == NULL || strcmp(col, "\n") == 0) break;

        printf("%s ", col);
        fgets(value, 63, stdin);
        value[strlen(value) - 1] = '|';

        strncat(new_line, value, 64);
    }

    fclose(file);

    if(!(file = fopen(fname, "a"))){
        printf("Erro ao abrir arquivo da tabela %s\n", argv[2]);
        return 1;
    }

    fprintf(file, "%s\n", new_line);
    
    fclose(file);
    printf("Tupla adicionada com Sucesso à tabela %s\n", fname);
}


/* Apagar tupla de uma tabela */
int deleteFromTable(int* argc, char* argv[]){
    char fname[10 + NAME_SIZE + 5] = {0};
    char line[256] = {0};

    sprintf(fname, "database/%s.txt", argv[2]);

    if(is_table(fname) == false) return 0;

    FILE *file;
    if(!(file = fopen(fname, "r"))){
        printf("Erro ao abrir arquivo da tabela %s\n", argv[2]);
        return 1;
    }

    FILE *temp;
    if(!(temp = fopen("temp.txt", "a"))){
        printf("Erro ao criar arquivo temporário\n");
        return 1;
    }

    /* Buscar no arquivo uma linha com mesma chave primária */
    while(fgets(line, 255, file) != NULL){
        char pk[NAME_SIZE] = {0}; 
        int i = 0;

        /* Procurar na linha apenas a chave primária */
        while(line[i] != '|'){
            pk[i] = line[i];
            i++;
        }

        pk[i] = '\0';

        /* Copiar pro temp apenas as linhas com chave primária diferente do argumento */
        if (atoi(argv[3]) == atoi(pk)) continue;

        fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    remove(fname);
    rename("temp.txt", fname);

    printf("Tupla removida com sucesso.\n");
    return 0;
}

/* Listar todas as linhas da tabela */
int listTableData(int* argc, char* argv[]){
    char fname[10 + NAME_SIZE + 5] = {0};
    char line[256];

    sprintf(fname, "database/%s.txt", argv[2]);

    if(is_table(fname) == 0) return 0;

    FILE *file;
    if(!(file = fopen(fname, "r"))){
        printf("Erro ao abrir arquivo da tabela %s\n", argv[2]);
        return 1;
    }

    while(fgets(line, 255, file) != NULL){
        printf("%s", line);
    }

    fclose(file);
}

/* Procurar na tabela */
int searchTable(int* argc, char* argv[]){
    char fname[10 + NAME_SIZE + 5] = {0};
    char header[256] = {0};
    char line[256];

    Column colunas[10] = {0};

    sprintf(fname, "database/%s.txt", argv[2]);

    if(is_table(fname) == false) return 0;

    FILE *file;
    if(!(file = fopen(fname, "r"))){
        printf("Erro ao abrir arquivo da tabela %s\n", argv[2]);
        return 1;
    }

    fgets(header, 255, file);
    printf("Pesquisar por:\n");

    int counter = 0;
    while(strlen(header) > 1){
        int middle_marker = find_next_marker(header, ')');
        int end_marker = find_next_marker(header, '|');
        if (end_marker == 0) break;

        strncpy(colunas[counter].datatype, header + 1, middle_marker - 1);
        strncpy(
            colunas[counter].columnName,
            header + middle_marker + 1,
            end_marker - middle_marker - 1
        );
        strcpy(header, header + end_marker + 1);

        counter++;
    }

    int column_choice = 0;

    for (int i = 0; i< counter; i++){
        printf(
            "%d -- (%s) %s\n",
            i,
            colunas[i].datatype, 
            colunas[i].columnName
        );
    } 

    scanf("%d", &column_choice);
    getchar();

    int method = 0;

    printf("Pesquisar valores:\n");
    printf("0 -- Maiores que: \n");
    printf("1 -- Maiores ou iguais a: \n");
    printf("2 -- Iguais a: \n");
    printf("3 -- Menores que: \n");
    printf("4 -- Menores ou iguais a: \n");
    printf("5 -- Próximos à (STRING): \n");

    scanf("%d", &method);
    getchar();

    printf("Valor: ");
    char value[NAME_SIZE] = {0};
    fgets(value, NAME_SIZE - 1, stdin);
    value[strlen(value) - 1] = '\0';

    while(fgets(line, 255, file) != NULL){
        char line_copy[256];
        strcpy(line_copy, line);

        char *token = strtok(line_copy, "|");

        for(int i = 0; i < column_choice; i++){
            token = strtok(NULL, "|");
        }

        switch (method) {
        case 0:
            if (atoi(token) > atoi(value)){
                printf("%s", line);
            }
            break;
        
        case 1:
            if (atoi(token) >= atoi(value)){
                printf("%s", line);
            }
            break;
        
        case 2:
            if (atoi(token) == atoi(value)){
                printf("%s", line);
            }
            break;
        
        case 3:
            if (atoi(token) < atoi(value)){
                printf("%s", line);
            }
            break;

        case 4:
            if (atoi(token) <= atoi(value)){
                printf("%s", line);
            }
            break;

        case 5:
            if (compare_strings(value, token) < 2){
                printf("%s", line);
            }
            break;

        default:
            break;
        }
    }
}
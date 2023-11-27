#include <dirent.h>

int listTablesUI(){
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
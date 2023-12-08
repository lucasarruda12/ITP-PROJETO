#include <stdio.h>

#include "definitions.h"

void help(){
    printf("INSTRUÇÕES DE USO DO PROGRAMA:\n");
    printf("Nomes de tabelas e colunas devem ter até %d caracteres\n\n", NAME_SIZE);

    printf("Criar Tabela:\n");
    printf("    c [Nome da Tabela] [Private Key] [DataType 1] [Coluna 1] [Datatype 2] [Coluna 2]...\n");

    printf("Listar todas as tabelas:\n");
    printf("    l\n");

    printf("Criar uma nova tupla na tabela\n");
    printf("    i [TABELA]\n");

    printf("Listar todos os dados de uma tabela:\n");
    printf("    u [TABELA]\n");

    printf("Pesquisar valores em uma tabela:\n");
    printf("    p [TABELA]\n");

    printf("Apagar uma tupla de uma tabela\n");
    printf("    a [TABELA] [PRIMARY KEY]\n");

    printf("Apagar Tabela:\n");
    printf("    d [Nome da Tabela]\n");

    printf("Interface de Texto:\n");
    printf("    g\n");
}
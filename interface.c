#include <stdio.h>

#include "createTable.c"

int interface(){
    print_h_line(40);
    printf("BEM-VINDO(A) AO SGBD ITP\n");
    printf("Feito por: Lucas Manoel Arruda Pinheiro\n");
    print_h_line(40);
    printf("1. Criar nova tabela.\n");
    // printf("2. Editar tabela existente.\n");
    printf("3. Sair.\n");

    int choice = 3;
    scanf("%d", &choice);

    if (choice == 1){
        createTable();
    }

    if (choice == 3){
        return 0;
    }
}
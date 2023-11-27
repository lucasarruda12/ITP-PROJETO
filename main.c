#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aux/funcs.h"
#include "aux/definitions.h"

#include "util/print_h_line.c"
#include "util/clear_terminal.c"
#include "util/check_for_file.c"

#include "src/createTable.c"
#include "src/dropTable.c"

int main(){
    while(1){
        print_h_line(40);
        printf("BEM-VINDO(A) AO SGBD ITP\n");
        printf("Feito por: Lucas Manoel Arruda Pinheiro\n");
        print_h_line(40);
        printf("1. Criar uma tabela\n");
        printf("2. Listar tabelas\n");
        printf("3. Modificar uma tabela\n");
        printf("4. Listar dados de uma tabela\n");
        printf("5. Pesquisar em uma tabela\n");
        printf("6. Apagar uma tabela\n");
        printf("7. SQLucas\n");
        printf("8. Sair\n");

        int choice = 3;
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            createTableUI();
            break;
        case 6:
            dropTableUI();
            break;
        case 8:
            return 0;
        
        default:
            printf("Opção inválida.\nPor favor tente novamente\n");
            break;
        }
    }
}
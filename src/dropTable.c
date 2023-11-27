
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

int dropTableUI(){
    char tablename[NAME_SIZE + 1];
    int choice = 0;

    print_h_line(40);
    printf("Nome da tabela a ser Apagada: ");

    fgets(tablename, NAME_SIZE, stdin);
    tablename[strlen(tablename) - 1] = '\0';

    if (check_for_file(tablename) == 0){
        return 0;
    }

    printf("Você quer apagar a tabela %s? (1. Sim) (0. Não)\n", tablename);
    printf("ATENÇÃO: ESSA AÇÃO É IRREVERSÍVEL.\n");
    scanf("%d", &choice);
    getchar();

    if (choice == 0) return 0;
    
    dropTable(tablename);
}
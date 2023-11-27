
int createTable(char tablename[NAME_SIZE], char tableHeader[200]){
    char filename[10 + NAME_SIZE + 5];
    sprintf(filename, "database/%s.txt", tablename);

    // CRIAR ARQUIVO .txt
    FILE *file;
    if(file = fopen(filename, "w")){
        fclose(file);
    } else {
        printf("Erro ao criar tabela %s\n", tablename);
        return 1;
    }

    // MODIFICAR ARQUIVO COM O CABEÇELHO DA TABELA
    if(file = fopen(filename, "a")){
        fprintf(file, "%s", tableHeader);
        fclose(file);
    } else {
        printf("Erro ao adicionar cabeçalho à tabela %s\n", tablename);
        return 1;
    }

    printf("Tabela %s criada com sucesso\n", tablename);
    return 0;
}

int createTableUI(){
    // PROMPT AO USUÁRIO
    char tableHeader[200] = {0};
    char tablename[NAME_SIZE + 1] = {0};
    char primaryKey[NAME_SIZE + 1] = {0};
    char columnName[NAME_SIZE + 1] = {0};
    int columnType = 0;
    int choice = 1;

    print_h_line(40);
    printf("Menu de criação de tabelas\n");
    print_h_line(40);

    printf("Nome da tabela (até %d caracteres): ", NAME_SIZE);
    fgets(tablename, NAME_SIZE, stdin);
    tablename[strlen(tablename) - 1] = '\0';

    printf("Chave primária (int): ");
    fgets(primaryKey, NAME_SIZE, stdin);
    primaryKey[strlen(primaryKey) - 1] = '\0';

    char primaryKey_type[2] = {'1','='};
    strcat(tableHeader, primaryKey_type);
    strcat(tableHeader, primaryKey);

    // MONTAR COLUNAS
    while(choice){
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

    createTable(tablename, tableHeader);
    return 0;
}
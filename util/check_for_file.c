int check_for_file(char filename[NAME_SIZE]){
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
#include <stdio.h>
#include <string.h>

#include "io.h"
#include "funcs.h"

int main(int argc, char* argv[]){
    if (argc < 2) {
        help();
        return 0;
    }

    switch (*argv[1]){
    case 'l':
        return listTables();
        break;
    case 'd':
        return dropTable(argv[2]);
        break;
    case 'c':
        return createTable(&argc, argv);
        break;
    case 'i':
        return insertInto(&argc, argv);
        break;
    default:
        help();
        return 0;
    }
}
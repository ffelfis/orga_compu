#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define error_cant_param "Cantidad incorrecta de argumentos"
#define mensaje_de_ayuda "Usage:\n \ttp0 -h\n\ttp0 -V\n\ttp0 [options] file\nOptions:\n\t-V, --version\t\tPrint version and quit.\n\t-h, --help\t\tPrint this information.\n\t-l, --lines\t\tPrint number of lines in file.\n\t-w, --words\t\tPrint number of words in files.\n\t-c, --characters\tPrint number of characters in file.\n\t-i, --input\t\tPath to input file.\nExamples:\n\n\ttp0 -w -i input.txt"

// Muestra ayuda
void ayuda(){
    printf("%s\n",mensaje_de_ayuda);
}

// Muestra error y termina ejecución
void error(char *mensaje){
    fprintf(stderr,"%s\n",mensaje);
    // fprintf se usa para escribir en stderr
    exit(1);
}

int main(int argc, char *argv[]){
//argc -> argument count, argv -> argument vector

    // Verifica la cantidad de argumentos
    if (argc < 2 || argc > 4){
        error(error_cant_param);
    }
    // Verifica por pedido de ayuda en el primer argumento
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        ayuda();
        return 0;
    }
    return 0;
}

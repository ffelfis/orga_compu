#include <stdio.h>
#include <string.h>

#define error_cant_param "Cantidad incorrecta de argumentos"
#define mensaje_de_ayuda "Usage:\n \ttp0 -h\n\ttp0 -V\n\ttp0 [options] file\nOptions:\n\t-V, --version\tPrint version and quit.\n\t-h, --help\tPrint this information.\n\t-l, --lines\tPrint number of lines in file.\n\t-w, --words\tPrint number of words in files.\n\t-c, --characters\tPrint number of characters in file.\n\t-i, --input\tPath to input file.\nExamples:\n\n\ttp0 -w -i input.txt"

// Función para mostrar ayuda
void ayuda(){
    printf("%s\n",mensaje_de_ayuda);
}

// Función para mostrar error y salir
void error(char *mensaje){
    printf(stderr,"%s\n",mensaje);
    exit(1);
}

//argc -> argument count, argv -> argument vector
int main(int argc, char *argv[]){

    // Verifica la cantidad de argumentos
    if (argc < 2 || argc > 5){
        error(error_cant_param);
    }
    // Verifica por pedido de ayuda en el primer argumento
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        ayuda();
        return 0;
    }
    return 0;
}

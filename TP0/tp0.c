#include <stdio.h>
#include <stdlib.h>

#define error_cant_param "Cantidad incorrecta de argumentos"
#define mensaje_de_ayuda "Usage:\n \ttp0 -h"

// Funcion para mostrar ayuda
void ayuda(){
    printf("%s\n",mensaje_de_ayuda);
}

//argc -> argument count, argv -> argument vector
int main(int argc, char *argv[]){

    // Verifica la cantidad de argumentos
    if (argc < 2 || argc > 5){
        error(error_cant_param, 1);
    }
    // Verifica por pedido de ayuda en el primer argumento
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        ayuda();
        return 0;
    }
    return 0;
}

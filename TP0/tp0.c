#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define error_cant_param "Cantidad incorrecta de argumentos"
#define error_param_incorrectos "Las opciones ingresadas son incorrectas"
#define error_archivo_inexistente "El archivo que intenta abrir no existe"
#define mensaje_de_ayuda "Usage:\n \ttp0 -h\n\ttp0 -V\n\ttp0 [options] file\nOptions:\n\t-V, --version\t\tPrint version and quit.\n\t-h, --help\t\tPrint this information.\n\t-l, --lines\t\tPrint number of lines in file.\n\t-w, --words\t\tPrint number of words in files.\n\t-c, --characters\tPrint number of characters in file.\n\t-i, --input\t\tPath to input file.\nExamples:\n\n\ttp0 -w -i input.txt"
#define version_num "tp0 v1.0"

// Muestra ayuda
void ayuda(){
    printf("%s\n",mensaje_de_ayuda);
}

// Muestra la versión del programa
void version(){
    printf("%s\n",version_num);
}

// Muestra error y termina ejecución
void error(char *mensaje){
    fprintf(stderr,"%s\n",mensaje);
    // fprintf se usa para escribir en stderr
    exit(0);
    // exit termina la ejecución del programa
}

// Cuenta caracteres
int contar_caracteres(FILE *archivo){
    printf("Conteo de caracteres.\n");
}

// Cuenta palabras
int contar_palabras(FILE *archivo){
    printf("Conteo de palabras.\n");
}

// Cuenta líneas
int contar_lineas(FILE *archivo){
    printf("Conteo de líneas.\n");
}

int main(int argc, char *argv[]){
//argc -> argument count, argv -> argument vector

    // Puntero a archivo
    FILE *file;

    // Verifica la cantidad de argumentos
    if (argc < 2 || argc > 4){
        error(error_cant_param);
    }

    // Verifica por pedido de ayuda en el primer argumento
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        // Por si hay algo luego del pedido de ayuda
        if (argc != 2) error(error_cant_param);
        ayuda();
        return 0;
    }

    // Verifica por pedido de versión en el primer argumento
    else if ((strcmp(argv[1], "-V") == 0) || (strcmp(argv[1], "--version") == 0)){
        // Por si hay algo luego del pedido de versión
        if (argc != 2) error(error_cant_param);
        version();
        return 0;
    }

    // Verifica por pedido de caracteres en el primer argumento y entrada en el segundo argumento
    else if (((strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "--characters") == 0)) && ((strcmp(argv[2], "-i")) || (strcmp(argv[2], "--input")))){
        // Por si hay algo luego del nombre del archivo
        if (argc != 4) error(error_cant_param);

        // Se intenta abrir el archivo en modo lectura
        file = fopen(argv[3], "r");
        if (file == NULL) error(error_archivo_inexistente);

        int num;
        num = contar_caracteres(file);
        return 0;
    }

    // Verifica por pedido de palabras en el primer argumento y entrada en el segundo argumento
    else if (((strcmp(argv[1], "-w") == 0) || (strcmp(argv[1], "--words") == 0)) && ((strcmp(argv[2], "-i")) || (strcmp(argv[2], "--input")))){
        // Por si hay algo luego del nombre del archivo
        if (argc != 4) error(error_cant_param);

        // Se intenta abrir el archivo en modo lectura
        file = fopen(argv[3], "r");
        if (file == NULL) error(error_archivo_inexistente);

        int num;
        num = contar_palabras(file);
        return 0;
    }

    // Verifica por pedido de líneas en el primer argumento y entrada en el segundo argumento
    else if (((strcmp(argv[1], "-l") == 0) || (strcmp(argv[1], "--lines") == 0)) && ((strcmp(argv[2], "-i")) || (strcmp(argv[2], "--input")))){
        // Por si hay algo luego del nombre del archivo
        if (argc != 4) error(error_cant_param);

        // Se intenta abrir el archivo en modo lectura
        file = fopen(argv[3], "r");
        if (file == NULL) error(error_archivo_inexistente);

        int num;
        num = contar_lineas(file);
        return 0;
    }     

    // Opciones ingresadas incorrectas
    else {
        error(error_param_incorrectos);
    }

    return 0;
}
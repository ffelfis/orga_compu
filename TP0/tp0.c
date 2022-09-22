#include <stdio.h>
#include <stdlib.h> // Uso de exit() [return fuera de main]
#include <string.h> // Uso de strcmp() [compara strings]
#include <stdbool.h> // Uso de [true, false]
#include <ctype.h> // Uso de isspace() [chequea si es caracter]

#define error_cant_param "Cantidad incorrecta de argumentos"
#define error_param_incorrectos "Las opciones ingresadas son incorrectas"
#define error_archivo_inexistente "El archivo que intenta abrir no existe"
#define mensaje_de_ayuda "Usage:\n \ttp0 -h\n\ttp0 -V\n\ttp0 [options] file\nOptions:\n\t-V, --version\t\tPrint version and quit.\n\t-h, --help\t\tPrint this information.\n\t-l, --lines\t\tPrint number of lines in file.\n\t-w, --words\t\tPrint number of words in files.\n\t-c, --characters\tPrint number of characters in file.\n\t-i, --input\t\tPath to input file.\nExamples:\n\n\ttp0 -w -i input.txt"
#define version_num "tp0 v1.0"

// Muestra ayuda
void ayuda()
{
    printf("%s\n",mensaje_de_ayuda);
}

// Muestra la versión del programa
void version()
{
    printf("%s\n",version_num);
}

// Muestra error y termina ejecución
void error(char *mensaje)
{
    fprintf(stderr,"%s\n",mensaje);
    // fprintf se usa para escribir en stderr
    exit(1);
    // exit termina la ejecución del programa
    // en lugar de return 1, lo hace fuera de main
}

// Cuenta caracteres
int contar_caracteres(FILE *archivo)
{
    char ch;
    int contador = 0;

    while ((ch = fgetc(archivo)) != EOF)
    {
        if ((ch != '\n') || (ch != ' ') || (ch != '\t') || (ch != '\0'))
            contador++;
    }

    fclose(archivo);
    return contador;
}

// Cuenta palabras
int contar_palabras(FILE *archivo){

    char ch;
    int contador = 0;
    // white space: espacio, tabulación, salto de línea
    bool white_space = true;
    // white_space se usa para comparar contra caracteres.
    // En rigor se usa para mantener un seguimiento de lo que
    // se estaba leyendo entre espacios blancos y [no espacios blancos]
    // Si se lee espacio blanco:
    //      white_space = true
    // Si se lee algo que no es espacio blanco
    //      white_space = false
    
    while ((ch = fgetc(archivo)) != EOF)
    {
        if (white_space && !isspace(ch))
        {
            // Si (espacio blanco && no espacio blanco)
            // Cambio a caracter. INICIO DE NUEVA PALABRA.
            contador++; // Cuenta palabra
            // Ahora se está leyendo algo [no espacio blanco]
            white_space = false;
        }
        else if (!white_space && isspace(ch))
        {
            // Si (no espacio blanco && espacio blanco)
            // Cambio a espacio blanco. TERMINA LA PALABRA
            white_space = true;
        }
    }

    fclose(archivo);
    return contador;
}

// Cuenta líneas
int contar_lineas(FILE *archivo)
{    
    char ch;
    int contador = 0;

    while ((ch = fgetc(archivo)) != EOF)
    {
        if (ch == '\n')
        {
            contador++;
        }
    }
    fclose(archivo);
    return contador;
}

int main(int argc, char *argv[])
{
//argc -> argument count, argv -> argument vector

    // Puntero a archivo
    FILE *file;

    // Verifica la cantidad de argumentos
    if (argc < 2 || argc > 4)
    {
        error(error_cant_param);
    }

    // Verifica por pedido de ayuda en el argumento 1
    else if ((strcmp(argv[1], "-h") == 0) || 
             (strcmp(argv[1], "--help") == 0))
    {
        // Verifica que la cantidad de argumentos sea 2
        if (argc != 2) error(error_cant_param);
        ayuda();
        return 0;
    }

    // Verifica por pedido de versión en el argumento 2
    else if ((strcmp(argv[1], "-V") == 0) || 
             (strcmp(argv[1], "--version") == 0))
    {
        // Verifica que la cantidad de argumentos sea 2
        if (argc != 2) error(error_cant_param);
        version();
        return 0;
    }

    // Verifica por pedido de caracteres en el argumento 1 y entrada en el argumento 2
    else if (((strcmp(argv[1], "-c") == 0) || 
              (strcmp(argv[1], "--characters") == 0)) && 
             ((strcmp(argv[2], "-i") == 0) || 
              (strcmp(argv[2], "--input") == 0)))
    {
        // Verifica que la cantidad de argumentos sea 4
        if (argc != 4) error(error_cant_param);

        // Se intenta abrir el archivo en modo lectura
        file = fopen(argv[3], "r");
        if (file == NULL) error(error_archivo_inexistente);

        int num;
        num = contar_caracteres(file);
        printf("%d %s\n", num, argv[3]);
        return 0;
    }

    // Verifica por pedido de palabras en el argumento 1 y entrada en el argumento 2
    else if (((strcmp(argv[1], "-w") == 0) || 
              (strcmp(argv[1], "--words") == 0)) && 
             ((strcmp(argv[2], "-i") == 0) || 
              (strcmp(argv[2], "--input") == 0)))
    {
        // Verifica que la cantidad de argumentos sea 4
        if (argc != 4) error(error_cant_param);

        // Se intenta abrir el archivo en modo lectura
        file = fopen(argv[3], "r");
        if (file == NULL) error(error_archivo_inexistente);

        int num;
        num = contar_palabras(file);
        printf("%d %s\n", num, argv[3]);
        return 0;
    }

    // Verifica por pedido de líneas en el argumento 1 y entrada en el argumento 2
    else if (((strcmp(argv[1], "-l") == 0) || 
              (strcmp(argv[1], "--lines") == 0)) && 
             ((strcmp(argv[2], "-i")) || 
              (strcmp(argv[2], "--input"))))
    {
        // Verifica que la cantidad de argumentos sea 4
        if (argc != 4) error(error_cant_param);

        // Se intenta abrir el archivo en modo lectura
        file = fopen(argv[3], "r");
        if (file == NULL) error(error_archivo_inexistente);

        int num;
        num = contar_lineas(file);
        printf("%d %s\n", num, argv[3]);
        return 0;
    }     

    // Salida por opciones ingresadas incorrectas
    else
    {
        error(error_param_incorrectos);
    }

    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define error_cant_param "Cantidad incorrecta de argumentos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define error_param_incorretos "Los argumentos ingresados son incorrectos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define error_inval_regla "La regla ingresada en inválida."
#define error_inval_celda "El número de celdas es inválido."
#define mensaje_ayuda "Uso:\n\tautcel -h\n\tautcel -V\n\tautcel R N inputfile [-o outputprefix]\nOpciones:\n\t-h, --help\tImprime este mensaje.\n\t-V, --version\tDa la version del programa.\n\t-o\t\tPrefijo de los archivos de salida.\nEjemplos:\n\tautcel 30 80 inicial -o evolucion\n\tCalcula la evolución del autómata \"Regla 30\",\n\ten un mundo unidimensional de 80 celdas, por 80 iteraciones.\n\tEl archivo de salida se llamará evolucion.pbm.\n\tSi no se da un prefijo para los archivos de salida,\n\tel prefijo será el nombre del archivo de entrada."
#define mensaje_version "autcel v1.0"

/* Muestra el error y sale de la ejecución */
void error(char *mensaje)
{
	fprintf(stderr, "%s\n", mensaje);
	exit(1);
}

/* Verifica argumentos numéricos */
/* Toma un string y el mensaje de error */
/* Devuelve el número si es válido */
int validateNum(char *palabra, char* mensaje_error)
{
	int numero;
	char *resto;
	
	numero = (int) strtol(palabra, &resto, 10);

	/* Verifica si el string es solo un número positivo y nada más */
	if (!strcmp(resto, "") == 0 || numero == 0 || numero < 0)
	{
		error(mensaje_error);
	}
	else printf("Función isValid: El número es válido.\n");
	return numero;
}

/*Abro y verifico que el archivo Seed existe: si existe devuelvo 1 y puntero
a archivo x parámetro, si no existe devuelvo 0*/
int openSeedFile(const char* arg ,FILE* seedFile){
	//Abro el archivo
	if((seedFile = fopen(arg, "r"))){
		return 0;
	}
	//printf("Error: El archivo no existe, ");
	return 1;
}


void closeSeedFile(FILE* seedFile){
	fclose(seedFile);
}


/* Validar que archivo semilla se encuentre en formato correcto */
/* Si el archivo es correcto devuelve true, sino devuelve false*/
bool validateSeed(FILE* seedFile, int* seed, int size){
	char aux[size];

	if(fgets(aux, size+1, seedFile)){
		int i = 0;
		//Chequeo si tengo valores numéricos
		while( i<(size+1) && isdigit(aux[i])){
			seed[i] = (int)aux[i] - '0';
			i++;
		}

		for(int j = 0; j<i; j++){
			printf("%i", seed[j]);
			}
		printf("%c",'\n');

		if(i<9){
			printf("El archivo no tiene una semilla válida\n");
			fclose(seedFile);
			return false;
		}
		return true;
	}

	return false;
}



int main(int argc, char *argv[])
{
	int numRegla; /* Guardará el número de regla */
	int numCelda; /* Guardará el número de celdas */

	/* Verificación inicial de argumentos */
	if (argc < 2 || argc > 6)
	{
		error(error_cant_param);
	}

	/* Verifica pedido de ayuda en argumento 1 */
	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
	{
		/* Verifica que la cantidad de argumentos sea 2 */
        if (argc != 2) error(error_cant_param);
        printf("%s\n", mensaje_ayuda);
        return 0;
	}

	/* Verifica pedido de versión en argumento 1 */
	if (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0)
	{
		/* Verifica que la cantidad de argumentos sea 2 */
        if (argc != 2) error(error_cant_param);
        printf("%s\n", mensaje_version);
        return 0;
	}

	/* Verifica regla y tamaño de la matriz para 4 argumentos */
	if (argc == 4)
	{
		printf("Tiene 4 argmentos.\n");

		numRegla = validateNum(argv[1], error_inval_regla);
		printf("Número de regla: %d\n", numRegla); /*BORRAR*/

		numCelda = validateNum(argv[2], error_inval_celda);
		printf("Número de celdas: %d\n", numCelda); /*BORRAR*/

		/* Verificar si el archivo de argv[3] existe */
		printf("Archivo semilla: %s\n", argv[3]);

		printf("Archivo salida: %s.pbm\n", argv[3]);

		return 0;
	}

	/* Verifica regla y tamaño de la matriz para 6 argumentos */
	if (argc == 6)
	{
		printf("Tiene 6 argmentos.\n");

		numRegla = validateNum(argv[1], error_inval_regla);
		printf("Número de regla: %d\n", numRegla); /*BORRAR*/

		numCelda = validateNum(argv[2], error_inval_celda);
		printf("Número de celdas: %d\n", numCelda); /*BORRAR*/

		/* Verificar si el archivo de argv[3] existe */
		printf("Archivo semilla: %s\n", argv[3]);

		if (strcmp(argv[4], "-o") == 0)
		{
			printf("Tiene prefijo para salida: %s\n", argv[4]);
		}

		printf("Archivo salida: %s.pbm\n", argv[5]);

		return 0;
	}

	/* Captura error de argumentos: último else */
	else
	{
		error(error_param_incorretos);
	}

	printf("Pasa lectura de argumentos.\n"); /*BORRAR*/

	return 0;
}

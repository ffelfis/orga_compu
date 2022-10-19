#include <stdio.h> /*FILE, fprint(), fopen(), fclose(), rewind()*/
#include <string.h> /*strcmp()*/

#include "utilidades.h"

#define error_cant_param "Cantidad incorrecta de argumentos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define error_param_incorretos "Los argumentos ingresados son incorrectos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define error_inval_regla "La regla ingresada en inválida"
#define error_inval_celda "El número de celdas es inválido"
#define error_archivo_inexistente "El archivo que intenta abrir no existe"
#define error_prefijo_salida "Prefijo de salida inválido"
#define mensaje_ayuda "Uso:\n\tautcel -h\n\tautcel -V\n\tautcel R N inputfile [-o outputprefix]\nOpciones:\n\t-h, --help\tImprime este mensaje.\n\t-V, --version\tDa la version del programa.\n\t-o\t\tPrefijo de los archivos de salida.\nEjemplos:\n\tautcel 30 80 inicial -o evolucion\n\tCalcula la evolución del autómata \"Regla 30\",\n\ten un mundo unidimensional de 80 celdas, por 80 iteraciones.\n\tEl archivo de salida se llamará evolucion.pbm.\n\tSi no se da un prefijo para los archivos de salida,\n\tel prefijo será el nombre del archivo de entrada."
#define mensaje_version "autcel v1.0"

int main(int argc, char *argv[])
{
	unsigned int numRegla; /* Guardará el número de regla */
	unsigned int numCelda; /* Guardará el número de celdas */

	FILE *file; /* Puntero al archivo de entrada */

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

	/* Verifica regla, tamaño de la matriz y archivo para 4 argumentos */
	if (argc == 4)
	{
		printf("Tiene 4 argmentos.\n");

		numRegla = validateNum(argv[1], error_inval_regla);

		numCelda = validateNum(argv[2], error_inval_celda);

		/* Verifica si el archivo de argv[3] existe */
		printf("Archivo semilla: %s\n", argv[3]);
		file = fopen(argv[3], "r");
		if (file == NULL) error(error_archivo_inexistente);
		validarSeed(file, numCelda);

		/* Crear matrix de dimensión numCelda x numCelda */

		/* Completar primera fila de matriz */

		/* Usar proximo() */

		/* Crear archivo de salida */

		printf("Archivo salida: %s.pbm\n", argv[3]);

		fclose(file);

		return 0; /* Termina la ejecución */
	}

	/* Verifica regla y tamaño de la matriz para 6 argumentos */
	if (argc == 6)
	{
		printf("Tiene 6 argmentos.\n");

		numRegla = validateNum(argv[1], error_inval_regla);

		numCelda = validateNum(argv[2], error_inval_celda);

		/* Verifica si el archivo de argv[3] existe */
		printf("Archivo semilla: %s\n", argv[3]);
		file = fopen(argv[3], "r");
		if (file == NULL) error(error_archivo_inexistente);
		validarSeed(file, numCelda);
		rewind(file); /* Resetea el puntero al inicio del archivo */

		if (strcmp(argv[4], "-o") == 0)
		{
			printf("Tiene prefijo para salida: %s\n", argv[4]);
		}
		else
		{
			error(error_prefijo_salida);
		}

		/* Crea la matriz de dimensión numCelda x numCelda */
		//printf("Crea la matriz\n");
		unsigned char matriz[numCelda][numCelda];

		/* Completa la primera fila de la matriz */
		//printf("Completa la fila 1\n");
		
		/*  matriz: puntero a primer elemento de arreglo de 2 dimensiones */
		/* *matriz: puntero a primer elemento de arreglo[numCelda] -> caracter */
		unsigned char *ptr_matriz = *matriz;
		
		fillRow1(file, ptr_matriz, numCelda);

		/* IMPRIME PRIMERA FILA DE MATRIZ BORRAR */
/*
		for (int i=0; i<numCelda; i++)
		{
			printf("%c ", matriz[0][i]);
		}
		printf("\n");
*/
		/* Usar proximo() */
		ptr_matriz = *matriz; /* Reset posición (0, 0)*/
		/* numCelda-1 ya que la primer fila está completa */
		for (int i=0; i<(numCelda-1); i++)
		{
			for (int j=0; j<numCelda; j++)
			{
				matriz[i+1][j] = proximo(ptr_matriz, i, j, numRegla, numCelda);
			}
		}

		/* IMPRIMIR MATRIZ */
		for (int i=0; i<numCelda; i++)
		{
			for (int j=0; j<numCelda; j++)
			{
				printf("%c ", matriz[i][j]);
			}
			printf("\n");
		}

		/* Crear archivo de salida */

		printf("Archivo salida: %s.pbm\n", argv[5]);

		fclose(file);

		return 0; /* Termina la ejecución */
	}

	/* Captura error de argumentos: último else */
	else
	{
		error(error_param_incorretos);
	}

	printf("Pasa lectura de argumentos.\n"); /*BORRAR*/

	return 0;
}

#include <stdio.h>
#include <stdlib.h> /*exit(), strtol()*/
#include <stdbool.h> /*true, false*/
#include <ctype.h> /*isdigit(), isspace()*/

#define error_caracter "El archivo tiene caracteres inválidos"
#define error_numCelda "La cantidad de celdas y caracteres no coincide"


/// @brief Muestra mensaje de error y sale de la ejecución
/// @param mensaje 
void error(char *mensaje)
{
	fprintf(stderr, "%s\n", mensaje);
	exit(1);
}


/// @brief Verifica números en cadena (palabra)
/// @param palabra 
/// @param mensaje_error De no ser número termina la ejecución con mensaje de error
/// @return número válido como unsigned int
unsigned int validateNum(char *palabra, char* mensaje_error)
{
	unsigned int numero;
	char *resto;
	
	numero = (int) strtol(palabra, &resto, 10);

	/* Verifica si el string es solo un número positivo y nada más */
	if (!strcmp(resto, "") == 0 || numero == 0 || numero < 0)
	{
		error(mensaje_error);
	}
	
	return numero;
}


/// @brief Verifica {'0', '1'}, {#celdas == #caracteres}, si no termina y devuelve error
/// @param seedFile 
/// @param numCelda 
void validarSeed(FILE *seedFile, unsigned int numCelda)
{
	char ch; /* Lectura de caracter */
	char last; /* Guarda el último caracter (REDUNDANTE) */
	unsigned int contador = 0; /* Cuenta caracteres */

	while ((ch = fgetc(seedFile)) != EOF)
	{
		last = ch; /* (REDUNDANTE) */
		/* Si no es white space: '\n' ' ' EOL */
		if (!isspace(ch))
        {
			/* Si no es '0' ó '1': error */
			if (!(ch == '0' || ch == '1'))
			{
				error(error_caracter);
			}
			contador++;
        }
		/* Si es white space distinto a EOL: error */
        else if (isspace(ch) && (ch != 10))
        {
			error(error_caracter);
        }
	}

	/* verifica que el último caracter sea el EOL (REDUNDANTE) */
	if (last != 10)
	{
		error(error_caracter);
	}

	/* Verifica que la cantidad de caracteres coincida con numCelda */
	if (contador != numCelda)
	{
		error(error_numCelda);
	}
	/* Resetea el puntero al inicio del archivo */ 
	//rewind(seedFile);
}


/// @brief Rellena la primera fila con los valores del archivo de entrada
/// @param seedFile 
/// @param a puntero a la posición (0, 0) de la matriz
/// @param N Cantidad de filas y columnas de la matriz
void fillRow1(FILE *seedFile, unsigned char *a, unsigned int N)
{
	unsigned char ch;

	for (int i=0; i<N; i++)
	{
		*a = fgetc(seedFile);
		a++;
	}
}


/// @brief Calcula el próximo estado de la celda indicada por (i, j)
/// @param a puntero a posición (0, 0) de la matriz
/// @param i fila de celda actual
/// @param j columna de celda actual
/// @param regla 
/// @param N Cantidad de filas y columnas de la matriz
/// @return Próximo estado de la celda
unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N)
{
	int divisiones = 0; 
	unsigned char valor = regla;

	/* Hay que posicionar el puntero */
	a = (a + (N*i)) + j; /* Mueve el puntero a la posición requrida */

	if (j == 0)
	{
		divisiones = (*(a+N-1)-'0')*4 + (*a-'0')*2 + (*(a+1)-'0');
	}
	else if (j == (N-1))
	{
		divisiones = (*(a-1)-'0')*4 + (*a-'0')*2 + (*(a-N+1)-'0');
	}
	else
	{
		divisiones = (*(a-1)-'0')*4 + (*a-'0')*2 + (*(a+1)-'0');
	}

	for (int k=0; k<divisiones; k++)
	{
		valor = valor / 2;
	}
	valor = valor % 2;

	return (unsigned char) valor + '0';
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define error_cant_param "Cantidad incorrecta de argumentos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define error_param_incorretos "Los argumentos ingresados son incorrectos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define mensaje_ayuda "Uso:\n\tautcel -h\n\tautcel -V\n\tautcel R N inputfile [-o outputprefix]\nOpciones:\n\t-h, --help\tImprime este mensaje.\n\t-V, --version\tDa la version del programa.\n\t-o\t\tPrefijo de los archivos de salida.\nEjemplos:\n\tautcel 30 80 inicial -o evolucion\n\tCalcula la evolución del autómata \"Regla 30\",\n\ten un mundo unidimensional de 80 celdas, por 80 iteraciones.\n\tEl archivo de salida se llamará evolucion.pbm.\n\tSi no se da un prefijo para los archivos de salida,\n\tel prefijo será el nombre del archivo de entrada."
#define mensaje_version "autcel v1.0"

/* Muestra el error y sale de la ejecución */
void error(char *mensaje)
{
	fprintf(stderr, "%s\n", mensaje);
	exit(1);
}

/* Ayuda */
void ayuda()
{
	printf("%s\n", mensaje_ayuda);
}

/* Versión */
void version()
{
	printf("%s\n", mensaje_version);
}

int main(int argc, char *argv[])
{
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
        ayuda();
        return 0;
	}

	/* Verifica pedido de versión */
	if (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0)
	{
		/* Verifica que la cantidad de argumentos sea 2 */
        if (argc != 2) error(error_cant_param);
        version(mensaje_version);
        return 0;
	}

	/* Captura error de argumentos */
	else
	{
		error(error_param_incorretos);
	}

	printf("Pasa lectura de argumentos.\n");

	return 0;
}

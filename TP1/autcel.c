#include <stdio.h>

#define error_cant_param "Canidad incorrecta de argumentos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."

/* Muestra el error y sale de la ejecución */
void error(char *mensaje)
{
	fprintf(stderr, "%s\n", mensaje);
}

int main(int argc, char *argv[])
{
	/* Verificación inicial de argumentos */
	if (argc < 2 || argc > 6)
	{
		error(error_cant_param);
	}

	printf("Fin de ejecución.\n");

	return 0;
}

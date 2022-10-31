#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* PROXIMO_ASM define si se usa o no la funci�n en Assembly */
/*====================================*/
//#define PROXIMO_ASM
/*====================================*/

#define error_cant_param "Cantidad incorrecta de argumentos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define error_param_incorretos "Los argumentos ingresados son incorrectos.\nIngrese \"autcel -h\" o \"autcel --help\" para más información."
#define error_inval_regla "La regla ingresada en inválida."
#define error_inval_celda "El número de celdas es inválido."
#define mensaje_ayuda "Uso:\n\tautcel -h\n\tautcel -V\n\tautcel R N inputfile [-o outputprefix]\nOpciones:\n\t-h, --help\tImprime este mensaje.\n\t-V, --version\tDa la version del programa.\n\t-o\t\tPrefijo de los archivos de salida.\nEjemplos:\n\tautcel 30 80 inicial -o evolucion\n\tCalcula la evolución del autómata \"Regla 30\",\n\ten un mundo unidimensional de 80 celdas, por 80 iteraciones.\n\tEl archivo de salida se llamará evolucion.pbm.\n\tSi no se da un prefijo para los archivos de salida,\n\tel prefijo será el nombre del archivo de entrada."
#define mensaje_version "autcel v1.0"
#define INIT_CHOP 60
#define CHOP_SIZE 30
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
	//else printf("Función isValid: El número es válido.\n");
	return numero;
}

#ifdef PROXIMO_ASM
extern unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char R, unsigned int N);
#endif

typedef enum{
	TRUE,
	FALSE
}bool_t;

void destroy_string (char *str);
char * string_merge (char * str1, char * str2);
char * read_line(FILE *file, bool_t *eof);
/*Generacion de automata*/
FILE* inicializar_pbm(char* archivo_pbm, int n);
int generar_automata(FILE* archivo_salida, char* valor_inicial,unsigned char regla, int n);
int cargar_valor_incial(char* valor_inicial, unsigned char* matriz, int n);
int exportar_fila(FILE* archivo_salida, unsigned char * fila, int n);

#ifndef PROXIMO_ASM
unsigned char proximo(unsigned char* a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N);
#endif

int main(int argc, char *argv[])
{
	FILE * archivo_semilla = NULL;
	FILE * archivo_salida = NULL;
	char * nombre_archivo_salida = NULL;//Variable utilizada para guardar la direccion de memoria del archivo de salida mas su extension
	char * linea = NULL;//Variable utilizada para guardar el estado inicial del automata
	char pbm[] = ".pbm";//Arreglo utilizado para agregar la extension pbm al archivo de salida

	bool_t eof;
	int numRegla; /* Guardará el número de regla */
	int numCelda; /* Guardará el número de celdas */
	/* Verificación inicial de argumentos */

	if (argc < 2 || argc > 6 || argc == 5 || argc == 3)
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
		//printf("Tiene 4 argmentos.\n");

		numRegla = validateNum(argv[1], error_inval_regla);
		if((numRegla<1) | (numRegla>255)) error(error_inval_regla);

		numCelda = validateNum(argv[2], error_inval_celda);

		/*Abro el archivo semilla*/
		if((archivo_semilla = fopen(argv[3], "r"))==NULL){
			fprintf(stderr, "Error al abrir archivo semilla.\n");
			return 0;
		}
		/*Creo un string con el nombre del archivo de salida mas su extension pbm*/
		if((nombre_archivo_salida=string_merge(argv[3],pbm))==NULL){
			fclose(archivo_semilla);
			fprintf(stderr,"Error al solicitar memoria dinámica.\n");
			return 0;
		}
		/*Abro el archivo de slaida en modo escritura. Si no se puede cierra los flujos y elimina la memoria solicitada*/
		if((archivo_salida = fopen(nombre_archivo_salida, "w"))==NULL){
			fprintf(stderr, "Error al crear archivo de salida.\n");
			fclose(archivo_semilla);
			destroy_string(nombre_archivo_salida);
			return 0;
		}

	}

	/* Verifica regla y tamaño de la matriz para 6 argumentos */
	if (argc == 6)
	{
		//printf("Tiene 6 argmentos.\n");

		numRegla = validateNum(argv[1], error_inval_regla);
		if((numRegla<1)|(numRegla>255)) error(error_inval_regla);
		numCelda = validateNum(argv[2], error_inval_celda);

		/* Verificar si el archivo de argv[3] existe */
		//printf("Archivo semilla: %s\n", argv[3]);
/*
		if (strcmp(argv[4], "-o") == 0)
		{
			printf("Tiene prefijo para salida: %s\n", argv[4]);
		}
*/
		/*Abro el archivo semilla*/
		if((archivo_semilla = fopen(argv[3], "r"))==NULL){
			fprintf(stderr, "Error al abrir archivo semilla.\n");
			return 0;
		}
		/*Creo un string con el nombre del archivo de salida mas su extension pbm*/
		if((nombre_archivo_salida=string_merge(argv[5],pbm))==NULL){
			fclose(archivo_semilla);
			fprintf(stderr,"Error al solicitar memoria dinámica.\n");
			return 0;
		}
		if((archivo_salida = fopen(nombre_archivo_salida, "w"))==NULL){
			fprintf(stderr, "Error al crear archivo de salida.\n");
			fclose(archivo_semilla);
			destroy_string(nombre_archivo_salida);
			return 0;
		}
	

	}

	/* Captura error de argumentos: último else 
	else
	{
		error(error_param_incorretos);
	}*/

	/*Inicializo el archivo PBM con el formato y la cantidad de filas y columnas*/
	if((archivo_salida=inicializar_pbm(nombre_archivo_salida,numCelda))==NULL){
		fclose(archivo_semilla);
		return 0;
	}
	fprintf(stdout,"Leyendo estado inicial...\n");
	if((linea=read_line(archivo_semilla,&eof))==NULL){
		fclose(archivo_semilla);
		fclose(archivo_salida);
		return 0;
	}

	fprintf(stdout,"Grabando %s\n",nombre_archivo_salida);
	if((generar_automata(archivo_salida, linea,(unsigned char)numRegla, numCelda))!=0){
		destroy_string(linea);
		fclose(archivo_semilla);
		fclose(archivo_salida);
		return 0;	
	}

	fprintf(stdout,"Listo!\n");
	fclose(archivo_semilla);
	fclose(archivo_salida);
	destroy_string(linea);
	return 0;
}


FILE* inicializar_pbm(char* archivo_pbm, int n) {
	FILE* file = fopen(archivo_pbm, "w");
	if (!file){
		fprintf(stderr, "Error al crear el archivo de salida.\n");
		return 0;
    }

	fprintf(file, "P1\n# feep.pbm\n%i %i\n", n, n);

	return file;
}

void destroy_string (char *str) {
	if(str==NULL)
		return;
	free(str);
	return;
}

char * string_merge (char * str1, char * str2){
	size_t len1=0;
	size_t len2=0;
	char * mrg=NULL;
	size_t i=0;

	if (str1==NULL  || str2==NULL){
		return NULL;
	}
	len1=strlen(str1);
	len2=strlen(str2);
	if((mrg=(char * )malloc(sizeof(char)*(len1+len2+1)))==NULL){
		return NULL;
	}
	for(i=0;i<len1;i++){
		mrg[i]=str1[i];
	}
	for(i=0;i<len2;i++){
		mrg[i+len1]=str2[i];
	}
	mrg[len1+len2]='\0';
	return mrg;
}

char * read_line(FILE *file, bool_t *eof) {
	size_t alloc_size, used_size;
	char * str;
	char * aux;
	char c;

	if(file == NULL || eof == NULL){
		fprintf(stderr, "Error argumentos nulos.\n");		
		return NULL;
	}
	if((str=(char *)malloc(sizeof(char)*INIT_CHOP))==NULL){
		fprintf(stderr, "Error al solicitar memoria dinámica.\n");
		return NULL;
	}
	alloc_size = INIT_CHOP;
	used_size = 0;
	*eof = FALSE;
	while((c = fgetc(file)) != EOF && c!= '\n'){
		if(used_size == alloc_size-3){
			if((aux=(char *)realloc(str, (alloc_size+CHOP_SIZE)*sizeof(char))) == NULL){
				destroy_string(str);
				fprintf(stderr, "Error al solicitar memoria dinámica.\n");
				return NULL;
			}
			str = aux;
			alloc_size +=CHOP_SIZE;
		}
		str[used_size++] = c;
	}
	str[used_size] = '\0';
	if(c == EOF){
	*eof = TRUE;
	}
	return str;
}


int generar_automata(FILE* archivo_salida, char* valor_inicial,unsigned char regla, int n) {

	unsigned char (* aux)[n] = NULL;
	unsigned char * matriz = NULL;
	size_t len=0;
	size_t i,j;
	
	if(archivo_salida==NULL || valor_inicial==NULL){
		fprintf(stderr, "Error argumentos nulos.\n");			
		return 1;
	}
	if((len=strlen(valor_inicial))!=n){
		fprintf(stderr, "%lu %i\n",(long unsigned int)len,n);
		fprintf(stderr, "Error en la cantidad de valores iniciales.\n");
		return 1;
	}
	if((matriz = (unsigned char *)malloc(sizeof(unsigned char)*n*n))==NULL){
		fprintf(stderr, "Error al solicitar memoria dinámica.\n");
		return 1;
	}

	if (cargar_valor_incial(valor_inicial, matriz, n) != 0) {
		free(matriz);
		return 1;		
	}
	aux = (unsigned char (*)[n]) matriz;

	exportar_fila(archivo_salida, &(aux[0][0]), n);
	for (i = 0; i < n-1; i++) {
		for (j = 0; j < n; j++) {
			aux[i+1][j] = proximo(matriz, i, j, regla, n);
		}
		exportar_fila(archivo_salida, &(aux[i+1][0]), n);
	}
	free(matriz);
	return 0;		
}

int cargar_valor_incial(char* valor_inicial, unsigned char* matriz, int n) {
	unsigned char (* aux)[n] = NULL;
	size_t i;
	int val;

	if(valor_inicial==NULL || matriz==NULL){
		fprintf(stderr, "Error argumentos nulos.\n");			
		return 1;		
	}

	aux = (unsigned char (*)[n]) matriz;

	for(i=0;i<n;i++){
		//val=valor_inicial[i] - '0';
		val=valor_inicial[i];
		//if(val!=0 && val!=1){
		if(val!=48 && val!=49){
			fprintf(stderr, "Error: el archivo inicial no cumple con el formato.\n");		
			return 1;
		}
		aux[0][i] = val;
	}
	return 0;
}

int exportar_fila(FILE* archivo_salida, unsigned char * fila, int n){
	size_t i;

	if(archivo_salida==NULL || fila==NULL){
		fprintf(stderr, "Error argumentos nulos.\n");			
		return 1;
	}

	for (i = 0; i < n; i++)	{
		fprintf(archivo_salida, "%c ", fila[i]);
	}
	fprintf(archivo_salida, "\n");
	return 0;
}

#ifndef PROXIMO_ASM
unsigned char proximo(unsigned char* a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N){
	unsigned char (* aux)[N] = NULL;
	char previo, central, siguiente;
	int posicion;

	aux = (unsigned char (*)[N])a;
	if (j == 0) {
		previo = aux[i][N-1];
		siguiente = aux[i][j+1];
	} else if (j == N-1) {
		previo = aux[i][j-1];
		siguiente = aux[i][0];
	} else {
		previo = aux[i][j-1];
		siguiente = aux[i][j+1];
	}
	central = aux[i][j];

	previo = previo - 48;
	central = central - 48;
	siguiente = siguiente - 48;

	posicion = previo << 2 | central << 1 | siguiente << 0;

	return ((1 & (regla >> posicion)) + 48);
}
#endif

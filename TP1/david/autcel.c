#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CHOP 40
#define CHOP_SIZE 20

typedef enum{
	TRUE,
	FALSE
}bool_t;

void destroy_string (char *str);
char * read_line(FILE *file, bool_t *eof);
/*Generacion de automata*/
FILE* inicializar_pbm(char* archivo_pbm, int n);
int generar_automata(FILE* archivo_salida, char* valor_inicial,unsigned char regla, int n);
int cargar_valor_incial(char* valor_inicial, unsigned char* matriz, int n);
int exportar_fila(FILE* archivo_salida, unsigned char * fila, int n);
unsigned char proximo(unsigned char* a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N);

int main(void)
{
	FILE * archivo_semilla = NULL;
	char * nombre_archivo_semilla = "inicial";
	FILE * archivo_salida = NULL;
	char * nombre_archivo_salida = "evolucion.pbm";
	char * linea = NULL;
	bool_t eof;



	int n=80;//Valor provisorio para realizar algunas pruebas
	
	/*Abro el archivo semilla*/
	if((archivo_semilla = fopen(nombre_archivo_semilla, "r"))==NULL){
		fprintf(stderr, "Error al abrir archivo semilla.\n");
		return 0;
	}

	/*Inicializo el archivo PBM con el formato y la cantidad de filas y columnas*/
	if((archivo_salida=inicializar_pbm(nombre_archivo_salida,n))==NULL){
		fclose(archivo_semilla);
		return 0;
	}
	
	if((linea=read_line(archivo_semilla,&eof))==NULL){
		fclose(archivo_semilla);
		fclose(archivo_salida);
		return 0;
	}


	if((generar_automata(archivo_salida, linea,126, n))!=0){
		destroy_string(linea);
		fclose(archivo_semilla);
		fclose(archivo_salida);
		return 0;	
	}

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
		fprintf(stderr, "%lu %i\n",len,n);
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
		val=valor_inicial[i] - '0';
		if(val!=0 && val!=1){
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
		fprintf(archivo_salida, "%i ", fila[i]);
	}
	fprintf(archivo_salida, "\n");
	return 0;
}

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

	posicion = previo << 2 | central << 1 | siguiente << 0;

	return (1 & (regla >> posicion));
}
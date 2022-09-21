#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Muestra la version del programa
void version()
{
    printf("%s\n",version_num);
}

// Muestra error y termina ejecucion
void error(char *mensaje)
{
    fprintf(stderr,"%s\n",mensaje);
    // fprintf se usa para escribir en stderr
    exit(0);
    // exit termina la ejecucion del programa
}

char * string_token(char *str,const char *delim,char **temp)
{
	register char *tok;

	if(str!=NULL)
	{
		for(tok=str;*tok;tok++)
			if(strchr(delim,*tok)!=NULL)
				break;
		if(!(*tok))
			*temp=tok;
		else{
			*tok='\0';
			*temp=tok+1;
		}
	}else{
		if(!(**temp))
			return NULL;
		str=*temp;
		for(tok=str;*tok;tok++)
			if(strchr(delim,*tok)!=NULL)
				break;

		if(!(*tok)){
			*temp=tok;
			return str;
		}else{
			*tok='\0';
			*temp=tok+1;
		}
	}
	return str;
}

char * clone_string (const char * orig)
{
	size_t len=0;
	size_t i=0;
    char * clone=NULL;

	if(orig==NULL )
		NULL;

	len=strlen(orig);

	if((clone=(char *)malloc(sizeof(char)*(len+1)))==NULL)
		NULL;
	
	for(i=0;i<=len;i++)
		clone[i]=orig[i];

	return clone;
}

void destroy_string (char *str)
{
	if(str==NULL)
		return;
	free(str);
	return;
}

void destroy_string_array(char **str_arr, size_t len)
{
	size_t i=0;

	if(str_arr==NULL)
		return;

	for(i = 0; i < len; i++)
	{
		free(str_arr[i]);
		str_arr[i] = NULL;
	}
	free(str_arr);
	str_arr=NULL;
	return;
}

char ** split_string(char * str,char * delim, size_t *len)
{
	char *dup, *q, *p,*temp;
	size_t n, i;
    char ** str_arr;

	if(str==NULL || delim==NULL || len==NULL)
		return NULL;

	if((dup=clone_string(str))==NULL)
		return NULL;

	for(n=0,i=0;dup[i];i++)
		if(strchr(delim,dup[i])!=NULL)
			n++;

	if((str_arr=(char **)malloc(sizeof(char*)*(n+1)))==NULL){
		destroy_string(dup);
		*len=0;
		return NULL;
	}
	for(i=0,q=dup;(p= string_token(q,delim,&temp))!=NULL;q=NULL,i++)
	{
		if((str_arr[i] =clone_string(p)) ==NULL)
		{
			destroy_string_array(str_arr, i);
			destroy_string(dup);
			*len=0;
			return NULL;
		}
	}
	destroy_string(dup);
	*len=i;
	return str_arr;
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
int contar_palabras(FILE *archivo)
{
    char linea[100 + 1];
    int i, cantidad_palabras = 0;
    char ** string_array=NULL;
    size_t len=0;
    char *delim= " \t\n\r";

    while (fgets(linea, 300, archivo) != NULL)
    {
        string_array=split_string(linea,delim, &len);
        for(i=0;i<len;i++)
        {
            if(strlen(string_array[i])>0)
            cantidad_palabras++;
        }
    destroy_string_array(string_array,len);
    len=0;           
    }    

    return cantidad_palabras;
}

// Cuenta lineas
int contar_lineas(FILE *archivo)
{    
    char ch;
    int contador = 0;

    while ((ch = fgetc(archivo)) != EOF){
        if (ch == '\n'){
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
    else if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0))
    {
        // Verifica que la cantidad de argumentos sea 2
        if (argc != 2) error(error_cant_param);
        ayuda();
        return 0;
    }

    // Verifica por pedido de version en el argumento 2
    else if ((strcmp(argv[1], "-V") == 0) || (strcmp(argv[1], "--version") == 0))
    {
        // Verifica que la cantidad de argumentos sea 2
        if (argc != 2) error(error_cant_param);
        version();
        return 0;
    }

    // Verifica por pedido de caracteres en el argumento 1 y entrada en el argumento 2
    else if (((strcmp(argv[1], "-c") == 0) || (strcmp(argv[1], "--characters") == 0)) && 
             ((strcmp(argv[2], "-i") == 0) || (strcmp(argv[2], "--input") == 0)))
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
    else if (((strcmp(argv[1], "-w") == 0) || (strcmp(argv[1], "--words") == 0)) && 
             ((strcmp(argv[2], "-i") == 0) || (strcmp(argv[2], "--input") == 0)))
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
    else if (((strcmp(argv[1], "-l") == 0) || (strcmp(argv[1], "--lines") == 0)) && 
             ((strcmp(argv[2], "-i")) || (strcmp(argv[2], "--input"))))
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

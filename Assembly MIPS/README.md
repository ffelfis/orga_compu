# Assembly MIPS

Lo siguiente se puede efectuar en la máquina virtual disponiendo del archivo `holamundo.c` y el archivo `mystrlen.S`.

## Compilación con linkeo de código C y código Assembly

```
# gcc -Wall -g -o holamundo holamundo.c mystrlen.S
```

- `-Wall`: activa todos los mensajes de warning;
- `-o`: archivo de salida (en este caso, `holamundo`).

La ejecución debería dar lo siguiente:

```
# ./holamundo
Hola mundo.
```

## Lectura del código Assembly

```
# objdump -S holamundo
```

Esto permite leer el código Assembly del archivo objeto `holamundo` generado como salida de la compilación.

```
# objdump -S holamundo > text_file.txt
```

Esto guarda el código Assembly en el archivo de texto `text_file.txt`.

También se puede obtener un archivo con el código Assembly usando GCC.

```
# gcc -Wall -O0 -S holamundo.c
```

- `-S`: detiene al compilador luego de generar el assembly;
- `-O0`: No aplica optimizaciones.

Esto genera el archivo `myprog.s` con el assembly que gcc genera para `holamundo.c`.

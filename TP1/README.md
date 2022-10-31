# Trabajo práctico 1

## Autómatas celulares elementales

https://mathworld.wolfram.com/ElementaryCellularAutomaton.html

## Makefile

```
compilar:
ifdef asm
	gcc -DPROXIMO_ASM -Wall -g -o autcel autcel.c proximo.S
else
	gcc -Wall -o autcel autcel.c
endif

clean:
	rm autcel *.pbm
```

Si la variable `asm` está definida se ejecuta la compilación definiendo la variable `PROXIMO_ASM` y usando los archivos `autcel.c` y `proximo.S`. Si no se compila solo con el archivo `autcel.c`.

### Compilación con función `proximo` en C

Ejecutar el siguiente código:

```
# make
```

### Compilación con función `proximo` en Assembly

Ejecutar el siguiente código:

```
# make asm=1
```

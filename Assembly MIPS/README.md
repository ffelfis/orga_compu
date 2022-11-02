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

## Directivas al ensamblador (Assembler)

El siguiente código en Assembly de la funci+on `operacion_asm`. Solo llama a la función `suma` escrita en C, presente y accesible en la definición de `main`.

```
#include <sys/regdef.h>

#define SS 32

#define	O_RA 24
#define O_FP 20
#define O_GP 16

#define O_A0 (SS)
#define O_A1 (O_A0 +4)

/* Callee guarda argumentos pasados */

	.text
	.align	2
	.globl	operacion_asm
	.ent	operacion_asm

operacion_asm:
	.frame	fp, SS, ra
	.set	noreorder
	.cpload	t9
	.set	reorder

	/* Stack stretch */
	subu	sp, sp, SS

	/* Saved Register Area */
	.cprestore O_GP
	sw	ra, O_RA(sp)
	sw	fp, O_FP(sp)
	/* sw	gp, O_GP(sp) */
	move	fp, sp

	/* Argument Building Area */
	sw	a0, O_A0(sp)
	sw	a1, O_A1(sp)

/* Solo se llama a la funcion suma de C */
operacion:
	jal	suma	/* los argumentos ya estan */
			/* devuelve resultado en v0 */

fin:
	/* Stack unwinding */
	lw	ra, O_RA(sp)
	lw	fp, O_FP(sp)
	lw	gp, O_GP(sp)
	addiu	sp, sp, SS

	jr	ra
.end	operacion_asm
```

--- 

```
	.frame	fp, SS, ra
	.set	noreorder
	.cpload	t9
	.set	reorder
```

Esto se puede usar como un prólogo. `.cpload t9` carga el `gp`. `.frame fp, SS, ra` describe el Stack Frame, `SS` es el valor usado para extender el Stack para la función.

```
.cprestore
```

Causes the assembler to emit the following at the point where it occurs: sw $gp, offset ($sp)

Also, causes the assembler to generate lw $gp, offset ($sp) after every JAL or BAL operation. Offset should point to the saved register area.

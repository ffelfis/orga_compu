#include <sys/regdef.h>

#define	SS 24

#define O_FP 20
#define O_GP 16

#define O_LTA_AUX 8
#define O_LTA_I 0
#define O_LTA_V 4
/* Al LTA le quedan 1 palabras libres */

#define	O_A0 (SS)
#define O_A1 (O_A0 + 4)
#define O_A2 (O_A1 + 4)
#define O_A3 (O_A2 + 4)
#define O_N (O_A3 + 4)

.text
.align	2
.globl	proximo_ass
.ent	proximo_ass
proximo_ass:

	subu	sp, sp, SS

	/* Saved Register Area */
	sw	fp, O_FP(sp)
	sw	gp, O_GP(sp)
	move	fp, sp

	/* Argument Building Area */
	sw	a0, O_A0(sp)	/* *a */
	sw	a1, O_A1(sp)	/* i */
	sw	a2, O_A2(sp)	/* j */
	sw	a3, O_A3(sp)	/* regla */

	/* Local and Temporary Area */
	add	t0, zero, zero	/* indice = 0 */
	sw	t0, O_LTA_I(sp)

	move	t0, a3		/* valor = regla */
	sw	t0, O_LTA_V(sp)

	/* Programa */

	/*====================================*/
	/* Indice = 8 para pruebas ~~BORRAR~~ */
	#add	t0, zero, zero
	#addiu	t0, t0, 56
	#sw	t0, O_LTA_I(sp)
	/*====================================*/
	
/* UBICACION DEL PUNTERO */
	
	/* Necesito #fila y #columna para avanzar en memoria */

	/* Carga del valor de la regla */
	lw	t0, O_N(sp)	/* t0 <- MEM[sp + O_N]: N = #columnas */

	/* Multiplica numero de columnas por cantidad de filas */
	multu	a1, t0		/* N*i resultado en LO */
	mflo	t0		/* resultado */

	/* Suma a la direccion de a0 la cantidad N*i */
	/* Con esto se desplaza en filas */
	#addu	t1, a0, t0	/* suma la direccion con N*i */
	#lw 	t0, 0(t1)

	/* Suma a la direccion la cantidad j */ 
	/* Con esto se desplaza en columnas */
	#addu	t0, a2, t0	/* A lo anterior se le suma j */

	/* Se carga lo de la direccion de t0 */
	#lw	t1, 0(t0)

	/*=========================*/
	move	t7, t0
	#addiu	t7, t7, 48 	/* Transformar en numero */
	sw	t7, O_LTA_AUX(sp)
	/*=========================*/

/* Hasta aqui se tiene el puntero a la posicion indicada por (i,j) */

col_0:
	bnez	a2, col_N	/* Si j no es 0 */

	/*========================*/
	#addiu 	t0, t0, 48	/* t0 <- t0 + 48 Visualiza numero */
	#sw	t0, O_LTA_I(sp)
	#sw	t1, O_LTA_I(sp)
	/*========================*/
	
	b	return		/* Ir al final */
	
col_N:
	ld	t0, O_N(sp)	/* t0 <- MEM[sp + O_N]: N = #filas */
	subu	t0, t0, 1	/* t0 <- N - 1 cuenta desde 0 */
	bne	a2, t0, col_medio	/* Si j no es N-1 */

	b	return		/* Ir al final */

col_medio:

	b	return		/* Ir al final */

return:
	/* return valor */
	lw	v0, O_LTA_AUX(sp)

	/* Stack unwinding */
	lw	fp, O_FP(sp)
	lw	gp, O_GP(sp)
	addiu	sp, sp, SS


	jr	ra
.end	proximo_ass

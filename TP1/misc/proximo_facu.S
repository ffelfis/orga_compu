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
	
/* UBICACION DEL PUNTERO */
	
	/* Necesito #fila y #columna para avanzar en memoria */

	/* Carga del valor de la regla */
	lw	t3, O_N(sp)	/* t3 <- MEM[sp + O_N]: N = #columnas */

	/* Multiplica numero de columnas por cantidad de filas */
	multu	a1, t3		/* N*i resultado en LO */
	mflo	t0		/* resultado */

	/* Suma a la direccion de a0 la cantidad N*i */
	/* Con esto se desplaza en filas */
	la	t1, 0(a0)	/* carga direccion de (0,0)*/
	addu	t1, t1, t0	/* suma direccion + (N*i) */

	/* Suma a la direccion la cantidad j */ 
	/* Con esto se desplaza en columnas */
	addu	t1, t1, a2	/* suma (direccion + (N*i)) + j */

	/* Son bytes, de querer ver lo que hay en la direccion usar: lb */
	#lb	t0, 0(t1) # se carga en t0 lo que hay en t1

	/*=========================*/
	#move	t7, t0
	#addiu	t7, t7, 48 	/* Transformar en numero */
	#addiu	t7, zero, 17	/* VALOR RARO tipo flag BORRAR */
	#sw	t7, O_LTA_AUX(sp)
	/*=========================*/

/* Hasta aqui se tiene el puntero a la posicion indicada por (i,j) */
/*								   */
/*	       t1 tiene tiene la direccion: en posicion		   */
/*=================================================================*/

col_0:
	bnez	a2, col_N	/* Si j no es 0 */
	
	#addiu 	t7, zero, 17
	#sw	t7, O_LTA_AUX(sp)	
		
	/* Elemento siguiente */
	addiu	t2, t1, 1	/* t2 <- t1 + 1: direccion de elemento siguiente */ 
	
	#addiu	t7, zero, 17
	#lb	t7, 0(t2)
	#sw	t7, O_LTA_AUX(sp)
	#j	salir
	
	# ======= en t2 esta la direccion del elemento siguiente
	#lb	t7, 0(t2)
	#sw	t7, O_LTA_AUX(sp)
	#j 	salir

	# ANDA
	#addu	t7, zero, zero
	#lb	t7, 0(t2)
	#sw	t7, O_LTA_AUX(sp)
	#j	salir


	/* Elemento anterior */
	subu 	t0, t3, 1	/* t0 <- t3 - 1: N-1 */
	addu	t0, t1, t0	/* t0 <- t1 - t0: direccion - (N-1) */

	# ANDA Tiene que ser 0: 48
	#addu	t7, zero, zero
	#lb	t7, 0(t0)
	#sw	t7, O_LTA_AUX(sp)
	#j	salir

	b	return		/* Ir al final */

	
col_N:
	subu	t0, t1, 1	/* t0 <- t1 - 1: direccion elemento anteior */
	subu	t4, t3, 1	/* t4 <- N - 1 cuenta desde 0 */
	bne	a2, t4, col_medio	/* Si j no es N-1 */

	subu	t2, t1, t4	/* t2 <- t1 - t4: direcicion centro - (N-1) */

	b	return		/* Ir al final */


col_medio:
	addiu	t2, t1, 1	/* t2 <- t1 + 1: direccion elemento siguiente */

	b	return		/* Ir al final */


salir:
	addu	v0, zero, zero		/* Limpia el v0 */
	lw	v0, O_LTA_AUX(sp)	/* devuelve lo que esta en AUX */
	j	stack_end


return:	
/* Recordar que los elementos son caracteres ('1', '0') o (48, 49) */
/* Hay que restar 48 */

	lb	t0, 0(t0)	/* t0 <- MEM[t0]: Elemento anterior */

	# ======= elemento anterior
	#sw	t0, O_LTA_AUX(sp)
	#j	salir
	
	subu	t0, t0, 48	/* t0 <- t0 - 48 */
	sll	t0, t0, 2	/* t0 <- t0 * 4 */ 
	
	# ======= multiplicacion por 4
	#sw	t0, O_LTA_AUX(sp)
	#j	salir

	lb	t1, 0(t1)	/* t1 <- MEM[t1]: Elemento central */
	
	# ======= elemento central
	#sw	t1, O_LTA_AUX(sp)
	#j	salir
	
	subu	t1, t1, 48	/* t1 <- t1 - 48 */
	sll	t1, t1, 1	/* t1 <- t1 * 2 */
	
	# ======= multiplicacion por 2
	#sw 	t1, O_LTA_AUX(sp)
	#j	salir

	lb	t2, 0(t2)	/* t2 <- MEM[t2]: Elemento siguiente */
	
	subu	t2, t2, 48	/* t2 <- t2 - 48 */

	# ======= elemento siguiente
	#sw	t2, O_LTA_AUX(sp)
	#j	salir
	
	addu	t0, t0, t1	/* t0 <- t0 + t1: Anterior + Central */
	
	# ======= suma
	#sw	t0, O_LTA_AUX(sp)
	#j	salir
	
	addu	t0, t0, t2	/* posicion (indice) */

	# ======= suma
	#sw	t0, O_LTA_AUX(sp)
	#j 	salir


	/* Regla en a3 */

	srlv	t0, a3, t0	/* t0 <- a3 >> lo que indique t0 */
	
	andi	v0, t0, 1 	/* v0 <- LSB de t0 */

	/* return valor */
	#lw	v0, O_LTA_AUX(sp)


stack_end:
	/* Stack unwinding */
	lw	fp, O_FP(sp)
	lw	gp, O_GP(sp)
	addiu	sp, sp, SS


	jr	ra
.end	proximo_ass

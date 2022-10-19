#include <sys/regdef.h>

#define	SS 16

#define O_FP 12
#define O_GP 8

#define O_LTA_I 0
#define O_LTA_V 4

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

	/* Argment Building Area */
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
	add	t0, zero, zero
	addiu	t0, t0, 56
	sw	t0, O_LTA_I(sp)
	/*====================================*/

col_0:
	bnez	a2, col_N	/* Si j no es 0 */
	
	/* Nesecito #fila y #columna para avanzar en memoria */
	lw	t0, O_N(sp)	/* t0 <- MEM[sp + O_N]: N = #filas */

	

	/*========================*/
	addiu 	t0, t0, 48	/* t0 <- t0 + 48 */
	sw	t0, O_LTA_I(sp)
	/*========================*/

col_N:
	ld	t0, O_N(sp)	/* t0 <- MEM[sp + O_N]: N = #filas */
	subu	t0, t0, 1	/* t0 <- N - 1 cuenta desde 0 */
	bne	a2, t0, col_medio	/* Si j no es N-1 */

col_medio:

	/* return valor */
	lw	v0, O_LTA_I(sp)

	/* Stack unwinding */
	lw	fp, O_FP(sp)
	lw	gp, O_GP(sp)
	addiu	sp, sp, SS


	jr	ra
.end	proximo_ass

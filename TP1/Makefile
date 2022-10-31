compilar:
ifdef asm
	gcc -DPROXIMO_ASM -Wall -g -o autcel autcel.c proximo.S
else
	gcc -Wall -o autcel autcel.c
endif

#autcel_make: autcel.c proximo.S
#	gcc -Wall -g -o autcel_make autcel.c proximo.S

clean:
	rm autcel *.pbm

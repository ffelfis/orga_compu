#include <stdio.h>

int main()
{
    int regla = 32; /* Regla: [0;255] */
    int pattern[8] = {0,1,2,3,4,5,6,7}; /* Tamaño fijo */
    /* Patrón: siempre tiene 8 motivos individuales */

    for (int i=7; i>=0; i--)
    {
        pattern[i] = regla % 2;
        regla = regla / 2;
    }

    for (int i=0; i<8; i++)
    {
        printf("%d ", pattern[i]);
    }
    printf("\n");

    return 0;
}
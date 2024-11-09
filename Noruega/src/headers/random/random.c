#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "random.h"


int generateRandomIntInRange(bool generate_new_seed, int range)
{
	/*
		Time retorna o hor�rio atual em segundos, como est� recendo null
		o tempo n�o � armazenado, apenas retornado srand, que seta uma nova
		seed para rand(), grantindo que sempre um n�mero aleat�rio ser� gerado.
	*/
	
	if (generate_new_seed)
		srand(time(NULL));
	//O resto da divis�o de um n�mero sempre est� entre 0 e n�mero - 1
	return rand() % range;
}

int* generateRandomIntArrayInRange(int array_size, int range)
{
	
	int* int_array = calloc(array_size, sizeof(int));
	if (!int_array)
	{
		printf_s("Mem�ria do array de ints in range n�o alocada");
		exit(-1);
	}
	for (int i = 0; i < array_size; i++)
	{	
		if(i == 0)
			int_array[i] = generateRandomIntInRange(true, range);
		else
			int_array[i] = generateRandomIntInRange(false, range);
	}
	return int_array;
}


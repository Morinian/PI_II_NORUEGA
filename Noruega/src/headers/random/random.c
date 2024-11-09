#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "random.h"


int generateRandomIntInRange(bool generate_new_seed, int range)
{
	/*
		Time retorna o horário atual em segundos, como está recendo null
		o tempo não é armazenado, apenas retornado srand, que seta uma nova
		seed para rand(), grantindo que sempre um número aleatório será gerado.
	*/
	
	if (generate_new_seed)
		srand(time(NULL));
	//O resto da divisão de um número sempre está entre 0 e número - 1
	return rand() % range;
}

int* generateRandomIntArrayInRange(int array_size, int range)
{
	
	int* int_array = calloc(array_size, sizeof(int));
	if (!int_array)
	{
		printf_s("Memória do array de ints in range não alocada");
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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "element.h"
#include <stdbool.h>

int generateRandonElement(generate_new_seed)
{
	int elements_amount = 15;
	/*
		Time retorna o hor�rio atual em segundos, como est� recendo null
		o tempo n�o � armazenado, apenas retornado srand, que seta uma nova
		seed para rand(), grantindo que sempre um n�mero aleat�rio ser� gerado.
	*/
	
	if (generate_new_seed)
		srand(time(NULL));
	//O resto da divis�o de um n�mero sempre est� entre 0 e n�mero - 1
	return rand() % elements_amount;
}

enum CHEMICAL_ELEMENTS * generateChemicalDeck()
{
	
	int deck_size = 4;
	int* elements = calloc(deck_size, sizeof(int));
	if (!elements)
	{
		printf_s("Mem�ria do deck n�o alocada");
		exit(-1);
	}
	for (int i = 0; i < deck_size; i++)
	{	
		if(i == 0)
			elements[i] = generateRandonElement(true);
		else
			elements[i] = generateRandonElement(false);
	}
	return elements;
}


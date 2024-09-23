#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "element.h"
#include <stdbool.h>

int generateRandonElement(generate_new_seed)
{
	int elements_amount = 15;
	/*
		Time retorna o horário atual em segundos, como está recendo null
		o tempo não é armazenado, apenas retornado srand, que seta uma nova
		seed para rand(), grantindo que sempre um número aleatório será gerado.
	*/
	
	if (generate_new_seed)
		srand(time(NULL));
	//O resto da divisão de um número sempre está entre 0 e número - 1
	return rand() % elements_amount;
}

enum CHEMICAL_ELEMENTS * generateChemicalDeck()
{
	
	int deck_size = 4;
	int* elements = calloc(deck_size, sizeof(int));
	if (!elements)
	{
		printf_s("Memória do deck não alocada");
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


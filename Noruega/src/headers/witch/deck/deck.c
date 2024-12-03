#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include "../witch.h"
#include "../../element/element.h"
#include "deck.h"

// Função para retornar o deck com base no número aleatório
void get_deck_type(int random_number, enum MIX_RESULTS deck[4]) {
    switch (random_number) {
    case 0: // Deck Balanceado
        printf("\nDeck Balanceado 1");
        deck[0] = COMPATIBLE;
        deck[1] = REDOX;
        deck[2] = WATER_REACTIVITY;
        deck[3] = METAL_REACTIVITY;
        break;
    case 1: // Outro Deck Balanceado
        printf("\nDeck Balanceado 2");
        deck[0] = COMPATIBLE;
        deck[1] = ACID_BASE;
        deck[2] = TOXIC_COMPOUND_FORMATION;
        deck[3] = WATER_REACTIVITY;
        break;
    case 2: // Deck Ofensivo
        printf("\nDeck Ofensivo 1");
        deck[0] = ACID_BASE;
        deck[1] = REDOX;
        deck[2] = TOXIC_COMPOUND_FORMATION;
        deck[3] = METAL_REACTIVITY;
        break;
    case 3: // Outro Deck Ofensivo
        printf("\nDeck Ofensivo 2");
        deck[0] = ACID_BASE;
        deck[1] = TOXIC_COMPOUND_FORMATION;
        deck[2] = WATER_REACTIVITY;
        deck[3] = METAL_REACTIVITY;
        break;
    case 4: // Deck Focado em Defesa
        printf("\nDeck Focado em Defesa 1");
        deck[0] = COMPATIBLE;
        deck[1] = WATER_REACTIVITY;
        deck[2] = REDOX;
        deck[3] = TOXIC_COMPOUND_FORMATION;
        break;
    case 5: // Outro Deck Focado em Defesa
        printf("\nDeck Focado em Defesa 2");
        deck[0] = COMPATIBLE;
        deck[1] = WATER_REACTIVITY;
        deck[2] = ACID_BASE;
        deck[3] = METAL_REACTIVITY;
        break;
    default:
        printf("Erro: número inválido.\n");
    }
}

void generateDeck(enum CHEMICAL_ELEMENTS entity_element, int deck_type, WITCH* witch) {
    enum MIX_RESULTS deck_format[4];
    get_deck_type(deck_type, deck_format);
    int deck_position = 0;
    while (deck_position < DECK_SIZE)
    {
        for (enum CHEMICAL_ELEMENTS element = 0; element < ELEMENTS_AMOUNT; element++)
        {
            if (mixElements(entity_element, element) == deck_format[deck_position]) {
                witch->deck[deck_position] = element;
                break;
            }
        }
        deck_position++;
    }
}
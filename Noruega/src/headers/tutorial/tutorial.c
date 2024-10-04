#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "tutorial.h"

ALLEGRO_BITMAP * initCardTutorial1()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardTutorial1;
    cardTutorial1 = al_load_bitmap("./images/card1.png");
    if (!cardTutorial1)
    {
        printf_s("\nImagem de cardTutorial1 nao alocada");
        exit(-1);
    }
    return cardTutorial1;
}

ALLEGRO_BITMAP* initCardTutorial2()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardTutorial2;
    cardTutorial2 = al_load_bitmap("./images/card2.png");
    if (!cardTutorial2)
    {
        printf_s("\nImagem de cardTutorial2 nao alocada");
        exit(-1);
    }
    return cardTutorial2;
}

ALLEGRO_BITMAP* initCardTutorial3()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardTutorial3;
    cardTutorial3 = al_load_bitmap("./images/card3.png");
    if (!cardTutorial3)
    {
        printf_s("\nImagem de cardTutorial3 nao alocada");
        exit(-1);
    }
    return cardTutorial3;
}

void cardDraw(int width, int height, ALLEGRO_BITMAP * cardTutorial1, ALLEGRO_BITMAP* cardTutorial2, ALLEGRO_BITMAP* cardTutorial3, int number)
{
    if (number == 1) {
        al_draw_bitmap(cardTutorial1, width, height, 0);
    }
    else if (number == 2) {
        al_draw_bitmap(cardTutorial2, width, height, 0);
    }
    else if (number == 3) {
        al_draw_bitmap(cardTutorial3, width, height, 0);
    }
}

void tutorialHeaderDestroy(TUTORIAL* tutorial)
{
    //Destruir criações
    al_destroy_bitmap(tutorial->cardTutorial1);
    al_destroy_bitmap(tutorial->cardTutorial2);
    al_destroy_bitmap(tutorial->cardTutorial3);
    free(tutorial);
}

TUTORIAL * initTutorial()
{
    TUTORIAL * tutorial = (TUTORIAL *) malloc(sizeof(TUTORIAL));
    if (!tutorial)
    {
        printf_s("Memoria nao alocada tutorial \n");
        exit(-1);
    }
    printf_s("Memoria alocada tutorial!! \n");

    tutorial->cardTutorial1 = initCardTutorial1();
    tutorial->cardTutorial2 = initCardTutorial2();
    tutorial->cardTutorial3 = initCardTutorial3();

    tutorial->cardDraw = cardDraw;
    tutorial->destroyMap = tutorialHeaderDestroy;
    return tutorial;
}
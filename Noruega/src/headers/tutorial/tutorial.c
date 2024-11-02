#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "tutorial.h"


//IMAGENS PARA O TUTORIAL NO INCIO ---------------------------

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

//IMAGENS PARA A LORE DA ENTIDADE -----------------------------

ALLEGRO_BITMAP* initCardEntidadeLore1()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardEntidade1;
    cardEntidade1 = al_load_bitmap("./images/entidade1.png");

    if (!cardEntidade1)
    {
        printf_s("\nImagem de cardEntidade1 nao alocada");
        exit(-1);
    }
    return cardEntidade1;
}

ALLEGRO_BITMAP* initCardEntidadeLore2()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardEntidade2;
    cardEntidade2 = al_load_bitmap("./images/entidade2.png");
    if (!cardEntidade2)
    {
        printf_s("\nImagem de cardEntidade2 nao alocada");
        exit(-1);
    }
    return cardEntidade2;
}

ALLEGRO_BITMAP* initCardEntidadeLore3()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardEntidade3;
    cardEntidade3 = al_load_bitmap("./images/entidade3.png");
    if (!cardEntidade3)
    {
        printf_s("\nImagem de cardEntidade3 nao alocada");
        exit(-1);
    }
    return cardEntidade3;
}
ALLEGRO_BITMAP* initCardEntidadeLore4()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardEntidade4;
    cardEntidade4 = al_load_bitmap("./images/entidade4.png");
    if (!cardEntidade4)
    {
        printf_s("\nImagem de cardEntidade4 nao alocada");
        exit(-1);
    }
    return cardEntidade4;
}

ALLEGRO_BITMAP* initCardEntidadeLore5()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardEntidade5;
    cardEntidade5 = al_load_bitmap("./images/entidade5.png");
    if (!cardEntidade5)
    {
        printf_s("\nImagem de cardEntidade5 nao alocada");
        exit(-1);
    }
    return cardEntidade5;
}

void cardDraw(int width, int height, ALLEGRO_BITMAP * cardTutorial1, ALLEGRO_BITMAP* cardTutorial2, ALLEGRO_BITMAP* cardTutorial3, int number)
{

    if (number == 1) {
        al_draw_bitmap(cardTutorial1, width+110, height+70, 0);
    }
    else if (number == 2) {
        al_draw_bitmap(cardTutorial2, width+110, height+70, 0);
    }
    else if (number == 3) {
        al_draw_bitmap(cardTutorial3, width+110, height+70, 0);
    }
}

void loreDraw(int width, int height, ALLEGRO_BITMAP* cardLore1, ALLEGRO_BITMAP* cardLore3, ALLEGRO_BITMAP* cardLore4, ALLEGRO_BITMAP* cardLore5, int number) {

    if (number == 1) {
        al_draw_scaled_bitmap(cardLore1,
            0, 0, al_get_bitmap_width(cardLore1), al_get_bitmap_height(cardLore1),
            0, 0, width, height,
            0);
    }
    else if (number == 2) {
        al_draw_scaled_bitmap(cardLore3,
            0, 0, al_get_bitmap_width(cardLore3), al_get_bitmap_height(cardLore3),
            0, 0, width, height,
            0);
    }
    else if (number == 3) {
        al_draw_scaled_bitmap(cardLore4,
            0, 0, al_get_bitmap_width(cardLore4), al_get_bitmap_height(cardLore3),
            0, 0, width, height,
            0);
    }
    else if (number == 4) {
        al_draw_scaled_bitmap(cardLore5,
            0, 0, al_get_bitmap_width(cardLore5), al_get_bitmap_height(cardLore4),
            0, 0, width, height,
            0);
    }

}

void tutorialHeaderDestroy(TUTORIAL* tutorial)
{
    //Destruir criações
    al_destroy_bitmap(tutorial->cardTutorial1);
    al_destroy_bitmap(tutorial->cardTutorial2);
    al_destroy_bitmap(tutorial->cardTutorial3);

    al_destroy_bitmap(tutorial->cardEntidade1);
    al_destroy_bitmap(tutorial->cardEntidade3);
    al_destroy_bitmap(tutorial->cardEntidade4);
    al_destroy_bitmap(tutorial->cardEntidade5);
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

    tutorial->cardEntidade1 = initCardEntidadeLore1();
    tutorial->cardEntidade3 = initCardEntidadeLore3();
    tutorial->cardEntidade4 = initCardEntidadeLore4();
    tutorial->cardEntidade5 = initCardEntidadeLore5();

    tutorial->cardDraw = cardDraw;
    tutorial->loreDraw = loreDraw;

    tutorial->destroyMap = tutorialHeaderDestroy;
    return tutorial;
}
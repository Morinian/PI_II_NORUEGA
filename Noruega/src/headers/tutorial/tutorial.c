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
    cardEntidade1 = al_load_bitmap("./images/card1.png");
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
    cardEntidade2 = al_load_bitmap("./images/card2.png");
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
    cardEntidade3 = al_load_bitmap("./images/card3.png");
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
    cardEntidade4 = al_load_bitmap("./images/card1.png");
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
    cardEntidade5 = al_load_bitmap("./images/card2.png");
    if (!cardEntidade5)
    {
        printf_s("\nImagem de cardEntidade5 nao alocada");
        exit(-1);
    }
    return cardEntidade5;
}

ALLEGRO_BITMAP* initCardEntidadeLore6()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardEntidade6;
    cardEntidade6 = al_load_bitmap("./images/card3.png");
    if (!cardEntidade6)
    {
        printf_s("\nImagem de cardEntidade6 nao alocada");
        exit(-1);
    }
    return cardEntidade6;
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

void loreDraw(int width, int height, ALLEGRO_BITMAP* cardLore1, ALLEGRO_BITMAP* cardLore2, ALLEGRO_BITMAP* cardLore3, ALLEGRO_BITMAP* cardLore4, ALLEGRO_BITMAP* cardLore5, ALLEGRO_BITMAP* cardLore6, int number) {

    if (number == 1) {
        al_draw_bitmap(cardLore1, width, height, 0);
    }
    else if (number == 2) {
        al_draw_bitmap(cardLore2, width, height, 0);
    }
    else if (number == 3) {
        al_draw_bitmap(cardLore3, width, height, 0);
    }
    else if (number == 4) {
        al_draw_bitmap(cardLore4, width, height, 0);
    }
    else if (number == 5) {
        al_draw_bitmap(cardLore5, width, height, 0);
    }
    else if (number == 6) {
        al_draw_bitmap(cardLore6, width, height, 0);
    }

}

void tutorialHeaderDestroy(TUTORIAL* tutorial)
{
    //Destruir cria��es
    al_destroy_bitmap(tutorial->cardTutorial1);
    al_destroy_bitmap(tutorial->cardTutorial2);
    al_destroy_bitmap(tutorial->cardTutorial3);

    al_destroy_bitmap(tutorial->cardEntidade1);
    al_destroy_bitmap(tutorial->cardEntidade2);
    al_destroy_bitmap(tutorial->cardEntidade3);
    al_destroy_bitmap(tutorial->cardEntidade4);
    al_destroy_bitmap(tutorial->cardEntidade5);
    al_destroy_bitmap(tutorial->cardEntidade6);
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
    tutorial->cardEntidade2 = initCardEntidadeLore2();
    tutorial->cardEntidade3 = initCardEntidadeLore3();
    tutorial->cardEntidade4 = initCardEntidadeLore4();
    tutorial->cardEntidade5 = initCardEntidadeLore5();
    tutorial->cardEntidade6 = initCardEntidadeLore6();

    tutorial->cardDraw = cardDraw;
    tutorial->loreDraw = loreDraw;

    tutorial->destroyMap = tutorialHeaderDestroy;
    return tutorial;
}
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "tutorial.h"

//Animação book
float frameBook = 0.f;

//IMAGENS PARA O TUTORIAL NO INCIO ---------------------------

ALLEGRO_BITMAP * initCardTutorial1()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardTutorial1;
    cardTutorial1 = al_load_bitmap("./images/tutorial/card1.png");
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
    cardTutorial2 = al_load_bitmap("./images/tutorial/card2.png");
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
    cardTutorial3 = al_load_bitmap("./images/tutorial/card3.png");
    if (!cardTutorial3)
    {
        printf_s("\nImagem de cardTutorial3 nao alocada");
        exit(-1);
    }
    return cardTutorial3;
}

ALLEGRO_BITMAP* initCardTutorial4()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardTutorial4;
    cardTutorial4 = al_load_bitmap("./images/tutorial/card4.png");
    if (!cardTutorial4)
    {
        printf_s("\nImagem de cardTutorial4 nao alocada");
        exit(-1);
    }
    return cardTutorial4;
}

ALLEGRO_BITMAP* initCardTutorial5()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* cardTutorial5;
    cardTutorial5 = al_load_bitmap("./images/tutorial/card5.png");
    if (!cardTutorial5)
    {
        printf_s("\nImagem de cardTutorial5 nao alocada");
        exit(-1);
    }
    return cardTutorial5;
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

//IMAGENS PARA O LIVRO

ALLEGRO_BITMAP* initBook1()
{
    ALLEGRO_BITMAP* book1;
    book1 = al_load_bitmap("./images/Livro/frame1.png");
    if (!book1)
    {
        printf_s("\nImagem de book1 nao alocada");
        exit(-1);
    }
    return book1;
}

ALLEGRO_BITMAP* initBook2()
{
    ALLEGRO_BITMAP* book2;
    book2 = al_load_bitmap("./images/Livro/frame2.png");
    if (!book2)
    {
        printf_s("\nImagem de book2 nao alocada");
        exit(-1);
    }
    return book2;
}

ALLEGRO_BITMAP* initBook3()
{
    ALLEGRO_BITMAP* book3;
    book3 = al_load_bitmap("./images/Livro/frame3.png");
    if (!book3)
    {
        printf_s("\nImagem de book3 nao alocada");
        exit(-1);
    }
    return book3;
}

ALLEGRO_BITMAP* initBook4()
{
    ALLEGRO_BITMAP* book4;
    book4 = al_load_bitmap("./images/Livro/frame4.png");
    if (!book4)
    {
        printf_s("\nImagem de book4 nao alocada");
        exit(-1);
    }
    return book4;
}

ALLEGRO_BITMAP* initBook5()
{
    ALLEGRO_BITMAP* book5;
    book5 = al_load_bitmap("./images/Livro/frame5.png");
    if (!book5)
    {
        printf_s("\nImagem de book5 nao alocada");
        exit(-1);
    }
    return book5;
}

ALLEGRO_BITMAP* initBookAnimaR()
{
    ALLEGRO_BITMAP* bookAnimaR;
    bookAnimaR = al_load_bitmap("./images/Livro/LivroAbertoAnimaDir.png");
    if (!bookAnimaR)
    {
        printf_s("\nImagem de LivroAbertoAnimaDir nao alocada");
        exit(-1);
    }
    return bookAnimaR;
}

ALLEGRO_BITMAP* initBookAnimaL()
{
    ALLEGRO_BITMAP* bookAnimaL;
    bookAnimaL = al_load_bitmap("./images/Livro/LivroAbertoAnimaEsq.png");
    if (!bookAnimaL)
    {
        printf_s("\nImagem de LivroAbertoAnimaDir nao alocada");
        exit(-1);
    }
    return bookAnimaL;
}

//FUNÇÕES DE DRAW ---------------------------------------------
void bookDraw(ALLEGRO_BITMAP* bookAnimaR, ALLEGRO_BITMAP* bookAnimaL , ALLEGRO_BITMAP* book1, ALLEGRO_BITMAP* book2, ALLEGRO_BITMAP* book3, ALLEGRO_BITMAP* book4, ALLEGRO_BITMAP* book5, int *play, int nbook, int frame_width, int frame_height,int coordinate_x, int coordinate_y)
{
    printf("%d", nbook);
    if (*play == 0) {

        if (nbook == 1) {
            al_draw_bitmap(book1, coordinate_x, coordinate_y , 0);
        }else if (nbook == 2) {
            al_draw_bitmap(book2, coordinate_x, coordinate_y, 0);
        }else if (nbook == 3) {
            al_draw_bitmap(book3, coordinate_x, coordinate_y, 0);
        }else if (nbook == 4) {
            al_draw_bitmap(book4, coordinate_x, coordinate_y, 0);
        }else if (nbook == 5) {
            al_draw_bitmap(book5, coordinate_x, coordinate_y, 0);
        }

    }else if (*play == 1) {
        frameBook += 0.3f;
        if (frameBook > 5) {
            frameBook = 0;
            *play = 0;
        }
        al_draw_bitmap_region(bookAnimaR, frame_width * (int)frameBook, 0, frame_width, frame_height, coordinate_x, coordinate_y - 9, 0);

    }else if (*play == 2) {
        frameBook += 0.3f;
          if (frameBook > 5) {
              frameBook = 0;
              *play = 0;
          }
        al_draw_bitmap_region(bookAnimaL, frame_width * (int)frameBook, 0, frame_width, frame_height, coordinate_x, coordinate_y - 9, 0);
    }

}

void cardDraw(int width, int height, ALLEGRO_BITMAP* cardTutorial1, ALLEGRO_BITMAP* cardTutorial2, ALLEGRO_BITMAP* cardTutorial3, ALLEGRO_BITMAP* cardTutorial4, ALLEGRO_BITMAP* cardTutorial5, int number)
{

    if (number == 1) {
        al_draw_bitmap(cardTutorial1, width+65, height + 50, 0);
    }
    else if (number == 2) {
        al_draw_bitmap(cardTutorial2, width+65, height + 50, 0);
    }
    else if (number == 3) {
        al_draw_bitmap(cardTutorial3, width+65, height + 50, 0);
    }
    else if (number == 4) {
        al_draw_bitmap(cardTutorial4, width + 65, height + 50, 0);
    }
    else if (number == 5) {
        al_draw_bitmap(cardTutorial5, width + 65, height + 50, 0);
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
    al_destroy_bitmap(tutorial->cardTutorial4);
    al_destroy_bitmap(tutorial->cardTutorial5);

    al_destroy_bitmap(tutorial->cardEntidade1);
    al_destroy_bitmap(tutorial->cardEntidade3);
    al_destroy_bitmap(tutorial->cardEntidade4);
    al_destroy_bitmap(tutorial->cardEntidade5);

    al_destroy_bitmap(tutorial->book1);
    al_destroy_bitmap(tutorial->book2);
    al_destroy_bitmap(tutorial->book3);
    al_destroy_bitmap(tutorial->book4);
    al_destroy_bitmap(tutorial->book5);
    al_destroy_bitmap(tutorial->bookAnimaR);
    al_destroy_bitmap(tutorial->bookAnimaL);
    free(tutorial);
}

TUTORIAL* initTutorial()
{
    TUTORIAL* tutorial = (TUTORIAL*)malloc(sizeof(TUTORIAL));
    if (!tutorial)
    {
        printf_s("Memoria nao alocada tutorial \n");
        exit(-1);
    }
    printf_s("Memoria alocada tutorial!! \n");

    // Inits
    tutorial->cardTutorial1 = initCardTutorial1();
    tutorial->cardTutorial2 = initCardTutorial2();
    tutorial->cardTutorial3 = initCardTutorial3();
    tutorial->cardTutorial4 = initCardTutorial4();
    tutorial->cardTutorial5 = initCardTutorial5();

    tutorial->cardEntidade1 = initCardEntidadeLore1();
    tutorial->cardEntidade3 = initCardEntidadeLore3();
    tutorial->cardEntidade4 = initCardEntidadeLore4();
    tutorial->cardEntidade5 = initCardEntidadeLore5();

    tutorial->book1 = initBook1();
    tutorial->book2 = initBook2();
    tutorial->book3 = initBook3();
    tutorial->book4 = initBook4();
    tutorial->book5 = initBook5();
    tutorial->bookAnimaR = initBookAnimaR();
    tutorial->bookAnimaL = initBookAnimaL();

    //Draw
    tutorial->cardDraw = cardDraw;
    tutorial->loreDraw = loreDraw;
    tutorial->bookDraw = bookDraw;

    tutorial->destroyMap = tutorialHeaderDestroy;
    return tutorial;
}
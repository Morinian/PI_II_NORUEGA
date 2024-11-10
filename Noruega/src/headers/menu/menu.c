#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

ALLEGRO_BITMAP * initBackgroundImage()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* background;
    background = al_load_bitmap("./images/menu/Img_Fundo_Inicio_Game.png");
    if (!background)
    {
        printf_s("\nImagem de background nao alocada");
        exit(-1);
    }
    return background;
}

ALLEGRO_BITMAP* initArrowImage()
{
    // Carregar imagem da seta
    ALLEGRO_BITMAP* arrow;
    arrow = al_load_bitmap("./images/seta.png");
    if (!arrow)
    {
        printf_s("\nImagem da seta nao alocada");
        exit(-1);
    }
    return arrow;
}

ALLEGRO_BITMAP* initBookMenu()
{
    // Carregar imagem do livro
    ALLEGRO_BITMAP* bookMenuImage;
    bookMenuImage = al_load_bitmap("./images/livro/livro.png");
    if (!bookMenuImage)
    {
        printf_s("\nImagem do livro nao alocada");
        exit(-1);
    }
    return bookMenuImage;
}

void menuDraw(int width, int height, ALLEGRO_BITMAP* background)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(background,
        0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, width, height,
        0);
    // Desenha a imagem de fundo redimensionada
}

void menuArrowDraw(int width, int height, ALLEGRO_BITMAP* seta)
{
    // Desenhar a seta
    al_draw_bitmap(seta, width, height, 0);
}

void menuBookDraw(int width, int height, ALLEGRO_BITMAP* bookMenuImage)
{
    // Desenhar a bookMenuImage
    al_draw_bitmap(bookMenuImage, width, height, 0);
}

void menuHeaderDestroy(MENU* menu)
{
    al_destroy_bitmap(menu->backgroundImage);
    al_destroy_bitmap(menu->arrowImage);
    al_destroy_bitmap(menu->bookMenuImage);
    free(menu);
}

MENU* initMenu()
{
    MENU* menu = (MENU*)malloc(sizeof(MENU));
    if (!menu)
    {
        printf_s("Memoria nao alocada menu \n");
        exit(-1);
    }
    printf_s("Memoria alocada menu!! \n");

    menu->backgroundImage = initBackgroundImage();
    menu->arrowImage = initArrowImage();
    menu->bookMenuImage = initBookMenu();

    menu->drawMenu = menuDraw;
    menu->drawArrow = menuArrowDraw;
    menu->drawBookMenu = menuBookDraw;

    menu->destroyMenu = menuHeaderDestroy;
    return menu;
}
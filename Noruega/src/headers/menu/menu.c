#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

ALLEGRO_BITMAP * initBackgroundImage()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* background;
    background = al_load_bitmap("./images/Img_Fundo_Inicio_Game.png");
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

void menuDraw(int width, int height, ALLEGRO_BITMAP * background)
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

void menuHeaderDestroy(MENU* menu)
{
    al_destroy_bitmap(menu->backgroundImage);
    al_destroy_bitmap(menu->arrowImage);
    free(menu);
}

MENU * initMenu()
{
    MENU * menu = (MENU *) malloc(sizeof(MENU));
    if (!menu)
    {
        printf_s("Memoria nao alocada menu \n");
        exit(-1);
    }
    printf_s("Memoria alocada menu!! \n");

    menu->backgroundImage = initBackgroundImage();
    menu->arrowImage = initArrowImage();

    menu->drawMenu = menuDraw;
    menu->drawArrow = menuArrowDraw;

    menu->destroyMenu = menuHeaderDestroy;
    return menu;
}
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

ALLEGRO_BITMAP * initBackgroundImage()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* background;
    background = al_load_bitmap("./Img_Fundo_Inicio_Game.png");
    if (!background)
    {
        printf_s("Imagem de background nao alocada");
        exit(-1);
    }
    return background;
}

void menuDraw(int width, int height, ALLEGRO_BITMAP * background)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(background,
        0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, width, height,
        0); // Desenha a imagem de fundo redimensionada
}


void menuHeaderDestroy(MENU* menu)
{
    al_destroy_bitmap(menu->backgroundImage);
    free(menu);
}

MENU * initMenu()
{
    MENU * menu = (MENU *) malloc(sizeof(MENU));
    if (!menu)
    {
        printf_s("Memoria nao alocada");
        exit(-1);
    }
    printf_s("Memoria alocada!!");
    menu->backgroundImage = initBackgroundImage();
    menu->dawMenu = menuDraw;
    menu->destroyMenu = menuHeaderDestroy;
    return &menu;
}
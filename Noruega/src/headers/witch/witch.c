#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "witch.h"

ALLEGRO_BITMAP* initWitchSprite(char image_path[])
{
    // Carregar o sprite da bruxa
    ALLEGRO_BITMAP* sprite;
    sprite = al_load_bitmap(image_path);
    if (!sprite)
    {
        printf_s("\nImagem da Bruxa nao alocada");
        exit(-1);
    }
    return sprite;
}

void drawWitch(WITCH* witch)
{
    al_draw_bitmap(witch->sprite, witch->coordinate_x, witch->coordinate_y, 0);
}

void destroyWitch(WITCH * witch)
{
    al_destroy_bitmap(witch->sprite);
    free(witch);
}

WITCH * initWitch(char image_path[])
{
    WITCH * witch = malloc(sizeof(WITCH));
    if (!witch)
    {
        printf_s("Memória de WITCH não alocada no INIT");
        exit(-1);
    }
    witch->sprite = initWitchSprite(image_path);
    witch->dawWitch = drawWitch;
    witch->destroyWitch = destroyWitch;
    witch->coordinate_x = 200;
    witch->coordinate_y = 280;

    return witch;
}
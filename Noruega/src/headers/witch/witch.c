#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../element/element.h"
#include "../random/random.h"
#include "witch.h"

const int DECK_SIZE = 4;

void atack(WITCH* witch)
{

}

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
    free(witch->deck);
    free(witch);
}

WITCH * initWitch(char image_path[], int coordinate_x, int coordinate_y, int health_points, enum WITCH_TYPE type)
{
    WITCH * witch = malloc(sizeof(WITCH));
    if (!witch)
    {
        printf_s("Memória de WITCH não alocada no INIT");
        exit(-1);
    }
    witch->sprite = initWitchSprite(image_path);
    witch->drawWitch = drawWitch;
    witch->destroyWitch = destroyWitch;
    witch->coordinate_x = coordinate_x;
    witch->coordinate_y = coordinate_y;
    witch->health_points = health_points;
    witch->type = type;
    witch->deck = (enum CHEMICAL_ELEMENTS *) generateRandomIntArrayInRange(DECK_SIZE, ELEMENTS_AMOUNT);

    return witch;
}
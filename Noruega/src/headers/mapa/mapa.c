#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

ALLEGRO_BITMAP * initBackgroundMapImage()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* backgroundMap;
    backgroundMap = al_load_bitmap("./images/Mapa_Jogo.png");
    if (!backgroundMap)
    {
        printf_s("\nImagem de backgroundMap nao alocada");
        exit(-1);
    }
    return backgroundMap;
}

void mapaDraw(int width, int height, ALLEGRO_BITMAP * backgroundMap)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(backgroundMap,
        0, 0, al_get_bitmap_width(backgroundMap), al_get_bitmap_height(backgroundMap),
        0, 0, width, height,
        0); // Desenha a imagem de fundo redimensionada
}

void mapaHeaderDestroy(MAPA* mapa)
{
    //Destruir criações
    al_destroy_bitmap(mapa->backgroundMap);
    free(mapa);
}

MAPA * initMapa()
{
    MAPA * mapa = (MAPA *) malloc(sizeof(MAPA));
    if (!mapa)
    {
        printf_s("Memoria nao alocada mapa \n");
        exit(-1);
    }
    printf_s("Memoria alocada mapa!! \n");

    mapa->backgroundMap = initBackgroundMapImage();
    mapa->drawMap = mapaDraw;
    mapa->destroyMap = mapaHeaderDestroy;
    return mapa;
}
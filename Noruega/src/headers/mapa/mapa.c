#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "../general/general.h"

ALLEGRO_BITMAP * initBackgroundMapImage()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* backgroundMap;
    backgroundMap = al_load_bitmap("./images/Mapa_Jogo.png");
    must_init(backgroundMap, "Imagem de backgroundMap");
    return backgroundMap;
}

ALLEGRO_BITMAP* initUnlockedPhase2()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* unlockedPhase2Image;
    unlockedPhase2Image = al_load_bitmap("./images/SombraFase2.png");
    must_init(unlockedPhase2Image, "Imagem de unlockedPhase2Image");
    return unlockedPhase2Image;
}

ALLEGRO_BITMAP* initUnlockedPhase3()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* unlockedPhase3Image;
    unlockedPhase3Image = al_load_bitmap("./images/SombraFase3.png");
    must_init(unlockedPhase3Image, "Imagem de unlockedPhase3Image");
    return unlockedPhase3Image;
}

void mapaDraw(int width, int height, ALLEGRO_BITMAP * backgroundMap)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(backgroundMap,
        0, 0, al_get_bitmap_width(backgroundMap), al_get_bitmap_height(backgroundMap),
        0, 0, width, height,
        0); // Desenha a imagem de fundo redimensionada
}

void drawShadowPhase(int width, int height, ALLEGRO_BITMAP* unlockedPhase2Image, ALLEGRO_BITMAP* unlockedPhase3Image,int phaseComplete)
{
    if (phaseComplete == 0) {
        al_draw_bitmap(unlockedPhase2Image, 730, 425, 0);
        al_draw_bitmap(unlockedPhase3Image, 450, 225, 0);
    }
    else if (phaseComplete == 1) {
        al_draw_bitmap(unlockedPhase3Image, 450, 225, 0);
    }
}

void mapaHeaderDestroy(MAPA* mapa)
{
    //Destruir criações
    al_destroy_bitmap(mapa->backgroundMap);
    al_destroy_bitmap(mapa->unlockedPhase2Image);
    al_destroy_bitmap(mapa->unlockedPhase3Image);
    free(mapa);
}

MAPA * initMapa()
{
    MAPA * mapa = (MAPA *) malloc(sizeof(MAPA));
    must_init(mapa, "mapa");

    mapa->backgroundMap = initBackgroundMapImage();
    mapa->unlockedPhase2Image = initUnlockedPhase2();
    mapa->unlockedPhase3Image = initUnlockedPhase3();
    mapa->drawMap = mapaDraw;
    mapa->drawShadowPhase = drawShadowPhase;
    mapa->destroyMap = mapaHeaderDestroy;
    return mapa;
}
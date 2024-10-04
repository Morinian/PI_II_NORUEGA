#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "fase3.h"

ALLEGRO_BITMAP * initBackgroundFase3()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* imageBackgroundFase3;
    imageBackgroundFase3 = al_load_bitmap("./images/DueloEntidade.png");
    if (!imageBackgroundFase3)
    {
        printf_s("\nImagem de imageBackgroundFase3 nao alocada");
        exit(-1);
    }
    return imageBackgroundFase3;
}

void fase3Draw(int width, int height, ALLEGRO_BITMAP * imageBackgroundFase3)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(imageBackgroundFase3,
        0, 0, al_get_bitmap_width(imageBackgroundFase3), al_get_bitmap_height(imageBackgroundFase3),
        0, 0, width, height,
        0); 
    // Desenha a imagem de fundo redimensionada
}

void fase3HeaderDestroy(FASE3* fase3)
{
    //Destruir criações
    al_destroy_bitmap(fase3->backgroundFase3);
    free(fase3);
}

FASE3 * initFase3()
{
    FASE3 * fase3 = (FASE3 *) malloc(sizeof(FASE3));
    if (!fase3)
    {
        printf_s("Memoria nao alocada fase 3 \n");
        exit(-1);
    }
    printf_s("Memoria alocada fase 3 \n!!");

    fase3->backgroundFase3 = initBackgroundFase3();
    fase3->drawFase3 = fase3Draw;
    fase3->destroyFase3 = fase3HeaderDestroy;
    return fase3;
}
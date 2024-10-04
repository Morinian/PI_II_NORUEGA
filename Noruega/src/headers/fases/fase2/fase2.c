#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "fase2.h"

ALLEGRO_BITMAP * initBackgroundFase2()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* imageBackgroundFase2;
    imageBackgroundFase2 = al_load_bitmap("./images/DueloBruxa2.png");
    if (!imageBackgroundFase2)
    {
        printf_s("\nImagem de imageBackgroundFase2 nao alocada");
        exit(-1);
    }
    return imageBackgroundFase2;
}

void fase2Draw(int width, int height, ALLEGRO_BITMAP * imageBackgroundFase2)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(imageBackgroundFase2,
        0, 0, al_get_bitmap_width(imageBackgroundFase2), al_get_bitmap_height(imageBackgroundFase2),
        0, 0, width, height,
        0); 
    // Desenha a imagem de fundo redimensionada
}

void fase2HeaderDestroy(FASE2* fase2)
{
    //Destruir criações
    al_destroy_bitmap(fase2->backgroundFase2);
    free(fase2);
}

FASE2 * initFase2()
{
    FASE2 * fase2 = (FASE2 *) malloc(sizeof(FASE2));
    if (!fase2)
    {
        printf_s("Memoria nao alocada fase 2 \n");
        exit(-1);
    }
    printf_s("Memoria alocada fase 2!! \n");

    fase2->backgroundFase2 = initBackgroundFase2();
    fase2->drawFase2 = fase2Draw;
    fase2->destroyFase2 = fase2HeaderDestroy;
    return fase2;
}
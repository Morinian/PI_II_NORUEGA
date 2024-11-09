#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "fase1.h"

ALLEGRO_BITMAP * initBackgroundFase1()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* imageBackgroundFase1;
    imageBackgroundFase1 = al_load_bitmap("./images/DueloBruxa1.png");
    if (!imageBackgroundFase1)
    {
        printf_s("\nImagem de imageBackgroundFase1 nao alocada");
        exit(-1);
    }
    return imageBackgroundFase1;
}

void fase1Draw(int width, int height, ALLEGRO_BITMAP * imageBackgroundFase1)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(imageBackgroundFase1,
        0, 0, al_get_bitmap_width(imageBackgroundFase1), al_get_bitmap_height(imageBackgroundFase1),
        0, 0, width, height,
        0); 
    // Desenha a imagem de fundo redimensionada
}

void fase1HeaderDestroy(FASE1* fase1)
{
    //Destruir criações
    al_destroy_bitmap(fase1->backgroundFase1);
    free(fase1);
}

FASE1 * initFase1()
{
    FASE1 * fase1 = (FASE1 *) malloc(sizeof(FASE1));
    if (!fase1)
    {
        printf_s("Memoria nao alocada fase 1 \n");
        exit(-1);
    }
    printf_s("Memoria alocada fase 1!! \n");

    fase1->backgroundFase1 = initBackgroundFase1();
    fase1->drawFase1 = fase1Draw;
    fase1->destroyFase1 = fase1HeaderDestroy;
    return fase1;
}
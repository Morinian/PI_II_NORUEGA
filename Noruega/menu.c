#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>




ALLEGRO_BITMAP * initBackgroundImage()
{
    // Carregar imagem de fundo
    ALLEGRO_BITMAP* background;
    return background = al_load_bitmap("./Img_Fundo_Inicio_Game.png");
}


void menuDraw(int width, int height, ALLEGRO_BITMAP * background)
{
    // Desenhar o fundo redimensionado
    al_draw_scaled_bitmap(background,
        0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, width, height,
        0); // Desenha a imagem de fundo redimensionada
}


void menuHeaderDestroy(ALLEGRO_BITMAP * background)
{
    al_destroy_bitmap(background);
}

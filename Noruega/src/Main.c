#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "./headers/menu/menu.h"

int main() {
    // Inicializações
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_init_primitives_addon();

    //init menu
    MENU* menu = initMenu();

    // Criação do display e nomear
    ALLEGRO_DISPLAY* display = al_create_display(1000, 550);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Burn the witches down");

    // Fonte e FPS
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

    //--------------------------------------------------------
    // Defina a nova largura e altura da imagem de fundo
    int new_width = 1000; // Defina a largura desejada
    int new_height = 550; // Defina a altura desejada

    //Imagens
    ALLEGRO_BITMAP* seta = al_load_bitmap("./images/seta.png");

    //--------------------------------------------------------
    // Eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    //----------------------------------------------------
    // Variáveis de controle de tela
    bool running = true;

    int screen = 1; //Numero que controla as telas principais
    //MENU -> 1
    //MAPA -> 2
    //TUTORIAL -> 3
    //FASE 1 -> 4
    //FASE 2 -> 5
    //FASE 3 -> 6

    int nphase = 1; //Numero que controla a troca das fases no mapa
    int nmenu = 1; //Numero que controla a troca de telas no menu

    while (running) {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela

        //MENU PRINCIPAL
        if (screen == 1) {

            // Desenhar o fundo redimensionado
            menu->dawMenu(new_width, new_height, menu->backgroundImage);

            //Movimenta a seta para cima e para baixo
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                nmenu = 2;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                nmenu = 1;
            }

            //Enter para decidir para onde vai
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (nmenu == 1) {
                    screen = 2; // MANDA PARA O MAPA
                }
                else if (nmenu == 2) {
                    screen = 3; // MANDA PARA O TUTORIAL
                }
            }

            //Movimenta a seta
            if (nmenu == 1) {
                al_draw_bitmap(seta,340,325, 0);
            }
            else if (nmenu == 2) {
                al_draw_bitmap(seta,340 ,410 , 0);
            }
        }       
     
        al_flip_display();
    }

    //--------------------------------------------------------
    // Destruições

    //Criados
    menu->destroyMenu(menu);

    //imgs
    al_destroy_display(seta);

    //Padrão
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}

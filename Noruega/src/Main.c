#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "./headers/menu/menu.h"
#include "./headers/witch/witch.h"

int main() {
    // Inicializa��es
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    //Init bruxa;
    WITCH* witch = initWitch("./images/BruxinhaMal.png", 200, 280);
    for (int i = 0; i < 4; i++)
        printf_s("\nGerado: %i", witch->deck[i]);
    // Cria��o do display e nomear
    ALLEGRO_DISPLAY* display = al_create_display(1000, 550);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Burn the witches down");

    // Fonte e FPS
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

    // Eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    // Vari�veis de controle de tela
    bool running = true;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela
        // Desenhar o fundo redimensionado
        witch->dawWitch(witch);
        al_flip_display();
    }

    //--------------------------------------------------------
    // Destrui��es
    witch->destroyWitch(witch);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}

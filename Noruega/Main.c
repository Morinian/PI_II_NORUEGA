#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int main() {
    // Inicializa��es
    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();

    // Cria��o do display e nomear
    ALLEGRO_DISPLAY* display = al_create_display(1000, 550);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Burn the witches down");

    // Fonte e FPS
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    //--------------------------------------------------------
    // Imagens uploads
    ALLEGRO_BITMAP* mal = al_load_bitmap("./bruxinhaMal.png");
    ALLEGRO_BITMAP* bem = al_load_bitmap("./bruxinha.png");
    ALLEGRO_BITMAP* p1 = al_load_bitmap("./p1.png");
    ALLEGRO_BITMAP* p2 = al_load_bitmap("./p2.png");
    ALLEGRO_BITMAP* p3 = al_load_bitmap("./p3.png");

    //--------------------------------------------------------
    // Eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    //--------------------------------------------------------
    //Po��es
    bool elementos = true; 
    double last_change_time = 0.0; // Tempo da �ltima mudan�a
    const double CHANGE_DURATION = 3.0; // Dura��o do estado em segundos

    //Lan�ar po��o
    bool lancarp1 = false;
    bool lancarp2 = false;
    bool lancarp3 = false;

    int pocaox = 750;
    int pocaoy = 350;

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) { //Evento do teclado
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_A:
            case ALLEGRO_KEY_S:
            case ALLEGRO_KEY_D:
                elementos = false;
                last_change_time = al_get_time(); // Atualiza o tempo da �ltima mudan�a
                break;
            }
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_A:
                lancarp1 = true;
            case ALLEGRO_KEY_S:
                lancarp2 = true;
            case ALLEGRO_KEY_D:
                lancarp3 = true;
            }
        }

        // Verifica se o tempo passou para restaurar o estado de elementos
        if (!elementos && (al_get_time() - last_change_time) >= CHANGE_DURATION) {
            elementos = true;

            //lan�amento para false
            lancarp1 = false;
            lancarp2 = false;
            lancarp3 = false;

            //Resetar lan�amento
            pocaox = 750;
            pocaoy = 350;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela

        al_draw_text(font, al_map_rgb(255, 255, 255), 480 - 50, 100, 0, "A entidade lhe entrega");
        al_draw_text(font, al_map_rgb(255, 255, 255), 500 - 50, 115, 0, "CLORETO DE ACETILO");

        al_draw_bitmap(mal, 200, 280, 0);
        al_draw_bitmap(bem, 720, 280, 0);

        if (elementos) {
            al_draw_text(font, al_map_rgb(255, 255, 255), 700, 180, 0, "A");
            al_draw_text(font, al_map_rgb(255, 255, 255), 680, 250, 0, "agua");
            al_draw_bitmap(p1, 680, 200, 0);

            al_draw_text(font, al_map_rgb(255, 255, 255), 770, 180, 0, "S");
            al_draw_text(font, al_map_rgb(255, 255, 255), 745, 250, 0, "nitrato");
            al_draw_bitmap(p2, 750, 200, 0);

            al_draw_text(font, al_map_rgb(255, 255, 255), 830, 180, 0, "D");
            al_draw_text(font, al_map_rgb(255, 255, 255), 820, 250, 0, "bromo");
            al_draw_bitmap(p3, 820, 200, 0);
        }

        //Lan�amento de po��o
        if (lancarp1 == true) {
           if (pocaox > 250) {
               pocaox = pocaox - 5;
               al_draw_bitmap(p1, pocaox, pocaoy, 0);
           }else {
               al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "LEVOU DANO");
           }
        }else if (lancarp2 == true) {
            if (pocaox > 250) {
                pocaox = pocaox - 5;
                al_draw_bitmap(p2, pocaox, pocaoy, 0);
            }else {
                al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "NAO LEVOU DANO");
            }
        }else if (lancarp3 == true) {
            if (pocaox > 250) {
                pocaox = pocaox - 5;
                al_draw_bitmap(p3, pocaox, pocaoy, 0);
            }else {
                al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "NAO LEVOU DANO");
            }
        }

        al_flip_display();
    }

    //--------------------------------------------------------
    // Destrui��es 
    al_destroy_bitmap(p1);
    al_destroy_bitmap(p2);
    al_destroy_bitmap(p3);
    al_destroy_bitmap(mal);
    al_destroy_bitmap(bem);

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}

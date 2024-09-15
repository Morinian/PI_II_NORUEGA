//--------------------------------------------------------
//Includes das bibliotecas

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int main() {

    //Inicializações
    al_init();
    al_init_font_addon();
    al_init_image_addon();
    al_install_keyboard();

    //Criação do display e nomear
    ALLEGRO_DISPLAY* display = al_create_display(1000, 550);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Burn the witches down");

    //Fonte e FPS
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    //--------------------------------------------------------
    //Imagens uploads
    
    //Exemplo
    ALLEGRO_BITMAP* mal = al_load_bitmap("./bruxinhaMal.png");
    ALLEGRO_BITMAP* bem = al_load_bitmap("./bruxinha.png");
    ALLEGRO_BITMAP* p1 = al_load_bitmap("./p1.png");
    ALLEGRO_BITMAP* p2 = al_load_bitmap("./p2.png");
    ALLEGRO_BITMAP* p3 = al_load_bitmap("./p3.png");

    //--------------------------------------------------------
    //Eventos

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);


    while (true) {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        al_draw_bitmap(mal, 200, 280, 0);
        al_draw_bitmap(bem, 700, 280, 0);
        al_draw_bitmap(p1, 680, 200, 0);
        al_draw_bitmap(p2, 730, 200, 0);
        al_draw_bitmap(p3, 780, 200, 0);

        al_flip_display();
    }


    //--------------------------------------------------------
    //Destruições 
    al_destroy_font(mal);
    al_destroy_font(bem);
    al_destroy_font(p1);
    al_destroy_font(p2);
    al_destroy_font(p3);

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
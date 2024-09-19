#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "menu.h"

// Função para desenhar o botão transparente
void draw_button(ALLEGRO_FONT* font, int x, int y, int width, int height) {
    // Desenhar o contorno do botão
    al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(0, 0, 0), 0.0); // Contorno branco, com espessura de 2 pixels
}

// Função que verifica se o botão foi clicado
bool is_button_clicked(int mouse_x, int mouse_y, int x, int y, int width, int height) {
    return mouse_x >= x && mouse_x <= (x + width) && mouse_y >= y && mouse_y <= (y + height);
}

int main() {
    // Inicializações
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    //init map
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

    // Imagens do jogo
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
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    // Variáveis de controle de tela
    bool on_main_menu = true; // Se estamos na tela do menu
    bool running = true;

    //Poções
    bool elementos = true;
    double last_change_time = 0.0; // Tempo da última mudança
    const double CHANGE_DURATION = 3.0; // Duração do estado em segundos

    //Lançar poção
    bool lancarp1 = false;
    bool lancarp2 = false;
    bool lancarp3 = false;

    int pocaox = 750;
    int pocaoy = 350;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Tela do menu
        if (on_main_menu) {
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (is_button_clicked(event.mouse.x, event.mouse.y, 410, 333, 195, 60)) {
                    on_main_menu = false; // Trocar para a tela do jogo
                }
            }

            al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela

            // Desenhar o fundo redimensionado
            

            // Desenhar o botão transparente
            draw_button(font, 410, 333, 195, 60);

            al_flip_display();
        }
        // Tela do jogo
        else {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) { // Evento do teclado
                switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_A:
                case ALLEGRO_KEY_S:
                case ALLEGRO_KEY_D:
                    elementos = false;
                    last_change_time = al_get_time(); // Atualiza o tempo da última mudança
                    break;
                }
                switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_A:
                    lancarp1 = true;
                    break;
                case ALLEGRO_KEY_S:
                    lancarp2 = true;
                    break;
                case ALLEGRO_KEY_D:
                    lancarp3 = true;
                    break;
                }
            }

            // Verifica se o tempo passou para restaurar o estado de elementos
            if (!elementos && (al_get_time() - last_change_time) >= CHANGE_DURATION) {
                elementos = true;
                lancarp1 = false;
                lancarp2 = false;
                lancarp3 = false;

                // Resetar lançamento
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

            // Lançamento de poção
            if (lancarp1) {
                if (pocaox > 250) {
                    pocaox -= 5;
                    al_draw_bitmap(p1, pocaox, pocaoy, 0);
                }
                else {
                    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "LEVOU DANO");
                }
            }
            else if (lancarp2) {
                if (pocaox > 250) {
                    pocaox -= 5;
                    al_draw_bitmap(p2, pocaox, pocaoy, 0);
                }
                else {
                    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "NAO LEVOU DANO");
                }
            }
            else if (lancarp3) {
                if (pocaox > 250) {
                    pocaox -= 5;
                    al_draw_bitmap(p3, pocaox, pocaoy, 0);
                }
                else {
                    al_draw_text(font, al_map_rgb(255, 255, 255), 200, 200, 0, "NAO LEVOU DANO");
                }
            }

            al_flip_display();
        }
    }

    //--------------------------------------------------------
    // Destruições
    menu->destroyMenu(menu);
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

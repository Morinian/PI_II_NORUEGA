#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "./headers/battle/battle_map/battle_map.h"
#include "./headers/general/general.h"
#include "./headers/menu/menu.h"
#include "./headers/witch/witch.h"
#include "./headers/battle/battle.h"
//import temporario para teste


int main() {
    // Inicializações
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    //Init bruxa;
    WITCH* player = initWitch("./images/bruxas/BruxinhaMal.png", 200, 370, 500, WATER);
    WITCH* bot = initWitch("./images/bruxas/Bruxinha.png", 900, 370, 350, FIRE);
    for (int i = 0; i < 4; i++)
       printf_s("  Gerado: %i   ", player->deck[i]);

    //init battle
    
    BATTLE_MAP * battle_map = initBattleMap("./images/batalha_cenario/battle_background.png",
                                            "./images/batalha_cenario/footer_background.png",
                                            "./images/batalha_cenario/entity_shadow.png",
                                            "./images/batalha_cenario/element_parchment.png",
                                            "./images/batalha_cenario/mix_parchment.png");
    BATTLE_PVE * battle_pve = initBattlePVE(player, bot, battle_map);

    // Criação do display e nomear
    ALLEGRO_DISPLAY* display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Burn the witches down");

    // Fonte e FPS
    ALLEGRO_FONT* small_font = al_load_font("./fonts/PaytoneOne-Regular.ttf", 16, 0);
    ALLEGRO_FONT* large_font = al_load_font("./fonts/PaytoneOne-Regular.ttf", 32, 0);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

    // Eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    bool running = true;
    int display_width = al_get_display_width(display);
    int  display_height = al_get_display_height(display);

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        //al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela
        battle_pve->play(event_queue, battle_pve, large_font);
    }
    
    //--------------------------------------------------------
    // Destruições
    battle_pve->destroyBattle(battle_pve);
    al_destroy_font(small_font);
    al_destroy_font(large_font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}

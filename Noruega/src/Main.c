#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "./headers/element/element.h"
#include "./headers/general/general.h"
#include "./headers/menu/menu.h"
#include "./headers/witch/witch.h"
#include "./headers/battle/battle_map/battle_map.h"
#include "./headers/battle/battle.h"

#include "./headers/mapa/mapa.h"
#include "./headers/tutorial/tutorial.h"
#include "./headers/witch/witch.h"


int main() {
    // Inicializações
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_init_primitives_addon();

    //init Headers
    MENU* menu = initMenu();
    MAPA* mapa = initMapa();
    TUTORIAL* tutorial = initTutorial();
    ELEMENTO* elemento = initElemento();

    //init Bruxas
    WITCH* player = initWitch("./images/bruxas/bruxa.png", 200, 340, 200, FIRE);
    WITCH* bot = initWitch("./images/bruxas/inimigo1.png", 900, 340, 200, WATER);

    /*
    WITCH* player = initWitch("./images/bruxas/bruxa.png", 230, 180, 350, FIRE);
    WITCH* bruxa1 = initWitch("./images/bruxas/inimigo1.png", 860, 180, 350, FIRE);
    WITCH* bruxa2 = initWitch("./images/bruxas/inimigo2.png", 860, 140, 350, FIRE);
    WITCH* inimigo3 = initWitch("./images/bruxas/inimigo3.png", 860, 0, 350, FIRE);
    WITCH* entidadePrin = initWitch("./images/bruxas/entidadePrin.png", 500, 20, 350, FIRE);
    WITCH* entidadeSec = initWitch("./images/bruxas/entidadeSec.png", 500, 20, 350, FIRE);
    */

    //init battle
    BATTLE_MAP* battle_map = initBattleMap("./images/batalha_cenario/battle_background.png",
        "./images/batalha_cenario/footer_background.png",
        "./images/batalha_cenario/entity_shadow.png",
        "./images/batalha_cenario/element_parchment.png",
        "./images/batalha_cenario/mix_parchment.png");
    BATTLE_PVE* battle_pve = initBattlePVE(player, bot, battle_map);

    //------------------------------------------------------------
    // Defina a nova largura e altura da imagem de fundo e display
    int width = 1200; // Defina a largura desejada
    int height = 700; // Defina a altura desejada

    // Criação do display e nomear
    ALLEGRO_DISPLAY* display = al_create_display(width, height);
    al_set_window_position(display, 80, 30);
    al_set_window_title(display, "Burn the witches down");

    // FPS e Fonts
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_FONT* small_font = al_load_font("./fonts/PaytoneOne-Regular.ttf", 16, 0);
    ALLEGRO_FONT* medium_font = al_load_font("./fonts/PaytoneOne-Regular.ttf", 22, 0);
    ALLEGRO_FONT* large_font = al_load_font("./fonts/PaytoneOne-Regular.ttf", 32, 0);
    ALLEGRO_FONT* font = al_create_builtin_font();
   
    //--------------------------------------------------------
    // Eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    //-------------------------------------------------------
    //imagens finais 
    ALLEGRO_BITMAP* gameover = al_load_bitmap("./images/menu/img_game_over.png");
    ALLEGRO_BITMAP* youwin = al_load_bitmap("./images/menu/img_you_win.png");
    ALLEGRO_BITMAP* entidadeFinal = al_load_bitmap("./images/menu/entidade_final.png");

    //----------------------------------------------------
    // Variáveis de controle de tela
    bool running = true;
    int display_width = al_get_display_width(display);
    int  display_height = al_get_display_height(display);

    //Cada tela
    enum screen {
        MENU,
        MAPA,
        LIVRO,
        TUTORIAL,
        FASE1,
        FASE2,
        FASE3
    };

    //Bloqueador de fase
    enum phaseBlock {
        BLOCK,
        PHASE2UNLOCKED,
        PHASE3UNLOCKED
    };

    //Fases completadas
    int phaseComplete = 0;
    //0->fase um incompleta
    //1->fase um completa
    //2->fase dois completa

    // Variável que controla a tela
    enum screen screen = MENU;

    // Variável Bloqueador de fase
    enum phaseBlock phaseBlock = BLOCK;

    int ntutorial = 0; //Numero que controla a troca das fases no mapa
    int nphase = 0; //Numero que controla a troca das fases no mapa
    int nmenu = 1; //Numero que controla a troca de telas no menu
    int nlore = 1; //Numero que controla a troca das img lore
    int nbook = 1;//Numero que controla a troca das img do livro
    int play = 0; // disparo da animação do livro
    int timeFinal = 0;//time que conta para o jogo fechar

    bool redraw = false;

    while (running) {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        //MENU PRINCIPAL
        if (screen == MENU) {

            //Movimenta a seta para cima e para baixo
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (nmenu == 3 && event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    nmenu += 0;
                }
                else if (nmenu == 1 && event.keyboard.keycode == ALLEGRO_KEY_UP) {
                    nmenu += 0;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    nmenu = nmenu + 1;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                    nmenu = nmenu - 1;
                }
            }

            //Enter para decidir para onde vai
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (nmenu == 1) {
                    screen = MAPA;
                }
                else if (nmenu == 2) {
                    screen = TUTORIAL;
                    ntutorial = 1;
                }
                else if (nmenu == 3) {
                    screen = LIVRO;
                    nbook = 1;
                }
            }

            
            if (redraw && al_is_event_queue_empty(event_queue))
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela

                //Menu completo img e livro -------------------------
                menu->drawMenu(width, height, menu->backgroundImage);
                menu->drawBookMenu(1050, 10, menu->bookMenuImage);

                //Movimenta a seta
                if (nmenu == 1) {
                    menu->drawArrow(400, 415, menu->arrowImage);
                }
                else if (nmenu == 2) {
                    menu->drawArrow(400, 520, menu->arrowImage);
                }
                else if (nmenu == 3) {
                    menu->drawArrow(980, 30, menu->arrowImage);
                }

                al_flip_display();
                redraw = false;
            }
            
        }
        else if (screen == MAPA){

            //Allegro event key down lê o teclado apenas uma vez
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (nphase == 3 && event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    nphase += 0;
                }
                else if (nphase == 1 && event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    nphase += 0;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    nphase = nphase + 1;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    nphase = nphase - 1;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    screen = MENU;
                    nphase = 0;
                }
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (nphase == 1) {
                    screen = FASE1; 
                }
                else if (nphase == 2 && phaseComplete == 1) {
                    screen = FASE2; 
                }
                else if (nphase == 3 && phaseComplete == 2) {
                    screen = FASE3;
                    nlore = 1;
                }
            }
            if (redraw && al_is_event_queue_empty(event_queue))
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela

                //Desenho o mapa
                mapa->drawMap(width, height, mapa->backgroundMap);
                mapa->drawShadowPhase(width, height, mapa->unlockedPhase2Image, mapa->unlockedPhase3Image, phaseComplete);

                if (nphase == 1) {
                    menu->drawArrow(365, 425, menu->arrowImage);
                }
                else if (nphase == 2) {
                    menu->drawArrow(810, 425, menu->arrowImage);
                }
                else if (nphase == 3) {
                    menu->drawArrow(580, 330, menu->arrowImage);
                }

                //Tela de game over
                if (nphase == -10) {
                    al_draw_scaled_bitmap(gameover,
                        0, 0, al_get_bitmap_width(gameover), al_get_bitmap_height(gameover),
                        0, 0, width, height,
                        0);
                    timeFinal++;
                    if (timeFinal == 40) {
                        al_destroy_display(display);
                        return -1;
                    }
                }

                //tela de vitoria 
                if (phaseComplete == 3) {
                    al_draw_scaled_bitmap(entidadeFinal,
                        0, 0, al_get_bitmap_width(entidadeFinal), al_get_bitmap_height(entidadeFinal),
                        0, 0, width, height,
                        0);
                    timeFinal++;
                    if (timeFinal >= 70) {
                        al_draw_scaled_bitmap(youwin,
                            0, 0, al_get_bitmap_width(youwin), al_get_bitmap_height(youwin),
                            0, 0, width, height,
                            0);

                        if (timeFinal == 140) {
                            al_destroy_display(display);
                            return -1;
                        }

                    }
                }

                al_flip_display();
                redraw = false;
            }
        }
        else if (screen == LIVRO) {

            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    screen = MENU;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    play = 1;

                    if (nbook < 5) {
                        nbook++;
                    }
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    play = 2;

                    if (nbook > 1) {
                        nbook--;
                    }
                }
            }
            if (redraw && al_is_event_queue_empty(event_queue))
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela

                //Menu completo img e livro -------------------------
                menu->drawMenu(width, height, menu->backgroundImage);
                menu->drawBookMenu(1050, 10, menu->bookMenuImage);

                //Desenha o livro junto com a animação
                tutorial->bookDraw(tutorial->bookAnimaR, tutorial->bookAnimaL, tutorial->book1, tutorial->book2, tutorial->book3, tutorial->book4, tutorial->book5, &play, nbook, 1095, 687, 80, 0);
                al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 100, ALLEGRO_ALIGN_CENTER, "%d", nbook);

                al_flip_display();
                redraw = false;
            }
        }
        else if (screen == TUTORIAL) { 
          
            //Allegro event key down lê o teclado apenas uma vez
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    screen = MENU;
                }
                else if (ntutorial == 5 && event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    ntutorial += 0;
                }
                else if (ntutorial == 1 && event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    ntutorial += 0;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    ntutorial = ntutorial + 1;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    ntutorial = ntutorial - 1;
                }
            }

            if (redraw && al_is_event_queue_empty(event_queue))
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela

                //Menu completo img e livro -------------------------
                menu->drawMenu(width, height, menu->backgroundImage);
                menu->drawBookMenu(1050, 10, menu->bookMenuImage);

                //Desenha os cards do tutorial
                tutorial->cardDraw(112, 0, tutorial->cardTutorial1, tutorial->cardTutorial2, tutorial->cardTutorial3, tutorial->cardTutorial4, tutorial->cardTutorial5, ntutorial);
                
                al_flip_display();
                redraw = false;
            }
        }
        else if (screen == FASE1) {

            player->sprite_frames[0] = 125; 
            player->sprite_frames[1] = 250;
            bot->sprite_frames[0] = 160;
            bot->sprite_frames[1] = 292;

            al_resize_display(display, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            //retorna true se o player venceu
            if (battle_pve->play(event_queue, battle_pve, large_font, medium_font, elemento))
                phaseComplete = 1;
            else {
                bot->health_points = bot->base_health;
                player->health_points = player->base_health;
                nphase = 0;
            }

            al_resize_display(display, width, height);
            screen = MAPA;
        }
        else if (screen == FASE2) { 

            bot->changeWitchSprite(bot, "./images/bruxas/inimigo2.png");
            bot->health_points = bot->base_health;
            bot->damage_received_multiplier = 1;
            bot->type = FIRE;
            bot->sprite_frames[0] = 205;
            bot->sprite_frames[1] = 296;
            bot->coordinate_y -= 50;
            player->health_points = player->base_health;
            player->damage_received_multiplier = 1;
            
            al_resize_display(display, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            //retorna true se o player venceu
            if (battle_pve->play(event_queue, battle_pve, large_font, medium_font, elemento)) {
                phaseComplete = 2;
            }
            else {
                bot->health_points = bot->base_health;
                player->health_points = player->base_health;
                nphase = 0;
            }
            al_resize_display(display, width, height);
            screen = MAPA;
            
        }
        else if (screen == FASE3) { 

            if (redraw && al_is_event_queue_empty(event_queue))
            {
                al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela

                //Desenha os cards do tutorial
                tutorial->loreDraw(width, height, tutorial->cardEntidade1, tutorial->cardEntidade3, tutorial->cardEntidade4, tutorial->cardEntidade5, nlore);

                al_flip_display();
                redraw = false;
            }

            if (nlore > 4) {

                bot->changeWitchSprite(bot, "./images/bruxas/inimigo3.png");
                bot->health_points = bot->base_health;
                bot->damage_received_multiplier = 1;
                bot->type = GROUND;
                bot->sprite_frames[0] = 253;
                bot->sprite_frames[1] = 396;
                bot->coordinate_y -= 100;
                player->health_points = player->base_health;
                player->damage_received_multiplier = 1;

                al_resize_display(display, DISPLAY_WIDTH, DISPLAY_HEIGHT);
                //retorna true se o player venceu
                if (battle_pve->play(event_queue, battle_pve, large_font, medium_font, elemento))
                    phaseComplete = 3; //fala para o MAPA renderizar a img de vitoria
                else {
                    bot->health_points = bot->base_health;
                    player->health_points = player->base_health;
                    nphase = -10; //fala para o MAPA renderizar a img de derrota
                }
                al_resize_display(display, width, height);
                screen = MAPA;
            }

            //Allegro event key down lê o teclado apenas uma vez
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    nlore = nlore + 1;
                }
            }
        }    
    }
    
    //--------------------------------------------------------

    // Destruições

    //Criados
    menu->destroyMenu(menu);
    mapa->destroyMap(mapa);
    tutorial->destroyMap(tutorial);
    elemento->destroyElemento(elemento);

    //imagens finais
    al_destroy_bitmap(gameover);
    al_destroy_bitmap(youwin);
    al_destroy_bitmap(entidadeFinal);
    
    //Padrão 
    al_destroy_font(font);
    al_destroy_font(small_font);
    al_destroy_font(large_font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}

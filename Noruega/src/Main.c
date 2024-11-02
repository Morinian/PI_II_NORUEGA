#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

//Headers
#include "./headers/menu/menu.h"
#include "./headers/mapa/mapa.h"
#include "./headers/tutorial/tutorial.h"
#include "./headers/fases/fase1/fase1.h"
#include "./headers/fases/fase2/fase2.h"
#include "./headers/fases/fase3/fase3.h"
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
    FASE1* fase1 = initFase1();
    FASE2* fase2 = initFase2();
    FASE3* fase3 = initFase3();

    //init Bruxas
    WITCH* player = initWitch("./images/bruxas/bruxa.png", 230, 180, 350, FIRE);
    WITCH* bruxa1 = initWitch("./images/bruxas/inimigo1.png", 860, 180, 350, FIRE);
    WITCH* bruxa2 = initWitch("./images/bruxas/inimigo2.png", 860, 140, 350, FIRE);
    WITCH* entidade = initWitch("./images/bruxas/entidade.png", 860, 0, 350, FIRE);

    //--------------------------------------------------------
    // Defina a nova largura e altura da imagem de fundo
    int width = 1200; // Defina a largura desejada
    int height = 700; // Defina a altura desejada

    // Criação do display e nomear
    ALLEGRO_DISPLAY* display = al_create_display(width, height);
    al_set_window_position(display, 80, 30);
    al_set_window_title(display, "Burn the witches down");

    // FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
   
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

    //Cada tela
    enum screen {
        MENU,
        MAPA,
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

    while (running) {

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        
        al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela

        //MENU PRINCIPAL
        if (screen == MENU) {

            // Desenhar o fundo redimensionado
            if (phaseBlock == BLOCK) {
                menu->drawMenu(width, height, menu->backgroundImage);
            }
            else if (phaseBlock == PHASE2UNLOCKED) {
                menu->drawMenu(width, height, menu->backgroundImage);
            }
            else if (phaseBlock == PHASE3UNLOCKED) {
                menu->drawMenu(width, height, menu->backgroundImage);
            }

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
                    screen = MAPA; 
                }
                else if (nmenu == 2) {
                    screen = TUTORIAL; 
                    ntutorial = 1;
                }
            }

            //Movimenta a seta
            if (nmenu == 1) {
                menu->drawArrow(400, 415, menu->arrowImage);
            }
            else if (nmenu == 2) {
                menu->drawArrow(400, 520, menu->arrowImage);
            }
        }
      
        else if (screen == MAPA){
          
            //Desenho o mapa
            mapa->drawMap(width, height, mapa->backgroundMap);
            mapa->drawShadowPhase(width, height, mapa->unlockedPhase2Image, mapa->unlockedPhase3Image, phaseComplete);

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
                    nphase = -1;
                }
            }

            if (nphase == 1) {
                menu->drawArrow(365, 425, menu->arrowImage);
            }
            else if (nphase == 2) {
                menu->drawArrow(810, 425, menu->arrowImage);
            }
            else if (nphase == 3) {
                menu->drawArrow(580, 330, menu->arrowImage);
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

        }
        else if (screen == TUTORIAL) { 
          
            // Desenhar o fundo redimensionado
            menu->drawMenu(width, height, menu->backgroundImage);

            //Allegro event key down lê o teclado apenas uma vez
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    screen = MENU;
                }
                else if (ntutorial == 3 && event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
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

            //Desenha os cards do tutorial
            tutorial->cardDraw(112, 0, tutorial->cardTutorial1, tutorial->cardTutorial2, tutorial->cardTutorial3,ntutorial);

        }
        else if (screen == FASE1) {

            fase1->drawFase1(width, height, fase1->backgroundFase1);

            player->drawWitch(player,125,250);
            bruxa1->drawWitch(bruxa1,160,250);

            //Allegro event key down lê o teclado apenas uma vez
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    phaseComplete = 1;
                    screen = MAPA;
                }
            }
        }
        else if (screen == FASE2) { 

            fase2->drawFase2(width, height, fase2->backgroundFase2);

            player->drawWitch(player,125,250);
            bruxa2>drawWitch(bruxa2,205,296);

            //Allegro event key down lê o teclado apenas uma vez
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    phaseComplete = 2;
                    screen = MAPA;
                }
            }
        }
        else if (screen == FASE3) { 

            fase3->drawFase3(width, height, fase3->backgroundFase3);
            tutorial->loreDraw(width, height, tutorial->cardEntidade1, tutorial->cardEntidade3, tutorial->cardEntidade4, tutorial->cardEntidade5, nlore);

            if (nlore > 4) {
                player->drawWitch(player, 125, 250);
                entidade > drawWitch(entidade,253,396);
            }

            //Allegro event key down lê o teclado apenas uma vez
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    screen = MAPA;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    nlore = nlore + 1;
                }
            }
        }     
        al_flip_display();
    }

    //--------------------------------------------------------
    // Destruições

    //Criados
    menu->destroyMenu(menu);
    mapa->destroyMap(mapa);
    tutorial->destroyMap(tutorial);
    fase1->destroyFase1(fase1);
    fase2->destroyFase2(fase2);
    fase3->destroyFase3(fase3);
    player->destroyWitch(player);
    entidade->destroyWitch(entidade);
    bruxa1->destroyWitch(bruxa1);
    bruxa2->destroyWitch(bruxa2);

    //Padrão
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}

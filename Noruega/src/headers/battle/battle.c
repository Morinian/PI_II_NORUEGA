#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "../battle/battle_map/battle_map.h"
#include "../element/element.h"
#include "../witch/witch.h"
#include "../battle/battle.h"
#include "../random/random.h"

void renderBattle(BATTLE_MAP* battle_map, int chosen_element, int round, int timer, 
	ALLEGRO_FONT* font, BATTLE_PVE* battle_pve, enum CHEMICAL_ELEMENTS central_element)
{
	battle_map->drawBattleMap(battle_map, chosen_element);
	al_draw_textf(font, al_map_rgba_f(0, 0, 1, 0.5), 650, 250, ALLEGRO_ALIGN_CENTER, "%d", central_element);

	//Desenha o player, sua barra de vida e seus status
	float inicial_x_player_bar = 100;
	float health_player_bar_size = inicial_x_player_bar + (250.0 * (battle_pve->player->health_points / (float)battle_pve->player->base_health));
	battle_pve->player->drawWitch(battle_pve->player);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 50, 15, ALLEGRO_ALIGN_CENTER, "%d", battle_pve->player->health_points);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 75, ALLEGRO_ALIGN_CENTER, "MDR - %.1f", battle_pve->player->damage_received_multiplier);
	al_draw_filled_rectangle(inicial_x_player_bar, 15, health_player_bar_size, 50, al_map_rgba_f(1, 0, 0, 0.5));

	//Desenha o bot, sua barra de vida e seus status
	float inicial_x_bot_bar = 950;
	float health_bot_bar_size = 950 + (250.0 * (battle_pve->bot->health_points / (float)battle_pve->bot->base_health));
	battle_pve->bot->drawWitch(battle_pve->bot);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 1250, 15, ALLEGRO_ALIGN_CENTER, "%d", battle_pve->bot->health_points);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 1200, 75, ALLEGRO_ALIGN_CENTER, "MDR - %.1f", battle_pve->bot->damage_received_multiplier);
	al_draw_filled_rectangle(inicial_x_bot_bar, 15, health_bot_bar_size, 50, al_map_rgba_f(1, 0, 0, 0.5));

	//Desenha o estado da partida (round e timer do round)
	al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 15, ALLEGRO_ALIGN_CENTER, "Round - %d", round);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 75, ALLEGRO_ALIGN_CENTER, "%d", timer);
	al_flip_display();
}

void play(ALLEGRO_EVENT_QUEUE* event_queue, BATTLE_PVE* battle_pve, ALLEGRO_FONT* font) 
{

	//Cria a variavel que guarda o timer do round e o timer do round
	int current_time;
	ALLEGRO_TIMER* battle_timer = al_create_timer(1.0);
	if (!battle_timer)
	{
		printf_s("\nErro! battle timer não alocado");
		exit(-1);
	}
	al_register_event_source(event_queue, al_get_timer_event_source(battle_timer));
	
	//inicia o contador de rounds e flag que verifica se o round está acontecendo
	battle_pve->round = 1;
	bool in_game = false;

	//flags de atack do player e bot
	bool bot_atacked;
	int bot_time_to_atack;
	bool player_atacked; 

	//Elemento gerado pela entidade
	enum ChemicalElement central_element;
	//Elemento escolhido pelo player
	enum ChemicalElement chosen_deck_element = battle_pve->player->deck[0];
	//Posição do elemento no deck
	int chosen_deck_element_position = 0;

	ALLEGRO_EVENT event;
	
	while (battle_pve->player->health_points > 0 && battle_pve->bot->health_points > 0)
	{
		
		//if (battle_pve->round > 1)
		//{
			//reporDeckElement(battle_pve->player->deck);
			//reporDeckElement(battle_pve->bot->deck);
		//}

		//Inicia as flags de atack do player e do bot para o round
		bot_atacked = false;
		player_atacked = false;
		bot_time_to_atack = generateRandomIntInRange(true, 15);

		//Gera um elemento da entidade para o novo round
		central_element = (enum CHEMICAL_ELEMENTS) generateRandomIntInRange(false, ELEMENTS_AMOUNT);

		//Inicializa flag de novo round, variavel de renderização e timer do round
		in_game = true;
		bool render = false;
		al_start_timer(battle_timer);

		//Zera a variavel que guarda o timer do round, para o inicio de um novo round
		current_time = 0;

		while (in_game)
		{
			al_wait_for_event(event_queue, &event);

			/*Atualiza a flag de renderização quando o timer que acionou o evento
			não é o timer do round, mas sim o timer do FPS */
			current_time = al_get_timer_count(battle_timer);
			if (event.type == ALLEGRO_EVENT_TIMER)
			{
				if (event.timer.source != current_time)
					render = true;
			}
			/*Renderiza apenas quando timer do FPS atualizou e quando não
			tem nenhum outro evento para ser processado*/
			if (render && al_is_event_queue_empty(event_queue))
			{
				renderBattle(battle_pve->battle_map, chosen_deck_element_position, 
					battle_pve->round, current_time, font, battle_pve, central_element);
				render = false;
			}

			//------------------------------------------------------------
			// Lógica de atack do Player e Bot, durante o round 
			if (current_time == 15 || (player_atacked && bot_atacked))
			{
				al_stop_timer(battle_timer);
				al_set_timer_count(battle_timer, 0);
				in_game = false;
			}
			else
			{
				// Atack do player
				if (!player_atacked)
				{ 
					if (event.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						switch (event.keyboard.keycode)
						{
						case ALLEGRO_KEY_Q:
							chosen_deck_element = battle_pve->player->deck[0];
							chosen_deck_element_position = 0;
							printf_s("\nEscolheu o 1 elemento");
							break;
						case ALLEGRO_KEY_W:
							chosen_deck_element = battle_pve->player->deck[1];
							chosen_deck_element_position = 1;
							printf_s("\nEscolheu o 2 elemento");
							break;
						case ALLEGRO_KEY_A:
							chosen_deck_element = battle_pve->player->deck[2];
							chosen_deck_element_position = 2;
							printf_s("\nEscolheu o 3 elemento");
							break;
						case ALLEGRO_KEY_S:
							chosen_deck_element = battle_pve->player->deck[3];
							chosen_deck_element_position = 3;
							printf_s("\nEscolheu o 4 elemento");
							break;
						case ALLEGRO_KEY_ENTER:
							printf_s("\n\n\nPlayer Atacou");
							printf_s("\nANTES ---- Vida player: %i Mult: %f || Vida Bot: %i Mult: %f",
								battle_pve->player->health_points, battle_pve->player->damage_received_multiplier,
								battle_pve->bot->health_points, battle_pve->bot->damage_received_multiplier);
						
							battle_pve->player->atack(battle_pve->player, battle_pve->bot, 
								chosen_deck_element,central_element);

							printf_s("\nDEPOIS ---- Vida player: %i Mult: %f || Vida Bot: %i Mult: %f",
								battle_pve->player->health_points, battle_pve->player->damage_received_multiplier,
								battle_pve->bot->health_points, battle_pve->bot->damage_received_multiplier);
							player_atacked = true;
							break;
						}
					}
				}
				// Atack do Bot
				if ((bot_time_to_atack == current_time || player_atacked) && !bot_atacked)
				{
					//Fazer o bot esperar para atacar, 2 segundos, caso o player tenha atacado antes
					//battle_pve->bot->atack(battle_pve->player, central_element);
					printf_s("\nBot Atacou");
					bot_atacked = true;
				}
			}
		}
		//incrementa o contador de round
		battle_pve->round += 1;
	}
	//Desaloca a memória do timer da batalha
	al_destroy_timer(battle_timer);
}

void destroyBattle(BATTLE_PVE* battle_pve)
{
	battle_pve->player->destroyWitch(battle_pve->player);
	battle_pve->bot->destroyWitch(battle_pve->bot);
	battle_pve->battle_map->destroyBattleMap(battle_pve->battle_map);
	free(battle_pve);
}

BATTLE_PVE* initBattlePVE(WITCH* player, WITCH* bot, BATTLE_MAP* battle_map)
{
	BATTLE_PVE* battle_pve = malloc(sizeof(BATTLE_PVE));
	battle_pve->battle_map = battle_map;
	battle_pve->player = player;
	battle_pve->bot = bot;
	battle_pve->destroyBattle = destroyBattle;
	battle_pve->play = play;
	return battle_pve;
}
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "../battle/battle_map/battle_map.h"
#include "../element/element.h"
#include "../witch/witch.h"
#include "../battle/battle.h"
#include "../random/random.h"

void renderBattle(BATTLE_MAP* battle_map, int chosen_element)
{
	battle_map->drawBattleMap(battle_map, chosen_element);
	al_flip_display();
}

void play(ALLEGRO_EVENT_QUEUE* event_queue, BATTLE_PVE* battle_pve) {

	ALLEGRO_TIMER* battle_timer = al_create_timer(1.0);
	if (!battle_timer)
	{
		printf_s("\nErro! battle timer não alocado");
		exit(-1);
	}
	al_register_event_source(event_queue, al_get_timer_event_source(battle_timer));

	bool in_game = false;
	//inicia o contador de rounds
	battle_pve->round = 1;

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
	renderBattle(battle_pve->battle_map, chosen_deck_element);
	bool re_render = false;
	while (battle_pve->player->health_points > 0 && battle_pve->bot->health_points > 0)
	{
		
		//if (battle_pve->round > 1)
		//{
			//reporDeckElement(battle_pve->player->deck);
			//reporDeckElement(battle_pve->bot->deck);
		//}

		bot_atacked = false;
		player_atacked = false;

		bot_time_to_atack = generateRandomIntInRange(true, 15);
		central_element = (enum CHEMICAL_ELEMENTS) generateRandomIntInRange(false, ELEMENTS_AMOUNT);

		in_game = true;
		al_start_timer(battle_timer);

		printf_s("\nround - %i", battle_pve->round);
		printf_s("\nInicia Battle timer");

		while (in_game)
		{
			
			if (al_get_timer_count(battle_timer) == 15 || (player_atacked && bot_atacked))
			{
				al_stop_timer(battle_timer);
				al_set_timer_count(battle_timer, 0);
				in_game = false;
			}

			else if(!player_atacked)
			{
				// Atack do player
				al_wait_for_event(event_queue, &event);
				if (event.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch (event.keyboard.keycode)
					{
					case ALLEGRO_KEY_Q:
						chosen_deck_element = battle_pve->player->deck[0];
						chosen_deck_element_position = 0;
						printf_s("\nEscolheu o 1 elemento");
						re_render = true;
						break;
					case ALLEGRO_KEY_W:
						chosen_deck_element = battle_pve->player->deck[1];
						chosen_deck_element_position = 1;
						printf_s("\nEscolheu o 2 elemento");
						re_render = true;
						break;
					case ALLEGRO_KEY_A:
						chosen_deck_element = battle_pve->player->deck[2];
						chosen_deck_element_position = 2;
						printf_s("\nEscolheu o 3 elemento");
						re_render = true;
						break;
					case ALLEGRO_KEY_S:
						chosen_deck_element = battle_pve->player->deck[3];
						chosen_deck_element_position = 3;
						printf_s("\nEsolheu o 4 elemento");
						re_render = true;
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
					if (re_render)
					{
						//O load da imagem está demorando d+
						renderBattle(battle_pve->battle_map, chosen_deck_element_position);
						re_render = false;
					}
				}
				// Atack do Bot
				if ((bot_time_to_atack == al_get_timer_count(battle_timer) || player_atacked) && !bot_atacked)
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

//WITCH DEVE SER ALOCADA INTERNAMENTE OU PASSADA VIA PARAMETRO? 
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
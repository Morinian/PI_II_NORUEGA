#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "../witch/witch.h"
#include "../battle/battle.h"

//void renderBattle();

void play(ALLEGRO_EVENT_QUEUE* event_queue, BATTLE_PVE* battle_pve) {

	int bot_time_to_atack;
	int timer;
	bool in_game = false;
	bool bot_atacked;
	bool player_atacked;

	//Elemento gerado pela entidade
	enum ChemicalElement central_element;

	//Elemento escolhido pelo player
	enum ChemicalElement chosen_deck_element = battle_pve->player->deck[0];

	ALLEGRO_EVENT event;
	while (battle_pve->player->health_points != 0 && battle_pve->bot->health_points != 0)
	{
		bot_atacked = false;
		player_atacked = false;

		if (!in_game && battle_pve->round == 0)
		{
			battle_pve->player->deck = initDeck();
			battle_pve->bot->deck = inictDeck();
		}
		else if (!in_game && battle_pve->round > 0)
		{
			reporDeckElement(battle_pve->player->deck);
			reporDeckElement(battle_pve->bot->deck);
		}

		timer = 0; //Segundos
		in_game = true;
		// Tranformar a função de getGeneral elemente em um gerador de número aleatório, 15 é o tempo, para pegar o resto da divisão entre 0 e 14
		bot_time_to_atack = gerarNurmero(15);
		central_element = generateRandomElement();

		while (in_game)
		{
			// Fazer o timer atualizar em segundos
			if (timer == 15 || (player_atacked && bot_atacked))
			{
				in_game = false;
			}

			else
			{
				//Tomar cuidado com Allegro event refrente a inicialização!!!
				//Verifica se existe um evento
				al_wait_for_event(event_queue, &event);

				// Atack do player
				if (event.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					switch (event.keyboard.keycode)
					{
					case ALLEGRO_KEY_Q:
						chosen_deck_element = battle_pve->player->deck[0];
						break;
					case ALLEGRO_KEY_W:
						chosen_deck_element = battle_pve->player->deck[1];
						break;
					case ALLEGRO_KEY_A:
						chosen_deck_element = battle_pve->player->deck[2];
						break;
					case ALLEGRO_KEY_S:
						chosen_deck_element = battle_pve->player->deck[3];
						break;
					case ALLEGRO_KEY_ENTER
						battle_pve->player->atack(battle_pve->bot, central_element);
						player_atacked = true;
						break;
					}
				}
				// Atack do Bot
				if (bot_time_to_atack == timer || player_atacked)
				{
					battle_pve->bot->atack(battle_pve->player, central_element);
					bot_atacked = true;
				}
			}

			// Talvez passar a informação de player e bot individualmente
			battle_pve->renderBattle(battle_pve);

			//incermentar o timer em segundos
			timer += 1;
		}
		//incrementa o contador de round
		battle_pve->round += 1;
	}
}

void destroyBattle(BATTLE_PVE* battle_pve)
{
	battle_pve->player->destroyWitch(battle_pve->player);
	battle_pve->bot->destroyWitch(battle_pve->bot);
	free(battle_pve);
}

//WITCH DEVE SER ALOCADA INTERNAMENTE OU PASSADA VIA PARAMETRO? 
BATTLE_PVE* initBattlePVE(WITCH* player, WITCH* bot)
{
	BATTLE_PVE* battle_pve = malloc(sizeof(BATTLE_PVE));
	battle_pve->player = player;
	battle_pve->bot = bot;
	battle_pve->destroyBattle = destroyBattle;
	//battle_pve->renderBattle = renderBattle;
	battle_pve->play = play;
}
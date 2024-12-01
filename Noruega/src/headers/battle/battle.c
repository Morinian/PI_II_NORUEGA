#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "../element/element.h"
#include "../battle/battle_map/battle_map.h"
#include "../witch/witch.h"
#include "../battle/battle.h"
#include "../random/random.h"
#include "../general/general.h";

const char* nome[15] = {
	"HCl", "NaOH", "H2SO4", "KMnO4", "H2O2", "Cl2", "NH3", "NaClO", "Na", "Mg", "Al", "HNO3", "Fe", "Cu", "Ag"
};

const char* resultado[6] = {
	"Compativel", "Incompatibilidade acido base", "Incompatibilidade redox", "Incompatibilidade componentes toxicos", "Reacao com agua", "Reacao com metal"
};

ALLEGRO_BITMAP* returnWitchIcon(enum WITCH_TYPE type, BATTLE_MAP * battle_map) {
	if (type == WATER)
		return battle_map->water_icon;
	else if (type == FIRE)
		return battle_map->fire_icon;
	else if (type == GROUND)
		return battle_map->ground_icon;
	else
	{
		printf("\nTipo de bruxa não encontrado, esse icone não existe");
		exit(-1);
	}
}

void renderBattle(BATTLE_MAP* battle_map, int chosen_element, int round, int timer,
	ALLEGRO_FONT* font, ALLEGRO_FONT* font_medium, BATTLE_PVE* battle_pve, enum CHEMICAL_ELEMENTS central_element,
	ELEMENTO* elemento)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));// Limpa a tela
	battle_map->drawBattleMap(battle_map, battle_pve->player->damage_received_multiplier,
		battle_pve->bot->damage_received_multiplier ,chosen_element);

	//Desenha o elemento da entidade
	al_draw_textf(font, al_map_rgba_f(0, 0, 1, 0.5), 650, 250, ALLEGRO_ALIGN_CENTER, "%s", nome[central_element]);

	//Pergaminho
	al_draw_textf(font_medium, al_map_rgba_f(0, 0, 0, 1), 970, 670, ALLEGRO_ALIGN_CENTER, "A combinacao elementos ");
	al_draw_textf(font_medium, al_map_rgba_f(0, 0, 0, 1), 970, 698, ALLEGRO_ALIGN_CENTER, "%s com %s",
		nome[central_element], nome[battle_pve->player->deck[chosen_element]]);
	al_draw_textf(font_medium, al_map_rgba_f(0, 0, 0, 1), 970, 725, ALLEGRO_ALIGN_CENTER, "%s",
		resultado[mixElements(battle_pve->player->deck[chosen_element], central_element)]);

	//Array dos ponteiros das iamgens dos elementos
	ALLEGRO_BITMAP* elementoImage[15] = {
		elemento->HCl,elemento->NaOH,elemento->H2SO4,elemento->KMnO4,elemento->H2O2,elemento->Cl2,elemento->NH3,elemento->NaClO,elemento->Na,elemento->Mg,elemento->Al,elemento->HNO3,elemento->Fe,elemento->Cu,elemento->Ag
	};

	//Render do deck da mão do player
	al_draw_bitmap(elementoImage[battle_pve->player->deck[0]], 25, 615, 0);
	al_draw_bitmap(elementoImage[battle_pve->player->deck[1]], 250, 615, 0);
	al_draw_bitmap(elementoImage[battle_pve->player->deck[2]], 25, 740, 0);
	al_draw_bitmap(elementoImage[battle_pve->player->deck[3]], 250, 740, 0);

	//Desenha o player, sua barra de vida e seus status
	float inicial_x_player_bar = 100;
	float health_player_bar_size = inicial_x_player_bar + (250.0 * (battle_pve->player->health_points / (float)battle_pve->player->base_health));
	battle_pve->player->drawWitch(battle_pve->player);
	al_draw_filled_rectangle(inicial_x_player_bar, 40, health_player_bar_size, 75, al_map_rgba_f(1, 0, 0, 0.5)); //barra de vida
	al_draw_textf(font_medium, al_map_rgb(255, 255, 255), 220, 40, ALLEGRO_ALIGN_CENTER, "%d", battle_pve->player->health_points);
	al_draw_bitmap(battle_map->cardLife, 20, 10, 0); //moldura da barra de vida
	//Desenha o tipo do player
	ALLEGRO_BITMAP* player_type_icon = returnWitchIcon(battle_pve->player->type, battle_map);
	al_draw_scaled_bitmap(player_type_icon, 0, 0, al_get_bitmap_width(player_type_icon), 
		al_get_bitmap_height(player_type_icon), 360, 0, 100, 100, 0);
	

	//Desenha o bot, sua barra de vida e seus status
	float inicial_x_bot_bar = 950;
	float health_bot_bar_size = 950 + (250.0 * (battle_pve->bot->health_points / (float)battle_pve->bot->base_health));
	battle_pve->bot->drawWitch(battle_pve->bot);
	al_draw_filled_rectangle(inicial_x_bot_bar, 40, health_bot_bar_size, 75, al_map_rgba_f(1, 0, 0, 0.5));  //barra de vida
	al_draw_textf(font_medium, al_map_rgb(255, 255, 255), 1080, 40, ALLEGRO_ALIGN_CENTER, "%d", battle_pve->bot->health_points);
	al_draw_bitmap(battle_map->cardLife, 930, 10, ALLEGRO_FLIP_HORIZONTAL);//moldura da barra de vida
	//Desenha o tipo do player
	ALLEGRO_BITMAP* bot_type_icon = returnWitchIcon(battle_pve->bot->type, battle_map);
	al_draw_scaled_bitmap(bot_type_icon, 0, 0, al_get_bitmap_width(bot_type_icon),
		al_get_bitmap_height(bot_type_icon), 842, 0, 100, 100, 0);

	//Desenha o estado da partida (round e timer do round)
	al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 15, ALLEGRO_ALIGN_CENTER, "Round - %d", round);
	al_draw_textf(font, al_map_rgb(255, 255, 255), 650, 75, ALLEGRO_ALIGN_CENTER, "%d", timer);

	//Passa para a tela desenhada
	al_flip_display();
}

//Retorna true se o player venceu 
bool play(ALLEGRO_EVENT_QUEUE* event_queue, BATTLE_PVE* battle_pve, ALLEGRO_FONT* font, ALLEGRO_FONT* font_medium, ELEMENTO* elemento)
{
	//Cria a variavel que guarda o timer do round e o timer do round
	int current_time;
	ALLEGRO_TIMER* battle_timer = al_create_timer(1.0);
	must_init(battle_timer, "battle timer");
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

		//Inicia as flags de atack do player e do bot para o round
		bot_atacked = false;
		player_atacked = false;
		bot_time_to_atack = generateRandomIntInRange(true, 15);

		//Gera um elemento da entidade para o novo round
		central_element = (enum CHEMICAL_ELEMENTS)generateRandomIntInRange(false, ELEMENTS_AMOUNT);

		//Inicializa flag de novo round, variavel de renderização e timer do round
		in_game = true;
		bool render = false;
		al_start_timer(battle_timer);

		//Zera a variavel que guarda o timer do round, para o inicio de um novo round
		current_time = 0;

		while (in_game)
		{
			al_wait_for_event(event_queue, &event);

			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				printf("\nO jogo foi fechado pela janela");
				exit(1);
			}

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
					battle_pve->round, current_time, font, font_medium, battle_pve, central_element,
					elemento);
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
							battle_pve->player->atack(battle_pve->player, battle_pve->bot, 
								chosen_deck_element,central_element);
							//Troca o elemento utilizado
							chosen_deck_element = (enum CHEMICAL_ELEMENTS) generateRandomIntInRange(false, ELEMENTS_AMOUNT);
							battle_pve->player->deck[chosen_deck_element_position] = chosen_deck_element;
							player_atacked = true;
							break;
						}
					}
				}
				// Atack do Bot
				if ((bot_time_to_atack == current_time || player_atacked) && !bot_atacked)
				{
					printf_s("\n\nBot Atacou");
					//O bot está pegando o elemento da mesma posição que o player escolheu
					battle_pve->bot->atack(battle_pve->bot, battle_pve->player, 
						battle_pve->bot->deck[chosen_deck_element_position], central_element);
					battle_pve->bot->deck[chosen_deck_element_position] = (enum CHEMICAL_ELEMENTS)generateRandomIntInRange(false, ELEMENTS_AMOUNT);
					bot_atacked = true;
				}
			}
		}
		//incrementa o contador de round
		battle_pve->round += 1;
	}
	//Desaloca a memória do timer da batalha
	al_destroy_timer(battle_timer);
	//Verifica quem venceu o combate
	if (battle_pve->player->health_points > battle_pve->bot->health_points)
		return true;
	return false;
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
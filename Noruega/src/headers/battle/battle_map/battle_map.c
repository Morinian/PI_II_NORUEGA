#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../../general/general.h"
#include "battle_map.h"
#include "../../witch/witch.h"


void destroyBattleMap(BATTLE_MAP * battle_map)
{
	al_destroy_bitmap(battle_map->cardLife);
	al_destroy_bitmap(battle_map->battle_background);
	al_destroy_bitmap(battle_map->element_parchment);
	al_destroy_bitmap(battle_map->entity_shadow);
	al_destroy_bitmap(battle_map->footer_background);
	al_destroy_bitmap(battle_map->mix_parchment);
	al_destroy_bitmap(battle_map->angelStatus);
	al_destroy_bitmap(battle_map->evilStatus);
	free(battle_map);
}

ALLEGRO_BITMAP* initCardLife()
{
	// Carregar imagem de fundo
	ALLEGRO_BITMAP* cardLife;
	cardLife = al_load_bitmap("./images/vida_status/barra_de_vida.png");
	if (!cardLife)
	{
		printf_s("\nImagem de initCardLife nao alocada");
		exit(-1);
	}
	return cardLife;
}

ALLEGRO_BITMAP* initScenarioImage(char image_path[])
{
	// Carrega uma imagem do cenário na memória
	ALLEGRO_BITMAP* image;
	image = al_load_bitmap(image_path);
	must_init(image, "Imagem de Battle Map");
	return image;
}

//As posições estão fixas
void renderStatus(BATTLE_MAP* battle_map, float damege_multiplayer, int x, int y, int sinal) {

	if (damege_multiplayer > 1) {
		for (float i = 1; i < damege_multiplayer; i += 0.2)
		{
			al_draw_scaled_bitmap(battle_map->evilStatus, 0, 0,
				al_get_bitmap_width(battle_map->evilStatus), al_get_bitmap_height(battle_map->evilStatus),
				x + (100 * i * sinal), y, 100, 100, 0);
		}
	}
	else {
		for (float i = 1; i < 1+(1-damege_multiplayer); i += 0.2)
		{
			al_draw_scaled_bitmap(battle_map->angelStatus, 0, 0,
				al_get_bitmap_width(battle_map->angelStatus), al_get_bitmap_height(battle_map->angelStatus),
				x + (100 * i * sinal), y, 100, 100, 0);
		}
	}
}

void drawBattleMap(BATTLE_MAP * battle_map, float player_status, float bot_status, int chosen_element)
{
	// Desenhar o fundo da batalha redimensionado 
	al_draw_scaled_bitmap(battle_map->battle_background,
		0, 0, al_get_bitmap_width(battle_map->battle_background), al_get_bitmap_height(battle_map->battle_background),
		0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT * 0.7, 0);

	//Desenha o Background do footer de escolha
	al_draw_scaled_bitmap(battle_map->footer_background, 0, 0,
		al_get_bitmap_width(battle_map->footer_background), al_get_bitmap_height(battle_map->footer_background),
		0, DISPLAY_HEIGHT * 0.7, DISPLAY_WIDTH, DISPLAY_HEIGHT * 0.3, 0);

	//Desenha a entidade centralizada na tela
	al_draw_scaled_bitmap(battle_map->entity_shadow, 0, 0,
		al_get_bitmap_width(battle_map->entity_shadow), al_get_bitmap_height(battle_map->entity_shadow),
		DISPLAY_WIDTH * 0.25, 0, 500, 500, 0);

	//Desenha o pergaminho
	al_draw_scaled_bitmap(battle_map->mix_parchment, 0, 0,
		al_get_bitmap_width(battle_map->mix_parchment), al_get_bitmap_height(battle_map->mix_parchment),
		DISPLAY_WIDTH - 650, DISPLAY_HEIGHT - 270, 630, 280, 0);

	//Desenha o deck no footer, se um elemento é escolhido, muda a opacidade
	int deck_position_coordinates[4][4] = { 
		{5, DISPLAY_HEIGHT - 250}, {230, DISPLAY_HEIGHT - 250},
		{5, DISPLAY_HEIGHT - 130}, {230, DISPLAY_HEIGHT - 130}
	};
	for (int deck_position = 0; deck_position < DECK_SIZE; deck_position++)
	{
		if(chosen_element == deck_position)
			al_draw_tinted_scaled_bitmap(battle_map->element_parchment,
				al_map_rgba_f(0.5, 0.5, 0.5, 0.5), 0, 0,
				al_get_bitmap_width(battle_map->element_parchment), al_get_bitmap_height(battle_map->element_parchment),
				deck_position_coordinates[deck_position][0], 
				deck_position_coordinates[deck_position][1],
				230, 120, 0);
		else
			al_draw_scaled_bitmap(battle_map->element_parchment, 0, 0,
				al_get_bitmap_width(battle_map->element_parchment), al_get_bitmap_height(battle_map->element_parchment),
				deck_position_coordinates[deck_position][0],
				deck_position_coordinates[deck_position][1],
				230, 120, 0);
	}
	renderStatus(battle_map, player_status, 0, 90, 1);
	renderStatus(battle_map, bot_status, 1200, 90, -1);
}


BATTLE_MAP* initBattleMap(char battle_background[], char footer_background[],
	char entity_shadow[], char element_parchment[], char mix_parchment[])
{
	BATTLE_MAP* battle_map = malloc(sizeof(BATTLE_MAP));
	battle_map->cardLife = initCardLife();
	battle_map->battle_background = initScenarioImage(battle_background);
	battle_map->footer_background = initScenarioImage(footer_background);
	battle_map->entity_shadow = initScenarioImage(entity_shadow);
	battle_map->element_parchment = initScenarioImage(element_parchment);
	battle_map->mix_parchment = initScenarioImage(mix_parchment);
	battle_map->destroyBattleMap = destroyBattleMap;
	battle_map->drawBattleMap = drawBattleMap;
	battle_map->renderStatus = renderStatus;
	battle_map->angelStatus = initScenarioImage("./images/vida_status/escudo_bom.png");
	battle_map->evilStatus = initScenarioImage("./images/vida_status/escudo_mal.png");
	return battle_map;
}
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "../../general/general.h"
#include "battle_map.h"
#include "../../witch/witch.h"


void destroyBattleMap(BATTLE_MAP * battle_map)
{
	al_destroy_bitmap(battle_map->battle_background);
	al_destroy_bitmap(battle_map->element_parchment);
	al_destroy_bitmap(battle_map->entity_shadow);
	al_destroy_bitmap(battle_map->footer_background);
	al_destroy_bitmap(battle_map->mix_parchment);
	free(battle_map);
}

ALLEGRO_BITMAP* initScenarioImage(char image_path[])
{
	// Carrega uma imagem do cenário na memória
	ALLEGRO_BITMAP* image;
	image = al_load_bitmap(image_path);
	if (!image)
	{
		printf_s("\nImagem de Battle Map nao alocada");
		exit(-1);
	}
	return image;
}

void drawBattleMap(BATTLE_MAP * battle_map, int chosen_element)
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

	//Desenha 
	al_draw_scaled_bitmap(battle_map->mix_parchment, 0, 0,
		al_get_bitmap_width(battle_map->mix_parchment), al_get_bitmap_height(battle_map->mix_parchment),
		DISPLAY_WIDTH - 600, DISPLAY_HEIGHT - 280, 600, 280, 0);

	//Desenha o deck no footer, se um elemento é escolhido, muda a opacidade
	int deck_position_coordinates[4][4] = { 
		{10, DISPLAY_HEIGHT - 250}, {180, DISPLAY_HEIGHT - 250},
		{10, DISPLAY_HEIGHT - 130}, {180, DISPLAY_HEIGHT - 130}
	};
	for (int deck_position = 0; deck_position < DECK_SIZE; deck_position++)
	{
		if(chosen_element == deck_position)
			al_draw_tinted_scaled_bitmap(battle_map->element_parchment,
				al_map_rgba_f(0.5, 0.5, 0.5, 0.5), 0, 0,
				al_get_bitmap_width(battle_map->element_parchment), al_get_bitmap_height(battle_map->element_parchment),
				deck_position_coordinates[deck_position][0], 
				deck_position_coordinates[deck_position][1],
				160, 110, 0);
		else
			al_draw_scaled_bitmap(battle_map->element_parchment, 0, 0,
				al_get_bitmap_width(battle_map->element_parchment), al_get_bitmap_height(battle_map->element_parchment),
				deck_position_coordinates[deck_position][0],
				deck_position_coordinates[deck_position][1],
				160, 110, 0);
	}
}

BATTLE_MAP* initBattleMap(char battle_background[], char footer_background[],
	char entity_shadow[], char element_parchment[], char mix_parchment[])
{
	BATTLE_MAP* battle_map = malloc(sizeof(BATTLE_MAP));
	battle_map->battle_background = initScenarioImage(battle_background);
	battle_map->footer_background = initScenarioImage(footer_background);
	battle_map->entity_shadow = initScenarioImage(entity_shadow);
	battle_map->element_parchment = initScenarioImage(element_parchment);
	battle_map->mix_parchment = initScenarioImage(mix_parchment);
	battle_map->destroyBattleMap = destroyBattleMap;
	battle_map->drawBattleMap = drawBattleMap;
	return battle_map;
}
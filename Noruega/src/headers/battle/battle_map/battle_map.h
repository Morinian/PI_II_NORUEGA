#ifndef BATTLE_MAP_H
	#define BATTLE_MAP_H

	typedef struct BATTLE_MAP BATTLE_MAP;

	struct BATTLE_MAP
	{
		ALLEGRO_BITMAP* battle_background;
		ALLEGRO_BITMAP* footer_background;
		ALLEGRO_BITMAP* entity_shadow;
		//Background das poções
		ALLEGRO_BITMAP* element_parchment;
		//Background do texto que mostra o efeito da mistura dos elementos
		ALLEGRO_BITMAP* mix_parchment;
			//-- Funções -- //
		void (*drawBattleMap)(BATTLE_MAP *, int, int, int);
		void (*destroyBattleMap)(BATTLE_MAP*);
	};

	BATTLE_MAP* initBattleMap(char battle_background[], char footer_background[], 
		char entity_shadow[], char element_parchment[], char mix_parchment[]);

#endif // !BATTLE_MAP_H


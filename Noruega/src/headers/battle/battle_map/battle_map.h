#ifndef BATTLE_MAP_H
	#define BATTLE_MAP_H

	typedef struct BATTLE_MAP BATTLE_MAP;

	struct BATTLE_MAP
	{
		ALLEGRO_BITMAP* cardLife;
		ALLEGRO_BITMAP* evilStatus;
		ALLEGRO_BITMAP* angelStatus;
		//Icones do tipo das bruxas
		ALLEGRO_BITMAP* fire_icon;
		ALLEGRO_BITMAP* water_icon;
		ALLEGRO_BITMAP* ground_icon;
		ALLEGRO_BITMAP* battle_background;
		ALLEGRO_BITMAP* footer_background;
		ALLEGRO_BITMAP* entity_shadow;
		//Background das po��es
		ALLEGRO_BITMAP* element_parchment;
		//Background do texto que mostra o efeito da mistura dos elementos
		ALLEGRO_BITMAP* mix_parchment;
			//-- Fun��es -- //
		void (*drawBattleMap)(BATTLE_MAP *, float, float, int, ALLEGRO_FONT*);
		void (*destroyBattleMap)(BATTLE_MAP*);
		void (*renderStatus)(BATTLE_MAP*, float, int, int, int);
	};

	BATTLE_MAP* initBattleMap(char battle_background[], char footer_background[], 
		char entity_shadow[], char element_parchment[], char mix_parchment[]);

#endif // !BATTLE_MAP_H


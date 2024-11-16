#ifndef BATTLE_H
	#define BATTLE_H

	typedef struct BATTLE_PVE BATTLE_PVE;

	struct BATTLE_PVE
	{
		// Round está declaro na struct pois será utilizado posteriormente para o Score (ideia de replay)
		int round;
		BATTLE_MAP* battle_map;
		WITCH* player;
		WITCH* bot;
		// --- funções ---//
		void (*destroyBattle)(BATTLE_PVE*);
		void (*play)(ALLEGRO_EVENT_QUEUE*, BATTLE_PVE*, ALLEGRO_FONT*, ELEMENTO*);
	};

	BATTLE_PVE* initBattlePVE(WITCH* player, WITCH* bot, BATTLE_MAP* battle_map);
#endif // !BATTLE_H


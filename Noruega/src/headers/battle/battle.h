#ifndef BATTLE_H
	#define BATTLE_H
	
	typedef struct BATTLE_PVE BATTLE_PVE;

	struct BATTLE_PVE
	{
		// Round est� declaro na struct pois ser� utilizado posteriormente para o Score (ideia de replay)
		int round;
		WITCH* player;
		WITCH* bot;
		// --- fun��es ---//
		void (*renderBattle)(BATTLE_PVE*);
		void (*destroyBattle)(BATTLE_PVE*);
		void (*play)(BATTLE_PVE*);
	};

	BATTLE_PVE* initBattlePVE(WITCH* player, WITCH bot);
#endif // !BATTLE_H


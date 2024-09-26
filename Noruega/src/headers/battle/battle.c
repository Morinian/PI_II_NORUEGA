#include <stdlib.h>
#include "../witch/witch.h"
#include "../battle/battle.h"

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
}
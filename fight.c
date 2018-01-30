#include "header.h"
/*
 calcul des dmg:

 int dmg = dmg_base;
    while (hero->premier->suivant != NULL)
    {
        dmg += hero->premier->damage_base;
        hero->premier = hero->premier->suivant;
    }
 */
Fight * create_fight(Monster *monster)
{
    Fight *fight;
    fight = malloc(sizeof(Fight));

    if(fight == NULL || monster->suivant == NULL)
        exit(EXIT_FAILURE);
    fight->monster = monster;
    fight->dmgDone = 0;
    return fight;
}

int calc_dmg_sec(Liste_Hero * heroes){
	int dmg = 0;
    while (heroes->premier->suivant != NULL)
    {
        dmg += heroes->premier->damage_base;
        heroes->premier = heroes->premier->suivant;
    }
    return dmg;
}

int calc_dmg_click(Fight *fight, User *user){
	if(fight){
		fight->dmgDone += user->dmg_base;
		fprintf(stderr, "damage = %d \/ %d \n", fight->dmgDone, fight->monster->life);
		if(fight->dmgDone >= fight->monster->life)
			return nextFight(fight, user);
		else
			return 1;
	}else{
		return 0;
	}
}

int calc_dmg(Fight *fight, int dmg, User *user)
{
	fight->dmgDone += dmg;

	fprintf(stderr, "damage %s = %d \/ %d \n", fight->monster->monster_name, fight->dmgDone, fight->monster->life);

	if(fight->dmgDone >= fight->monster->life)
		return nextFight(fight, user);
	else
		return 1;
    return 0;
}

int nextFight(Fight *fight, User *user)
{
    if(fight != NULL)
    {
    	int code_return = 0;
        fight->dmgDone = 0;

        user->money += fight->monster->money_drop;
        user->xp += fight->monster->experience_drop;

        if(fight->monster->suivant->suivant != NULL){
			fight->monster = fight->monster->suivant;
			fprintf(stderr, "Passage monstre suivant %s \n", fight->monster->monster_name);
        }else{
			user->current_round++;
			code_return = 2;
			fprintf(stderr, "Passage round suivant %d \n", user->current_round);
        }

        if(user->xp >=100)
        {
            user->xp = 0;
            user->current_level = user->current_level + 1 ;
            user->dmg_base = user->dmg_base + user->dmg_ratio;
        }

        return code_return;
    }

}

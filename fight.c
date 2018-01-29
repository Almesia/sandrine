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
Fight * create_fight(Liste_Monster *monster)
{
    Fight *fight;
    fight = malloc(sizeof(Fight));

    if(fight == NULL)
        exit(EXIT_FAILURE);
    fight->monster = monster;
    fight->dmgDone = 0;
    return fight;
}

int calc_dmg_sec(User * user, Liste_Hero * heroes){
	int dmg = user->dmg_base;
    while (heroes->premier->suivant != NULL)
    {
        dmg += heroes->premier->damage_base;
        heroes->premier = heroes->premier->suivant;
    }
    return dmg;
}

int calc_dmg(Fight *fight, int dmg, User *user)
{
    if(fight != NULL)
    {
        fight->dmgDone += dmg;

        fprintf(stderr, "damage = %d", fight->dmgDone);

        if(fight->dmgDone >= fight->monster->life)
            return nextFight(fight, user);
        else
            return 1;
    }
    return 0;
}

int nextFight(Fight *fight, User *user)
{
    if(fight != NULL)
    {
    	int code_return = 0;
        fight->dmgDone = 0;
        int xp, money;
        xp = fight->monster->experience_drop;
        money = fight->monster->money_drop;
        if(fight->monster->suivant != NULL){
			fight->monster = fight->monster->suivant;
			fprintf(stderr, "Passage monstre suivant %s \n", fight->monster->monster_name);
        }
        else{
			user->current_round += 1;
			code_return = 2;
			fprintf(stderr, "Passage round suivant %d \n", user->current_round);
        }
        user->money += money;
        user->xp += xp;
        if(user->xp >=100)
        {
            user->xp = 0;
            user->current_level = user->current_level + 1 ;
            user->dmg_base = user->dmg_base + user->dmg_ratio;
        }
        return code_return;
    }

}

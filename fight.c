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
fight * create_fight(Liste_Monster *monster)
{
    fight *fight;
    fight = malloc(sizeof(fight));

    if(fight == NULL)
        exit(EXIT_FAILURE);
    fight->monster = monster;
    fight->dmgDone = 0;
    printf("fight cree");
    return fight;
}

int calc_dmg(fight *fight, int dmg, User *user)
{
    if(fight != NULL)
    {
        fight->dmgDone += dmg;

        if(fight->dmgDone >= fight->monster->life)
            nextFight(fight, user);
        else
            return 1;
    }
    return 0;
}

int nextFight(fight *fight, User *user)
{
    if(fight != NULL)
    {
        fight->dmgDone = 0;
        int xp, money;
        xp = fight->monster->experience_drop;
        money = fight->monster->money_drop;
        if(fight->monster->suivant != NULL)
			fight->monster = fight->monster->suivant;
        else
            printf("end of fight");
        user->money += money;
        user->xp += xp;
        if(user->xp >=100)
        {
            user->xp = 0;
            user->current_level = user->current_level + 1 ;
            user->dmg_base = user->dmg_base + user->dmg_ratio;
        }

    }

}

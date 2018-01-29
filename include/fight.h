//
// Created by Basile on 28/01/2018.
//
typedef struct fight
{
    Monster *monster;
    int dmgDone;

}fight;

fight * create_fight(Liste_Monster *monster);
int calc_dmg(fight *fight, int dmg, User *user);
int nextFight(fight *fight, User *user);

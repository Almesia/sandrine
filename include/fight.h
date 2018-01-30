//
// Created by Basile on 28/01/2018.
//
typedef struct Fight
{
    Monster *monster;
    int dmgDone;

}Fight;

Fight * create_fight(Monster *monster);
int calc_dmg_sec(Liste_Hero * heroes);
int calc_dmg_click(Fight *fight, User *user);
int calc_dmg(Fight *fight, int dmg, User *user);
int nextFight(Fight *fight, User *user);

//
// Created by Basile on 28/01/2018.
//

#include "header.h"

int buy(sqlite3 * db, User *user, Hero *hero)
{
    if(user->money >= hero->money_cost)
    {
        add_heroes_to_user(db,hero->hero_id,user->user_id);
        return 1;
    }
    return 0;
}


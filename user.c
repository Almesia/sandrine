#include <stdio.h>
#include <stdlib.h>

#include "user.h"

User *initialisation_user(User * user, int id, char name[100], int level, int money, int xp, int dmg_base, double dmg_ratio)
{
    if (user == NULL)
    {
        exit(EXIT_FAILURE);
    }

    user->user_id = id;
    user->user_name = name;
    user->current_level = level;
    user->money = money;
    user->xp = xp;
    user->dmg_base = dmg_base;
    user->dmg_ratio = dmg_ratio;

    return user;
}

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

int export_user(User * user, char * file_name){
    FILE * file = fopen(file_name, "wb");
    if(!file)
        return 0;
	fwrite(&user, sizeof(User), 1, file);
	fclose(file);
	return 1;
}

int import_user(User * user, char * file_name){
	FILE * file = fopen(file_name, "rb");
    if(!file)
        return 0;
	if(fread(&user, sizeof(User), 1, file) > 0){
		fclose(file);
		return 1;
	}else{
		return -1;
	}
}

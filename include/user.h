typedef struct User{
	int user_id;
	int current_round;
	char * user_name;
	int current_level;
	int money;
	int xp;
	int dmg_base;
	double dmg_ratio;
} User;

User *initialisation_user(User * user, int id, char * name, int level, int money, int xp, int dmg_base, double dmg_ratio);
int export_user(User * user, char * file_name);
int import_user(User * user, char * file_name);

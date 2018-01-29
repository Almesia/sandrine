typedef struct Hero{
	int hero_id;
	char * hero_name;
	int level_max;
	int current_level;
	int damage_base;
	double damage_ratio;
	int money_cost;
	char * img_link;
	int pos_x;
	int pos_y;
	int red;
	int green;
	int blue;
	struct Hero *suivant;
} Hero;

typedef struct Liste_Hero{
    Hero *premier;
} Liste_Hero;

Liste_Hero *initialisation_hero();
void insertion_hero(Liste_Hero *liste, int hero_id, char* hero_name, int level_max, int current_level, int damage_base, double damage_ratio, int money_cost, char * img_link, int pos_x, int pos_y, int red, int green, int blue);
void suppression_hero(Liste_Hero *liste);
void afficherListe_hero(Liste_Hero *liste);

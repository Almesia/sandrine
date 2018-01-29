typedef struct Monster{
	int monster_id;
	char * monster_name;
	int life;
	int money_drop;
	int experience_drop;
	char * img_link;
	int pos_x;
	int pos_y;
	int red;
	int green;
	int blue;
	struct Monster *suivant;
} Monster;

typedef struct Liste_Monster {
    Monster *premier;
} Liste_Monster;

Liste_Monster *initialisation_monster();
void insertion_monster(Liste_Monster *liste, int monster_id, char* monster_name, int life, int money_drop, int experience_drop, char * img_link, int pos_x, int pos_y, int red, int green, int blue);
void suppression_monster(Liste_Monster *liste);
void afficherListe_monster(Liste_Monster *liste);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monster.h"

/* FUNCTION TO INITIALISE LIST */

Liste_Monster *initialisation_monster()
{
    Liste_Monster *liste = malloc(sizeof(Liste_Monster));
    Monster *element = malloc(sizeof(Monster));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->monster_id = 0;
    element->monster_name = NULL;
    element->life = 0;
    element->money_drop = 0;
    element->experience_drop = 0;
	element->img_link = NULL;
    element->pos_x = 0;
    element->pos_y = 0;
    element->red = 0;
    element->green = 0;
    element->blue = 0;
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}

/* FUNCTION TO INSERT INTO LIST */

void insertion_monster(Liste_Monster *liste, int monster_id, char* monster_name, int life, int money_drop, int experience_drop, char * img_link, int pos_x, int pos_y, int red, int green, int blue)
{
    /* Création du nouvel élément */
    Monster *nouveau = malloc(sizeof(Monster));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->monster_id = monster_id;
    nouveau->monster_name = malloc(sizeof(char)*strlen(monster_name)+1);
    strcpy(nouveau->monster_name, monster_name);
    nouveau->life = life;
    nouveau->money_drop = money_drop;
    nouveau->experience_drop = experience_drop;
    nouveau->img_link = malloc(sizeof(char)*strlen(img_link)+1);
    strcpy(nouveau->img_link, img_link);
    nouveau->pos_x = pos_x;
    nouveau->pos_y = pos_y;
    nouveau->red = red;
    nouveau->green = green;
    nouveau->blue = blue;
    nouveau->suivant = NULL;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

/* FUNCTION TO DELETE LAST INSERT */

void suppression_monster(Liste_Monster *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL)
    {
        Monster *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

/* FUNCTION TO SHOW ALL THE LIST */

void afficherListe_monster(Liste_Monster *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Monster *actuel = liste->premier;

    while (actuel != NULL)
    {
        fprintf(stdout, "%d : %s : %d : %d : %d : %s : %d -> \n", actuel->monster_id, actuel->monster_name, actuel->life, actuel->money_drop, actuel->experience_drop, actuel->img_link, actuel->monster_id);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}


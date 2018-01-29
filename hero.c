#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hero.h"

/* FUNCTION TO INITIALISE LIST */

Liste_Hero *initialisation_hero()
{
    Liste_Hero *liste = malloc(sizeof(Liste_Hero));
    Hero *element = malloc(sizeof(Hero));

    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->hero_id = 0;
    element->hero_name = NULL;
    element->level_max = 0;
    element->current_level = 0;
    element->damage_base = 0;
    element->damage_ratio = 0;
    element->money_cost = 0;
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

void insertion_hero(Liste_Hero *liste, int hero_id, char* hero_name, int level_max, int current_level, int damage_base, double damage_ratio, int money_cost, char * img_link, int pos_x, int pos_y, int red, int green, int blue)
{
    /* Création du nouvel élément */
    Hero *nouveau = malloc(sizeof(Hero));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->hero_id = hero_id;
    nouveau->hero_name = malloc(sizeof(char)*strlen(hero_name)+1);
    strcpy(nouveau->hero_name, hero_name);
    nouveau->level_max = level_max;
    nouveau->current_level = current_level;
    nouveau->damage_base = damage_base;
    nouveau->damage_ratio = damage_ratio;
    nouveau->money_cost = money_cost;
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

void suppression_hero(Liste_Hero *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (liste->premier != NULL)
    {
        Liste_Hero *aSupprimer = liste->premier;
        liste->premier = liste->premier->suivant;
        free(aSupprimer);
    }
}

/* FUNCTION TO SHOW ALL THE LIST */

void afficherListe_hero(Liste_Hero *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Hero *actuel = liste->premier;

    while (actuel != NULL)
    {
        fprintf(stdout, "%d : %s : %d : %d : %d : %lf : %d : %s -> \n", actuel->hero_id, actuel->hero_name, actuel->level_max, actuel->current_level, actuel->damage_base, actuel->damage_ratio, actuel->money_cost, actuel->img_link);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}



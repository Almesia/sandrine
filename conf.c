//
// Created by Basile on 29/01/2018.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "conf.h"

Conf *intializeConf()
{
	int i;
    Conf *conf;
    conf = malloc(sizeof(Conf));

    FILE *file;
    file = fopen("config.conf", "r");

    char *param;
    param = malloc(sizeof(char)*255);

    fflush(stdin);
    fgets(param, 255, file);
    conf->language = malloc(sizeof(char)*strlen(param));
    strcpy(conf->language, param+8);
    conf->language[strlen(param)-9] = '\0';

    fflush(stdin);
    fgets(param, 255, file);
    conf->bdd = malloc(sizeof(char)*strlen(param));
    strcpy(conf->bdd, param+5);
    conf->bdd[strlen(param)-6] = '\0';

    fflush(stdin);
    fgets(param, 255, file);
    conf->sound = malloc(sizeof(char)*strlen(param));
    strcpy(conf->sound, param+7);
    conf->sound[strlen(param)-7] = '\0';

    fclose(file);
    free(param);
    return conf;
}

Conf *updateConf(Conf *conf, int param, char *value)
{
    switch (param)
    {
        case 0:
            strcpy(conf->language, value);
            break;
        case 1:
            strcpy(conf->bdd, value);
            break;
        case 2:
            strcpy(conf->sound, value);
            break;
        default:
            return conf;
    }
    FILE * file;
    file = fopen("config.conf", "w+");
    fprintf(file,"langue: %s\n", conf->language);
    fprintf(file,"bdd: %s\n", conf->bdd);
    fprintf(file,"sound: %s\n", conf->sound);
    fclose(file);

    return conf;
}

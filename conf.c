//
// Created by Basile on 29/01/2018.
//

#include "conf.h"

conf *intializeConf()
{
    conf *conf;
    conf = malloc(sizeof(conf));
    conf->language = malloc(sizeof(char)*25);
    conf->bdd = malloc(sizeof(char)*25);
    conf->sound = malloc(sizeof(char)*25);
    FILE *file;
    file = fopen("config.conf", "r");

    char *param;
    param = malloc(sizeof(char)*255);
    fgets(param,255,file);

    for (int i = 7; i < strlen(param); ++i)
        strcat(conf->language, param+i);

    free(param);
    param = malloc(sizeof(char)*255);
    fgets(param,255,file);

    for (int i = 4; i < strlen(param); ++i)
        strcat(conf->bdd, param+i);

    free(param);
    param = malloc(sizeof(char)*255);
    fgets(param,255,file);

    for (int i = 6; i < strlen(param); ++i)
        strcat(conf->bdd, param+i);

    fclose(file);
    free(param);
    return conf;
}

conf *updateConf(conf *conf, int param, char *value)
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
    FILE file;
    file = fopen("config.conf", "w+");
    fprintf(file,"langue: %s\n", conf->language);
    fprintf(file,"bdd: %s\n", conf->bdd);
    fprintf(file,"sound: %s\n", conf->sound);
    fclose(file);

    return conf;
}
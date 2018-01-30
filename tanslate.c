//
// Created by Basile on 30/01/2018.
//

#include "tanslate.h"

char *loadText(char *word, conf *conf) {
    FILE *file;
    char *name;

    name = malloc(sizeof(char) * 255);
    strcpy(name, conf->language);
    strcat(name, ".lang");

    file = fopen(name, "r");

    if (file != NULL) {
        char *line;
        fgets(line, 255, file);
        while (strstr(line, word) == NULL && line != NULL)
            fgets(line, 255, file);

        int pass;
        pass = strlen(word) + 2;

        char *text;
        text = malloc(sizeof(char) * 255);
        strcpy(text, line + pass);

        free(name);
        free(line);
        fclose(file);


        return text;
    }


    free(name);
    fclose(file);
    return NULL;

}

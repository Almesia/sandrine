//
// Created by Basile on 29/01/2018.
//

#ifndef ESGI_TEST_CONF_H
#define ESGI_TEST_CONF_H

#endif //ESGI_TEST_CONF_H
 typedef struct conf
 {
     char *language;
     char *bdd;
     char *sound;
 }conf;

conf *intializeConf();
conf *updateConf(conf *conf, int param, char *value);
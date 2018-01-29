typedef struct Conf
 {
     char *language;
     char *bdd;
     char *sound;
 }Conf;

Conf *intializeConf();
Conf *updateConf(Conf *conf, int param, char *value);

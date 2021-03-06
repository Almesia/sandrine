#include "header.h"

int main(int argc, char *argv[]){

    Conf *conf;
    conf = intializeConf();

	sqlite3 * db;
    db = init_database(db, conf->bdd);

    User * user = select_user(db, "remi");

    Liste_Monster * monsters = initialisation_monster();
    monsters = select_monster_current_level(db, user->current_round);

    afficherListe_monster(monsters);

    Liste_Hero* heroes = select_heroes_user(db, user->user_id);

    int dmg = calc_dmg_sec(heroes);

	Liste_Hero* heroes_all = select_heroes(db);

	Fight * fight = create_fight(monsters->premier);

    //sdl
    int continuer = 1, herosx, herosy, nb;
    unsigned long int argent=0;
    char argents[255];
    char PvMonstreString[255];
    char heroInfo[255];
    SDL_Event event;
    SDL_Surface *ecran = NULL, *ui = NULL, *coin=NULL, *money=NULL, *cursor=NULL, *bam=NULL,*background=NULL, *infos=NULL, *infos2=NULL;
    SDL_Surface *heros1=NULL, *heros2=NULL, *heros3=NULL, *heros4=NULL, *heros5=NULL, *heros6=NULL, *heros7=NULL, *heros8=NULL;
    SDL_Surface *button1=NULL, *button2=NULL, *button3=NULL, *button4=NULL, *button5=NULL, *button6=NULL, *button7=NULL, *button8=NULL, *foe=NULL;
    SDL_Surface *pvmonstre=NULL;

    SDL_Surface *infoHero1_1=NULL;
    SDL_Surface *infoHero1_2=NULL;
    SDL_Surface *infoHero1_3=NULL;
    SDL_Surface *infoHero1_4=NULL;

    SDL_Surface *infoHero2_1=NULL;
    SDL_Surface *infoHero2_2=NULL;
    SDL_Surface *infoHero2_3=NULL;
    SDL_Surface *infoHero2_4=NULL;

    SDL_Surface *infoHero3_1=NULL;
    SDL_Surface *infoHero3_2=NULL;
    SDL_Surface *infoHero3_3=NULL;
    SDL_Surface *infoHero3_4=NULL;

    SDL_Surface *infoHero4_1=NULL;
    SDL_Surface *infoHero4_2=NULL;
    SDL_Surface *infoHero4_3=NULL;
    SDL_Surface *infoHero4_4=NULL;

    SDL_Surface *infoHero5_1=NULL;
    SDL_Surface *infoHero5_2=NULL;
    SDL_Surface *infoHero5_3=NULL;
    SDL_Surface *infoHero5_4=NULL;

    SDL_Surface *infoHero6_1=NULL;
    SDL_Surface *infoHero6_2=NULL;
    SDL_Surface *infoHero6_3=NULL;
    SDL_Surface *infoHero6_4=NULL;

    SDL_Surface *infoHero7_1=NULL;
    SDL_Surface *infoHero7_2=NULL;
    SDL_Surface *infoHero7_3=NULL;
    SDL_Surface *infoHero7_4=NULL;

    SDL_Surface *infoHero8_1=NULL;
    SDL_Surface *infoHero8_2=NULL;
    SDL_Surface *infoHero8_3=NULL;
    SDL_Surface *infoHero8_4=NULL;

    Mix_Music *bgm=NULL;
    TTF_Font *police = NULL,*police2 = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    time_t t;
    srand((unsigned) time(&t));

    if(SDL_Init(SDL_INIT_VIDEO) == -1){
        fprintf(stderr, "Erreur d'initialisation de SDL_Init : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1){
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
        //Initialisation de l'API Mixer
        fprintf(stderr, "Erreur d'initialisation de Mis_OpenAudio : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    /* On cr�e la fen�tre d'affichage */
    ecran = SDL_SetVideoMode(800, 450, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(ecran==NULL){
        fprintf(stderr, "Erreur d'initialisation de la fenetre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Esgi Clicker", NULL);

    police = TTF_OpenFont("font/font2.ttf", 22);
    police2 = TTF_OpenFont("font/font2.ttf", 10);
    herosx=35;
    herosy=120;

    ui=init_image("img/ui/back.bmp",0,0,0);
    infos=init_image("img/ui/infos.bmp",255,255,255);
    infos2=init_image("img/ui/infos2.bmp",255,255,255);
    background=init_image("img/cliff3.bmp",255,255,255);
    coin=init_image("img/ui/coin.bmp",255,255,255);
    cursor=init_image("img/ui/cursor.bmp",255,255,255);
    bam=init_image("img/ui/bam.bmp",255,255,255);

    heros1=init_image("img/heros/heros1.bmp",0,0,0);
    heros2=init_image("img/heros/heros2.bmp",0,0,0);
    heros3=init_image("img/heros/heros3.bmp",0,0,0);
    heros4=init_image("img/heros/heros4.bmp",0,0,0);
    heros5=init_image("img/heros/heros5.bmp",0,0,0);
    heros6=init_image("img/heros/heros6.bmp",0,0,0);
    heros7=init_image("img/heros/heros7.bmp",0,0,0);
    heros8=init_image("img/heros/heros8.bmp",0,0,0);

    button1=init_image("img/ui/button.bmp",255,255,255);
    button2=init_image("img/ui/button.bmp",255,255,255);
    button3=init_image("img/ui/button.bmp",255,255,255);
    button4=init_image("img/ui/button.bmp",255,255,255);
    button5=init_image("img/ui/button.bmp",255,255,255);
    button6=init_image("img/ui/button.bmp",255,255,255);
    button7=init_image("img/ui/button.bmp",255,255,255);
    button8=init_image("img/ui/button.bmp",255,255,255);

    foe=init_image("img/mob/mob1.bmp",255,255,255);
    SDL_SetAlpha(background, SDL_SRCALPHA, 175);

    Liste_Hero *temp;

    temp = malloc(sizeof(Liste_Hero));
    temp->premier = heroes_all->premier;

    //hero1
    sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero1_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero1_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero1_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero1_2,230,230);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero1_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero1_3,130,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero1_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero1_4,120,130);

	//temp->premier = temp->premier->suivant; //ca marche

	//hero2
	sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero2_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero2_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero2_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero2_2,120,120);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero2_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero2_3,120,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero2_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero2_4,120,120);

   //temp->premier = temp->premier->suivant; // ca marche plus

	//hero3
	sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero3_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero3_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero3_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero3_2,120,120);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero3_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero3_3,120,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero3_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero3_4,120,120);

    //temp->premier = temp->premier->suivant;

	//hero4
	sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero4_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero4_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero4_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero4_2,120,120);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero4_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero4_3,120,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero4_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero4_4,120,120);

    //temp->premier = temp->premier->suivant;

	//hero5
	sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero5_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero5_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero5_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero5_2,120,120);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero5_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero5_3,120,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero5_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero5_4,120,120);

    //temp->premier = temp->premier->suivant;

	//hero6
	sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero6_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero6_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero6_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero6_2,120,120);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero6_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero6_3,120,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero6_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero6_4,120,120);

    //temp->premier = temp->premier->suivant;

	//hero7
	sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero7_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero7_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero7_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero7_2,120,120);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero7_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero7_3,120,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero7_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero7_4,120,120);

    //temp->premier = temp->premier->suivant;

	//hero8
	sprintf(heroInfo,"%s",temp->premier->hero_name);
	infoHero8_1 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero8_1,120,120);

	sprintf(heroInfo,"%d",temp->premier->money_cost);
	infoHero8_2 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero8_2,120,120);

	sprintf(heroInfo,"%d",temp->premier->damage_base);
	infoHero8_3 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero8_3,120,120);

	sprintf(heroInfo,"%d",temp->premier->current_level);
	infoHero8_4 = TTF_RenderText_Blended(police2,heroInfo,couleurNoire);
	blit(ecran,infoHero8_4,120,120);

    bgm=Mix_LoadMUS("sound/bgm.mp3");
    Mix_PlayMusic(bgm,-1);

    SDL_ShowCursor(0);

    time_t start_t, end_t;
	double diff_t;

	time(&start_t);

    while (continuer){ /* TANT QUE la variable ne vaut pas 0*/

		time(&end_t);
		diff_t = difftime(end_t, start_t);
		if(diff_t >= 1){
			fprintf(stderr, "damage sec = %d", dmg);
			afficherListe_monster(monsters);
			time(&start_t);
			if(fight){
				if(calc_dmg(fight, dmg, user) == 2){
					update_user(db, user);
					free(monsters);
					monsters = select_monster_current_level(db, user->current_round);
					free(fight);
					fight = create_fight(monsters->premier);
				}
			}else{
				if(monsters->premier->suivant != NULL){
					free(monsters);
					monsters = select_monster_current_level(db, user->current_round);
					free(fight);
					fight = create_fight(monsters->premier);
				}
			}
		}

        SDL_PollEvent(&event); /* On attend un �v�nement qu'on r�cup�re dans event */

        switch(event.type){ /* On teste le type d'�v�nement */
            case SDL_QUIT: /* Si c'est un �v�nement QUITTER */
                continuer = 0; /* On met le bool�en � 0, donc la boucle va s'arr�ter */
                break;
        }

        if(event.button.button==SDL_BUTTON_LEFT && event.button.type==SDL_MOUSEBUTTONDOWN){
            event.button.button=0;
            if(event.button.x>550 && event.button.x<600 && event.button.y>175 && event.button.y<275){
				if(fight){
					if(calc_dmg_click(fight, user) == 2){
						update_user(db, user);
						free(monsters);
						monsters = select_monster_current_level(db, user->current_round);
						free(fight);
						fight = create_fight(monsters->premier);
					}
				}else{
					if(monsters->premier->suivant != NULL){
						free(monsters);
						monsters = select_monster_current_level(db, user->current_round);
						free(fight);
						fight = create_fight(monsters->premier);
					}
				}
                blit(ecran,cursor,event.button.x, event.button.y);
                blit(ecran,bam,event.button.x,event.button.y);

                SDL_Flip(ecran);
            }else if(event.button.x>30 && event.button.x<200 && event.button.y>120 && event.button.y<180){
                if(buy(db, user, select_hero_name(db, "heroes_1"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }else if(event.button.x>200 && event.button.x<350 && event.button.y>120 && event.button.y<180){
                if(buy(db, user, select_hero_name(db, "heroes_2"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }else if(event.button.x>30 && event.button.x<200 && event.button.y>190 && event.button.y<250){
                if(buy(db, user, select_hero_name(db, "heroes_3"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }else if(event.button.x>200 && event.button.x<350 && event.button.y>190 && event.button.y<250){
                if(buy(db, user, select_hero_name(db, "heroes_4"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }else if(event.button.x>30 && event.button.x<200 && event.button.y>265 && event.button.y<325){
                if(buy(db, user, select_hero_name(db, "heroes_5"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }else if(event.button.x>200 && event.button.x<350 && event.button.y>265 && event.button.y<325){
                if(buy(db, user, select_hero_name(db, "heroes_6"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }else if(event.button.x>30 && event.button.x<200 && event.button.y>340 && event.button.y<400){
                if(buy(db, user, select_hero_name(db, "heroes_7"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }else if(event.button.x>200 && event.button.x<350 && event.button.y>340 && event.button.y<400){
                if(buy(db, user, select_hero_name(db, "heroes_8"))){
					heroes = select_heroes_user(db, user->user_id);
					dmg = calc_dmg_sec(heroes);
                }
            }
        }
        if(SDL_MOUSEMOTION){
            blit(ecran,ui,0,0);
            blit(ecran,background,455,109);
            blit(ecran,infos,390,10);
            blit(ecran,infos2,390,315);
            blit(ecran,foe,550,175);
            blit(ecran,heros1,herosx,herosy);
            blit(ecran,heros2,herosx+165,herosy);
            blit(ecran,heros3,herosx,herosy+75);
            blit(ecran,heros4,herosx+165,herosy+75);
            blit(ecran,heros5,herosx,herosy+150);
            blit(ecran,heros6,herosx+165,herosy+150);
            blit(ecran,heros7,herosx,herosy+225);
            blit(ecran,heros8,herosx+165,herosy+225);

            blit(ecran,button1,herosx+65,herosy);
            blit(ecran,button2,herosx+225,herosy);
            blit(ecran,button3,herosx+65,herosy+75);
            blit(ecran,button4,herosx+225,herosy+75);
            blit(ecran,button5,herosx+65,herosy+150);
            blit(ecran,button6,herosx+225,herosy+150);
            blit(ecran,button7,herosx+65,herosy+225);
            blit(ecran,button8,herosx+225,herosy+225);

            blit(ecran,coin,50,50);
            blit(ecran,money,140,60);
            blit(ecran,cursor,event.button.x, event.button.y);

            blit(ecran,infoHero1_1,110,120);
            blit(ecran,infoHero1_2,110,150);
            blit(ecran,infoHero1_3,110,135);
            blit(ecran,infoHero1_4,170,150);

            blit(ecran,infoHero2_1,265,120);
            blit(ecran,infoHero2_2,265,150);
            blit(ecran,infoHero2_3,265,135);
            blit(ecran,infoHero2_4,325,150);

            blit(ecran,infoHero3_1,110,195);
            blit(ecran,infoHero3_2,110,225);
            blit(ecran,infoHero3_3,110,210);
            blit(ecran,infoHero3_4,110,225);

            blit(ecran,infoHero4_1,265,195);
            blit(ecran,infoHero4_2,265,225);
            blit(ecran,infoHero4_3,265,210);
            blit(ecran,infoHero4_4,325,225);

            blit(ecran,infoHero5_1,110,270);
            blit(ecran,infoHero5_2,110,300);
            blit(ecran,infoHero5_3,110,285);
            blit(ecran,infoHero5_4,110,300);

            blit(ecran,infoHero6_1,265,270);
            blit(ecran,infoHero6_2,265,300);
            blit(ecran,infoHero6_3,265,285);
            blit(ecran,infoHero6_4,325,300);

            blit(ecran,infoHero7_1,110,345);
            blit(ecran,infoHero7_2,110,375);
            blit(ecran,infoHero7_3,110,360);
            blit(ecran,infoHero7_4,110,375);

            blit(ecran,infoHero8_1,265,345);
            blit(ecran,infoHero8_2,265,375);
            blit(ecran,infoHero8_3,265,360);
            blit(ecran,infoHero8_4,325,375);

            SDL_Flip(ecran);
        }

		sprintf(PvMonstreString,"%d",fight->monster->life-fight->dmgDone);
		SDL_FreeSurface(pvmonstre);
		pvmonstre = TTF_RenderText_Blended(police,PvMonstreString,couleurNoire);
		blit(ecran,pvmonstre,555,340);
		SDL_Flip(ecran);

        argent=user->money;
        sprintf(argents,"%d",argent);
        SDL_FreeSurface(money);
        money = TTF_RenderText_Blended(police,argents, couleurNoire);
        blit(ecran,money,140,60);
        blit(ecran,cursor,event.button.x, event.button.y);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(coin);
    SDL_FreeSurface(bam);
    SDL_FreeSurface(heros1);
    SDL_FreeSurface(heros2);
    SDL_FreeSurface(heros3);
    SDL_FreeSurface(heros4);
    SDL_FreeSurface(heros5);
    SDL_FreeSurface(heros6);
    SDL_FreeSurface(cursor);

    SDL_FreeSurface(infoHero1_1);
    SDL_FreeSurface(infoHero1_2);
    SDL_FreeSurface(infoHero1_3);
    SDL_FreeSurface(infoHero1_4);

    SDL_FreeSurface(infoHero2_1);
    SDL_FreeSurface(infoHero2_2);
    SDL_FreeSurface(infoHero2_3);
    SDL_FreeSurface(infoHero2_4);

    SDL_FreeSurface(infoHero3_1);
    SDL_FreeSurface(infoHero3_2);
    SDL_FreeSurface(infoHero3_3);
    SDL_FreeSurface(infoHero3_4);

    SDL_FreeSurface(infoHero4_1);
    SDL_FreeSurface(infoHero4_2);
    SDL_FreeSurface(infoHero4_3);
    SDL_FreeSurface(infoHero4_4);

    SDL_FreeSurface(infoHero5_1);
    SDL_FreeSurface(infoHero5_2);
    SDL_FreeSurface(infoHero5_3);
    SDL_FreeSurface(infoHero5_4);

    SDL_FreeSurface(infoHero6_1);
    SDL_FreeSurface(infoHero6_2);
    SDL_FreeSurface(infoHero6_3);
    SDL_FreeSurface(infoHero6_4);

    SDL_FreeSurface(infoHero7_1);
    SDL_FreeSurface(infoHero7_2);
    SDL_FreeSurface(infoHero7_3);
    SDL_FreeSurface(infoHero7_4);

    SDL_FreeSurface(infoHero8_1);
    SDL_FreeSurface(infoHero8_2);
    SDL_FreeSurface(infoHero8_3);
    SDL_FreeSurface(infoHero8_4);

    SDL_FreeSurface(foe);
    SDL_FreeSurface(infos);
    SDL_FreeSurface(pvmonstre);
    SDL_FreeSurface(money);
    SDL_FreeSurface(ui); /* On libere la surface */
    SDL_FreeSurface(ecran);
    TTF_CloseFont(police);
    TTF_CloseFont(police2);
    Mix_FreeMusic(bgm);

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}


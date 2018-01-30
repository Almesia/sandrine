#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>

#include "header.h"

sqlite3* init_database(sqlite3 *db, char * name_db){
	int already_exist = 0;
	if(access( name_db, F_OK ) != -1){
		already_exist = 1;
	}
	db = open_database(db, name_db);
	if (db != NULL && !already_exist)
	{
		if(!create_tables(db, "sql/createTables.sql")){
			return NULL;
		}
		if(!insert_content_tables(db, "sql/insertTables.sql")){
			return NULL;
		}
	}else{
		if(already_exist)
			return db;
		return NULL;
	}
	return db;
}


sqlite3* open_database(sqlite3 *db, char * name_db){
	int rc = sqlite3_open(name_db, &db);

	if ( rc ) {
		if(DEBUG)
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return NULL;
	}
	else{
		if(DEBUG)
			fprintf(stdout, "Opened database successfully\n");
	}
	return db;
}


void close_database(sqlite3 *db){
	if (db != NULL)
	{
		sqlite3_close(db);
	}
}


int exec_sql_stmt(sqlite3 *db, char * line){
    if(line != NULL && db != NULL){
		char *errmsg = "";
        if(sqlite3_exec(db, line, 0, 0, &errmsg) != SQLITE_OK){
        	if(DEBUG)
				fprintf(stderr, "SQL statement : %s error: %s\n", line, errmsg);
			sqlite3_free(errmsg);
			return 0;
        }else{
        	if(DEBUG)
				fprintf(stdout, "SQL statement : %s done successfully\n", line);
			return 1;
        }
    }
    return 0;
}


int read_file_to_exec(sqlite3* db, char * file_name){
	FILE *file = fopen(file_name, "r");
	if(file){
		char line[2048];
		while(fgets(line, 2048, file)){
			if (!exec_sql_stmt(db, line))
			{
				fclose(file);
				return 0;
			};
		}
		fclose(file);
	}else{
		if(DEBUG)
			fprintf(stderr, "SQL file : %s doesn't exist\n", file_name);
		free(file);
		return 0;
	}
	return 1;
}


int create_tables(sqlite3* db, char * file_name){
	if(read_file_to_exec(db, file_name)){
		return 1;
	}
	return 0;
}


int insert_content_tables(sqlite3* db, char * file_name){
	if(read_file_to_exec(db, file_name)){
		return 1;
	}
	return 0;
}

User * select_user(sqlite3* db, char * user_name){
	User * user;
	user = malloc(sizeof(User));
	sqlite3_stmt *res;
	char * sql = "SELECT * FROM user WHERE user_name = ? LIMIT 1;";
	int rc;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return NULL;
	}

	rc = sqlite3_bind_text(res, 1, user_name, -1, NULL);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on bind : %s on %s", user_name, sql);
		return NULL;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE) {
			user->user_id=sqlite3_column_int(res, 0);
			user->current_round=sqlite3_column_int(res, 1);

			user->user_name = malloc(sizeof(char)*strlen(sqlite3_column_text(res, 2))+1);
			strcpy(user->user_name, sqlite3_column_text(res, 2));

			user->current_level=sqlite3_column_int(res, 3);
			user->money=sqlite3_column_int(res, 4);
			user->xp=sqlite3_column_int(res, 5);
			user->dmg_base=sqlite3_column_int(res, 6);
			user->dmg_ratio=sqlite3_column_double(res, 7);
		}
	}

	sqlite3_finalize(res);
	free(user_name);
	free(sql);
	return user;
}

Liste_Hero* select_heroes_user(sqlite3* db, int user_id){
	Liste_Hero * heroes = initialisation_hero();
	sqlite3_stmt *res;
	char * sql = "SELECT * FROM hero WHERE hero_id IN (SELECT hero_id FROM possesses WHERE user_id = ?) ORDER BY hero_id DESC;";
	int rc;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return NULL;
	}

	rc = sqlite3_bind_int(res, 1, user_id);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on bind : %d on %s", user_id, sql);
		return NULL;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE) {
			insertion_hero(
				heroes,
				sqlite3_column_int(res, 0),
				sqlite3_column_text(res, 1),
				sqlite3_column_int(res, 2),
				sqlite3_column_int(res, 3),
				sqlite3_column_int(res, 4),
				sqlite3_column_double(res, 5),
				sqlite3_column_int(res, 6),
				sqlite3_column_text(res, 7),
				sqlite3_column_int(res, 8),
				sqlite3_column_int(res, 9),
				sqlite3_column_int(res, 10),
				sqlite3_column_int(res, 11),
				sqlite3_column_int(res, 12)
			);
		}
	}

	sqlite3_finalize(res);
	free(sql);
	return heroes;
}

Liste_Hero* select_heroes(sqlite3* db){
	Liste_Hero * heroes = initialisation_hero();
	sqlite3_stmt *res;
	char * sql = "SELECT * FROM hero ORDER BY hero_id DESC;";
	int rc;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return NULL;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE) {
			insertion_hero(
				heroes,
				sqlite3_column_int(res, 0),
				sqlite3_column_text(res, 1),
				sqlite3_column_int(res, 2),
				sqlite3_column_int(res, 3),
				sqlite3_column_int(res, 4),
				sqlite3_column_double(res, 5),
				sqlite3_column_int(res, 6),
				sqlite3_column_text(res, 7),
				sqlite3_column_int(res, 8),
				sqlite3_column_int(res, 9),
				sqlite3_column_int(res, 10),
				sqlite3_column_int(res, 11),
				sqlite3_column_int(res, 12)
			);
		}
	}

	sqlite3_finalize(res);
	free(sql);
	return heroes;
}

int add_heroes_to_user(sqlite3* db, int hero_id, int user_id){
	sqlite3_stmt *res;
	char * sql = "INSERT OR IGNORE INTO possesses(user_id, hero_id) VALUES ( ? , ? );";
	int rc = 0;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return 0;
	}

	rc += sqlite3_bind_int(res, 1, user_id);
	rc += sqlite3_bind_int(res, 2, hero_id);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on bind : on %s", sql);
		return NULL;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE){
		};
	}

	sqlite3_finalize(res);
	free(sql);
	return 1;
}

Liste_Monster * select_monster_current_level(sqlite3 *db, int level){
	Liste_Monster * monsters = initialisation_monster();
	sqlite3_stmt *res;
	char * sql = "SELECT * FROM monster WHERE monster_id IN (SELECT monster_id FROM belongs WHERE round_id = ?) AND boss != 1 ORDER BY monster_id DESC;";
    int rc;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return NULL;
	}

	rc = sqlite3_bind_int(res, 1, level%3);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on bind : %d on %s", level, sql);
		return NULL;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE) {
            insertion_monster(
				monsters,
				sqlite3_column_int(res, 0),
				sqlite3_column_text(res, 1),
				sqlite3_column_int(res, 2) * (level+1),
				sqlite3_column_int(res, 3) * (0.5 * level + 1),
				sqlite3_column_int(res, 4) * (0.5 * level + 1),
				sqlite3_column_text(res, 6),
				sqlite3_column_int(res, 7),
				sqlite3_column_int(res, 8),
				sqlite3_column_int(res, 9),
				sqlite3_column_int(res, 10),
				sqlite3_column_int(res, 11)
			);
		}
	}

	sqlite3_finalize(res);
	free(sql);
	return monsters;
}

int update_user(sqlite3 * db, User *user){
	sqlite3_stmt *res;
	time_t timer;
    char * buffer = malloc(sizeof(char)*26);
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

	char * sql = "UPDATE user SET round_id = ? , user_name = ? , current_level = ? , money = ? , xp = ? , dmg_base = ? , dmg_ratio = ? , last_connection = ? WHERE user_id = ? ;";
    int rc = 0;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return 0;
	}

	rc += sqlite3_bind_int(res, 1, user->current_round);
	rc += sqlite3_bind_text(res, 2, user->user_name, -1, NULL);
	rc += sqlite3_bind_int(res, 3, user->current_level);
	rc += sqlite3_bind_int(res, 4, user->money);
	rc += sqlite3_bind_int(res, 5, user->xp);
	rc += sqlite3_bind_int(res, 6, user->dmg_base);
	rc += sqlite3_bind_int(res, 7, user->dmg_ratio);
	rc += sqlite3_bind_text(res, 8, buffer, -1, NULL);
	rc += sqlite3_bind_int(res, 9, user->user_id);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on update user bind : %s", sql);
		return 0;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE) {
		}
	}

	sqlite3_finalize(res);
	free(buffer);
	free(tm_info);
	free(sql);
	return 1;
}

int update_hero(sqlite3 * db, Hero *hero){
	sqlite3_stmt *res;

	char * sql = "UPDATE hero SET current_level = ? , damage_base = ? , damage_ratio = ? , money_cost = ? WHERE hero_id = ? ;";
    int rc = 0;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return 0;
	}

	rc += sqlite3_bind_int(res, 1, hero->current_level);
	rc += sqlite3_bind_int(res, 1, hero->damage_base);
	rc += sqlite3_bind_double(res, 1, hero->damage_ratio);
	rc += sqlite3_bind_int(res, 1, hero->money_cost);
	rc += sqlite3_bind_int(res, 1, hero->hero_id);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on update user bind : %s", sql);
		return 0;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE) {
		}
	}

	sqlite3_finalize(res);
	free(sql);
	return 1;
}

Image * select_img_round(sqlite3* db, int round_id){
	Image * img = malloc(sizeof(img));
	sqlite3_stmt *res;
	char * sql = "SELECT * FROM round WHERE round_id = ? LIMIT 1;";
	int rc;

	rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on prepare : %s", sql);
		return NULL;
	}

	rc = sqlite3_bind_int(res, 1, round_id);

	if(rc != SQLITE_OK){
		fprintf(stderr, "Error on bind : %d on %s", round_id, sql);
		return NULL;
	}

	if(res != NULL){
		while (sqlite3_step(res) != SQLITE_DONE) {
			img->img_link = malloc(sizeof(char)*strlen(sqlite3_column_text(res, 2))+1);
			strcpy(img->img_link, sqlite3_column_text(res, 2));
			sqlite3_column_int(res, 3);
			sqlite3_column_int(res, 4);
			sqlite3_column_int(res, 5);
			sqlite3_column_int(res, 6);
			sqlite3_column_int(res, 7);
		}
	}

	sqlite3_finalize(res);
	free(sql);
	return img;
}








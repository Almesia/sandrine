#include "user.h"
#include "monster.h"
#include "hero.h"
#include "image.h"
/*
 * Function: init_database
 * ----------------------------
 *   Function to initialise the database tables
 *
 *   db: the database variable
 *   name_db: string who contain the name of the database
 *
 *   returns: return the database variable on success
 *			  return NULL on error
 */
sqlite3* init_database(sqlite3 *db, char * name_db);

/*
 * Function: open_database
 * ----------------------------
 *   Open the database from the name / create it if not exist
 *
 *	 db: pointer of the database
 *   name_db: string who contain the name of the database
 *
 *   returns: return the database variable on success
 *			  return NULL on error
 */
sqlite3* open_database(sqlite3 *db, char * name_db);

/*
 * Function: close_database
 * ----------------------------
 *   Close the database from the db variable
 *
 *	 db: pointer of the database
 *
 *   returns: void
 */
void close_database(sqlite3 *db);

/*
 * Function: exec_sql_stmt
 * ----------------------------
 *   Execute an sql statement
 *
 *	 db: pointer of the database
 *   line: string who contain the sql statement
 *
 *   returns: return 1 on success
 *			  return 0 on error
 */
int exec_sql_stmt(sqlite3 *db, char * line);

/*
 * Function: create_tables
 * ----------------------------
 *   Create all the tables of the database
 *
 *	 db: pointer of the database
 *   file_name: string of the name of the sql file
 *
 *   returns: return 1 on success
 *			  return 0 on error
 */
int read_file_to_exec(sqlite3* db, char * file_name);

/*
 * Function: create_tables
 * ----------------------------
 *   Create all the tables of the database
 *
 *	 db: pointer of the database
 *   file_name: string of the name of the sql file for table creation
 *
 *   returns: return 1 on success
 *			  return 0 on error
 */
int create_tables(sqlite3* db, char * file_name);

/*
 * Function: insert_content_tables
 * ----------------------------
 *   Insert all the content into the database
 *
 *	 db: pointer of the database
 *   file_name: string of the name of the sql file for insert statement
 *
 *   returns: return 1 on success
 *			  return 0 on error
 */
int insert_content_tables(sqlite3* db, char * file_name);

/*
 * Function: select_user
 * ----------------------------
 *   Create user struct with the information of the current user
 *
 *	 db: pointer of the database
 *   user_name: string of the name of the user
 *
 *   returns: return User on success
 *			  return NULL on error
 */
User * select_user(sqlite3* db, char * user_name);

/*
 * Function: select_heroes_user
 * ----------------------------
 *   Select all the heroes for the user given
 *
 *	 db: pointer of the database
 *   user_id: id of the user
 *
 *   returns: return Liste_Hero on success
 *			  return NULL on error
 */
Liste_Hero* select_heroes_user(sqlite3* db, int user_id);

/*
 * Function: select_heroes
 * ----------------------------
 *   Select all the heroes
 *
 *	 db: pointer of the database
 *
 *   returns: return Liste_Hero on success
 *			  return NULL on error
 */
Liste_Hero* select_heroes(sqlite3* db);

/*
 * Function: select_monster_current_level
 * ----------------------------
 *   Select all the monsters for the level given
 *
 *	 db: pointer of the database
 *   level: int of the level
 *
 *   returns: return Liste_Monster on success
 *			  return NULL on error
 */
Liste_Monster * select_monster_current_level(sqlite3 *db, int level);

/*
 * Function: update_user
 * ----------------------------
 *   Update user given into db
 *
 *	 db: pointer of the database
 *   user: User to update
 *
 *   returns: return 1 on success
 *			  return 0 on error
 */
int update_user(sqlite3 * db, User *user);

/*
 * Function: update_hero
 * ----------------------------
 *   Update hero given into db
 *
 *	 db: pointer of the database
 *   hero: Hero to update
 *
 *   returns: return 1 on success
 *			  return 0 on error
 */
int update_hero(sqlite3 * db, Hero *hero);

/*
 * Function: select_img_round
 * ----------------------------
 *   Select image background for the round id given
 *
 *	 db: pointer of the database
 *   round_id: int of the round
 *
 *   returns: return Image on success
 *			  return NULL on error
 */
Image * select_img_round(sqlite3* db, int round_id);

/*
 * Function: add_heroes_to_user
 * ----------------------------
 *   Insert bound user with hero
 *
 *	 db: pointer of the database
 *   hero_id: int of the hero id
 *   user_id: int of the user id
 *
 *   returns: return Liste_Monster on success
 *			  return NULL on error
 */
int add_heroes_to_user(sqlite3* db, int hero_id, int user_id);

/*
 * Function: select_hero_name
 * ----------------------------
 *   Select hero from name
 *
 *	 db: pointer of the database
 *   hero_name: name of the hero
 *
 *   returns: return Hero on success
 *			  return NULL on error
 */
Hero * select_hero_name(sqlite3* db, char * hero_name);

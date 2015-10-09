/*************************************************************************
* Fournier Laurent
* Travail 'AGENDA' v8 - Cours de programmation procédurale
*************************************************************************/
#ifndef GLOBAL_CONFIG
#define GLOBAL_CONFIG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*************************************************************************
* Constantes
*************************************************************************/
#define FILE_LENGTH 21
#define PMODE_LENGTH 16

#define FNAME_LENGTH 15
#define LNAME_LENGTH 15
#define JOB_LENGTH 15
#define PHONE_LENGTH 15

#define READ "r"
#define WRITE "w"
#define APPEND "a"
#define READ_BINARY "rb"
#define WRITE_BINARY "wb"
#define APPEND_BINARY "ab"

static const char *CLEAR_SCREEN =
#ifdef __WIN32__
    "cls";
#else
    "clear";
#endif

static const char *LIST_DIR =
#ifdef __WIN32__
    "dir /b *.dat";
#else
    "ls *.dat";
#endif


/*************************************************************************
* Enumerations & structures
*************************************************************************/
enum Menu { SELECT_AGENDA, NEW_AGENDA, APPEND_ENTRY, IMPORT_ENTRIES, SEARCH_PART, SEARCH_NUM, READ_ALL, F7, F8, QUIT };

typedef struct entry_Name {
        char fname[FNAME_LENGTH+1];
        char lname[LNAME_LENGTH+1];
        int age;
        char filler_1[12];
        char job[JOB_LENGTH+1];
        char phone[PHONE_LENGTH+1];
        char filler_2[16];
} db_Entry;

typedef struct db_Active {
    int dbstate;
    char dbname[FILE_LENGTH];
    FILE * dbfile;
} db_Used;


/*************************************************************************
* Prototypes
*************************************************************************/
    /* main.c */
int showMenu(db_Used active_Db);

    /* gestion_fichiers.c */
void selectAgenda(db_Used *active_Db);
void createAgenda(void);
void newEntry(db_Used *active_Db);
void importEntries(db_Used *active_Db);

    /* recherche.c */
void searchNum(db_Used *active_Db);
void searchPart(db_Used *active_Db);
void readAll(db_Used *active_Db);

    /* fonctions_utiles.c */
void printResult(db_Entry entry, char *print_Mode);
void dataListing(char *db_Name);
char *stringFormater(char *str);
void fgetsCleaner(char *chain);
void fgetsPurger(void);

#endif // GLOBAL_CONFIG

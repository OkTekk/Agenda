/*************************************************************************
* Fournier Laurent
* Travail 'AGENDA' v8 - Cours de programmation procédurale
*************************************************************************/
#include "global.h"


/*************************************************************************
* Programme principal
*************************************************************************/
int main(int argc, char *argv[]) {
    int end_Menu = 0;

    db_Used active_Db;
    memset(&active_Db, sizeof(active_Db), 0);

    while(!end_Menu) {
        switch(showMenu(active_Db)) {
            case SELECT_AGENDA: selectAgenda(&active_Db); break;
            case NEW_AGENDA: createAgenda(); break;
            case APPEND_ENTRY: newEntry(&active_Db); break;
            case IMPORT_ENTRIES: importEntries(&active_Db); break;
            case SEARCH_PART: searchPart(&active_Db); break;
            case SEARCH_NUM: searchNum(&active_Db); break;
            case READ_ALL: readAll(&active_Db); break;

            case QUIT: printf("Bye bye !\n\n"); end_Menu = 1; break;
            default: printf("Error !\nBad Entry, try again.\n\n"); break;
        }
    }

    return 0;
}


/*************************************************************************
* Affichage du menu
*************************************************************************/
int showMenu(db_Used active_Db) {
    int menu_Choice;

    printf("------------------\n");
    printf("------ Menu ------\n");
    if(active_Db.dbstate == 1) printf("--- %s ---\n", active_Db.dbname);
    printf("------------------\n\n");
    printf("%d. Select agenda\n", SELECT_AGENDA);
    printf("%d. Create agenda\n\n", NEW_AGENDA);
    printf("%d. Add entries\n", APPEND_ENTRY);
    printf("%d. Import entries\n\n", IMPORT_ENTRIES);
    printf("%d. Search (name)\n", SEARCH_PART);
    printf("%d. Search (number)\n", SEARCH_NUM);
    printf("%d. Read all\n\n", READ_ALL);
    printf("%d. Quit\n", QUIT);
    printf("\n----------------\n");
    printf("Your choice : ");

    scanf("%d", &menu_Choice); getchar();
    system(CLEAR_SCREEN);

    return menu_Choice;
}

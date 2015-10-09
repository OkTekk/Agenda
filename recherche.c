/*************************************************************************
* Fournier Laurent
* Travail 'AGENDA' v8 - Cours de programmation procédurale
*************************************************************************/
#include "global.h"


/*************************************************************************
* Fonctions liées aux recherches
*************************************************************************/
/* recherche par id d'entrée */
void searchNum(db_Used *active_Db) {
    char f_Name[FILE_LENGTH], print_Mode[PMODE_LENGTH];
    int search_Number, f_Size, f_Position, entries_Nr;
    db_Entry entry;

    printf("User id searched : ");
    scanf("%d", &search_Number); getchar();

    printf("How to print results ('Short' or 'Long') : ");
    fgets(print_Mode, sizeof(print_Mode), stdin);
    fgetsCleaner(print_Mode);
    system(CLEAR_SCREEN);

    fseek(active_Db->dbfile, 0, SEEK_END);
    f_Size = ftell(active_Db->dbfile);
    f_Position = search_Number * sizeof(entry);

    printf("------------------------------\n");
    if(search_Number < 0 || f_Position >= f_Size) {
        entries_Nr = f_Size / sizeof(entry);
        printf("-- This ID don't exist, %d entries found --\n\n", entries_Nr);
    }
    else {
        fseek(active_Db->dbfile, f_Position, 0);
        fread (&entry, sizeof(entry), 1, active_Db->dbfile);
        printResult(entry, print_Mode);
    }
    printf("------------------------------\n\n");
}


/* recherche par nom de famille avec écriture partielle */
void searchPart(db_Used *active_Db) {
    char f_Name[FILE_LENGTH], search_Lname[LNAME_LENGTH+1], print_Mode[PMODE_LENGTH];
    int i, search_Length, user_Found, nr_Found = 0;
    db_Entry entry;

    fseek(active_Db->dbfile, 0, SEEK_SET);

    printf("Last name (partial) searched : ");
    fgets(search_Lname, sizeof(search_Lname), stdin);
    fgetsCleaner(search_Lname);
    stringFormater(search_Lname);

    search_Length = strlen(search_Lname);

    printf("How to print results ('Short' or 'Long') : ");
    fgets(print_Mode, sizeof(print_Mode), stdin);
    fgetsCleaner(print_Mode);
    system(CLEAR_SCREEN);

    printf("------------------------------\n");
    while(!feof(active_Db->dbfile)) {
        user_Found = 1;
        fread(&entry, sizeof(entry), 1, active_Db->dbfile);

        for(i=0; i<search_Length; i++) {
            if(search_Lname[i] != entry.lname[i]) { user_Found = 0; break; }
        }

        if(user_Found && !feof(active_Db->dbfile)) {
            nr_Found++;
            printResult(entry, print_Mode);
        }
    }
    printf("\n\t\tEntries found : %d\n", nr_Found);
    printf("------------------------------\n\n");

    if(!nr_Found) printf("\n-- Name %s not found --\n\n", search_Lname);
}


/* affiche toutes les entrées de la database */
void readAll(db_Used *active_Db) {
    char f_Name[FILE_LENGTH], print_Mode[PMODE_LENGTH];
    db_Entry entry;

    printf("How to print results ('Short' or 'Long') : ");
    fgets(print_Mode, sizeof(print_Mode), stdin);
    fgetsCleaner(print_Mode);
    system(CLEAR_SCREEN);

    fseek(active_Db->dbfile, 0, SEEK_SET);

    printf("------------------------------\n");
    while(!feof(active_Db->dbfile)) {
        fread(&entry, sizeof(entry), 1, active_Db->dbfile);
        if(!feof(active_Db->dbfile)) printResult(entry, print_Mode);
    }
    printf("------------------------------\n\n");
}

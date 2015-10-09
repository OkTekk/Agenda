/*************************************************************************
* Fournier Laurent
* Travail 'AGENDA' v8 - Cours de programmation procédurale
*************************************************************************/
#include "global.h"


/*************************************************************************
* Fonctions liées à la gestion des fichiers de DB
*************************************************************************/
/* sélection de la database active */
void selectAgenda(db_Used *active_Db) {
    char f_Name[FILE_LENGTH];

    if(active_Db->dbstate == 1) fclose(active_Db->dbfile);
    system(LIST_DIR);

    printf("Enter database to use : ");
    fgets(f_Name, sizeof(f_Name), stdin);
    fgetsCleaner(f_Name);
    stringFormater(f_Name);
    system(CLEAR_SCREEN);

    strcpy(active_Db->dbname, f_Name);
    active_Db->dbfile = fopen(f_Name, APPEND_BINARY);
    active_Db->dbstate = 1;
}


/* crée nouvelle DB */
void createAgenda(void) {
    char f_Name[FILE_LENGTH];
    FILE * f_Output;

    printf("Filename to create : ");
    fgets(f_Name, sizeof(f_Name), stdin);
    fgetsCleaner(f_Name);
    stringFormater(f_Name);
    f_Output = fopen(f_Name, WRITE_BINARY);
    system(CLEAR_SCREEN);
    fclose(f_Output);
}


/* ajoute de nouvelles entrées avec 'APPEND' */
void newEntry(db_Used *active_Db) {
    char f_Name[FILE_LENGTH];
    int exit_Loop = 0, entry_Nr = 1, test_Output;

    db_Entry entry;
    memset(&entry, sizeof(entry), 0);

    fflush(stdin);

    fseek(active_Db->dbfile, 0, SEEK_END);
    test_Output = ftell(active_Db->dbfile);
    entry_Nr = test_Output / sizeof(entry);

    while(!exit_Loop) {
        printf("Entry number : %d\n\n", entry_Nr+1);

        printf("\nFirst name : ");
        fgets(entry.fname, sizeof(entry.fname), stdin);
        fgetsCleaner(entry.fname);
        stringFormater(entry.fname);

        if(strcmp(entry.fname, "Quit") == 0) { system(CLEAR_SCREEN); break; }

        printf("\nLast name : ");
        fgets(entry.lname, sizeof(entry.lname), stdin);
        fgetsCleaner(entry.lname);
        stringFormater(entry.lname);

        printf("\nAge : ");
        scanf("%d", &entry.age); getchar();

        printf("\nWork : ");
        fgets(entry.job, sizeof(entry.job), stdin);
        fgetsCleaner(entry.job);
        stringFormater(entry.job);

        printf("\nPhone number : ");
        fgets(entry.phone, sizeof(entry.phone), stdin);
        fgetsCleaner(entry.phone);

        fwrite(&entry, sizeof(entry), 1, active_Db->dbfile);
        fflush(stdin);

        entry_Nr++;
        system(CLEAR_SCREEN);
    }
}


/* importe des entrées contenues dans un fichier texte */
void importEntries(db_Used *active_Db) {
    char file_In[FILE_LENGTH], file_Out[FILE_LENGTH];
    FILE *f_Input;

    db_Entry entry;
    memset(&entry, sizeof(entry), 0);

    printf("File to import : ");
    fgets(file_In, sizeof(file_In), stdin); fgetsCleaner(file_In);
    f_Input = fopen(file_In, READ);
    if(f_Input == NULL) printf("Error opening : %s\n", file_In);
    else printf("Text source : %s opened\n\n", file_In);

    fseek(f_Input, 0, SEEK_SET);
    fseek(active_Db->dbfile, 0, SEEK_END);

    while(!feof(f_Input)) {
        fscanf(f_Input, "%s %s %d %s %s", &entry.fname, &entry.lname, &entry.age, &entry.job, &entry.phone);
        stringFormater(entry.fname);
        stringFormater(entry.lname);
        stringFormater(entry.job);

        fwrite(&entry, sizeof(entry), 1, active_Db->dbfile);
    }

    system(CLEAR_SCREEN);
    printf("%s successfully imported in %s\n\n", file_In, active_Db->dbfile);

    fclose(f_Input);
}

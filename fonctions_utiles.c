/*************************************************************************
* Fournier Laurent
* Travail 'AGENDA' v8 - Cours de programmation procédurale
*************************************************************************/
#include "global.h"


/*************************************************************************
* Fonctions 'pratiques' et/ou visant à alléger les fonctions principales
*************************************************************************/
/* affiche les résultats de recherche en version détaillée ou compacte, au choix */
void printResult(db_Entry entry, char *print_Mode) {
    print_Mode = stringFormater(print_Mode);

    if(strcmp(print_Mode, "Long") == 0) {
        printf("First name : %s\n", entry.fname);
        printf("Last name : %s\n", entry.lname);
        printf("Age : %d\n", entry.age);
        printf("Work : %d\n", entry.job);
        printf("Phone number : %s\n\n", entry.phone);
    }
    else if(strcmp(print_Mode, "Short") == 0) {
        printf("%s %s %d %s %s\n", entry.fname, entry.lname, entry.age, entry.job, entry.phone);
    }
    else printf("Wrong mode\n");
}


/* crée un fichier contenant les databases existantes */
void dataListing(char *db_Name) {
    FILE * f_Output =  fopen("databases.list", APPEND);
    fputs(db_Name, f_Output);
    fputs("\n", f_Output);
    fclose(f_Output);
}


/* force l'écriture des entrées sorties avec un format défini */
char *stringFormater(char *str) {
    size_t i = 0;
    size_t string_Length = strlen(str);

    str[i] = toupper((unsigned char)str[i]);
    for(i=1; i<string_Length; i++) str[i] = tolower((unsigned char)str[i]);

    return str;
}


/* purge les fgets de leur carractère d'échapement */
void fgetsCleaner(char *chain) {
    char *mark = strchr(chain, '\n');
    if(mark) *mark = 0;
    else fgetsPurger();
}

void fgetsPurger(void) {
    int c;
    while((c=getchar()) != '\n' && c != EOF) {}
}

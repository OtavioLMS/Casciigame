#include "characters.h"

void loadEn(char *enList, int n){
    char ch[15];
    char file_name[25] = "settings.txt";
    int cont=0;
    FILE *fp;

    fp = fopen(file_name,"r"); // read mode

    if( fp == NULL )
    {
        perror("Error while opening the settings file.\n");
        system("pause");
        exit(EXIT_FAILURE);
    }
    fgets(ch,sizeof(ch),fp);
    fgets(ch,sizeof(ch),fp);
    while( (fgets(ch,sizeof(ch),fp))&&cont<n){
        cont++;
    }
    strcpy(enList, ch);
    strtok(enList, "\n");
    fclose(fp);

}


void enemy(char *ene, chara *bad, char *ename, int enN){
    char ch[78];
    char file_name[25];
    int aux =rand()%enN;
    char eList[10];
    loadEn(eList, aux);
    strcpy(file_name,eList);
    FILE *fp;
    strcpy(ename, eList);
    strtok(ename, ".");
    while(strlen(ename)<6){
        strcat(ename, " ");
    }
    char auxsting[77]="";
    fp = fopen(file_name,"r"); // read mode
    if( fp == NULL )
    {
        char error[99];
        sprintf(error, "Error while opening the enemy file.\n%s",file_name);
        system("pause");
        perror(error);

        exit(EXIT_FAILURE);
    }
    int flag =0;

    while( ( fgets(ch,sizeof(ch),fp) )){
        if(flag == 0){
            strcat(ene,ch);
            if(ch[0]=='x'){
                flag=1;
            }
        }
        else{
            strcpy(auxsting,ch);
            switch(auxsting[0]){
                case 'h':
                    fflush(stdin);
                    sscanf(auxsting, "h: %d", &aux);
                    bad->hp = aux;
                    break;
                case 's':
                    fflush(stdin);
                    sscanf(auxsting, "s: %d", &aux);
                    bad->st = aux;
                    break;
                case 'm':
                    fflush(stdin);
                    sscanf(auxsting, "m: %d", &aux);
                    bad->sp = aux;
                    break;
                case 'd':
                    fflush(stdin);
                    sscanf(auxsting, "d: %d", &aux);
                    bad->def=aux;
                    break;

            }

        }


    }
    fclose(fp);
}

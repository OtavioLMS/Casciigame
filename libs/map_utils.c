#include "map_utils.h"

int checkli(int x, int y, pos *b, int size){
    int i;
    for(i=0;i<size;i++){
        if(x==b[i].x && y==b[i].y){
            return 1;
        }
    }
    return 0;
}

void posiSet(int x,int y,pos *a){
    a->x=x;
    a->y=y;
}

void loadMap(pos *a, pos *b, pos *goal, int lv){
    char ch;
    int ind;
    for(ind=0;ind<(MAX*MAX);ind++){
        b[ind].x=-1;
        b[ind].y=-1;
    }
    char file_name[25];
    sprintf(file_name,"lv%d.txt",lv);
    FILE *fp;

    fp = fopen(file_name,"r"); // read mode

    if( fp == NULL )
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int x=0;
    int y=0;
    int aux=0;
    while( ( ch = fgetc(fp) ) != EOF ){
        switch(ch){
            case ' ':
                x++;
                break;
            case 'I':
                b[aux].x=x;
                b[aux].y=y;
                x++;
                break;
            case 'X':
                a->x=x;
                a->y=y;
                x++;
                break;
            case '\n':
                x=0;
                y++;
                break;
            case '>':
                goal->x=x;
                goal->y=y;
                x++;
                break;
            default:
                x++;
        }
        aux++;
    }
    fclose(fp);

}

void mapi(pos a, pos *b, pos goal, int size, chara hero){

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int x,y;

    printf("hero stats:\n");
    printf("hp = %d ----- the health of the hero\n", hero.hp);
    printf("st = %d ----- physical power\n", hero.st);
    printf("sp = %d ----- magical power\n", hero.sp);
    printf("def = %d ----- defense\n", hero.def);
    printf("xp = %d ----- experience(gets random status upgrades upon reaching 100)\n\n", hero.xp);

    for(y=0;y<MAX;y++){

        for(x=0;x<MAX;x++){

            if(x== a.x && y== a.y){
                SetConsoleTextAttribute(hConsole, 15);
                printf("X");
            }
            else if(goal.x == x && goal.y== y){
                SetConsoleTextAttribute(hConsole, 58);
                printf(">");
            }
            else if(checkli(x,y,b,size)){
                SetConsoleTextAttribute(hConsole, 202);
                printf("I");
            }
            else{
                SetConsoleTextAttribute(hConsole, 15);
                printf(" ");
            }

        }
        SetConsoleTextAttribute(hConsole, 15);
        printf("\n");

    }

}

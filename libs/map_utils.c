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
/*
mapi function:
    prints the current map on the screen
OBS:
    you need to have called start_color on the main loop BEFORE calling this
    function
*/
void mapi(pos a, pos *b, pos goal, int size, chara hero){

    int x,y;

    printw("hero stats:\n");
    printw("hp = %d ----- the health of the hero\n", hero.hp);
    printw("st = %d ----- physical power\n", hero.st);
    printw("sp = %d ----- magical power\n", hero.sp);
    printw("def = %d ----- defense\n", hero.def);
    printw("xp = %d ----- experience(gets random status upgrades upon reaching 100)\n\n", hero.xp);

    for(y=0;y<MAX;y++){

        for(x=0;x<MAX;x++){

            if(x== a.x && y== a.y){
                printw("X");
            }
            else if(goal.x == x && goal.y== y){
                attron(COLOR_PAIR(3));
                printw(">");
                attroff(COLOR_PAIR(3));
            }
            else if(checkli(x,y,b,size)){
                attron(COLOR_PAIR(2));
                printw("I");
                attroff(COLOR_PAIR(2));
            }
            else{
                printw(" ");
            }

        }
        printw("\n");

    }

}

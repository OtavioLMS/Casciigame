#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "libs/arrkeys.h"
#include "libs/characters.h"
#include "libs/map_utils.h"

void loadLv(int *nLv, int *enN);
void fightSmiley(chara *hero, int ind, int enN);

int main (){

    srand(time(0));

    int ch;
    int ind = 0;
    int lvs = 2;
    int enN = 3;

    loadLv(&lvs, &enN);

    int map_size = MAX*MAX;

    pos you_are_here, map_positions[map_size];
    pos goal;
    chara hero;

    hero.hp = 30;
    hero.st = 10;
    hero.sp = 20;
    hero.def = 7;
    hero.xp = 0;

    system("mode con:cols=80 lines=31");

    for(ind=0;ind<map_size;ind++){
        map_positions[ind].x=-1;
        map_positions[ind].y=-1;
    }

    ind =1;

    loadMap(&you_are_here, map_positions, &goal, ind);

    ch=0;

    mapi(you_are_here, map_positions, goal, map_size, hero);

    while ((ch = getch()) != 27){  /* 27 = Esc key */
        if (ch == 0 || ch == 224){

            switch (_getch ()){

                case 72:
                    if(!checkli(you_are_here.x, you_are_here.y-1, map_positions, map_size)){
                        if(you_are_here.y > 0){
                            you_are_here.y -= 1;
                        }
                        else if(!checkli(you_are_here.x, MAX-1, map_positions, map_size)){
                            you_are_here.y = MAX-1;
                        }
                    }
                    break;

                case 77:
                    if(!checkli(((you_are_here.x+1)%MAX), you_are_here.y, map_positions, map_size)){
                        you_are_here.x = (you_are_here.x+1)%MAX;
                    }
                    break;
                case 75:
                    if(!checkli(you_are_here.x-1, you_are_here.y, map_positions, map_size)){
                        if(you_are_here.x > 0){
                            you_are_here.x -= 1;
                        }
                        else if(!checkli(MAX-1, you_are_here.y, map_positions, map_size)){
                            you_are_here.x = MAX-1;
                        }
                    }
                    break;
                case 80:
                    if(!checkli(you_are_here.x, (you_are_here.y+1)%MAX, map_positions, map_size)){
                        you_are_here.y = (you_are_here.y+1)%MAX;
                    }
                    break;
            }

            system("cls");

            if(rand()%15==1){
                fightSmiley(&hero, ind, enN);
            }

            system("cls");

            mapi(you_are_here, map_positions, goal, map_size, hero);
        }
        if (you_are_here.x==goal.x&& you_are_here.y==goal.y){

            char lv[16];
            int pp=0;

            if (ind<lvs){
                ind++;
                loadMap(&you_are_here, map_positions, &goal, ind);
                system("cls");

                sprintf(lv, "L E V E L   %d", ind);

                int pp=0;

                for(pp=0;lv[pp]!='\0';pp++){
                    printf("%c", lv[pp]);
                    Sleep(100);
                }

            }
            else{
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n");

                char end[107] = "congratulations you've escaped the castle of death \n and survived the evil smiley horde\n\n\n T H E   E N D";

                for(pp=0;end[pp] != '\0';pp++){
                    printf("%c", end[pp]);
                    Sleep(100);
                }

                printf("\n\n");
                system("pause");

                exit(0);

            }
        }
    }

    printf("ESC %d\n", ch);
    return (0);
}


void loadLv(int *nLv, int *enN){

    char ch[7];
    char file_name[25] = "settings.txt";
    FILE *fp;

    fp = fopen(file_name, "r"); // read mode

    if( fp == NULL )
    {
        perror("Error while opening the level file.\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    fgets(ch, sizeof(ch), fp);
    sscanf(ch, "lv: %d", nLv);
    fgets(ch, sizeof(ch), fp);
    sscanf(ch, "en: %d", enN);
    fclose(fp);

}

void fightSmiley(chara *hero, int ind, int enN){

    system("mode con:cols=80 lines=25");

    char ene[1020] = "";
    char ename[20];
    chara bad;
    bad.xp = 0;

    enemy(ene, &bad, ename, enN);

    int hp = hero->hp;
    int enehp = (bad.hp)*ind;
    char f1 = 'X';
    char f2 = ' ';
    char f3 = ' ';
    char f4 = ' ';
    char texto[30];

    sprintf(texto, "an evil %s has appeared ", ename);

    int choice = 3;

    while(enehp > 0 && hp > 0){
        system("cls");
        printf("%s", ene);
        printf("|--------------------------------------------------------------------------|\n");
        printf("||                                       +---------------------------------|\n");
        printf("|| %s          | %c attack                      |-|\n", texto, f1);
        printf("|| hp = %2d                               | %c magic                       |-|\n", hp, f2);
        printf("|| enemy hp = %2d                         | %c healing magic               |-|\n", enehp, f3);
        printf("||                                       | %c guard                       |-|\n", f4);
        printf("||                                       +---------------------------------|\n");
        printf("|--------------------------------------------------------------------------|\n");
        printf("+--------------------------------------------------------------------------+\n");
        switch(arrkeys()){
            case 'u':
                choice = (choice+1)%4;
                break;
            case 'd':
                choice -= 1;
                if(choice < 0){
                    choice = 3;
                }
                break;
            case 'q':
                switch(choice){
                    case 3:
                        sprintf(texto, "you've attacked evil %s ", ename);
                        system("color 4F");
                        Sleep(100);
                        system("color 0F");
                        enehp-=(hero->st-(bad.def));
                        hp -= -(hero->def-(bad.st+rand()%5));
                        break;
                    case 2:
                        strcpy(texto, "you've used magic!          ");
                        enehp -= (hero->sp-(bad.sp+rand()%15));
                        hp -= -(hero->def-(bad.st+rand()%5));
                        break;
                    case 1:
                        sprintf(texto, "you used healing magic      ");
                        system("color 0A");
                        Sleep(100);
                        system("color A0");
                        Sleep(50);
                        system("color 0F");
                        hp = hp + hero->sp/2;
                        hp -= -(hero->def-(bad.st+rand()%5));
                        break;
                    case 0:
                        system("color 84");
                        Sleep(100);
                        system("color 0F");
                        strcpy(texto, "you  guard to reduce damage ");
                        hp -= -((hero->def*2)-(bad.st+rand()%5));
                        break;
                }
                break;
        }
        switch(choice){
            case 3:
                f1 = 'X';
                f2 = ' ';
                f3 = ' ';
                f4 = ' ';
                break;
            case 2:
                f1 = ' ';
                f2 = 'X';
                f3 = ' ';
                f4 = ' ';
                break;
            case 1:
                f1 =' ';
                f2 =' ';
                f3 ='X';
                f4 =' ';
                break;
            case 0:
                f1 =' ';
                f2 =' ';
                f3 =' ';
                f4 ='X';
                break;
        }

        if(hp > (hero->hp)){
            hp = hero->hp;
        }

    }

    if(hp <= 0){

        system("cls");

        printf("                                            \n");
        printf("  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$ \n");
        printf(" /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/ \n");
        printf("| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$       \n");
        printf("| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$    \n");
        printf("| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/    \n");
        printf("| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$       \n");
        printf("|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$ \n");
        printf(" \\______/ |__/  |__/|__/     |__/|________/ \n");
        printf("                                            \n");
        printf("                                            \n");
        printf("                                            \n");
        printf("  /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$    \n");
        printf(" /$$__  $$| $$   | $$| $$_____/| $$__  $$   \n");
        printf("| $$  \\ $$| $$   | $$| $$      | $$  \\ $$   \n");
        printf("| $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/   \n");
        printf("| $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$   \n");
        printf("| $$  | $$  \\  $$$/  | $$      | $$  \\ $$   \n");
        printf("|  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$   \n");
        printf(" \\______/     \\_/    |________/|__/  |__/   \n");
        printf("                                            \n");
        printf("                                            \n");
        printf("                                            \n");

        system("pause");
        exit(0);

    }

    else{

        hero->xp += (rand()%900)/hp;

        if (hero->xp >= 100){
            hero->hp += rand()%10;
            hero->st += rand()%3;
            hero->sp += rand()%4;
            hero->def += rand()%5;
            hero->xp = 0;
        }

        system("cls");

        printf("+--------------------------------------------------------------------------+\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("|                                                                          |\n");
        printf("+--------------------------------------------------------------------------+\n");
        printf("                                                                            \n");
        printf("|--------------------------------------------------------------------------|\n");
        printf("||                                       +---------------------------------|\n");
        printf("|| you've defeated the evil %s       |                               |-|\n", ename);
        printf("|| CONGRATULATIONS!                      |                               |-|\n");
        printf("||                                       |                               |-|\n");
        printf("||                                       +---------------------------------|\n");
        printf("|--------------------------------------------------------------------------|\n");
        printf("+--------------------------------------------------------------------------+\n");

        system("pause");

        system("cls");

        printf("                                                                \n");
        printf("__/\\\\\\________/\\\\\\_______/\\\\\\\\\\_______/\\\\\\________/\\\\\\_         \n");
        printf(" _\\///\\\\\\____/\\\\\\/______/\\\\\\///\\\\\\____\\/\\\\\\_______\\/\\\\\\_        \n");
        printf("  ___\\///\\\\\\/\\\\\\/______/\\\\\\/__\\///\\\\\\__\\/\\\\\\_______\\/\\\\\\_       \n");
        printf("   _____\\///\\\\\\/_______/\\\\\\______\\//\\\\\\_\\/\\\\\\_______\\/\\\\\\_      \n");
        printf("    _______\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_     \n");
        printf("     _______\\/\\\\\\_______\\//\\\\\\______/\\\\\\__\\/\\\\\\_______\\/\\\\\\_    \n");
        printf("      _______\\/\\\\\\________\\///\\\\\\__/\\\\\\____\\//\\\\\\______/\\\\\\__   \n");
        printf("       _______\\/\\\\\\__________\\///\\\\\\\\\\/______\\///\\\\\\\\\\\\\\\\\\/___  \n");
        printf("        _______\\///_____________\\/////__________\\/////////_____ \n");
        printf("__/\\\\\\______________/\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\\\\\_____/\\\\\\_        \n");
        printf(" _\\/\\\\\\_____________\\/\\\\\\_\\/////\\\\\\///__\\/\\\\\\\\\\\\___\\/\\\\\\_       \n");
        printf("  _\\/\\\\\\_____________\\/\\\\\\_____\\/\\\\\\_____\\/\\\\\\/\\\\\\__\\/\\\\\\_      \n");
        printf("   _\\//\\\\\\____/\\\\\\____/\\\\\\______\\/\\\\\\_____\\/\\\\\\//\\\\\\_\\/\\\\\\_     \n");
        printf("    __\\//\\\\\\__/\\\\\\\\\\__/\\\\\\_______\\/\\\\\\_____\\/\\\\\\\\//\\\\\\\\/\\\\\\_    \n");
        printf("     ___\\//\\\\\\/\\\\\\/\\\\\\/\\\\\\________\\/\\\\\\_____\\/\\\\\\_\\//\\\\\\/\\\\\\_   \n");
        printf("      ____\\//\\\\\\\\\\\\//\\\\\\\\\\_________\\/\\\\\\_____\\/\\\\\\__\\//\\\\\\\\\\\\_  \n");
        printf("       _____\\//\\\\\\__\\//\\\\\\_______/\\\\\\\\\\\\\\\\\\\\\\_\\/\\\\\\___\\//\\\\\\\\\\_ \n");
        printf("        ______\\///____\\///_______\\///////////__\\///_____\\/////__\n");
        printf("                                                                \n");
        printf("                                                                \n");

        system("pause");

        system("mode con:cols=80 lines=31");

    }

}

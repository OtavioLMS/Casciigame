#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "libs/arrkeys.h"
#include "libs/characters.h"
#include "libs/map_utils.h"
#include "libs/x_system.h"

void loadLv(int *nLv, int *enN);
void fightSmiley(chara *hero, int ind, int enN);

int main (){

    srand(time(0));

    initscr();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_YELLOW, COLOR_RED);
    init_pair(3, COLOR_CYAN, COLOR_MAGENTA);
    int ch;
    int ind = 0;
    int lvs = 2;
    int enN = 3;

    loadLv(&lvs, &enN);

    int map_size = MAX*MAX;

    pos you_are_here, wall_positions[map_size];
    pos goal;
    chara hero;

    hero.hp = 30;
    hero.st = 10;
    hero.sp = 20;
    hero.def = 7;
    hero.xp = 0;

    for(ind=0;ind<map_size;ind++){
        wall_positions[ind].x=-1;
        wall_positions[ind].y=-1;
    }

    ind =1;

    loadMap(&you_are_here, wall_positions, &goal, ind);

    ch=0;

    mapi(you_are_here, wall_positions, goal, map_size, hero);

    while ((ch = getch()) != 27){  /* 27 = Esc key */

        switch (ch){

            case 259:
                if(!checkli(you_are_here.x, you_are_here.y-1, wall_positions, map_size)){
                    if(you_are_here.y > 0){
                        you_are_here.y -= 1;
                    }
                    else if(!checkli(you_are_here.x, MAX-1, wall_positions, map_size)){
                        you_are_here.y = MAX-1;
                    }
                }
                break;

            case 261:
                if(!checkli(((you_are_here.x+1)%MAX), you_are_here.y, wall_positions, map_size)){
                    you_are_here.x = (you_are_here.x+1)%MAX;
                }
                break;
            case 260:
                if(!checkli(you_are_here.x-1, you_are_here.y, wall_positions, map_size)){
                    if(you_are_here.x > 0){
                        you_are_here.x -= 1;
                    }
                    else if(!checkli(MAX-1, you_are_here.y, wall_positions, map_size)){
                        you_are_here.x = MAX-1;
                    }
                }
                break;
            case 258:
                if(!checkli(you_are_here.x, (you_are_here.y+1)%MAX, wall_positions, map_size)){
                    you_are_here.y = (you_are_here.y+1)%MAX;
                }
                break;
        }

        clear();
        refresh();

        if(rand()%15==1){
            fightSmiley(&hero, ind, enN);
        }

        clear();
        refresh();

        mapi(you_are_here, wall_positions, goal, map_size, hero);

        if (you_are_here.x==goal.x&& you_are_here.y==goal.y){

            char lv[16];
            int pp=0;

            if (ind<lvs){
                ind++;
                loadMap(&you_are_here, wall_positions, &goal, ind);
                clear();
                refresh();


                sprintf(lv, "L E V E L   %d", ind);

                int pp=0;
                attron(COLOR_PAIR(1));
                for(pp=0;lv[pp]!='\0';pp++){
                    printw("%c", lv[pp]);
                    refresh();
                    x_sleep(100);
                }
                attroff(COLOR_PAIR(1));

            }
            else{
                clear();
                refresh();
                printw("\n\n\n\n\n\n\n\n\n");

                char end[107] = "congratulations you've escaped the castle of death \n and survived the evil smiley horde\n\n\n T H E   E N D";

                attron(COLOR_PAIR(1));
                for(pp=0;end[pp] != '\0';pp++){
                    printw("%c", end[pp]);
                    x_sleep(100);
                    refresh();
                }
                attroff(COLOR_PAIR(1));

                printw("\n\n");
                x_sleep(100);
                refresh();
                x_pause();

                endwin();
                exit(0);

            }
        }
        refresh();
    }

    printw("ESC %d\n", ch);
    endwin();
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
        x_pause();
        endwin();
        exit(EXIT_FAILURE);
    }

    fgets(ch, sizeof(ch), fp);
    sscanf(ch, "lv: %d", nLv);
    fgets(ch, sizeof(ch), fp);
    sscanf(ch, "en: %d", enN);
    fclose(fp);

}

void fightSmiley(chara *hero, int ind, int enN){

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
        clear();
        refresh();
        printw("%s", ene);
        printw("|--------------------------------------------------------------------------|\n");
        printw("||                                       +---------------------------------|\n");
        printw("|| %s          | %c attack                      |-|\n", texto, f1);
        printw("|| hp = %2d                               | %c magic                       |-|\n", hp, f2);
        printw("|| enemy hp = %2d                         | %c healing magic               |-|\n", enehp, f3);
        printw("||                                       | %c guard                       |-|\n", f4);
        printw("||                                       +---------------------------------|\n");
        printw("|--------------------------------------------------------------------------|\n");
        printw("+--------------------------------------------------------------------------+\n");
        switch(arrkeys()){
            case 'x':
                endwin();
                exit(0);
                break;
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
                        hp = hp + hero->sp/2;
                        hp -= -(hero->def-(bad.st+rand()%5));
                        break;
                    case 0:
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

        clear();
        refresh();

        printw("                                            \n");
        printw("  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$ \n");
        printw(" /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/ \n");
        printw("| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$       \n");
        printw("| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$    \n");
        printw("| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/    \n");
        printw("| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$       \n");
        printw("|  $$$$$$/| $$  | $$| $$ \\/  | $$| $$$$$$$$ \n");
        printw(" \\______/ |__/  |__/|__/     |__/|________/ \n");
        printw("                                            \n");
        printw("                                            \n");

        x_sleep(100);
        refresh();

        printw("                                            \n");
        printw("  /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$    \n");
        printw(" /$$__  $$| $$   | $$| $$_____/| $$__  $$   \n");
        printw("| $$  \\ $$| $$   | $$| $$      | $$  \\ $$   \n");
        printw("| $$  | $$|  $$ / $$/| $$$$$   | $$$$$$$/   \n");
        printw("| $$  | $$ \\  $$ $$/ | $$__/   | $$__  $$   \n");
        printw("| $$  | $$  \\  $$$/  | $$      | $$  \\ $$   \n");
        printw("|  $$$$$$/   \\  $/   | $$$$$$$$| $$  | $$   \n");
        printw(" \\______/     \\_/    |________/|__/  |__/   \n");
        printw("                                            \n");
        printw("                                            \n");
        printw("                                            \n");

        x_sleep(100);
        refresh();
        x_pause();
        endwin();
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

        clear();
        refresh();

        printw("+--------------------------------------------------------------------------+\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("|                                                                          |\n");
        printw("+--------------------------------------------------------------------------+\n");
        printw("                                                                            \n");
        printw("|--------------------------------------------------------------------------|\n");
        printw("||                                       +---------------------------------|\n");
        printw("|| you've defeated the evil %s       |                               |-|\n", ename);
        printw("|| CONGRATULATIONS!                      |                               |-|\n");
        printw("||                                       |                               |-|\n");
        printw("||                                       +---------------------------------|\n");
        printw("|--------------------------------------------------------------------------|\n");
        printw("+--------------------------------------------------------------------------+\n");

        refresh();
        x_pause();

        clear();
        refresh();

        printw("                                                                \n");
        printw("__/\\\\\\________/\\\\\\_______/\\\\\\\\\\_______/\\\\\\________/\\\\\\_         \n");
        printw(" _\\///\\\\\\____/\\\\\\/______/\\\\\\///\\\\\\____\\/\\\\\\_______\\/\\\\\\_        \n");
        printw("  ___\\///\\\\\\/\\\\\\/______/\\\\\\/__\\///\\\\\\__\\/\\\\\\_______\\/\\\\\\_       \n");
        printw("   _____\\///\\\\\\/_______/\\\\\\______\\//\\\\\\_\\/\\\\\\_______\\/\\\\\\_      \n");
        printw("    _______\\/\\\\\\_______\\/\\\\\\_______\\/\\\\\\_\\/\\\\\\_______\\/\\\\\\_     \n");
        printw("     _______\\/\\\\\\_______\\//\\\\\\______/\\\\\\__\\/\\\\\\_______\\/\\\\\\_    \n");
        printw("      _______\\/\\\\\\________\\///\\\\\\__/\\\\\\____\\//\\\\\\______/\\\\\\__   \n");
        printw("       _______\\/\\\\\\__________\\///\\\\\\\\\\/______\\///\\\\\\\\\\\\\\\\\\/___  \n");
        printw("        _______\\///_____________\\/////__________\\/////////_____ \n");

        x_sleep(100);
        refresh();

        printw("__/\\\\\\______________/\\\\\\__/\\\\\\\\\\\\\\\\\\\\\\__/\\\\\\\\\\_____/\\\\\\_        \n");
        printw(" _\\/\\\\\\_____________\\/\\\\\\_\\/////\\\\\\///__\\/\\\\\\\\\\\\___\\/\\\\\\_       \n");
        printw("  _\\/\\\\\\_____________\\/\\\\\\_____\\/\\\\\\_____\\/\\\\\\/\\\\\\__\\/\\\\\\_      \n");
        printw("   _\\//\\\\\\____/\\\\\\____/\\\\\\______\\/\\\\\\_____\\/\\\\\\//\\\\\\_\\/\\\\\\_     \n");
        printw("    __\\//\\\\\\__/\\\\\\\\\\__/\\\\\\_______\\/\\\\\\_____\\/\\\\\\\\//\\\\\\\\/\\\\\\_    \n");
        printw("     ___\\//\\\\\\/\\\\\\/\\\\\\/\\\\\\________\\/\\\\\\_____\\/\\\\\\_\\//\\\\\\/\\\\\\_   \n");
        printw("      ____\\//\\\\\\\\\\\\//\\\\\\\\\\_________\\/\\\\\\_____\\/\\\\\\__\\//\\\\\\\\\\\\_  \n");
        printw("       _____\\//\\\\\\__\\//\\\\\\_______/\\\\\\\\\\\\\\\\\\\\\\_\\/\\\\\\___\\//\\\\\\\\\\_ \n");
        printw("        ______\\///____\\///_______\\///////////__\\///_____\\/////__\n");
        printw("                                                                \n");
        printw("                                                                \n");

        x_sleep(100);
        refresh();
        x_pause();

    }

}

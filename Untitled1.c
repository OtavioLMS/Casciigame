#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>   // WinApi header
#include <time.h>
#include <math.h>
#include <string.h>
#define MAX  23
typedef struct axys{
    int x;
    int y;
}pos;
typedef struct chaar{
    int hp;
    int st;
    int sp;
    int def;
    int xp;
}chara;

void mapi(pos a, pos *b, pos goal, int size, chara hero);
int checkli(int x, int y, pos *b, int size);
void posiSet(int x,int y,pos *a);
void widewall(int x1, int x2, int y , pos *a,int *ind);
void longwall(int y1, int y2, int x , pos *a, int *ind);
void fightSmiley(chara *hero, int ind, int enN);
char arrkeys();
void enemy(char *ene, chara *bad, char *ename, int enN);
void loadMap(pos *a, pos *b, pos *goal,int lv);
void loadLv(int *nLv, int *enN);
void loadEn(char *enList, int n);

int main (){
    srand(time(0));
    int ch;
    int ind = 0;
    int lvs = 2;
    int enN = 3;
    loadLv(&lvs, &enN);
    int sizeb = MAX*MAX;
    pos a,b[sizeb];
    pos goal;
    chara hero;
    hero.hp = 30;
    hero.st = 10;
    hero.sp = 20;
    hero.def = 7;
    hero.xp = 0;
    system("mode con:cols=80 lines=31");
    for(ind=0;ind<sizeb;ind++){
        b[ind].x=-1;
        b[ind].y=-1;
    }
    ind =1;
    loadMap(&a, b,&goal, ind);
/*    goal.x = 5;
    goal.y = 5;
    a.x = 0;
    a.y = 1;

    widewall(0,9,0,b,&ind);
    longwall(0,9,9,b,&ind);
    longwall(2,9,0,b,&ind);
    widewall(0,7,2,b,&ind);
    longwall(2,7,7,b,&ind);
    widewall(3,7,7,b,&ind);
    longwall(4,7,2,b,&ind);
    widewall(3,5,4,b,&ind);
    widewall(0,9,9,b,&ind);
*/
    ch=0;
    mapi(a, b, goal, sizeb, hero);
    while ((ch = getch()) != 27) /* 27 = Esc key */
    {

        if (ch == 0 || ch == 224){
            switch (_getch ()){
                case 72:
                    if(checkli(a.x, a.y-1,b,sizeb)){
                        break;
                    }
                    if(a.y > 0){
                        a.y -=1;
                    }
                    else{
                        if(!checkli(a.x, MAX-1,b,sizeb)){
                            a.y = MAX-1;
                        }
                    }

                break;
                case 77:
                    if(checkli(((a.x+1)%MAX), a.y,b,sizeb)){
                        break;
                    }
                    a.x=(a.x+1)%MAX;
                break;
                case 75:
                    if(checkli(a.x-1, a.y,b,sizeb)){
                        break;
                    }
                    if(a.x > 0){
                        a.x -=1;
                    }
                    else{
                        if(!checkli(MAX-1, a.y,b,sizeb)){
                            a.x = MAX-1;
                        }
                    }
                break;
                case 80:
                    if(checkli(a.x, (a.y+1)%MAX,b,sizeb)){
                        break;
                    }
                    a.y=(a.y+1)%MAX;
                break;
                }
            printf("\a");
            system("cls");
            if(rand()%15==1){
                fightSmiley(&hero, ind, enN);
            }
            system("cls");
            mapi(a,b,goal,sizeb, hero);
            }
        if (a.x==goal.x&& a.y==goal.y){
            char lv[16];
            int pp=0;
            if (ind<lvs){
                ind++;
                loadMap(&a, b,&goal, ind);
                system("cls");
                sprintf(lv,"L E V E L   %d",ind);
                int pp=0;
                for(pp=0;lv[pp]!='\0';pp++){
                    printf("%c\a",lv[pp]);
                    Sleep(100);
                }
            }
            else{
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n");
                char end[107]="congratulations you've escaped the castle of death \n and survived the evil smiley horde\n\n\n T H E   E N D";

                for(pp=0;end[pp]!='\0';pp++){
                printf("%c\a",end[pp]);
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
void widewall(int x1, int x2, int y , pos *a, int *ind){
    int i;
    int aux =x2-x1+*ind;
    for(i=*ind; i<=aux;i++){
        a[i].y=y;
        a[i].x=(aux-i)+x1;
        *ind +=1;
    }
}
void longwall(int y1, int y2, int x , pos *a, int *ind){
    int i;
    int aux =y2-y1+*ind;
    for(i=*ind; i<=aux;i++){
        a[i].x=x;
        a[i].y=(aux-i)+y1;
        *ind +=1;
    }
}

void fightSmiley(chara *hero, int ind, int enN){
    system("mode con:cols=80 lines=25");
    char ene[1020]="";
    char ename[20];
    chara bad;
    bad.xp =0;
    enemy(ene, &bad, ename, enN);
    int hp = hero->hp;
    int enehp = (bad.hp)*ind;
    char f1 ='X';
    char f2 =' ';
    char f3 =' ';
    char f4 =' ';
    char texto[30];
    sprintf(texto,"an evil %s has appeared ",ename);
    int choice = 3;
    while(enehp>0&&hp>0){
    system("cls");
    printf("%s",ene);
    printf("|--------------------------------------------------------------------------|\n");
    printf("||                                       +---------------------------------|\n");
    printf("|| %s          | %c attack                      |-|\n",texto,f1);
    printf("|| hp = %2d                               | %c frown                       |-|\n",hp,f2);
    printf("|| enemy hp = %2d                         | %c smile back                  |-|\n",enehp,f3);
    printf("||                                       | %c guard                       |-|\n",f4);
    printf("||                                       +---------------------------------|\n");
    printf("|--------------------------------------------------------------------------|\n");
    printf("+--------------------------------------------------------------------------+\n");
     switch(arrkeys()){
        case 'u':
            choice =(choice+1)%4;
        break;
        case 'd':
            choice -=1;
            if(choice<0){
                choice=3;
            }
        break;
        case 'q':
            switch(choice){
                case 3:
                    sprintf(texto,"you've attacked evil %s ",ename);
                    system("color 4F");
                    Sleep(100);
                    system("color 0F");
                    enehp-=(hero->st-(bad.def));
                    hp -= -(hero->def-(bad.st+rand()%5));
                break;
                case 2:
                    strcpy(texto, "you've frowned              ");
                    enehp-=(hero->sp-(bad.sp+rand()%15));
                    hp -= -(hero->def-(bad.st+rand()%5));
                break;
                case 1:
                    sprintf(texto,"you smile back to the smiley",ename);
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
                    f1 ='X';
                    f2 =' ';
                    f3 =' ';
                    f4 =' ';
                break;
                case 2:
                    f1 =' ';
                    f2 ='X';
                    f3 =' ';
                    f4 =' ';
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
    if(hp>(hero->hp)){
       hp=30;
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
        printf("|| you've defeated the evil %s       |                               |-|\n",ename);
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

char arrkeys(){
    int ch = getch();
    if (ch == 0 || ch == 224){
        switch (_getch ()){
            case 72:
                return 'u';
            break;
            case 77:
                return 'r';
            break;
            case 75:
                return 'l';
            break;
            case 80:
                return 'd';
            break;
            default:
                return 'e';
            }
        }
    if(ch == 13){
        return 'q';
        }
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
void enemy(char *ene, chara *bad, char *ename, int enN){
   char ch[78];
   int n =0;
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
void loadLv(int *nLv,int *enN){
   char ch[7];
   char file_name[25] = "settings.txt";
   FILE *fp;

   fp = fopen(file_name,"r"); // read mode

   if( fp == NULL )
   {
      perror("Error while opening the level file.\n");
      exit(EXIT_FAILURE);
   }
    fgets(ch,sizeof(ch),fp);
        sscanf(ch, "lv: %d", &nLv);
    fgets(ch,sizeof(ch),fp);
        sscanf(ch, "en: %d", &enN);
    fclose(fp);

}

void loadEn(char *enList, int n){
   char ch[15];
   char file_name[25] = "settings.txt";
   int cont=0;
   FILE *fp;

   fp = fopen(file_name,"r"); // read mode

   if( fp == NULL )
   {
      perror("Error while opening the settings file.\n");
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

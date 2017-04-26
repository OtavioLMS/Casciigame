#ifndef _MAP_UTILS_LIB_
#define _MAP_UTILS_LIB_
#include "characters.h"
#include <windows.h>   // WinApi header
#define MAX  23
    typedef struct axys{
        int x;
        int y;
    }pos;

    int checkli(int x, int y, pos *b, int size);
    void posiSet(int x,int y,pos *a);
    void loadMap(pos *a, pos *b, pos *goal,int lv);
    void mapi(pos a, pos *b, pos goal, int size, chara hero);
#endif // _MAP_UTILS_LIB_


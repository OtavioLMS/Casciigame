#ifndef _CHARACTERS_LIB_
#define _CHARACTERS_LIB_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    typedef struct chaar{
        int hp;
        int st;
        int sp;
        int def;
        int xp;
    }chara;

    void loadEn(char *enList, int n);
    void enemy(char *ene, chara *bad, char *ename, int enN);

#endif // _CHARACTERS_LIB_

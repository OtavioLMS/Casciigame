#include "arrkeys.h"

char arrkeys(){
    switch (getch()){
        case 259:
            return 'u';
            break;
        case 261:
            return 'r';
            break;
        case 260:
            return 'l';
            break;
        case 258:
            return 'd';
            break;
        case 10:
            return 'q';
            break;
        case 27:
            return 'x';
            break;
        default:
            return 'e';
    }
}

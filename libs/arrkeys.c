#include "arrkeys.h"

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

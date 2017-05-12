#include "x_system.h"
#ifdef WIN32
    void x_pause(){
        system("pause");
    }
    void x_clear(){
        system("cls");
    }
#else
    void x_pause(){
        printf("press ENTER key to continue...")
        getchar();
    }
    void x_clear(){
        system("clear");
    }
#endif

#include "x_system.h"
#ifdef WIN32
    void x_pause(){
        system("pause");
    }
#else
    void x_pause(){
        printw("press ENTER key to continue...")
        getchar();
    }
#endif

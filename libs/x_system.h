#ifndef _X_SYSTEM_LIB_
#define _X_SYSTEM_LIB_
    #ifdef WIN32
        #include <windows.h>
        #define x_sleep(ms) Sleep(ms)
    #else
        #include <unistd.h>
        #define x_sleep(ms) usleep(ms)
    #endif
    void x_pause();
#endif

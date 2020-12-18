#ifndef __AVALIACAO_TOOLS_INCLUIDO__
#define __AVALIACAO_TOOLS_INCLUIDO__

#include <windows.h>
#include <time.h>

typedef struct
{
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
}stopWatch;

class CStopWatch
{
    private:
        stopWatch timer;
        LARGE_INTEGER frequency;
        double LIToSecs( LARGE_INTEGER & L);
    public:
        CStopWatch();
        void startTimer( );
        void stopTimer( );
        double getElapsedTime();
};

#endif

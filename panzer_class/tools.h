#ifndef __SENTA_A_PUA_TOOLS_INCLUIDO__
#define __SENTA_A_PUA_TOOLS_INCLUIDO__

#include <math.h>
#include <windows.h>

void limiteAngulo(float * angulo);

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

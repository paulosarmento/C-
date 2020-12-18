#include "tools.h"

void limiteAngulo(float * angulo)
{
    if(*angulo < 0.0f)
        *angulo += 360.0f;
    else if(*angulo >= 360)
        *angulo -= 360.0f;
};

//CLASSE CSTOPWATCH (CPLUS.ABOUT.COM) (PARA FIXAR O FRAMERATE)
double CStopWatch::LIToSecs( LARGE_INTEGER & L)
{
	return ((double)L.QuadPart /(double)frequency.QuadPart);
}

CStopWatch::CStopWatch()
{
	timer.start.QuadPart=0;
	timer.stop.QuadPart=0;
	QueryPerformanceFrequency( &frequency );
}

void CStopWatch::startTimer( )
{
    QueryPerformanceCounter(&timer.start);
}

void CStopWatch::stopTimer( )
{
    QueryPerformanceCounter(&timer.stop);
}

double CStopWatch::getElapsedTime()
{
	LARGE_INTEGER time;
	time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;
    return LIToSecs( time) ;
}


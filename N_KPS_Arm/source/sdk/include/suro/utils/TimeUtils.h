#ifndef __TIME_UTILS_HEADER__
#define __TIME_UTILS_HEADER__

#include <stdio.h>
#include <sys/time.h>

class TimeUtils
{
private:
    /* data */
public:
    static long GetTimeStampMs();
    
}; 

#endif
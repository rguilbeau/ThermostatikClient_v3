#ifndef T_DATE_H
#define T_DATE_H

#include <Arduino.h>

class Date {

public:
    Date();
    Date(long time);

    int findDayIndex();
    unsigned short findTimeSinceMidnight();

    bool before(Date date);

    long getTimeMin();

    String toShortFormat();
    String toLongFormat();

    static int timezone;
    static bool summerTime;
    static bool timeInitialized;
private:
    long mTime;
    bool mNow;
    long getTime();

    static const String sDaysOfWeek[7];
    static const String sDaysOfWeekShort[7];
    static const String sMonthsOfYear[12];

};

#endif
#include "Date.h"

int Date::timezone = 0;
bool Date::summerTime = false;
bool Date::timeInitialized = false;

const String Date::sDaysOfWeek[] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
const String Date::sMonthsOfYear[] = {"janvier", "fevrier", "mars", "avril", "mai", "juin", "juillet", "aout", "septembre", "octobre", "novembre", "decembre"};

Date::Date() {
    mTime = 0;
    mNow = true;
}

Date::Date(long time) {
    mTime = time;
    mNow = false;
}

long Date::getTime() {
    long timestamp = mTime;
    if(mNow) {
        timestamp = time(nullptr);
    }
    return timestamp;
}

long Date::getLocalTime() {
    return getTime() + timezone + (summerTime ? 3600 : 0);
}

long Date::getTimeMin() {
    return (long) (getLocalTime() / 60);
}

bool Date::before(Date date) {
    long thisTime = getLocalTime();
    long checkDate = date.getLocalTime();

    return thisTime < checkDate;
}

String Date::toShortFormat() {
    time_t s = this->getLocalTime();
    struct tm* t = localtime(&s);

    String dayOfWeek = Date::sDaysOfWeek[t->tm_wday];
    String monthDay = t->tm_mday < 10 ? F("0") + String(t->tm_mday) : String(t->tm_mday);
    String month = Date::sMonthsOfYear[t->tm_mon];
    String hours = t->tm_hour < 10 ? F("0") + String(t->tm_hour) : String(t->tm_hour);
    String minutes = t->tm_min < 10 ? F("0") + String(t->tm_min) : String(t->tm_min);

    return dayOfWeek.substring(0, 3) + F(". ") + monthDay + F(" ") + month.substring(0, 3) + F(".  ") + hours + F(":") + minutes;
}

String Date::toLongFormat() {
    time_t s = this->getLocalTime();
    struct tm* t = localtime(&s);

    String dayOfWeek = Date::sDaysOfWeek[t->tm_wday];
    String monthDay = t->tm_mday < 10 ? F("0") + String(t->tm_mday) : String(t->tm_mday);
    String month = Date::sMonthsOfYear[t->tm_mon];
    String hours = t->tm_hour < 10 ? F("0") + String(t->tm_hour) : String(t->tm_hour);
    String minutes = t->tm_min < 10 ? F("0") + String(t->tm_min) : String(t->tm_min);

    return dayOfWeek + F(" ") + monthDay + F(" ") + month + F("  ") + hours + F(":") + minutes;
}

unsigned short Date::findDayIndex() {
    time_t s = this->getLocalTime();
    struct tm* t = localtime(&s);

    short dayIndex = t->tm_wday;
    // start monday
    dayIndex -= 1;
    if(dayIndex == -1) {
        dayIndex = 6;
    }

    // 0-> monday / 6-> sunday
    return dayIndex;
}

unsigned short Date::findTimeSinceMidnight() {
    time_t s = this->getLocalTime();
    struct tm* t = localtime(&s);
    return (t->tm_hour * 60) + t->tm_min;
}

unsigned short Date::findTimeSinceStartWeek() {
    return findTimeSinceMidnight() + (findDayIndex() * 1440);
}
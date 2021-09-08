#ifndef EDATE_H
#define EDATE_H

#include <string>

enum class eMonth {
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

namespace eMonthHelper {
    std::string shortName(const eMonth m);
    int days(const eMonth m);
    eMonth nextMonth(const eMonth m, bool& nextYear);
}

class eDate {
public:
    eDate(const int day, const eMonth month, const int year);

    std::string shortString() const;
    void nextDay(bool& nextMonth, bool& nextYear);
private:
    int mDay;
    eMonth mMonth;
    int mYear;
};

#endif // EDATE_H

#ifndef EPOPULATIONDATA_H
#define EPOPULATIONDATA_H

class ePopulationData {
    friend class eGameBoard;
public:
    ePopulationData();

    void incVacancies(const int v);
    void incSettlers(const int s);
    void incLeft(const int s);
    void nextMonth();

    int population() const { return mPop; }
    int vacancies() const { return mVacs; }
    int settlers() const { return mSettlers; }
    int arrived() const { return mArrivedThisMonth; }
    int left() const { return mLeftThisMonth; }
private:
    void incPopulation(const int p);
private:
    int mPop{0};
    int mVacs{0};
    int mSettlers{0};
    int mArrivedThisMonth{0};
    int mLeftThisMonth{0};
};

#endif // EPOPULATIONDATA_H

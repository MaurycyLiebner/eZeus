#ifndef EPOPULATIONDATA_H
#define EPOPULATIONDATA_H

class ePopulationData {
public:
    ePopulationData();

    void incPopulation(const int p);
    void incVacancies(const int v);

    int population() const { return mPop; }
    int vacancies() const { return mVacs; }
private:
    int mPop{0};
    int mVacs{0};
};

#endif // EPOPULATIONDATA_H

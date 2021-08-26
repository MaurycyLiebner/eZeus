#ifndef EEMPLOYMENTDATA_H
#define EEMPLOYMENTDATA_H

class ePopulationData;

class eEmploymentData {
public:
    eEmploymentData(const ePopulationData& popData);

    void incTotalJobVacancies(const int v);

    int employable() const;
    int employed() const;
    int pensions() const;
    int unemployed() const;
    int freeJobVacancies() const;
    int totalJobVacancies() const;

    double employedFraction() const;
private:
    const ePopulationData& mPopData;
    int mTotalJobVacs{0};
};

#endif // EEMPLOYMENTDATA_H

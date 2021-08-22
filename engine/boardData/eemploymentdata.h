#ifndef EEMPLOYMENTDATA_H
#define EEMPLOYMENTDATA_H

class ePopulationData;

class eEmploymentData {
public:
    eEmploymentData(const ePopulationData& popData);

    void incEmployed(const int p);

    int employed() const { return mEmployed; }

    int pensions() const;
    int unemployed() const;
    int jobVacancies() const;
private:
    const ePopulationData& mPopData;
    int mEmployed{0};
};

#endif // EEMPLOYMENTDATA_H

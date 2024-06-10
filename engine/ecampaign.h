#ifndef ECAMPAIGN_H
#define ECAMPAIGN_H

#include "egameboard.h"

enum class eEpisodeType {
    parentCity,
    colony
};

enum class eEpisodeGoalType {
    population,
    treasury,
    sanctuary,
    support,
    quest,
    slay,
    rule,
    housing,
    setAsideGoods
};

struct eEpisodeGoal {
    eEpisodeGoalType fType;
    int fEnumInt;
    int fRequiredCount;
    int fStatusCount = 0;

    void read(eReadStream& src) {
        src >> fType;
        src >> fEnumInt;
        src >> fRequiredCount;
        src >> fStatusCount;
    }

    void write(eWriteStream& dst) const {
        dst << fType;
        dst << fEnumInt;
        dst << fRequiredCount;
        dst << fStatusCount;
    }

    bool met() const {
        return fStatusCount >= fRequiredCount;
    }
};

struct eEpisode {
    void read(eReadStream& src) {
        {
            int nfg;
            src >> nfg;
            for(int i = 0; i < nfg; i++) {
                eGodType g;
                src >> g;
                fFriendlyGods.push_back(g);
            }
        }
        {
            int nhg;
            src >> nhg;
            for(int i = 0; i < nhg; i++) {
                eGodType g;
                src >> g;
                fHostileGods.push_back(g);
            }
        }
        {
            int nevs;
            src >> nevs;
            for(int i = 0; i < nevs; i++) {
                eGameEventType type;
                src >> type;
                const auto branch = eGameEventBranch::root;
                const auto e = eGameEvent::sCreate(type, branch, fFakeBoard);
                e->read(src);
                fEvents.push_back(e);
            }
        }
        {
            int ng;
            src >> ng;
            for(int i = 0; i < ng; i++) {
                const auto g = std::make_shared<eEpisodeGoal>();
                g->read(src);
                fGoals.push_back(g);
            }
        }
        fAvailableBuildings.read(src);
    }

    void write(eWriteStream& dst) const {
        dst << fFriendlyGods.size();
        for(const auto g : fFriendlyGods) {
            dst << g;
        }
        dst << fHostileGods.size();
        for(const auto g : fHostileGods) {
            dst << g;
        }
        dst << fEvents.size();
        for(const auto& e : fEvents) {
            dst << e->type();
            e->write(dst);
        }
        dst << fGoals.size();
        for(const auto& g : fGoals) {
            g->write(dst);
        }
        fAvailableBuildings.write(dst);
    }

    std::string fTitle;
    std::string fIntroduction;
    std::string fComplete;

    std::vector<eGodType> fFriendlyGods;
    std::vector<eGodType> fHostileGods;

    std::vector<stdsptr<eGameEvent>> fEvents;
    std::vector<stdsptr<eEpisodeGoal>> fGoals;

    eAvailableBuildings fAvailableBuildings;

    eGameBoard fFakeBoard;
};

struct eParentCityEpisode : public eEpisode {
};

struct eColonyEpisode : public eEpisode {
    std::string fSelection;
};

struct eCampaignGlossary {
    std::string fFolderName;
    int fBitmap = 0;
    std::string fTitle;
    std::string fIntroduction;
    std::string fComplete;
};

class eCampaign {
public:
    eCampaign();

    void initialize(const std::string& title);

    void setInitialFunds(const int f) { mInitialFunds = f; }
    void setStartDate(const eDate& d) { mStartDate = d; }

    void setBitmap(const int b) { mBitmap = b; }

    using eMap = std::map<std::string, std::string>;
    static bool sLoadStrings(const std::string& path, eMap& map);
    bool loadStrings(const std::string& path);
    bool writeStrings(const std::string& path) const;

    eWorldBoard& worldBoard() { return mWorldBoard; }
    eGameBoard& parentCityBoard()
    { return *mParentBoard; }
    eGameBoard& colonyBoard(const int id)
    { return *mColonyBoards[id]; }

    static bool sReadGlossary(const std::string& name,
                              eCampaignGlossary& glossary);
    void read(eReadStream& src);
    void write(eWriteStream& dst) const;

    bool load(const std::string& name);
    bool save() const;
private:
    int mBitmap = 0;
    std::string mTitle;
    std::string mIntroduction;
    std::string mComplete;

    int mCurrentEpisode = 0;

    int mInitialFunds = 5000;

    eDate mStartDate;

    eWorldBoard mWorldBoard;
    stdsptr<eGameBoard> mParentBoard;
    std::vector<stdsptr<eGameBoard>> mColonyBoards;

    std::vector<eEpisodeType> mEpisodes;

    std::vector<stdsptr<eParentCityEpisode>> mParentCityEpisodes;
    std::vector<stdsptr<eColonyEpisode>> mColonyEpisodes;
    std::vector<int> mPlayedColonyEpisodes;
};

#endif // ECAMPAIGN_H

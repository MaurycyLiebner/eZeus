#ifndef ECAMPAIGN_H
#define ECAMPAIGN_H

#include "egameboard.h"

#include "eepisodegoal.h"

enum class eEpisodeType {
    parentCity,
    colony
};

struct eEpisode {
    virtual void read(eReadStream& src) {
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
                const auto e = eGameEvent::sCreate(type, branch, fBoard);
                e->setGameBoard(fBoard);
                e->setWorldBoard(fWorldBoard);
                e->read(src);
                fEvents.push_back(e);
            }
        }
        {
            int ng;
            src >> ng;
            for(int i = 0; i < ng; i++) {
                const auto g = std::make_shared<eEpisodeGoal>();
                g->read(fWorldBoard, src);
                fGoals.push_back(g);
            }
        }
        fAvailableBuildings.read(src);
    }

    virtual void write(eWriteStream& dst) const {
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

    bool availableBuilding(const eBuildingType type,
                           const int id = -1) const {
        switch(type) {
        case eBuildingType::chariotVendor:
        case eBuildingType::chariotFactory: {
            if(!fAtlantean) return false;
        } break;
        case eBuildingType::horseTrainer: {
            if(fAtlantean) return false;
        } break;
        default:
            break;
        }

        return fAvailableBuildings.available(type, id);
    }

    void clear() {
        fFriendlyGods.clear();
        fHostileGods.clear();
        fEvents.clear();
        fGoals.clear();
        fAvailableBuildings = eAvailableBuildings();
    }

    eGameBoard* fBoard = nullptr;
    eWorldBoard* fWorldBoard = nullptr;
    bool fAtlantean = true;

    std::string fTitle;
    std::string fIntroduction;
    std::string fComplete;

    std::vector<eGodType> fFriendlyGods;
    std::vector<eGodType> fHostileGods;

    std::vector<stdsptr<eGameEvent>> fEvents;
    std::vector<stdsptr<eEpisodeGoal>> fGoals;

    eAvailableBuildings fAvailableBuildings;
};

struct eParentCityEpisode : public eEpisode {
    void read(eReadStream& src) override {
        eEpisode::read(src);
        src >> fNextEpisode;
    }

    void write(eWriteStream& dst) const override {
        eEpisode::write(dst);
        dst << fNextEpisode;
    }

    eEpisodeType fNextEpisode{eEpisodeType::parentCity};
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
    bool loadStrings();
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

    void startEpisode(const eEpisodeType type, const int cid = -1);

    bool atlantean() const { return mAtlantean; }
    void setAtlantean(const bool a);

    std::vector<int> colonyEpisodesLeft() const;

    using eParentCityEpisodes = std::vector<stdsptr<eParentCityEpisode>>;
    eParentCityEpisodes& parentCityEpisodes()
    { return mParentCityEpisodes; }
    stdsptr<eParentCityEpisode> addParentCityEpisode();
    stdsptr<eParentCityEpisode> insertParentCityEpisode(const int id);
    void deleteParentCityEpisode(const int id);
    void setVictoryParentCityEpisode(const int id);
    void copyParentCityEpisodeSettings(const int from, const int to);
    void copyParentCityEpisodeSettings(eParentCityEpisode* const from,
                                       eParentCityEpisode* const to);

    const std::string& titleText() const { return mTitle; }
    const std::string& introductionText() const { return mIntroduction; }
    const std::string& completeText() const { return mComplete; }
private:
    int mBitmap = 0;
    std::string mTitle;
    std::string mIntroduction;
    std::string mComplete;

    bool mAtlantean = true;

    int mCurrentEpisode = 0;

    int mInitialFunds = 5000;

    eDate mStartDate;

    eWorldBoard mWorldBoard;
    stdsptr<eGameBoard> mParentBoard;
    std::vector<stdsptr<eGameBoard>> mColonyBoards;

    std::vector<stdsptr<eParentCityEpisode>> mParentCityEpisodes;
    std::vector<stdsptr<eColonyEpisode>> mColonyEpisodes;
    std::vector<int> mPlayedColonyEpisodes;
};

#endif // ECAMPAIGN_H

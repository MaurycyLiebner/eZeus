#include "ecampaign.h"

#include <fstream>

#include <filesystem>
#include <regex>

#include "evectorhelpers.h"

eCampaign::eCampaign() {

}

void eCampaign::initialize(const std::string& name) {
    mName = name;

    mParentBoard = std::make_shared<eGameBoard>();
    mParentBoard->initialize(100, 100);
    mParentBoard->setWorldBoard(&mWorldBoard);

    for(int i = 0; i < 4; i++) {
        auto& board = mColonyBoards.emplace_back();
        board = std::make_shared<eGameBoard>();
        board->initialize(100, 100);
        board->setWorldBoard(&mWorldBoard);

        const auto e = std::make_shared<eColonyEpisode>();
        e->fBoard = board.get();
        e->fWorldBoard = &mWorldBoard;
        mColonyEpisodes.push_back(e);
    }

    addParentCityEpisode();
}

bool eCampaign::sLoadStrings(const std::string& path, eMap& map) {
    std::ifstream file(path);
    if(!file.good()) {
        printf("File missing %s\n", path.c_str());
        return false;
    }
    std::string line;
    std::string key;
    std::string value;
    while(std::getline(file, line)) {
        if(line.empty()) continue;
        if(line.front() == '\r') continue;
        if(line.front() == '\t') continue;
        if(line.front() == ';') continue;
        if(key.empty()) {
            const auto keyEnd1 = line.find(' ');
            const auto keyEnd2 = line.find('=');
            const auto keyEnd = std::min(keyEnd1, keyEnd2);
            if(keyEnd == std::string::npos) continue;
            key = line.substr(0, keyEnd);
        }

        unsigned long valueStart = 0;
        if(value.empty()) {
            valueStart = line.find('"');
            if(valueStart == std::string::npos) continue;
            valueStart += 1;
        }
        bool foundEnd = true;
        auto valueEnd = line.find('"', valueStart);
        if(valueEnd == std::string::npos) {
            valueEnd = line.size();
            foundEnd = false;
        }
        const auto valueLen = valueEnd - valueStart;
        value = value + line.substr(valueStart, valueLen);

        if(foundEnd) {
            value = std::regex_replace(value, std::regex("@L"), "\n");
            value = std::regex_replace(value, std::regex("@P"), "\n");
            map[key] = value;
            key = "";
            value = "";
        }
    }
    return true;
}

bool eCampaign::loadStrings() {
    const auto baseDir = "../Adventures/";
    const auto aDir = baseDir + mName + "/";
    const auto txtFile = aDir + mName + ".txt";
    std::map<std::string, std::string> map;
    const bool r = sLoadStrings(txtFile, map);
    if(!r) return false;

    mTitle = map["Adventure_Title"];
    mIntroduction = map["Adventure_Introduction"];
    mComplete = map["Adventure_Complete"];

    int id = 1;
    for(auto& e : mParentCityEpisodes) {
        const auto ids = std::to_string(id++);
        const auto titleK = "Parent_Episode_" + ids + "_Title";
        const auto introK = "Parent_Episode_" + ids + "_Introduction";
        const auto completeK = "Parent_Episode_" + ids + "_Complete";
        e->fTitle = map[titleK];
        e->fIntroduction = map[introK];
        e->fComplete = map[completeK];
    }
    id = 1;
    for(auto& e : mColonyEpisodes) {
        const auto ids = std::to_string(id++);
        const auto titleK = "Colony_" + ids + "_Title";
        const auto introK = "Colony_" + ids + "_Introduction";
        const auto completeK = "Colony_" + ids + "_Complete";
        const auto selectionK = "Colony_" + ids + "_Selection";
        e->fTitle = map[titleK];
        e->fIntroduction = map[introK];
        e->fComplete = map[completeK];
        e->fSelection = map[selectionK];
    }
    return true;
}

bool eCampaign::writeStrings(const std::string& path) const {
    std::ofstream file(path);
    if(!file.good()) {
        printf("File missing %s\n", path.c_str());
        return false;
    }

    const auto titleStr = mTitle.empty() ? "INSERT TEXT HERE" : mTitle;
    file << "Adventure_Title=\"" + titleStr + "\"\n";
    file << "Adventure_Introduction=\"" + mIntroduction + "\"\n";
    file << "Adventure_Complete=\"" + mComplete + "\"\n";
    file << '\n';
    for(int i = 1; i < 11; i++) {
        const eParentCityEpisode* e = nullptr;
        const int iMax = mParentCityEpisodes.size();
        if(i < iMax) {
            e = mParentCityEpisodes[i].get();
        }
        const auto titleStr = e ? e->fTitle : "";
        const auto introStr = e ? e->fIntroduction : "";
        const auto completeStr = e ? e->fComplete : "";
        const auto is = std::to_string(i);
        file << "Parent_Episode_" + is + "_Title=\"" + titleStr + "\"\n";
        file << "Parent_Episode_" + is + "_Introduction=\"" + introStr + "\"\n";
        file << "Parent_Episode_" + is + "_Complete=\"" + completeStr + "\"\n";
    }
    file << '\n';
    for(int i = 1; i < 5; i++) {
        const eColonyEpisode* e = nullptr;
        const int iMax = mColonyEpisodes.size();
        if(i < iMax) {
            e = mColonyEpisodes[i].get();
        }
        const auto titleStr = e ? e->fTitle : "";
        const auto introStr = e ? e->fIntroduction : "";
        const auto completeStr = e ? e->fComplete : "";
        const auto selectionStr = e ? e->fSelection : "";
        const auto is = std::to_string(i);
        file << "Colony_" + is + "_Title=\"" + titleStr + "\"\n";
        file << "Colony_" + is + "_Introduction=\"" + introStr + "\"\n";
        file << "Colony_" + is + "_Complete=\"" + completeStr + "\"\n";
        file << "Colony_" + is + "_Selection=\"" + selectionStr + "\"\n";
    }
    return true;
}

bool eCampaign::sReadGlossary(const std::string& name,
                              eCampaignGlossary& glossary) {
    const auto baseDir = "../Adventures/";
    const auto aDir = baseDir + name + "/";
    const auto txtFile = aDir + name + ".txt";
    std::map<std::string, std::string> map;
    const bool r = sLoadStrings(txtFile, map);
    if(!r) return false;
    glossary.fFolderName = name;
    glossary.fTitle = map["Adventure_Title"];
    glossary.fIntroduction = map["Adventure_Introduction"];
    glossary.fComplete = map["Adventure_Complete"];

    const auto pakFile = aDir + name + ".epak";
    const auto file = SDL_RWFromFile(pakFile.c_str(), "r+b");
    if(!file) return false;
    eReadStream src(file);
    src >> glossary.fBitmap;
    SDL_RWclose(file);
    return true;
}

void eCampaign::read(eReadStream& src) {
    src >> mBitmap;
    src >> mName;
    src >> mAtlantean;
    src >> mCurrentParentEpisode;
    src >> mCurrentColonyEpisode;
    src >> mCurrentEpisodeType;
    src >> mInitialFunds;
    mDate.read(src);
    src >> mDifficulty;
    mWorldBoard.read(src);
    mParentBoard = std::make_shared<eGameBoard>();
    mParentBoard->setWorldBoard(&mWorldBoard);
    mParentBoard->read(src);
    {
        int nc;
        src >> nc;
        for(int i = 0; i < nc; i++) {
            auto& b = mColonyBoards.emplace_back();
            b = std::make_shared<eGameBoard>();
            b->setWorldBoard(&mWorldBoard);
            b->read(src);
        }
    }

    {
        int ne;
        src >> ne;
        for(int i = 0; i < ne; i++) {
            const auto e = std::make_shared<eParentCityEpisode>();
            e->fBoard = mParentBoard.get();
            e->fWorldBoard = &mWorldBoard;
            e->read(src);
            mParentCityEpisodes.push_back(e);
        }
    }

    {
        int ne;
        src >> ne;
        for(int i = 0; i < ne; i++) {
            const auto e = std::make_shared<eColonyEpisode>();
            e->fBoard = mColonyBoards[i].get();
            e->fWorldBoard = &mWorldBoard;
            e->read(src);
            mColonyEpisodes.push_back(e);
        }
    }

    {
        int ne;
        src >> ne;
        for(int i = 0; i < ne; i++) {
            int e;
            src >> e;
            mPlayedColonyEpisodes.push_back(e);
        }
    }
}

void eCampaign::write(eWriteStream& dst) const {
    dst << mBitmap;
    dst << mName;
    dst << mAtlantean;
    dst << mCurrentParentEpisode;
    dst << mCurrentColonyEpisode;
    dst << mCurrentEpisodeType;
    dst << mInitialFunds;
    mDate.write(dst);
    dst << mDifficulty;
    mWorldBoard.write(dst);
    mParentBoard->write(dst);

    dst << mColonyBoards.size();
    for(const auto& b : mColonyBoards) {
        b->write(dst);
    }

    dst << mParentCityEpisodes.size();
    for(const auto& e : mParentCityEpisodes) {
        e->write(dst);
    }

    dst << mColonyEpisodes.size();
    for(const auto& e : mColonyEpisodes) {
        e->write(dst);
    }

    dst << mPlayedColonyEpisodes.size();
    for(const int e : mPlayedColonyEpisodes) {
        dst << e;
    }
}

bool eCampaign::load(const std::string& name) {
    mName = name;
    const auto baseDir = "../Adventures/";
    const auto aDir = baseDir + mName + "/";

    const auto pakFile = aDir + mName + ".epak";
    const auto file = SDL_RWFromFile(pakFile.c_str(), "r+b");
    if(!file) return false;
    eReadStream src(file);
    read(src);
    src.handlePostFuncs();
    SDL_RWclose(file);

    const auto txtFile = aDir + mName + ".txt";
    loadStrings();
    return true;
}

bool eCampaign::save() const {
    const auto baseDir = "../Adventures/";
    const auto aDir = baseDir + mName + "/";
    std::filesystem::create_directories(aDir);
    const auto txtFile = aDir + mName + ".txt";
    if(!std::filesystem::exists(txtFile)) writeStrings(txtFile);

    const auto pakFile = aDir + mName + ".epak";
    const auto file = SDL_RWFromFile(pakFile.c_str(), "w+b");
    if(!file) return false;
    eWriteStream dst(file);
    write(dst);
    SDL_RWclose(file);
    return true;
}

eEpisode* eCampaign::currentEpisode() {
    if(mCurrentEpisodeType == eEpisodeType::colony) {
        return mColonyEpisodes[mCurrentColonyEpisode].get();
    } else {
        return mParentCityEpisodes[mCurrentParentEpisode].get();
    }
}

void eCampaign::setCurrentColonyEpisode(const int e) {
    mCurrentColonyEpisode = e;
}

void eCampaign::startEpisode() {
    if(mCurrentEpisodeType == eEpisodeType::colony) {
        mPlayedColonyEpisodes.push_back(mCurrentColonyEpisode);
        mWorldBoard.activateColony(mCurrentColonyEpisode);
        mWorldBoard.setColonyAsCurrentCity(mCurrentColonyEpisode);
    } else { // parentCity
        mWorldBoard.setParentAsCurrentCity();
    }
    const auto e = currentEpisode();
    e->fStartDate = mDate;
    const auto board = e->fBoard;
    board->startEpisode(e);
}

void eCampaign::episodeFinished() {
    const auto e = currentEpisode();
    const auto board = e->fBoard;
    mDate = board->date();
    if(mCurrentEpisodeType == eEpisodeType::parentCity) {
        const auto ee = static_cast<eParentCityEpisode*>(e);
        auto n = ee->fNextEpisode;
        if(n == eEpisodeType::parentCity) {
            mCurrentParentEpisode++;
        } else {
            const auto rem  = remainingColonies();
            if(rem.size() == 0) {
                mCurrentParentEpisode++;
                n = eEpisodeType::parentCity;
            }
        }
        mCurrentEpisodeType = n;
    } else {
        mCurrentParentEpisode++;
        mCurrentEpisodeType = eEpisodeType::parentCity;
    }
}

bool eCampaign::finished() const {
    const int n = mParentCityEpisodes.size();
    return mCurrentParentEpisode >= n;
}

std::vector<eColonyEpisode*> eCampaign::remainingColonies() const {
    std::vector<eColonyEpisode*> result;
    for(int i = 0; i < 4; i++) {
        const bool p = eVectorHelpers::contains(mPlayedColonyEpisodes, i);
        if(p) continue;
        const auto& ep = mColonyEpisodes[i];
        if(!ep->fCity) continue;
        result.push_back(ep.get());
    }
    return result;
}

void eCampaign::setAtlantean(const bool a) {
    mAtlantean = a;
    for(const auto& e : mParentCityEpisodes) {
        e->fAtlantean = a;
    }
    for(const auto& e : mColonyEpisodes) {
        e->fAtlantean = a;
    }
    mParentBoard->setPoseidonMode(a);
    for(const auto& b : mColonyBoards) {
        b->setPoseidonMode(a);
    }
}

std::vector<int> eCampaign::colonyEpisodesLeft() const {
    std::vector<int> result;
    const int iMax = mColonyEpisodes.size();
    for(int i = 0; i < iMax; i++) {
        const bool p = eVectorHelpers::contains(mPlayedColonyEpisodes, i);
        if(p) continue;
        result.push_back(i);
    }
    return result;
}

stdsptr<eParentCityEpisode> eCampaign::addParentCityEpisode() {
    const auto e = std::make_shared<eParentCityEpisode>();
    e->fBoard = mParentBoard.get();
    e->fWorldBoard = &mWorldBoard;
    mParentCityEpisodes.push_back(e);
    return e;
}

stdsptr<eParentCityEpisode> eCampaign::insertParentCityEpisode(const int id) {
    const auto e = std::make_shared<eParentCityEpisode>();
    mParentCityEpisodes.insert(mParentCityEpisodes.begin() + id, e);
    return e;
}

void eCampaign::deleteParentCityEpisode(const int id) {
    mParentCityEpisodes.erase(mParentCityEpisodes.begin() + id);
}

void eCampaign::setVictoryParentCityEpisode(const int id) {
    for(int i = mParentCityEpisodes.size() - 1; i > id; i--) {
        deleteParentCityEpisode(id);
    }
}

void eCampaign::copyParentCityEpisodeSettings(const int from, const int to) {
    const auto f = mParentCityEpisodes[from];
    const auto t = mParentCityEpisodes[to];
    copyEpisodeSettings(f.get(), t.get());
}

void eCampaign::copyEpisodeSettings(eEpisode* const from,
                                    eEpisode* const to) {
    to->clear();
    const size_t size = 1000000;
    void* mem = malloc(size);
    {
        mWorldBoard.setIOIDs();
        const auto file = SDL_RWFromMem(mem, size);
        eWriteStream dst(file);
        from->write(dst);
    }
    {
        const auto file = SDL_RWFromMem(mem, size);
        eReadStream src(file);
        to->read(src);
        src.handlePostFuncs();
    }

    free(mem);
}

void eCampaign::setDifficulty(const eDifficulty d) {
    mDifficulty = d;
    mParentBoard->setDifficulty(d);
    for(const auto& b : mColonyBoards) {
        b->setDifficulty(d);
    }
}

void eCampaign::setEditorMode(const bool e) {
    mWorldBoard.setEditorMode(e);
    mParentBoard->setEditorMode(e);
    for(const auto& c : mColonyBoards) {
        c->setEditorMode(e);
    }
}

void eCampaign::copyColonyEpisodeSettings(const int from, const int to) {
    const auto f = mColonyEpisodes[from];
    const auto t = mColonyEpisodes[to];
    copyEpisodeSettings(f.get(), t.get());
}

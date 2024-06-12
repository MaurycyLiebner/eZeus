#include "ecampaign.h"

#include <fstream>

#include <filesystem>
#include <regex>

#include "evectorhelpers.h"

eCampaign::eCampaign() {

}

void eCampaign::initialize(const std::string& title) {
    mTitle = title;

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
    const auto aDir = baseDir + mTitle + "/";
    const auto txtFile = aDir + mTitle + ".txt";
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
    src >> mAtlantean;
    src >> mInitialFunds;
    mStartDate.read(src);
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
    dst << mAtlantean;
    dst << mInitialFunds;
    mStartDate.write(dst);
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
    mTitle = name;
    const auto baseDir = "../Adventures/";
    const auto aDir = baseDir + mTitle + "/";
    const auto txtFile = aDir + mTitle + ".txt";
    loadStrings();

    const auto pakFile = aDir + mTitle + ".epak";
    const auto file = SDL_RWFromFile(pakFile.c_str(), "r+b");
    if(!file) return false;
    eReadStream src(file);
    read(src);
    SDL_RWclose(file);
    return true;
}

bool eCampaign::save() const {
    const auto baseDir = "../Adventures/";
    const auto aDir = baseDir + mTitle + "/";
    std::filesystem::create_directories(aDir);
    const auto txtFile = aDir + mTitle + ".txt";
    if(!std::filesystem::exists(txtFile)) writeStrings(txtFile);

    const auto pakFile = aDir + mTitle + ".epak";
    const auto file = SDL_RWFromFile(pakFile.c_str(), "w+b");
    if(!file) return false;
    eWriteStream dst(file);
    write(dst);
    SDL_RWclose(file);
    return true;
}

void eCampaign::startEpisode(const eEpisodeType type, const int cid) {
    if(type == eEpisodeType::colony) {
        mPlayedColonyEpisodes.push_back(cid);
        mWorldBoard.activateColony(cid);
        mWorldBoard.setColonyAsCurrentCity(cid);
    } else { // parentCity
        mWorldBoard.setParentAsCurrentCity();
    }
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
    copyParentCityEpisodeSettings(f.get(), t.get());
}

void eCampaign::copyParentCityEpisodeSettings(eParentCityEpisode* const from,
                                              eParentCityEpisode* const to) {
    to->clear();
    const size_t size = 1000000;
    void* mem = malloc(size);
    {
        const auto file = SDL_RWFromMem(mem, size);
        eWriteStream dst(file);
        from->write(dst);
    }
    {
        const auto file = SDL_RWFromMem(mem, size);
        eReadStream src(file);
        to->read(src);
    }

    free(mem);
}

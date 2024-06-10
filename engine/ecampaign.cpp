#include "ecampaign.h"

#include <fstream>

#include <filesystem>

eCampaign::eCampaign() {

}

void eCampaign::initialize(const std::string& title) {
    mTitle = title;

    mParentBoard = std::make_shared<eGameBoard>();
    mParentBoard->initialize(100, 100);

    for(int i = 0; i < 4; i++) {
        auto& board = mColonyBoards.emplace_back();
        board = std::make_shared<eGameBoard>();
        board->initialize(100, 100);
    }
}

bool eCampaign::sLoadStrings(const std::string& path, eMap& map) {
    std::ifstream file(path);
    if(!file.good()) {
        printf("File missing %s\n", path.c_str());
        return false;
    }
    std::string str;
    while(std::getline(file, str)) {
        if(str.empty()) continue;
        if(str.front() == '\r') continue;
        if(str.front() == '\t') continue;
        if(str.front() == ';') continue;
        const auto keyEnd1 = str.find(' ');
        const auto keyEnd2 = str.find('=');
        const auto keyEnd = std::min(keyEnd1, keyEnd2);
        if(keyEnd == std::string::npos) continue;
        const auto key = str.substr(0, keyEnd);

        const auto valueStart = str.find('"');
        if(valueStart == std::string::npos) continue;
        const auto valueEnd = str.find('"', valueStart + 1);
        const auto valueLen = valueEnd - valueStart;
        const auto value = str.substr(valueStart + 1, valueLen - 1);

        map[key] = value;
    }
    return true;
}

bool eCampaign::loadStrings(const std::string& path) {
    std::map<std::string, std::string> map;
    const bool r = sLoadStrings(path, map);
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
    src >> mInitialFunds;
    mStartDate.read(src);
    mWorldBoard.read(src);
    mParentBoard = std::make_shared<eGameBoard>();
    mParentBoard->read(src);
    {
        int nc;
        src >> nc;
        for(int i = 0; i < nc; i++) {
            auto& b = mColonyBoards.emplace_back();
            b = std::make_shared<eGameBoard>();
            b->read(src);
        }
    }

    {
        int ne;
        src >> ne;
        for(int i = 0; i < ne; i++) {
            eEpisodeType e;
            src >> e;
            mEpisodes.push_back(e);
        }
    }

    {
        int ne;
        src >> ne;
        for(int i = 0; i < ne; i++) {
            const auto e = std::make_shared<eParentCityEpisode>();
            e->read(src);
            mParentCityEpisodes.push_back(e);
        }
    }

    {
        int ne;
        src >> ne;
        for(int i = 0; i < ne; i++) {
            const auto e = std::make_shared<eColonyEpisode>();
            e->read(src);
            mColonyEpisodes.push_back(e);
        }
    }
}

void eCampaign::write(eWriteStream& dst) const {
    dst << mBitmap;
    dst << mInitialFunds;
    mStartDate.write(dst);
    mWorldBoard.write(dst);
    mParentBoard->write(dst);

    dst << mColonyBoards.size();
    for(const auto& b : mColonyBoards) {
        b->write(dst);
    }

    dst << mEpisodes.size();
    for(const auto e : mEpisodes) {
        dst << e;
    }

    dst << mParentCityEpisodes.size();
    for(const auto& e : mParentCityEpisodes) {
        e->write(dst);
    }

    dst << mColonyEpisodes.size();
    for(const auto& e : mColonyEpisodes) {
        e->write(dst);
    }
}

bool eCampaign::load(const std::string& name) {
    mTitle = name;
    const auto baseDir = "../Adventures/";
    const auto aDir = baseDir + mTitle + "/";
    const auto txtFile = aDir + mTitle + ".txt";
    loadStrings(txtFile);

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

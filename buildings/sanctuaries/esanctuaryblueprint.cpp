#include "esanctuaryblueprint.h"

#include <fstream>
#include <regex>

eSanctBlueprints eSanctBlueprints::instance;

bool loadLineBP(const int x,
                std::vector<eSanctEle>& bp,
                const std::string& line) {
    const std::string rgxStr = "([0-9]+)_([a-z]+)([0-9]*)";
    std::regex rgx(rgxStr);
    const auto begin =
            std::sregex_iterator(line.begin(), line.end(), rgx);
    const auto end = std::sregex_iterator();
    int y = 0;
    for(auto i = begin; i != end; i++) {
        const auto is = (*i).str();
        std::regex rgx(rgxStr);
        std::smatch matches;
        std::regex_search(is, matches, rgx);

        const auto altm = matches[1];
        const auto altStr = altm.str();
        const int alt = std::stoi(altStr);

        const auto codem = matches[2];
        const auto codeStr = codem.str();

        const auto idm = matches[3];
        const auto idStr = idm.str();

        eSanctEle ele;
        ele.fA = alt;
        ele.fX = x;
        ele.fY = y++;
        ele.fId = idStr.empty() ? 0 : std::stoi(idStr);
        if(codeStr == "s") {
            ele.fType = eSanctEleType::stairs;
        } else if(codeStr == "y") {
            ele.fType = eSanctEleType::statue;
        } else if(codeStr == "b") {
            ele.fType = eSanctEleType::sanctuary;
        } else if(codeStr == "m") {
            ele.fType = eSanctEleType::monument;
        } else if(codeStr == "a") {
            ele.fType = eSanctEleType::altar;
        } else if(codeStr == "c") {
            ele.fType = eSanctEleType::copper;
        } else if(codeStr == "t") {
            ele.fType = eSanctEleType::tile;
        } else { // x
            ele.fType = eSanctEleType::none;
        }

        bp.push_back(ele);
    }
    return true;
}

bool loadBP(eSanctBlueprint& bp,
            const std::string& path) {
    std::ifstream file(path);
    if(!file.good()) {
        printf("File missing %s\n", path.c_str());
        return false;
    }
    std::string str;
    int x = 0;
    int s = -1;
    while(std::getline(file, str)) {
        auto& lineBP = bp.fTiles.emplace_back();
        loadLineBP(x++, lineBP, str);
        const int lineBPs = lineBP.size();
        if(s == -1) {
            s = lineBPs;
        } else if(s != lineBPs) {
            printf("Invalid sanctuary %s\n", path.c_str());
            return false;
        }
    }
    if(bp.fTiles.empty()) {
        printf("Invalid sanctuary %s\n", path.c_str());
        return false;
    }
    bp.fW = bp.fTiles.size();
    bp.fH = s;
    return true;
}

void eSanctBlueprints::load() {
    fLoaded = true;
    const std::string dir = "../Sanctuaries/";
    loadBP(fHephaestus, dir + "hephaestus.txt");
}

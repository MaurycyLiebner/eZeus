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
        auto idStr = idm.str();

        eSanctEle ele;
        ele.fA = alt;
        ele.fX = x;
        ele.fY = y++;

        if(codeStr == "s") {
            ele.fType = eSanctEleType::stairs;
        } else if(codeStr == "y") {
            ele.fType = eSanctEleType::defaultStatue;
        } else if(codeStr == "b") {
            ele.fType = eSanctEleType::sanctuary;
        } else if(codeStr == "m") {
            ele.fType = eSanctEleType::monument;
        } else if(codeStr == "a") {
            ele.fType = eSanctEleType::altar;
        } else if(codeStr == "c") {
            ele.fType = eSanctEleType::copper;
        } else if(codeStr == "ot") {
            ele.fType = eSanctEleType::oliveTree;
        } else if(codeStr == "v") {
            ele.fType = eSanctEleType::vine;
        } else if(codeStr == "t") {
            ele.fType = eSanctEleType::tile;
        } else { // x
            ele.fType = eSanctEleType::none;
        }

        if(codeStr == "y" && idStr.size() > 1) {
            const auto godIdStr = idStr.substr(1, idStr.size() - 1);
            idStr = idStr.substr(0, 1);
            const int godId = std::stoi(godIdStr);
            const auto aphEle = eSanctEleType::aphroditeStatue;
            const int id0 = static_cast<int>(aphEle);
            const auto god = static_cast<eSanctEleType>(id0 + godId);
            ele.fType = god;
        }
        ele.fId = idStr.empty() ? 0 : std::stoi(idStr);

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

eSanctEle rotate(const eSanctEle& src) {
    eSanctEle result = src;
    result.fX = src.fY;
    result.fY = src.fX;
    if(result.fType == eSanctEleType::stairs) {
        int& id = result.fId;
        if(id == 1) id = 7;
        else if(id == 5) id = 3;
        else if(id == 3) id = 5;
        else if(id == 7) id = 1;
        else if(id == 2) id = 6;
        else if(id == 4) id = 4;
        else if(id == 8) id = 8;
        else if(id == 11) id = 9;
        else if(id == 10) id = 10;
        else if(id == 9) id = 11;
        else if(id == 6) id = 2;
        else if(id == 0) id = 0;
    } else if(result.fType == eSanctEleType::defaultStatue ||
              result.fType == eSanctEleType::aphroditeStatue ||
              result.fType == eSanctEleType::apolloStatue ||
              result.fType == eSanctEleType::aresStatue ||
              result.fType == eSanctEleType::artemisStatue ||
              result.fType == eSanctEleType::athenaStatue ||
              result.fType == eSanctEleType::atlasStatue ||
              result.fType == eSanctEleType::demeterStatue ||
              result.fType == eSanctEleType::dionysusStatue ||
              result.fType == eSanctEleType::hadesStatue ||
              result.fType == eSanctEleType::hephaestusStatue ||
              result.fType == eSanctEleType::heraStatue ||
              result.fType == eSanctEleType::hermesStatue ||
              result.fType == eSanctEleType::poseidonStatue ||
              result.fType == eSanctEleType::zeusStatue ||
              result.fType == eSanctEleType::monument) {
        int& id = result.fId;
        if(id == 1) id = 2;
        else if(id == 2) id = 1;
        else if(id == 3) id = 0;
        else if(id == 0) id = 3;
    } else if(result.fType == eSanctEleType::sanctuary) {
        int& id = result.fId;
        if(id == 1) id = 0;
        else if(id == 0) id = 1;
        else if(id == 2) id = 3;
        else if(id == 3) id = 2;
    }

    return result;
}

eSanctBlueprint rotate(const eSanctBlueprint& src) {
    eSanctBlueprint result;
    result.fH = src.fW;
    result.fW = src.fH;
    for(int y = 0; y < src.fH; y++) {
        std::vector<eSanctEle> v;
        for(int x = 0; x < src.fW; x++) {
            const auto& row = src.fTiles[x];
            const auto& col = row[y];
            v.push_back(rotate(col));
        }
        result.fTiles.push_back(v);
    }
    return result;
}

void eSanctBlueprints::loadImpl() {
    if(mLoaded) return;
    mLoaded = true;
    const std::string dir = "../Sanctuaries/";

    loadBP(fZeusW, dir + "zeus.txt");
    fZeusH = rotate(fZeusW);

    loadBP(fApolloW, dir + "apollo.txt");
    fApolloH = rotate(fApolloW);

    loadBP(fAthenaW, dir + "athena.txt");
    fAthenaH = rotate(fAthenaW);

    loadBP(fDionysusW, dir + "dionysus.txt");
    fDionysusH = rotate(fDionysusW);

    loadBP(fHephaestusW, dir + "hephaestus.txt");
    fHephaestusH = rotate(fHephaestusW);

    loadBP(fArtemisW, dir + "artemis.txt");
    fArtemisH = rotate(fArtemisW);
}

const eSanctBlueprint* eSanctBlueprints::sSanctuaryBlueprint(
        const eBuildingType type, const bool rotate) {
    const auto& i = eSanctBlueprints::instance;
    switch(type) {
    case eBuildingType::templeZeus: {
        if(rotate) {
            return &i.fZeusH;
        } else {
            return &i.fZeusW;
        }
    } break;
    case eBuildingType::templeApollo: {
        if(rotate) {
            return &i.fApolloH;
        } else {
            return &i.fApolloW;
        }
    } break;
    case eBuildingType::templeAthena: {
        if(rotate) {
            return &i.fAthenaH;
        } else {
            return &i.fAthenaW;
        }
    } break;
    case eBuildingType::templeArtemis: {
        if(rotate) {
            return &i.fArtemisH;
        } else {
            return &i.fArtemisW;
        }
    } break;
    case eBuildingType::templeDionysus: {
        if(rotate) {
            return &i.fDionysusH;
        } else {
            return &i.fDionysusW;
        }
    } break;
    case eBuildingType::templeHephaestus: {
        if(rotate) {
            return &i.fHephaestusH;
        } else {
            return &i.fHephaestusW;
        }
    } break;
    default:
        return nullptr;
    }
    return nullptr;
}

void eSanctBlueprints::load() {
    instance.loadImpl();
}

bool eSanctBlueprints::loaded() {
    return instance.mLoaded;
}

#include "exmlparser.h"

#include <fstream>

bool match(const std::string& str, const std::string& line,
           const int oldIndex, int& newIndex) {
    const int ls = line.size();
    const int iMax = str.size();
    newIndex = oldIndex;
    for(int i = 0; i < iMax; i++, newIndex++) {
        const int lineIndex = oldIndex + i;
        if(lineIndex >= ls) return false;
        const auto strC = str[i];
        const auto lineC = line[lineIndex];
        if(strC != lineC) return false;
    }
    return true;
}

void skipSpaces(const std::string& line, int& index) {
    const int ls = line.size();
    if(index >= ls) return;
    while(line[index] == ' ') {
        index++;
        if(index >= ls) break;
    }
}

bool readId(const std::string& line,
            const int oldIndex,
            int& newIndex,
            int& id) {
    const int ls = line.size();
    newIndex = oldIndex;
    if(newIndex >= ls) return false;
    {
        const bool q = line[newIndex++] == '"';
        if(!q) return false;
    }
    if(newIndex >= ls) return false;
    std::string numberStr;
    while(newIndex < ls) {
        const auto c = line[newIndex];
        if(c == '"') break;
        if(!std::isdigit(c)) return false;
        numberStr = numberStr + c;
        newIndex++;
    }
    id = std::stoi(numberStr);
    {
        if(newIndex >= ls) return false;
        const bool q = line[newIndex++] == '"';
        if(!q) return false;
    }
    return true;
}

bool eXmlParser::sParse(eTextStrings& strings,
                        const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file.good()) {
        printf("File missing %s\n", filePath.c_str());
        return false;
    }
    eTextGroup* group = nullptr;
    std::string line;
    while(std::getline(file, line)) {
        if(line.empty()) continue;
        const int ls = line.size();
        int index = 0;
        {
            skipSpaces(line, index);
            if(index >= ls) continue;
        }
        {
            int newIndex;
            const bool isGroup = match("<group id=", line, index, newIndex);
            if(isGroup) {
                index = newIndex;
                if(index >= ls) continue;
                int id;
                const bool r = readId(line, index, newIndex, id);
                if(!r) continue;
                index = newIndex;
                if(index >= ls) continue;
                group = &strings[id];
                continue;
            }
        }
        {
            int newIndex;
            const bool isString = match("<string id=", line, index, newIndex);
            if(isString) {
                index = newIndex;
                if(index >= ls) continue;
                int id;
                const bool r = readId(line, index, newIndex, id);
                if(!r) continue;
                index = newIndex + 1;
                if(index >= ls) continue;
                if(!group) continue;
                auto& str = (*group)[id];
                while(index < ls && line[index] != '<') {
                    str.push_back(line[index++]);
                }
                continue;
            }
        }
    }
    return true;
}

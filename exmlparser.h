#ifndef EXMLPARSER_H
#define EXMLPARSER_H

#include <map>
#include <string>

using eTextGroup = std::map<int, std::string>;
using eTextStrings = std::map<int, eTextGroup>;

namespace eXmlParser {
    bool sParse(eTextStrings& strings,
                const std::string& filePath);
};

#endif // EXMLPARSER_H

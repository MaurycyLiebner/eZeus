#ifndef ELOADTEXTHELPER_H
#define ELOADTEXTHELPER_H

#include <string>
#include <map>

namespace eLoadTextHelper {
    using eMap = std::map<std::string, std::string>;
    bool load(const std::string& path, eMap& map);
};

#endif // ELOADTEXTHELPER_H

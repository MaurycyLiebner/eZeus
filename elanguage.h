#ifndef ELANGUAGE_H
#define ELANGUAGE_H

#include <string>
#include <map>

class eLanguage {
public:
    eLanguage() {}

    static eLanguage instance;

    static bool load();
    static bool loaded();

    static const std::string& text(const std::string& key);

    std::map<std::string, std::string> fText;
private:
    bool loadImpl();
    bool mLoaded = false;
};

#endif // ELANGUAGE_H

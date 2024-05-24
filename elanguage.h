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

    static const std::string& zeusText(const int g, const int s);

    std::map<std::string, std::string> fText;

    std::map<int, std::map<int, std::string>> fZeusText;
private:
    bool loadImpl();
    bool mLoaded = false;
};

#endif // ELANGUAGE_H

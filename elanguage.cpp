#include "elanguage.h"

#include "eloadtexthelper.h"

eLanguage eLanguage::instance;

const std::string& eLanguage::text(const std::string& key) {
    return instance.fText[key];
}

bool eLanguage::load() {
    return instance.loadImpl();
}

bool eLanguage::loaded() {
    return instance.mLoaded;
}

bool eLanguage::loadImpl() {
    if(mLoaded) return false;
    mLoaded = true;

    const std::string path = "../Text/language.txt";
    return eLoadTextHelper::load(path, fText);
}

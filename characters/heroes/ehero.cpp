#include "ehero.h"

#include "eachilles.h"

#include "elanguage.h"

eHero::eHero(eGameBoard& board, const eHeroType mt) :
    eCharacter(board, sHeroToCharacterType(mt)) {}

eHeroType eHero::sCharacterToHeroType(const eCharacterType type,
                                      bool* const valid) {
    if(valid) *valid = true;
    switch(type) {
    case eCharacterType::achilles: return eHeroType::achilles;
    case eCharacterType::atalanta: return eHeroType::atalanta;
    case eCharacterType::bellerophon: return eHeroType::bellerophon;
    case eCharacterType::hercules: return eHeroType::hercules;
    case eCharacterType::jason: return eHeroType::jason;
    case eCharacterType::odysseus: return eHeroType::odysseus;
    case eCharacterType::perseus: return eHeroType::perseus;
    case eCharacterType::theseus: return eHeroType::theseus;
    default:
        if(valid) *valid = false;
        return eHeroType::achilles;
    }
}

eCharacterType eHero::sHeroToCharacterType(const eHeroType type) {
    switch(type) {
    case eHeroType::achilles: return eCharacterType::achilles;
    case eHeroType::atalanta: return eCharacterType::atalanta;
    case eHeroType::bellerophon: return eCharacterType::bellerophon;
    case eHeroType::hercules: return eCharacterType::hercules;
    case eHeroType::jason: return eCharacterType::jason;
    case eHeroType::odysseus: return eCharacterType::odysseus;
    case eHeroType::perseus: return eCharacterType::perseus;
    case eHeroType::theseus: return eCharacterType::theseus;
    default: return eCharacterType::achilles;
    }
}

stdsptr<eHero> eHero::sCreateHero(const eHeroType type, eGameBoard& board) {
    switch(type) {
    case eHeroType::achilles:
        return e::make_shared<eAchilles>(board);
    case eHeroType::atalanta:
        return e::make_shared<eAtalanta>(board);
    case eHeroType::bellerophon:
        return e::make_shared<eBellerophon>(board);
    case eHeroType::hercules:
        return e::make_shared<eHercules>(board);
    case eHeroType::jason:
        return e::make_shared<eJason>(board);
    case eHeroType::odysseus:
        return e::make_shared<eOdysseus>(board);
    case eHeroType::perseus:
        return e::make_shared<ePerseus>(board);
    case eHeroType::theseus:
        return e::make_shared<eTheseus>(board);
    }
}

std::string eHero::sHeroName(const eHeroType ht) {
    switch(ht) {
    case eHeroType::achilles: return eLanguage::text("achilles");
    case eHeroType::atalanta: return eLanguage::text("atalanta");
    case eHeroType::bellerophon: return eLanguage::text("bellerophon");
    case eHeroType::hercules: return eLanguage::text("hercules");
    case eHeroType::jason: return eLanguage::text("jason");
    case eHeroType::odysseus: return eLanguage::text("odysseus");
    case eHeroType::perseus: return eLanguage::text("perseus");
    case eHeroType::theseus: return eLanguage::text("theseus");
    }
    return "";
}

void eHero::sHeroStrings(std::vector<eHeroType>& heros,
                       std::vector<std::string>& heroNames) {
    heros.push_back(eHeroType::achilles);
    heros.push_back(eHeroType::atalanta);
    heros.push_back(eHeroType::bellerophon);
    heros.push_back(eHeroType::hercules);
    heros.push_back(eHeroType::jason);
    heros.push_back(eHeroType::odysseus);
    heros.push_back(eHeroType::perseus);
    heros.push_back(eHeroType::theseus);
    for(const auto h : heros) {
        heroNames.push_back(sHeroName(h));
    }
}

#include "eachilles.h"

eAchilles::eAchilles(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fAchilles,
               eHeroType::achilles) {}

eAtalanta::eAtalanta(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fAtalanta,
               eHeroType::atalanta) {}

eBellerophon::eBellerophon(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fBellerophon,
               eHeroType::bellerophon) {}

eHercules::eHercules(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fHercules,
               eHeroType::hercules) {}

eJason::eJason(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fJason,
               eHeroType::jason) {}

eOdysseus::eOdysseus(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fOdysseus,
               eHeroType::odysseus) {}

ePerseus::ePerseus(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fPerseus,
               eHeroType::perseus) {}

eTheseus::eTheseus(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fTheseus,
               eHeroType::theseus) {}

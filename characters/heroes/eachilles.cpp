#include "eachilles.h"

#include "textures/egametextures.h"

eAchilles::eAchilles(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fAchilles,
               eHeroType::achilles) {
    eGameTextures::loadAchilles();
}

eAtalanta::eAtalanta(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fAtalanta,
               eHeroType::atalanta) {
    eGameTextures::loadAtalanta();
}

eBellerophon::eBellerophon(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fBellerophon,
               eHeroType::bellerophon) {
    eGameTextures::loadBellerophon();
}

eHercules::eHercules(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fHercules,
               eHeroType::hercules) {
    eGameTextures::loadHeracles();
}

eJason::eJason(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fJason,
               eHeroType::jason) {
    eGameTextures::loadJason();
}

eOdysseus::eOdysseus(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fOdysseus,
               eHeroType::odysseus) {
    eGameTextures::loadOdysseus();
}

ePerseus::ePerseus(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fPerseus,
               eHeroType::perseus) {
    eGameTextures::loadPerseus();
}

eTheseus::eTheseus(eGameBoard& board) :
    eBasicHero(board, &eCharacterTextures::fTheseus,
               eHeroType::theseus) {
    eGameTextures::loadTheseus();
}

#include "egodquest.h"

eHeroType eGodQuest::sDefaultHero(
        const eGodType gt, const eGodQuestId gqi) {
    switch(gt) {
    case eGodType::aphrodite: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::hercules;
        case eGodQuestId::godQuest2:
            return eHeroType::bellerophon;
        }
    } break;
    case eGodType::apollo: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::hercules;
        case eGodQuestId::godQuest2:
            return eHeroType::atalanta;
        }
    } break;
    case eGodType::ares: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::hercules;
        case eGodQuestId::godQuest2:
            return eHeroType::atalanta;
        }
    } break;
    case eGodType::artemis: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::hercules;
        case eGodQuestId::godQuest2:
            return eHeroType::atalanta;
        }
    } break;
    case eGodType::athena: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::perseus;
        case eGodQuestId::godQuest2:
            return eHeroType::bellerophon;
        }
    } break;
    case eGodType::atlas: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::hercules;
        case eGodQuestId::godQuest2:
            return eHeroType::hercules;
        }
    } break;
    case eGodType::demeter: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::hercules;
        case eGodQuestId::godQuest2:
            return eHeroType::jason;
        }
    } break;
    case eGodType::dionysus: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::theseus;
        case eGodQuestId::godQuest2:
            return eHeroType::perseus;
        }
    } break;
    case eGodType::hades: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::perseus;
        case eGodQuestId::godQuest2:
            return eHeroType::theseus;
        }
    } break;
    case eGodType::hephaestus: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::achilles;
        case eGodQuestId::godQuest2:
            return eHeroType::odysseus;
        }
    } break;
    case eGodType::hera: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::bellerophon;
        case eGodQuestId::godQuest2:
            return eHeroType::jason;
        }
    } break;
    case eGodType::hermes: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::perseus;
        case eGodQuestId::godQuest2:
            return eHeroType::achilles;
        }
    } break;
    case eGodType::poseidon: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::odysseus;
        case eGodQuestId::godQuest2:
            return eHeroType::theseus;
        }
    } break;
    case eGodType::zeus: {
        switch(gqi) {
        case eGodQuestId::godQuest1:
            return eHeroType::jason;
        case eGodQuestId::godQuest2:
            return eHeroType::odysseus;
        }
    } break;
    }
}

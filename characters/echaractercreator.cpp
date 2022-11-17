#include "echaracter.h"

#include "eactor.h"
#include "earcher.h"
#include "eartisan.h"
#include "eboar.h"
#include "ebronzeminer.h"
#include "ecarttransporter.h"
#include "edeer.h"
#include "edonkey.h"
#include "efirefighter.h"
#include "efishingboat.h"
#include "egoat.h"
#include "egoatherd.h"
#include "egreekhoplite.h"
#include "egreekhorseman.h"
#include "egreekrockthrower.h"
#include "egrower.h"
#include "egymnast.h"
#include "ehealer.h"
#include "ehoplite.h"
#include "ehorse.h"
#include "ehorseman.h"
#include "ehunter.h"
#include "elumberjack.h"
#include "emarbleminer.h"
#include "eox.h"
#include "epeddler.h"
#include "ephilosopher.h"
#include "eporter.h"
#include "erockthrower.h"
#include "esettler.h"
#include "esheep.h"
#include "eshepherd.h"
#include "esilverminer.h"
#include "etaxcollector.h"
#include "etradeboat.h"
#include "etrader.h"
#include "etrailer.h"
#include "ewatchman.h"
#include "ewaterdistributor.h"

#include "monsters/ecalydonianboar.h"

#include "gods/eathena.h"
#include "gods/edemeter.h"
#include "gods/edionysus.h"
#include "gods/ehermes.h"

#include "heroes/eachilles.h"

stdsptr<eCharacter> eCharacter::sCreate(
        const eCharacterType t, eGameBoard& board) {
    switch(t) {
    case eCharacterType::none:
    case eCharacterType::wolf:
    case eCharacterType::cattle:
        return nullptr;
    case eCharacterType::actor:
        return e::make_shared<eActor>(board);
    case eCharacterType::archer:
        return e::make_shared<eArcher>(board);
    case eCharacterType::artisan:
        return e::make_shared<eArtisan>(board);
    case eCharacterType::boar:
        return e::make_shared<eBoar>(board);
    case eCharacterType::bronzeMiner:
        return e::make_shared<eBronzeMiner>(board);
    case eCharacterType::cartTransporter:
        return e::make_shared<eCartTransporter>(board);
    case eCharacterType::deer:
        return e::make_shared<eDeer>(board);
    case eCharacterType::donkey:
        return e::make_shared<eDonkey>(board);
    case eCharacterType::fireFighter:
        return e::make_shared<eFireFighter>(board);
    case eCharacterType::fishingBoat:
        return e::make_shared<eFishingBoat>(board);
    case eCharacterType::goat:
        return e::make_shared<eGoat>(board);
    case eCharacterType::goatherd:
        return e::make_shared<eGoatherd>(board);
    case eCharacterType::greekHoplite:
        return e::make_shared<eGreekHoplite>(board);
    case eCharacterType::greekHorseman:
        return e::make_shared<eGreekHorseman>(board);
    case eCharacterType::greekRockThrower:
        return e::make_shared<eGreekRockThrower>(board);
    case eCharacterType::grower:
        return e::make_shared<eGrower>(board);
    case eCharacterType::gymnast:
        return e::make_shared<eGymnast>(board);
    case eCharacterType::healer:
        return e::make_shared<eHealer>(board);
    case eCharacterType::hoplite:
        return e::make_shared<eHoplite>(board);
    case eCharacterType::horse:
        return e::make_shared<eHorse>(board);
    case eCharacterType::horseman:
        return e::make_shared<eHorseman>(board);
    case eCharacterType::hunter:
        return e::make_shared<eHunter>(board);
    case eCharacterType::lumberjack:
        return e::make_shared<eLumberjack>(board);
    case eCharacterType::marbleMiner:
        return e::make_shared<eMarbleMiner>(board);
    case eCharacterType::ox:
        return e::make_shared<eOx>(board);
    case eCharacterType::peddler:
        return e::make_shared<ePeddler>(board);
    case eCharacterType::philosopher:
        return e::make_shared<ePhilosopher>(board);
    case eCharacterType::porter:
        return e::make_shared<ePorter>(board);
    case eCharacterType::rockThrower:
        return e::make_shared<eRockThrower>(board);
    case eCharacterType::settler:
        return e::make_shared<eSettler>(board);
    case eCharacterType::sheep:
        return e::make_shared<eSheep>(board);
    case eCharacterType::shepherd:
        return e::make_shared<eShepherd>(board);
    case eCharacterType::silverMiner:
        return e::make_shared<eSilverMiner>(board);
    case eCharacterType::taxCollector:
        return e::make_shared<eTaxCollector>(board);
    case eCharacterType::tradeBoat:
        return e::make_shared<eTradeBoat>(board);
    case eCharacterType::trader:
        return e::make_shared<eTrader>(board);
    case eCharacterType::trailer:
        return e::make_shared<eTrailer>(board);
    case eCharacterType::watchman:
        return e::make_shared<eWatchman>(board);
    case eCharacterType::waterDistributor:
        return e::make_shared<eWaterDistributor>(board);

    case eCharacterType::calydonianBoar:
        return e::make_shared<eCalydonianBoar>(board);
    case eCharacterType::cerberus:
        return e::make_shared<eCerberus>(board);
    case eCharacterType::chimera:
        return e::make_shared<eChimera>(board);
    case eCharacterType::cyclops:
        return e::make_shared<eCyclops>(board);
    case eCharacterType::dragon:
        return e::make_shared<eDragon>(board);
    case eCharacterType::echidna:
        return e::make_shared<eEchidna>(board);
    case eCharacterType::harpies:
        return e::make_shared<eHarpies>(board);
    case eCharacterType::hector:
        return e::make_shared<eHector>(board);
    case eCharacterType::hydra:
        return e::make_shared<eHydra>(board);
    case eCharacterType::kraken:
        return e::make_shared<eKraken>(board);
    case eCharacterType::maenads:
        return e::make_shared<eMaenads>(board);
    case eCharacterType::medusa:
        return e::make_shared<eMedusa>(board);
    case eCharacterType::minotaur:
        return e::make_shared<eMinotaur>(board);
    case eCharacterType::scylla:
        return e::make_shared<eScylla>(board);
    case eCharacterType::sphinx:
        return e::make_shared<eSphinx>(board);
    case eCharacterType::talos:
        return e::make_shared<eTalos>(board);

    case eCharacterType::aphrodite:
        return e::make_shared<eAphrodite>(board);
    case eCharacterType::apollo:
        return e::make_shared<eApollo>(board);
    case eCharacterType::ares:
        return e::make_shared<eAres>(board);
    case eCharacterType::artemis:
        return e::make_shared<eArtemis>(board);
    case eCharacterType::athena:
        return e::make_shared<eAthena>(board);
    case eCharacterType::atlas:
        return e::make_shared<eAtlas>(board);
    case eCharacterType::demeter:
        return e::make_shared<eDemeter>(board);
    case eCharacterType::dionysus:
        return e::make_shared<eDionysus>(board);
    case eCharacterType::hades:
        return e::make_shared<eHades>(board);
    case eCharacterType::hephaestus:
        return e::make_shared<eHephaestus>(board);
    case eCharacterType::hera:
        return e::make_shared<eHera>(board);
    case eCharacterType::hermes:
        return e::make_shared<eHermes>(board);
    case eCharacterType::poseidon:
        return e::make_shared<ePoseidon>(board);
    case eCharacterType::zeus:
        return e::make_shared<eZeus>(board);

    case eCharacterType::achilles:
        return e::make_shared<eAchilles>(board);
    case eCharacterType::atalanta:
        return e::make_shared<eAtalanta>(board);
    case eCharacterType::bellerophon:
        return e::make_shared<eBellerophon>(board);
    case eCharacterType::hercules:
        return e::make_shared<eHercules>(board);
    case eCharacterType::jason:
        return e::make_shared<eJason>(board);
    case eCharacterType::odysseus:
        return e::make_shared<eOdysseus>(board);
    case eCharacterType::perseus:
        return e::make_shared<ePerseus>(board);
    case eCharacterType::theseus:
        return e::make_shared<eTheseus>(board);
    }
}
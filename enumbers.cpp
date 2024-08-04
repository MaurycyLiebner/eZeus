#include "enumbers.h"

#include "egamedir.h"
#include "eloadtexthelper.h"

#include <fstream>
#include <iostream>

int eNumbers::sBoarMaxCount;
int eNumbers::sBoarSpawnPeriod;
int eNumbers::sDeerMaxCount;
int eNumbers::sDeerSpawnPeriod;

int eNumbers::sOlivePressProcessingPeriod;
int eNumbers::sWineryProcessingPeriod;
int eNumbers::sArmoryProcessingPeriod;
int eNumbers::sSculptureStudioProcessingPeriod;

int eNumbers::sOliveTreeRipePeriod;
int eNumbers::sVineRipePeriod;
int eNumbers::sOrangeTreeRipePeriod;

double eNumbers::sTreeVineFullyRipePeriodMultiplier;

double eNumbers::sTreeVineBlessedFullyRipePeriodMultiplier;
double eNumbers::sTreeVineBlessedRipePeriodMultiplier;
double eNumbers::sTreeVineCursedFullyRipePeriodMultiplier;
double eNumbers::sTreeVineCursedRipePeriodMultiplier;

int eNumbers::sLandMonsterInvadePeriod;
int eNumbers::sWaterMonsterInvadePeriod;
int eNumbers::sMonsterAttackPeriod;

int eNumbers::sFriendlyGodVisitPeriod;
int eNumbers::sGodHelpPeriod;

void eNumbers::sLoad() {
    const auto path = eGameDir::numbersPath();
    std::map<std::string, std::string> map;
    eLoadTextHelper::load(path, map);

    const bool write = false;

    std::ofstream file;
    if(write) file.open(path);

    const auto loadI = [&map, &file](const std::string& name,
                                     int& val, const int def) {
        if(write) {
            file << name << " \"" << def << "\"\n";
        }
        const auto it = map.find(name);
        if(it == map.end()) {
            printf("Could not find '%s' in numbers.txt. Using default value %d\n", name.c_str(), def);
            val = def;
            return;
        }
        const auto iStr = it->second;
        try {
            val = std::stoi(iStr);
        } catch(...) {
            printf("Invalid '%s' value '%s'. Using default value %d\n", name.c_str(), iStr.c_str(), def);
            val = def;
            return;
        }
    };

    const auto loadD = [&map, &file](const std::string& name,
                                     double& val, const double def) {
        if(write) {
            file << name << " \"" << def << "\"\n";
        }
        const auto it = map.find(name);
        if(it == map.end()) {
            printf("Could not find '%s' in numbers.txt. Using default value %f\n", name.c_str(), def);
            val = def;
            return;
        }
        const auto iStr = it->second;
        try {
            val = std::stod(iStr);
        } catch(...) {
            printf("Invalid '%s' value '%s'. Using default value %f\n", name.c_str(), iStr.c_str(), def);
            val = def;
            return;
        }
    };

    loadI("board_max_count_i", sBoarMaxCount, 8);
    loadI("board_spawn_period_i", sBoarSpawnPeriod, 4000);
    loadI("deer_max_count_i", sDeerMaxCount, 8);
    loadI("deer_spawn_period_i", sDeerSpawnPeriod, 4000);

    loadI("olive_press_processing_period_i", sOlivePressProcessingPeriod, 20000);
    loadI("winery_processing_period_i", sWineryProcessingPeriod, 20000);
    loadI("armory_processing_period_i", sArmoryProcessingPeriod, 40000);
    loadI("sculpture_studio_processing_period_i", sSculptureStudioProcessingPeriod, 100000);

    loadI("olive_tree_ripe_period_i", sOliveTreeRipePeriod, 40000);
    loadI("vine_ripe_period_i", sVineRipePeriod, 40000);
    loadI("orange_tree_ripe_period_i", sOrangeTreeRipePeriod, 40000);

    loadD("tree_vine_fully_ripe_period_multiplier_d", sTreeVineFullyRipePeriodMultiplier, 2.);

    loadD("tree_vine_blessed_fully_ripe_period_multiplier_d", sTreeVineBlessedFullyRipePeriodMultiplier, 3.);
    loadD("tree_vine_blessed_ripe_period_multiplier_d", sTreeVineBlessedRipePeriodMultiplier, 0.333);
    loadD("tree_vine_cursed_fully_ripe_period_multiplier_d", sTreeVineCursedFullyRipePeriodMultiplier, 0.333);
    loadD("tree_vine_cursed_ripe_period_multiplier_d", sTreeVineCursedRipePeriodMultiplier, 3.);

    loadI("monster_attack_period_i", sMonsterAttackPeriod, 8000);
    loadI("land_monster_invade_period_i", sLandMonsterInvadePeriod, 200000);
    loadI("water_monster_invade_period_i", sWaterMonsterInvadePeriod, 100000);

    loadI("friendly_god_visit_period_i", sFriendlyGodVisitPeriod, 450);
    loadI("god_help_period_i", sGodHelpPeriod, 250000);
}

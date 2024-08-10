#include "enumbers.h"

#include "egamedir.h"
#include "eloadtexthelper.h"

#include <fstream>
#include <iostream>

int eNumbers::sDayLength;

int eNumbers::sArmyTravelTime;

int eNumbers::sEarthquakeProgressPeriod;

int eNumbers::sBoarMaxCount;
int eNumbers::sBoarSpawnPeriod;
int eNumbers::sDeerMaxCount;
int eNumbers::sDeerSpawnPeriod;

int eNumbers::sOlivePressProcessingPeriod;
int eNumbers::sWineryProcessingPeriod;
int eNumbers::sArmoryProcessingPeriod;
int eNumbers::sSculptureStudioProcessingPeriod;

int eNumbers::sFarmRipePeriod;

int eNumbers::sShepherdGoatherdMaxDistance;
int eNumbers::sShepherdGoatherdMaxGroom;
int eNumbers::sShepherdGoatherdGroomTime;
int eNumbers::sShepherdGoatherdCollectTime;
int eNumbers::sShepherdGoatherdWaitTime;

int eNumbers::sSheepMaxGroom;
int eNumbers::sGoatMaxGroom;

int eNumbers::sCorralProcessingPeriod;
int eNumbers::sCorralTakePeriod;
int eNumbers::sCorralKillPeriod;
int eNumbers::sCorralReplacePeriod;
int eNumbers::sCattleMaturePeriod;

int eNumbers::sUrchinQuayUnpackTime;
int eNumbers::sFisheryBoatBuildTime;
int eNumbers::sFisheryUnpackTime;

int eNumbers::sHuntingLodgeWaitPeriod;

int eNumbers::sMintDrachmasPerSilver;

int eNumbers::sSpreadFirePeriod;
int eNumbers::sFireCollapsePeriod;
int eNumbers::sRuinsFireEndPeriod;
int eNumbers::sMaintenanceDecrementPeriod;
double eNumbers::sFireRiskPeriodMultiplier;
double eNumbers::sFireRiskPeriodBaseIncrement;
double eNumbers::sFireRiskPeriodExponent;
double eNumbers::sCollapseRiskPeriodMultiplier;
double eNumbers::sCollapseRiskPeriodBaseIncrement;
double eNumbers::sCollapseRiskPeriodExponent;

int eNumbers::sHouseCultureDecrementPeriod;
int eNumbers::sHouseWaterDecrementPeriod;
int eNumbers::sHouseHygieneDecrementPeriod;
double eNumbers::sHouseHealPlaguePeriodMultiplier;
double eNumbers::sHouseHealPlaguePeriodBaseMultiplier;
double eNumbers::sHouseHealPlaguePeriodExponent;
double eNumbers::sHousePlagueRiskPeriodMultiplier;
double eNumbers::sHousePlagueRiskPeriodBaseIncrement;
double eNumbers::sHousePlagueRiskPeriodExponent;
int eNumbers::sHouseDisgruntledRemovePeriod;
double eNumbers::sHouseDisgruntledRiskPeriodMultiplier;
double eNumbers::sHouseDisgruntledRiskPeriodBaseIncrement;
double eNumbers::sHouseDisgruntledRiskPeriodExponent;
double eNumbers::sHouseLeaveRiskPeriodMultiplier;
double eNumbers::sHouseLeaveRiskPeriodBaseIncrement;
double eNumbers::sHouseLeaveRiskPeriodExponent;
int eNumbers::sHouseSatisfactionUpdatePeriod;
int eNumbers::sHouseDisgruntledSpawnPeriod;
int eNumbers::sHouseSickSpawnPeriod;

int eNumbers::sHerosHallArrivalPeriod;
int eNumbers::sHerosHallSpawnPeriod;

int eNumbers::sHorseRanchWheatUsePeriod;
int eNumbers::sHorseRanchHorseSpawnPeriod;

int eNumbers::sPatrolerMaxDistance;
int eNumbers::sPatrolerWaitTime;
int eNumbers::sPatrolerSourceSpawnPeriod;

int eNumbers::sArtisanWaitTime;
int eNumbers::sArtisanBuildTime;

int eNumbers::sTowerSpawnPeriod;

int eNumbers::sTraderSpawnPeriod;

int eNumbers::sChariotBuildingTime;

int eNumbers::sOliveTreeRipePeriod;
int eNumbers::sVineRipePeriod;
int eNumbers::sOrangeTreeRipePeriod;

double eNumbers::sTreeVineFullyRipePeriodMultiplier;

double eNumbers::sTreeVineBlessedFullyRipePeriodMultiplier;
double eNumbers::sTreeVineBlessedRipePeriodMultiplier;
double eNumbers::sTreeVineCursedFullyRipePeriodMultiplier;
double eNumbers::sTreeVineCursedRipePeriodMultiplier;

int eNumbers::sMarbleCollectTime;
int eNumbers::sBronzeCollectTime;
int eNumbers::sSilverCollectTime;
int eNumbers::sWoodCollectTime;
int eNumbers::sFishCollectTime;
int eNumbers::sUrchinCollectTime;

int eNumbers::sGrowerMaxDistance;
int eNumbers::sGrowerMaxGroom;
int eNumbers::sGrowerWorkTime;
int eNumbers::sGrowerSpawnWaitTime;

int eNumbers::sMonsterAttackPeriod;
int eNumbers::sMonsterAttackRange;
int eNumbers::sLandMonsterInvadePeriod;
int eNumbers::sWaterMonsterInvadePeriod;

int eNumbers::sFriendlyGodVisitPeriod;
int eNumbers::sGodHelpPeriod;

int eNumbers::sGodAttackCursePeriod;
int eNumbers::sGodAttackCurseRange;
int eNumbers::sGodAttackAttackPeriod;
int eNumbers::sGodAttackAttackRange;
int eNumbers::sGodAttackAggressiveAttackPeriod;
int eNumbers::sGodAttackTargetedCursePeriod;
int eNumbers::sGodAttackTargetedCurseRange;
int eNumbers::sGodAttackTargetedAttackPeriod;
int eNumbers::sGodAttackTargetedAttackRange;
int eNumbers::sGodAttackGodFightRange;
int eNumbers::sGodAttackApolloPlaguePeriod;
int eNumbers::sGodAttackApolloPlagueRange;
int eNumbers::sGodAttackAphroditeEvictPeriod;
int eNumbers::sGodAttackAphroditeEvictRange;

int eNumbers::sGodVisitSoldierAttackPeriod;
int eNumbers::sGodVisitSoldierAttackRange;
int eNumbers::sGodVisitBlessPeriod;
int eNumbers::sGodVisitBlessRange;
int eNumbers::sGodVisitPatrolDistance;
int eNumbers::sGodVisitMoveAroundTime;

int eNumbers::sGodWorshippedSoldierAttackPeriod;
int eNumbers::sGodWorshippedSoldierAttackRange;
int eNumbers::sGodWorshippedBlessPeriod;
int eNumbers::sGodWorshippedBlessRange;

int eNumbers::sSoldierBeingAttackedCallRange;

int eNumbers::sTowerHP;
int eNumbers::sTowerRange;
double eNumbers::sTowerAttack;

int eNumbers::sWallHP;

int eNumbers::sWallArcherRange;
double eNumbers::sWallArcherAttack;

int eNumbers::sRabbleHP;
int eNumbers::sRabbleRange;
double eNumbers::sRabbleAttack;

int eNumbers::sSpearthrowerHP;
int eNumbers::sSpearthrowerRange;
double eNumbers::sSpearthrowerAttack;

int eNumbers::sArcherHP;
int eNumbers::sArcherRange;
double eNumbers::sArcherAttack;

int eNumbers::sHopliteHP;
double eNumbers::sHopliteAttack;

int eNumbers::sChariotHP;
double eNumbers::sChariotSpeed;
double eNumbers::sChariotAttack;

int eNumbers::sHorsemanHP;
double eNumbers::sHorsemanSpeed;
double eNumbers::sHorsemanAttack;

int eNumbers::sWatchmanHP;
double eNumbers::sWatchmanAttack;
int eNumbers::sWatchmanSatisfactionProvide;

int eNumbers::sDefendCityMaxKilled;
int eNumbers::sDefendCityTalosMaxKilled;

int eNumbers::sBasicVendorMaxResourceTakeDistance;
int eNumbers::sHorseVendorMaxResourceTakeDistance;
int eNumbers::sResourceBuildingMaxResourceGiveDistance;
int eNumbers::sProcessingBuildingMaxResourceTakeDistance;
int eNumbers::sTriremeWharfMaxResourceTakeDistance;

void eNumbers::sLoad() {
    const auto path = eGameDir::numbersPath();
    std::map<std::string, std::string> map;
    eLoadTextHelper::load(path, map);

    const bool write = map.empty();

    std::ofstream file;
    if(write) file.open(path);

    const auto loadI = [&](const std::string& name,
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

    const auto loadD = [&](const std::string& name,
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
    loadI("day_length_i", sDayLength, 350);

    loadI("army_travel_time_i", sArmyTravelTime, 150);

    loadI("earthquake_progress_period_i", sEarthquakeProgressPeriod, 500);

    loadI("boar_max_count_i", sBoarMaxCount, 8);
    loadI("boar_spawn_period_i", sBoarSpawnPeriod, 4000);
    loadI("deer_max_count_i", sDeerMaxCount, 8);
    loadI("deer_spawn_period_i", sDeerSpawnPeriod, 4000);

    loadI("olive_press_processing_period_i", sOlivePressProcessingPeriod, 20000);
    loadI("winery_processing_period_i", sWineryProcessingPeriod, 20000);
    loadI("armory_processing_period_i", sArmoryProcessingPeriod, 40000);
    loadI("sculpture_studio_processing_period_i", sSculptureStudioProcessingPeriod, 100000);

    loadI("farm_ripe_period_i", sFarmRipePeriod, 15000);

    loadI("shepherd_goatherd_max_distance_i", sShepherdGoatherdMaxDistance, 40);
    loadI("shepherd_goatherd_max_groom_i", sShepherdGoatherdMaxGroom, 20);
    loadI("shepherd_goatherd_groom_time_i", sShepherdGoatherdGroomTime, 1000);
    loadI("shepherd_goatherd_collect_time_i", sShepherdGoatherdCollectTime, 2000);
    loadI("shepherd_goatherd_wait_time_i", sShepherdGoatherdWaitTime, 2000);

    loadI("sheep_max_groom_i", sSheepMaxGroom, 15);
    loadI("goat_max_groom_i", sGoatMaxGroom, 10);

    loadI("corral_processing_period_i", sCorralProcessingPeriod, 10000);
    loadI("corral_take_period_i", sCorralTakePeriod, 10000);
    loadI("corral_kill_period_i", sCorralKillPeriod, 10000);
    loadI("corral_replace_period_i", sCorralReplacePeriod, 10000);
    loadI("cattle_mature_period_i", sCattleMaturePeriod, 25000);

    loadI("urchin_quay_unpack_time_i", sUrchinQuayUnpackTime, 10000);
    loadI("fishery_boat_build_time_i", sFisheryBoatBuildTime, 40000);
    loadI("fishery_unpack_time_i", sFisheryUnpackTime, 10000);

    loadI("hunting_lodge_wait_period_i", sHuntingLodgeWaitPeriod, 5000);

    loadI("mint_drachmas_per_silver_i", sMintDrachmasPerSilver, 25);

    loadI("spread_fire_period_i", sSpreadFirePeriod, 50000);
    loadI("fire_collapse_period_i", sFireCollapsePeriod, 50000);
    loadI("ruins_fire_end_period_i", sRuinsFireEndPeriod, 10000);
    loadI("maintenance_decrement_period_i", sMaintenanceDecrementPeriod, 2000);
    loadD("fire_risk_period_multiplier_d", sFireRiskPeriodMultiplier, 10);
    loadD("fire_risk_period_base_increment_d", sFireRiskPeriodBaseIncrement, 10);
    loadD("fire_risk_period_exponent_d", sFireRiskPeriodExponent, 4);
    loadD("collapse_risk_period_multiplier_d", sCollapseRiskPeriodMultiplier, 10);
    loadD("collapse_risk_period_base_increment_d", sCollapseRiskPeriodBaseIncrement, 10);
    loadD("collapse_risk_period_exponent_d", sCollapseRiskPeriodExponent, 4);

    loadI("house_culture_decrement_period_i", sHouseCultureDecrementPeriod, 20000);
    loadI("house_water_decrement_period_i", sHouseWaterDecrementPeriod, 7500);
    loadI("house_hygiene_decrement_period_i", sHouseHygieneDecrementPeriod, 25000);
    loadD("house_heal_plague_period_multiplier_d", sHouseHealPlaguePeriodMultiplier, 10);
    loadD("house_heal_plague_period_base_multiplier_d", sHouseHealPlaguePeriodBaseMultiplier, 1000);
    loadD("house_heal_plague_period_exponent_d", sHouseHealPlaguePeriodExponent, 4);
    loadD("house_plague_risk_period_multiplier_d", sHousePlagueRiskPeriodMultiplier, 10);
    loadD("house_plague_risk_period_base_increment_d", sHousePlagueRiskPeriodBaseIncrement, 10);
    loadD("house_plague_risk_period_exponent_d", sHousePlagueRiskPeriodExponent, 4);
    loadI("house_disgruntled_remove_period_i", sHouseDisgruntledRemovePeriod, 500000);
    loadD("house_disgruntled_risk_period_multiplier_d", sHouseDisgruntledRiskPeriodMultiplier, 10);
    loadD("house_disgruntled_risk_period_base_increment_d", sHouseDisgruntledRiskPeriodBaseIncrement, 10);
    loadD("house_disgruntled_risk_period_exponent_d", sHouseDisgruntledRiskPeriodExponent, 3);
    loadD("house_leave_risk_period_multiplier_d", sHouseLeaveRiskPeriodMultiplier, 10);
    loadD("house_leave_risk_period_base_increment_d", sHouseLeaveRiskPeriodBaseIncrement, 10);
    loadD("house_leave_risk_period_exponent_d", sHouseLeaveRiskPeriodExponent, 3);
    loadI("house_satisfaction_update_period_i", sHouseSatisfactionUpdatePeriod, 7500);
    loadI("house_disgruntled_spawn_period_i", sHouseDisgruntledSpawnPeriod, 10000);
    loadI("house_sick_spawn_period_i", sHouseSickSpawnPeriod, 10000);

    loadI("heros_hall_arrival_period_i", sHerosHallArrivalPeriod, 15000);
    loadI("heros_hall_spawn_period_i", sHerosHallSpawnPeriod, 5000);

    loadI("horse_ranch_wheat_use_period_i", sHorseRanchWheatUsePeriod, 1000);
    loadI("horse_ranch_horse_spawn_period_i", sHorseRanchHorseSpawnPeriod, 40000);

    loadI("patroler_max_distance_i", sPatrolerMaxDistance, 40);
    loadI("patroler_wait_time_i", sPatrolerWaitTime, 5000);
    loadI("patroler_source_spawn_period_i", sPatrolerSourceSpawnPeriod, 10000);

    loadI("artisan_wait_time_i", sArtisanWaitTime, 2000);
    loadI("artisan_build_time_i", sArtisanBuildTime, 6000);

    loadI("tower_spawn_period_i", sTowerSpawnPeriod, 5000);

    loadI("trader_spawn_period_i", sTraderSpawnPeriod, 30000);

    loadI("chariot_building_time_i", sChariotBuildingTime, 20000);

    loadI("olive_tree_ripe_period_i", sOliveTreeRipePeriod, 40000);
    loadI("vine_ripe_period_i", sVineRipePeriod, 40000);
    loadI("orange_tree_ripe_period_i", sOrangeTreeRipePeriod, 40000);

    loadD("tree_vine_fully_ripe_period_multiplier_d", sTreeVineFullyRipePeriodMultiplier, 2.);

    loadD("tree_vine_blessed_fully_ripe_period_multiplier_d", sTreeVineBlessedFullyRipePeriodMultiplier, 3.);
    loadD("tree_vine_blessed_ripe_period_multiplier_d", sTreeVineBlessedRipePeriodMultiplier, 0.333);
    loadD("tree_vine_cursed_fully_ripe_period_multiplier_d", sTreeVineCursedFullyRipePeriodMultiplier, 0.333);
    loadD("tree_vine_cursed_ripe_period_multiplier_d", sTreeVineCursedRipePeriodMultiplier, 3.);

    loadI("marble_collect_period_i", sMarbleCollectTime, 10000);
    loadI("bronze_collect_period_i", sBronzeCollectTime, 10000);
    loadI("silver_collect_period_i", sSilverCollectTime, 10000);
    loadI("wood_collect_period_i", sWoodCollectTime, 10000);
    loadI("fish_collect_period_i", sFishCollectTime, 10000);
    loadI("urchin_collect_period_i", sUrchinCollectTime, 10000);

    loadI("grower_max_distance_i", sGrowerMaxDistance, 40);
    loadI("grower_max_groom_i", sGrowerMaxGroom, 5);
    loadI("grower_work_time_i", sGrowerWorkTime, 2000);
    loadI("grower_spawn_wait_time_i", sGrowerSpawnWaitTime, 5000);

    loadI("monster_attack_period_i", sMonsterAttackPeriod, 8000);
    loadI("monster_attack_range_i", sMonsterAttackRange, 10);
    loadI("land_monster_invade_period_i", sLandMonsterInvadePeriod, 200000);
    loadI("water_monster_invade_period_i", sWaterMonsterInvadePeriod, 100000);

    loadI("friendly_god_visit_period_i", sFriendlyGodVisitPeriod, 450);
    loadI("god_help_period_i", sGodHelpPeriod, 250000);

    loadI("god_attack_curse_period_i", sGodAttackCursePeriod, 6000);
    loadI("god_attack_curse_range_i", sGodAttackCurseRange, 10);
    loadI("god_attack_attack_period_i", sGodAttackAttackPeriod, 12000);
    loadI("god_attack_attack_range_i", sGodAttackAttackRange, 10);
    loadI("god_attack_aggressive_attack_period_i", sGodAttackAggressiveAttackPeriod, 8000);
    loadI("god_attack_targeted_curse_period_i", sGodAttackTargetedCursePeriod, 3000);
    loadI("god_attack_targeted_curse_range_i", sGodAttackTargetedCurseRange, 10);
    loadI("god_attack_targeted_attack_period_i", sGodAttackTargetedAttackPeriod, 4000);
    loadI("god_attack_targeted_attack_range_i", sGodAttackTargetedAttackRange, 10);
    loadI("god_attack_god_fight_range_i", sGodAttackGodFightRange, 10);
    loadI("god_attack_apollo_plague_period_i", sGodAttackApolloPlaguePeriod, 7500);
    loadI("god_attack_apollo_plague_range_i", sGodAttackApolloPlagueRange, 10);
    loadI("god_attack_aphrodite_evict_period_i", sGodAttackAphroditeEvictPeriod, 3500);
    loadI("god_attack_aphrodite_evict_range_i", sGodAttackAphroditeEvictRange, 10);

    loadI("god_visit_soldier_attack_period_i", sGodVisitSoldierAttackPeriod, 2500);
    loadI("god_visit_soldier_attack_range_i", sGodVisitSoldierAttackRange, 10);
    loadI("god_visit_bless_period_i", sGodVisitBlessPeriod, 18000);
    loadI("god_visit_bless_range_i", sGodVisitBlessRange, 10);
    loadI("god_visit_patrol_distance_i", sGodVisitPatrolDistance, 100);
    loadI("god_visit_move_around_time_i", sGodVisitMoveAroundTime, 25000);

    loadI("god_worshipped_soldier_attack_period_i", sGodWorshippedSoldierAttackPeriod, 2500);
    loadI("god_worshipped_soldier_attack_range_i", sGodWorshippedSoldierAttackRange, 10);
    loadI("god_worshipped_bless_period_i", sGodWorshippedBlessPeriod, 6000);
    loadI("god_worshipped_bless_range_i", sGodWorshippedBlessRange, 10);

    loadI("soldier_being_attacked_call_range_i", sSoldierBeingAttackedCallRange, 2);

    loadI("tower_hp_i", sTowerHP, 5000);
    loadI("tower_range_i", sTowerRange, 8);
    loadD("tower_attack_d", sTowerAttack, 0.5);

    loadI("wall_hp_i", sWallHP, 2000);

    loadI("wall_archer_range_i", sWallArcherRange, 8);
    loadD("wall_archer_attack_d", sWallArcherAttack, 0.5);

    loadI("rabble_hp_i", sRabbleHP, 300);
    loadI("rabble_range_i", sRabbleRange, 4);
    loadD("rabble_attack_d", sRabbleAttack, 0.05);

    loadI("spearthrower_hp_i", sSpearthrowerHP, 300);
    loadI("spearthrower_range_i", sSpearthrowerRange, 4);
    loadD("spearthrower_attack_d", sSpearthrowerAttack, 0.05);

    loadI("archer_hp_i", sArcherHP, 300);
    loadI("archer_range_i", sArcherRange, 4);
    loadD("archer_attack_d", sArcherAttack, 0.05);

    loadI("hoplite_hp_i", sHopliteHP, 500);
    loadD("hoplite_attack_d", sHopliteAttack, 0.5);

    loadI("chariot_hp_i", sChariotHP, 500);
    loadD("chariot_speed_d", sChariotSpeed, 1.5);
    loadD("chariot_attack_d", sChariotAttack, 0.6);

    loadI("horseman_hp_i", sHorsemanHP, 500);
    loadD("horseman_speed_d", sHorsemanSpeed, 1.5);
    loadD("horseman_attack_d", sHorsemanAttack, 0.6);

    loadI("watchman_hp_i", sWatchmanHP, 200);
    loadD("watchman_attack_d", sWatchmanAttack, 0.5);
    loadI("watchman_satisfaction_provide_i", sWatchmanSatisfactionProvide, 25);

    loadI("defend_city_max_killed_i", sDefendCityMaxKilled, 6);
    loadI("defend_city_talos_max_killed_i", sDefendCityTalosMaxKilled, 16);

    loadI("basic_vendor_max_resource_take_distance_i", sBasicVendorMaxResourceTakeDistance, 60);
    loadI("horse_vendor_max_resource_take_distance_i", sHorseVendorMaxResourceTakeDistance, 200);

    loadI("resource_building_max_resource_give_distance_i", sResourceBuildingMaxResourceGiveDistance, 60);
    loadI("processing_building_max_resource_take_distance_i", sProcessingBuildingMaxResourceTakeDistance, 60);
    loadI("trireme_wharf_max_resource_take_distance_i", sTriremeWharfMaxResourceTakeDistance, 60);
}

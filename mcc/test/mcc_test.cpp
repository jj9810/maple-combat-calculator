#include "combat_power.h"
#include "combat_power_raw.h"
#include "skill_damage.h"
#include "skill_damage_raw.h"
#include "types.h"

#include <cassert>
#include <iostream>

using namespace mcc;

void test_combat_power() {
    std::cout << "Testing calculate_combat_power_raw..." << std::endl;

    // Simple test case with dummy values
    int cp = calculate_combat_power_raw(
        10000, // mainStat
        2000,  // subStat
        1000,  // flatAtt
        500,   // weaponBaseAtt
        100,   // weaponSfAtt
        600,   // standardWeaponAtt
        20.0,  // attPercent
        50.0,  // critDmgPercent
        35.0,  // innateCritDmgPercent
        100.0, // bossDmgPercent
        0.0,   // innateBossDmgPercent
        50.0,  // dmgPercent
        0.0,   // innateDmgPercent
        20.0,  // finalDmgPercent
        0.0    // innateFinalDmgPercent
    );

    std::cout << "Calculated Combat Power: " << cp << std::endl;
    assert(cp > 0);
    std::cout << "Combat Power Test Success!" << std::endl;
}

void test_skill_damage() {
    std::cout << "Testing calc_skill_damage_raw..." << std::endl;

    long long damage = calc_skill_damage_raw(
        500.0,   // skillDamagePercent
        10000.0, // mainStat
        2000.0,  // subStat
        1000.0,  // attack
        95.0,    // masteryPercent
        50.0,    // damagePercent
        20.0,    // finalDamagePercent
        1.0,     // critRatePercent
        50.0,    // critDamagePercent
        90.0,    // ignoreDefensePercent
        1.0,     // elementalAdjustPercent
        300.0,   // mobDefensePercent
        50.0,    // mobElemResPercent
        1.5,     // weaponConst
        1.1,     // levelAdjust
        1.0      // forceAdjust
    );

    std::cout << "Calculated Skill Damage: " << damage << std::endl;
    assert(damage > 0);

    long long percent_scaled_damage = calc_skill_damage_raw(
        100.0, // 100% should be treated as 1.0x, not 100.0x
        100.0,
        0.0,
        100.0,
        100.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        1.0,
        1.0,
        1.0
    );
    assert(percent_scaled_damage == 400);

    long long overcrit_damage = calc_skill_damage_raw(
        240.0,
        133886.0,
        16890.0,
        22967.0,
        91.0,
        741.0,
        98.08,
        111.0,
        196.05,
        99.36,
        0.0,
        300.0,
        0.0,
        1.3,
        1.1,
        1.0
    );
    assert(overcrit_damage <= DEFAULT_MAX_DAMAGE);

    std::cout << "Skill Damage Test Success!" << std::endl;
}

int main() {
    test_combat_power();
    test_skill_damage();
    return 0;
}

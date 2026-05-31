#include "combat_power.h"
#include "common.h"
#include "skill_damage.h"
#include "types.h"
#include "utils.h"

#include <iostream>

using namespace mcc;

mcc_test::MCCStat make_demon_avenger_stat() {
    mcc_test::MCCStat stat;
    stat.set_hp(60000.0);
    stat.set_str(1000.0);
    stat.set_attack_power(700.0);
    stat.set_damage(50.0);
    stat.set_boss_damage(100.0);
    stat.set_final_damage(20.0);
    stat.set_ignore_defense(90.0);
    stat.set_critical_chance(100.0);
    stat.set_critical_damage(50.0);
    return stat;
}

void test_demon_avenger_mapping_uses_effective_hp_and_str() {
    MappedStats mapped = map_stat_type(make_demon_avenger_stat(), MainStatType::HP_DEMON_AVENGER);

    mcc_test::expect_near("demon avenger main hp", mapped.mainStat, 60000.0, 1e-12);
    mcc_test::expect_near("demon avenger sub str", mapped.subStat, 1000.0, 1e-12);
    mcc_test::expect_near("demon avenger attack", mapped.attackOrMagic, 700.0, 1e-12);
}

void test_demon_avenger_combat_power_uses_effective_hp() {
    int combatPower = calculateCombatPower(
        make_demon_avenger_stat(),
        MainStatType::HP_DEMON_AVENGER,
        500,
        100,
        600,
        35.0,
        0.0,
        0.0,
        0.0
    );

    mcc_test::expect_eq("demon avenger calculateCombatPower", combatPower, 8882055);
}

void test_demon_avenger_skill_damage_uses_effective_hp() {
    long long damage = calcSkillDamage(
        200.0,
        make_demon_avenger_stat(),
        MainStatType::HP_DEMON_AVENGER,
        100.0,
        300.0,
        0.0,
        1.3,
        280,
        280,
        ForceType::NONE,
        0
    );

    mcc_test::expect_eq("demon avenger calcSkillDamage", damage, 17040387);
}

int main() {
    test_demon_avenger_mapping_uses_effective_hp_and_str();
    test_demon_avenger_combat_power_uses_effective_hp();
    test_demon_avenger_skill_damage_uses_effective_hp();

    std::cout << "MCC Demon Avenger special stat tests passed." << std::endl;
    return 0;
}

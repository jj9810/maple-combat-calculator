#include "combat_power.h"
#include "common.h"
#include "skill_damage.h"
#include "types.h"
#include "utils.h"
#include "xenon_support.h"

#include <iostream>

using namespace mcc;

mcc_test::MCCStat make_xenon_stat() {
    mcc_test::MCCStat stat;
    stat.set_str(1000.0);
    stat.set_dex(2000.0);
    stat.set_luk(3000.0);
    stat.set_attack_power(700.0);
    stat.set_damage(50.0);
    stat.set_boss_damage(100.0);
    stat.set_final_damage(20.0);
    stat.set_ignore_defense(90.0);
    stat.set_critical_chance(100.0);
    stat.set_critical_damage(50.0);
    return stat;
}

void test_xenon_mapping_keeps_all_stat_shape() {
    MappedStats mapped = map_stat_type(make_xenon_stat(), MainStatType::ALL_XENON);

    mcc_test::expect_near("xenon main stat", mapped.mainStat, 6000.0, 1e-12);
    mcc_test::expect_near("xenon sub stat", mapped.subStat, 0.0, 1e-12);
    mcc_test::expect_near("xenon attack", mapped.attackOrMagic, 700.0, 1e-12);
}

void test_xenon_combat_power_applies_class_multiplier() {
    int combatPower = calculateCombatPower(
        make_xenon_stat(), MainStatType::ALL_XENON, 500, 100, 600, 35.0, 0.0, 0.0, 0.0
    );

    mcc_test::expect_eq("xenon calculateCombatPower", combatPower, 773955);
}

void test_xenon_skill_damage_applies_class_multiplier() {
    long long damage = calcSkillDamage(
        200.0,
        make_xenon_stat(),
        MainStatType::ALL_XENON,
        100.0,
        300.0,
        0.0,
        1.5,
        280,
        280,
        ForceType::NONE,
        0
    );

    mcc_test::expect_eq("xenon calcSkillDamage", damage, 1713285);
}

void test_xenon_dot_damage_applies_class_multiplier() {
    long long damage = calcDotDamage(
        200.0, make_xenon_stat(), MainStatType::ALL_XENON, 0.0, 1.5, 280, 280, ForceType::NONE, 0
    );

    mcc_test::expect_eq("xenon calcDotDamage", damage, 441000);
}

int main() {
    test_xenon_mapping_keeps_all_stat_shape();
    test_xenon_combat_power_applies_class_multiplier();
    test_xenon_skill_damage_applies_class_multiplier();
    test_xenon_dot_damage_applies_class_multiplier();

    std::cout << "MCC Xenon special stat tests passed." << std::endl;
    return 0;
}

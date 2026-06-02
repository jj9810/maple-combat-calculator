#ifndef MCC_TEST_COMMON_H
#define MCC_TEST_COMMON_H

#include "internal/mcc_stat.pb.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

namespace mcc_test {

using maple_combat_calculator::shared::MCCStat;

inline void expect_eq(const std::string& name, long long actual, long long expected) {
    if (actual != expected) {
        std::cerr << name << " failed: expected " << expected << ", got " << actual << std::endl;
    }
    assert(actual == expected);
}

inline void expect_near(const std::string& name, double actual, double expected, double epsilon) {
    if (std::fabs(actual - expected) > epsilon) {
        std::cerr << name << " failed: expected " << expected << ", got " << actual << std::endl;
    }
    assert(std::fabs(actual - expected) <= epsilon);
}

inline MCCStat make_basic_str_stat() {
    MCCStat stat;
    stat.set_str(10000.0);
    stat.set_dex(2000.0);
    stat.set_attack_power(1000.0);
    stat.set_damage(50.0);
    stat.set_boss_damage(100.0);
    stat.set_final_damage(20.0);
    stat.set_ignore_defense(90.0);
    stat.set_critical_chance(1.0);
    stat.set_critical_damage(50.0);
    stat.set_elemental_resistance_ignore(1.0);
    return stat;
}

inline MCCStat make_physical_stat(
    double str,
    double dex,
    double luk,
    double attack,
    double damage,
    double bossDamage,
    double finalDamage,
    double ignoreDefense,
    double criticalChance,
    double criticalDamage
) {
    MCCStat stat;
    stat.set_str(str);
    stat.set_dex(dex);
    stat.set_luk(luk);
    stat.set_attack_power(attack);
    stat.set_damage(damage);
    stat.set_boss_damage(bossDamage);
    stat.set_final_damage(finalDamage);
    stat.set_ignore_defense(ignoreDefense);
    stat.set_critical_chance(criticalChance);
    stat.set_critical_damage(criticalDamage);
    return stat;
}

inline MCCStat make_magic_stat(
    double intStat,
    double luk,
    double magicAttack,
    double damage,
    double bossDamage,
    double finalDamage,
    double ignoreDefense,
    double criticalChance,
    double criticalDamage
) {
    MCCStat stat;
    stat.set_int_(intStat);
    stat.set_luk(luk);
    stat.set_magic_power(magicAttack);
    stat.set_damage(damage);
    stat.set_boss_damage(bossDamage);
    stat.set_final_damage(finalDamage);
    stat.set_ignore_defense(ignoreDefense);
    stat.set_critical_chance(criticalChance);
    stat.set_critical_damage(criticalDamage);
    return stat;
}

} // namespace mcc_test

#endif // MCC_TEST_COMMON_H

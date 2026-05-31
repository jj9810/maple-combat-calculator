#include "adjustments.h"
#include "common.h"
#include "combat_power_raw.h"
#include "skill_damage_raw.h"
#include "types.h"

#include <iostream>

using namespace mcc;

long long raw_policy_damage(
    double skillDamagePercent,
    double mainStat,
    double attack,
    double critRatePercent,
    double ignoreDefensePercent,
    double elementalAdjustPercent,
    double mobDefensePercent,
    double mobElemResPercent
) {
    return calc_skill_damage_raw(
        skillDamagePercent,
        mainStat,
        0.0,
        attack,
        100.0,
        0.0,
        0.0,
        critRatePercent,
        0.0,
        ignoreDefensePercent,
        elementalAdjustPercent,
        mobDefensePercent,
        mobElemResPercent,
        1.0,
        1.0,
        1.0
    );
}

void test_raw_skill_damage_keeps_invalid_scalar_arithmetic() {
    mcc_test::expect_eq(
        "negative stat remains arithmetic input",
        raw_policy_damage(100.0, -100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0),
        -400
    );
    mcc_test::expect_eq(
        "negative attack remains arithmetic input",
        raw_policy_damage(100.0, 100.0, -100.0, 0.0, 0.0, 0.0, 0.0, 0.0),
        -400
    );
    mcc_test::expect_eq(
        "over-100 ignore defense remains arithmetic input",
        raw_policy_damage(100.0, 100.0, 100.0, 0.0, 110.0, 0.0, 300.0, 0.0),
        520
    );
    mcc_test::expect_eq(
        "over-100 elemental ignore remains arithmetic input",
        raw_policy_damage(100.0, 100.0, 100.0, 0.0, 0.0, 120.0, 0.0, 50.0),
        440
    );
}

void test_raw_skill_damage_clamps_only_documented_critical_rate() {
    mcc_test::expect_eq(
        "negative critical chance clamps to zero",
        raw_policy_damage(100.0, 100.0, 100.0, -25.0, 0.0, 0.0, 0.0, 0.0),
        400
    );
    mcc_test::expect_eq(
        "over-100 critical chance clamps to one hundred",
        raw_policy_damage(100.0, 100.0, 100.0, 150.0, 0.0, 0.0, 0.0, 0.0),
        540
    );
}

void test_adjustment_invalid_input_policy() {
    mcc_test::expect_near(
        "non-positive required force is neutral",
        get_force_adjust(ForceType::ARCANE, 0, 0),
        1.0,
        1e-12
    );
    mcc_test::expect_near(
        "level correction has minimum clamp", get_level_adjust(200, 285), 0.1, 1e-12
    );
}

void test_combat_power_raw_requires_nonzero_weapon_base_attack() {
    int combatPower = calculate_combat_power_raw(
        10000.0,
        2000.0,
        1000.0,
        500,
        100,
        600,
        0.0,
        35.0,
        35.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0
    );

    mcc_test::expect_eq("valid combat power policy baseline", combatPower, 634473);
}

int main() {
    test_raw_skill_damage_keeps_invalid_scalar_arithmetic();
    test_raw_skill_damage_clamps_only_documented_critical_rate();
    test_adjustment_invalid_input_policy();
    test_combat_power_raw_requires_nonzero_weapon_base_attack();

    std::cout << "MCC invalid input policy tests passed." << std::endl;
    return 0;
}

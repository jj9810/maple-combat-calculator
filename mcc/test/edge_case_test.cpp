#include "adjustments.h"
#include "common.h"
#include "skill_damage_raw.h"
#include "types.h"

#include <iostream>

using namespace mcc;

long long simple_raw_damage(
    double critRate,
    double ignoreDefense,
    double mobDefense,
    double elementalIgnore,
    double mobElementalRes,
    double mastery
) {
    return calc_skill_damage_raw(
        100.0,
        100.0,
        0.0,
        100.0,
        mastery,
        0.0,
        0.0,
        critRate,
        0.0,
        ignoreDefense,
        elementalIgnore,
        mobDefense,
        mobElementalRes,
        1.0,
        1.0,
        1.0
    );
}

void test_ignore_defense_boundaries() {
    mcc_test::expect_eq(
        "ignore defense 0", simple_raw_damage(0.0, 0.0, 300.0, 0.0, 0.0, 100.0), -800
    );
    mcc_test::expect_eq(
        "ignore defense 100", simple_raw_damage(0.0, 100.0, 300.0, 0.0, 0.0, 100.0), 400
    );
    mcc_test::expect_eq(
        "ignore defense overcap", simple_raw_damage(0.0, 110.0, 300.0, 0.0, 0.0, 100.0), 520
    );
}

void test_critical_chance_boundaries() {
    mcc_test::expect_eq(
        "critical chance 0", simple_raw_damage(0.0, 0.0, 0.0, 0.0, 0.0, 100.0), 400
    );
    mcc_test::expect_eq(
        "critical chance 100", simple_raw_damage(100.0, 0.0, 0.0, 0.0, 0.0, 100.0), 540
    );
    mcc_test::expect_eq(
        "critical chance overcap", simple_raw_damage(150.0, 0.0, 0.0, 0.0, 0.0, 100.0), 540
    );
}

void test_mob_defense_boundaries() {
    mcc_test::expect_eq("mob defense 0", simple_raw_damage(0.0, 0.0, 0.0, 0.0, 0.0, 100.0), 400);
    mcc_test::expect_eq(
        "mob defense 300", simple_raw_damage(0.0, 50.0, 300.0, 0.0, 0.0, 100.0), -200
    );
    mcc_test::expect_eq(
        "mob defense 380", simple_raw_damage(0.0, 50.0, 380.0, 0.0, 0.0, 100.0), -361
    );
}

void test_elemental_resistance_boundaries() {
    mcc_test::expect_eq(
        "elemental resistance no ignore", simple_raw_damage(0.0, 0.0, 0.0, 0.0, 50.0, 100.0), 200
    );
    mcc_test::expect_eq(
        "elemental resistance full ignore",
        simple_raw_damage(0.0, 0.0, 0.0, 100.0, 50.0, 100.0),
        400
    );
}

void test_mastery_boundaries() {
    mcc_test::expect_eq("mastery 50", simple_raw_damage(0.0, 0.0, 0.0, 0.0, 0.0, 50.0), 300);
    mcc_test::expect_eq("mastery 100", simple_raw_damage(0.0, 0.0, 0.0, 0.0, 0.0, 100.0), 400);
}

void test_level_adjust_boundaries() {
    mcc_test::expect_near("level above by 5", get_level_adjust(280, 275), 1.1, 1e-12);
    mcc_test::expect_near("level equal", get_level_adjust(275, 275), 1.0, 1e-12);
    mcc_test::expect_near("level below", get_level_adjust(270, 275), 0.75, 1e-12);
    mcc_test::expect_near("level minimum clamp", get_level_adjust(250, 285), 0.1, 1e-12);
}

void test_force_adjust_boundaries() {
    mcc_test::expect_near(
        "starforce shortage", get_force_adjust(ForceType::STARFORCE, 50, 100), 0.5, 1e-12
    );
    mcc_test::expect_near(
        "starforce equal", get_force_adjust(ForceType::STARFORCE, 100, 100), 1.0, 1e-12
    );
    mcc_test::expect_near(
        "starforce surplus capped", get_force_adjust(ForceType::STARFORCE, 130, 100), 1.2, 1e-12
    );

    mcc_test::expect_near(
        "arcane shortage", get_force_adjust(ForceType::ARCANE, 50, 100), 0.6, 1e-12
    );
    mcc_test::expect_near(
        "arcane equal", get_force_adjust(ForceType::ARCANE, 100, 100), 1.0, 1e-12
    );
    mcc_test::expect_near(
        "arcane surplus capped", get_force_adjust(ForceType::ARCANE, 150, 100), 1.5, 1e-12
    );

    mcc_test::expect_near(
        "authentic shortage", get_force_adjust(ForceType::AUTHENTIC, 50, 100), 0.6, 1e-12
    );
    mcc_test::expect_near(
        "authentic equal", get_force_adjust(ForceType::AUTHENTIC, 100, 100), 1.0, 1e-12
    );
    mcc_test::expect_near(
        "authentic surplus capped", get_force_adjust(ForceType::AUTHENTIC, 160, 100), 1.25, 1e-12
    );
}

int main() {
    test_ignore_defense_boundaries();
    test_critical_chance_boundaries();
    test_mob_defense_boundaries();
    test_elemental_resistance_boundaries();
    test_mastery_boundaries();
    test_level_adjust_boundaries();
    test_force_adjust_boundaries();

    std::cout << "MCC edge-case tests passed." << std::endl;
    return 0;
}

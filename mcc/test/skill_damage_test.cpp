#include "common.h"
#include "skill_damage.h"
#include "skill_damage_raw.h"
#include "types.h"

#include <iostream>

using namespace mcc;

void test_skill_damage_raw_expected_value() {
    long long damage = calc_skill_damage_raw(
        500.0,
        10000.0,
        2000.0,
        1000.0,
        95.0,
        50.0,
        20.0,
        1.0,
        50.0,
        90.0,
        1.0,
        300.0,
        50.0,
        1.5,
        1.1,
        1.0
    );

    mcc_test::expect_eq("calc_skill_damage_raw", damage, 2167932);
}

void test_skill_damage_percent_input_is_scaled_once() {
    long long damage = calc_skill_damage_raw(
        100.0, 100.0, 0.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0
    );

    mcc_test::expect_eq("calc_skill_damage_raw percent scaling", damage, 400);
}

void test_skill_damage_public_wrapper_expected_value() {
    long long damage = calcSkillDamage(
        500.0,
        mcc_test::make_basic_str_stat(),
        MainStatType::STR,
        95.0,
        300.0,
        50.0,
        1.5,
        275,
        270,
        ForceType::NONE,
        0
    );

    mcc_test::expect_eq("calcSkillDamage", damage, 3613219);
}

void test_dot_damage_expected_value() {
    long long damage = calcDotDamage(
        100.0,
        mcc_test::make_basic_str_stat(),
        MainStatType::STR,
        50.0,
        1.5,
        275,
        270,
        ForceType::NONE,
        0
    );

    mcc_test::expect_eq("calcDotDamage", damage, 318150);
}

int main() {
    test_skill_damage_raw_expected_value();
    test_skill_damage_percent_input_is_scaled_once();
    test_skill_damage_public_wrapper_expected_value();
    test_dot_damage_expected_value();

    std::cout << "MCC skill damage tests passed." << std::endl;
    return 0;
}

#include "combat_power.h"
#include "combat_power_raw.h"
#include "common.h"
#include "types.h"

#include <iostream>

using namespace mcc;

void test_combat_power_raw_expected_value() {
    int combat_power = calculate_combat_power_raw(
        10000, 2000, 1000, 500, 100, 600, 20.0, 50.0, 35.0, 100.0, 0.0, 50.0, 0.0, 20.0, 0.0
    );

    mcc_test::expect_eq("calculate_combat_power_raw", combat_power, 2536380);
}

void test_combat_power_public_wrapper_expected_value() {
    int combat_power = calculateCombatPower(
        mcc_test::make_basic_str_stat(), MainStatType::STR, 500, 100, 600, 35.0, 0.0, 0.0, 0.0
    );

    mcc_test::expect_eq("calculateCombatPower", combat_power, 2114910);
}

int main() {
    test_combat_power_raw_expected_value();
    test_combat_power_public_wrapper_expected_value();

    std::cout << "MCC combat power tests passed." << std::endl;
    return 0;
}

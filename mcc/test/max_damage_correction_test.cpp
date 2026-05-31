#include "common.h"
#include "max_damage_correction.h"
#include "types.h"

#include <iostream>

using namespace mcc;

void test_max_damage_correction_no_cap_expected_value() {
    long long corrected = apply_max_damage_correction(12345, 1000.0, 50.0, 95.0, true);

    mcc_test::expect_eq("apply_max_damage_correction no cap", corrected, 12345);
}

void test_max_damage_correction_all_cap_expected_value() {
    long long corrected = apply_max_damage_correction(999999, 1000000000000.0, 50.0, 95.0, true);

    mcc_test::expect_eq("apply_max_damage_correction all cap", corrected, DEFAULT_MAX_DAMAGE);
}

int main() {
    test_max_damage_correction_no_cap_expected_value();
    test_max_damage_correction_all_cap_expected_value();

    std::cout << "MCC max damage correction tests passed." << std::endl;
    return 0;
}

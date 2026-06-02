#include "common.h"
#include "skill_damage.h"
#include "types.h"

#include <iostream>

using namespace mcc;

void test_adele_divide_against_default_boss() {
    auto stat = mcc_test::make_physical_stat(
        45000.0, 5000.0, 1000.0, 3000.0, 120.0, 350.0, 10.0, 96.0, 100.0, 85.0
    );

    long long damage = calcSkillDamage(
        375.0, stat, MainStatType::STR, 95.0, 300.0, 0.0, 1.3, 275, 285, ForceType::NONE, 0
    );

    mcc_test::expect_eq("Adele Divide default boss", damage, 160108768);
}

void test_adele_divide_against_training_dummy() {
    auto stat = mcc_test::make_physical_stat(
        45000.0, 5000.0, 1000.0, 3000.0, 120.0, 350.0, 10.0, 96.0, 100.0, 85.0
    );

    long long damage = calcSkillDamage(
        375.0, stat, MainStatType::STR, 95.0, 0.0, 0.0, 1.3, 275, 275, ForceType::NONE, 0
    );

    mcc_test::expect_eq("Adele Divide training dummy", damage, 363883564);
}

void test_bishop_angel_ray_against_default_boss() {
    auto stat =
        mcc_test::make_magic_stat(38000.0, 4000.0, 2800.0, 40.0, 200.0, 91.0, 96.0, 75.0, 15.0);

    long long damage = calcSkillDamage(
        225.0, stat, MainStatType::INT, 70.0, 300.0, 0.0, 1.2, 275, 285, ForceType::NONE, 0
    );

    mcc_test::expect_eq("Bishop AngelRay default boss", damage, 39385192);
}

void test_bowmaster_hurricane_against_default_boss() {
    auto stat = mcc_test::make_physical_stat(
        4500.0, 39000.0, 1000.0, 2900.0, 60.0, 250.0, 30.0, 96.0, 65.0, 41.0
    );

    long long damage = calcSkillDamage(
        262.5, stat, MainStatType::DEX, 70.0, 300.0, 0.0, 1.3, 275, 285, ForceType::NONE, 0
    );

    mcc_test::expect_eq("Bowmaster Hurricane default boss", damage, 47303698);
}

void test_dual_blade_phantom_blow_against_default_boss() {
    auto stat = mcc_test::make_physical_stat(
        4000.0, 5000.0, 41000.0, 3100.0, 90.0, 250.0, 20.0, 96.0, 40.0, 15.0
    );

    long long damage = calcSkillDamage(
        330.0,
        stat,
        MainStatType::LUK_SECONDARY,
        70.0,
        300.0,
        0.0,
        1.3,
        275,
        285,
        ForceType::NONE,
        0
    );

    mcc_test::expect_eq("DualBlade PhantomBlow default boss", damage, 54519499);
}

void test_ren_ghost_sword_strike_against_default_boss() {
    auto stat = mcc_test::make_physical_stat(
        43000.0, 5000.0, 1000.0, 3200.0, 91.0, 250.0, 0.0, 96.0, 60.0, 21.0
    );

    long long damage = calcSkillDamage(
        743.0, stat, MainStatType::STR, 70.0, 300.0, 0.0, 1.34, 275, 285, ForceType::NONE, 0
    );

    mcc_test::expect_eq("Ren GhostSwordStrike3 default boss", damage, 124260616);
}

int main() {
    test_adele_divide_against_default_boss();
    test_adele_divide_against_training_dummy();
    test_bishop_angel_ray_against_default_boss();
    test_bowmaster_hurricane_against_default_boss();
    test_dual_blade_phantom_blow_against_default_boss();
    test_ren_ghost_sword_strike_against_default_boss();

    std::cout << "MCC ground-truth baseline tests passed." << std::endl;
    return 0;
}

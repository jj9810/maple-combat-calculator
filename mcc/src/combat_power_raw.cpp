#include "combat_power_raw.h"

#include "utils.h"

#include <cmath>

namespace mcc {

int calculate_combat_power_raw(
    int mainStat,
    int subStat,
    int flatAtt,
    int weaponBaseAtt,
    int weaponSfAtt,
    int standardWeaponAtt,
    double attPercent,
    double critDmgPercent,
    double innateCritDmgPercent,
    double bossDmgPercent,
    double innateBossDmgPercent,
    double dmgPercent,
    double innateDmgPercent,
    double finalDmgPercent,
    double innateFinalDmgPercent
) {
    // totalFlatAtt 계산 로직:
    // flatAtt(주인공격력/마력)에 무기 관련 보정치를 계산하여 합산합니다.
    double totalFlatAtt =
        flatAtt + std::floor(
                      (static_cast<double>(standardWeaponAtt) / weaponBaseAtt - 1.0) *
                      (weaponBaseAtt + weaponSfAtt)
                  );

    double attMul = to_multiplier(attPercent);

    return static_cast<int>(std::floor(
        BASE_RATIO * (mainStat * 4 + subStat) * std::floor(totalFlatAtt * attMul) *
        to_multiplier(critDmgPercent - innateCritDmgPercent + BASE_CRIT_CONSTANT) *
        to_multiplier(bossDmgPercent - innateBossDmgPercent + dmgPercent - innateDmgPercent) *
        (to_multiplier(finalDmgPercent) / to_multiplier(innateFinalDmgPercent))
    ));
}

} // namespace mcc

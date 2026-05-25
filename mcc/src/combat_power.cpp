#include "combat_power.h"

#include "combat_power_raw.h"
#include "internal/mcc_stat.pb.h"
#include "utils.h"

namespace mcc {

int calculateCombatPower(
    const maple_combat_calculator::shared::MCCStat& stat,
    MainStatType mainStatType,
    int weaponBaseAtt,
    int weaponSfAtt,
    int standardWeaponAtt,
    double innateCritDmgPercent,
    double innateBossDmgPercent,
    double innateDmgPercent,
    double innateFinalDmgPercent
) {
    // StatType 로직을 별개 함수로 분리하여 사용합니다.
    MappedStats mapped = map_stat_type(stat, mainStatType);

    // 무기 및 기본 제공(innate) 정보를 모두 외부에서 받아 기존 함수로 전달합니다.
    return calculate_combat_power_raw(
        static_cast<int>(mapped.mainStat),
        static_cast<int>(mapped.subStat),
        static_cast<int>(mapped.attackOrMagic),
        weaponBaseAtt,
        weaponSfAtt,
        standardWeaponAtt,
        0, // attPercent (이미 합산됨)
        stat.critical_damage(),
        innateCritDmgPercent,
        stat.boss_damage(),
        innateBossDmgPercent,
        stat.damage(),
        innateDmgPercent,
        stat.final_damage(),
        innateFinalDmgPercent
    );
}

} // namespace mcc

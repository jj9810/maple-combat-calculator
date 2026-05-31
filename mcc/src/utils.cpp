#include "utils.h"

#if MCC_ENABLE_DEMON_AVENGER_SUPPORT
#include "demon_avenger_support.h"
#endif
#include "internal/mcc_stat.pb.h"
#if MCC_ENABLE_XENON_SUPPORT
#include "xenon_support.h"
#endif

#include <algorithm>

namespace mcc {

MappedStats
map_stat_type(const maple_combat_calculator::shared::MCCStat& stat, MainStatType mainStatType) {
    MappedStats mapped = {0, 0, 0};

    switch (mainStatType) {
    case MainStatType::STR: // STR
        mapped.mainStat = stat.str();
        mapped.subStat = stat.dex();
        mapped.attackOrMagic = stat.attack_power();
        break;
    case MainStatType::DEX: // DEX
        mapped.mainStat = stat.dex();
        mapped.subStat = stat.str();
        mapped.attackOrMagic = stat.attack_power();
        break;
    case MainStatType::INT: // INT
        mapped.mainStat = stat.int_();
        mapped.subStat = stat.luk();
        mapped.attackOrMagic = stat.magic_power();
        break;
    case MainStatType::LUK: // LUK
        mapped.mainStat = stat.luk();
        mapped.subStat = stat.dex();
        mapped.attackOrMagic = stat.attack_power();
        break;
    case MainStatType::LUK_SECONDARY: // LUK (Dual Blade 등)
        mapped.mainStat = stat.luk();
        mapped.subStat = stat.str() + stat.dex();
        mapped.attackOrMagic = stat.attack_power();
        break;
    case MainStatType::ALL_XENON: // ALL (Xenon)
#if MCC_ENABLE_XENON_SUPPORT
        if (is_xenon(mainStatType)) {
            mapped = map_xenon_stats(stat);
        }
#endif
        break;
    case MainStatType::HP_DEMON_AVENGER: // HP (Demon Avenger)
#if MCC_ENABLE_DEMON_AVENGER_SUPPORT
        if (is_demon_avenger(mainStatType)) {
            mapped = map_demon_avenger_stats(stat);
        }
#endif
        break;
    default:
        // 알 수 없는 타입의 경우 가장 높은 수치를 사용하도록 예외 처리
        mapped.mainStat = std::max({stat.str(), stat.dex(), stat.int_(), stat.luk()});
        mapped.attackOrMagic = std::max(stat.attack_power(), stat.magic_power());
    }

    return mapped;
}

int get_force_value(const maple_combat_calculator::shared::MCCStat& stat, ForceType forceType) {
    switch (forceType) {
    case ForceType::STARFORCE:
        return stat.starforce();
    case ForceType::ARCANE:
        return stat.arcaneforce();
    case ForceType::AUTHENTIC:
        return stat.authenticforce();
    default:
        return 0;
    }
}

} // namespace mcc

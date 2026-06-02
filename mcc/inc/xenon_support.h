#ifndef MCC_XENON_SUPPORT_H
#define MCC_XENON_SUPPORT_H

#include "internal/mcc_stat.pb.h"
#include "types.h"

namespace mcc {

#if MCC_ENABLE_XENON_SUPPORT

constexpr double XENON_FINAL_DAMAGE_MULTIPLIER = 0.875;

inline bool is_xenon(MainStatType mainStatType) {
    return mainStatType == MainStatType::ALL_XENON;
}

inline MappedStats map_xenon_stats(const maple_combat_calculator::shared::MCCStat& stat) {
    return {stat.str() + stat.dex() + stat.luk(), 0.0, stat.attack_power()};
}

inline double
apply_xenon_final_damage_multiplier(double finalDamagePercent, MainStatType mainStatType) {
    if (!is_xenon(mainStatType)) {
        return finalDamagePercent;
    }

    return ((1.0 + finalDamagePercent * 0.01) * XENON_FINAL_DAMAGE_MULTIPLIER - 1.0) * 100.0;
}

inline double xenon_dot_final_damage_percent(MainStatType mainStatType) {
    return is_xenon(mainStatType) ? (XENON_FINAL_DAMAGE_MULTIPLIER - 1.0) * 100.0 : 0.0;
}

#else

inline bool is_xenon(MainStatType) {
    return false;
}

inline double apply_xenon_final_damage_multiplier(double finalDamagePercent, MainStatType) {
    return finalDamagePercent;
}

inline double xenon_dot_final_damage_percent(MainStatType) {
    return 0.0;
}

#endif // MCC_ENABLE_XENON_SUPPORT

} // namespace mcc

#endif // MCC_XENON_SUPPORT_H

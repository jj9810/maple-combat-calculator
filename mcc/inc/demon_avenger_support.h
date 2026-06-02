#ifndef MCC_DEMON_AVENGER_SUPPORT_H
#define MCC_DEMON_AVENGER_SUPPORT_H

#include "internal/mcc_stat.pb.h"
#include "types.h"

namespace mcc {

#if MCC_ENABLE_DEMON_AVENGER_SUPPORT

inline bool is_demon_avenger(MainStatType mainStatType) {
    return mainStatType == MainStatType::HP_DEMON_AVENGER;
}

inline MappedStats map_demon_avenger_stats(const maple_combat_calculator::shared::MCCStat& stat) {
    return {stat.hp(), stat.str(), stat.attack_power()};
}

#else

inline bool is_demon_avenger(MainStatType) {
    return false;
}

#endif // MCC_ENABLE_DEMON_AVENGER_SUPPORT

} // namespace mcc

#endif // MCC_DEMON_AVENGER_SUPPORT_H

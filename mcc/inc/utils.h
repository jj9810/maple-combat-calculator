#ifndef MCC_UTILS_H
#define MCC_UTILS_H

#include "types.h"

namespace maple_combat_calculator::shared {
class MCCStat;
}

namespace mcc {

/**
 * Stat과 StatType을 기반으로 주스탯, 부스탯, 공격력/마력을 매핑합니다.
 */
MappedStats
map_stat_type(const maple_combat_calculator::shared::MCCStat& stat, MainStatType mainStatType);

/**
 * 포스 타입에 맞는 포스 수치를 추출합니다.
 */
int get_force_value(const maple_combat_calculator::shared::MCCStat& stat, ForceType forceType);

/**
 * 퍼센트 수치를 배율로 변환합니다. (예: 10% -> 1.1)
 */
inline double to_multiplier(double percent) {
    return 1.0 + percent * 0.01;
}

/**
 * 퍼센트 수치의 보수 배율을 반환합니다. (예: 10% -> 0.9)
 * 방어율 무시, 방어율에 따른 데미지 감소 등에 사용됩니다.
 */
inline double to_complement_multiplier(double percent) {
    return 1.0 - percent * 0.01;
}

} // namespace mcc

#endif // MCC_UTILS_H

//
// Created by ubuntu on 25. 8. 10..
//

#ifndef MCC_SKILL_DAMAGE_H
#define MCC_SKILL_DAMAGE_H

#include "types.h"

namespace maple_combat_calculator::shared {
class MCCStat;
}

namespace mcc {

/**
 * 공식 API 기반의 Stat을 사용하여 스킬 데미지를 계산합니다.
 */
long long calcSkillDamage(
    double skillDamage,
    const maple_combat_calculator::shared::MCCStat& stat,
    MainStatType mainStatType,
    double mastery,
    double mobDefense,
    double mobElemRes,
    double weaponConst,
    int charLevel,
    int mobLevel,
    ForceType forceType,
    int reqForce
);

/**
 * 공식 API 기반의 Stat을 사용하여 도트 데미지를 계산합니다.
 */
long long calcDotDamage(
    double skillDamage,
    const maple_combat_calculator::shared::MCCStat& stat,
    MainStatType mainStatType,
    double mobElemRes,
    double weaponConst,
    int charLevel,
    int mobLevel,
    ForceType forceType,
    int reqForce
);

} // namespace mcc

#endif // MCC_SKILL_DAMAGE_H

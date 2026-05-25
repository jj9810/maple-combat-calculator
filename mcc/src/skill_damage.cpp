//
// Created by ubuntu on 25. 8. 10..
//

#include "skill_damage.h"

#include "adjustments.h"
#include "internal/mcc_stat.pb.h"
#include "skill_damage_raw.h"
#include "utils.h"

#include <algorithm>

namespace mcc {

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
) {
    // StatType 로직을 사용하여 필요한 스탯을 매핑합니다.
    MappedStats mapped = map_stat_type(stat, mainStatType);

    double levelAdjust = get_level_adjust(charLevel, mobLevel);
    int myForce = get_force_value(stat, forceType);
    double forceAdjust = get_force_adjust(forceType, myForce, reqForce);

    // 공식 API 기반의 MCCStat은 이미 최종 합산된 값을 제공하므로,
    // 기존의 복잡한 개별 파라미터 대신 필요한 필드를 직접 추출하여 계산합니다.
    return calc_skill_damage_raw(
        skillDamage,
        mapped.mainStat,
        mapped.subStat,
        mapped.attackOrMagic,
        mastery,
        stat.damage() + stat.boss_damage(), // 데미지 + 보공 합산
        stat.final_damage(),
        stat.critical_chance(),
        stat.critical_damage(),
        stat.ignore_defense(),              // MCM에서 이미 합산된 값을 사용
        stat.elemental_resistance_ignore(), // stat 내부의 속성 내성 무시 사용
        mobDefense,
        mobElemRes,
        weaponConst,
        levelAdjust,
        forceAdjust
    );
}

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
) {
    MappedStats mapped = map_stat_type(stat, mainStatType);

    double levelAdjust = get_level_adjust(charLevel, mobLevel);
    int myForce = get_force_value(stat, forceType);
    double forceAdjust = get_force_adjust(forceType, myForce, reqForce);

    // DOT 데미지 특성 (인벤 실험 참고: https://www.inven.co.kr/board/maple/2304/24096)
    return calc_skill_damage_raw(
        skillDamage,
        mapped.mainStat,
        mapped.subStat,
        mapped.attackOrMagic,
        100.0, // mastery: 도트딜은 숙련도 100% (고정 데미지)
        0.0,   // damagePercent: 미적용
        0.0,   // finalDamagePercent: 미적용
        0.0,   // critRate: 크리티컬 미적용
        0.0,   // critDamagePercent: 크리티컬 데미지 미적용
        0.0,   // ignoreDefense: 방무 미적용
        stat.elemental_resistance_ignore(), // elementalAdjust
        0.0,                                // mobDefense: 방어율 무시 (0으로 처리)
        mobElemRes,
        weaponConst,
        std::min(1.0, levelAdjust), // 레벨 보정은 1.0 이하(감소)만 적용
        forceAdjust
    );
}

} // namespace mcc

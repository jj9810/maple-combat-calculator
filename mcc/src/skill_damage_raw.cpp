#include "skill_damage_raw.h"

#include "max_damage_correction.h"
#include "utils.h"

#include <algorithm>
#include <cmath>

namespace mcc {

inline long long calc_average_skill_damage(
    double damageBaseVal, double masteryPercent, double critDamagePercent, bool isCrit
) {
    // mastery는 % 단위이므로 비율로 변환
    return std::floor(
        damageBaseVal * (to_multiplier(masteryPercent - 100.0) + 1.0) / 2.0 *
        (isCrit ? (CRIT_RATIO_MEAN + critDamagePercent * 0.01) : 1.0)
    );
}

/**
 * 스킬의 최종 데미지를 계산하는 핵심 함수
 */
long long calc_skill_damage_raw(
    double skillDamagePercent,
    double mainStat,
    double subStat,
    double attack,
    double masteryPercent,
    double damagePercent,
    double finalDamagePercent,
    double critRatePercent,
    double critDamagePercent,
    double ignoreDefensePercent,
    double elementalAdjustPercent,
    double mobDefensePercent,
    double mobElemResPercent,
    double weaponConst,
    double levelAdjust,
    double forceAdjust
) {
    // (주스텟*4 + 부스텟) / 100
    double statRatio = (mainStat * 4 + subStat) * 0.01;
    double skillDamageRatio = skillDamagePercent * 0.01;

    double damageRatio = to_multiplier(damagePercent);
    double finalDamageRatio = to_multiplier(finalDamagePercent);
    double clampedCritRatePercent = std::clamp(critRatePercent, 0.0, 100.0);

    double defenseRatio = to_complement_multiplier(
        mobDefensePercent * to_complement_multiplier(ignoreDefensePercent)
    );

    // {1 - 속성내성% * (1 - 내속성무시%)}
    double elementalRatio = to_complement_multiplier(
        mobElemResPercent * to_complement_multiplier(elementalAdjustPercent)
    );

    double maxDamageVal = skillDamageRatio * statRatio * weaponConst * attack * damageRatio *
                          finalDamageRatio * defenseRatio * elementalRatio * levelAdjust *
                          forceAdjust;

    long long averageDamageCrit =
        calc_average_skill_damage(maxDamageVal, masteryPercent, critDamagePercent, true);
    long long averageDamageNonCrit =
        calc_average_skill_damage(maxDamageVal, masteryPercent, 0, false);

#if MAX_DAMAGE_CAP
    long long correctedAverageDamageCrit = apply_max_damage_correction(
        averageDamageCrit, maxDamageVal, critDamagePercent, masteryPercent, true
    );
    long long correctedAverageDamageNonCrit =
        apply_max_damage_correction(averageDamageNonCrit, maxDamageVal, 0, masteryPercent, false);
    long long averageDamageFinal = static_cast<long long>(
        (clampedCritRatePercent * 0.01 * correctedAverageDamageCrit) +
        ((100.0 - clampedCritRatePercent) * 0.01 * correctedAverageDamageNonCrit)
    );
    return averageDamageFinal;
#else
    long long averageDamage = static_cast<long long>(
        (clampedCritRatePercent * 0.01 * averageDamageCrit) +
        ((100.0 - clampedCritRatePercent) * 0.01 * averageDamageNonCrit)
    );
    return averageDamage;
#endif
}

} // namespace mcc

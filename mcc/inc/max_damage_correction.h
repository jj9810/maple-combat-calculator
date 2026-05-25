#ifndef MCC_MAX_DAMAGE_CORRECTION_H
#define MCC_MAX_DAMAGE_CORRECTION_H

namespace mcc {

/**
 * 맥뎀 보정 계산 함수
 * @param averageDamage 평균 데미지
 * @param maxDamageVal (크리티컬 데미지 증폭 미적용 기준) 최대 데미지 값
 * @param critDamagePercent 크리티컬 데미지 (%)
 * @param mastery 숙련도 (%)
 * @param isCrit 크리티컬 여부
 * @return 보정된 데미지
 */
long long apply_max_damage_correction(
    long long averageDamage,
    double maxDamageVal,
    double critDamagePercent,
    double mastery,
    bool isCrit
);

} // namespace mcc

#endif // MCC_MAX_DAMAGE_CORRECTION_H

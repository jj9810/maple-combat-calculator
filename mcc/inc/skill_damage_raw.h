#ifndef MCC_SKILL_DAMAGE_RAW_H
#define MCC_SKILL_DAMAGE_RAW_H

namespace mcc {

/**
 * 스킬의 최종 데미지를 계산하는 가장 기본적인 함수
 * @param skillDamagePercent 스킬 데미지 퍼센트 (예: 500.0)
 * @param mainStat 주스탯 실제값 (예: 10000.0)
 * @param subStat 부스탯 실제값 (예: 2000.0)
 * @param attack 공격력/마력 실제값 (예: 1000.0)
 * @param masteryPercent 숙련도 퍼센트 (예: 95.0)
 * @param damagePercent 데미지% + 보스 데미지% 합산 (예: 450.0)
 * @param finalDamagePercent 최종 데미지 퍼센트 (예: 50.0)
 * @param critRatePercent 크리티컬 확률 퍼센트 (0.0 ~ 100.0)
 * @param critDamagePercent 크리티컬 데미지 퍼센트 (예: 80.0)
 * @param ignoreDefensePercent 방어율 무시 퍼센트 (예: 95.0)
 * @param elementalAdjustPercent 속성 내성 무시 퍼센트 (예: 10.0)
 * @param mobDefensePercent 몬스터 방어율 퍼센트 (예: 300.0)
 * @param mobElemResPercent 몬스터 속성 내성 퍼센트 (예: 50.0)
 * @param weaponConst 무기 상수 배율 (예: 1.5)
 * @param levelAdjust 레벨 차이 보정 배율 (예: 1.1)
 * @param forceAdjust 포스 차이 보정 배율 (예: 1.0)
 * @return 계산된 최종 평균 데미지
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
);

} // namespace mcc

#endif // MCC_SKILL_DAMAGE_RAW_H

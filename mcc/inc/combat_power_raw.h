#ifndef MCC_COMBAT_POWER_RAW_H
#define MCC_COMBAT_POWER_RAW_H

namespace mcc {

/**
 * 캐릭터의 상세 스탯 수치들을 직접 입력받아 전투력을 계산합니다.
 * @param mainStat 주스탯 실제값
 * @param subStat 부스탯 실제값
 * @param flatAtt 순수 공격력/마력 실제값
 * @param weaponBaseAtt 무기 기본 공격력/마력
 * @param weaponSfAtt 무기 스타포스 공격력/마력
 * @param standardWeaponAtt 전투력 계산 기준이 되는 표준 무기의 공격력/마력
 * @param attPercent 공격력/마력 퍼센트 (예: 20.0)
 * @param critDmgPercent 크리티컬 데미지 퍼센트 (예: 80.0)
 * @param innateCritDmgPercent 기본 제공 크리티컬 데미지 퍼센트
 * @param bossDmgPercent 보스 데미지 퍼센트
 * @param innateBossDmgPercent 기본 제공 보스 데미지 퍼센트
 * @param dmgPercent 데미지 퍼센트
 * @param innateDmgPercent 기본 제공 데미지 퍼센트
 * @param finalDmgPercent 최종 데미지 퍼센트
 * @param innateFinalDmgPercent 기본 제공 최종 데미지 퍼센트
 * @return 계산된 전투력
 */
int calculate_combat_power_raw(
    int mainStat,
    int subStat,
    int flatAtt,
    int weaponBaseAtt,
    int weaponSfAtt,
    int standardWeaponAtt,
    double attPercent,
    double critDmgPercent,
    double innateCritDmgPercent,
    double bossDmgPercent,
    double innateBossDmgPercent,
    double dmgPercent,
    double innateDmgPercent,
    double finalDmgPercent,
    double innateFinalDmgPercent
);

} // namespace mcc

#endif // MCC_COMBAT_POWER_RAW_H

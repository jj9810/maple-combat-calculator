#ifndef MCC_LIBRARY_H
#define MCC_LIBRARY_H

#include "types.h"

namespace maple_combat_calculator::shared {
class MCCStat;
}

namespace mcc {

/***
 *
 * https://maplestorywiki.net/w/Combat_Power
 *
 * https://python-fiddle.com/saved/Hv6sN7miNlXfTijSoTO6
 *
 */

/**
 * 공식 API 기반의 Stat과 무기 및 기본 제공(innate) 수치를 입력으로 받아 전투력을 계산합니다.
 * @param stat 최종 합산된 스탯 정보를 담은 객체
 * @param mainStatType 캐릭터의 주스탯 종류 (enum)
 * @param weaponBaseAtt 무기 기본 공격력/마력
 * @param weaponSfAtt 무기 스타포스 공격력/마력
 * @param standardWeaponAtt 전투력 계산 기준이 되는 표준 무기의 공격력/마력
 * @param innateCritDmgPercent 기본 제공 크리티컬 데미지 퍼센트 (일반적으로 35.0%)
 * @param innateBossDmgPercent 기본 제공 보스 데미지 퍼센트
 * @param innateDmgPercent 기본 제공 데미지 퍼센트
 * @param innateFinalDmgPercent 기본 제공 최종 데미지 퍼센트
 * @return 계산된 전투력
 */
int calculateCombatPower(
    const maple_combat_calculator::shared::MCCStat& stat,
    MainStatType mainStatType,
    int weaponBaseAtt,
    int weaponSfAtt,
    int standardWeaponAtt,
    double innateCritDmgPercent,
    double innateBossDmgPercent,
    double innateDmgPercent,
    double innateFinalDmgPercent
);

} // namespace mcc

#endif // MCC_LIBRARY_H

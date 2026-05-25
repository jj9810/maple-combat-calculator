#ifndef MCC_ADJUSTMENTS_H
#define MCC_ADJUSTMENTS_H

#include "types.h"

namespace mcc {

/**
 * 레벨 차이에 따른 데미지 보정 배율을 계산합니다.
 */
double get_level_adjust(int charLevel, int mobLevel);

/**
 * 포스(ARC/AUT/STAR) 요구치에 따른 데미지 보정 배율을 계산합니다.
 */
double get_force_adjust(ForceType type, int myForce, int reqForce);

} // namespace mcc

#endif // MCC_ADJUSTMENTS_H

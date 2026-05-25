#include "max_damage_correction.h"

#include "types.h"

#include <boost/multiprecision/cpp_bin_float.hpp>

using namespace boost::multiprecision;

namespace mcc {

typedef cpp_bin_float_quad high_float;

long long apply_max_damage_correction(
    long long averageDamage,
    double maxDamageVal,
    double critDamagePercent,
    double mastery,
    bool isCrit
) {
    high_float D = DEFAULT_MAX_DAMAGE; // 맥뎀 기준값 (고정밀도)

    high_float minCrit = isCrit ? high_float(CRIT_RATIO_MIN) + high_float(critDamagePercent) * 0.01
                                : high_float(1.0);
    high_float maxCrit = isCrit ? high_float(CRIT_RATIO_MAX) + high_float(critDamagePercent) * 0.01
                                : high_float(1.0);

    high_float x1 = high_float(maxDamageVal) * (high_float(mastery) * 0.01);
    high_float x2 = high_float(maxDamageVal);
    high_float y1 = minCrit;
    high_float y2 = maxCrit;

    // 이론상 최대치가 맥뎀 미만인 경우
    if (x2 * y2 <= D) {
        return averageDamage;
    }

    // 모든 데미지가 맥뎀 이상인 경우
    if (x1 * y1 >= D) {
        return static_cast<long long>(D);
    }

    // x1 == x2 이고 y1 == y2 인 경우는 위에서 이미 처리됨 (x2*y2 <= D 또는 x1*y1 >= D)

    // y1 == y2 인 경우 (예: Non-Crit) - 1차원 적분
    if (y1 == y2) {
        high_float x_p = D / y1;
        high_float result = ((y1 / 2.0) * (x_p * x_p - x1 * x1) + D * (x2 - x_p)) / (x2 - x1);
        return static_cast<long long>(result);
    }

    // x1 == x2 인 경우 (예: 숙련도 100%) - 1차원 적분
    if (x1 == x2) {
        high_float y_p = D / x1;
        high_float result = ((x1 / 2.0) * (y_p * y_p - y1 * y1) + D * (y2 - y_p)) / (y2 - y1);
        return static_cast<long long>(result);
    }

    high_float normalizer = (x2 - x1) * (y2 - y1);
    high_float basis = (x1 + x2) / 2.0 * (y1 + y2) / 2.0;

    // Case별 맥뎀 보정 (E[min(D, xy)] 계산)
    // Reference:
    // https://github.com/oleneyl/maplestory_dpm_calc/blob/master/dpmModule/kernel/core.py

    if (D > x1 * y2 && D > x2 * y1) {
        high_float x_p = D / y2;
        // Case 1
        high_float excess = D * y2 * (x2 - x_p) - (y2 * y2 / 4.0) * (x2 * x2 - x_p * x_p) -
                            (D * D / 2.0) * log(x2 / x_p);
        high_float result = basis + excess / normalizer;
        return static_cast<long long>(result);
    } else if (D <= x1 * y2 && D > x2 * y1) {
        // Case 2
        high_float x_p = x1;
        high_float excess = D * y2 * (x2 - x_p) - (y2 * y2 / 4.0) * (x2 * x2 - x_p * x_p) -
                            (D * D / 2.0) * log(x2 / x_p);
        high_float result = basis + excess / normalizer;
        return static_cast<long long>(result);
    } else if (D > x1 * y2 && D <= x2 * y1) {
        // Case 3: Swap x and y to reuse Case 2 logic
        high_float y_p_c3 = D / x2;
        high_float excess = D * x2 * (y2 - y_p_c3) - (x2 * x2 / 4.0) * (y2 * y2 - y_p_c3 * y_p_c3) -
                            (D * D / 2.0) * log(y2 / y_p_c3);
        high_float result = basis + excess / normalizer;
        return static_cast<long long>(result);
    } else if (D > x1 * y1) {
        // Case 4
        high_float x_p = D / y1;
        high_float excess = D * y1 * (x_p - x1) - (y1 * y1 / 4.0) * (x_p * x_p - x1 * x1) -
                            (D * D / 2.0) * log(x_p / x1);
        high_float result = D + excess / normalizer;
        return static_cast<long long>(result);
    }

    return static_cast<long long>(D);
}

} // namespace mcc

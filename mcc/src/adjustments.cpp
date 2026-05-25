#include "adjustments.h"

#include "utils.h"

#include <algorithm>

namespace mcc {

double get_level_adjust(int charLevel, int mobLevel) {
    int level_diff = charLevel - mobLevel;
    if (level_diff >= 5) return 1.1;
    if (level_diff >= 0) return 1.0 + (level_diff * 0.02);

    double adjust = 1.0 + (level_diff * 0.05);
    return std::max(0.1, adjust);
}

double get_force_adjust(ForceType type, int myForce, int reqForce) {
    if (reqForce <= 0) return 1.0;

    switch (type) {
    case ForceType::STARFORCE: {
        if (myForce >= reqForce) {
            int excess = myForce - reqForce;
            return to_multiplier(std::min(excess, 20));
        }

        double ratio = static_cast<double>(myForce) / reqForce;
        if (ratio >= 0.7) return 0.7;
        if (ratio >= 0.5) return 0.5;
        if (ratio >= 0.3) return 0.3;
        if (ratio >= 0.1) return 0.1;
        return 0.01; // Less than 10%
    }
    case ForceType::ARCANE: {
        double ratio = static_cast<double>(myForce) / reqForce;
        if (ratio >= 1.5) return 1.5;
        if (ratio >= 1.3) return 1.3;
        if (ratio >= 1.1) return 1.1;
        if (ratio >= 1.0) return 1.0;
        if (ratio >= 0.7) return 0.8;
        if (ratio >= 0.5) return 0.6;
        if (ratio >= 0.3) return 0.3;
        return 0.1;
    }
    case ForceType::AUTHENTIC: {
        if (myForce >= reqForce) return 1.0 + (std::min(myForce - reqForce, 50) / 10 * 0.05);

        double ratio = static_cast<double>(myForce) / reqForce;
        if (ratio >= 0.9) return 0.95;
        if (ratio >= 0.8) return 0.90;
        if (ratio >= 0.7) return 0.85;
        if (ratio >= 0.6) return 0.75;
        if (ratio >= 0.5) return 0.60;
        if (ratio >= 0.4) return 0.50;
        if (ratio >= 0.3) return 0.40;
        if (ratio >= 0.2) return 0.25;
        if (ratio >= 0.1) return 0.10;
        return 0.05;
    }
    case ForceType::NONE:
    default:
        return 1.0;
    }
}
} // namespace mcc

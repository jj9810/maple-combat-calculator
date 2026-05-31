#ifndef MCC_TYPES_H
#define MCC_TYPES_H

namespace mcc {

// Preprocessors

#define MAX_DAMAGE_CAP true

#ifndef MCC_ENABLE_XENON_SUPPORT
#define MCC_ENABLE_XENON_SUPPORT 1
#endif

#ifndef MCC_ENABLE_DEMON_AVENGER_SUPPORT
#define MCC_ENABLE_DEMON_AVENGER_SUPPORT 1
#endif

// Constants
constexpr double BASE_RATIO = 0.01;
constexpr int BASE_CRIT_CONSTANT = 35;

constexpr long long DEFAULT_MAX_DAMAGE = 700000000000;

constexpr double CRIT_RATIO_MIN = 1.2;
constexpr double CRIT_RATIO_MEAN = 1.35;
constexpr double CRIT_RATIO_MAX = 1.5;

// Enums
/**
 * 포스 종류를 정의합니다.
 */
enum class ForceType {
    NONE = 0,
    STARFORCE = 1,
    ARCANE = 2,
    AUTHENTIC = 3
};

/**
 * 주스탯 종류를 정의합니다.
 */
enum class MainStatType {
    NONE = 0,
    STR = 1,
    DEX = 2,
    INT = 3,
    LUK = 4,
    LUK_SECONDARY = 5,
    ALL_XENON = 6,
    HP_DEMON_AVENGER = 7
};

// Structs
/**
 * 매핑된 스탯 정보를 담는 구조체
 */
struct MappedStats {
    double mainStat;
    double subStat;
    double attackOrMagic;
};

} // namespace mcc

#endif // MCC_TYPES_H

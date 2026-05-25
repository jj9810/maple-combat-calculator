#pragma once

#include "context.h"
#include "internal/combat_log.pb.h"

#include <google/protobuf/struct.pb.h>

namespace mcm {

/**
 * MCM과 MCC 사이의 데이터 가교 역할을 수행하는 클래스입니다.
 * MCM의 시뮬레이션 데이터(Context, Event)를 MCC의 수식 파라미터로 변환합니다.
 */
class MCMConnector {
public:
    /**
     * DAMAGE 이벤트를 기반으로 최종 데미지를 산출합니다.
     */
    static long long calculate_damage(
        const SimulationContext& context, const maple_combat_calculator::shared::Event& event
    );

    /**
     * DOT 이벤트를 기반으로 도트 데미지를 산출합니다.
     */
    static long long calculate_dot_damage(
        const SimulationContext& context, const maple_combat_calculator::shared::Event& event
    );

    /**
     * @brief Protobuf Struct 형태의 페이로드를 InternalStat 구조체로 파싱합니다.
     */
    static InternalStat parse_stat_from_payload(const google::protobuf::Struct& payload);
};

} // namespace mcm

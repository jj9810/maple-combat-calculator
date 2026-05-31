cmake_minimum_required(VERSION 3.10)
project(mcc)

# Protobuf 라이브러리 찾기
find_package(Protobuf REQUIRED)

# Boost 라이브러리 찾기
find_package(Boost CONFIG REQUIRED)

# 프로토 파일 생성 설정
get_filename_component(PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../shared/proto" ABSOLUTE)
set(MCC_PROTO_FILE "${PROTO_DIR}/internal/mcc_stat.proto")

set(PROTO_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}")
file(MAKE_DIRECTORY "${PROTO_GEN_DIR}/internal")

set(MCC_PROTO_SRCS "${PROTO_GEN_DIR}/internal/mcc_stat.pb.cc")
set(MCC_PROTO_HDRS "${PROTO_GEN_DIR}/internal/mcc_stat.pb.h")

# CMake Configure(리로드) 시점에 파일을 강제 생성하여 CLion 빨간줄 방지 및 인덱싱 자동화
if(Protobuf_PROTOC_EXECUTABLE)
    execute_process(
        COMMAND ${Protobuf_PROTOC_EXECUTABLE} "--cpp_out=${PROTO_GEN_DIR}" "-I${PROTO_DIR}" "${MCC_PROTO_FILE}"
    )
endif()

add_custom_command(
    OUTPUT "${MCC_PROTO_SRCS}" "${MCC_PROTO_HDRS}"
    COMMAND protobuf::protoc
    ARGS "--cpp_out=${PROTO_GEN_DIR}" "-I${PROTO_DIR}" "${MCC_PROTO_FILE}"
    DEPENDS "${MCC_PROTO_FILE}"
    COMMENT "Running C++ protocol buffer compiler on ${MCC_PROTO_FILE}"
    VERBATIM
)

# MCC 라이브러리 정의
add_library(mcc STATIC
    inc/combat_power.h
    inc/combat_power_raw.h
    inc/skill_damage.h
    inc/skill_damage_raw.h
    inc/max_damage_correction.h
    inc/adjustments.h
    inc/utils.h
    inc/types.h
    src/combat_power.cpp
    src/combat_power_raw.cpp
    src/skill_damage.cpp
    src/skill_damage_raw.cpp
    src/max_damage_correction.cpp
    src/adjustments.cpp
    src/utils.cpp
    ${MCC_PROTO_SRCS}
    ${MCC_PROTO_HDRS}
)

# 인클루드 경로 설정
target_include_directories(mcc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

# Protobuf 및 Boost 라이브러리 연결
target_link_libraries(mcc PUBLIC protobuf::libprotobuf Boost::multiprecision)

# 테스트 실행 파일 정의
function(add_mcc_unit_test target source labels)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE mcc)
    add_test(NAME ${target} COMMAND ${target})
    set_tests_properties(${target} PROPERTIES LABELS "${labels}")
endfunction()

add_mcc_unit_test(mcc_combat_power_test test/combat_power_test.cpp "mcc;combat_power")
add_mcc_unit_test(mcc_skill_damage_test test/skill_damage_test.cpp "mcc;skill_damage")
add_mcc_unit_test(
    mcc_max_damage_correction_test
    test/max_damage_correction_test.cpp
    "mcc;max_damage_correction"
)
add_mcc_unit_test(mcc_ground_truth_test test/ground_truth_test.cpp "mcc;ground_truth")
add_mcc_unit_test(mcc_edge_case_test test/edge_case_test.cpp "mcc;edge_cases")
add_mcc_unit_test(mcc_invalid_input_policy_test test/invalid_input_policy_test.cpp "mcc;invalid_input_policy")

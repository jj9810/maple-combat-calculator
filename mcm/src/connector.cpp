#include "mcm/inc/connector.h"

#include "mcc/inc/skill_damage.h"

#include <string>

namespace mcm {

long long MCMConnector::calculate_damage(
    const SimulationContext& context, const maple_combat_calculator::shared::Event& event
) {
    auto total_stat = context.get_current_total_stat();
    const auto& char_info = context.get_char_info();
    const auto& mob_info = context.get_mob_info();

    double skill_damage_percent = event.damage();
    double mastery = total_stat.mastery();

    // 포스 타입 매핑
    mcc::ForceType force_type = static_cast<mcc::ForceType>(mob_info.force_type());

    return mcc::calcSkillDamage(
        skill_damage_percent,
        total_stat,
        static_cast<mcc::MainStatType>(char_info.main_stat_type()),
        mastery,
        mob_info.defense_rate(),
        mob_info.elemental_resistance(),
        char_info.weapon_constant(),
        char_info.level(),
        mob_info.level(),
        force_type,
        mob_info.required_force()
    );
}

long long MCMConnector::calculate_dot_damage(
    const SimulationContext& context, const maple_combat_calculator::shared::Event& event
) {
    auto total_stat = context.get_current_total_stat();
    const auto& char_info = context.get_char_info();
    const auto& mob_info = context.get_mob_info();

    // 포스 타입 매핑
    mcc::ForceType force_type = static_cast<mcc::ForceType>(mob_info.force_type());

    return mcc::calcDotDamage(
        event.damage(),
        total_stat,
        static_cast<mcc::MainStatType>(char_info.main_stat_type()),
        mob_info.elemental_resistance(),
        char_info.weapon_constant(),
        char_info.level(),
        mob_info.level(),
        force_type,
        mob_info.required_force()
    );
}

InternalStat MCMConnector::parse_stat_from_payload(const google::protobuf::Struct& payload) {
    InternalStat stat;
    const auto& fields = payload.fields();

    auto get_val = [&](const std::string& key) -> double {
        auto it = fields.find(key);
        if (it != fields.end() && it->second.kind_case() == google::protobuf::Value::kNumberValue) {
            return it->second.number_value();
        }
        return 0.0;
    };

    stat.str_fixed = get_val("str_fixed");
    stat.str_percent = get_val("str_percent");
    stat.dex_fixed = get_val("dex_fixed");
    stat.dex_percent = get_val("dex_percent");
    stat.int_fixed = get_val("int_fixed");
    stat.int_percent = get_val("int_percent");
    stat.luk_fixed = get_val("luk_fixed");
    stat.luk_percent = get_val("luk_percent");
    stat.hp_fixed = get_val("hp_fixed");
    stat.hp_percent = get_val("hp_percent");
    stat.mp_fixed = get_val("mp_fixed");
    stat.mp_percent = get_val("mp_percent");

    stat.att_fixed = get_val("attack_power_fixed");
    stat.att_percent = get_val("attack_power_percent");
    stat.mag_fixed = get_val("magic_power_fixed");
    stat.mag_percent = get_val("magic_power_percent");

    stat.damage = get_val("damage");
    stat.boss_damage = get_val("boss_damage");
    stat.final_damage = get_val("final_damage");
    stat.ignore_defense = get_val("ignore_defense");
    stat.crit_chance = get_val("critical_chance");
    stat.crit_damage = get_val("critical_damage");

    return stat;
}

} // namespace mcm

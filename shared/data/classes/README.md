# Class Data YAML Guide

Class data files live in this directory and use the filename format
`<normalized_class_key>.yaml`. The loader normalizes the API `character_class`
value by lowercasing ASCII letters and replacing separators with `_`.

## Top-Level Layout

```yaml
metadata:
  class: "Display Name"
  main_stat_type: "STR"
  source:
    name: "source_name"
    checked_date: "YYYY-MM-DD"

base_specs:
  weapon:
    constant: 1.3

skills:
  - name: "InternalSkillName"
    display_name: "In-game skill name"
    type: "attack"
    actions:
      - damage: 100
        hit: 1
```

## Metadata

- `class`: Display name from the upstream data source.
- `main_stat_type`: One of `STR`, `DEX`, `INT`, `LUK`, `LUK_SECONDARY`, `ALL`, or `HP`.
- `source`: Provenance for non-skill baseline specs.
- Do not put `weapon_constant` in `metadata`; use `base_specs.weapon.constant`.

## Base Specs

`base_specs` stores baseline values for documentation and future simulation use.
In Nexon API scenario, only reads `base_specs.weapon.constant`.

Recommended groups:
- `weapon`: weapon type, constant, attack speed, mastery, secondary weapon data.
- `attack`: stat, attack power, damage, boss damage, final damage, ignore defense.
- `defense`: resistance, stance, damage reduction, guard behavior.
- `critical`: critical chance and critical damage.
- `hp_mp`: HP/MP increase and recovery traits.
- `movement`: speed, jump, and movement skill capabilities.

Use numeric percentages as plain numbers, for example `45.2` means `45.2%`.
For variable values, use `base` and `max` keys.

## Skills

Each skill should define:
- `name`: Stable internal English-like identifier.
- `display_name`: Name used by incoming timeline data.
- `type`: `attack`, `buff`, `summon`, `origin`, or another loader-recognized type.
- `actions`: Damage events with `damage`, `hit`, and optional `repeat`, `interval`, `delay`.
- `effects`: Buff stat payload fields when `type` is `buff`.
- `hexa_upgrade`: Optional upgraded display name and growth metadata.

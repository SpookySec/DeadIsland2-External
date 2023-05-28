#pragma once

#include "../osmium/Cheat/Feature/feature.hpp"
#include "../hdr/offsets.hpp"

class ft_increase_damage : public feature
{
public:
    void tick() override {};
    void on_enable() override;
    void on_disable() override;
    void on_first_activation() override {};
    void on_render() override {};
    void on_shutdown() override {};

private:
    uintptr_t pDefaultValueOverride  = Offsets::GlobalDamageModifier + 0x3C;
    uintptr_t pbOverrideDefaultValue = Offsets::GlobalDamageModifier + 0x38;
    uintptr_t pMaxValueLimit         = Offsets::GlobalDamageModifier + 0x4C;
};
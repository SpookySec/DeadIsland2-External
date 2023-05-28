#pragma once

#include "../osmium/Cheat/Feature/feature.hpp"

#include "../hdr/offsets.hpp"

class ft_infinite_fury : public feature
{
public:
    void tick() override {};
    void on_enable() override;
    void on_disable() override;
    void on_first_activation() override {};
    void on_render() override {};
    void on_shutdown() override {};
private:
    uintptr_t pInfiniteFury = Offsets::FuryValues + 0x214;
};
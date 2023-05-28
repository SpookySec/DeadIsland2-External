#pragma once

#include "../osmium/Cheat/Feature/feature.hpp"

#include "../osmium/Includings/modules.hpp"
#include "../hdr/offsets.hpp"

class ft_infinite_durability : public feature
{
public:
    void tick() override {};
    void on_enable() override;
    void on_disable() override;
    void on_first_activation() override;
    void on_render() override {};
    void on_shutdown() override {};
private:
    uintptr_t m_loc{ 0 };
    uint32_t m_bytes{ 0 };
};
#pragma once

#include "../osmium/Cheat/Feature/feature.hpp"
#include "../hdr/globals.hpp"

class ft_infinite_ammo : public feature
{
public:
    ft_infinite_ammo() : feature(), m_bytes(uint64_t()) {};
    void tick() override {};
    void on_enable() override;
    void on_disable() override;
    void on_first_activation() override;
    void on_render() override {};
    void on_shutdown() override {};

private:
    uint64_t m_bytes{ 0 };
    uintptr_t m_loc{ 0 };
};
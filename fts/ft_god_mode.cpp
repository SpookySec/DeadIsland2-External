#include "ft_god_mode.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"

void ft_god_mode::on_enable()
{
    // Write 9999 to health
    Modules::g_pProcess->write<float>(pHealth, 9999.f);

    // Set the global damage modifier (damage dealt to player) = 0.f
    Modules::g_pProcess->write<float>(Offsets::GlobalDamageMuliplier, 0.f);
}

void ft_god_mode::on_disable()
{
    Modules::g_pProcess->write<float>(pHealth, 1800.f);

    Modules::g_pProcess->write<float>(Offsets::GlobalDamageMuliplier, 1.f);
}
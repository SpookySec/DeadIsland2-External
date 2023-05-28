#include "ft_increase_damage.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"

void ft_increase_damage::on_enable()
{
    Modules::g_pProcess->write<float>(pDefaultValueOverride, 232.f);
    Modules::g_pProcess->write<float>(pMaxValueLimit, 232.f);
    Modules::g_pProcess->write<int>(pbOverrideDefaultValue, 232);
}

void ft_increase_damage::on_disable()
{
    Modules::g_pProcess->write<float>(pDefaultValueOverride, 1.f);
    Modules::g_pProcess->write<float>(pMaxValueLimit, 2.f);
    Modules::g_pProcess->write<int>(pbOverrideDefaultValue, 1.f);
}
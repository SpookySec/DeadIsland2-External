#include "ft_infinite_stamina.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"

void ft_infinite_stamina::on_enable()
{
    Modules::g_pProcess->write<int>(pbInfiniteStaminaExpressionValue, 1);
    Modules::g_pProcess->write<float>(pStamina, 1000.f);
}

void ft_infinite_stamina::on_disable()
{
    Modules::g_pProcess->write<int>(pbInfiniteStaminaExpressionValue, 0);
}
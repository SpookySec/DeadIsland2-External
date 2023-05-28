#include "ft_infinite_fury.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"

void ft_infinite_fury::on_enable()
{
    Modules::g_pProcess->write<int>(pInfiniteFury, 1);
}

void ft_infinite_fury::on_disable()
{
    Modules::g_pProcess->write<int>(pInfiniteFury, 0);
}
#include "ft_infinite_ammo.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"
#include "../hdr/globals.hpp"

void ft_infinite_ammo::on_enable()
{
    Modules::g_pProcess->nop_bytes(this->m_loc, 8);
}

void ft_infinite_ammo::on_disable()
{
    Modules::g_pProcess->write<uint64_t>(this->m_loc, this->m_bytes);
}

void ft_infinite_ammo::on_first_activation()
{
    this->m_loc = Modules::g_pProcess->get_image_base(L"DeadIsland-Win64-Shipping.exe") + 0x16559B6;
    this->m_bytes = Modules::g_pProcess->read<uint64_t>(this->m_loc, 8);
}
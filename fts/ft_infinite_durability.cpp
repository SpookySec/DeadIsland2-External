#include "ft_infinite_durability.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"

void ft_infinite_durability::on_enable()
{
    Modules::g_pProcess->nop_bytes(this->m_loc, 4);
}

void ft_infinite_durability::on_disable()
{
    Modules::g_pProcess->write<uint32_t>(this->m_loc, this->m_bytes);
}

void ft_infinite_durability::on_first_activation()
{
    this->m_loc = Modules::g_pProcess->get_image_base(L"DeadIsland-Win64-Shipping.exe") + 0x1751854;
    this->m_bytes = Modules::g_pProcess->read<uint32_t>(this->m_loc);
}
#include "ft_super_jump_speed.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"

void ft_super_jump_speed::on_enable()
{
    Modules::g_pProcess->write<float>(pMovementSpeed, 2500.f);
    Modules::g_pProcess->write<float>(pJumpVelocityZ, 3000.f);

    Modules::g_pProcess->write<float>(pFallCriticalImpactHeight, 99999.f);
    Modules::g_pProcess->write<float>(pFallDamageImpactHeight, 99999.f);
}

void ft_super_jump_speed::on_disable()
{
    // Leave it up to the user to disable God Mode
    Modules::g_pProcess->write<float>(pMovementSpeed, 0);
    Modules::g_pProcess->write<float>(pJumpVelocityZ, 0);

    Modules::g_pProcess->write<float>(pFallCriticalImpactHeight, 700.f);
    Modules::g_pProcess->write<float>(pFallDamageImpactHeight, 450.f);
}
#include "ft_no_clip.hpp"

#include "../osmium/Includings/modules.hpp"

#include "../hdr/offsets.hpp"

void ft_no_clip::on_enable()
{
    Modules::g_pProcess->write<int>(pActorEnableCollision, 67);
    Modules::g_pProcess->write<int>(pMovementMode, 5);
}

void ft_no_clip::on_disable()
{
    Modules::g_pProcess->write<int>(pActorEnableCollision, 68);
    Modules::g_pProcess->write<int>(pMovementMode, 2);
}

void ft_no_clip::tick()
{
    Modules::g_pProcess->write<float>(pfVelocityZ, 0.f);

    if (GetAsyncKeyState(VK_SPACE))
        Modules::g_pProcess->write<float>(pfVelocityZ, 500.f);

    if (GetAsyncKeyState(VK_LCONTROL))
        Modules::g_pProcess->write<float>(pfVelocityZ, -500.f);
}
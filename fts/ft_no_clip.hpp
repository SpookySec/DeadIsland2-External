#pragma once

#include "../osmium/Cheat/Feature/feature.hpp"
#include "../hdr/offsets.hpp"

class ft_no_clip : public feature
{
public:
    void tick() override;
    void on_enable() override;
    void on_disable() override;
    void on_first_activation() override {};
    void on_render() override {};
    void on_shutdown() override {};

private:
    uintptr_t pActorEnableCollision = Offsets::ActorCharacter + 0x77;
    uintptr_t pMovementMode = Offsets::CharacterMovement + 0x1A4;
    uintptr_t pfVelocityZ = Offsets::CharacterMovement + 0x104;
};
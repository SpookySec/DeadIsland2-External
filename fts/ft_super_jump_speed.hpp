#pragma once

#include "../osmium/Cheat/Feature/feature.hpp"

#include "../hdr/offsets.hpp"

class ft_super_jump_speed : public feature
{
public:
    void tick() override {};
    void on_enable() override;
    void on_disable() override;
    void on_first_activation() override {};
    void on_render() override {};
    void on_shutdown() override {};
private:
    uintptr_t pMovementSpeed = Offsets::CharacterMovement + 0x1E4;
    uintptr_t pJumpVelocityZ = Offsets::CharacterMovement + 0x194;
    uintptr_t pFallCriticalImpactHeight = Offsets::ActorCharacter + 0xDB8;
    uintptr_t pFallDamageImpactHeight = Offsets::ActorCharacter + 0xDBC;
};
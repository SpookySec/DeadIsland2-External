#include "../hdr/dead_cheat.hpp"
#include "../hdr/utils.hpp"
#include "../osmium/Includings/modules.hpp"
#include "../hdr/offsets.hpp"
#include "../hdr/globals.hpp"
#include "../gui/gui_fonts.h"

#include "../fts/ft_god_mode.hpp"
#include "../fts/ft_infinite_ammo.hpp"
#include "../fts/ft_no_clip.hpp"
#include "../fts/ft_infinite_fury.hpp"
#include "../fts/ft_infinite_durability.hpp"
#include "../fts/ft_increase_damage.hpp"
#include "../fts/ft_infinite_stamina.hpp"
#include "../fts/ft_super_jump_speed.hpp"

#include <Windows.h>

bool dead_island::setup_features()
{
    auto god_mode = std::make_unique<ft_god_mode>();
    god_mode->set_name(L"God Mode");
    god_mode->enable_print_status();
    god_mode->set_activation_delay(200);
    god_mode->disable_drawing();
    god_mode->set_virtual_key_code(VK_NUMPAD1);
    this->m_features.push_back(std::move(god_mode));

    auto infinite_ammo = std::make_unique<ft_infinite_ammo>();
    infinite_ammo->set_name(L"Infinite Bullets");
    infinite_ammo->enable_print_status();
    infinite_ammo->set_activation_delay(200);
    infinite_ammo->disable_drawing();
    infinite_ammo->set_virtual_key_code(VK_NUMPAD2);
    this->m_features.push_back(std::move(infinite_ammo));

    auto no_clip = std::make_unique<ft_no_clip>();
    no_clip->set_name(L"No Clip");
    no_clip->enable_print_status();
    no_clip->set_activation_delay(200);
    no_clip->disable_drawing();
    no_clip->set_virtual_key_code(VK_NUMPAD3);
    this->m_features.push_back(std::move(no_clip));

    auto infinite_fury = std::make_unique<ft_infinite_fury>();
    infinite_fury->set_name(L"Infinite Fury");
    infinite_fury->enable_print_status();
    infinite_fury->set_activation_delay(200);
    infinite_fury->disable_drawing();
    infinite_fury->set_virtual_key_code(VK_NUMPAD4);
    this->m_features.push_back(std::move(infinite_fury));

    auto infinite_durability = std::make_unique<ft_infinite_durability>();
    infinite_durability->set_name(L"Infinite Durability");
    infinite_durability->enable_print_status();
    infinite_durability->set_activation_delay(200);
    infinite_durability->disable_drawing();
    infinite_durability->set_virtual_key_code(VK_NUMPAD5);
    this->m_features.push_back(std::move(infinite_durability));

    auto increase_damage = std::make_unique<ft_increase_damage>();
    increase_damage->set_name(L"Increase Damage");
    increase_damage->enable_print_status();
    increase_damage->set_activation_delay(200);
    increase_damage->disable_drawing();
    increase_damage->set_virtual_key_code(VK_NUMPAD6);
    this->m_features.push_back(std::move(increase_damage));

    auto infinite_stamina = std::make_unique<ft_infinite_stamina>();
    infinite_stamina->set_name(L"Infinite Stamina");
    infinite_stamina->enable_print_status();
    infinite_stamina->set_activation_delay(200);
    infinite_stamina->disable_drawing();
    infinite_stamina->set_virtual_key_code(VK_NUMPAD7);
    this->m_features.push_back(std::move(infinite_stamina));

    auto super_jump_speed = std::make_unique<ft_super_jump_speed>();
    super_jump_speed->set_name(L"Super Jump & Speed");
    super_jump_speed->enable_print_status();
    super_jump_speed->set_activation_delay(200);
    super_jump_speed->disable_drawing();
    super_jump_speed->set_virtual_key_code(VK_NUMPAD8);
    this->m_features.push_back(std::move(super_jump_speed));

    return true;
}

bool dead_island::setup_offsets()
{
    //const auto image = Modules::g_pProcess->get_image_ptr_by_name(L"DeadIsland-Win64-Shipping.exe");

    const auto pGEngine = 0x147932728;
    Offsets::GEngine = Modules::g_pProcess->read<uintptr_t>(pGEngine);
    if (!Offsets::GEngine)
        return false;

    const auto pGameViewPort = Offsets::GEngine + 0x7D8;
    Offsets::GameViewPort = Modules::g_pProcess->read<uintptr_t>(pGameViewPort);
    if (!Offsets::GameViewPort)
        return false;

    const auto pGameViewPortClientWorld = Offsets::GameViewPort + 0x78;
    Offsets::GameViewPortClientWorld = Modules::g_pProcess->read<uintptr_t>(pGameViewPortClientWorld);
    if (!Offsets::GameViewPortClientWorld)
        return false;

    const auto pUWorld = Offsets::GameViewPort + Offsets::GameViewPortClientWorld;
    Offsets::UWorld = Modules::g_pProcess->read<uintptr_t>(pUWorld);

    const auto pGameInstance = Offsets::GEngine + 0xEA8;
    Offsets::GameInstance = Modules::g_pProcess->read<uintptr_t>(pGameInstance);
    if (!Offsets::GameInstance)
        return false;

    const auto pLocalPlayers = Offsets::GameInstance + 0x38;
    Offsets::LocalPlayers = Modules::g_pProcess->read<uintptr_t>(pLocalPlayers);
    if (!Offsets::LocalPlayers)
        return false;

    const auto pUnknownName = Offsets::LocalPlayers + 0x00; // In case of an update this offset can be updated as well. (unlikely)
    Offsets::UnknownName = Modules::g_pProcess->read<uintptr_t>(pUnknownName);
    if (!Offsets::UnknownName)
        return false;

    const auto pPlayerController = Offsets::UnknownName + 0x30;
    Offsets::PlayerController = Modules::g_pProcess->read<uintptr_t>(pPlayerController);
    if (!Offsets::PlayerController)
        return false;

    const auto pActorCharacter = Offsets::PlayerController + 0x2F0;
    Offsets::ActorCharacter = Modules::g_pProcess->read<uintptr_t>(pActorCharacter);
    if (!Offsets::ActorCharacter)
        return false;

    const auto pCharacterMovement = Offsets::ActorCharacter + 0x328;
    Offsets::CharacterMovement = Modules::g_pProcess->read<uintptr_t>(pCharacterMovement);
    if (!Offsets::CharacterMovement)
        return false;

    Offsets::CustomTimeDilation = Offsets::ActorCharacter + 0xC8;
    if (!Offsets::CustomTimeDilation)
        return false;

    const auto pCCapsule = Offsets::ActorCharacter + 0x330;
    Offsets::CCapsule = Modules::g_pProcess->read<uintptr_t>(pCCapsule);
    if (!Offsets::CCapsule)
        return false;

    const auto pCHealth = Offsets::ActorCharacter + 0x948;
    Offsets::CHealth = Modules::g_pProcess->read<uintptr_t>(pCHealth);
    if (!Offsets::CHealth)
        return false;

    const auto pCStamina = Offsets::ActorCharacter + 0x950;
    Offsets::CStamina = Modules::g_pProcess->read<uintptr_t>(pCStamina);
    if (!Offsets::CStamina)
        return false;

    const auto pCDamage = Offsets::ActorCharacter + 0x958;
    Offsets::CDamage = Modules::g_pProcess->read<uintptr_t>(pCDamage);
    if (!Offsets::CDamage)
        return false;

    const auto pCAIMeleeTarget = Offsets::ActorCharacter + 0x970;
    Offsets::CAIMeleeTarget = Modules::g_pProcess->read<uintptr_t>(pCAIMeleeTarget);
    if (!Offsets::CAIMeleeTarget)
        return false;

    const auto pFuryValues = Offsets::PlayerController + 0x788;
    Offsets::FuryValues = Modules::g_pProcess->read<uintptr_t>(pFuryValues);
    if (!Offsets::FuryValues)
        return false;

    const auto pGlobalDamageModifier = Offsets::CDamage + 0xF8;
    Offsets::GlobalDamageModifier = Modules::g_pProcess->read<uintptr_t>(pGlobalDamageModifier);
    if (!Offsets::GlobalDamageModifier)
        return false;

    Offsets::GlobalDamageMuliplier = Offsets::CDamage + 0xF0;
    if (!Offsets::GlobalDamageMuliplier)
        return false;

    return true;
}


// ===========================================

void dead_island::run()
{
    for (const auto& feature : this->m_features)
    {
        if (utils::is_key_pressed(feature->get_virtual_key_code()))
            feature->toggle();

        if (feature->is_active())
            feature->tick();
    }
}

void dead_island::shutdown()
{
    for (const auto& feature : this->m_features)
        if (feature->is_active())
            feature->disable();

    if (Modules::g_pProcess)
        Modules::g_pProcess->clear_image_map();
}

void dead_island::print_offsets()
{
    printf("\n");

    const auto log = [](const std::string& name, const std::uintptr_t value)
    {
        printf("[*] %-25s -> 0x%llX\n", name.c_str(), value);
    };

    log("Local Player", Offsets::ActorCharacter);
    log("GEngine", Offsets::GEngine);
    log("GameViewPort", Offsets::GameViewPort);
    log("GameViewPortClient", Offsets::GameViewPortClientWorld);
    log("UWorld", Offsets::UWorld);
    log("GameInstance", Offsets::GameInstance);
    log("LocalPlayers", Offsets::LocalPlayers);
    log("UnknownName", Offsets::UnknownName);
    log("PlayerController", Offsets::PlayerController);
    log("ActorCharacter", Offsets::ActorCharacter);
    log("CharacterMovement", Offsets::CharacterMovement);
    log("CCapsule", Offsets::CCapsule);
    log("CHealth", Offsets::CHealth);
    log("FuryValues", Offsets::FuryValues);
}

void dead_island::print_features()
{
    printf("\n");
    printf("%-25s | Hotkey\n", "Feature");

    for (const auto& feature : this->m_features)
        printf("%-25ws | %s\n", feature->get_name().c_str(), utils::virtual_key_as_string(feature->get_virtual_key_code()).c_str());

    printf("\n");
}
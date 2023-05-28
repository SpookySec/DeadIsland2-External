#pragma once

#include <cstdint>

#include <Windows.h>
#include <system_error>
#include <psapi.h>

#include "../osmium/Includings/modules.hpp"

#define InRange(x, a, b)    (x >= a && x <= b) 
#define GetBits(x)          (InRange(x, '0', '9') ? (x - '0') : ((x & (~0x20)) - 'A' + 0xa))
#define GetByte(x)          (GetBits(x[0]) << 4 | GetBits(x[1]))

namespace utils
{

    inline bool is_key_pressed(const int32_t virtual_key_code)
    {
        return GetAsyncKeyState(virtual_key_code) & 0x8000;
    }

    // cc: https://stackoverflow.com/a/38107083
    inline std::string virtual_key_as_string(const int16_t vk_code)
    {
        UINT scanCode = MapVirtualKey(vk_code, MAPVK_VK_TO_VSC);

        CHAR szName[128];
        int result = 0;
        switch (vk_code)
        {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT:
        case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE:
        case VK_DIVIDE:
        case VK_NUMLOCK:
            scanCode |= KF_EXTENDED;
        default:
            result = GetKeyNameTextA(scanCode << 16, szName, 128);
        }
        if (result == 0)
            throw std::system_error(std::error_code(GetLastError(), std::system_category()),
                "WinAPI Error occured.");
        return szName;
    }

    template< typename T >
    inline T follow_pointer_path(uintptr_t ptr, std::vector<unsigned int> offsets)
    {
        if (!Modules::g_pProcess)
            return NULL;

        uintptr_t addr = ptr;
        T buffer;

        for (auto offset : offsets)
        {
            ReadProcessMemory(Modules::g_pProcess->get_process_handle(), (PBYTE)addr, &addr, sizeof(addr), 0);
            addr += offsets[offset];
        }

        ReadProcessMemory(Modules::g_pProcess->get_process_handle(), (PBYTE)addr, &buffer, sizeof(buffer), 0);

        return buffer;
    }


    /*inline std::uintptr_t find_signature(DWORD base, const char* sig, const char* mask)
    {
        auto buffer = std::make_unique<std::array<std::uint8_t, 0x100000>>();
        auto data = buffer.get();

        for (std::uintptr_t i = 0u; i < (2u << 25u); ++i)
        {
            ReadProcessMemory(Modules::g_pProcess->get_process_handle(), (LPCVOID)(base + i * 0x100000), data, 0x100000, 0);

            if (!data)
                return 0;

            for (std::uintptr_t j = 0; j < 0x100000u; ++j)
            {
                if ([](std::uint8_t const* data, std::uint8_t const* sig, char const* mask)
                    {
                        for (; *mask; ++mask, ++data, ++sig)
                        {
                            if (*mask == 'x' && *data != *sig) return false;
                        }
                        return (*mask) == 0;
                    }(data + j, (std::uint8_t*)sig, mask))
                {
                    std::uintptr_t result = base + i * 0x100000 + j;
                    std::uint32_t rel = 0;

                    ReadProcessMemory(Modules::g_pProcess->get_process_handle(), (LPCVOID)(result + 3), &rel, sizeof(std::uint32_t), 0);

                    if (!rel)
                        return 0;

                    return result + rel + 7;
                }
            }
        }
    }*/

    inline std::vector<std::wstring> scan_process()
    {
        if (!Modules::g_pProcess->get_process_handle())
            return std::vector<std::wstring>();

        DWORD cbNeeded;
        unsigned int i;
        HMODULE hMods[1024];
        std::vector<std::wstring> sMods;

        if (EnumProcessModules(Modules::g_pProcess->get_process_handle(), hMods, sizeof(hMods), &cbNeeded))
        {
            for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
            {
                TCHAR szModName[MAX_PATH];
                if (GetModuleFileNameEx(Modules::g_pProcess->get_process_handle(), hMods[i], szModName,
                    sizeof(szModName) / sizeof(TCHAR)))
                {
                    // Print the module name and handle value.
                    std::wstring mod(&szModName[0]);
                    sMods.push_back(std::wstring(mod.begin(), mod.end()));
                }
            }
        }

        return sMods;
    }
}
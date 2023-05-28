#include <stdio.h>
#include <iostream>

#include "../osmium/Includings/modules.hpp"
#include "../hdr/dead_cheat.hpp"
#include "../hdr/utils.hpp"

#include "../gui/gui_source.h"
#include "../gui/gui_fonts.h"
#include "../gui/gui_menu.h"

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
    bool bExit = false;
    //FILE* fp;

    //AllocConsole();
    //freopen_s(&fp, "CONOUT$", "w", stdout);
    //SetConsoleTitle(L"SpookySec#6710 | Dead Island 2");

    std::wstring title = L"Dead Island 2 Cheat | SpookySec#6710";

    WNDCLASSEX window_class = {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)->LRESULT {
            if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
                return true;

            switch (msg)
            {
            case WM_SIZE:
                if (device_handle != 0 && wParam != SIZE_MINIMIZED)
                {
                    device_parameters.BackBufferWidth = LOWORD(lParam);
                    device_parameters.BackBufferHeight = HIWORD(lParam);
                    ResetDevice();
                }
                return 0;
            case WM_SYSCOMMAND:
                if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                    return 0;
                break;
            case WM_DESTROY:
                ExitProcess(0);
                return 0;
            }
            return DefWindowProc(hWnd, msg, wParam, lParam);
        },
        0L,
        0L,
        GetModuleHandle(0),
        0,
        0,
        0,
        0,
        title.c_str(),
        0
    };

    RegisterClassEx(&window_class);
    window_handle = CreateWindowEx(0, window_class.lpszClassName, title.c_str(), WS_POPUP, 0, 0, 5, 5, 0, 0, window_class.hInstance, 0);
    if (!CreateDeviceD3D(window_handle))
    {
        CleanupDeviceD3D();
        UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return 1;
    }

    ShowWindow(window_handle, SW_HIDE);
    SetWindowPos(window_handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    UpdateWindow(window_handle);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    ImFontConfig icons_config;

    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;

    ImFontConfig rubik;
    rubik.FontDataOwnedByAtlas = false;

    //ImFontConfig proggy;
    //proggy.SizePixels = 11.5f;

    //io.Fonts->AddFontFromMemoryTTF(const_cast<unsigned char*>(rawData), sizeof(rawData), 25.f, &rubik);
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 15.f, &icons_config, icons_ranges);

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    if (!Menu::Initialize())
    {
        CleanupDeviceD3D();
        UnregisterClass(window_class.lpszClassName, window_class.hInstance);
        return 1;
    }

    ImGui_ImplWin32_Init(window_handle);
    ImGui_ImplDX9_Init(device_handle);
    ImGui_ImplWin32_EnableAlphaCompositing(window_handle);

    printf("[*] Waiting for game...");

    int dots = 0;

    while (!Modules::g_pProcess->setup_process(L"DeadIsland-Win64-Shipping.exe"))
    {
        MSG message;
        if (PeekMessage(&message, 0, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
            continue;
        }

        if (message.message == WM_QUIT)
            break;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowBgAlpha(0.5f);
        ImGui::SetNextWindowSize(ImVec2(250, 100), ImGuiCond_Once);
        ImGui::Begin("Waiting for game", &bExit, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
        ImGui::SetCursorPos((ImVec2(ImGui::GetWindowSize().x / 2 - (strlen("Waiting for game...")*3.f), ImGui::GetWindowSize().y / 2.3f)));
        ImGui::Text("Waiting for game");
        ImGui::SameLine(0, -0.3f);
        for (int i = 0; i < dots; i++)
        {
            ImGui::Text(".");
            ImGui::SameLine(0, -0.3f);
        }

        ImGui::End();

        ImGui::EndFrame();

        device_handle->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (device_handle->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            device_handle->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = device_handle->Present(0, 0, 0, 0);
        if (result == D3DERR_DEVICELOST && device_handle->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }

        Sleep(400);
        dots++;

        if (dots == 4)
            dots = 0;

        if (utils::is_key_pressed(VK_END))
            break;
    }

    dots = 0;

    printf("done!\n");

    printf("[+] PID   : %018d\n", (int)Modules::g_pProcess->get_process_id());
    printf("[+] BASE  : 0x%p\n", (void*)Modules::g_pProcess->get_first_image_ptr());
    printf("[+] HANDLE: 0x%p\n", (void*)Modules::g_pProcess->get_process_handle());

    printf("[*] Setting up offsets...");
    while (!Modules::g_pCheat->setup_offsets())
    {
        MSG message;
        if (PeekMessage(&message, 0, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
            continue;
        }

        if (message.message == WM_QUIT)
            break;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(250, 100), ImGuiCond_Once);
        ImGui::Begin("Waiting for offsets", &bExit, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
        ImGui::SetCursorPos((ImVec2(ImGui::GetWindowSize().x / 2 - (strlen("Searching for offsets...") * 3.f), ImGui::GetWindowSize().y / 2.3f)));
        ImGui::Text("Setting up cheat");
        ImGui::SameLine(0, -0.3f);
        for (int i = 0; i < dots; i++)
        {
            ImGui::Text(".");
            ImGui::SameLine(0, -0.3f);
        }

        ImGui::End();

        ImGui::EndFrame();

        device_handle->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (device_handle->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            device_handle->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = device_handle->Present(0, 0, 0, 0);
        if (result == D3DERR_DEVICELOST && device_handle->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }


        Sleep(400);
        dots++;

        if (dots == 4)
            dots = 0;

        if (utils::is_key_pressed(VK_END))
            break;

    }

    printf("done!\n");

    Modules::g_pCheat->print_offsets();

    //printf("[*] Preparing the overlay..");

    //while (!Modules::g_pOverlay->initialize(Modules::g_pProcess->get_window_handle()))
    //    Sleep(300);

    //printf("done!\n");

    printf("[*] Setting up features...");
    while (!Modules::g_pCheat->setup_features())
        Sleep(300);

    printf("done!\n");

    Modules::g_pCheat->print_features();

    while (true)
    {
        //SetWindowLong(window_handle, 0, WS_EX_TOPMOST);
        MSG message;
        if (PeekMessage(&message, 0, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
            continue;
        }

        if (message.message == WM_QUIT)
            break;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        Menu::Render(); // Actual menu.

        ImGui::EndFrame();

        device_handle->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (device_handle->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            device_handle->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = device_handle->Present(0, 0, 0, 0);
        if (result == D3DERR_DEVICELOST && device_handle->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }

        if (utils::is_key_pressed(VK_END))
            break;

        Modules::g_pCheat->run();

        Sleep(3);
    }

    Modules::g_pCheat->shutdown();

    Sleep(50);
    return 0;
}
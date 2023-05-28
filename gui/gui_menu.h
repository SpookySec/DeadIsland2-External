#pragma once

#include "gui_includes.h"
#include "../osmium/Includings/modules.hpp"

namespace Menu {

	inline bool Initialize()
	{


		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();

		const auto size = sizeof(style.Colors) / sizeof(style.Colors[0]);
		ImVec4(&colors)[size] = style.Colors;

		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.FrameRounding = 1.5f;

		colors[ImGuiCol_TitleBg] = ImColor(40, 40, 40);
		colors[ImGuiCol_TitleBgActive] = ImColor(40, 40, 40);
		colors[ImGuiCol_TitleBgCollapsed] = ImColor(40, 40, 40);

		colors[ImGuiCol_FrameBg] = ImColor(24, 24, 24);
		colors[ImGuiCol_FrameBgActive] = ImColor(26, 26, 26);
		colors[ImGuiCol_FrameBgHovered] = ImColor(26, 26, 26);

		colors[ImGuiCol_Header] = ImColor(50, 50, 50);
		colors[ImGuiCol_HeaderActive] = ImColor(50, 50, 50);
		colors[ImGuiCol_HeaderHovered] = ImColor(50, 50, 50);

		colors[ImGuiCol_Button] = ImColor(26, 26, 26);
		colors[ImGuiCol_ButtonHovered] = ImColor(32, 32, 32);
		colors[ImGuiCol_ButtonActive] = ImColor(36, 36, 36);

		return true;
	}

	inline void Render()
	{
		const int flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;// | ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImGui::SetNextWindowSize(ImVec2(230, 300));

		ImGui::Begin("Dead Island 2 | SpookySec#6710", 0, flags);

		for (const auto& feature : *Modules::g_pCheat->get_features_as_ptr())
		{

			ImGui::Text("%ws", feature->get_name().c_str());
			ImGui::SameLine();
			char label[16];
			snprintf(label, sizeof(label), feature->is_active() ? "ON##%d" : "OFF##%d", feature->get_virtual_key_code());
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 60);
			ImGui::PushStyleColor(ImGuiCol_Text, feature->is_active() ? ImColor(10, 255, 10).Value : ImColor(255, 10, 10).Value);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, feature->is_active() ? ImColor(255, 10, 10).Value : ImColor(10, 255, 10).Value);
			if (ImGui::Button(label, ImVec2(50, 20)))
				feature->toggle();

			ImGui::PopStyleColor(2);
		}

		//ImGui::SetCursorPos(ImVec2(0, ImGui::GetWindowSize().y - 30));
		ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 30);
		if (ImGui::Button("Toggle All", ImVec2(ImGui::GetContentRegionAvail().x, 20)))
			for (const auto& feature : *Modules::g_pCheat->get_features_as_ptr())
				feature->toggle();

		ImGui::End();
	}
}
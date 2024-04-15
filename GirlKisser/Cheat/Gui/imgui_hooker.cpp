#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <d3d11.h>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <thread>
#include <map>
#include <MinHook.h>

#include "imgui_hooker.h"
#include "../Logger/Logger.h"
#include "../Hooks/Hooks.h"

#pragma comment( lib, "d3d11.lib" )

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
WPARAM MapLeftRightKeys(const MSG& msg);

std::stringstream full_title;
std::string combo_file = "default";
static char config_file[32] = "default";
static char offsets_rhd[32] = "";
static char return_rhd[32] = "";
static LPVOID last_rhd = nullptr;
static ImU32 color_title = ImGui::ColorConvertFloat4ToU32({0.875f, 0.12f, 0.9f, 1.00f});
static ImU32 color_bg = ImGui::ColorConvertFloat4ToU32({0.00f, 0.00f, 0.00f, 0.75f});
static bool boundless_value_setting = false;
static bool font_changed = false;

void InitModules(const std::vector<GKModule>& init_mods);
void HandleModuleSettingRendering(GKModule& module);
void HandleModuleRendering(GKModule& module);
void HandleCategoryRendering(const std::string& name, GKCategory cat);

struct Theme
{
    ImVec4 solid_bg;
    ImVec4 dark_main;
    ImVec4 main;
    ImVec4 highlight;
};

std::string current_font = "C:/Windows/Fonts/calibril.ttf";
std::string current_theme = "GirlKisser";

std::vector<std::string> get_native_font_list(bool ttf_only)
{
    std::vector<std::string> paths;
    const std::string path = "C:/Windows/Fonts";
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        const std::filesystem::path& p = entry.path();
        if (ttf_only && !p.extension().string().contains("ttf")) continue;
        if (p.extension().string().contains("wing")) continue;
        // std::string str_path = p.generic_string();
        // str_path = str_path.replace(str_path.begin(), str_path.end(), "/", "\\");
        paths.push_back(p.generic_string());
    }
    return paths;
}

auto fonts = get_native_font_list(true);
std::vector<std::string> themes = {"GirlKisser", "Binary"};

// https://github.com/ocornut/imgui/issues/707
void init_style()
{
    Logger::log_info("Initialized GUI style");
    auto style = &ImGui::GetStyle();
    auto colors = style->Colors;
    Theme theme;
    if (current_theme == "GirlKisser")
    {
        theme = {
            ImVec4(0.00f, 0.00f, 0.00f, 0.00f),
            ImVec4(125.0f / 255.0f, 37.0f / 255.0f, 112.0f / 255.0f, 1.00f),
            ImVec4(223.0f / 255.0f, 31.0f / 255.0f, 230.0f / 255.0f, 1.00f),
            ImVec4(209.0f / 255.0f, 89.0f / 255.0f, 191.0f / 255.0f, 1.00f)
        };
    }
    else if (current_theme == "Binary")
    {
        theme = {
            ImVec4(0.00f, 0.00f, 0.00f, 0.00f),
            ImVec4(41.0f / 255.0f, 125.0f / 255.0f, 37.0f / 255.0f, 1.00f),
            ImVec4(41.0f / 255.0f, 230.0f / 255.0f, 31.0f / 255.0f, 1.00f),
            ImVec4(93.0f / 255.0f, 209.0f / 255.0f, 89.0f / 255.0f, 1.00f)
        };
    }

    colors[ImGuiCol_Text]                   = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.75f);
    colors[ImGuiCol_ChildBg]                = theme.solid_bg;
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = theme.dark_main;
    colors[ImGuiCol_BorderShadow]           = theme.solid_bg;
    colors[ImGuiCol_FrameBg]                = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TitleBg]                = theme.dark_main;
    colors[ImGuiCol_TitleBgActive]          = theme.main;
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark]              = theme.highlight;
    colors[ImGuiCol_SliderGrab]             = theme.main;
    colors[ImGuiCol_SliderGrabActive]       = theme.main;
    colors[ImGuiCol_Button]                 = theme.dark_main;
    colors[ImGuiCol_ButtonHovered]          = theme.main;
    colors[ImGuiCol_ButtonActive]           = theme.highlight;
    colors[ImGuiCol_Header]                 = theme.dark_main;
    colors[ImGuiCol_HeaderHovered]          = theme.main;
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = theme.main;
    colors[ImGuiCol_SeparatorActive]        = theme.highlight;
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered]      = theme.main;
    colors[ImGuiCol_ResizeGripActive]       = theme.highlight;
    colors[ImGuiCol_Tab]                    = theme.dark_main;
    colors[ImGuiCol_TabHovered]             = theme.main;
    colors[ImGuiCol_TabActive]              = theme.highlight;
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    style->FramePadding = ImVec2(4, 2);
    style->ItemSpacing = ImVec2(10, 2);
    style->IndentSpacing = 12;
    style->ScrollbarSize = 10;

    style->WindowRounding = 4;
    style->FrameRounding = 4;
    style->PopupRounding = 4;
    style->ScrollbarRounding = 6;
    style->GrabRounding = 4;
    style->TabRounding = 4;

    style->WindowTitleAlign = ImVec2(1.0f, 0.5f);
    style->WindowMenuButtonPosition = ImGuiDir_Right;

    style->DisplaySafeAreaPadding = ImVec2(4, 4);
    
    style->WindowPadding                     = ImVec2(8.00f, 8.00f);
    style->FramePadding                      = ImVec2(5.00f, 2.00f);
    style->CellPadding                       = ImVec2(6.00f, 6.00f);
    style->ItemSpacing                       = ImVec2(6.00f, 6.00f);
    style->ItemInnerSpacing                  = ImVec2(6.00f, 6.00f);
    style->TouchExtraPadding                 = ImVec2(0.00f, 0.00f);
    style->IndentSpacing                     = 25;
    style->ScrollbarSize                     = 15;
    style->GrabMinSize                       = 10;
    style->WindowBorderSize                  = 1;
    style->ChildBorderSize                   = 1;
    style->PopupBorderSize                   = 1;
    style->FrameBorderSize                   = 1;
    style->TabBorderSize                     = 1;
    style->WindowRounding                    = 7;
    style->ChildRounding                     = 4;
    style->FrameRounding                     = 3;
    style->PopupRounding                     = 4;
    style->ScrollbarRounding                 = 9;
    style->GrabRounding                      = 3;
    style->LogSliderDeadzone                 = 4;
    style->TabRounding                       = 4;
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)
    horizontal = desktop.right;
    vertical = desktop.bottom;
}

inline int(__stdcall* rhd_original)(void* arg);
inline int __stdcall rhd(void* arg)
{
    Logger::log_debug("Dev Hook Called!");
    return std::stoi(return_rhd);
}

void try_runtime_hook()
{
    if (!last_rhd == 0)
    {
        Logger::log_debug("Clearing Last Hook");
        MH_DisableHook(last_rhd);
        MH_RemoveHook(last_rhd);
    }
    uint64_t offset;
    std::stringstream stringstream;
    stringstream << std::hex << offsets_rhd;
    stringstream >> offset;
    std::stringstream s2;
    if (offset == 0)
    {
        Logger::log_debug("Not Creating Null Hook!");
        return;
    }
    s2 << "Creating Hook | Offset: " << offset << " | Return: " << return_rhd;
    Logger::log_debug(s2.str());
    last_rhd = (LPVOID*)offset;
    if (MH_CreateHook((LPVOID*)(Hooks::GameAssembly + offset), &rhd, (LPVOID*)&rhd_original) == MH_OK)
    {
        Logger::log_debug("Hook Created");
        MH_EnableHook((LPVOID*)(Hooks::GameAssembly + offset));
    }
}

std::wstring get_executing_directory()
{
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

std::string sanity_config(const std::wstring* dir, const char* config_file)
{
    const std::wstring config_dir = *dir + L"/GK_config";
    CreateDirectory(config_dir.c_str(), nullptr);
    const std::string config_string_temp(config_file);
    const std::wstring config_string(config_string_temp.begin(), config_string_temp.end());
    const std::wstring path_temp = config_dir + L"/" + config_string + L".GK";
    std::string path(path_temp.begin(), path_temp.end());
    FILE* file;
    fopen_s(&file, path.c_str(), "a+");
    fclose(file);
    return path;
}

std::string find_or_default_config(std::list<std::string> lines, std::string search)
{
    for (auto line : lines)
    {
        if(line.starts_with(search))
        {
            return line.substr(line.find_last_of(";") + 1, line.length());
        }
    }
    return "not_found";
}

void panic()
{
    // Turn modules off
    for (const auto& module : GKImGuiHooker::modules)
    {
        std::stringstream full_setting_name;
        full_setting_name << "Enabled##" << module->name;
        module->enabled = module->enabled_by_default;

        for (const auto setting : module->settings)
        {
            switch (setting->type)
            {
            case 1:
            {
                ((GKCheckbox*)setting)->enabled = ((GKCheckbox*)setting)->default_value;
                break;
            }
            case 2:
                ((GKSlider*)setting)->value = ((GKSlider*)setting)->default_value;
                break;
            case 3:
                ((GKSliderInt*)setting)->value = ((GKSliderInt*)setting)->default_value;
                break;
            default: break;
            }
        }
    }

    Logger::log_info("Panic! Reset all settings to default");
}

std::vector<std::string> get_config_names() {
	std::vector<std::string> files;
	const std::wstring dir = get_executing_directory();
	const std::wstring config_dir = dir + L"/bkc_config";
	for (const auto& entry : std::filesystem::directory_iterator(config_dir))
	{
		const std::filesystem::path& p = entry.path();
		std::string str_path = p.generic_string();
		str_path = str_path.substr(str_path.find_last_of("\\/") + 1);
		str_path = str_path.substr(0, str_path.find_last_of("."));
		files.push_back(str_path);
	}
	return files;
}

void load_config(const char* config_file)
{
    const std::wstring dir = get_executing_directory();
    const std::string file_path = sanity_config(&dir, config_file);
    FILE* file;
    fopen_s(&file, file_path.c_str(), "r+");
    std::ifstream in(file);
    std::list<std::string> lines;
    if (in.is_open())
    {
        std::string line;
        while (std::getline(in, line))
        {
            lines.push_back(line);
        }
        in.close();
    }

    const std::string NOT_FOUND = "not_found";
    
    // Read Modules
    for (const auto& module : GKImGuiHooker::modules)
    {
        std::string found;
        const std::string NOT_FOUND = "not_found";
        std::stringstream pe;
        pe << module->name << ";" << "enabled" << ";";
        bool enabled;
        found = find_or_default_config(lines, pe.str());
        if (found != NOT_FOUND)
        {
            std::istringstream(found) >> enabled; // idk why this errors in ide it works
            module->enabled = enabled;
        }
        
        std::stringstream ke;
        ke << module->name << ";" << "key" << ";";
        found = find_or_default_config(lines, ke.str());
        if (found != NOT_FOUND)
        {
            const int key = stoi(found);
            module->key = key;
        }
        
        for (const auto setting : module->settings)
        {
            std::stringstream data;
            bool cbv;
            float slv;
            int islv;
            int dtv;
            switch (setting->type)
            {
            case 1:
                data << module->name << ";" << setting->name << ";" << "checkbox" << ";";
                found = find_or_default_config(lines, data.str());
                if (found != NOT_FOUND)
                {
                    std::istringstream(found) >> cbv;
                    ((GKCheckbox*)setting)->enabled = cbv;
                }
                break;
            case 2:
                data << module->name << ";" << setting->name << ";" << "slider" << ";";
                found = find_or_default_config(lines, data.str());
                if (found != NOT_FOUND)
                {
                    slv = std::stof(found);
                    ((GKSlider*)setting)->value = slv;
                }
                break;
            case 3:
                data << module->name << ";" << setting->name << ";" << "int_slider" << ";";
                found = find_or_default_config(lines, data.str());
                if (found != NOT_FOUND)
                {
                    islv = std::stoi(found);
                    ((GKSliderInt*)setting)->value = islv;
                }
                break;
            case 4:
                data << module->name << ";" << setting->name << ";" << "dropdown" << ";";
                found = find_or_default_config(lines, data.str());
                if (found != NOT_FOUND)
                {
                    dtv = std::stoi(found);
                    ((GKDropdown*)setting)->current_index = dtv;
                    ((GKDropdown*)setting)->current_value = ((GKDropdown*)setting)->values[dtv];
                }
                break;
            default: break;
            }
        }
    }
    
    // Read Other Configs
    std::stringstream data;
    data << "clientsetting;font;";
    std::string found = find_or_default_config(lines, data.str());
    if (found != NOT_FOUND)
    {
        current_font = found;
        font_changed = true;
    }

    std::stringstream msg;
    msg << "Loaded config " << config_file;
    Logger::log_info(msg.str());
    fclose(file);
}

void save_config(const char* config_file)
{
    const std::wstring dir = get_executing_directory();
    const std::string file_path = sanity_config(&dir, config_file);
    FILE* file;
    fopen_s(&file, file_path.c_str(), "w+");
    std::ofstream out(file);

    // Write Modules
    for (const auto& module : GKImGuiHooker::modules)
    {
        out << module->name << ";" << "enabled" << ";" << module->enabled << std::endl;
        out << module->name << ";" << "key" << ";" << module->key << std::endl;
        for (const auto setting : module->settings)
        {
            switch (setting->type)
            {
            case 1:
                out << module->name << ";" << setting->name << ";" << "checkbox" << ";" << ((GKCheckbox*)setting)->enabled << std::endl;
                break;
            case 2:
                out << module->name << ";" << setting->name << ";" << "slider" << ";" << ((GKSlider*)setting)->value << std::endl;
                break;
            case 3:
                out << module->name << ";" << setting->name << ";" << "int_slider" << ";" << ((GKSliderInt*)setting)->value << std::endl;
                break;
            case 4:
                out << module->name << ";" << setting->name << ";" << "dropdown" << ";" << ((GKDropdown*)setting)->indexof(((GKDropdown*)setting)->current_value) << std::endl;
                break;
            default: break;
            }
        }
    }

    // Write Other Config
    out << "clientsetting;font;" << current_font << std::endl;

    std::stringstream msg;
    msg << "Saved config " << config_file;
    Logger::log_info(msg.str());
    out.close();
    fclose(file);
}

HWND imgui_hwnd;
std::list<GKModule*> GKImGuiHooker::modules = {};
ImFont* GKImGuiHooker::gui_font = nullptr;
ImFont* GKImGuiHooker::watermark_font = nullptr;
ImFont* GKImGuiHooker::arraylist_font = nullptr;
bool GKImGuiHooker::modules_loaded = false;
bool GKImGuiHooker::config_loaded = false;
bool GKImGuiHooker::c_GuiEnabled = false;
float GKImGuiHooker::scale_factor = 1;
std::string GKImGuiHooker::c_Title = "GirlKisser";
std::string GKImGuiHooker::c_Build = "v1.5-BETA";
std::string GKImGuiHooker::c_Message = "Tits <3";


void GKImGuiHooker::setup_imgui_hwnd(HWND handle, ID3D11Device * device, ID3D11DeviceContext * device_context)
{
    imgui_hwnd = handle;
    Logger::log_info("Setting up ImGui instance...");
    full_title << c_Title << " - " << c_Message << " (" << c_Build << ")"; // init the full title
    Logger::log_info("Found current version: " + full_title.str());
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    // Load Theme
    ImGui::StyleColorsDark();
    init_style();
    ImGui_ImplWin32_Init(imgui_hwnd);
    ImGui_ImplDX11_Init(device, device_context);
    int horizontal = 0;
    int vertical = 0;
    GetDesktopResolution(horizontal, vertical);
    scale_factor = ((float)horizontal / 1920.0f + (float)vertical / 1080.0f) / 2.0f;
    std::stringstream multi_out;
    multi_out << "Using " << scale_factor << "x scale factor for ImGui fonts";
    Logger::log_info(multi_out.str());
    // create font from file (thank god doesn't need to be only loaded from memory, but still can be)
    gui_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 20.0f * scale_factor);
    watermark_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 32.0f * scale_factor);
    arraylist_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 24.0f * scale_factor);
}

void GKImGuiHooker::start(ID3D11RenderTargetView* g_mainRenderTargetView, ID3D11DeviceContext* g_pd3dDeviceContext)
{
    while (gui_font == nullptr || watermark_font == nullptr || arraylist_font == nullptr)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    // Load Config
    if (modules_loaded && !config_loaded)
    {
        config_loaded = true;
        Logger::log_info("Loaded default config!");
    }

    // TODO: Make this not suck
    if (font_changed)
    {
        font_changed = false;
        ImGuiIO& io2 = ImGui::GetIO(); (void)io2;
        gui_font = io2.Fonts->AddFontFromFileTTF(current_font.c_str(), 20.0f * scale_factor);
        watermark_font = io2.Fonts->AddFontFromFileTTF(current_font.c_str(), 32.0f * scale_factor);
        arraylist_font = io2.Fonts->AddFontFromFileTTF(current_font.c_str(), 24.0f * scale_factor);
        io2.Fonts->Build();
        // force invalidation and new frames
        ImGui_ImplDX11_InvalidateDeviceObjects();
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        Logger::log_info("Changed client font to " + current_font);
        return;
    }
    
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::PushFont(gui_font);
    if (c_GuiEnabled)
    {
        ImGui::Begin(full_title.str().c_str());

        // HandleCategoryRendering("General", GENERAL);
        HandleCategoryRendering("Combat", COMBAT);
        HandleCategoryRendering("Visual", VISUAL);
        HandleCategoryRendering("Movement", MOVEMENT);
        HandleCategoryRendering("Player", PLAYER);
        HandleCategoryRendering("Rewards", REWARDS);
        HandleCategoryRendering("Uncategorized", NONE);

        // Configs
        if (ImGui::CollapsingHeader("Config"))
        {
			ImGui::Indent();

            ImGui::InputText("##config_text", config_file, sizeof(config_file));
            ImGui::SameLine();
			if (ImGui::Button("Create##config"))
			{
				save_config(config_file);
                combo_file = config_file;
			}

			std::vector<std::string> files = get_config_names();

			if (ImGui::BeginCombo("##config_combo", combo_file.c_str()))
			{
				for (std::string::size_type i = 0; i < files.size(); i++)
				{
					const bool selected = combo_file == files[i];

					if (ImGui::Selectable(files[i].c_str(), selected))
					{
						combo_file = files[i];
					}
					if (selected) ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}
            
            ImGui::SameLine();
            if (ImGui::Button("Load"))
            {
                load_config(combo_file.c_str());
            }
            ImGui::SameLine();
            if (ImGui::Button("Save"))
            {
                save_config(combo_file.c_str());
            }

			ImGui::Unindent();
        }

        // Hack client stuff
        if (ImGui::CollapsingHeader("Client"))
        {
            ImGui::Indent();
            if (ImGui::Button("Panic"))
            {
                panic();
            }

            if (ImGui::BeginCombo("Font", current_font.c_str()))
            {
                for (std::string::size_type i = 0; i < fonts.size(); i++)
                {
                    const bool selected = current_font == fonts[i];

                    if (ImGui::Selectable(fonts[i].c_str(), selected))
                    {
                        current_font = fonts[i];
                        ImGuiIO& io = ImGui::GetIO(); (void)io;
                        gui_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 20.0f * scale_factor);
                        watermark_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 32.0f * scale_factor);
                        arraylist_font = io.Fonts->AddFontFromFileTTF(current_font.c_str(), 24.0f * scale_factor);
                        io.Fonts->Build();
                        // force invalidation and new frames
                        ImGui_ImplDX11_InvalidateDeviceObjects();
                        ImGui_ImplDX11_NewFrame(); 
                        ImGui_ImplWin32_NewFrame();
                        ImGui::NewFrame();
                        Logger::log_info("Changed client font to " + current_font);
                        return;
                    }
                    if (selected) ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            if (ImGui::BeginCombo("Theme", current_theme.c_str()))
            {
                for (std::string::size_type i = 0; i < themes.size(); i++)
                {
                    const bool selected = current_theme == themes[i];

                    if (ImGui::Selectable(themes[i].c_str(), selected))
                    {
                        if (selected) continue;
                        current_theme = themes[i];

                        // force invalidation, new frames, and style change
                        // init_style();
                        ImGui_ImplDX11_InvalidateDeviceObjects();
                        ImGui_ImplDX11_NewFrame();
                        ImGui_ImplWin32_NewFrame();
                        ImGui::NewFrame();
                        Logger::log_info("Changed client theme to " + current_theme);
                        return;
                    }
                    if (selected) ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }

            ImGui::Checkbox("Boundless Sliders", &boundless_value_setting);
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Use at your own risk. Allow setting values on sliders below or above minimum and maximum when manually changing them (CTRL Clicking)");
            }

            auto show_enabled = *std::find_if(modules.begin(), modules.end(), [](const auto& module) { return module->name == "Show Enabled Modules"; });
            ImGui::Checkbox("Show Enabled Modules", &show_enabled->enabled);
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Display a list of each module currently enabled");
            }

            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Runtime Hooks (Dev)"))
        {
            {
                ImGui::Indent();


                ImGui::InputText("Offset##rhd", offsets_rhd, sizeof(offsets_rhd));
                ImGui::InputText("Return##rhd", return_rhd, sizeof(return_rhd));
                if (ImGui::Button("Create"))
                {
                    if (ImGui::Button("Create##rhd"))
                    {
                        try_runtime_hook();
                    }
                }
                    
                ImGui::Unindent();
            }
        }

        ImGui::End();
        // ENABLE THIS FOR EASILY FINDING WHAT YOU NEED TO ADD TO THE GUI
        // ImGui::ShowDemoWindow();
    }

    // Modules
    Hooks::draw_all();
    for (auto module : Hooks::on_imgui_draw_modules)
    {
        module->run(nullptr);
    }
    
    ImGui::PopFont();

    // Watermark
    ImGui::PushFont(watermark_font);
    float size = ImGui::GetFontSize();
    ImVec2 true_size = ImGui::CalcTextSize(full_title.str().c_str());
    ImGui::GetBackgroundDrawList()->AddRectFilled({ 5, 5 }, { 15 + true_size.x, 10 + true_size.y }, color_bg, 10);
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, { 10, 5 }, color_title, full_title.str().c_str());
    ImGui::PopFont();
    ImGui::Render();
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void HandleModuleSettingRendering(GKModule& module)
{
    for (auto& setting : module.settings)
    { 
        std::stringstream per_module_name;
        
        if (setting->type == 1)
        {
            auto* checkbox = (GKCheckbox*)setting;
            per_module_name << setting->name << "##" << module.name << setting->type;
            ImGui::Checkbox(per_module_name.str().c_str(), &checkbox->enabled);
        }
        else if (setting->type == 2)
        {
            auto* slider = (GKSlider*)setting;
            per_module_name << setting->name << "##" << module.name << setting->type;
            ImGui::SliderFloat(per_module_name.str().c_str(), &slider->value, slider->minimum, slider->maximum);
            if (!boundless_value_setting) slider->value = std::ranges::clamp(slider->value, slider->minimum, slider->maximum);
        }
        else if (setting->type == 3)
        {
            auto* slider = (GKSliderInt*)setting;
            per_module_name << setting->name << "##" << module.name << setting->type;
            ImGui::SliderInt(per_module_name.str().c_str(), &slider->value, slider->minimum, slider->maximum);
            if (!boundless_value_setting) slider->value = std::ranges::clamp(slider->value, slider->minimum, slider->maximum);
        }
        else if (setting->type == 4)
        {
            auto* dropdown = (GKDropdown*)setting;
            per_module_name << setting->name << "##" << module.name << setting->type;
            if (ImGui::BeginCombo(per_module_name.str().c_str(), dropdown->current_value.c_str()))
            {
                for (std::string::size_type i = 0; i < dropdown->values.size(); i++)
                {
                    const bool selected = dropdown->current_value == dropdown->values[i];
                    
                    if (ImGui::Selectable(dropdown->values[i].c_str(), selected))
                    {
                        dropdown->current_value = dropdown->values[i];
                        dropdown->current_index = dropdown->indexof(dropdown->current_value);
                    }
                    if (selected) ImGui::SetItemDefaultFocus();
                }

                ImGui::EndCombo();
            }
        }

        if (!setting->tooltip.empty())
        {
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip(setting->tooltip.c_str());
            }
        }
    }
}

void HandleModuleRendering(GKModule& module)
{
    ImGui::Indent();
    if (ImGui::CollapsingHeader(module.name.c_str()))
    {
        std::stringstream module_enabled_id;
        module_enabled_id << "Enabled##" << module.name;
        ImGui::Indent();
        ImGui::SeparatorText("Active Status");
        ImGui::Checkbox(module_enabled_id.str().c_str(), &module.enabled);
        ImGui::SeparatorText("Settings");
        HandleModuleSettingRendering(module);
        ImGui::Unindent();
    }
    ImGui::Unindent();
}


void HandleCategoryRendering(const std::string& name, const GKCategory cat)
{
    if (ImGui::CollapsingHeader(name.c_str()))
    {
        for (auto& module : GKImGuiHooker::modules)
        {
            if (module->category != cat) continue;
            if (module->name == "Show Enabled Modules") continue;
            HandleModuleRendering(*module);
        }
    }
}
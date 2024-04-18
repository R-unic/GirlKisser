#pragma once

#include <imgui.h>
#include <iostream>
#include <vector>
#include <d3d11.h>
#include <list>

// Boykisser Central Module Vars
template<typename T = int>
class GKSetting
{
public:
    int type = 0;
    T default_value;
    std::string name;
    std::string tooltip;
};

class GKCheckbox : public GKSetting<bool>
{
public:
    GKCheckbox(const std::string& setting_name, const bool checked, const std::string& extra_info = "")
    {
        name = setting_name;
        default_value = checked;
        enabled = checked;
        tooltip = extra_info;
        type = 1;
    }
    bool default_value;
    bool enabled;
};

class GKSlider : public GKSetting<float>
{
public:
    GKSlider(const std::string& setting_name, const float val, const float min, const float max, const std::string& extra_info = "")
    {
        name = setting_name;
        default_value = val;
        value = val;
        minimum = min;
        maximum = max;
        tooltip = extra_info;
        type = 2;
    }
    float default_value;
    float value;
    float minimum;
    float maximum;
};

class GKSliderInt : public GKSetting<int>
{
public:
    GKSliderInt(const std::string& setting_name, const int val, const int min, const int max, const std::string& extra_info = "")
    {
        name = setting_name;
        default_value = val;
        value = val;
        minimum = min;
        maximum = max;
        tooltip = extra_info;
        type = 3;
    }
    int default_value;
    int value;
    int minimum;
    int maximum;
};

class GKDropdown : public GKSetting<>
{
public:
    GKDropdown(const std::string& setting_name, const std::string& def_val, const std::vector<std::string>& vals, const std::string& extra_info = "", const bool allow_search = false)
    {
        name = setting_name;
        values = vals;
        current_value = def_val;
        current_index = indexof(def_val);
        tooltip = extra_info;
        search = allow_search;
        type = 4;
    }
    int indexof(std::string val)
    {
        auto indexer = std::ranges::find(values, val);
        return indexer != values.end() ? (int)(indexer - values.begin()) : -1;
    }
    int current_index;
    std::string current_value;
    std::vector<std::string> values;
    bool search;
    char search_str[64] = "";
};

enum GKCategory
{
    NONE = 0,
    GENERAL = 1,
    COMBAT = 2,
    VISUAL = 3,
    MOVEMENT = 4,
    PLAYER = 5,
    EXPLOIT = 6
};

class GKModule
{
public:
    std::string name;
    GKCategory category = NONE;
    WPARAM key = 0x0;
    ImGuiKey activationKey;
    bool enabled = false;
    std::vector<GKSetting<>*> settings = {};
    bool enabled_by_default = enabled;
    void toggle()
    {
        enabled = !enabled;
    }
};

class GKImGuiHooker
{
public:
    static std::list<GKModule*> modules;
    static ImFont* gui_font;
    static ImFont* watermark_font;
    static ImFont* arraylist_font;
    static std::string c_Title;
    static std::string c_Build;
    static std::string c_Message;
    static std::string c_RealBuild;
    static float scale_factor;
    static bool modules_loaded;
    static bool config_loaded;
    static bool c_GuiEnabled;
    static void setup_imgui_hwnd(HWND handle, ID3D11Device* device, ID3D11DeviceContext* device_context);
    static void start(ID3D11RenderTargetView* g_mainRenderTargetView, ID3D11DeviceContext* g_pd3dDeviceContext);
};
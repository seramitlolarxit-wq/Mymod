#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <cstdint>
#include <cstring>
#include <string>

#include "imgui.h"
#include "imgui_impl_opengl3.h"

#define LOG_TAG "ROCKET"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// ============================================================
//  ОФФСЕТЫ (RVA от базы libil2cpp.so)
// ============================================================
namespace off {
    // --- il2cpp API ---
    constexpr uintptr_t il2cpp_alloc                        = 0x63279E8;
    constexpr uintptr_t il2cpp_array_class_get              = 0x63279FC;
    constexpr uintptr_t il2cpp_array_length                 = 0x6327A00;
    constexpr uintptr_t il2cpp_array_new                    = 0x6327A04;
    constexpr uintptr_t il2cpp_assembly_get_image           = 0x6327A18;
    constexpr uintptr_t il2cpp_class_array_element_size     = 0x6327B3C;
    constexpr uintptr_t il2cpp_class_enum_basetype          = 0x6327A1C;
    constexpr uintptr_t il2cpp_class_from_il2cpp_type       = 0x6327A34;
    constexpr uintptr_t il2cpp_class_from_name              = 0x6327A3C;
    constexpr uintptr_t il2cpp_class_from_type              = 0x6327B40;
    constexpr uintptr_t il2cpp_class_get_assemblyname       = 0x6327B64;
    constexpr uintptr_t il2cpp_class_get_declaring_type     = 0x6327AE4;
    constexpr uintptr_t il2cpp_class_get_element_class      = 0x6327AC4;
    constexpr uintptr_t il2cpp_class_get_field_from_name    = 0x6327AD0;
    constexpr uintptr_t il2cpp_class_get_fields             = 0x6327AC8;
    constexpr uintptr_t il2cpp_class_get_flags              = 0x6327B04;
    constexpr uintptr_t il2cpp_class_get_image              = 0x6327B60;
    constexpr uintptr_t il2cpp_class_get_interfaces         = 0x632EAB8;
    constexpr uintptr_t il2cpp_class_get_method_from_name   = 0x632EC50;
    constexpr uintptr_t il2cpp_class_get_methods            = 0x6327AD4;
    constexpr uintptr_t il2cpp_class_get_name               = 0x6327AD8;
    constexpr uintptr_t il2cpp_class_get_namespace          = 0x6327ADC;
    constexpr uintptr_t il2cpp_class_get_nested_types       = 0x6327ACC;
    constexpr uintptr_t il2cpp_class_get_parent             = 0x6327AE0;
    constexpr uintptr_t il2cpp_class_get_rank               = 0x6327B68;
    constexpr uintptr_t il2cpp_class_get_type               = 0x6327B48;
    constexpr uintptr_t il2cpp_class_instance_size          = 0x6327AE8;
    constexpr uintptr_t il2cpp_class_is_abstract            = 0x6327B0C;
    constexpr uintptr_t il2cpp_class_is_blittable           = 0x6327AF8;
    constexpr uintptr_t il2cpp_class_is_enum                = 0x6327B50;
    constexpr uintptr_t il2cpp_class_is_generic             = 0x6327A28;
    constexpr uintptr_t il2cpp_class_is_interface           = 0x6327B54;
    constexpr uintptr_t il2cpp_class_is_valuetype           = 0x6327B18;
    constexpr uintptr_t il2cpp_domain_assembly_open         = 0x6327B74;
    constexpr uintptr_t il2cpp_domain_get                   = 0x6327B70;
    constexpr uintptr_t il2cpp_field_get_flags              = 0x6327C3C;
    constexpr uintptr_t il2cpp_field_get_name               = 0x6327C38;
    constexpr uintptr_t il2cpp_field_get_offset             = 0x6327C44;
    constexpr uintptr_t il2cpp_field_get_parent             = 0x6327C40;
    constexpr uintptr_t il2cpp_field_get_type               = 0x6327C48;
    constexpr uintptr_t il2cpp_field_get_value              = 0x6327C4C;
    constexpr uintptr_t il2cpp_field_static_get_value       = 0x6327C50;
    constexpr uintptr_t il2cpp_free                         = 0x63279F8;
    constexpr uintptr_t il2cpp_get_corlib                   = 0x63279F0;
    constexpr uintptr_t il2cpp_init                         = 0x6327990;
    constexpr uintptr_t il2cpp_memory_pool_get_region_size  = 0x63279EC;
    constexpr uintptr_t il2cpp_method_get_class             = 0x6327D04;
    constexpr uintptr_t il2cpp_method_get_declaring_type    = 0x6327D0C;
    constexpr uintptr_t il2cpp_method_get_from_reflection   = 0x6327CE4;
    constexpr uintptr_t il2cpp_method_get_name              = 0x6327CEC;
    constexpr uintptr_t il2cpp_method_get_object            = 0x6327CE8;
    constexpr uintptr_t il2cpp_method_get_param             = 0x6327D00;
    constexpr uintptr_t il2cpp_method_get_param_count       = 0x6327CFC;
    constexpr uintptr_t il2cpp_method_get_param_name        = 0x6327D10;
    constexpr uintptr_t il2cpp_method_get_return_type       = 0x6327CE0;
    constexpr uintptr_t il2cpp_method_has_attribute         = 0x6327D08;
    constexpr uintptr_t il2cpp_method_is_generic            = 0x6327CF0;
    constexpr uintptr_t il2cpp_method_is_inflated           = 0x6327CF4;
    constexpr uintptr_t il2cpp_method_is_instance           = 0x6327CF8;
    constexpr uintptr_t il2cpp_object_get_virtual_method    = 0x6327D14;
    constexpr uintptr_t il2cpp_object_new                   = 0x6327D38;
    constexpr uintptr_t il2cpp_object_unbox                 = 0x6327D34;
    constexpr uintptr_t il2cpp_register_log_callback        = 0x6327E78;
    constexpr uintptr_t il2cpp_resolve_icall                = 0x63279F4;
    constexpr uintptr_t il2cpp_runtime_invoke               = 0x6327D44;
    constexpr uintptr_t il2cpp_runtime_invoke_convert_args  = 0x6327D40;
    constexpr uintptr_t il2cpp_runtime_object_init_exception= 0x6327D48;
    constexpr uintptr_t il2cpp_runtime_unhandled_exception_policy_set = 0x6327D4C;
    constexpr uintptr_t il2cpp_set_commandline_arguments    = 0x63279C8;
    constexpr uintptr_t il2cpp_set_config_dir               = 0x63279C0;
    constexpr uintptr_t il2cpp_set_memory_callbacks         = 0x63279E4;
    constexpr uintptr_t il2cpp_set_temp_dir                 = 0x63279C4;
    constexpr uintptr_t il2cpp_shutdown                     = 0x63279BC;
    constexpr uintptr_t il2cpp_string_chars                 = 0x6327D54;
    constexpr uintptr_t il2cpp_string_intern                = 0x6327D68;
    constexpr uintptr_t il2cpp_string_length                = 0x6327D50;
    constexpr uintptr_t il2cpp_string_new                   = 0x6327D58;
    constexpr uintptr_t il2cpp_string_new_len               = 0x6327D64;
    constexpr uintptr_t il2cpp_string_new_utf16             = 0x6327D60;
    constexpr uintptr_t il2cpp_string_new_wrapper           = 0x6327D5C;
    constexpr uintptr_t il2cpp_thread_attach                = 0x6327D70;
    constexpr uintptr_t il2cpp_thread_current               = 0x6327D6C;
    constexpr uintptr_t il2cpp_thread_detach                = 0x6327D74;
    constexpr uintptr_t il2cpp_type_get_attrs               = 0x6327E40;
    constexpr uintptr_t il2cpp_type_get_class_or_element_class = 0x6327D84;
    constexpr uintptr_t il2cpp_type_get_name                = 0x6327D8C;
    constexpr uintptr_t il2cpp_type_get_object              = 0x6327D7C;
    constexpr uintptr_t il2cpp_type_get_reflection_name     = 0x6327E2C;
    constexpr uintptr_t il2cpp_type_get_type                = 0x6327D80;
    constexpr uintptr_t il2cpp_type_is_byref                = 0x6327E34;
    constexpr uintptr_t il2cpp_value_box                    = 0x6327D3C;

    // --- metadata tables ---
    constexpr uintptr_t metadataMethodDefinitions           = 0x2016BC0;
    constexpr uintptr_t metadataPropertyDefinitions         = 0x274BDF4;
    constexpr uintptr_t metadataTypeDefinitions             = 0x29F1F52;
    constexpr uintptr_t metadataFieldDefinitions            = 0x1AA3620;
    constexpr uintptr_t metadataStringHeap                  = 0x2D21B04;
    constexpr uintptr_t metadataParameterDefinitions        = 0x1C1AD98;
    constexpr uintptr_t typePointerTable                    = 0xB9BB0E0;
    constexpr uintptr_t fieldOffsetPointerTable             = 0xBF211F8;
    constexpr uintptr_t typeInfoDefinitionTable             = 0xB9BB0E0;

    // --- runtime layouts ---
    constexpr uintptr_t Il2CppImage__class_count            = 0x24;

    constexpr uintptr_t Il2CppClass__image                  = 0x0;
    constexpr uintptr_t Il2CppClass__static_fields          = 0x40;
    constexpr uintptr_t Il2CppClass__field_count            = 0x58;
    constexpr uintptr_t Il2CppClass__instance_size          = 0x60;
    constexpr uintptr_t Il2CppClass__interface_count        = 0x6E;
    constexpr uintptr_t Il2CppClass__methods                = 0x80;
    constexpr uintptr_t Il2CppClass__nested_type_count      = 0x88;
    constexpr uintptr_t Il2CppClass__implemented_interfaces = 0xA0;
    constexpr uintptr_t Il2CppClass__nested_types           = 0xB8;
    constexpr uintptr_t Il2CppClass__fields                 = 0xC0;
    constexpr uintptr_t Il2CppClass__namespace              = 0xD8;
    constexpr uintptr_t Il2CppClass__parent                 = 0xE8;
    constexpr uintptr_t Il2CppClass__declaring_type         = 0xF0;
    constexpr uintptr_t Il2CppClass__generic_class          = 0xF8;
    constexpr uintptr_t Il2CppClass__typeMetadataHandle     = 0x108;
    constexpr uintptr_t Il2CppClass__flags                  = 0x118;
    constexpr uintptr_t Il2CppClass__element_class          = 0x120;
    constexpr uintptr_t Il2CppClass__byval_arg              = 0x138;
    constexpr uintptr_t Il2CppClass__method_count           = 0x17A;
    constexpr uintptr_t Il2CppClass__rank                   = 0x194;
    constexpr uintptr_t Il2CppClass__name                   = 0x198;

    constexpr uintptr_t FieldInfo__name                     = 0x0;
    constexpr uintptr_t FieldInfo__token                    = 0x8;
    constexpr uintptr_t FieldInfo__parent                   = 0x10;
    constexpr uintptr_t FieldInfo__type                     = 0x18;
    constexpr uintptr_t FieldInfo__offset                   = 0x20;
    constexpr uintptr_t FieldInfo__size                     = 0x28;

    constexpr uintptr_t MethodInfo__slot                    = 0x0;
    constexpr uintptr_t MethodInfo__return_type             = 0x8;
    constexpr uintptr_t MethodInfo__name                    = 0x10;
    constexpr uintptr_t MethodInfo__methodPointer           = 0x30;
    constexpr uintptr_t MethodInfo__parameters              = 0x38;
    constexpr uintptr_t MethodInfo__invokerMethod           = 0x40;
    constexpr uintptr_t MethodInfo__token                   = 0x48;
    constexpr uintptr_t MethodInfo__flags                   = 0x4C;
    constexpr uintptr_t MethodInfo__virtualMethodPointer    = 0x50;
    constexpr uintptr_t MethodInfo__klass                   = 0x68;
    constexpr uintptr_t MethodInfo__parameters_count        = 0x71;
    constexpr uintptr_t MethodInfo__is_generic_bitfield     = 0x72;
}

// ============================================================
//  БАЗА libil2cpp.so + указатели на API
// ============================================================
static uintptr_t g_il2cppBase = 0;

typedef void*   (*t_class_from_name)(const void*, const char*, const char*);
typedef void*   (*t_domain_get)();
typedef void*   (*t_domain_assembly_open)(void*, const char*);
typedef void*   (*t_assembly_get_image)(void*);
typedef void*   (*t_class_get_method_from_name)(void*, const char*, int);
typedef void*   (*t_class_get_field_from_name)(void*, const char*);
typedef size_t  (*t_field_get_offset)(void*);
typedef void*   (*t_runtime_invoke)(void*, void*, void**, void**);
typedef void*   (*t_object_new)(void*);
typedef void*   (*t_thread_attach)(void*);
typedef void*   (*t_string_new)(const char*);

static t_class_from_name             p_class_from_name;
static t_domain_get                  p_domain_get;
static t_domain_assembly_open        p_domain_assembly_open;
static t_assembly_get_image          p_assembly_get_image;
static t_class_get_method_from_name  p_class_get_method_from_name;
static t_class_get_field_from_name   p_class_get_field_from_name;
static t_field_get_offset            p_field_get_offset;
static t_runtime_invoke              p_runtime_invoke;
static t_object_new                  p_object_new;
static t_thread_attach               p_thread_attach;
static t_string_new                  p_string_new;

static void InitIl2CppApi(uintptr_t base) {
    p_class_from_name            = (t_class_from_name)(base + off::il2cpp_class_from_name);
    p_domain_get                 = (t_domain_get)(base + off::il2cpp_domain_get);
    p_domain_assembly_open       = (t_domain_assembly_open)(base + off::il2cpp_domain_assembly_open);
    p_assembly_get_image         = (t_assembly_get_image)(base + off::il2cpp_assembly_get_image);
    p_class_get_method_from_name = (t_class_get_method_from_name)(base + off::il2cpp_class_get_method_from_name);
    p_class_get_field_from_name  = (t_class_get_field_from_name)(base + off::il2cpp_class_get_field_from_name);
    p_field_get_offset           = (t_field_get_offset)(base + off::il2cpp_field_get_offset);
    p_runtime_invoke             = (t_runtime_invoke)(base + off::il2cpp_runtime_invoke);
    p_object_new                 = (t_object_new)(base + off::il2cpp_object_new);
    p_thread_attach              = (t_thread_attach)(base + off::il2cpp_thread_attach);
    p_string_new                 = (t_string_new)(base + off::il2cpp_string_new);
}

// ============================================================
//  КОНФИГ
// ============================================================
struct AimbotConfig {
    bool enabled = false;
    bool silent = false;
    float speed = 1.0f;
    bool throughWalls = false;
    float fov = 30.0f;
    bool selectAim = false;
    float selectFov = 30.0f;
};

struct VisualConfig {
    bool boxEsp = false;
    bool healthEsp = false;
    bool ammoEsp = false;
};

struct MiscConfig {
    bool shootThroughWalls = false;
    bool killTeammates = false;
    bool antiAim = false;
    bool thirdPerson = false;
    bool moveBeforeRound = false;
    bool bhop = false;
};

struct SettingsConfig {
    bool hideFromScreenshots = false;
    ImVec4 menuColor = ImVec4(0.48f, 0.18f, 0.97f, 1.0f);
};

static AimbotConfig aim;
static VisualConfig vis;
static MiscConfig misc;
static SettingsConfig set;
static bool g_menuOpen = false;

// ============================================================
//  UI
// ============================================================
static void ApplyStyle() {
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowRounding    = 10.0f;
    s.FrameRounding     = 6.0f;
    s.GrabRounding      = 6.0f;
    s.ScrollbarRounding = 6.0f;
    s.WindowPadding     = ImVec2(12, 12);
    s.FramePadding      = ImVec2(8, 4);
    s.ItemSpacing       = ImVec2(8, 6);

    ImVec4* c = s.Colors;
    c[ImGuiCol_WindowBg]         = ImVec4(0.07f, 0.07f, 0.10f, 0.96f);
    c[ImGuiCol_ChildBg]          = ImVec4(0.10f, 0.10f, 0.14f, 1.00f);
    c[ImGuiCol_FrameBg]          = ImVec4(0.15f, 0.15f, 0.20f, 1.00f);
    c[ImGuiCol_FrameBgHovered]   = ImVec4(0.20f, 0.20f, 0.28f, 1.00f);
    c[ImGuiCol_FrameBgActive]    = set.menuColor;
    c[ImGuiCol_CheckMark]        = set.menuColor;
    c[ImGuiCol_SliderGrab]       = set.menuColor;
    c[ImGuiCol_SliderGrabActive] = set.menuColor;
    c[ImGuiCol_Button]           = ImVec4(0.18f, 0.18f, 0.24f, 1.00f);
    c[ImGuiCol_ButtonHovered]    = set.menuColor;
    c[ImGuiCol_ButtonActive]     = set.menuColor;
    c[ImGuiCol_Header]           = set.menuColor;
    c[ImGuiCol_HeaderHovered]    = set.menuColor;
    c[ImGuiCol_HeaderActive]     = set.menuColor;
    c[ImGuiCol_Tab]              = ImVec4(0.12f, 0.12f, 0.16f, 1.00f);
    c[ImGuiCol_TabHovered]       = set.menuColor;
    c[ImGuiCol_TabActive]        = set.menuColor;
}

static void DrawTriggerBar() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, 6));
    ImGui::Begin("##trigger", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    ImGui::InvisibleButton("##bar", ImVec2(io.DisplaySize.x, 6));
    if (ImGui::IsItemActive() && ImGui::GetIO().MouseDelta.y > 4.0f)
        g_menuOpen = true;
    ImGui::End();
}

static void TabAimbot() {
    ImGui::Columns(2, nullptr, false);

    ImGui::TextColored(set.menuColor, "AIMBOT");
    ImGui::Separator();
    ImGui::Checkbox("Enable Aimbot", &aim.enabled);
    ImGui::Checkbox("Silent Aim", &aim.silent);
    ImGui::SliderFloat("Speed", &aim.speed, 0.0f, 2.0f, "%.1fx");
    ImGui::Checkbox("Through Walls", &aim.throughWalls);
    ImGui::SliderFloat("FOV", &aim.fov, 0.0f, 1000.0f, "%.0f%%");

    ImGui::NextColumn();

    ImGui::TextColored(set.menuColor, "SELECT AIM");
    ImGui::Separator();
    ImGui::Checkbox("Enable Select", &aim.selectAim);
    if (aim.selectAim)
        ImGui::SliderFloat("Select FOV", &aim.selectFov, 0.0f, 1000.0f, "%.0f%%");

    ImGui::Columns(1);
}

static void TabVisual() {
    ImGui::TextColored(set.menuColor, "VISUALS");
    ImGui::Separator();
    ImGui::Checkbox("Box ESP",    &vis.boxEsp);
    ImGui::Checkbox("Health ESP", &vis.healthEsp);
    ImGui::Checkbox("Ammo ESP",   &vis.ammoEsp);
}

static void TabMisc() {
    ImGui::TextColored(set.menuColor, "MISC");
    ImGui::Separator();
    ImGui::Checkbox("Shoot Through Walls",  &misc.shootThroughWalls);
    ImGui::Checkbox("Kill Teammates",       &misc.killTeammates);
    ImGui::Checkbox("Anti-Aim",             &misc.antiAim);
    ImGui::Checkbox("Third Person",         &misc.thirdPerson);
    ImGui::Checkbox("Move Before Round",    &misc.moveBeforeRound);
    ImGui::Checkbox("Bunny Hop",            &misc.bhop);
}

static void TabConfig() {
    ImGui::Columns(2, nullptr, false);
    static char cfgName[32] = "default";

    ImGui::TextColored(set.menuColor, "SAVE");
    ImGui::Separator();
    ImGui::InputText("Name", cfgName, 32);
    if (ImGui::Button("Save Config", ImVec2(150, 0))) {
        // TODO: сохранить в /sdcard/RocketMenu/<cfgName>.cfg
    }

    ImGui::NextColumn();

    ImGui::TextColored(set.menuColor, "LOAD");
    ImGui::Separator();
    for (int i = 0; i < 5; i++) {
        std::string slot = "slot" + std::to_string(i);
        if (ImGui::Button(slot.c_str(), ImVec2(150, 0))) {
            // TODO: загрузить из /sdcard/RocketMenu/<slot>.cfg
        }
    }

    ImGui::Columns(1);
}

static void TabSettings() {
    ImGui::TextColored(set.menuColor, "SETTINGS");
    ImGui::Separator();
    ImGui::Checkbox("Hide from Video/Screenshots", &set.hideFromScreenshots);
    ImGui::ColorEdit4("Menu Color", (float*)&set.menuColor);
}

static void RenderMenu() {
    DrawTriggerBar();
    if (!g_menuOpen) return;

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(ImVec2(560, 380), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
                            ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));

    ImGui::Begin("ROCKET", &g_menuOpen,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    if (ImGui::BeginTabBar("##tabs")) {
        if (ImGui::BeginTabItem("Aimbot"))   { TabAimbot();   ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("Visual"))   { TabVisual();   ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("Misc"))     { TabMisc();     ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("Config"))   { TabConfig();   ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("Settings")) { TabSettings(); ImGui::EndTabItem(); }
        ImGui::EndTabBar();
    }

    ImGui::End();
}

// ============================================================
//  JNI_OnLoad — точка входа
// ============================================================
extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("ROCKET loaded");

    void* handle = dlopen("libil2cpp.so", RTLD_LAZY | RTLD_NOLOAD);
    if (!handle) handle = dlopen("libil2cpp.so", RTLD_LAZY);

    if (handle) {
        g_il2cppBase = (uintptr_t)handle;
        InitIl2CppApi(g_il2cppBase);
        LOGI("libil2cpp.so base: 0x%lx", (unsigned long)g_il2cppBase);
    } else {
        LOGE("libil2cpp.so not found");
    }

    return JNI_VERSION_1_6;
}

// Точки, которые вызывает твой overlay/render поток
extern "C" void InitUI()      { ApplyStyle(); }
extern "C" void RenderFrame() { RenderMenu(); }

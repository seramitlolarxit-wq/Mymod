#include <jni.h>
#include <string>
#include "imgui.h"
#include "imgui_internal.h"
#include "Offsets.h" // Исправлено на большую букву

// ============================================================================
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ НАСТРОЕК
// ============================================================================

float g_MenuScale = 1.0f;
float g_LastAppliedScale = 1.0f;
bool g_HideFromScreenshots = false;

bool g_EspEnabled = false;
bool g_EspBox = true;
bool g_EspLine = false;
bool g_EspDistance = true;
bool g_EspHealth = true;

bool g_AimbotEnabled = false;
int g_AimType = 0; 
int g_SelectedAimTarget = 0; 
const char* g_AimTargets[] = { "Голова (Head)", "Шея (Neck)", "Тело (Chest)" };
float g_AimbotFov = 60.0f;
float g_AimbotSmooth = 5.0f;
bool g_WallCheck = true;
bool g_AimOnShoot = false;

bool g_NoRecoil = false;
bool g_OneHitKill = false;
bool g_KillAura360 = false;
bool g_AntiBanProtect = true;
bool g_BypassCrashes = true;

// ============================================================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ============================================================================

void ApplyMenuScale(float newScale) {
    ImGuiStyle& style = ImGui::GetStyle();
    style = ImGuiStyle();
    ImGui::StyleColorsDark();
    style.ScaleAllSizes(newScale);
    ImGui::GetIO().FontGlobalScale = newScale;
    g_LastAppliedScale = newScale;
}

void SetWindowSecureFlag(JNIEnv* env, jobject context, bool enable) {
    if (!env || !context) return;
}

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ ОТРИСОВКИ МЕНЮ
// ============================================================================

void RenderCheatMenu(JNIEnv* env, jobject context) {
    if (g_MenuScale != g_LastAppliedScale) {
        ApplyMenuScale(g_MenuScale);
    }

    ImGui::SetNextWindowSize(ImVec2(500 * g_MenuScale, 430 * g_MenuScale), ImGuiCond_FirstUseEver);
    ImGui::Begin("Ultimate Cheat Menu", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginTabBar("MainTabBar")) {

        if (ImGui::BeginTabItem("ESP")) {
            ImGui::Spacing();
            ImGui::Checkbox("Включить ESP", &g_EspEnabled);
            if (g_EspEnabled) {
                ImGui::Separator();
                ImGui::Checkbox("Боксы (Boxes)", &g_EspBox);
                ImGui::Checkbox("Линии (Lines)", &g_EspLine);
                ImGui::Checkbox("Дистанция (Distance)", &g_EspDistance);
                ImGui::Checkbox("Здоровье (Health Bar)", &g_EspHealth);
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Aim")) {
            ImGui::Spacing();
            ImGui::Checkbox("Включить Aim", &g_AimbotEnabled);
            if (g_AimbotEnabled) {
                ImGui::Separator();
                const char* aimTypes[] = { "Memory Aim (Обычный)", "Silent Aim (Скрытый)" };
                ImGui::Combo("Тип Аима", &g_AimType, aimTypes, IM_ARRAYSIZE(aimTypes));
                ImGui::Combo("Цель", &g_SelectedAimTarget, g_AimTargets, IM_ARRAYSIZE(g_AimTargets));
                ImGui::SliderFloat("Радиус (FOV)", &g_AimbotFov, 10.0f, 180.0f, "%.1f deg");
                ImGui::SliderFloat("Плавность", &g_AimbotSmooth, 1.0f, 20.0f, "%.1f");
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Checkbox("WallCheck", &g_WallCheck);
                ImGui::Checkbox("Aim on Shoot", &g_AimOnShoot);
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Разное")) {
            ImGui::Spacing();
            ImGui::Checkbox("Антиотдача", &g_NoRecoil);
            ImGui::Checkbox("One Hit Kill", &g_OneHitKill);
            ImGui::Checkbox("Kill Aura 360", &g_KillAura360);
            ImGui::Separator();
            ImGui::Checkbox("Антибан", &g_AntiBanProtect);
            ImGui::Checkbox("Защита от крашей", &g_BypassCrashes);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Настройки")) {
            if (ImGui::Checkbox("FLAG_SECURE", &g_HideFromScreenshots)) {
                SetWindowSecureFlag(env, context, g_HideFromScreenshots);
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();
}

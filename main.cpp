#include <jni.h>
#include <string>
#include "imgui.h"
#include "imgui_internal.h"
#include "offsets.h" // Подключаем твой файл с оффсетами

// ============================================================================
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ НАСТРОЕК
// ============================================================================

// 1. Настройки UI и видимости
float g_MenuScale = 1.0f;
float g_LastAppliedScale = 1.0f;
bool g_HideFromScreenshots = false;

// 2. Настройки ESP
bool g_EspEnabled = false;
bool g_EspBox = true;
bool g_EspLine = false;
bool g_EspDistance = true;
bool g_EspHealth = true;

// 3. Настройки Aim
bool g_AimbotEnabled = false;
int g_AimType = 0; // 0 - Обычный Aim, 1 - Silent Aim
int g_SelectedAimTarget = 0; // 0 - Голова, 1 - Шея, 2 - Грудь
const char* g_AimTargets[] = { "Голова (Head)", "Шея (Neck)", "Тело (Chest)" };
float g_AimbotFov = 60.0f;
float g_AimbotSmooth = 5.0f;     // Скорость / плавность наводки
bool g_WallCheck = true;         // Не целить и не стрелять за стеной
bool g_AimOnShoot = false;       // Прицеливать только при стрельбе

// 4. Разное (Боевые функции и Защита)
bool g_NoRecoil = false;         // Антиотдача
bool g_OneHitKill = false;       // Убийство в одно касание
bool g_KillAura360 = false;      // Убивать врагов рядом, даже если не смотришь на них
bool g_AntiBanProtect = true;    // Антибан
bool g_BypassCrashes = true;     // Защита от крашей

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
    // Логика установки флага FLAG_SECURE для скрытия меню от скриншотов и записи
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

        // --------------------------------------------------------------------
        // 1. ESP
        // --------------------------------------------------------------------
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

        // --------------------------------------------------------------------
        // 2. AIM
        // --------------------------------------------------------------------
        if (ImGui::BeginTabItem("Aim")) {
            ImGui::Spacing();
            ImGui::Checkbox("Включить Aim", &g_AimbotEnabled);

            if (g_AimbotEnabled) {
                ImGui::Separator();
                
                const char* aimTypes[] = { "Memory Aim (Обычный)", "Silent Aim (Скрытый)" };
                ImGui::Combo("Тип Аима", &g_AimType, aimTypes, IM_ARRAYSIZE(aimTypes));
                
                ImGui::Combo("Цель", &g_SelectedAimTarget, g_AimTargets, IM_ARRAYSIZE(g_AimTargets));
                
                ImGui::SliderFloat("Радиус (FOV)", &g_AimbotFov, 10.0f, 180.0f, "%.1f deg");
                ImGui::SliderFloat("Плавность / Скорость наводки", &g_AimbotSmooth, 1.0f, 20.0f, "%.1f");

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Text("Дополнительно для Aim:");
                ImGui::Checkbox("Не целиться и не стрелять за стеной (WallCheck)", &g_WallCheck);
                ImGui::Checkbox("Прицеливать только при стрельбе (Aim on Shoot)", &g_AimOnShoot);

                if (g_AimType == 1) {
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), "[Silent Aim] Прицел не дергается, пули летят в цель!");
                }
            }
            ImGui::EndTabItem();
        }

        // --------------------------------------------------------------------
        // 3. РАЗНОЕ
        // --------------------------------------------------------------------
        if (ImGui::BeginTabItem("Разное")) {
            ImGui::Spacing();
            ImGui::Text("Модификации игры:");
            ImGui::Separator();

            ImGui::Checkbox("Антиотдача (No Recoil)", &g_NoRecoil);
            ImGui::Checkbox("Убийство в одно касание (One Hit Kill)", &g_OneHitKill);
            
            ImGui::Checkbox("Убивать тех, кто рядом (Kill Aura 360°)", &g_KillAura360);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Уничтожает противников вокруг вас, даже если вы смотрите в другую сторону!");
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Text("Безопасность:");
            ImGui::Checkbox("Антибан (Anti-Ban Guard)", &g_AntiBanProtect);
            ImGui::Checkbox("Защита от крашей", &g_BypassCrashes);

            ImGui::EndTabItem();
        }

        // --------------------------------------------------------------------
        // 4. НАСТРОЙКИ
        // --------------------------------------------------------------------
        if (ImGui::BeginTabItem("Настройки")) {
            ImGui::Spacing();
            ImGui::Text("Безопасность меню и видимость:");
            ImGui::Separator();

            if (ImGui::Checkbox("Скрывать от скриншотов и видео (FLAG_SECURE)", &g_HideFromScreenshots)) {
                SetWindowSecureFlag(env, context, g_HideFromScreenshots);
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Text("Масштаб меню:");

            if (ImGui::Button("Маленькое (0.7x)", ImVec2(120 * g_MenuScale, 30 * g_MenuScale))) {
                g_MenuScale = 0.70f;
                ApplyMenuScale(g_MenuScale);
            }
            ImGui::SameLine();
            if (ImGui::Button("Обычное (1.0x)", ImVec2(120 * g_MenuScale, 30 * g_MenuScale))) {
                g_MenuScale = 1.0f;
                ApplyMenuScale(g_MenuScale);
            }
            ImGui::SameLine();
            if (ImGui::Button("Большое (2.0x)", ImVec2(120 * g_MenuScale, 30 * g_MenuScale))) {
                g_MenuScale = 2.0f;
                ApplyMenuScale(g_MenuScale);
            }

            ImGui::SliderFloat("Точный масштаб", &g_MenuScale, 0.50f, 2.50f, "%.2fx");
            if (g_MenuScale != g_LastAppliedScale) {
                ApplyMenuScale(g_MenuScale);
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

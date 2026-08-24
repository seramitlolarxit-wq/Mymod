#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <dlfcn.h>
#include "imgui.h"
#include "Offsets.h"

#define LOG_TAG "StandoffCheat"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

// Структура настроек меню
struct CheatSettings {
    bool espBox = false;
    bool espHealth = false;
    bool chamsMap = false; 

    bool silentAimEnable = false;
    bool fovCircleEnable = true;
    float fovSize = 100.0f; 

    bool hitboxesResize = false;
    float hitboxScale = 1.5f; 
    bool noRecoil = false;
    bool antiAimSpin = false;   
    bool antiAimJump = false;   
    bool bunnyHop = false;
    float bhopSpeed = 1.0f;     
};

CheatSettings g_Cfg;
bool showMenu = true; 

// ==========================================
// ФУНКЦИИ ОБХОДА АНТИЧИТА И ВАЛИДАЦИИ
// ==========================================
void* hook_FoxInit(void* fox, void* validatorX, void* validatorY, void* resetFun) {
    LOGI("FoxInit hooked! Bypassing mouse validation...");
    return nullptr; 
}

void hook_FoxOnHit(void* fox, void* hitEventArgs) {
    return; // Блокируем проверки хитов античитом
}

bool hook_ValidateHit(void* hitController, void* shooter, void* victim) {
    return true; // Всегда легитимное попадание для Silent Aim
}

bool hook_ValidateElapsedMs(int16_t shooterElapsedMs) {
    return true; // Обход спидхака по времени
}

bool hook_ValidateShooter(void* shooter, int32_t shooterViewId, void* playerController, bool isGrenade) {
    return true;
}

bool hook_ValidateShooterByController(void* hitController, void* shooter, int32_t shooterPacketId, void* playerController) {
    return true;
}

bool hook_ValidateVector3(void* value) {
    return true;
}

bool hook_ValidateFloat(float value) {
    return true;
}

// Отрисовка ImGui меню
void RenderImGuiMenu() {
    if (!showMenu) return;

    ImGui::SetNextWindowSize(ImVec2(450, 320), ImGuiCond_FirstUseEver);
    ImGui::Begin("Standleo - Menu", &showMenu, ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginTabBar("CheatTabs")) {
        
        if (ImGui::BeginTabItem("ESP")) {
            ImGui::Checkbox("ESP Box", &g_Cfg.espBox);
            ImGui::Checkbox("ESP HP", &g_Cfg.espHealth);
            ImGui::Checkbox("Chams", &g_Cfg.chamsMap);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Silent Aim")) {
            ImGui::Checkbox("Включить Silent Aim", &g_Cfg.silentAimEnable);
            ImGui::Separator();
            ImGui::Checkbox("Круг FOV", &g_Cfg.fovCircleEnable);
            if (g_Cfg.fovCircleEnable) {
                ImGui::SliderFloat("Размер круга", &g_Cfg.fovSize, 30.0f, 300.0f, "%.1f");
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Разное")) {
            ImGui::Checkbox("Увеличение хитбоксов", &g_Cfg.hitboxesResize);
            if (g_Cfg.hitboxesResize) {
                ImGui::SliderFloat("Размер", &g_Cfg.hitboxScale, 1.0f, 3.0f, "%.1f x");
            }
            
            ImGui::Separator();
            ImGui::Checkbox("Анти-отдача", &g_Cfg.noRecoil);
            ImGui::Checkbox("Антиаим: Спин", &g_Cfg.antiAimSpin);
            ImGui::Checkbox("Баннихоп", &g_Cfg.bunnyHop);
            
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();

    if (g_Cfg.silentAimEnable && g_Cfg.fovCircleEnable) {
        ImVec2 center = ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
        ImGui::GetBackgroundDrawList()->AddCircle(center, g_Cfg.fovSize, IM_COL32(255, 0, 0, 200), 64, 1.5f);
    }
}

void* MainThread(void*) {
    LOGI("Cheat library loaded successfully!");

    uintptr_t libBase = 0;
    while (!libBase) {
        libBase = (uintptr_t)dlopen("libil2cpp.so", RTLD_NOLOAD);
        usleep(1000000);
    }
    LOGI("libil2cpp.so found at: %p", (void*)libBase);

    // Пример вызова хуков с использованием Offsets:
    // DobbyHook((void*)(libBase + Offsets::FoxInit), (void*)hook_FoxInit, nullptr);
    // DobbyHook((void*)(libBase + Offsets::FoxOnHit), (void*)hook_FoxOnHit, nullptr);
    // DobbyHook((void*)(libBase + Offsets::ValidateHit), (void*)hook_ValidateHit, nullptr);
    // DobbyHook((void*)(libBase + Offsets::ValidateElapsedMs), (void*)hook_ValidateElapsedMs, nullptr);
    // DobbyHook((void*)(libBase + Offsets::ValidateVector3), (void*)hook_ValidateVector3, nullptr);
    // DobbyHook((void*)(libBase + Offsets::ValidateFloat), (void*)hook_ValidateFloat, nullptr);

    return nullptr;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    pthread_t thread;
    pthread_create(&thread, nullptr, MainThread, nullptr);
    return JNI_VERSION_1_6;
}

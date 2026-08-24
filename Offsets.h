#pragma once
#include <cstdint>

namespace Offsets {
    // 1. Античит Fox & Валидация
    constexpr uintptr_t FoxInit = 33421256;          
    constexpr uintptr_t FoxOnHit = 87624;            
    constexpr uintptr_t ValidateHit = 39945976;      
    constexpr uintptr_t ValidateElapsedMs = 205860;  
    constexpr uintptr_t ValidateVector3 = 39973272;  
    constexpr uintptr_t ValidateFloat = 39973924;    

    // 2. Игрок и Здоровье
    constexpr uintptr_t SetHealth = 39647668;        
    constexpr uintptr_t GetHealth = 39649152;        
    constexpr uintptr_t SetUntouchable = 39954156;   
    constexpr uintptr_t ApplyDamage = 45071044;      

    // 3. Движение и Физика
    constexpr uintptr_t SetJumpSpeed = 39712424;          
    constexpr uintptr_t SetJumpSpeedMultiplier = 39712728; 
    constexpr uintptr_t TeleportTo = 203580;              

    // 4. Оружие и Стрельба
    constexpr uintptr_t WeaponRaycast = 40585412;    
    constexpr uintptr_t ApplyRecoil = 216636;        

    // 5. Радар и ESP
    constexpr uintptr_t RadarController_Set = 292008; 
    constexpr uintptr_t ShouldShowPlayer = 292260;    
}

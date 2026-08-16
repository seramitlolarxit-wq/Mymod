#ifndef OFFSETS_H
#define OFFSETS_H

#pragma once

// ─── Static Class Offsets (get_static) ────────────────────────────────
#define OFF_PLAYER_MANAGER_STATIC       0xAC5E190ULL   // PlayerManager (static)
#define OFF_PLAYER_MANAGER_ALT          132435632ULL   // Альтернативный PM static

// ─── il2cpp Internals (get_static chain) ──────────────────────────────
#define OFF_IL2CPP_CLASS_STATIC_FIELDS  0x90   // Il2CppClass → static_fields*
#define OFF_IL2CPP_OBJ_FIELDS           0x10   // Il2CppObject → fields data

// ─── PlayerManager (PM) offsets ───────────────────────────────────────
#define OFF_PM_LOCAL_PLAYER             0x70   // PM → LocalPlayer*
#define OFF_PM_PLAYER_LIST              0x28   // PM → PlayerList*

// ─── PlayerList (il2cpp List<T>) ──────────────────────────────────────
#define OFF_LIST_COUNT                  0x20   // List<T> → _size (int)
#define OFF_LIST_BUFFER                 0x18   // List<T> → _items (T**)
#define OFF_LIST_ENTRY_BASE             0x30   // buffer[x] base
#define OFF_LIST_ENTRY_STRIDE           0x18   // stride между элементами

// ─── Player ───────────────────────────────────────────────────────────
#define OFF_PLAYER_TEAM                 0x79   // Player → team (uint8_t)
#define OFF_PLAYER_MOVEMENT_CTRL        0x98   // Player → MovementController*
#define OFF_PLAYER_PHOTON_PTR           0x160  // Player → PhotonPlayer*
#define OFF_PLAYER_MAIN_CAMERA          0xE8   // Player → PlayerMainCamera*
#define OFF_PLAYER_VIEW_1               0x48   // Player → View1*
#define OFF_PLAYER_VIEW_2               0x50   // Player → View2*
#define OFF_PLAYER_WEAPON_ROOT          0x88   // Player → WeaponRootController*
#define OFF_PLAYER_AIM_ANIM_CTRL        0xA0   // Player → AimAnimController*
#define OFF_PLAYER_AIM_CONTROLLER       0x80   // Player → AimController*
#define OFF_PLAYER_OCCLUSION            0xB8   // Player → OcclusionController*

// ─── MovementController ───────────────────────────────────────────────
#define OFF_MC_TRANSFORM_DATA           0xB0   // MC → TransformData*
#define OFF_MC_TRAJECTORY               0xA8   // MC → TrajectoryPredictor*
#define OFF_MC_THRUST_DATA              0xB0   // MC → ThrustData*

// ─── TransformData (позиция) ──────────────────────────────────────────
#define OFF_TD_POSITION                 0x44   // TransformData → position (vec3)

// ─── Transform System (Unity) ─────────────────────────────────────────
#define OFF_TRANSFORM_NATIVE            0x10   // Transform → NativeTransform*
#define OFF_NATIVE_TRANSFORM_DATA       0x38   // NativeTransform → TransformData*
#define OFF_NATIVE_TRANSFORM_INDEX      0x40   // NativeTransform → index (int)
#define OFF_NATIVE_TRANSFORM_DIRECT     0x90   // NativeTransform → directPosition (vec3)
#define OFF_TRANSFORM_DATA_ARRAY        0x18   // TransformData → transformArray*
#define OFF_TRANSFORM_DATA_INDICES      0x20   // TransformData → indicesArray*

// ─── PhotonPlayer ─────────────────────────────────────────────────────
#define OFF_PHOTON_NAME                 0x20   // PhotonPlayer → name (System.String*)
#define OFF_PHOTON_PROPS_REG            0x38   // PhotonPlayer → PropertiesRegistry*

// ─── PropertiesRegistry (Photon) ──────────────────────────────────────
#define OFF_PROPS_COUNT                 0x20   // Registry → count (int)
#define OFF_PROPS_LIST                  0x18   // Registry → propertiesList*
#define OFF_PROPS_KEY_BASE              0x28   // entry → key pointer (base)
#define OFF_PROPS_VAL_BASE              0x30   // entry → value pointer (base)
#define OFF_PROPS_VALUE_DATA            0x10   // value → data (int)

// ─── OcclusionController ──────────────────────────────────────────────
#define OFF_OCCLUSION_CURRENT           0x34   // Occlusion → currentState (int)
#define OFF_OCCLUSION_NEXT              0x38   // Occlusion → nextState (int)

// ─── View → BipedMap (кости) ──────────────────────────────────────────
#define OFF_VIEW_BIPED_MAP              0x48   // View → BipedMap*

// ─── Bone Offsets (BipedMap → Transform*) ─────────────────────────────
#define OFF_BONE_HEAD_1                 0x28   // BipedMap → HeadBone1*
#define OFF_BONE_HEAD_2                 0x20   // BipedMap → HeadBone2*
#define OFF_BONE_CHEST_1                0x40   // BipedMap → ChestBone1*
#define OFF_BONE_CHEST_2                0x38   // BipedMap → ChestBone2*
#define OFF_BONE_CHEST_3                0x30   // BipedMap → ChestBone3*
#define OFF_BONE_CHEST_4                0x88   // BipedMap → ChestBone4*
#define OFF_BONE_FOOT_LEFT              0x98   // BipedMap → LeftFoot*
#define OFF_BONE_FOOT_RIGHT             0xB8   // BipedMap → RightFoot*
#define OFF_BONE_SPINE_1                0x88   // BipedMap → SpineBone1*
#define OFF_BONE_SPINE_2                0x90   // BipedMap → SpineBone2*
#define OFF_BONE_SPINE_3                0xB0   // BipedMap → SpineBone3*

// ─── BipedMap ─────────────────────────────────────────────────────────
#define OFF_BIPED_MAP_BONE_COUNT        22     // кол-во костей
#define OFF_BIPED_MAP_PTRS_BASE         0x20   // BipedMap → массив transform ptr
#define BONE_MATRIX_DATA                0x28   // NativeTransform → TransformData*
#define BONE_TRANSFORM_IDX              0x30   // NativeTransform → index
#define BONE_MATRIX_LIST                0x18   // TransformData → transformArray*
#define BONE_MATRIX_INDICES             0x20   // TransformData → indicesArray*

// ─── Camera ───────────────────────────────────────────────────────────
#define OFF_CAM_TRANSFORM               0x20   // PlayerMainCamera → CameraTransform*
#define OFF_CAM_TRANSFORM_MATRIX        0x10   // CameraTransform → CameraMatrix*
#define OFF_CAM_MATRIX_DATA             0xF0   // CameraMatrix → viewMatrix (matrix 4x4)
#define OFF_CAM_SETTINGS                0x28   // PlayerMainCamera → CameraSettings*
#define OFF_CAM_FOV                     0x38   // CameraSettings → fieldOfView (float)

// ─── MainCamera Chain ─────────────────────────────────────────────────
#define OFF_PLAYER_MAIN_CAM_DATA        0x40   // PlayerMainCamera → CameraData*
#define OFF_CAM_MOVEMENT_CTRL           0xA0   // CameraData → MovementController*
#define OFF_CAM_NATIVE                  0x10   // MovementController → NativeCamera*
#define OFF_NATIVE_CAM_ASPECT           0x4F0  // NativeCamera → aspectRatio (float)
#define OFF_NATIVE_CAM_FOV_FIELD        0x180  // NativeCamera → fieldOfView (float)

// ─── Sky Color (NativeCamera) ─────────────────────────────────────────
#define OFF_NATIVE_CAM_SKY_MODE         0x418  
#define OFF_NATIVE_CAM_SKY_COLOR_R      0x41C  
#define OFF_NATIVE_CAM_SKY_COLOR_G      0x420  
#define OFF_NATIVE_CAM_SKY_COLOR_B      0x424  
#define OFF_NATIVE_CAM_SKY_COLOR_A      0x428  

// ─── AimAnimController ────────────────────────────────────────────────
#define OFF_AAC_VIEWMODEL_OFFSET        0xE8   

// ─── AimController → AimingData ───────────────────────────────────────
#define OFF_AIM_CONTROLLER_DATA         0x90   // AimController → AimingData*
#define OFF_AIMDATA_PITCH               0x18   // AimingData → pitch (float)
#define OFF_AIMDATA_YAW                 0x1C   // AimingData → yaw (float)
#define OFF_AIMDATA_PITCH_YAW_VEC3      0x18   
#define OFF_AIMDATA_SECOND_VEC3         0x24   

// ─── WeaponRootController ─────────────────────────────────────────────
#define OFF_WRC_ACTIVE_WEAPON           0xA0   // WRC → WeaponController*

// ─── WeaponController ─────────────────────────────────────────────────
#define OFF_WC_FIRE_DURATION            0x108  
#define OFF_WC_AMMO_CURRENT             0x120  
#define OFF_WC_AMMO_MAX                 0x128  
#define OFF_WC_RECOIL_CTRL              0x160  // WC → RecoilController*
#define OFF_WC_RECOIL_MULT              0x240  // RecoilMultiplier (float)
#define OFF_WC_RECOIL_MULT2             0x244  // RecoilMultiplier2 (float)
#define OFF_WC_WEAPON_PROPS             0xA8   // WC → WeaponProperties*
#define OFF_WC_FIRE_BUTTON              0x148  

// ─── WeaponProperties ─────────────────────────────────────────────────
#define OFF_WP_WEAPON_ID                0x18   
#define OFF_WP_PENETRATION              0x264  // Prostrel / Wallshot

// ─── RecoilController ─────────────────────────────────────────────────
#define OFF_RC_RECOIL_0                 0x18
#define OFF_RC_RECOIL_1                 0x1C
#define OFF_RC_RECOIL_2                 0x20
#define OFF_RC_RECOIL_3                 0x24
#define OFF_RC_RECOIL_4                 0x28
#define OFF_RC_RECOIL_5                 0x2C

// ─── TrajectoryPredictor ──────────────────────────────────────────────
#define OFF_TP_JUMP_PARAMS              0x50   
#define OFF_TP_CROUCH_PARAMS            0x48   

// ─── JumpParams ───────────────────────────────────────────────────────
#define OFF_JP_JUMP_SPEED               0x10   // Bunnyhop
#define OFF_JP_JUMP_SPEED2              0x60   

// ─── CrouchParams ─────────────────────────────────────────────────────
#define OFF_CP_SPEED_MULT               0x10   
#define OFF_CP_SPEED_MULT2              0x14   

// ─── ThrustData ───────────────────────────────────────────────────────
#define OFF_TD_THRUST_VEC               0x68   

// ─── Constants ────────────────────────────────────────────────────────
#define AIMBOT_VERTICAL_FOV_DEG         70.0f
#define AIMBOT_PI                       3.14159265f
#define AIMBOT_RAD_TO_DEG               57.2957795f
#define PLAYER_HEIGHT                   1.67f

#endif // OFFSETS_H

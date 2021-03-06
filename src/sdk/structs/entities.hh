//
//  ruvi base
//

#pragma once

// includes
#include "../memory/memory.hh"
#include "../netvars/netvars.hh"
#include "../valve/iclientnetworkable.hh"
#include "../valve/iclientrenderable.hh"
#include "../vector/matrix3x4.hh"
#include "../vector/vector.hh"

struct weapon_t;

enum cs_team_id_t {
  NONE              = 0,
  SPECTATOR         = 1,
  TERRORIST         = 2,
  COUNTER_TERRORIST = 3
};

enum entity_flag_t {
  ON_GROUND             = (1 << 0),
  DUCKING               = (1 << 1),
  PARTIAL_GROUND        = (1 << 17),
  STEP_MOVEMENT         = (1 << 21),
  UNBLOCKABLE_BY_PLAYER = (1 << 30)
};

enum item_definition_index_t {
  INVALID     = -1,
  WEAPON_NONE = 0,
  WEAPON_DEAGLE,
  WEAPON_ELITE,
  WEAPON_FIVESEVEN,
  WEAPON_GLOCK,
  WEAPON_AK47 = 7,
  WEAPON_AUG,
  WEAPON_AWP,
  WEAPON_FAMAS,
  WEAPON_G3SG1,
  WEAPON_GALILAR = 13,
  WEAPON_M249,
  WEAPON_M4A1 = 16,
  WEAPON_MAC10,
  WEAPON_P90 = 19,
  WEAPON_MP5 = 23,
  WEAPON_UMP45,
  WEAPON_XM1014,
  WEAPON_BIZON,
  WEAPON_MAG7,
  WEAPON_NEGEV,
  WEAPON_SAWEDOFF,
  WEAPON_TEC9,
  WEAPON_TASER,
  WEAPON_HKP2000,
  WEAPON_MP7,
  WEAPON_MP9,
  WEAPON_NOVA,
  WEAPON_P250,
  WEAPON_SHIELD,
  WEAPON_SCAR20,
  WEAPON_SG556,
  WEAPON_SSG08,
  KNIFE_GG,
  KNIFE_CT,
  WEAPON_FLASHBANG,
  WEAPON_HEGRENADE,
  WEAPON_SMOKEGRENADE,
  WEAPON_MOLOTOV,
  WEAPON_DECOY,
  WEAPON_INCGRENADE,
  WEAPON_C4,
  WEAPON_HEALTHSHOT = 57,
  KNIFE_T           = 59,
  WEAPON_M4A1_SILENCER,
  WEAPON_USP_SILENCER,
  WEAPON_CZ75A = 63,
  WEAPON_REVOLVER,
  WEAPON_TAGRENADE = 68,
  WEAPON_FISTS,
  WEAPON_BREACHCHARGE,
  WEAPON_TABLET = 72,
  WEAPON_MELEE  = 74,
  WEAPON_AXE,
  WEAPON_HAMMER,
  WEAPON_SPANNER = 78,
  KNIFE_GHOST    = 80,
  WEAPON_FIREBOMB,
  WEAPON_DIVERSION,
  WEAPON_FRAG_GRENADE,
  WEAPON_SNOWBALL,
  WEAPON_BUMPMINE,
  KNIFE_BAYONET = 500,
  KNIFE_FLIP    = 505,
  KNIFE_GUT,
  KNIFE_KARAMBIT,
  KNIFE_M9_BAYONET,
  KNIFE_TACTICAL,
  KNIFE_FALCHION = 512,
  KNIFE_BOWIE    = 514,
  KNIFE_BUTTERFLY,
  KNIFE_PUSH,
  KNIFE_URSUS = 519,
  KNIFE_NAVAJA,
  KNIFE_STILETTO = 522,
  KNIFE_TALON,
  GLOVE_STUDDED_BLOODHOUND = 5027,
  GLOVE_T_SIDE             = 5028,
  GLOVE_CT_SIDE            = 5029,
  GLOVE_SPORTY             = 5030,
  GLOVE_SLICK              = 5031,
  GLOVE_LEATHER_WRAP       = 5032,
  GLOVE_MOTORCYCLE         = 5033,
  GLOVE_SPECIALIST         = 5034,
  GLOVE_HYDRA              = 5035,
  WEAPON_MAX
};

enum class_id_t {

  AK_47                    = 1,
  PLAYER                   = 40,
  ENV_TONEMAP_CONTROLLER   = 69,
  KNIFE                    = 107,
  KNIFE_GOLDEN             = 108,
  SMOKE_GRENADE_PROJECTILE = 156

};

enum observer_mode_t {
  MODE_NONE = 0,  // not in spectator mode
  MODE_DEATHCAM,  // special mode for death cam animation
  MODE_FREEZECAM, // zooms to a target, and freeze-frames on them
  MODE_FIXED,     // view from a fixed camera position
  MODE_IN_EYE,    // follow a player in first person view
  MODE_CHASE,     // follow a player in third person view
  MODE_POI,       // PASSTIME point of interest - game objective, big fight,
            // anything interesting; added in the middle of the enum due to
            // tons of hard-coded "<ROAMING" enum compares
  MODE_ROAMING, // free roaming
  OBSERVER_MODES,
};

struct smoke_grenade_projectile_t {

  NETVAR_PTR(bool, m_bDidSmokeEffect, "DT_SmokeGrenadeProjectile",
             "m_bDidSmokeEffect");
  NETVAR_PTR(int, m_nSmokeEffectTickBegin, "DT_SmokeGrenadeProjectile",
             "m_nSmokeEffectTickBegin");
};

struct tonemap_controller_t {

  NETVAR_PTR(bool, m_bUseCustomAutoExposureMin, "DT_EnvTonemapController",
             "m_bUseCustomAutoExposureMin");
  NETVAR_PTR(bool, m_bUseCustomAutoExposureMax, "DT_EnvTonemapController",
             "m_bUseCustomAutoExposureMax");
  NETVAR_PTR(float, m_flCustomAutoExposureMin, "DT_EnvTonemapController",
             "m_flCustomAutoExposureMin");
  NETVAR_PTR(float, m_flCustomAutoExposureMax, "DT_EnvTonemapController",
             "m_flCustomAutoExposureMax");
};

struct entity_t : public i_client_networkable, public i_client_renderable {

  inline vector3d get_bone_position(int i) {

    matrix3x4_t matrix[128];

    if (setup_bones(matrix, 128, 0x100, 0))
      return vector3d(matrix[i][0][3], matrix[i][1][3], matrix[i][2][3]);

    return {};
  }

  inline vector3d get_eye_position() {
    return m_vecOrigin() + m_vecViewOffset();
  }

  inline vector3d get_abs_origin() {
    return memory::vfunc<12, const vector3d &>(this);
  }

  inline void set_model_index(int index) {
    return memory::vfunc<111, void>(this, index);
  }

  inline player_info_t get_entity_info() {
    static player_info_t temp_info;
    csgo::engine_client->get_player_info(IClientNetworkable()->get_index(),
                                         &temp_info);
    return temp_info;
  }

  //
  // offsets goes here
  //
  OFFSET_PTR(i_client_networkable, IClientNetworkable, 0x10);
  OFFSET(qangle, m_angEyeAngles, 0x8 + 0x4);
  OFFSET(int, m_lastOcclusionCheck, 0xA30);
  OFFSET(int, m_occlusionFlags, 0xA28);
  OFFSET(unsigned int, m_flLastBoneSetupTime, 0x2924);
  OFFSET(unsigned int, m_iMostRecentModelBoneCounter, 0x2690);

  //
  // netvars goes here
  //
  NETVAR(int, m_iHealth, "DT_CSPlayer", "m_iHealth");
  NETVAR(bool, m_bGunGameImmunity, "DT_CSPlayer", "m_bGunGameImmunity");
  NETVAR(class_id_t, m_iTeamNum, "DT_CSPlayer", "m_iTeamNum");
  NETVAR(entity_flag_t, m_fFlags, "DT_CSPlayer", "m_fFlags");
  NETVAR(bool, m_bInBombZone, "DT_CSPlayer", "m_bInBombZone");
  NETVAR(vector3d, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin");
  NETVAR(float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime");
  NETVAR(vector3d, m_vecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]");
  NETVAR(vector3d, m_vecMins, "DT_BaseEntity", "m_vecMins");
  NETVAR(vector3d, m_vecMaxs, "DT_BaseEntity", "m_vecMaxs");
  NETVAR(float, m_flFlashDuration, "DT_CSPlayer", "m_flFlashDuration");
  NETVAR(bool, m_bIsScoped, "DT_CSPlayer", "m_bIsScoped");
  NETVAR(int, m_aimPunchAngle, "DT_CSPlayer", "m_aimPunchAngle");
  NETVAR_PTR(observer_mode_t, m_iObserverMode, "DT_BasePlayer",
             "m_iObserverMode");
  NETVAR_PTR(bool, m_bSpotted, "DT_BaseEntity", "m_bSpotted");
  NETVAR_PTR(float, m_flHealthShotBoostExpirationTime, "DT_CSPlayer",
             "m_flHealthShotBoostExpirationTime");
  NETVAR_PTR(float, m_flFlashMaxAlpha, "DT_CSPlayer", "m_flFlashMaxAlpha");
  NETVAR_PTR(weapon_t, m_hActiveWeapon, "DT_BaseCombatCharacter",
             "m_hActiveWeapon");
};

struct weapon_t : public entity_t {

  OFFSET(item_definition_index_t, m_iItemDefinitionIndex,
         0x37B2); // hardcoded offset until the netvar manager is fixed.

  NETVAR(int, m_iClip1, "DT_BaseCombatWeapon", "m_iClip1");
};
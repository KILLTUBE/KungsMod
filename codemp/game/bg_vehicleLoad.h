#pragma once

#include "qcommon/q_shared.h"
#include "bg_public.h"
#include "bg_vehicles.h"
#include "bg_weapons.h"

#include "g_local.h"
#include "cgame/cg_local.h"
#include "cgame/cg_tempwrappers.h"
#include "ui/ui_local.h"

// These buffers are filled in with the same contents and then just read from in
// a few places. We only need one copy on Xbox.

#define MAX_VEH_WEAPON_DATA_SIZE 0x40000 // 0x4000
#define MAX_VEHICLE_DATA_SIZE 0x100000 // 0x10000

typedef enum {
	VF_IGNORE,
	VF_INT,
	VF_FLOAT,
	VF_STRING,	// string on disk, pointer in memory
	VF_VECTOR,
	VF_BOOL,
	VF_VEHTYPE,
	VF_ANIM,
	VF_WEAPON,	// take string, resolve into index into VehWeaponParms
	VF_MODEL,	// take the string, get the G_ModelIndex
	VF_MODEL_CLIENT,	// (cgame only) take the string, get the G_ModelIndex
	VF_EFFECT,	// take the string, get the G_EffectIndex
	VF_EFFECT_CLIENT,	// (cgame only) take the string, get the index
	VF_SHADER,	// (cgame only) take the string, call R_RegisterShader
	VF_SHADER_NOMIP,// (cgame only) take the string, call R_RegisterShaderNoMip
	VF_SOUND,	// take the string, get the G_SoundIndex
	VF_SOUND_CLIENT	// (cgame only) take the string, get the index
} vehFieldType_t;

typedef struct vehField_s {
	const char	*name;
	size_t		ofs;
	vehFieldType_t	type;
} vehField_t;

EXTERNC vehField_t vehicleFields[];
EXTERNC stringID_table_t VehicleTable[VH_NUM_VEHICLES+1];
EXTERNC vehField_t vehWeaponFields[];
EXTERNC int numVehicles;
EXTERNC vehicleInfo_t g_vehicleInfo[MAX_VEHICLES];
EXTERNC int numVehicleWeapons;
EXTERNC vehWeaponInfo_t g_vehWeaponInfo[MAX_VEH_WEAPONS];
EXTERNC char VehicleParms[MAX_VEHICLE_DATA_SIZE];
EXTERNC char VehWeaponParms[MAX_VEH_WEAPON_DATA_SIZE];
EXTERNC stringID_table_t animTable[MAX_ANIMATIONS+1];

CCALL void AttachRidersGeneric(Vehicle_t *pVeh);
CCALL int BG_GetTime(void);
CCALL void BG_GetVehicleSkinName(char *skinname,int len);
CCALL void BG_GetVehicleModelName(char *modelName,const char *vehicleName,size_t len);
CCALL int BG_VehicleGetIndex(const char *vehicleName);
CCALL void BG_VehWeaponLoadParms(void);
CCALL int VEH_VehicleIndexForName(const char *vehicleName);
CCALL int VEH_LoadVehicle(const char *vehicleName);
CCALL void BG_VehicleClampData(vehicleInfo_t *vehicle);
CCALL void BG_VehicleSetDefaults(vehicleInfo_t *vehicle);
CCALL void BG_SetSharedVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void G_SetSharedVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL int VEH_VehWeaponIndexForName(const char *vehWeaponName);
CCALL int VEH_LoadVehWeapon(const char *vehWeaponName);
CCALL int vfieldcmp(const void *a,const void *b);
CCALL void BG_VehicleLoadParms(void);
CCALL void BG_VehicleLoadParms(void);
CCALL void G_SetFighterVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void G_SetWalkerVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void G_SetSpeederVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void G_SetAnimalVehicleFunctions(vehicleInfo_t *pVehInfo);
CCALL void BG_ClearVehicleParseParms(void);


#include "ui_tempwrappers.h"
#include "game/g_local.h"
#include "ui/ui_local.h"

EXTERNC level_locals_t	level;
EXTERNC cg_t			cg;

level_locals_t	level;
cg_t			cg;


CCALL void Com_Printf( const char *fmt, ... ) {
	// todo
	//Com_Printf
	//__debugbreak();
}

CCALL void Com_Error(int code,  const char *fmt, ... ) {
		// todo
	//__debugbreak();
}

CCALL cvar_t *Cvar_Get( const char *var_name, const char *var_value, uint32_t flags, const char *var_desc ) {
	//__debugbreak();
	//return NULL;
	return Cvar_Get(var_name, var_value, flags, var_desc);
}

//NORETURN void QDECL CG_Error( int level, const char *error, ... ) {
//	va_list argptr;
//	char text[1024] = {0};
//
//	va_start( argptr, error );
//	Q_vsnprintf( text, sizeof( text ), error, argptr );
//	va_end( argptr );
//
//	trap_Error( text );
//}
//
//void QDECL CG_Printf( const char *msg, ... ) {
//	va_list argptr;
//	char text[4096] = {0};
//	int ret;
//
//	va_start( argptr, msg );
//	ret = Q_vsnprintf( text, sizeof( text ), msg, argptr );
//	va_end( argptr );
//
//	if ( ret == -1 )
//		trap_Print( "CG_Printf: overflow of 4096 bytes buffer\n" );
//	else
//		trap_Print( text );
//}
//


CCALL sfxHandle_t		S_RegisterSound						( const char *sample ) {
	//return S_RegisterSound(sample);
	__debugbreak();
	return 0;
}


CCALL qhandle_t		R_RegisterFont						( const char *fontName ) {
	//return R_RegisterFont(fontName);
		__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterModel						( const char *name ) {
	//return R_RegisterModel(name);
		__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterShader					( const char *name ) {
	//return R_RegisterShader(name);
	__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterShaderNoMip				( const char *name ) {
	return R_RegisterShaderNoMip(name);
	__debugbreak();
	return 0;
}

CCALL qhandle_t		R_RegisterSkin						( const char *name ) {
	//return R_RegisterSkin(name);
	__debugbreak();
	return 0;
}

CCALL int				FX_RegisterEffect					( const char *file ) {
	//return FX_RegisterEffect(file);
	__debugbreak();
	return 0;
}
/*
CCALL qboolean isGame() {
	return (qboolean)(0);
}
CCALL qboolean isCGame() {
	return (qboolean)(0);
}
CCALL qboolean isUI() {
	return (qboolean)(1);
}
*/
CCALL int	FS_Read	( void *buffer, int len, fileHandle_t f ) {
	return FS_Read(buffer, len, f);
	__debugbreak();
	return 0;
}

CCALL void FS_FCloseFile( fileHandle_t f ) {
	FS_FCloseFile(f);
	//__debugbreak();
	return;
}

CCALL int		FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode ) {
	return FS_FOpenFileByMode(qpath, f, mode);
	//return trap->FS_FOpenFileByMod
		__debugbreak();
	return 0;
}


CCALL void G_AllocateVehicleObject(Vehicle_t **pVeh) {
	__debugbreak();
}


CCALL int	FS_GetFileList( const char *path, const char *extension, char *listbuf, int bufsize ) {
	return FS_GetFileList(path, extension, listbuf, bufsize);
	
	__debugbreak();
	return 0;
}



CCALL void Vehicle_SetAnim(gentity_t *ent,int setAnimParts,int anim,int setAnimFlags, int iBlend) {
}
CCALL void G_Knockdown( gentity_t *self, gentity_t *attacker, const vec3_t pushDir, float strength, qboolean breakSaberLock ) {
}
CCALL void G_VehicleTrace( trace_t *results, const vec3_t start, const vec3_t tMins, const vec3_t tMaxs, const vec3_t end, int passEntityNum, int contentmask ) {
}

CCALL int G_SoundIndex( const char *name ) {
	__debugbreak();
	return 0;
}


CCALL qhandle_t SV_R_RegisterSkin( const char *name ) {
	__debugbreak();
	return 0;
}

CCALL void G_SetAnimalVehicleFunctions( vehicleInfo_t *pVehInfo ) {
	__debugbreak();
}
CCALL void G_SetSpeederVehicleFunctions( vehicleInfo_t *pVehInfo ) {
	__debugbreak();
}
CCALL void G_SetWalkerVehicleFunctions( vehicleInfo_t *pVehInfo ) {
	__debugbreak();
}
CCALL void G_SetFighterVehicleFunctions( vehicleInfo_t *pVehInfo ) {
	__debugbreak();
}

CCALL int G_ModelIndex( const char *name ) {
	__debugbreak();
	return 0;
}

CCALL int G_EffectIndex( const char *name ) {
	__debugbreak();
	return 0;
}

CCALL void G_SetSharedVehicleFunctions( vehicleInfo_t *pVehInfo ) {
	__debugbreak();
}



cvar_t *bg_showevents = NULL;
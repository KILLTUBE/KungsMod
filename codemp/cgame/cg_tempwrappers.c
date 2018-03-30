#include "cg_tempwrappers.h"


CCALL void Com_Printf( const char *fmt, ... ) {
	__debugbreak();
}

CCALL void Com_Error(int code,  const char *fmt, ... ) {
	__debugbreak();
}

CCALL cvar_t *Cvar_Get( const char *var_name, const char *var_value, uint32_t flags, const char *var_desc ) {
	return trap->GetRealCvar(var_name, var_value, flags, var_desc);
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
	return trap->S_RegisterSound(sample);
}


CCALL qhandle_t		R_RegisterFont						( const char *fontName ) {
	return trap->R_RegisterFont(fontName);
}

CCALL qhandle_t		R_RegisterModel						( const char *name ) {
	return trap->R_RegisterModel(name);
}

CCALL qhandle_t		R_RegisterShader					( const char *name ) {
	return trap->R_RegisterShader(name);
}

CCALL qhandle_t		R_RegisterShaderNoMip				( const char *name ) {
	return trap->R_RegisterShaderNoMip(name);
}

CCALL qhandle_t		R_RegisterSkin						( const char *name ) {
	return trap->R_RegisterSkin(name);
}

CCALL int				FX_RegisterEffect					( const char *file ) {
	return trap->FX_RegisterEffect(file);
}

CCALL qboolean isGame() {
	return (qboolean)(0);
}
CCALL qboolean isCGame() {
	return (qboolean)(1);
}
CCALL qboolean isUI() {
	return (qboolean)(0);
}

CCALL int	FS_Read	( void *buffer, int len, fileHandle_t f ) {
	return trap->FS_Read(buffer, len, f);
}

CCALL void FS_FCloseFile( fileHandle_t f ) {
	trap->FS_Close(f);
}

CCALL int		FS_FOpenFileByMode( const char *qpath, fileHandle_t *f, fsMode_t mode ) {
	return trap->FS_Open(qpath, f, mode);
	__debugbreak(); // shouldnt be called?
	//return trap->FS_FOpenFileByMod
}


gentity_t g_entities[1024];
CCALL void G_AllocateVehicleObject(Vehicle_t **pVeh) {

}

CCALL void WP_GetVehicleCamPos( gentity_t *ent, gentity_t *pilot, vec3_t camPos ) {
	__debugbreak();
}

CCALL void NPC_SetAnim(gentity_t *ent, int setAnimParts, int anim, int setAnimFlags) {
	__debugbreak();
}

CCALL int	FS_GetFileList( const char *path, const char *extension, char *listbuf, int bufsize ) {
	return trap->FS_GetFileList(path, extension, listbuf, bufsize);
}


CCALL qhandle_t SV_RE_RegisterSkin( const char *name ) {
	__debugbreak();
	return 0;
}

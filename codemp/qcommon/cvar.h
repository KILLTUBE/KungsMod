#pragma once

#include "../qcommon/qcommon.h"

#define	MAX_CVARS	8192
#define FILE_HASH_SIZE		512

EXTERNC int cvar_numIndexes;
EXTERNC cvar_t cvar_indexes[MAX_CVARS];
EXTERNC uint32_t cvar_modifiedFlags;
EXTERNC cvar_t *cvar_cheats;
EXTERNC cvar_t *cvar_vars;

CCALL void Cvar_Defrag(void);
CCALL void Cvar_Init(void);
CCALL void Cvar_CompleteCvarName(char *args,int argNum);
CCALL void Cvar_Update(cvar_t *vmCvar);
CCALL void Cvar_Register(cvar_t *vmCvar,const char *varName,const char *defaultValue,uint32_t flags);
CCALL void Cvar_CheckRange(cvar_t *var,float min,float max,qboolean integral);
CCALL void Cvar_InfoStringBuffer(int bit,char *buff,int buffsize);
CCALL char *Cvar_InfoString_Big(int bit);
CCALL char *Cvar_InfoString(int bit);
CCALL void Cvar_Restart_f(void);
CCALL void Cvar_Restart(qboolean unsetVM);
CCALL void Cvar_UnsetUserCreated_f(void);
CCALL void Cvar_Unset_f(void);
CCALL cvar_t *Cvar_Unset(cvar_t *cv);
CCALL void Cvar_ListUserCreated_f(void);
CCALL void Cvar_ListModified_f(void);
CCALL void Cvar_List_f(void);
CCALL void Cvar_WriteVariables(fileHandle_t f);
CCALL void Cvar_Reset_f(void);
CCALL void Cvar_Math_f(void);
CCALL void Cvar_Set_f(void);
CCALL void Cvar_Toggle_f(void);
CCALL void Cvar_Print_f(void);
CCALL qboolean Cvar_Command(void);
CCALL void Cvar_SetCheatState(void);
CCALL void Cvar_ForceReset(const char *var_name);
CCALL void Cvar_Reset(const char *var_name);
CCALL void Cvar_VM_SetValue(const char *var_name,float value,vmSlots_t vmslot);
CCALL void Cvar_User_SetValue(const char *var_name,float value);
CCALL cvar_t *Cvar_SetValue(const char *var_name,float value);
CCALL void Cvar_VM_Set(const char *var_name,const char *value,vmSlots_t vmslot);
CCALL void Cvar_Server_Set(const char *var_name,const char *value);
CCALL cvar_t *Cvar_User_Set(const char *var_name,const char *value);
CCALL cvar_t *Cvar_SetSafe(const char *var_name,const char *value);
CCALL cvar_t *Cvar_Set(const char *var_name,const char *value);
CCALL void Cvar_Print(cvar_t *v);
CCALL cvar_t *Cvar_Set2(const char *var_name,const char *value,uint32_t defaultFlags,qboolean force);
CCALL cvar_t *Cvar_Get(const char *var_name,const char *var_value,uint32_t flags,const char *var_desc);
CCALL void Cvar_CommandCompletion(callbackFunc_t callback);
CCALL uint32_t Cvar_Flags(const char *var_name);
CCALL char *Cvar_DescriptionString(const char *var_name);
CCALL void Cvar_VariableStringBuffer(const char *var_name,char *buffer,int bufsize);
CCALL char *Cvar_VariableString(const char *var_name);
CCALL int Cvar_VariableIntegerValue(const char *var_name);
CCALL float Cvar_VariableValue(const char *var_name);

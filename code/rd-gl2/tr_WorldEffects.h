#ifdef __JKA_WEATHER__
#pragma once

void R_InitWorldEffects(void);
void R_ShutdownWorldEffects(void);
void RB_RenderWorldEffects(void);

void R_WorldEffectCommand(const char *command);
void R_WorldEffect_f(void);

bool R_GetWindVector(vec3_t windVector);
bool R_GetWindSpeed(float &windSpeed);

bool R_IsOutside(vec3_t pos);
float R_IsOutsideCausingPain(vec3_t pos);

float R_GetChanceOfSaberFizz();
bool R_IsShaking(vec3_t pos);

bool R_IsRaining();
//bool R_IsSnowing();
bool R_IsPuffing();
void R_AddWeatherZone(vec3_t mins, vec3_t maxs);
#endif //__JKA_WEATHER__

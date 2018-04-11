#include "g_local.h"
#include "qcommon/q_shared.h"

#define START_DIS 15

CCALL void SP_misc_turret(gentity_t *base);
CCALL void turret_base_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void turret_base_think(gentity_t *self);
CCALL void turret_head_think(gentity_t *self);
CCALL void bottom_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void auto_turret_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void TurretBasePain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void TurretPain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void ObjectDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL qboolean turret_base_spawn_top(gentity_t *base);
CCALL qboolean turret_base_spawn_top(gentity_t *base);
CCALL void G_SetEnemy(gentity_t *self,gentity_t *enemy);

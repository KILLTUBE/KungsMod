#include "g_local.h"
#include "ghoul2/G2.h"
#include "qcommon/q_shared.h"

#define SPF_TURRETG2_CANRESPAWN	4
#define SPF_TURRETG2_TURBO		8
#define SPF_TURRETG2_LEAD_ENEMY	16
#define SPF_SHOWONRADAR			32

#define	ARM_ANGLE_RANGE		60
#define	HEAD_ANGLE_RANGE	90

#define name "models/map_objects/imp_mine/turret_canon.glm"
#define name2 "models/map_objects/imp_mine/turret_damage.md3"
#define name3 "models/map_objects/wedge/laser_cannon_model.glm"

#define START_DIS 15

CCALL void SP_misc_turretG2(gentity_t *base);
CCALL void turretG2_base_think(gentity_t *self);
CCALL void turretG2_head_think(gentity_t *self);
CCALL void turretG2_respawn(gentity_t *self);
CCALL void WP_FireTurboLaserMissile(gentity_t *ent,vec3_t start,vec3_t dir);
CCALL void TurboLaser_SetBoneAnim(gentity_t *eweb,int startFrame,int endFrame);
CCALL void turretG2_die(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void TurretG2Pain(gentity_t *self,gentity_t *attacker,int damage);
CCALL void turretG2_set_models(gentity_t *self,qboolean dying);
CCALL void G2Tur_SetBoneAngles(gentity_t *ent,char *bone,vec3_t angles);
CCALL void turretG2_base_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void turretG2_base_use(gentity_t *self,gentity_t *other,gentity_t *activator);
CCALL void ObjectDie(gentity_t *self,gentity_t *inflictor,gentity_t *attacker,int damage,int meansOfDeath);
CCALL void finish_spawning_turretG2(gentity_t *base);
CCALL void finish_spawning_turretG2(gentity_t *base);
CCALL void G_SetEnemy(gentity_t *self,gentity_t *enemy);

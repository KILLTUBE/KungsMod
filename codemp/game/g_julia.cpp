#include "../game/g_local.h"
#include "../imgui_docks/dock_console.h"
//#include <kung/duktape/dukdebugheaders.h>
//#include "include_math.h"
#include <server/server.h>
// poly fills



// spawn entity and return the ID
CCALL int jl_g_spawn() {
	gentity_t *grenade = G_Spawn();
	return (int)(grenade - g_entities);
}

/*
	I wanna generate an interface automatically, which exposes all variables to julia.. so Julia builds correspondending code at startup
	but atm starting slowly... 
*/

CCALL void *jl_g_entities() { return g_entities; }
CCALL int jl_g_entities_sizeof() { return sizeof(gentity_t); }

CCALL void *jl_clients() { return svs.clients; }
CCALL int jl_clients_sizeof() { return sizeof(client_t); }

CCALL void *jl_cg_entities() { return cg_entities; }
CCALL int jl_cg_entities_sizeof() { return sizeof(centity_t); }

typedef struct vec3 {
	float x;
	float y;
	float z;
} vek3_t;
int moveto(gentity_t *ent, vek3_t *to, float durationSeconds);

CCALL int jl_entity_moveto(int id, vek3_t *to, float durationSeconds) {
	//printf("id=%d to=%d durationSeconds=%f\n", id, to, durationSeconds);
	//printf("vec: %f %f %f\n", to[0], to[1], to[2]);
	//return 123;
	return moveto(g_entities + id, to, durationSeconds);
}

CCALL void jl_player_set_velocity(int id, vek3_t *pos) {
	gentity_t *ent = g_entities + id;
	memcpy(ent->client->ps.velocity, pos, sizeof(vek3_t));
}

CCALL vec3_t *jl_player_get_velocity(int id) {
	gentity_t *ent = g_entities + id;
	return &ent->client->ps.velocity;
}

// From ET:Legacy, seems to not be in q3
/**
 * @brief G_SetAngle
 * @param[out] ent
 * @param[in] angle
 */
void G_SetAngle(gentity_t *ent, vec3_t angle)
{
	VectorCopy(angle, ent->s.apos.trBase);
	ent->s.apos.trType     = TR_STATIONARY;
	ent->s.apos.trTime     = 0;
	ent->s.apos.trDuration = 0;
	VectorClear(ent->s.apos.trDelta);

	VectorCopy(angle, ent->r.currentAngles);
}

CCALL void jl_player_set_viewangles(int id, float *pos) {
	gentity_t *ent = g_entities + id;
	//memcpy(ent->client->ps.viewangles, pos, sizeof(float) * 3);
	//G_SetAngle(ent, pos); // for normal entities
	SetClientViewAngle(ent, pos); // for players
}

CCALL vec3_t *jl_player_get_viewangles(int id) {
	gentity_t *ent = g_entities + id;
	return &ent->client->ps.viewangles;
}

CCALL void jl_entity_set_angles(int id, float *angles) {
	gentity_t *ent = g_entities + id;
	G_SetAngle(ent, angles);
	SV_LinkEntity((sharedEntity_t *) ent);
	
}
CCALL vec3_t *jl_entity_get_angles(int id) {
	gentity_t *ent = g_entities + id;
	return &ent->r.currentAngles;
}

CCALL void jl_entity_set_pos(int id, float *pos) {
	// can prob be optimized with & or so
	//if (id <= 0 || id >= 1024) {
	//	printf("jl_entity_set_pos wtf u doing, id is out of range, id=%d\n", id);
	//	return;
	//}
	gentity_t *ent = g_entities + id;

	SV_UnlinkEntity ((sharedEntity_t *)ent);

	if(ent->client)
	{
		// as in icarus Q3_SetOrigin, in Q3 G_SetOrigin works, but not in OpenJK
		VectorCopy(pos, ent->client->ps.origin);
		VectorCopy(pos, ent->r.currentOrigin);
		ent->client->ps.eFlags ^= EF_TELEPORT_BIT;
	} else {
		G_SetOrigin(ent, pos);
	}
	SV_LinkEntity((sharedEntity_t *) ent);
}

CCALL int jl_player_viewheight(int playerid) {
	return g_entities[playerid].client->ps.viewheight;
}
#include "../ghoul2/G2.h"


CCALL void jl_ghoul(gentity_t *ent) {
	char name1[200] = "models/players/kyle/modelmp.glm";
	//char name1[200] = "models/players/jedi_zf/model.glm";
	SV_G2API_InitGhoul2Model(&ent->ghoul2, name1, G_ModelIndex( name1 ), 0, 0, 0, 0);
	SV_G2API_SetBoneAnim(ent->ghoul2, 0, "model_root", 0, 12, BONE_ANIM_OVERRIDE_LOOP, 1.0f, level.time, -1, -1);
	//ent->s.radius = 150;
//	VectorSet (ent->r.mins, -16, -16, -16);
//	VectorSet (ent->r.maxs, 16, 16, 16);
	SV_LinkEntity ((sharedEntity_t *)ent);

	G_SetOrigin( ent, ent->s.origin );
	VectorCopy( ent->s.angles, ent->s.apos.trBase );
}

CCALL void jl_ghoul_cg(centity_t *ent) {
	char name1[200] = "models/players/kyle/modelmp.glm";
	//char name1[200] = "models/players/jedi_zf/model.glm";	
	SV_G2API_InitGhoul2Model(&ent->ghoul2, name1, G_ModelIndex( name1 ), 0, 0, 0, 0);
	SV_G2API_SetBoneAnim(ent->ghoul2, 0, "model_root", 0, 12, BONE_ANIM_OVERRIDE_LOOP, 1.0f, level.time, -1, -1);
	//ent->s.radius = 150;
//	VectorSet (ent->r.mins, -16, -16, -16);
//	VectorSet (ent->r.maxs, 16, 16, 16);
	SV_LinkEntity ((sharedEntity_t *)ent);

	//G_SetOrigin( ent, ent->s.origin );
	//VectorCopy( ent->s.angles, ent->s.apos.trBase );
}

CCALL void *cgentity_ghoul2(centity_t *ent) {
	return &ent->ghoul2;
}
CCALL void *gentity_ghoul2(gentity_t *ent) {
	return &ent->ghoul2;
}

CCALL struct vec3 jl_entity_get_pos(int id, float *pos) {
	struct vec3 ret;
	gentity_t *ent = g_entities + id;
	//G_Printf("Got id: %d ent->client=%d\n", id, ent->client);
	if (ent->client == NULL) {
		VectorCopy(ent->r.currentOrigin, (float *)&ret);
	} else {
		VectorCopy(ent->client->ps.origin,  (float *)&ret);
	}
	return ret;
}

CCALL struct vec3 jl_player_forward(int playerid) {
	gentity_t *ent = g_entities + playerid;
	struct vec3 buf;
	AngleVectors(ent->client->ps.viewangles, (float *)&buf, NULL, NULL);
	return buf;
}

CCALL struct vec3 *js_player_forward(int playerid) {
	gentity_t *ent = g_entities + playerid;
	static struct vec3 buf; // so we can just read the pointer address
	AngleVectors(ent->client->ps.viewangles, (float *)&buf, NULL, NULL);
	return &buf;
}

CCALL int jl_entity_set_model(int id, char *model) {
	gentity_t *entity = g_entities + id;
	int modelid = G_ModelIndex(model); // stuff like "models/ammo/rocket/rocket.md3"
	entity->s.modelindex  = modelid;
	entity->s.modelindex2 = 0;    // no clue, ripped from other code
	SV_LinkEntity((sharedEntity_t *) entity); // is that even needed? meh idc
	return modelid;
}

CCALL int jl_entity_inuse(int id) {
	return g_entities[id].inuse;
}



void aagun_spawn(gentity_t *gun)
{
	gun->clipmask      = CONTENTS_SOLID;
	gun->r.contents    = CONTENTS_SOLID;
	gun->s.eType       = ET_GENERAL;
	//gun->s.dmgFlags    = HINT_MG42;
	//gun->s.modelindex  = G_ModelIndex("models/mapobjects/weapons/flak_a.md3");
	gun->s.modelindex  = G_ModelIndex("models/box.md3");
	gun->s.modelindex2 = 0;    // which barrel should fire next

	gun->s.origin[2] += 24;
	G_SetOrigin(gun, gun->s.origin);
	G_SetAngle(gun, gun->s.angles);

	VectorSet(gun->r.mins, -48, -48, -24);
	VectorSet(gun->r.maxs, 48, 48, 56);

	gun->s.apos.trTime     = 0;
	gun->s.apos.trDuration = 0;
	gun->s.apos.trType     = TR_LINEAR_STOP;

	VectorCopy(gun->s.angles, gun->s.angles2);   // initial angles

	//gun->touch = aagun_touch;
	//gun->think = aagun_think;
	//gun->use   = aagun_use;
	//gun->die   = aagun_die;

	gun->nextthink    = level.time + FRAMETIME;
	gun->timestamp    = level.time + 1000;
	gun->s.number     = gun - g_entities;
	//gun->s.origin2[0] = gun->harc;
	//gun->s.origin2[1] = gun->varc;
	gun->takedamage   = qfalse;

	SV_LinkEntity((sharedEntity_t *) gun);
}


// The actual hard working code :^)
#define DEBUG_MOVETO 0
int moveto(gentity_t *ent, vek3_t *to, float durationSeconds) {
	
#if DEBUG_MOVETO
	imgui_log("id=%d to=%d durationSeconds=%f\n", ent-g_entities, to, durationSeconds);
	imgui_log("vec: %f %f %f\n", to[0], to[1], to[2]);	
#endif
	if (durationSeconds <= 0.0) {
		imgui_log("durationMilliseconds must be > 0.0\n");
		return 0;
	}
	
#if DEBUG_MOVETO
	imgui_log("BEFORE:\nto=%f %f %f \ntrBase=%f %f %f \nr.currentOrigin=%f %f %f \ndelta=%f %f %f\n\n",
		to[0], to[1], to[2],
		ent->s.pos.trBase[0], ent->s.pos.trBase[1], ent->s.pos.trBase[2], 
		ent->r.currentOrigin[0], ent->r.currentOrigin[1], ent->r.currentOrigin[2],
		ent->s.pos.trDelta[0], ent->s.pos.trDelta[1], ent->s.pos.trDelta[2]
	);
#endif

	vec3_t		move;

	// VectorSubstract: C = A - B 
	// VectorScale:     C = A * B
	VectorSubtract( ent->r.currentOrigin, (float *)to, move );
	float distance = VectorLength( move );
#if DEBUG_MOVETO
	imgui_log("distance: %f\n", distance);
#endif
	if (distance < 0.01)
	{
		return 0;
	}

	BG_EvaluateTrajectory( &ent->s.pos, level.time, ent->r.currentOrigin/*, qfalse, 0*/); // extra vals were for ET:Legacy


	
#if DEBUG_MOVETO
	imgui_log("AFTER:\nto=%f %f %f \ntrBase=%f %f %f \nr.currentOrigin=%f %f %f \ndelta=%f %f %f\n\n",
		to[0], to[1], to[2],
		ent->s.pos.trBase[0], ent->s.pos.trBase[1], ent->s.pos.trBase[2], 
		ent->r.currentOrigin[0], ent->r.currentOrigin[1], ent->r.currentOrigin[2],
		ent->s.pos.trDelta[0], ent->s.pos.trDelta[1], ent->s.pos.trDelta[2]
	);
#endif
	VectorCopy(ent->r.currentOrigin, ent->s.pos.trBase);
	//VectorScale( move, speed, ent->s.pos.trDelta );
	//ent->s.pos.trDuration = distance * 1000 / speed;
	ent->s.pos.trDuration = durationSeconds * 1000; // trDuration is in milliseconds, so * 1000
	
	
	ent->moverState == MOVER_1TO2;
	//MatchTeam( ent, MOVER_1TO2, level.time + 50 );
	vec3_t			delta;
	
	
	// start moving 50 msec later, becase if this was player
	// triggered, level.time hasn't been advanced yet
	//ent->s.pos.trTime = level.time + 50;
	ent->s.pos.trTime = level.time;

		////VectorCopy( ent->pos1, ent->s.pos.trBase );
		VectorSubtract( (float *)to, ent->s.pos.trBase, delta );
		//durationSeconds = 1000.0 / ent->s.pos.trDuration;
		VectorScale( delta, 1.0 / durationSeconds, ent->s.pos.trDelta );
		ent->s.pos.trType = TR_LINEAR_STOP;

	//BG_EvaluateTrajectory( &ent->s.pos, level.time, ent->r.currentOrigin/*, 0, 0*/);	
	SV_LinkEntity((sharedEntity_t *) ent );
	return 1;
}

CCALL void player_forwardmove(gentity_t *player, int state) {
	//g_entities[id].client->pers.cmd.buttons & BUTTON_USE_HOLDABLE
	if (state) {
		player->client->pers.cmd.forwardmove = 120;
		player->client->pers.cmd.buttons |= BUTTON_WALKING;
	} else {
		player->client->pers.cmd.forwardmove = 0;
		player->client->pers.cmd.buttons &= ~BUTTON_WALKING;
	}
}

CCALL int player_isbot(gentity_t *player) {
	return player->r.svFlags & SVF_BOT;
}

int attackButtonPressed(gentity_t *player) {
	if (player->client == NULL)
		return 0;
	return player->client->pers.cmd.buttons & BUTTON_ATTACK;
}
CCALL int jl_player_attackbuttonpressed (int id) { return g_entities[id].client->pers.cmd.buttons & BUTTON_ATTACK;       }
CCALL int jl_player_usebuttonpressed    (int id) { return g_entities[id].client->pers.cmd.buttons & BUTTON_USE_HOLDABLE; }
CCALL int jl_player_walkbuttonpressed   (int id) { return g_entities[id].client->pers.cmd.buttons & BUTTON_WALKING;      }
//CCALL int jl_player_aimbuttonpressed    (int id) { return g_entities[id].client->pers.cmd.buttons & BUTTON_AIM;          }
//CCALL int jl_player_nadebuttonpressed   (int id) { return g_entities[id].client->pers.cmd.buttons & BUTTON_NADE;         }


int useButtonPressed(gentity_t *player) {
	if (player->client == NULL)
		return 0;
	return player->client->pers.cmd.buttons & BUTTON_USE_HOLDABLE;
}

// meh, gotta rename for q3 from etlegacy
int sprintButtonPressed(gentity_t *player) {
	if (player->client == NULL)
		return 0;
	return player->client->pers.cmd.buttons & BUTTON_WALKING;
}

int getEye(gentity_t *player, vec3_t out_eye) {
	
	if (player->client == NULL) {
		imgui_log("call getEye only on player entity\n");
		return 0;
	}
	playerState_t *ps = &player->client->ps;

	vec3_t right;
	AngleVectors(ps->viewangles, NULL, right, NULL);

	VectorCopy(ps->origin, out_eye);
	out_eye[2] += (float)ps->viewheight;

	//// add lean
	//if (ps->leanf != 0.f) {
	//	VectorMA(out_eye, ps->leanf, right, out_eye);
	//}
	return 1;
}

int isZooming(gentity_t *player) {
	if (player->client == NULL)
		return 0;
	//return player->client->ps.eFlags & EF_ZOOMING;
	return 0; // no clue how to get that in q3 yet
}






// The glue code

#if 0
int duk_func_entity_moveto(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float x = duk_to_number(ctx, 1);
	float y = duk_to_number(ctx, 2);
	float z = duk_to_number(ctx, 3);
	float durationSeconds = duk_to_number(ctx, 4);
	gentity_t *ent = g_entities + entid;
	vec3_t to = {x, y, z};
	moveto(ent, to, durationSeconds);

	//duk_push_int(ctx, 1);
	return 0;
}


float *js_push_vec3(duk_context *ctx) {
	//  ... BUFFER
	// 3 * 4 = 12 bytes for float[3]
	float *buf = (float *) duk_push_buffer(ctx, 3 * 4, 0);

	// ... BUFFER FLOAT32BUFFER
	duk_push_buffer_object(ctx, -1, 0, 3 * 4, DUK_BUFOBJ_FLOAT32ARRAY);

	// ... FLOAT32BUFFER
	duk_remove(ctx, -2);
	return buf;
}

int duk_func_entity_get_origin(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	
	float *buf = js_push_vec3(ctx);
	gentity_t *ent = g_entities+entid;
	//G_Printf("Got id: %d ent->client=%d\n", entid, ent->client);
	if (ent->client == NULL) {
		VectorCopy(ent->r.currentOrigin, buf);
		return 1;
	}
	VectorCopy(ent->client->ps.origin, buf);
	return 1;
}

int duk_func_entity_get_eye(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float *buf = js_push_vec3(ctx);
	gentity_t *ent = g_entities+entid;
	getEye(ent, buf);
	return 1;
}

int duk_func_entity_get_forward(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float *buf = js_push_vec3(ctx);
	gentity_t *ent = g_entities+entid;
	if (ent->client == NULL) return 0;
	AngleVectors(ent->client->ps.viewangles, buf, NULL, NULL);
	return 1;
}
int duk_func_entity_get_right(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float *buf = js_push_vec3(ctx);
	gentity_t *ent = g_entities+entid;
	if (ent->client == NULL) return 0;
	AngleVectors(ent->client->ps.viewangles, NULL, buf, NULL);
	return 1;
}
int duk_func_entity_get_up(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float *buf = js_push_vec3(ctx);
	gentity_t *ent = g_entities+entid;
	if (ent->client == NULL) return 0;
	AngleVectors(ent->client->ps.viewangles, NULL, NULL, buf);
	return 1;
}

int duk_func_entity_attackbuttonpressed(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	if (ent->client == NULL) return 0;
	duk_push_int(ctx, attackButtonPressed(ent));
	return 1;
}
int duk_func_entity_sprintbuttonpressed(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	if (ent->client == NULL) return 0;
	duk_push_int(ctx, sprintButtonPressed(ent));
	return 1;
}
int duk_func_entity_usebuttonpressed(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	if (ent->client == NULL) return 0;
	duk_push_int(ctx, useButtonPressed(ent));
	return 1;
}
int duk_func_entity_get_weapon(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	if (ent->client == NULL) return 0;
	duk_push_int(ctx, ent->client->ps.weapon);
	return 1;
}
int duk_func_entity_get_weaponstate(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	if (ent->client == NULL) return 0;
	duk_push_int(ctx, ent->client->ps.weaponstate);
	return 1;
}
int duk_func_entity_get_weapontime(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	if (ent->client == NULL) return 0;
	duk_push_int(ctx, ent->client->ps.weaponTime);
	return 1;
}

int duk_func_entity_set_origin(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float x = duk_to_number(ctx, 1);
	float y = duk_to_number(ctx, 2);
	float z = duk_to_number(ctx, 3);
	gentity_t *ent = g_entities + entid;
	vec3_t to = {x, y, z};
	G_SetOrigin(ent, to);
	trap_LinkEntity(ent);
	return 0;
}

void SetClientViewAngle(gentity_t *ent, vec3_t angle);
int duk_func_entity_set_angles(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float x = duk_to_number(ctx, 1);
	float y = duk_to_number(ctx, 2);
	float z = duk_to_number(ctx, 3);
	gentity_t *ent = g_entities + entid;
	
	vec3_t angle = {x, y, z};
	if (ent->client == NULL)
		G_SetAngle(ent, angle);
	else
		SetClientViewAngle(ent, angle);
	trap_LinkEntity(ent);
	return 0;
}

int duk_func_entity_get_angles(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float *buf = js_push_vec3(ctx);
	gentity_t *ent = g_entities+entid;
	//G_Printf("Got id: %d ent->client=%d\n", entid, ent->client);
	if (ent->client == NULL) {
		VectorCopy(ent->r.currentAngles, buf);
		return 1;
	}
	VectorCopy(ent->client->ps.viewangles, buf);
	return 1;
}

int duk_func_entity_add_event(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	float *buf = js_push_vec3(ctx);
	gentity_t *ent = g_entities+entid;
	float normal[3];
	normal[0] = duk_to_number(ctx, 1);
	normal[1] = duk_to_number(ctx, 2);
	normal[2] = duk_to_number(ctx, 3);
	G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( normal ) );
	return 1;
}

int duk_func_spawn_grenade(duk_context *ctx) {
	gentity_t *grenade = G_Spawn();
	aagun_spawn(grenade);
	duk_push_int(ctx, (int)(grenade - g_entities));
	return 1;
}

int duk_func_g_spawn(duk_context *ctx) {
	gentity_t *ent = G_Spawn();
	duk_push_int(ctx, (int)(ent - g_entities));
	return 1;
}


int duk_func_entity_notsolid(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	// remove the bit by and'ing with the invertion (~/not/invertion)
	//ent->s.solid is for what?
	ent->r.contents &= ~CONTENTS_SOLID;
	ent->clipmask &= ~CONTENTS_SOLID; // needed? no clue, it's set in aagun_spawn aswell
	trap_LinkEntity(ent);
	return 0;
}
int duk_func_entity_delete(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	// rather not call it on clients...
	if (ent->client) {
		printf("entity_delete(%d): I don't think it makes any sense to delete clients lol\n");
		return 0;
	}
	G_FreeEntity(ent);
	return 0;
}
int duk_func_entity_solid(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;
	ent->r.contents |= CONTENTS_SOLID;
	ent->clipmask |= CONTENTS_SOLID; // needed? no clue, it's set in aagun_spawn aswell
	trap_LinkEntity(ent);
	return 0;
}
int duk_func_entity_suicide(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *ent = g_entities + entid;


	//if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {
	//	return;
	//}
	//if (ent->health <= 0) {
	//	return;
	//}
	//ent->flags &= ~FL_GODMODE;
	ent->client->ps.stats[STAT_HEALTH] = ent->health = -999;

	//player_die (ent, ent, ent, 100000, MOD_SUICIDE);
	return 0;
}
int duk_func_entity_die(duk_context *ctx) {
	int self = duk_to_int(ctx, 0);
	int inflictor = duk_to_int(ctx, 1);
	int attacker = duk_to_int(ctx, 2);
	int damage = duk_to_int(ctx, 3);
	int mod = duk_to_int(ctx, 4);
	player_die (g_entities + self, g_entities + inflictor, g_entities + attacker, damage, mod);
	return 0;
}

int duk_func_getargs(duk_context *ctx) {
	char buf[4096];

	// doesnt exist lol retarded
	///trap_Args(buf, sizeof buf);

	duk_push_array(ctx);
	for (int i = 0; i<trap_Argc(); i++) {
		trap_Argv(i, buf, sizeof buf);
		duk_push_string(ctx, buf);
		duk_put_prop_index(ctx, -2, i);
	}
	//duk_push_string(ctx, buf);
	return 1;

}

CCALL void jl_test_vec3(float *vec) {
	imgui_log("%f %f %f\n", vec[0], vec[1], vec[2]);
}


int duk_func_trace(duk_context *ctx) {
	float from_x = duk_to_number(ctx, 0);
	float from_y = duk_to_number(ctx, 1);
	float from_z = duk_to_number(ctx, 2);
	float to_x = duk_to_number(ctx, 3);
	float to_y = duk_to_number(ctx, 4);
	float to_z = duk_to_number(ctx, 5);
	int passentity = duk_to_int(ctx, 6);
	//int mask = duk_to_int(ctx, 7);

	trace_t trace; 
	
	vec3_t from = {from_x, from_y, from_z};
	vec3_t to = {to_x, to_y, to_z};
	trap_Trace(&trace, from, vec3_origin, vec3_origin, to, passentity, MASK_SOLID);


	duk_push_object(ctx);
	float *endpos = js_push_vec3(ctx);
	VectorCopy(trace.endpos, endpos);
	duk_put_prop_string(ctx, -2, "endpos");
	duk_push_number(ctx, trace.fraction);
	duk_put_prop_string(ctx, -2, "fraction");
	duk_push_int(ctx, trace.entityNum);
	duk_put_prop_string(ctx, -2, "entityNum");

	
	float *normal = js_push_vec3(ctx);
	VectorCopy(trace.plane.normal, normal);
	duk_put_prop_string(ctx, -2, "normal");

	return 1;
}

int duk_func_entity_get_classname(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	gentity_t *entity = g_entities + entid;
	duk_push_string(ctx, entity->classname);
	return 1;
}


int duk_func_entity_set_model(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	const char *model = duk_to_string(ctx, 1);
	gentity_t *entity = g_entities + entid;
	entity->s.modelindex  = G_ModelIndex(model); // stuff like "models/ammo/rocket/rocket.md3"
	entity->s.modelindex2 = 0;    // no clue, ripped from other code
	trap_LinkEntity(entity); // is that even needed? meh idc
	return 0;
}

int duk_func_sendservercommand(duk_context *ctx) {
	int entid = duk_to_int(ctx, 0);
	const char *command = duk_to_string(ctx, 1);
	trap_SendServerCommand(entid, command);
	return 0;
}

int duk_func_getPlayersInRange(duk_context *ctx) {
	float x = duk_to_number(ctx, 0);
	float y = duk_to_number(ctx, 1);
	float z = duk_to_number(ctx, 2);
	float maxdistance = duk_to_number(ctx, 3);
	vec3_t compare = {x, y, z};
	vec3_t delta;
	int count = 0;
	duk_push_array(ctx);
	float distanceSquared = maxdistance * maxdistance;
	gentity_t *player;
	for (int i=0; i < g_maxclients.integer; i++) {
		player = g_entities + i;
		if (player->inuse == qfalse)
			continue;
		vec3_a_is_b_minus_c(delta, compare, player->client->ps.origin); // delta = compate - player.origin
		float ds = delta[0]*delta[0] + delta[1]*delta[1] + delta[2]*delta[2];
		if (ds <= distanceSquared) {
			//duk_push_number(ctx, ds);
			duk_push_int(ctx, i); // push playerid
			duk_put_prop_index(ctx, -2, count++);
		}
	}
	return 1;
}

#endif


	//hudelem->left = MSG_ReadLong(msg); // maybe use MSG_ReadByte and scale from 0-255 to 0-640 and 0-480?
	//hudelem->top = MSG_ReadLong(msg);
	//hudelem->width = MSG_ReadLong(msg);
	//hudelem->height = MSG_ReadLong(msg);
	//hudelem->color[0] = (float)MSG_ReadByte(msg) / 255.0;
	//hudelem->color[1] = (float)MSG_ReadByte(msg) / 255.0;
	//hudelem->color[2] = (float)MSG_ReadByte(msg) / 255.0;
	//hudelem->color[3] = (float)MSG_ReadByte(msg) / 255.0;
	//strcpy(hudelem->text, MSG_ReadString(msg));	

#if 0
	
/*

entity_send_hud(0, 20, 30, 100, 20, 1.0, 0.0, 0.0, 0.5, "hurri durri")
_entity_send_hud(0, 20, 30, 100, 20, 1.0, 0.0, 0.0, 0.5, alloc_string("hurri durri"))
*/
CCALL int jl_entity_send_hud(int playerid, int left, int top, int width, int height, float r, float g, float b, float a, char *text) {
	client_t *client = svs.clients + playerid;
	hudelem_t *clienthudelem = NULL;
	// todo make MAX_CLIENT_HUDS or something
	int i;
	for (i=0; i<128; i++) {
		
		if (client->clienthudelems[i].active) // search some non-active hudelem to use
			continue;
		clienthudelem = client->clienthudelems + i;
		break;
	}
	if (clienthudelem == NULL) {
		imgui_log("No clienthudelems left... clean some or increase limits\n");
		return -1; // -1 == invalid hud
	}
	clienthudelem->active = 1;
	clienthudelem->resend = 1;
	clienthudelem->left = left;
	clienthudelem->top = top;
	clienthudelem->width = width;
	clienthudelem->height = height;
	clienthudelem->color[0] = r;
	clienthudelem->color[1] = g;
	clienthudelem->color[2] = b;
	clienthudelem->color[3] = a;
	strcpy(clienthudelem->text, text);
	return i; // return hud id
}
CCALL void jl_entity_update_hud(int playerid, int hudid, int left, int top, int width, int height, float r, float g, float b, float a, char *text) {
	client_t *client = svs.clients + playerid;
	hudelem_t *clienthudelem = client->clienthudelems + hudid;
	clienthudelem->active = 1;
	clienthudelem->resend = 1;
	clienthudelem->left = left;
	clienthudelem->top = top;
	clienthudelem->width = width;
	clienthudelem->height = height;
	clienthudelem->color[0] = r;
	clienthudelem->color[1] = g;
	clienthudelem->color[2] = b;
	clienthudelem->color[3] = a;
	strcpy(clienthudelem->text, text);
}	
	
/*

entity_send_hud(0, 20, 30, 100, 20, 1.0, 0.0, 0.0, 0.5, "hurri durri")
*/
int duk_func_entity_send_hud(duk_context *ctx) {

	int   playerid = duk_to_int   (ctx, 0);
	int   left     = duk_to_int   (ctx, 1);
	int   top      = duk_to_int   (ctx, 2);
	int   width    = duk_to_int   (ctx, 3);
	int   height   = duk_to_int   (ctx, 4);
	float r        = duk_to_number(ctx, 5);
	float g        = duk_to_number(ctx, 6);
	float b        = duk_to_number(ctx, 7);
	float a        = duk_to_number(ctx, 8);
	char *text     = duk_to_string(ctx, 9);


	client_t *client = svs.clients + playerid;

	hudelem_t *clienthudelem = NULL;
	// todo make MAX_CLIENT_HUDS or something
	int i;
	for (i=0; i<128; i++) {
		
		if (client->clienthudelems[i].active) // search some non-active hudelem to use
			continue;
		clienthudelem = client->clienthudelems + i;
		break;
	}

	if (clienthudelem == NULL) {
		imgui_log("No clienthudelems left... clean some or increase limits\n");
		duk_push_int(ctx, -1); // -1 == invalid hud obviously
		return 1;
	}

	clienthudelem->active = 1;
	clienthudelem->resend = 1;
	
	clienthudelem->left = left;
	clienthudelem->top = top;
	clienthudelem->width = width;
	clienthudelem->height = height;
	clienthudelem->color[0] = r;
	clienthudelem->color[1] = g;
	clienthudelem->color[2] = b;
	clienthudelem->color[3] = a;
	strcpy(clienthudelem->text, text);
	duk_push_int(ctx, i); // push hud id
	return 1;
}


CCALL void jl_player_hudelem_settext(int playerid, int hudid, char *text) {
	client_t *client = svs.clients + playerid;
	hudelem_t *clienthudelem = client->clienthudelems + hudid;
	strcpy(clienthudelem->text, text);
	clienthudelem->resend = 1;
}

int duk_func_entity_hudelem_settext(duk_context *ctx) {
	int   playerid = duk_to_int   (ctx, 0);
	int   hudid    = duk_to_int   (ctx, 1);
	char *text     = duk_to_string(ctx, 2);
	jl_player_hudelem_settext(playerid, hudid, text);
	return 0;
}

CCALL void jl_player_hudelem_hide(int playerid, int hudid) {
	client_t *client = svs.clients + playerid;
	hudelem_t *clienthudelem = client->clienthudelems + hudid;
	clienthudelem->hidden = 1;
	clienthudelem->resend = 1;
}

int duk_func_entity_hudelem_hide(duk_context *ctx) {
	int   playerid = duk_to_int   (ctx, 0);
	int   hudid    = duk_to_int   (ctx, 1);
	jl_player_hudelem_hide(playerid, hudid);
	return 0;
}

CCALL void jl_player_hudelem_show(int playerid, int hudid) {
	client_t *client = svs.clients + playerid;
	hudelem_t *clienthudelem = client->clienthudelems + hudid;
	clienthudelem->hidden = 0;
	clienthudelem->resend = 1;
}

int duk_func_entity_hudelem_show(duk_context *ctx) {
	int   playerid = duk_to_int   (ctx, 0);
	int   hudid    = duk_to_int   (ctx, 1);
	jl_player_hudelem_show(playerid, hudid);
	return 0;
}

CCALL void jl_player_hudelem_free(int playerid, int hudid) {
	client_t *client = svs.clients + playerid;
	hudelem_t *clienthudelem = client->clienthudelems + hudid;
	clienthudelem->free = 1;
	clienthudelem->resend = 1;
}

int duk_func_entity_hudelem_free(duk_context *ctx) {
	int   playerid = duk_to_int   (ctx, 0);
	int   hudid    = duk_to_int   (ctx, 1);
	jl_player_hudelem_free(playerid, hudid);
	return 0;
}

int bind_ioquake3(duk_context *ctx) {
	
	// register some bindings to flashb4ck
	struct funcis funcs[] = {
		{"entity_moveto",		          duk_func_entity_moveto                      },
		{"entity_delete",		          duk_func_entity_delete                      },
		{"getargs",				          duk_func_getargs                            },
		{"entity_get_origin",             duk_func_entity_get_origin                  },
		{"entity_set_origin",             duk_func_entity_set_origin                  },
		{"entity_set_model",              duk_func_entity_set_model                   },
		{"entity_set_angles",             duk_func_entity_set_angles                  },
		{"entity_get_angles",             duk_func_entity_get_angles                  },
		{"entity_add_event",              duk_func_entity_add_event                   },
		{"entity_get_eye",                duk_func_entity_get_eye                     },
		{"entity_get_forward",            duk_func_entity_get_forward                 },
		{"entity_get_right",              duk_func_entity_get_right                   },
		{"entity_get_up",                 duk_func_entity_get_up                      },
		{"entity_attackbuttonpressed",    duk_func_entity_attackbuttonpressed         },
		{"entity_sprintbuttonpressed",    duk_func_entity_sprintbuttonpressed         },
		{"entity_usebuttonpressed",       duk_func_entity_usebuttonpressed            },
		{"entity_get_weapon",             duk_func_entity_get_weapon                  },
		{"entity_get_weaponstate",        duk_func_entity_get_weaponstate             },
		{"entity_get_weapontime",         duk_func_entity_get_weapontime              },
		{"spawngrenade",                  duk_func_spawn_grenade                      },
		{"g_spawn",                       duk_func_g_spawn                            },
		{"trace",                         duk_func_trace                              },
		{"entity_get_classname",          duk_func_entity_get_classname               },
		{"entity_solid",                  duk_func_entity_solid                       },
		{"entity_suicide",                duk_func_entity_suicide                     },
		{"entity_die",                    duk_func_entity_die                         },
		{"entity_notsolid",               duk_func_entity_notsolid                    },
		{"entity_delete",                 duk_func_entity_delete                      },
		{"sendservercommand",             duk_func_sendservercommand                  },
		{"getPlayersInRange",             duk_func_getPlayersInRange                  },
		{"entity_send_hud",               duk_func_entity_send_hud                    },
		{"entity_hudelem_settext",        duk_func_entity_hudelem_settext             },
		{"entity_hudelem_hide",           duk_func_entity_hudelem_hide                },
		{"entity_hudelem_show",           duk_func_entity_hudelem_show                },
		{"entity_hudelem_free",           duk_func_entity_hudelem_free                },
		{NULL, NULL}
	};
	for (int i=0; funcs[i].name; i++) {
		js_register_function(ctx, funcs[i].name, funcs[i].func);
	}

	// and lets load our "standard library"
	//js_eval_file_safe(ctx, "test.js");
}

#endif

//
//
// cmds
//
//
#if 0
// two neat helpers
int argv_int(int id) {
	char tmp[MAX_TOKEN_CHARS];
	trap_Argv(id, tmp, MAX_TOKEN_CHARS);
	return atoi(tmp);
}
int argv_float(int id) {
	char tmp[MAX_TOKEN_CHARS];
	trap_Argv(id, tmp, MAX_TOKEN_CHARS);
	return atof(tmp);
}



void svcmd_moveto() {
	
	int entity_id = argv_int(1);
	
	float to_x = argv_float(2);
	float to_y = argv_float(3);
	float to_z = argv_float(4);
	vec3_t to = {to_x, to_y, to_z};
	float durationMilliseconds = argv_float(5);
	G_Printf("mover entity_id=%d to ( %f %f %f ) durationMilliseconds=%f level.time=%d trType=%d\n", entity_id, to_x, to_y, to_z, durationMilliseconds, level.time, g_entities[entity_id].s.pos.trType);
	gentity_t *ent = g_entities + entity_id;
	moveto(ent, to, durationMilliseconds);
}

void svcmd_org() {
	int entid = argv_int(1);
	int which_origin = argv_int(2);
	float amount = argv_float(3);
	G_Printf("entid=%d which_origin=%d amount=%f\n", entid, which_origin, amount);
	gentity_t *ent = g_entities + entid;
	switch (which_origin) {
		case 0: ent->s.pos.trBase[2] += amount; break;
		case 1: ent->s.origin[2] += amount; break;
		case 2: ent->s.origin2[2] += amount; break;
		case 3: ent->r.currentOrigin[2] += amount; break;
		case 4: ent->pos1[2] += amount; break;
		case 5: ent->pos2[2] += amount; break;
		//case 6: ent->pos3[2] += amount; break;
	
	
	
	
	}

	trap_LinkEntity(ent);
}
void svcmd_setorigin() {
	int entid = argv_int(1);
	
	float x = argv_float(2);
	float y = argv_float(3);
	float z = argv_float(4);
	G_Printf("entid=%d %f %f %f\n", entid, x, y, z);
	gentity_t *ent = g_entities + entid;
	vec3_t tmp = {x, y, z};
	G_SetOrigin(ent, tmp);
}

void svcmd_ent() {
	int entity_id = argv_int(1);
	gentity_t *ent = g_entities + entity_id;
	G_Printf("classname: %\n", ent->classname);
	G_Printf("   s.pos.trBase: %5f %5f %5f\n", ent->s.pos.trBase   [0], ent->s.pos.trBase   [1], ent->s.pos.trBase   [2]);
	G_Printf("       s.origin: %5f %5f %5f\n", ent->s.origin       [0], ent->s.origin       [1], ent->s.origin       [2]);
	G_Printf("      s.origin2: %5f %5f %5f\n", ent->s.origin2      [0], ent->s.origin2      [1], ent->s.origin2      [2]);
	G_Printf("r.currentOrigin: %5f %5f %5f\n", ent->r.currentOrigin[0], ent->r.currentOrigin[1], ent->r.currentOrigin[2]);
	G_Printf("           pos1: %5f %5f %5f\n", ent->pos1           [0], ent->pos1           [1], ent->pos1           [2]);
	G_Printf("           pos2: %5f %5f %5f\n", ent->pos2           [0], ent->pos2           [1], ent->pos2           [2]);
	//G_Printf("           pos3: %5f %5f %5f\n", ent->pos3           [0], ent->pos3           [1], ent->pos3           [2]);
	G_Printf("trDelta: %f %f %f\n", ent->s.pos.trDelta[0], ent->s.pos.trDelta[1], ent->s.pos.trDelta[2]);
	G_Printf("trType: %d\n", ent->s.pos.trType);
	G_Printf("speed: %f\n", ent->speed);


	if (ent->r.contents & CONTENTS_SOLID              ) G_Printf("CONTENTS_SOLID            \n");
	//if (ent->r.contents & CONTENTS_LIGHTGRID          ) G_Printf("CONTENTS_LIGHTGRID        \n");
	if (ent->r.contents & CONTENTS_LAVA               ) G_Printf("CONTENTS_LAVA             \n");
	if (ent->r.contents & CONTENTS_SLIME              ) G_Printf("CONTENTS_SLIME            \n");
	if (ent->r.contents & CONTENTS_WATER              ) G_Printf("CONTENTS_WATER            \n");
	if (ent->r.contents & CONTENTS_FOG                ) G_Printf("CONTENTS_FOG              \n");
	//if (ent->r.contents & CONTENTS_MISSILECLIP        ) G_Printf("CONTENTS_MISSILECLIP      \n");
	//if (ent->r.contents & CONTENTS_ITEM               ) G_Printf("CONTENTS_ITEM             \n");
	if (ent->r.contents & CONTENTS_MOVER              ) G_Printf("CONTENTS_MOVER            \n");
	if (ent->r.contents & CONTENTS_AREAPORTAL         ) G_Printf("CONTENTS_AREAPORTAL       \n");
	if (ent->r.contents & CONTENTS_PLAYERCLIP         ) G_Printf("CONTENTS_PLAYERCLIP       \n");
	if (ent->r.contents & CONTENTS_MONSTERCLIP        ) G_Printf("CONTENTS_MONSTERCLIP      \n");
	if (ent->r.contents & CONTENTS_TELEPORTER         ) G_Printf("CONTENTS_TELEPORTER       \n");
	if (ent->r.contents & CONTENTS_JUMPPAD            ) G_Printf("CONTENTS_JUMPPAD          \n");
	if (ent->r.contents & CONTENTS_CLUSTERPORTAL      ) G_Printf("CONTENTS_CLUSTERPORTAL    \n");
	if (ent->r.contents & CONTENTS_DONOTENTER         ) G_Printf("CONTENTS_DONOTENTER       \n");
	//if (ent->r.contents & CONTENTS_DONOTENTER_LARGE   ) G_Printf("CONTENTS_DONOTENTER_LARGE \n");
	if (ent->r.contents & CONTENTS_ORIGIN             ) G_Printf("CONTENTS_ORIGIN           \n");
	if (ent->r.contents & CONTENTS_BODY               ) G_Printf("CONTENTS_BODY             \n");
	if (ent->r.contents & CONTENTS_CORPSE             ) G_Printf("CONTENTS_CORPSE           \n");
	if (ent->r.contents & CONTENTS_DETAIL             ) G_Printf("CONTENTS_DETAIL           \n");
	//
	if (ent->r.contents & CONTENTS_STRUCTURAL     	  ) G_Printf("CONTENTS_STRUCTURAL     	\n");
	if (ent->r.contents & CONTENTS_TRANSLUCENT    	  ) G_Printf("CONTENTS_TRANSLUCENT    	\n");
	if (ent->r.contents & CONTENTS_TRIGGER        	  ) G_Printf("CONTENTS_TRIGGER        	\n");
	if (ent->r.contents & CONTENTS_NODROP         	  ) G_Printf("CONTENTS_NODROP         	\n");


	//G_Printf("classname: %\n", ent->classname);
	//G_Printf("classname: %\n", ent->classname);
	//G_Printf("classname: %\n", ent->classname);
	//G_Printf("classname: %\n", ent->classname);

}

#endif
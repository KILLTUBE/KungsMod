void NPC_Mark1_Precache();
void NPC_Mark1_Part_Explode( gentity_t *self, int bolt );
void Mark1_Idle();
void Mark1Dead_FireRocket();
void Mark1Dead_FireBlaster();
void Mark1_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod, int dFlags, int hitLoc );
void Mark1_dying( gentity_t *self );
void NPC_Mark1_Pain( gentity_t *self, gentity_t *attacker, int damage );
void Mark1_Hunt();
void Mark1_FireBlaster();
void Mark1_BlasterAttack( qboolean advance );
void Mark1_FireRocket();
void Mark1_RocketAttack( qboolean advance );
void Mark1_AttackDecision();
void Mark1_Patrol();
void NPC_BSMark1_Default();
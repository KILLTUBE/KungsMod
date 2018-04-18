void NPC_Howler_Precache();
void Howler_Idle();
void Howler_Patrol();
void Howler_Move( qboolean visible );
void Howler_TryDamage( gentity_t *enemy, int damage );
void Howler_Attack();
void Howler_Combat();
void NPC_Howler_Pain( gentity_t *self, gentity_t *attacker, int damage );
void NPC_BSHowler_Default();

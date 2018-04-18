void NPC_MineMonster_Precache();
void MineMonster_Idle();
void MineMonster_Patrol();
void MineMonster_Move( qboolean visible );
void MineMonster_TryDamage( gentity_t *enemy, int damage );
void MineMonster_Attack();
void MineMonster_Combat();
void NPC_MineMonster_Pain( gentity_t *self, gentity_t *attacker, int damage );
void NPC_BSMineMonster_Default();

void SetGoal( gentity_t *goal, float rating );
void NPC_SetGoal( gentity_t *goal, float rating );
void NPC_ClearGoal();
qboolean G_BoundsOverlap( const vec3_t mins1, const vec3_t maxs1, const vec3_t mins2, const vec3_t maxs2 );
void NPC_ReachedGoal();
qboolean ReachedGoal( gentity_t *goal );
gentity_t *UpdateGoal();

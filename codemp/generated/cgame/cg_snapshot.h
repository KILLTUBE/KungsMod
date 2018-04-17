static void CG_ResetEntity( centity_t *cent );
static void CG_TransitionEntity( centity_t *cent );
void CG_SetInitialSnapshot( snapshot_t *snap );
static void CG_TransitionSnapshot();
static void CG_SetNextSnap( snapshot_t *snap );
static snapshot_t *CG_ReadNextSnapshot();
void CG_ProcessSnapshots();

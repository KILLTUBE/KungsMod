CG_ResetEntity( cent_ ) = ccall((:CG_ResetEntity, lib), Void, ( Ptr{centity_t},  ), cent_ );
CG_TransitionEntity( cent_ ) = ccall((:CG_TransitionEntity, lib), Void, ( Ptr{centity_t},  ), cent_ );
CG_SetInitialSnapshot( snap_ ) = ccall((:CG_SetInitialSnapshot, lib), Void, ( Ptr{snapshot_t},  ), snap_ );
CG_TransitionSnapshot() = ccall((:CG_TransitionSnapshot, lib), Void, (),  );
CG_SetNextSnap( snap_ ) = ccall((:CG_SetNextSnap, lib), Void, ( Ptr{snapshot_t},  ), snap_ );
CG_ReadNextSnapshot() = ccall((:CG_ReadNextSnapshot, lib), snapshot_t, (),  );
CG_ProcessSnapshots() = ccall((:CG_ProcessSnapshots, lib), Void, (),  );

NPC_GalakMech_Precache() = ccall((:NPC_GalakMech_Precache, lib), Void, (),  );
NPC_GalakMech_Init( ent_ ) = ccall((:NPC_GalakMech_Init, lib), Void, ( Ptr{gentity_t},  ), ent_ );
GM_CreateExplosion( self_, boltID_, doSmall_ ) = ccall((:GM_CreateExplosion, lib), Void, ( Ptr{gentity_t}, Int32, qboolean,  ), self_, boltID_, doSmall_ );
GM_Dying( self_ ) = ccall((:GM_Dying, lib), Void, ( Ptr{gentity_t},  ), self_ );
NPC_GM_Pain( self_, attacker_, damage_ ) = ccall((:NPC_GM_Pain, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Int32,  ), self_, attacker_, damage_ );
GM_HoldPosition() = ccall((:GM_HoldPosition, lib), Void, (),  );
GM_Move() = ccall((:GM_Move, lib), qboolean, (),  );
NPC_BSGM_Patrol() = ccall((:NPC_BSGM_Patrol, lib), Void, (),  );
GM_CheckMoveState() = ccall((:GM_CheckMoveState, lib), Void, (),  );
GM_CheckFireState() = ccall((:GM_CheckFireState, lib), Void, (),  );
NPC_GM_StartLaser() = ccall((:NPC_GM_StartLaser, lib), Void, (),  );
GM_StartGloat() = ccall((:GM_StartGloat, lib), Void, (),  );
NPC_BSGM_Attack() = ccall((:NPC_BSGM_Attack, lib), Void, (),  );
NPC_BSGM_Default() = ccall((:NPC_BSGM_Default, lib), Void, (),  );

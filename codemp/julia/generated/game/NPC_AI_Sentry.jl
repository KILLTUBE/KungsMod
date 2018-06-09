NPC_Sentry_Precache() = ccall((:NPC_Sentry_Precache, lib), Void, (),  );
sentry_use( self_, other_, activator_ ) = ccall((:sentry_use, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t},  ), self_, other_, activator_ );
NPC_Sentry_Pain( self_, attacker_, damage_ ) = ccall((:NPC_Sentry_Pain, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Int32,  ), self_, attacker_, damage_ );
Sentry_Fire() = ccall((:Sentry_Fire, lib), Void, (),  );
Sentry_MaintainHeight() = ccall((:Sentry_MaintainHeight, lib), Void, (),  );
Sentry_Idle() = ccall((:Sentry_Idle, lib), Void, (),  );
Sentry_Strafe() = ccall((:Sentry_Strafe, lib), Void, (),  );
Sentry_Hunt( visible_, advance_ ) = ccall((:Sentry_Hunt, lib), Void, ( qboolean, qboolean,  ), visible_, advance_ );
Sentry_RangedAttack( visible_, advance_ ) = ccall((:Sentry_RangedAttack, lib), Void, ( qboolean, qboolean,  ), visible_, advance_ );
Sentry_AttackDecision() = ccall((:Sentry_AttackDecision, lib), Void, (),  );
NPC_Sentry_Patrol() = ccall((:NPC_Sentry_Patrol, lib), Void, (),  );
NPC_BSSentry_Default() = ccall((:NPC_BSSentry_Default, lib), Void, (),  );
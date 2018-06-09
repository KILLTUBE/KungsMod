WP_SetSaberModel( client_, npcClass_ ) = ccall((:WP_SetSaberModel, lib), Int32, ( Ptr{gclient_t}, class_t,  ), client_, npcClass_ );
NPC_PainFunc( ent_ ) = ccall((:NPC_PainFunc, lib), Ptr{PAIN_FUNC}, ( Ptr{gentity_t},  ), ent_ );
NPC_TouchFunc( ent_ ) = ccall((:NPC_TouchFunc, lib), Ptr{TOUCH_FUNC}, ( Ptr{gentity_t},  ), ent_ );
NPC_SetMiscDefaultData( ent_ ) = ccall((:NPC_SetMiscDefaultData, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_WeaponsForTeam( team_, spawnflags_, NPC_type_ ) = ccall((:NPC_WeaponsForTeam, lib), Int32, ( team_t, Int32, Ptr{Char},  ), team_, spawnflags_, NPC_type_ );
NPC_SetWeapons( ent_ ) = ccall((:NPC_SetWeapons, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_SpawnEffect( ent_ ) = ccall((:NPC_SpawnEffect, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_SetFX_SpawnStates( ent_ ) = ccall((:NPC_SetFX_SpawnStates, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_SpotWouldTelefrag( npc_ ) = ccall((:NPC_SpotWouldTelefrag, lib), qboolean, ( Ptr{gentity_t},  ), npc_ );
NPC_Begin( ent_ ) = ccall((:NPC_Begin, lib), Void, ( Ptr{gentity_t},  ), ent_ );
New_NPC_t( entNum_ ) = ccall((:New_NPC_t, lib), Ptr{gNPC_t}, ( Int32,  ), entNum_ );
NPC_DefaultScriptFlags( ent_ ) = ccall((:NPC_DefaultScriptFlags, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_Spawn_Do( ent_ ) = ccall((:NPC_Spawn_Do, lib), Ptr{gentity_t}, ( Ptr{gentity_t},  ), ent_ );
NPC_Spawn_Go( ent_ ) = ccall((:NPC_Spawn_Go, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_ShySpawn( ent_ ) = ccall((:NPC_ShySpawn, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_Spawn( ent_, other_, activator_ ) = ccall((:NPC_Spawn, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_, activator_ );
NPC_PrecacheType( NPC_type_ ) = ccall((:NPC_PrecacheType, lib), Void, ( Ptr{Char},  ), NPC_type_ );
SP_NPC_spawner( self_ ) = ccall((:SP_NPC_spawner, lib), Void, ( Ptr{gentity_t},  ), self_ );
NPC_VehiclePrecache( spawner_ ) = ccall((:NPC_VehiclePrecache, lib), qboolean, ( Ptr{gentity_t},  ), spawner_ );
NPC_VehicleSpawnUse( self_, other_, activator_ ) = ccall((:NPC_VehicleSpawnUse, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t},  ), self_, other_, activator_ );
SP_NPC_Vehicle( self_ ) = ccall((:SP_NPC_Vehicle, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Kyle( self_ ) = ccall((:SP_NPC_Kyle, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Lando( self_ ) = ccall((:SP_NPC_Lando, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Jan( self_ ) = ccall((:SP_NPC_Jan, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Luke( self_ ) = ccall((:SP_NPC_Luke, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_MonMothma( self_ ) = ccall((:SP_NPC_MonMothma, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Tavion( self_ ) = ccall((:SP_NPC_Tavion, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Tavion_New( self_ ) = ccall((:SP_NPC_Tavion_New, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Alora( self_ ) = ccall((:SP_NPC_Alora, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Reborn_New( self_ ) = ccall((:SP_NPC_Reborn_New, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Cultist_Saber( self_ ) = ccall((:SP_NPC_Cultist_Saber, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Cultist_Saber_Powers( self_ ) = ccall((:SP_NPC_Cultist_Saber_Powers, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Cultist( self_ ) = ccall((:SP_NPC_Cultist, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Cultist_Commando( self_ ) = ccall((:SP_NPC_Cultist_Commando, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Cultist_Destroyer( self_ ) = ccall((:SP_NPC_Cultist_Destroyer, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Reelo( self_ ) = ccall((:SP_NPC_Reelo, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Galak( self_ ) = ccall((:SP_NPC_Galak, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Desann( self_ ) = ccall((:SP_NPC_Desann, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Bartender( self_ ) = ccall((:SP_NPC_Bartender, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_MorganKatarn( self_ ) = ccall((:SP_NPC_MorganKatarn, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Jedi( self_ ) = ccall((:SP_NPC_Jedi, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Prisoner( self_ ) = ccall((:SP_NPC_Prisoner, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Rebel( self_ ) = ccall((:SP_NPC_Rebel, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Human_Merc( self_ ) = ccall((:SP_NPC_Human_Merc, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Stormtrooper( self_ ) = ccall((:SP_NPC_Stormtrooper, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_StormtrooperOfficer( self_ ) = ccall((:SP_NPC_StormtrooperOfficer, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Snowtrooper( self_ ) = ccall((:SP_NPC_Snowtrooper, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Tie_Pilot( self_ ) = ccall((:SP_NPC_Tie_Pilot, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Ugnaught( self_ ) = ccall((:SP_NPC_Ugnaught, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Jawa( self_ ) = ccall((:SP_NPC_Jawa, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Gran( self_ ) = ccall((:SP_NPC_Gran, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Rodian( self_ ) = ccall((:SP_NPC_Rodian, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Weequay( self_ ) = ccall((:SP_NPC_Weequay, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Trandoshan( self_ ) = ccall((:SP_NPC_Trandoshan, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Tusken( self_ ) = ccall((:SP_NPC_Tusken, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Noghri( self_ ) = ccall((:SP_NPC_Noghri, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_SwampTrooper( self_ ) = ccall((:SP_NPC_SwampTrooper, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Imperial( self_ ) = ccall((:SP_NPC_Imperial, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_ImpWorker( self_ ) = ccall((:SP_NPC_ImpWorker, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_BespinCop( self_ ) = ccall((:SP_NPC_BespinCop, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Reborn( self_ ) = ccall((:SP_NPC_Reborn, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_ShadowTrooper( self_ ) = ccall((:SP_NPC_ShadowTrooper, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Murjj( self_ ) = ccall((:SP_NPC_Monster_Murjj, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Swamp( self_ ) = ccall((:SP_NPC_Monster_Swamp, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Howler( self_ ) = ccall((:SP_NPC_Monster_Howler, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_MineMonster( self_ ) = ccall((:SP_NPC_MineMonster, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Claw( self_ ) = ccall((:SP_NPC_Monster_Claw, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Glider( self_ ) = ccall((:SP_NPC_Monster_Glider, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Flier2( self_ ) = ccall((:SP_NPC_Monster_Flier2, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Lizard( self_ ) = ccall((:SP_NPC_Monster_Lizard, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Fish( self_ ) = ccall((:SP_NPC_Monster_Fish, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Wampa( self_ ) = ccall((:SP_NPC_Monster_Wampa, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Monster_Rancor( self_ ) = ccall((:SP_NPC_Monster_Rancor, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Interrogator( self_ ) = ccall((:SP_NPC_Droid_Interrogator, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Probe( self_ ) = ccall((:SP_NPC_Droid_Probe, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Mark1( self_ ) = ccall((:SP_NPC_Droid_Mark1, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Mark2( self_ ) = ccall((:SP_NPC_Droid_Mark2, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_ATST( self_ ) = ccall((:SP_NPC_Droid_ATST, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Remote( self_ ) = ccall((:SP_NPC_Droid_Remote, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Seeker( self_ ) = ccall((:SP_NPC_Droid_Seeker, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Sentry( self_ ) = ccall((:SP_NPC_Droid_Sentry, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Gonk( self_ ) = ccall((:SP_NPC_Droid_Gonk, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Mouse( self_ ) = ccall((:SP_NPC_Droid_Mouse, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_R2D2( self_ ) = ccall((:SP_NPC_Droid_R2D2, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_R5D2( self_ ) = ccall((:SP_NPC_Droid_R5D2, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_NPC_Droid_Protocol( self_ ) = ccall((:SP_NPC_Droid_Protocol, lib), Void, ( Ptr{gentity_t},  ), self_ );
NPC_SpawnType( ent_, npc_type_, targetname_, isVehicle_ ) = ccall((:NPC_SpawnType, lib), Ptr{gentity_t}, ( Ptr{gentity_t}, Ptr{Char}, Ptr{Char}, qboolean,  ), ent_, npc_type_, targetname_, isVehicle_ );
NPC_Spawn_f( ent_ ) = ccall((:NPC_Spawn_f, lib), Void, ( Ptr{gentity_t},  ), ent_ );
NPC_Kill_f() = ccall((:NPC_Kill_f, lib), Void, (),  );
NPC_PrintScore( ent_ ) = ccall((:NPC_PrintScore, lib), Void, ( Ptr{gentity_t},  ), ent_ );
Cmd_NPC_f( ent_ ) = ccall((:Cmd_NPC_f, lib), Void, ( Ptr{gentity_t},  ), ent_ );
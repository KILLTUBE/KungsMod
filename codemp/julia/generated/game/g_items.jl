adjustRespawnTime( preRespawnTime_, itemType_, itemTag_ ) = ccall((:adjustRespawnTime, lib), Int32, ( Float32, Int32, Int32,  ), preRespawnTime_, itemType_, itemTag_ );
ShieldRemove( self_ ) = ccall((:ShieldRemove, lib), Void, ( Ptr{gentity_t},  ), self_ );
ShieldThink( self_ ) = ccall((:ShieldThink, lib), Void, ( Ptr{gentity_t},  ), self_ );
ShieldDie( self_, inflictor_, attacker_, damage_, mod_ ) = ccall((:ShieldDie, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t}, Int32, Int32,  ), self_, inflictor_, attacker_, damage_, mod_ );
ShieldPain( self_, attacker_, damage_ ) = ccall((:ShieldPain, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Int32,  ), self_, attacker_, damage_ );
ShieldGoSolid( self_ ) = ccall((:ShieldGoSolid, lib), Void, ( Ptr{gentity_t},  ), self_ );
ShieldGoNotSolid( self_ ) = ccall((:ShieldGoNotSolid, lib), Void, ( Ptr{gentity_t},  ), self_ );
ShieldTouch( self_, other_, trace_ ) = ccall((:ShieldTouch, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{trace_t},  ), self_, other_, trace_ );
CreateShield( ent_ ) = ccall((:CreateShield, lib), Void, ( Ptr{gentity_t},  ), ent_ );
PlaceShield( playerent_ ) = ccall((:PlaceShield, lib), qboolean, ( Ptr{gentity_t},  ), playerent_ );
ItemUse_Binoculars( ent_ ) = ccall((:ItemUse_Binoculars, lib), Void, ( Ptr{gentity_t},  ), ent_ );
ItemUse_Shield( ent_ ) = ccall((:ItemUse_Shield, lib), Void, ( Ptr{gentity_t},  ), ent_ );
SentryTouch( ent_, other_, trace_ ) = ccall((:SentryTouch, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{trace_t},  ), ent_, other_, trace_ );
pas_fire( ent_ ) = ccall((:pas_fire, lib), Void, ( Ptr{gentity_t},  ), ent_ );
pas_find_enemies( self_ ) = ccall((:pas_find_enemies, lib), qboolean, ( Ptr{gentity_t},  ), self_ );
pas_adjust_enemy( ent_ ) = ccall((:pas_adjust_enemy, lib), Void, ( Ptr{gentity_t},  ), ent_ );
sentryExpire( self_ ) = ccall((:sentryExpire, lib), Void, ( Ptr{gentity_t},  ), self_ );
pas_think( ent_ ) = ccall((:pas_think, lib), Void, ( Ptr{gentity_t},  ), ent_ );
turret_die( self_, inflictor_, attacker_, damage_, mod_ ) = ccall((:turret_die, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t}, Int32, Int32,  ), self_, inflictor_, attacker_, damage_, mod_ );
turret_free( self_ ) = ccall((:turret_free, lib), Void, ( Ptr{gentity_t},  ), self_ );
SP_PAS( base_ ) = ccall((:SP_PAS, lib), Void, ( Ptr{gentity_t},  ), base_ );
ItemUse_Sentry( ent_ ) = ccall((:ItemUse_Sentry, lib), Void, ( Ptr{gentity_t},  ), ent_ );
ItemUse_Seeker( ent_ ) = ccall((:ItemUse_Seeker, lib), Void, ( Ptr{gentity_t},  ), ent_ );
MedPackGive( ent_, amount_ ) = ccall((:MedPackGive, lib), Void, ( Ptr{gentity_t}, Int32,  ), ent_, amount_ );
ItemUse_MedPack_Big( ent_ ) = ccall((:ItemUse_MedPack_Big, lib), Void, ( Ptr{gentity_t},  ), ent_ );
ItemUse_MedPack( ent_ ) = ccall((:ItemUse_MedPack, lib), Void, ( Ptr{gentity_t},  ), ent_ );
Jetpack_Off( ent_ ) = ccall((:Jetpack_Off, lib), Void, ( Ptr{gentity_t},  ), ent_ );
Jetpack_On( ent_ ) = ccall((:Jetpack_On, lib), Void, ( Ptr{gentity_t},  ), ent_ );
ItemUse_Jetpack( ent_ ) = ccall((:ItemUse_Jetpack, lib), Void, ( Ptr{gentity_t},  ), ent_ );
ItemUse_UseCloak( ent_ ) = ccall((:ItemUse_UseCloak, lib), Void, ( Ptr{gentity_t},  ), ent_ );
SpecialItemThink( ent_ ) = ccall((:SpecialItemThink, lib), Void, ( Ptr{gentity_t},  ), ent_ );
G_SpecialSpawnItem( ent_, item_ ) = ccall((:G_SpecialSpawnItem, lib), Void, ( Ptr{gentity_t}, Ptr{gitem_t},  ), ent_, item_ );
G_PrecacheDispensers() = ccall((:G_PrecacheDispensers, lib), Void, (),  );
ItemUse_UseDisp( ent_, type_ ) = ccall((:ItemUse_UseDisp, lib), Void, ( Ptr{gentity_t}, Int32,  ), ent_, type_ );
EWebDisattach( owner_, eweb_ ) = ccall((:EWebDisattach, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t},  ), owner_, eweb_ );
EWebPrecache() = ccall((:EWebPrecache, lib), Void, (),  );
EWebDie( self_, inflictor_, attacker_, damage_, mod_ ) = ccall((:EWebDie, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t}, Int32, Int32,  ), self_, inflictor_, attacker_, damage_, mod_ );
EWebPain( self_, attacker_, damage_ ) = ccall((:EWebPain, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Int32,  ), self_, attacker_, damage_ );
EWeb_SetBoneAngles( ent_, bone_, angles_ ) = ccall((:EWeb_SetBoneAngles, lib), Void, ( Ptr{gentity_t}, Ptr{Char}, vec3_t,  ), ent_, bone_, angles_ );
EWeb_SetBoneAnim( eweb_, startFrame_, endFrame_ ) = ccall((:EWeb_SetBoneAnim, lib), Void, ( Ptr{gentity_t}, Int32, Int32,  ), eweb_, startFrame_, endFrame_ );
EWebFire( owner_, eweb_ ) = ccall((:EWebFire, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t},  ), owner_, eweb_ );
EWebPositionUser( owner_, eweb_ ) = ccall((:EWebPositionUser, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t},  ), owner_, eweb_ );
EWebUpdateBoneAngles( owner_, eweb_ ) = ccall((:EWebUpdateBoneAngles, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t},  ), owner_, eweb_ );
EWebThink( self_ ) = ccall((:EWebThink, lib), Void, ( Ptr{gentity_t},  ), self_ );
EWeb_Create( spawner_ ) = ccall((:EWeb_Create, lib), Ptr{gentity_t}, ( Ptr{gentity_t},  ), spawner_ );
ItemUse_UseEWeb( ent_ ) = ccall((:ItemUse_UseEWeb, lib), Void, ( Ptr{gentity_t},  ), ent_ );
Pickup_Powerup( ent_, other_ ) = ccall((:Pickup_Powerup, lib), Int32, ( Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_ );
Pickup_Holdable( ent_, other_ ) = ccall((:Pickup_Holdable, lib), Int32, ( Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_ );
Add_Ammo( ent_, weapon_, count_ ) = ccall((:Add_Ammo, lib), Void, ( Ptr{gentity_t}, Int32, Int32,  ), ent_, weapon_, count_ );
Pickup_Ammo( ent_, other_ ) = ccall((:Pickup_Ammo, lib), Int32, ( Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_ );
Pickup_Weapon( ent_, other_ ) = ccall((:Pickup_Weapon, lib), Int32, ( Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_ );
Pickup_Health( ent_, other_ ) = ccall((:Pickup_Health, lib), Int32, ( Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_ );
Pickup_Armor( ent_, other_ ) = ccall((:Pickup_Armor, lib), Int32, ( Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_ );
RespawnItem( ent_ ) = ccall((:RespawnItem, lib), Void, ( Ptr{gentity_t},  ), ent_ );
CheckItemCanBePickedUpByNPC( item_, pickerupper_ ) = ccall((:CheckItemCanBePickedUpByNPC, lib), qboolean, ( Ptr{gentity_t}, Ptr{gentity_t},  ), item_, pickerupper_ );
Touch_Item( ent_, other_, trace_ ) = ccall((:Touch_Item, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{trace_t},  ), ent_, other_, trace_ );
LaunchItem( item_, origin_, velocity_ ) = ccall((:LaunchItem, lib), Ptr{gentity_t}, ( Ptr{gitem_t}, vec3_t, vec3_t,  ), item_, origin_, velocity_ );
Drop_Item( ent_, item_, angle_ ) = ccall((:Drop_Item, lib), Ptr{gentity_t}, ( Ptr{gentity_t}, Ptr{gitem_t}, Float32,  ), ent_, item_, angle_ );
Use_Item( ent_, other_, activator_ ) = ccall((:Use_Item, lib), Void, ( Ptr{gentity_t}, Ptr{gentity_t}, Ptr{gentity_t},  ), ent_, other_, activator_ );
FinishSpawningItem( ent_ ) = ccall((:FinishSpawningItem, lib), Void, ( Ptr{gentity_t},  ), ent_ );
G_CheckTeamItems() = ccall((:G_CheckTeamItems, lib), Void, (),  );
ClearRegisteredItems() = ccall((:ClearRegisteredItems, lib), Void, (),  );
RegisterItem( item_ ) = ccall((:RegisterItem, lib), Void, ( Ptr{gitem_t},  ), item_ );
SaveRegisteredItems() = ccall((:SaveRegisteredItems, lib), Void, (),  );
G_ItemDisabled( item_ ) = ccall((:G_ItemDisabled, lib), Int32, ( Ptr{gitem_t},  ), item_ );
G_SpawnItem( ent_, item_ ) = ccall((:G_SpawnItem, lib), Void, ( Ptr{gentity_t}, Ptr{gitem_t},  ), ent_, item_ );
G_BounceItem( ent_, trace_ ) = ccall((:G_BounceItem, lib), Void, ( Ptr{gentity_t}, Ptr{trace_t},  ), ent_, trace_ );
G_RunItem( ent_ ) = ccall((:G_RunItem, lib), Void, ( Ptr{gentity_t},  ), ent_ );

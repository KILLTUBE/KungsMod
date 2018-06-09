MenuFontToHandle_CG( iMenuFont_ ) = ccall((:MenuFontToHandle_CG, lib), Int32, ( Int32,  ), iMenuFont_ );
CG_Text_Width( text_, scale_, iMenuFont_ ) = ccall((:CG_Text_Width, lib), Int32, ( Ptr{Char}, Float32, Int32,  ), text_, scale_, iMenuFont_ );
CG_Text_Height( text_, scale_, iMenuFont_ ) = ccall((:CG_Text_Height, lib), Int32, ( Ptr{Char}, Float32, Int32,  ), text_, scale_, iMenuFont_ );
CG_Text_Paint( x_, y_, scale_, color_, text_, adjust_, limit_, style_, iMenuFont_ ) = ccall((:CG_Text_Paint, lib), Void, ( Float32, Float32, Float32, vec4_t, Ptr{Char}, Float32, Int32, Int32, Int32,  ), x_, y_, scale_, color_, text_, adjust_, limit_, style_, iMenuFont_ );
CG_DrawZoomMask() = ccall((:CG_DrawZoomMask, lib), Void, (),  );
CG_Draw3DModel( x_, y_, w_, h_, model_, ghoul2_, g2radius_, skin_, origin_, angles_ ) = ccall((:CG_Draw3DModel, lib), Void, ( Float32, Float32, Float32, Float32, qhandle_t, Ptr{Void}, Int32, qhandle_t, vec3_t, vec3_t,  ), x_, y_, w_, h_, model_, ghoul2_, g2radius_, skin_, origin_, angles_ );
CG_DrawHead( x_, y_, w_, h_, clientNum_, headAngles_ ) = ccall((:CG_DrawHead, lib), Void, ( Float32, Float32, Float32, Float32, Int32, vec3_t,  ), x_, y_, w_, h_, clientNum_, headAngles_ );
CG_DrawFlagModel( x_, y_, w_, h_, team_, force2D_ ) = ccall((:CG_DrawFlagModel, lib), Void, ( Float32, Float32, Float32, Float32, Int32, qboolean,  ), x_, y_, w_, h_, team_, force2D_ );
CG_DrawHealth( menuHUD_ ) = ccall((:CG_DrawHealth, lib), Void, ( Ptr{menuDef_t},  ), menuHUD_ );
CG_DrawArmor( menuHUD_ ) = ccall((:CG_DrawArmor, lib), Void, ( Ptr{menuDef_t},  ), menuHUD_ );
CG_DrawSaberStyle( cent_, menuHUD_ ) = ccall((:CG_DrawSaberStyle, lib), Void, ( Ptr{centity_t}, Ptr{menuDef_t},  ), cent_, menuHUD_ );
CG_DrawAmmo( cent_, menuHUD_ ) = ccall((:CG_DrawAmmo, lib), Void, ( Ptr{centity_t}, Ptr{menuDef_t},  ), cent_, menuHUD_ );
CG_DrawForcePower( menuHUD_ ) = ccall((:CG_DrawForcePower, lib), Void, ( Ptr{menuDef_t},  ), menuHUD_ );
CG_DrawSimpleSaberStyle( cent_ ) = ccall((:CG_DrawSimpleSaberStyle, lib), Void, ( Ptr{centity_t},  ), cent_ );
CG_DrawSimpleAmmo( cent_ ) = ccall((:CG_DrawSimpleAmmo, lib), Void, ( Ptr{centity_t},  ), cent_ );
CG_DrawSimpleForcePower( cent_ ) = ccall((:CG_DrawSimpleForcePower, lib), Void, ( Ptr{centity_t},  ), cent_ );
CG_DrawHUD( cent_ ) = ccall((:CG_DrawHUD, lib), Void, ( Ptr{centity_t},  ), cent_ );
ForcePower_Valid( i_ ) = ccall((:ForcePower_Valid, lib), qboolean, ( Int32,  ), i_ );
CG_DrawForceSelect() = ccall((:CG_DrawForceSelect, lib), Void, (),  );
CG_DrawInvenSelect() = ccall((:CG_DrawInvenSelect, lib), Void, (),  );
CG_CheckTargetVehicle( pTargetVeh_, alpha_ ) = ccall((:CG_CheckTargetVehicle, lib), qboolean, ( Ptr{Ptr{centity_t}}, Ptr{Float32},  ), pTargetVeh_, alpha_ );
CG_DrawVehicleShields( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleShields, lib), Float32, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleAmmo( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleAmmo, lib), Void, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleAmmoUpper( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleAmmoUpper, lib), Void, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleAmmoLower( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleAmmoLower, lib), Void, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleTurboRecharge( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleTurboRecharge, lib), Void, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleWeaponsLinked( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleWeaponsLinked, lib), Void, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleSpeed( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleSpeed, lib), Void, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleArmor( menuHUD_, veh_ ) = ccall((:CG_DrawVehicleArmor, lib), Void, ( Ptr{menuDef_t}, Ptr{centity_t},  ), menuHUD_, veh_ );
CG_DrawVehicleDamage( veh_, brokenLimbs_, menuHUD_, alpha_, index_ ) = ccall((:CG_DrawVehicleDamage, lib), Void, ( Ptr{centity_t}, Int32, Ptr{menuDef_t}, Float32, Int32,  ), veh_, brokenLimbs_, menuHUD_, alpha_, index_ );
CG_DrawVehicleDamageHUD( veh_, brokenLimbs_, percShields_, menuName_, alpha_ ) = ccall((:CG_DrawVehicleDamageHUD, lib), Void, ( Ptr{centity_t}, Int32, Float32, Ptr{Char}, Float32,  ), veh_, brokenLimbs_, percShields_, menuName_, alpha_ );
CG_DrawVehicleHud( cent_ ) = ccall((:CG_DrawVehicleHud, lib), qboolean, ( Ptr{centity_t},  ), cent_ );
CG_DrawStats() = ccall((:CG_DrawStats, lib), Void, (),  );
CG_DrawPickupItem() = ccall((:CG_DrawPickupItem, lib), Void, (),  );
CG_DrawTeamBackground( x_, y_, w_, h_, alpha_, team_ ) = ccall((:CG_DrawTeamBackground, lib), Void, ( Int32, Int32, Int32, Int32, Float32, Int32,  ), x_, y_, w_, h_, alpha_, team_ );
CG_DrawMiniScoreboard( y_ ) = ccall((:CG_DrawMiniScoreboard, lib), Float32, ( Float32,  ), y_ );
CG_DrawEnemyInfo( y_ ) = ccall((:CG_DrawEnemyInfo, lib), Float32, ( Float32,  ), y_ );
CG_DrawSnapshot( y_ ) = ccall((:CG_DrawSnapshot, lib), Float32, ( Float32,  ), y_ );
CG_DrawFPS( y_ ) = ccall((:CG_DrawFPS, lib), Float32, ( Float32,  ), y_ );
CG_DrawHealthBarRough( x_, y_, width_, height_, ratio_, color1_, color2_ ) = ccall((:CG_DrawHealthBarRough, lib), Void, ( Float32, Float32, Int32, Int32, Float32, Ptr{Float32}, Ptr{Float32},  ), x_, y_, width_, height_, ratio_, color1_, color2_ );
CG_DrawDuelistHealth( x_, y_, w_, h_, duelist_ ) = ccall((:CG_DrawDuelistHealth, lib), Void, ( Float32, Float32, Float32, Float32, Int32,  ), x_, y_, w_, h_, duelist_ );
CG_DrawRadar( y_ ) = ccall((:CG_DrawRadar, lib), Float32, ( Float32,  ), y_ );
CG_DrawTimer( y_ ) = ccall((:CG_DrawTimer, lib), Float32, ( Float32,  ), y_ );
CG_DrawTeamOverlay( y_, right_, upper_ ) = ccall((:CG_DrawTeamOverlay, lib), Float32, ( Float32, qboolean, qboolean,  ), y_, right_, upper_ );
CG_DrawPowerupIcons( y_ ) = ccall((:CG_DrawPowerupIcons, lib), Void, ( Int32,  ), y_ );
CG_DrawUpperRight() = ccall((:CG_DrawUpperRight, lib), Void, (),  );
CG_DrawReward() = ccall((:CG_DrawReward, lib), Void, (),  );
CG_AddLagometerFrameInfo() = ccall((:CG_AddLagometerFrameInfo, lib), Void, (),  );
CG_AddLagometerSnapshotInfo( snap_ ) = ccall((:CG_AddLagometerSnapshotInfo, lib), Void, ( Ptr{snapshot_t},  ), snap_ );
CG_DrawDisconnect() = ccall((:CG_DrawDisconnect, lib), Void, (),  );
CG_DrawLagometer() = ccall((:CG_DrawLagometer, lib), Void, (),  );
CG_DrawSiegeMessage( str_, objectiveScreen_ ) = ccall((:CG_DrawSiegeMessage, lib), Void, ( Ptr{Char}, Int32,  ), str_, objectiveScreen_ );
CG_DrawSiegeMessageNonMenu( str_ ) = ccall((:CG_DrawSiegeMessageNonMenu, lib), Void, ( Ptr{Char},  ), str_ );
CG_CenterPrint( str_, y_, charWidth_ ) = ccall((:CG_CenterPrint, lib), Void, ( Ptr{Char}, Int32, Int32,  ), str_, y_, charWidth_ );
BG_IsWhiteSpace( c_ ) = ccall((:BG_IsWhiteSpace, lib), qboolean, ( Char,  ), c_ );
CG_DrawCenterString() = ccall((:CG_DrawCenterString, lib), Void, (),  );
CG_DrawSiegeInfo( cent_, chX_, chY_, chW_, chH_ ) = ccall((:CG_DrawSiegeInfo, lib), Void, ( Ptr{centity_t}, Float32, Float32, Float32, Float32,  ), cent_, chX_, chY_, chW_, chH_ );
CG_DrawHealthBar( cent_, chX_, chY_, chW_, chH_ ) = ccall((:CG_DrawHealthBar, lib), Void, ( Ptr{centity_t}, Float32, Float32, Float32, Float32,  ), cent_, chX_, chY_, chW_, chH_ );
CG_DrawHaqrBar( chX_, chY_, chW_, chH_ ) = ccall((:CG_DrawHaqrBar, lib), Void, ( Float32, Float32, Float32, Float32,  ), chX_, chY_, chW_, chH_ );
CG_DrawGenericTimerBar() = ccall((:CG_DrawGenericTimerBar, lib), Void, (),  );
CG_LerpCrosshairPos( x_, y_ ) = ccall((:CG_LerpCrosshairPos, lib), Void, ( Ptr{Float32}, Ptr{Float32},  ), x_, y_ );
CG_DrawCrosshair( worldPoint_, chEntValid_ ) = ccall((:CG_DrawCrosshair, lib), Void, ( vec3_t, Int32,  ), worldPoint_, chEntValid_ );
CG_WorldCoordToScreenCoordFloat( worldCoord_, x_, y_ ) = ccall((:CG_WorldCoordToScreenCoordFloat, lib), qboolean, ( vec3_t, Ptr{Float32}, Ptr{Float32},  ), worldCoord_, x_, y_ );
CG_WorldCoordToScreenCoord( worldCoord_, x_, y_ ) = ccall((:CG_WorldCoordToScreenCoord, lib), qboolean, ( vec3_t, Ptr{Int32}, Ptr{Int32},  ), worldCoord_, x_, y_ );
CG_SaberClashFlare() = ccall((:CG_SaberClashFlare, lib), Void, (),  );
CG_DottedLine( x1_, y1_, x2_, y2_, dotSize_, numDots_, color_, alpha_ ) = ccall((:CG_DottedLine, lib), Void, ( Float32, Float32, Float32, Float32, Float32, Int32, vec4_t, Float32,  ), x1_, y1_, x2_, y2_, dotSize_, numDots_, color_, alpha_ );
CG_BracketEntity( cent_, radius_ ) = ccall((:CG_BracketEntity, lib), Void, ( Ptr{centity_t}, Float32,  ), cent_, radius_ );
CG_InFighter() = ccall((:CG_InFighter, lib), qboolean, (),  );
CG_InATST() = ccall((:CG_InATST, lib), qboolean, (),  );
CG_DrawBracketedEntities() = ccall((:CG_DrawBracketedEntities, lib), Void, (),  );
CG_DrawHolocronIcons() = ccall((:CG_DrawHolocronIcons, lib), Void, (),  );
CG_IsDurationPower( power_ ) = ccall((:CG_IsDurationPower, lib), qboolean, ( Int32,  ), power_ );
CG_DrawActivePowers() = ccall((:CG_DrawActivePowers, lib), Void, (),  );
CG_DrawRocketLocking( lockEntNum_, lockTime_ ) = ccall((:CG_DrawRocketLocking, lib), Void, ( Int32, Int32,  ), lockEntNum_, lockTime_ );
CG_CalcVehicleMuzzlePoint( entityNum_, start_, d_f_, d_rt_, d_up_ ) = ccall((:CG_CalcVehicleMuzzlePoint, lib), qboolean, ( Int32, vec3_t, vec3_t, vec3_t, vec3_t,  ), entityNum_, start_, d_f_, d_rt_, d_up_ );
CG_CalcEWebMuzzlePoint( cent_, start_, d_f_, d_rt_, d_up_ ) = ccall((:CG_CalcEWebMuzzlePoint, lib), Void, ( Ptr{centity_t}, vec3_t, vec3_t, vec3_t, vec3_t,  ), cent_, start_, d_f_, d_rt_, d_up_ );
CG_ScanForCrosshairEntity() = ccall((:CG_ScanForCrosshairEntity, lib), Void, (),  );
CG_DrawCrosshairNames() = ccall((:CG_DrawCrosshairNames, lib), Void, (),  );
CG_DrawSpectator() = ccall((:CG_DrawSpectator, lib), Void, (),  );
CG_DrawVote() = ccall((:CG_DrawVote, lib), Void, (),  );
CG_DrawTeamVote() = ccall((:CG_DrawTeamVote, lib), Void, (),  );
CG_DrawScoreboard() = ccall((:CG_DrawScoreboard, lib), qboolean, (),  );
CG_DrawIntermission() = ccall((:CG_DrawIntermission, lib), Void, (),  );
CG_DrawFollow() = ccall((:CG_DrawFollow, lib), qboolean, (),  );
CG_DrawTemporaryStats() = ccall((:CG_DrawTemporaryStats, lib), Void, (),  );
CG_DrawAmmoWarning() = ccall((:CG_DrawAmmoWarning, lib), Void, (),  );
CG_DrawWarmup() = ccall((:CG_DrawWarmup, lib), Void, (),  );
CG_DrawTimedMenus() = ccall((:CG_DrawTimedMenus, lib), Void, (),  );
CG_DrawFlagStatus() = ccall((:CG_DrawFlagStatus, lib), Void, (),  );
CG_DrawJetpackFuel() = ccall((:CG_DrawJetpackFuel, lib), Void, (),  );
CG_DrawEWebHealth() = ccall((:CG_DrawEWebHealth, lib), Void, (),  );
CG_DrawCloakFuel() = ccall((:CG_DrawCloakFuel, lib), Void, (),  );
CG_DrawSiegeTimer( timeRemaining_, isMyTeam_ ) = ccall((:CG_DrawSiegeTimer, lib), Void, ( Int32, qboolean,  ), timeRemaining_, isMyTeam_ );
CG_DrawSiegeDeathTimer( timeRemaining_ ) = ccall((:CG_DrawSiegeDeathTimer, lib), Void, ( Int32,  ), timeRemaining_ );
CG_DrawSiegeHUDItem() = ccall((:CG_DrawSiegeHUDItem, lib), Void, (),  );
CG_ChatBox_StrInsert( buffer_, place_, str_ ) = ccall((:CG_ChatBox_StrInsert, lib), Void, ( Ptr{Char}, Int32, Ptr{Char},  ), buffer_, place_, str_ );
CG_ChatBox_AddString( chatStr_ ) = ccall((:CG_ChatBox_AddString, lib), Void, ( Ptr{Char},  ), chatStr_ );
CG_ChatBox_ArrayInsert( array_, insPoint_, maxNum_, item_ ) = ccall((:CG_ChatBox_ArrayInsert, lib), Void, ( Ptr{Ptr{chatBoxItem_t}}, Int32, Int32, Ptr{chatBoxItem_t},  ), array_, insPoint_, maxNum_, item_ );
CG_ChatBox_DrawStrings() = ccall((:CG_ChatBox_DrawStrings, lib), Void, (),  );
CG_Draw2DScreenTints() = ccall((:CG_Draw2DScreenTints, lib), Void, (),  );
CG_Draw2D() = ccall((:CG_Draw2D, lib), Void, (),  );
CG_DrawMiscStaticModels() = ccall((:CG_DrawMiscStaticModels, lib), Void, (),  );
CG_DrawTourneyScoreboard() = ccall((:CG_DrawTourneyScoreboard, lib), Void, (),  );
CG_DrawActive( stereoView_ ) = ccall((:CG_DrawActive, lib), Void, ( stereoFrame_t,  ), stereoView_ );
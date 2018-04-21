G_AddVoiceEvent( self_, event_, speakDebounceTime_ ) = ccall((:G_AddVoiceEvent, lib), Void, ( Ptr{gentity_t}, Int32, Int32,  ), self_, event_, speakDebounceTime_ );
NPC_PlayConfusionSound( self_ ) = ccall((:NPC_PlayConfusionSound, lib), Void, ( Ptr{gentity_t},  ), self_ );

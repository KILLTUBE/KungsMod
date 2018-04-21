#Debug_Printf( cv_, debugLevel_, fmt_, _ ) = ccall((:Debug_Printf, lib), Void, ( Ptr{cvar_t}, Int32, Ptr{Char}, ,  ), cv_, debugLevel_, fmt_, _ );
#Debug_NPCPrintf( printNPC_, cv_, debugLevel_, fmt_, _ ) = ccall((:Debug_NPCPrintf, lib), Void, ( Ptr{gentity_t}, Ptr{cvar_t}, Int32, Ptr{Char}, ,  ), printNPC_, cv_, debugLevel_, fmt_, _ );

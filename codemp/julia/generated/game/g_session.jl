G_WriteClientSessionData( client_ ) = ccall((:G_WriteClientSessionData, lib), Void, ( Ptr{gclient_t},  ), client_ );
G_ReadSessionData( client_ ) = ccall((:G_ReadSessionData, lib), Void, ( Ptr{gclient_t},  ), client_ );
G_InitSessionData( client_, userinfo_, isBot_ ) = ccall((:G_InitSessionData, lib), Void, ( Ptr{gclient_t}, Ptr{Char}, qboolean,  ), client_, userinfo_, isBot_ );
G_InitWorldSession() = ccall((:G_InitWorldSession, lib), Void, (),  );
G_WriteSessionData() = ccall((:G_WriteSessionData, lib), Void, (),  );

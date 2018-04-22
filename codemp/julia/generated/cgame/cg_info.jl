CG_LoadingString( s_ ) = ccall((:CG_LoadingString, lib), Void, ( Ptr{Char},  ), s_ );
CG_LoadingItem( itemNum_ ) = ccall((:CG_LoadingItem, lib), Void, ( Int32,  ), itemNum_ );
CG_LoadingClient( clientNum_ ) = ccall((:CG_LoadingClient, lib), Void, ( Int32,  ), clientNum_ );
CG_DrawInformation() = ccall((:CG_DrawInformation, lib), Void, (),  );
CG_LoadBar() = ccall((:CG_LoadBar, lib), Void, (),  );

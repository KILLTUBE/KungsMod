G_Alloc( size_ ) = ccall((:G_Alloc, lib), Void, ( Int32,  ), size_ );
G_InitMemory() = ccall((:G_InitMemory, lib), Void, (),  );
Svcmd_GameMem_f() = ccall((:Svcmd_GameMem_f, lib), Void, (),  );

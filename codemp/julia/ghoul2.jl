type Ghoul2
	ptrptr::Ptr{Ptr{Int64}}
end
function ghoul2(entity::AbstractEntity)::Ghoul2
	ptrptr = ccall((:cgentity_ghoul2, lib), Ptr{Ptr{Int64}}, (Ptr{centity_t},), cgentity(entity))
	return Ghoul2(ptrptr)
end
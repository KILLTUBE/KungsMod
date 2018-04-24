type Ghoul2
	ptrptr::Ptr{Ptr{Int64}}
end

function ghoul2(entity::AbstractEntity)::Ghoul2
	ptrptr = ccall((:cgentity_ghoul2, lib), Ptr{Ptr{Int64}}, (Ptr{centity_t},), cgentity(entity))
	return Ghoul2(ptrptr)
end

function mItem(ghoul2::Ghoul2)::Int32
	ccall( (:ghoul2_mitem,lib), Int32, (Ptr{Ptr{Int64}},), ghoul2.ptrptr)
end

clean!(ghoul2::Ghoul2) = ccall( (:CL_G2API_CleanGhoul2Models, lib), Void, (Ptr{Ptr{Int64}}, ), ghoul2.ptrptr)


# CL_G2API_AddBolt( void *ghoul2, int modelIndex, const char *boneName ) 

addBolt!(ghoul2::Ghoul2, modelIndex, boneName) = ccall( (:CL_G2API_AddBolt, lib), Int32, (Ptr{Int64}, Int32, Cstring), unsafe_load(ghoul2.ptrptr), modelIndex, boneName)


#CCALL void *ghoul2_get_ghoulentry(void **ghoul2_ptr, int entryid) {

type GhoulEntry
	ptr::Ptr{Int64}
end

function getGhoulEntry(ghoul2::Ghoul2, entryid)::GhoulEntry
	ptr = ccall( (:ghoul2_get_ghoulentry, lib), Ptr{Int64}, (Ptr{Ptr{Int64}}, Int32), ghoul2.ptrptr, entryid)
	GhoulEntry(ptr)
end

#CCALL char *ghoulentry_get_filename(CGhoul2Info *ghoulentry) {
valid(ghoulentry::GhoulEntry) = ghoulentry.ptr != C_NULL



function filename(ghoulentry::GhoulEntry)::String
	if ! valid(ghoulentry)
		throw(ArgumentError("ghoulentry.ptr == NULL"))
	end
	cstr = ccall( (:ghoulentry_get_filename,lib), Cstring, (Ptr{Int64},), ghoulentry.ptr)
	return unsafe_string( cstr )
end

if false
	g2 = ghoul2(player)
	mItem(ghoul2(player1))
	g2.ptrptr
	clean!(g2)
	addBolt!(g2, 0, "*r_hand") # 0
	addBolt!(g2, 0, "*l_hand") # 1
	addBolt!(g2, 0, "r_handa") # 17
	addBolt!(g2, 0, "l_handa") # 18
	ghoulentry = getGhoulEntry(g2, 2)
	filename( getGhoulEntry(g2, 0) ) # models/players/jedi_zf/model.glm
	filename( getGhoulEntry(g2, 1) ) # models/weapons2/saber_6/saber_6.glm
	filename( getGhoulEntry(g2, 2) ) # 
end


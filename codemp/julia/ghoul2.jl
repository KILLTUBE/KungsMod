type Ghoul2
	ptrptr::Ptr{Ptr{Int64}}
end

function ghoul2(entity::AbstractEntity)::Ghoul2
	ptrptr = ccall((:cgentity_ghoul2, lib), Ptr{Ptr{Int64}}, (Ptr{centity_t},), cgentity(entity))
	return Ghoul2(ptrptr)
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

function boltListSize(ghoulentry::GhoulEntry)::Int64
	if ! valid(ghoulentry)
		throw(ArgumentError("ghoulentry.ptr == NULL"))
	end
	return ccall( (:ghoulentry_get_boltlist_size,lib), Int64, (Ptr{Int64},), ghoulentry.ptr)
end

#void *CG_G2WeaponInstance(centity_t *cent, int weapon)
CG_G2WeaponInstance(cent, weapon) = ccall( (:CG_G2WeaponInstance,lib), Ptr{Int64}, (Ptr{centity_t}, Int32), cent, weapon)


#CCALL void CL_G2API_CopySpecificGhoul2Model( void *g2From, int modelFrom, void *g2To, int modelTo ) {

CL_G2API_CopySpecificGhoul2Model(g2From, modelFrom, g2To, modelTo) = ccall( (:CL_G2API_CopySpecificGhoul2Model,lib), Void, (Ptr{Int64}, Int32, Ptr{Int64}, Int32), g2From, modelFrom, g2To, modelTo)

#CCALL int CL_G2API_InitGhoul2Model( void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin, qhandle_t customShader, int modelFlags, int lodBias )

function loadGhoul(filename)
	ptr = malloc(Int64)
	unsafe_store!(ptr, 0)
	handle = ccall( (:CL_G2API_InitGhoul2Model,lib), Int32, (Ptr{Int64}, Cstring, Int32, Int32, Int32, Int32, Int32), ptr, filename, 0, 0, 0, 0, 0)
	ghoulptr = unsafe_load(ptr)
	return (handle, ghoulptr)
end

function loadGhoul(entity::AbstractEntity, filename)
#	ptr = malloc(Int64)
#	unsafe_store!(ptr, 0)
	ptrptr = ghoul2(entity).ptrptr
	

	handle = ccall( (:CL_G2API_InitGhoul2Model,lib), Int32, (Ptr{Int64}, Cstring, Int32, Int32, Int32, Int32, Int32), ptrptr, filename, 0, 0, 0, 0, 0)
	#ghoulptr = unsafe_load(ptr)
	#return (handle, ghoulptr)
	return handle
end

#qboolean CL_G2API_AttachG2Model( void *ghoul2From, int modelIndexFrom, void *ghoul2To, int toBoltIndex, int toModel )

function CL_G2API_AttachG2Model(ghoul2From, modelIndexFrom, ghoul2To, toBoldIndex, toModel)::Int32
	ccall( (:CL_G2API_AttachG2Model,lib), Int32, (Ptr{Int64}, Int32, Ptr{Int64}, Int32, Int32), ghoul2From, modelIndexFrom, ghoul2To, toBoldIndex, toModel)
end

type GhoulInfo
	entity::AbstractEntity
	infoid::Int32
	function GhoulInfo(entity::AbstractEntity, infoid::Integer)
		ghoul2_ = ghoul2(entity)
		ghoulentry_ = getGhoulEntry(ghoul2_, infoid)
		if ! valid(ghoulentry_)
			throw(ArgumentError("ghoul model has no infoid $infoid"))
		end

		new(entity, infoid)
	end
end

type Bolt
	ghoulinfo::GhoulInfo
	boltname::String
	boltid::Int32
end

function getBolt(ghoulinfo::GhoulInfo, boltname::String)
	g2 = ghoul2(ghoulinfo.entity)
	boltid = addBolt!(g2, ghoulinfo.infoid, boltname)
	if boltid == -1
		throw(ArgumentError("boltname doesnt exist"))
	end
	return Bolt(ghoulinfo, boltname, boltid)
end


function addModel(bolt::Bolt, filename::String, infoid::Integer)
	ret = loadGhoul(filename)
	ghoulweapon = Ptr{Int64}(ret[2])
	

	g2 = ghoul2(bolt.ghoulinfo.entity)
	g2To = unsafe_load( g2.ptrptr )

	#CL_G2API_AttachG2Model( ghoulweapon, 0, g2To, bolt.boltid, infoid) # ghoul2From, modelIndexFrom, ghoul2To, toBoltIndex, toModel
	#CL_G2API_CopySpecificGhoul2Model(ghoulweapon, 0, g2To, infoid)

	# first we copy over the loaded ghoul model into our model
	CL_G2API_CopySpecificGhoul2Model(ghoulweapon, 0, g2To, infoid)
	# now we attach the loaded ghoulinfo to our bolt
	CL_G2API_AttachG2Model( g2To, infoid, g2To, bolt.boltid, bolt.ghoulinfo.infoid) # ghoul2From, modelIndexFrom, ghoul2To, toBoltIndex, toModel



	#CL_G2API_CopySpecificGhoul2Model(ghoulweapon, 0, g2To, infoid)
	#CL_G2API_AttachG2Model( ghoulweapon, 0, g2To, bolt.boltid, bolt.ghoulinfo.infoid) # ghoul2From, modelIndexFrom, ghoul2To, toBoltIndex, toModel

end

if false


	CL_G2API_AttachG2Model( ghoulweapon, 0, g2To, 1, 0)
	

	#ret = loadGhoul("models/flags/r_flag.md3") # crashes cuz md3?
	ret = loadGhoul("models/weapons2/demp2/demp2_w.glm")
	demp = Ptr{Int64}( ret[2] )


	g2 = ghoul2(player)


	

	ghoulInfoModel = GhoulInfo(player, 0)
	ghoulInfoSaber = GhoulInfo(player, 1)
	ghoulInfoExtra2 = GhoulInfo(player, 2)
	ghoulInfoExtra3 = GhoulInfo(player, 3)
	ghoulInfoExtra4 = GhoulInfo(player, 4)

	boltFace = getBolt(ghoulInfoModel, "face")
	boltLeftHand = getBolt(ghoulInfoModel, "*l_hand")
	boltRightArm = getBolt(ghoulInfoModel, "r_arma")


	CL_G2API_AttachG2Model( g2To, 1, g2To, boltFace.boltid, 0)
	CL_G2API_AttachG2Model( g2To, 1, g2To, boltLeftHand.boltid, 0)

	entrySaber = getGhoulEntry(g2, 1)
	boltListSize(entryModel)
	boltListSize(entrySaber)

	addModel(boltLeftHand,"models/weapons2/saber_6/saber_6.glm", 1)
	addModel(boltLeftHand,"models/players/jedi_zf/model.glm", 0)
	addModel(boltLeftHand,"models/weapons2/demp2/demp2_w.glm", 4)
	addModel(boltRightArm,"models/weapons2/bowcaster/bowcaster_w.glm", 2)
	addModel(boltRightArm,"models/weapons2/heavy_repeater/heavy_repeater_w.glm", 4)
	addModel(boltLeftHand,"models/weapons2/bowcaster/bowcaster_w.glm",4)

	bc_ret = loadGhoul("models/weapons2/bowcaster/bowcaster_w.glm")
	bc_ghoulweapon = Ptr{Int64}(bc_ret[2])
	g2 = ghoul2(player)
	g2To = unsafe_load( g2.ptrptr )
	CL_G2API_AttachG2Model( bc_ghoulweapon, 0, g2To, boltFace.boltid, 2) # ghoul2From, modelIndexFrom, ghoul2To, toBoltIndex, toModel
	CL_G2API_CopySpecificGhoul2Model(bc_ghoulweapon, 0, g2To, 2)
	CL_G2API_AttachG2Model( g2To, 2, g2To, boltFace.boltid, 0) # ghoul2From, modelIndexFrom, ghoul2To, toBoltIndex, toModel

 # ghoul2From, modelIndexFrom, ghoul2To, toBoltIndex, toModel
getGhoulEntry(g2, 3)
	GhoulInfo


	mItem(ghoul2(player1))
	g2.ptrptr
	clean!(g2)
	addBolt!(g2, 0, "*r_hand") # 0
	addBolt!(g2, 0, "*l_hand") # 1
	addBolt!(g2, 0, "r_handa") # 17
	addBolt!(g2, 0, "l_handa") # 18
	addBolt!(g2, 0, "face") # 8
	ghoulentry = getGhoulEntry(g2, 2)
	filename( getGhoulEntry(g2, 0) ) # models/players/jedi_zf/model.glm
	filename( getGhoulEntry(g2, 1) ) # models/weapons2/saber_6/saber_6.glm
	filename( getGhoulEntry(g2, 2) ) # 
	filename( getGhoulEntry(g2, 3) ) # 
	filename( getGhoulEntry(g2, 4) ) # 
	filename( getGhoulEntry(g2, 5) ) # 
	ghoulweapon = CG_G2WeaponInstance( cgentity(player), 4 ) # some ghoul2 Ptr{Int64}

	# CL_G2API_CopySpecificGhoul2Model(CG_G2WeaponInstance(cent, WP_SABER), 0, cent->ghoul2, 1);
	g2To = unsafe_load( g2.ptrptr )
	CL_G2API_CopySpecificGhoul2Model(ghoulweapon, 0, g2To, 2)



e = Entity()
pos!(e, pos(player))

unsafe_load(ghoul2(e).ptrptr)

saber = loadGhoul("models/weapons2/saber_6/saber_6.glm")
saberweapon = Ptr{Int64}(ret[2])
saberghoul = ghoul2(e)

unsafe_store!(saberghoul.ptrptr, saberweapon)




# trying to spawn an entity with glm model

entity = Entity()
gentity(e)
getGhoulEntry(g2, 0)
ptrptr = ccall((:gentity_ghoul2, lib), Ptr{Ptr{Int64}}, (Ptr{gentity_t},), gentity(entity))
g2 = Ghoul2(ptrptr)
entity_ghoul = unsafe_load(ptrptr)
filename_ = "models/weapons2/bowcaster/bowcaster_w.glm"
#GhoulInfo(entity, 0) # for cg
handle = ccall( (:CL_G2API_InitGhoul2Model,lib), Int32, (Ptr{Int64}, Cstring, Int32, Int32, Int32, Int32, Int32), ptrptr, filename_, 0, 0, 0, 0, 0)
pos!(entity, pos(player))

SV_LinkEntity(entity::AbstractEntity) = ccall( (:SV_LinkEntity,lib), Void, (Ptr{gentity_t},), gentity(entity))
SV_LinkEntity(entity)

CL_G2API_CopySpecificGhoul2Model(demp, 0, entity_ghoul, 0)
CL_G2API_CopySpecificGhoul2Model(ghoulweapon, 0, entity_ghoul, 2)
# i dont know yet how to spawn... maybe add bolts, or check weapon code for trip mines



model!(entity, "models/weapons2/saber_6/saber_6.glm")
model!(entity2, "models/weapons2/bowcaster/bowcaster_w.glm")

entity_c = Entity()
pos!(entity_c, pos(player))
model!(entity_c, "models/weapons2/bowcaster/bowcaster_w.glm")

entity_d = Entity()
pos!(entity_d, pos(player))
model!(entity_d, "models/players/jedi_zf/model.glm")
model!(entity_d, "models/players/jedi_zf/model_exported.glm")

animate(entity::AbstractEntity, frame_start, frame_stop, frame_flip) = ccall( (:jl_entity_animate,lib), Void, (Int32, Int32, Int32, Int32), id_c(entity), frame_start, frame_stop, frame_flip)

animate(entity_d, 100, 2000, 1)

end


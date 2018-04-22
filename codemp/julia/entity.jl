
abstract type SuperEntity end

abstract type AbstractEntity <: SuperEntity end

type Entity <: AbstractEntity
	id::Int32
	Entity(         ) = new( jl_g_spawn() + 1 ) # todo: check for no entities left
	Entity(id       ) = Entity( Int32(id) )
	function Entity(id::Int32)
		if id < 1 || id > 1024
			throw(ArgumentError("Entity(" * string(id) * "): invalid id, must be between 1 and 1024"))
		end
		new(id)
	end
end

abstract type AbstractPlayer <: AbstractEntity end

type Player <: AbstractPlayer
	id::Int32
	Player(         ) = new( G_AddBot() + 1)
	Player(id       ) = Player( Int32(id) )
	function Player(id::Int32)
		if id < 1 || id > 64
			throw(ArgumentError("Player(" * string(id) * "): invalid id, must be between 1 and 64"))
		end
		new(id)
	end
end

Player(entity::Entity) = Player(entity.id)

# doesnt work?
#convert(::Type{AbstractEntity}, address::Ptr{Int64}) = 321

function convert(::Type{Player}, address::Ptr{Int64})::Player
	c_id = Int32((address - jl_g_entities()) / jl_g_entities_sizeof())
	Player(c_id + 1)
end
function convert(::Type{Entity}, address::Ptr{Int64})::Entity
	c_id = Int32((address - jl_g_entities()) / jl_g_entities_sizeof())
	Entity(c_id + 1)
end
#convert(Player, gentity(player2))

jl_g_spawn() = ccall((:jl_g_spawn, lib), Int32, ())
G_AddBot() = ccall((:G_AddBot,lib), Int32, ())

function player_get_velocity(id::Int32)::Vec3
	vecptr = ccall((:jl_player_get_velocity, lib), Ptr{Vec3}, (Int32,), id)
	return unsafe_load(vecptr)
end
player_set_velocity(id::Int32, velocity::Vec3)::Void = ccall((:jl_player_set_velocity, lib), Void, (Int32,Ptr{Float32}), id, pointer(velocity))

test_vec3(vec3::Vec3)::Void = ccall((:jl_test_vec3, lib), Void, (Vec3,), vec3)

function player_get_viewangles(id::Int32)::Vec3
	vecptr = ccall((:jl_player_get_viewangles, lib), Ptr{Vec3}, (Int32,), id)
	return unsafe_load(vecptr)
end
player_set_viewangles(id::Int32, velocity::Vec3)::Void = ccall((:jl_player_set_viewangles, lib), Void, (Int32,Ptr{Float32}), id, pointer(velocity))

function entity_get_angles(id::Int32)::Vec3
	vecptr = ccall((:jl_entity_get_angles, lib), Ptr{Vec3}, (Int32,), id)
	return unsafe_load(vecptr)
end
entity_set_angles(id::Int32, angles::Vec3)::Void = ccall((:jl_entity_set_angles, lib), Void, (Int32, Ptr{Float32}), id, pointer(angles))

# I kinda want this for Entity only, but I cant subtype Teddy <: Entity
angles( this::AbstractEntity           ) = entity_get_angles(id_c(this))
angles!(this::AbstractEntity, vec::Vec3) = entity_set_angles(id_c(this), vec)



function vectoangles(normal::Vec3)::Vec3
	angles = Float32[1,2,3]
	ccall((:vectoangles, lib), Void, (Vec3,Ptr{Float32}), normal, pointer(angles,1))
	return Vec3(angles[1], angles[2], angles[3])
end

#vectoangles(Vec3(0,1,0))

# our C FFI is zero indexed, since thats the land of C
entity_moveto(id::Int32, to::Vec3, durationSeconds::Float32) = ccall((:jl_entity_moveto, lib), Int32, (Int32, Ptr{Float32}, Float32), id, pointer(to), durationSeconds)
entity_get_pos(id::Int32) = ccall((:jl_entity_get_pos, lib), Vec3, (Int32,), id)
entity_set_pos(id::Int32, pos::Vec3) = ccall((:jl_entity_set_pos, lib), Void, (Int32,Ptr{Float32}), id, pointer(pos))
entity_set_model(id::Int32, model::AbstractString) = ccall((:jl_entity_set_model, lib), Int32, (Int32,Cstring), id, model)
entity_inuse(id::Int32) = ccall((:jl_entity_inuse, lib), Int32, (Int32,), id)

#setTeam(player1, "s")
#setTeam(player1, "r")
#setTeam(player1, "b")
setTeam(player::Player, team::AbstractString) = ccall((:SetTeam, lib), Void, (Ptr{Int64},Cstring), gentity(player), team)

# int jl_entity_send_hud(int playerid, int left, int top, int width, int height, float r, float g, float b, float a, char *text)
# entity_send_hud(0, 20, 30, 100, 20, 1.0, 0.0, 0.0, 0.5, "hurri durri")
function entity_send_hud(id::Int32, left::Int32, top::Int32, width::Int32, height::Int32, r::Float32, g::Float32, b::Float32, a::Float32, text::AbstractString)::Int32
	ccall((:jl_entity_send_hud, lib), Int32, (Int32,Int32,Int32,Int32,Int32,Float32,Float32,Float32,Float32,Cstring), id, left, top, width, height, r, g, b, a, text)
end

# entity_update_hud(Int32(0), Int32(1), Int32(20), Int32(30), Int32(100), Int32(20), Float32(1.0), Float32(0.0), Float32(0.0), Float32(0.5), "hurri")
function entity_update_hud(playerid::Int32, hudid::Int32, left::Int32, top::Int32, width::Int32, height::Int32, r::Float32, g::Float32, b::Float32, a::Float32, text::AbstractString)::Void
	ccall((:jl_entity_update_hud, lib), Void, (Int32,Int32,Int32,Int32,Int32,Int32,Float32,Float32,Float32,Float32,Cstring), playerid, hudid, left, top, width, height, r, g, b, a, text)
end

function player_hudelem_settext(playerid::Int32, hudid::Int32, text::AbstractString)::Void
	ccall((:jl_player_hudelem_settext, lib), Void, (Int32,Int32,Cstring), playerid, hudid, text)
	nothing
end
function player_hudelem_hide(playerid::Int32, hudid::Int32)::Void
	ccall((:jl_player_hudelem_hide, lib), Void, (Int32,Int32), playerid, hudid)
	nothing
end
function player_hudelem_show(playerid::Int32, hudid::Int32)::Void
	ccall((:jl_player_hudelem_show, lib), Void, (Int32,Int32), playerid, hudid)
	nothing
end
function player_hudelem_free(playerid::Int32, hudid::Int32)::Void
	ccall((:jl_player_hudelem_free, lib), Void, (Int32,Int32), playerid, hudid)
	nothing
end

player_attackbuttonpressed(id::Int32) = ccall((:jl_player_attackbuttonpressed, lib), Int32, (Int32,), id)
player_usebuttonpressed(   id::Int32) = ccall((:jl_player_usebuttonpressed   , lib), Int32, (Int32,), id)
player_walkbuttonpressed(  id::Int32) = ccall((:jl_player_walkbuttonpressed  , lib), Int32, (Int32,), id)
player_aimbuttonpressed(   id::Int32) = ccall((:jl_player_aimbuttonpressed   , lib), Int32, (Int32,), id)
player_nadebuttonpressed(  id::Int32) = ccall((:jl_player_nadebuttonpressed  , lib), Int32, (Int32,), id)
player_forward(id::Int32) = ccall((:jl_player_forward, lib), Vec3, (Int32,), id)
player_viewheight(id::Int32) = ccall((:jl_player_viewheight, lib), Int32, (Int32,), id)

(==)(a::AbstractEntity, b::AbstractEntity)::Bool = a.id == b.id

# pos!(Entity(0), Vec3(1,2,3))
# pos(Entity(0))

function movetoVelocity!(this::AbstractEntity, to::Vec3, velocity::Float32)::Float32
	# velocity = distance / time, e.g. a car, velocity = 100km / 1 hour
	distance_ = distance( pos(this), to)
	time = distance_ / velocity
	#println(this, " is at ", pos(this), " distance is ", distance_, " time is ", time)
	entity_moveto(Int32(this.id - 1), to, Float32(time))
	time
end
function moveto!(this::AbstractEntity, pos::Vec3, durationSeconds)::Void
	entity_moveto(Int32(this.id - 1), pos, Float32(durationSeconds))
	nothing
end
function pos(this::AbstractEntity)::Vec3
	entity_get_pos(Int32(this.id - 1))
end
function pos!(this::AbstractEntity, pos::Vec3)::Void
	entity_set_pos(Int32(this.id - 1), pos)
	nothing
end

# todo: set model on a player
function model!(this::AbstractEntity, model::AbstractString)::Int32
	entity_set_model(Int32(this.id - 1), model)
end

function gentity(this::AbstractEntity)::Ptr{Int64}
	return jl_g_entities() + id_c(this) * jl_g_entities_sizeof()
end

EV_GENERAL_SOUND = Int32(45)
# playSound(player1, "sound/cash_register_open_coins_cha_ching_01.wav")
function playSound(this::AbstractEntity, soundname::AbstractString)::Void
	soundNum = G_SoundIndex(soundname)
	G_AddEvent(gentity(this), EV_GENERAL_SOUND, soundNum)
	nothing
end

function printBold(this::Player, args...)
	text = ""
	for arg in args
		text *= string(arg) * " "
	end
	SV_SendServerCommand(id_c(this), "cp " * text)
end
function print(this::Player, text::AbstractString)
	SV_SendServerCommand(id_c(this), "print " * string(text))
end
if false
	print(player1, "hurr durr asddddddddddddd")
	printBold(player1, "hurr durr asddddddddddddd")
end

inuse(this::AbstractEntity)::Bool = entity_inuse(Int32(this.id - 1)) === Int32(1)

# only works on players, since it dereferences "client", which is NULL for normal entities
attackButtonPressed(this::Player)::Bool = player_attackbuttonpressed(Int32(this.id - 1)) !== Int32(0)
useButtonPressed(   this::Player)::Bool = player_usebuttonpressed(   Int32(this.id - 1)) !== Int32(0)
walkButtonPressed(  this::Player)::Bool = player_walkbuttonpressed(  Int32(this.id - 1)) !== Int32(0)
aimButtonPressed(   this::Player)::Bool = player_aimbuttonpressed(   Int32(this.id - 1)) !== Int32(0)
nadeButtonPressed(  this::Player)::Bool = player_nadebuttonpressed(  Int32(this.id - 1)) !== Int32(0)

health( player::Player     ) = ccall((:player_get_health,lib), Int32, (Ptr{Int64},      ), gentity(player)            )
health!(player::Player, val) = ccall((:player_set_health,lib),  Void, (Ptr{Int64}, Int32), gentity(player), Int32(val))
team(   player::Player     ) = ccall((:player_get_team  ,lib), Int32, (Ptr{Int64},      ), gentity(player)            )
team!(  player::Player, val) = ccall((:player_set_team  ,lib),  Void, (Ptr{Int64}, Int32), gentity(player), Int32(val))
score(  player::Player     ) = ccall((:player_get_score ,lib), Int32, (Ptr{Int64},      ), gentity(player)            )
score!( player::Player, val) = ccall((:player_set_score ,lib),  Void, (Ptr{Int64}, Int32), gentity(player), Int32(val))
deaths( player::Player     ) = ccall((:player_get_deaths,lib), Int32, (Ptr{Int64},      ), gentity(player)            )
deaths!(player::Player, val) = ccall((:player_set_deaths,lib),  Void, (Ptr{Int64}, Int32), gentity(player), Int32(val))
if false

	health!(player1, 101)
	health(player1)
	team(player1)
	team!(player1, 0)
	score(player1)
	score!(player1, 4)
	deaths(player1)
	deaths!(player1, 444)

end

forward(  this::Player)::Vec3 = player_forward(  Int32(this.id - 1))
viewheight(  this::Player)::Int32 = player_viewheight(  Int32(this.id - 1))

id_c(this::AbstractEntity) = Int32(this.id - 1)

vel(this::Player)::Vec3 = player_get_velocity( id_c(this) )
vel!(this::Player, vec::Vec3)::Void = player_set_velocity( id_c(this), vec )

free(this::AbstractEntity) = ccall( (:G_FreeEntity,lib), Void, (Ptr{Int64},), gentity(this))

angles(this::Player)::Vec3             = player_get_viewangles( id_c(this) )
angles!(this::Player, vec::Vec3)::Void = player_set_viewangles( id_c(this), vec )

function getEye(player::Player)::Vec3
	pos(player) + Vec3(0,0,viewheight(player))
end

# sendHud(player1, 20, 30, 100, 20, 1.0, 0.0, 0.0, 0.5, "hurri durri")
function sendHud(this::Player, left, top, width, height, r, g, b, a, text)::Int32
	entity_send_hud(Int32(this.id - 1), Int32(left), Int32(top), Int32(width), Int32(height), Float32(r), Float32(g), Float32(b), Float32(a), text)
end

# hudSetText(player1, 0, "haiii")
function hudSetText(this::Player, hudid, text)::Void
	player_hudelem_settext(Int32(this.id - 1), Int32(hudid), text)
	nothing
end
# hudHide(player1, 0)
function hudHide(this::Player, hudid)::Void
	player_hudelem_hide(Int32(this.id - 1), Int32(hudid))
	nothing
end
# hudShow(player1, 0)
function hudShow(this::Player, hudid)::Void
	player_hudelem_show(Int32(this.id - 1), Int32(hudid))
	nothing
end
# hudFree(player1, 0)
function hudFree(this::Player, hudid)::Void
	player_hudelem_free(Int32(this.id - 1), Int32(hudid))
	nothing
end

players = Player[]
for i in range(1, 1, 64)
	push!(players, Player(i))
end

function onDisconnect(player::Player)
	notify(player, "disconnect")
	log(console, player, "disconnected")
	deletePlayerTeddies(player) # todo: make this stuff mod specific
end

function disconnect(player::Player)
	onDisconnect(player)
	ccall( (:ClientDisconnect          , lib), Void      , (Int32,                                         ), id_c(player)           );
end

player = players[1] # very handy in lots of functions
player1 = players[1]
player2 = players[2]
player3 = players[3]
player4 = players[4]

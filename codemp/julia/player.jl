if !isdefined(:playersTeam)
	playersTeam = zeros(Int32, 64)
end


init(player::Player) = ccall((:G_InitGentity,lib), Void, (Ptr{Int64},), gentity(player))
spawn(player::Player) = ccall((:ClientSpawn,lib), Void, (Ptr{Int64},), gentity(player))


#TEAM_FREE=0, TEAM_RED=1, TEAM_BLUE=2, TEAM_SPECTATOR=3
# implemented this in entity.jl now, which is using quake3 ccalls

#team(this::Player) = playersTeam[this.id]
#team!(this::Player, team) = team!(this, Int32(team))
#function team!(this::Player, team::Int32)::Void
#	playersTeam[this.id] = team
#	nothing
#end

if false
	team(player1)
	team!(player1, 0)
end

spec!(this::Player) = team!(this, Int32(3))

hunter(this::Player) = team(this) == Int32(1)
hunter!(this::Player) = team!(this, Int32(1))
zombie( this::Player) = team(this) == Int32(2)
zombie!(this::Player) = team!(this, Int32(2))

isBot(player::AbstractPlayer) = ccall((:player_isbot,lib), Int32, (Ptr{Int64}, ), gentity(player)) != Int32(0)

if false
	spec!(player1)
	hunter(player1)
	hunter!(player1)
	zombie!(player1)
	zombie(player1)
end

team!(player1, 2)

# void player_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath )


function die(self::Player, inflictor::AbstractEntity, attack::AbstractEntity, damage::Int32, meansOfDeath::Int32)
	ccall( (:player_die, lib), Void,
		(Ptr{Int64}, Ptr{Int64}, Ptr{Int64}, Int32, Int32),
			gentity(self), gentity(inflictor), gentity(attack), damage, meansOfDeath
	)
end

DAMAGE_NO_ARMOR = Int32(2)

function kill(player::Player)
	damage(player, player, player, Vec3(0,0,0), Vec3(0,0,0), Int32(2000), DAMAGE_NO_ARMOR, Int32(6))
end

if false
	kill(player1)
	die(player1, player1, player1, Int32(1110), Int32(6))
	damage(player1, player1, player1, Vec3(0,0,0), Vec3(0,0,0), Int32(40), DAMAGE_NO_ARMOR, Int32(6))
end

# void G_Damage( gentity_t *targ, gentity_t *inflictor, gentity_t *attacker, vec3_t dir, vec3_t point, int damage, int dflags, int mod )

function damage(self::Player, inflictor::AbstractEntity, attack::AbstractEntity, dir::Vec3, point::Vec3, damage::Int32, dflags::Int32, meansOfDeath::Int32)
	ccall( (:G_Damage, lib), Void,
		(Ptr{Int64}, Ptr{Int64}, Ptr{Int64}, Ptr{Float32}, Ptr{Float32}, Int32, Int32, Int32),
			gentity(self), gentity(inflictor), gentity(attack), pointer(dir), pointer(point), damage, dflags, meansOfDeath
	)
end

# functional programming kinda... maybe composeable? zombie! = forEachPlayerInUse(zombie!)
function zombie!(players::Vector{Player})
	for player in players
		if ! inuse(player)
			continue
		end
		zombie!(player)
	end
end
function hunter!(players::Vector{Player})
	for player in players
		if ! inuse(player)
			continue
		end
		hunter!(player)
	end
end

if false
	zombie!(players)
	hunter!(players)
end



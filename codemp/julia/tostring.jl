include("lexer_c.jl")
include("ctypes.jl")

import Glob

#type MetaVar
#	name::String
#	#vartype::DataType
#	typestring::String
#	isConst::Bool
#	isStatic::Bool
#	isStruct::Bool
#	numPointer::Int32 # 0 is "int foo"    1 is "int *foo"    2 is "int **foo"    etc.
#	dimensionA_startTokenPos::Int32 # -1 if no dimension
#	dimensionB_startTokenPos::Int32 # -1 if no dimension
#	function MetaVar()
#		new("", "", false, false, false, 0, -1, -1)
#	end
#end

function tostring(parser::Parser, metaVar::MetaVar)
	ret = ""
	
	# special case, simply return
	if metaVar.isVarArgs
		return "..."
	end
	
	if metaVar.isExtern
		ret *= "extern "
	end
	if metaVar.isEXTERNC
		ret *= "EXTERNC "
	end
	if metaVar.isCCALL
		ret *= "CCALL "
	end
	if metaVar.isQDECL
		ret *= "QDECL "
	end
	if metaVar.isQINLINE
		ret *= "QINLINE "
	end
	if metaVar.isConst
		ret *= "const "
	end
	if metaVar.isStatic
		ret *= "static "
	end
	if metaVar.isUnsigned
		ret *= "unsigned "
	end
	if metaVar.isStruct
		ret *= "struct "
	end

	ret *= metaVar.typestring
	
	ret *= " "
	ret *= "*" ^ metaVar.numPointer
	
	# meh, not used for MetaFunctions... but for vars... i should make a MetaType, a MetaVar = name + MetaType
	ret *= metaVar.name
	
	if metaVar.dimensionA_startTokenPos != -1
		ret *= "["
		tokStart = parser.tokens[ metaVar.dimensionA_startTokenPos ]
		if typeof(tokStart) <: TokenSquareBracketClose
			# its simply nothing, like int foo[]
		else
			ret *= tokStart.str
		end
		ret *= "]"
	end
	
	return ret
end

function tostring(parser::Parser, metaFunction::MetaFunction)
	ret = tostring(parser, metaFunction.metaVar) # * metaFunction.name
	
	if length(metaFunction.args) > 0
		ret *= "( "
		lastOne = last(metaFunction.args)
		for arg in metaFunction.args
			ret *= tostring(parser, arg)
			if arg != lastOne
				ret *= ", "
			end
		end
		ret *= " )"
	else
		ret *= "()"
	end
	
	ret *= ";"
	
	ret
end

function cToJuliaType(ctype)
	if ctype == "int"
		return "Int32"
	end
	if ctype == "float"
		return "Float32"
	end
	if ctype == "void"
		return "Void"
	end
	if ctype == "char"
		return "Char"
	end
	if ctype == "short"
		return "Int16"
	end
	return ctype
end

function toStringJuliaType(metaVar::MetaVar)::String
	ret = ""
	for i in range(1, metaVar.numPointer)
		ret *= "Ptr{"
	end
	
	ret *= cToJuliaType( metaVar.typestring )
	
	for i in range(1, metaVar.numPointer)
		ret *= "}"
	end
	
	ret
end

function toccall(parser::Parser, metaFunction::MetaFunction)
	ret = "" # * tostring(parser, metaFunction.metaVar) # * metaFunction.name

	funcname = metaFunction.metaVar.name
	rettype = cToJuliaType(metaFunction.metaVar.typestring)
	
	ignoreThisFunc = false
	for arg in metaFunction.args
		if arg.isVarArgs
			ignoreThisFunc = true
			break
		end
	end
	if funcname == "BG_VehicleAdjustBBoxForOrientation" # meh gotta add callback stuff later
		ignoreThisFunc = true
	end
	if ignoreThisFunc
		ret *= "#" # ignore varargs, idk yet how to ccall it
	end
	
	
	ret *= funcname
	
	if length(metaFunction.args) > 0
		ret *= "( "
		lastOne = last(metaFunction.args)
		for arg in metaFunction.args
			#ret *= tostring(parser, arg)
			ret *= arg.name * "_" # add _ to prevent name collisions with julia keywords, like "end"
			if arg != lastOne
				ret *= ", "
			end
		end
		ret *= " )"
	else
		ret *= "()"
	end
	
	ret *= " = ccall((:$funcname, lib), $rettype, "
	
	
	if length(metaFunction.args) > 0
		ret *= "( "
		lastOne = last(metaFunction.args)
		for arg in metaFunction.args
			#ret *= tostring(parser, arg)
			ret *= toStringJuliaType(arg)
			#if arg != lastOne
				ret *= ", "
			#end
		end
		ret *= " )"
	else
		ret *= "()"
	end	
	
	ret *= ", "
	
	if length(metaFunction.args) > 0
		lastOne = last(metaFunction.args)
		for arg in metaFunction.args
			#ret *= tostring(parser, arg)
			ret *= arg.name * "_" # add _ to prevent name collisions with julia keywords, like "end"
			if arg != lastOne
				ret *= ", "
			end
		end
	end	
	ret *= " )"
	
	ret *= ";"
	
	ret
end


function file_put_contents(filename, content)
	f = open(filename, "w")
	write(f, content)
	close(f)
end


# generateHeader("C:\\OpenSciTech\\codemp\\cgame\\cg_main.cpp")
function generateHeader(filename)
	bn             = basename(filename)                                 # something like "cg_main.cpp"
	pureName       = first(split(bn, '.'))                              # something like "cg_main"
	headerName     = pureName * ".h"                                    # something like "cg_main.h"
	dn             = dirname(filename)                                  # something like "C:\\OpenSciTech\\codemp\\cgame"
	lastFolderName = last(split(dn, '\\'))                              # something like "cgame"
	prevFolder     = abspath(dn * "\\..")                               # something like "C:\\OpenSciTech\\codemp\\"
	fullGenFolder  = prevFolder * "generated\\" * lastFolderName * "\\" # something like "C:\\OpenSciTech\\codemp\\generated\\cgame\\"
	genName        = fullGenFolder * headerName                         # something like "C:\\OpenSciTech\\codemp\\generated\\cgame\\cg_main.cpp"
	
	# only game and cgame files atm
	if ! ( startswith(pureName, "g_") || startswith(pureName, "cg_"))
		#return
	end
	
	println("generateHeader( \"" * filename * "\"")
	
	sourcecode = file_get_contents(filename)
	parser = parseC(sourcecode)
	tmp = ""
	for func_ in parser.functions
		tmp *= tostring(parser, func_) * "\n"
	end
	
	file_put_contents(genName, tmp)
	return parser
end

function generateJuliaHeader(filename)
	bn             = basename(filename)                                 # something like "cg_main.cpp"
	pureName       = first(split(bn, '.'))                              # something like "cg_main"
	headerName     = pureName * ".jl"                                   # something like "cg_main.jl"
	dn             = dirname(filename)                                  # something like "C:\\OpenSciTech\\codemp\\cgame"
	lastFolderName = last(split(dn, '\\'))                              # something like "cgame"
	prevFolder     = abspath(dn * "\\..")                               # something like "C:\\OpenSciTech\\codemp\\"
	fullGenFolder  = prevFolder * "julia\\generated\\" * lastFolderName * "\\" # something like "C:\\OpenSciTech\\codemp\\generated\\cgame\\"
	genName        = fullGenFolder * headerName                         # something like "C:\\OpenSciTech\\codemp\\generated\\cgame\\cg_main.cpp"
	
	# only game and cgame files atm
	if ! ( startswith(pureName, "g_") || startswith(pureName, "cg_"))
		#return
	end
	
	println("generateJuliaHeader( \"" * filename * "\" )")
	
	sourcecode = file_get_contents(filename)
	parser = parseC(sourcecode)
	tmp = ""
	for func_ in parser.functions
		tmp *= toccall(parser, func_) * "\n"
	end
	
	file_put_contents(genName, tmp)
	return parser
end


mode = 5

if mode == 1
	files_cgame = Glob.glob("*.cpp", "C:\\OpenSciTech\\codemp\\cgame\\")
	for filename in files_cgame
		generateHeader(filename)
	end
end
if mode == 3
	files_cgame = Glob.glob("*.cpp", "C:\\OpenSciTech\\codemp\\game\\")
	for filename in files_cgame
		
		generateHeader(filename)
	end
end

if mode == 4
	files_cgame = Glob.glob("*.cpp", "C:\\OpenSciTech\\codemp\\game\\")
	includefile = ""
	for filename in files_cgame
		bn             = basename(filename)                                 # something like "cg_main.cpp"
		pureName       = first(split(bn, '.'))                              # something like "cg_main"
		headerName     = pureName * ".jl"                                   # something like "cg_main.jl"		
		includefile *= "include(\"game/$headerName\")\n"
		generateJuliaHeader(filename)
	end
	file_put_contents("generated/game.jl", includefile)
end

function genJulia(dir_)
	files_cgame = Glob.glob("*.cpp", dir_)
	includefile = ""
	
	dir_bn             = basename(dir_)                            # something like "cg_main.cpp"
	dir_pureName       = first(split(dir_bn, '.'))                     # something like "cg_main"
	dir_headerName     = dir_pureName * ".jl"                          # something like "cg_main.jl"
	dir_dn             = dirname(dir_)                                 # something like "C:\\OpenSciTech\\codemp\\cgame"
	dir_lastFolderName = last(split(dir_dn, '\\'))                     # something like "cgame"	
	
	for filename in files_cgame
		bn             = basename(filename)                                 # something like "cg_main.cpp"
		pureName       = first(split(bn, '.'))                              # something like "cg_main"
		headerName     = pureName * ".jl"                                   # something like "cg_main.jl"
		dn             = dirname(filename)                                  # something like "C:\\OpenSciTech\\codemp\\cgame"
		lastFolderName = last(split(dn, '\\'))                              # something like "cgame"
		includefile *= "include(\"$lastFolderName/$headerName\")\n"
		generateJuliaHeader(filename)
	end
	file_put_contents("generated/$dir_lastFolderName.jl", includefile)
end

if mode == 2
	parser = generateHeader("C:\\OpenSciTech\\codemp\\game\\NPC.cpp")
end

genJulia("C:\\OpenSciTech\\codemp\\game\\")
genJulia("C:\\OpenSciTech\\codemp\\cgame\\")

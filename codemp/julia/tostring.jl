include("lexer_c.jl")
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

function tostring(metaVar::MetaVar)
	ret = ""
	
	if metaVar.isConst
		ret *= "const "
	end
	if metaVar.isStatic
		ret *= "static "
	end
	if metaVar.isStruct
		ret *= "struct "
	end
	ret *= metaVar.typestring
	
	ret *= " "
	ret *= "*" ^ metaVar.numPointer
	
	# meh, not used for MetaFunctions... but for vars... i should make a MetaType, a MetaVar = name + MetaType
	ret *= metaVar.name
		
end

function tostring(metaFunction::MetaFunction)
	ret = tostring(metaFunction.metaVar) * metaFunction.name
	
	if length(metaFunction.args) > 0
		ret *= "( "
		lastOne = last(metaFunction.args)
		for arg in metaFunction.args
			ret *= tostring(arg)
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


function file_put_contents(filename, content)
	f = open(filename, "w")
	write(f, content)
	close(f)
end


# generateHeader("C:\\OpenSciTech\\codemp\\cgame\\cg_main.cpp")
function generateHeader(filename)
	bn             = basename(filename)                                      # something like "cg_main.cpp"
	dn             = dirname(filename)                                       # something like "C:\\OpenSciTech\\codemp\\cgame"
	lastFolderName = last(split(dn, '\\'))                                   # something like "cgame"
	prevFolder     = abspath(dn * "\\..")                                    # something like "C:\\OpenSciTech\\codemp\\"
	genName        = prevFolder * "generated\\" * lastFolderName * "\\" * bn # something like "C:\\OpenSciTech\\codemp\\generated\\cgame\\cg_main.cpp"
	
	println("generateHeader( \"" * filename * "\"")
	
	sourcecode = file_get_contents(filename)
	parser = parseC(sourcecode)
	tmp = ""
	for func_ in parser.functions
		tmp *= tostring(func_) * "\n"
	end
	
	file_put_contents(genName, tmp)
end



if false
	files_cgame = Glob.glob("*.cpp", "C:\\OpenSciTech\\codemp\\cgame\\")
	for filename in files_cgame
		generateHeader(filename)
	end
else
	generateHeader("C:\\OpenSciTech\\codemp\\cgame\\cg_effects.cpp")
end




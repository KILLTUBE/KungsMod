include("php_trim.jl")
include("tokenizer.jl")

file_get_contents(name) = String(read(name))


content = file_get_contents("C:\\OpenSciTech\\codemp\\cgame\\cg_main.cpp")
#content = file_get_contents("enums.cpp")

tokens = tokenize(content)

isOpStar(    token::Token) = typeof(token) <: TokenOp         && token.str == "*"        # just for pointer detection
isOpStarStar(token::Token) = typeof(token) <: TokenOp         && token.str == "**"       # just for pointer detection

# collect data of C vars while parsing over it
type MetaVar
	name::String
	#vartype::DataType
	typestring::String
	isConst::Bool
	isStatic::Bool
	isStruct::Bool
	numPointer::Int32 # 0 is "int foo"    1 is "int *foo"    2 is "int **foo"    etc.
	dimensionA_startTokenPos::Int32 # -1 if no dimension
	dimensionB_startTokenPos::Int32 # -1 if no dimension
	function MetaVar()
		new("", "", false, false, false, 0, -1, -1)
	end
end

# just to collect the data of a struct while parsing over it
type MetaStruct
	name::String
	vars::Vector{MetaVar}
	function MetaStruct()
		new("", Vector{MetaVar}())
	end
end

type MetaFunction
	name::String
	metaVar::MetaVar
	args::Vector{MetaVar}
	#statements::Vector{MetaStatement} or whatever
	function MetaFunction()
		new("unnamed", MetaVar(), Vector{MetaVar}())
	end
end
type MetaPrototype
	name::String
	metaVar::MetaVar
	args::Vector{MetaVar}
	function MetaPrototype()
		new("unnamed", MetaVar(), Vector{MetaVar}())
	end
end

type Parser
	i::Int32
	tokens::Vector{Token}
	structs::Vector{MetaStruct}
	functions::Vector{MetaFunction}
	prototypes::Vector{MetaPrototype}
	globalVars::Vector{MetaVar}
	function Parser(tokenizer::Tokenizer)
		new(
			1,
			tokenizer.tokens,
			Vector{MetaStruct}(),
			Vector{MetaFunction}(),
			Vector{MetaPrototype}(),
			Vector{MetaVar}()
		)
	end
end

currentToken(parser::Parser) = parser.tokens[ parser.i ]
nextTokenType(parser::Parser) = typeof(parser.tokens[parser.i + 1])

function newStruct(parser::Parser, name::String)::MetaStruct
	ms = MetaStruct()
	ms.name = name
	push!( parser.structs, ms )
	return ms
end

type vec3_t
	x::Float32
	y::Float32
	z::Float32
end

function cStringToJuliaType(string::String)
	if string == "int"       return Int32   end
	if string == "float"     return Float32 end
	if string == "void"      return Void    end
	if string == "qboolean"  return Bool    end
	if string == "char"      return Char    end
	if string == "vec3_t"    return vec3_t  end
	println("cStringToJuliaType> i dont know ", string)
	return Any
end

function readType(parser::Parser)
	curTok = currentToken(parser)
	
	if isStruct(curTok)
	
		#print("readType> got a struct...\n")
		
		curTok = advance(parser) # token identifier, e.g. "testtype_s"
		#print("MakeStruct(", curTok.str, "\n")
		
		ms = newStruct(parser, curTok.str)
		advance(parser) # should be curly brace open
		
		
		while nextTokenType(parser) == TokenIdentifier
			# idea: tokType, tokName, semicolon = advance(TokenIdentifier, TokenIdentifier, TokenSemicolon)
			tokType   = advance(parser)
			tokName   = advance(parser)
			semicolon = advance(parser)
			
			mv = MetaVar()
			mv.vartype = cStringToJuliaType( tokType.str )
			mv.name = tokName.str
			push!( ms.vars, mv )
		end
		
		# idea: advanceAndExpect(parser, TokenCurlyBracketClose) or throw an error
		tokCurlyBracketClose = advance(parser)
		tokTypedefName       = advance(parser)
		tokSemicolon         = advance(parser)
		
		#debug(parser)
		return ms
	end

	return Void
end

function advance(parser::Parser)::Token
	parser.i += 1
	return currentToken(parser)
end

pos(parser::Parser) = parser.i
pos!(parser::Parser, i) = parser.i = Int32(i)


function debugPos(parser::Parser, pos::Int32)
	if (pos > 1)
		print("prev token pos=$pos> ", parser.tokens[pos - 1], "\n")
	end
	print("current token pos=$pos> ", parser.tokens[pos], "\n")
	# e.g. 3 tokens, 1, 2, 3, when i==2, we can show the next one
	if pos + 1 <= length(parser.tokens)
		print("next token pos=$pos> ", parser.tokens[pos + 1], "\n")
	end
end
function debug(parser::Parser)
	debugPos(parser, parser.i)
end

parser = Parser(tokens)

function getPosOfNextTokenType(parser::Parser, tokentype)::Int32
	from = parser.i
	while from <= length(parser.tokens)
		if typeof(parser.tokens[ from ]) == tokentype
			return from
		end
		from += 1
	end
	return -1
end

# metaVar is written into
function parseMetaTypeFromTo(parser::Parser, metaVar::MetaVar, from, to)

	# my god sometimes i hate this Julia nitpicking on fucking types, promotion shit from Int32/64 etc.
	from = Int32(from)
	to = Int32(to)
	
	pos = from
	while pos <= to
		token = parser.tokens[ pos ]
		
		if typeof(token) <: TokenIdentifier
			#metaVar.vartype = cStringToJuliaType(token.str) # meh do i need this for anything yet? atm just need this to generate nice headers
			metaVar.typestring = token.str
		elseif typeof(token) <: TokenStatic
			metaVar.isStatic = true
		elseif typeof(token) <: TokenConst
			metaVar.isConst = true
		elseif isOpStar(token)
			metaVar.numPointer += 1
		elseif isOpStarStar(token)
			metaVar.numPointer += 2
		else
			println("rekt in parseMetaTypeFromTo ", token)
			debugPos(parser, Int32(pos))
		end
		
		pos += 1
	end
end

function parseFunctionArguments(parser::Parser, metaFunction::MetaFunction, from, to)
	parseFunctionArguments(parser, metaFunction, Int32(from), Int32(to))
end
function parseFunctionArguments(parser::Parser, metaFunction::MetaFunction, from::Int32, to::Int32)
	numTokens = to - from
	# a function should contain zero or at least 2 tokens (type + name)
	# a special case is this void bullshit: int main(void)
	# but whatever, below 2 tokens = just ignore tokens between (...)
	if numTokens < 2
		return
	end
	
	argFrom = from
	argTo = to

	# shrink argTo if more than 1 argument
	nextCommaPos = getTokenPosByTypeBetweenFromTo(parser, TokenComma, from, to)
	if nextCommaPos != -1
		# if there is a comma, fit the argTo position
		argTo = nextCommaPos - 1
	end
	runOnceAgain = true
	# todo: it works, but quite ugly, i have better idea:
	# range = (from,to)
	# range = nextRange(parser, range, TokenComma)
	# this is run at least once, since we have two tokens
	while true
		metaVar = MetaVar()
		
		parseMetaTypeFromTo(parser, metaVar, argFrom, argTo - 1) # -1 because this function only parses stuff like "const int *"
		metaVar.name = parser.tokens[ argTo ].str # so here we can set the name now, should be a TokenIdentifier
		#println("parseMetaTypeFromTo(parser, metaVar, argFrom=$argFrom, argTo=$argTo) ret= ", metaVar)
		push!( metaFunction.args, metaVar )
		
		
		
		# after parsing the first argument fit the values for next turn
		
		argFrom = argTo + 2 # we can imply this already, just need to figure out the new argTo with comma-finding
		
		
		nextCommaPos = getTokenPosByTypeBetweenFromTo(parser, TokenComma, argTo + 2, to)
		
		if nextCommaPos == -1
			argTo = to # when there is no next comma, this is our end
		else
			argTo = nextCommaPos - 1
		end
		
		# seems like we reached the end
		if typeof(parser.tokens[argTo + 1]) <: TokenBracketClose
			if runOnceAgain == false
				break
			end
			runOnceAgain = false
		end
		
		if nextCommaPos == -1
			#break
		end
	end
end

function readFunction(parser::Parser)::MetaFunction
	# could have bunch of specifiers, like: const static int main()
	# parse strategy here is to first find the (
	# then pos of ( minus one is the function name...
	# everything before that is const/static or an actual type, like void/int/float
	
	posBracketOpen = getPosOfNextTokenType(parser, TokenBracketOpen)
	posBracketClose = getPosOfNextTokenType(parser, TokenBracketClose)
	posFuncName = posBracketOpen - 1 # prob should do checks like it should be a TokenIdentifier
	
	func = MetaFunction()
	func.name = parser.tokens[posFuncName].str
	
	parseFunctionArguments(parser, func, posBracketOpen + 1, posBracketClose - 1)
	
	# now we can iterate over the "const static int" tokens
	parseMetaTypeFromTo(parser, func.metaVar, parser.i, posFuncName - 1)
	
	
	# this should either be a TokenCurlyBracketOpen or TokenSemicolon
	afterBracketClose = parser.tokens[ posBracketClose + 1 ];
	
	
	# ignore all the statements in a function for now, just skip over it
	# idea: i could probably add meta info to each token in the tokenizer, like the } token pos for each {
	# or also stuff like prevCurlyBracketPos and nextCurlyBracketPos, then i wouldnt need to iterate over every token
	posCurlyBracketOpen = getPosOfNextTokenType(parser, TokenCurlyBracketOpen)
	depth = 0
	pos = posCurlyBracketOpen
	while pos <= length( parser.tokens )
		token = parser.tokens[ pos ]
		if typeof(token) <: TokenCurlyBracketOpen
			depth += 1
		elseif typeof(token) <: TokenCurlyBracketClose
			depth -= 1
		end
		if depth == 0
			break
		end
		pos += 1
	end
	#println("Found curly function end at ", pos)
	parser.i = pos
	
	return func
end

function readPrototype(parser::Parser)::MetaPrototype
	# could have bunch of specifiers, like: const static int main()
	# parse strategy here is to first find the (
	# then pos of ( minus one is the function name...
	# everything before that is const/static or an actual type, like void/int/float
	
	posBracketOpen = getPosOfNextTokenType(parser, TokenBracketOpen)
	posBracketClose = getPosOfNextTokenType(parser, TokenBracketClose)
	posFuncName = posBracketOpen - 1 # prob should do checks like it should be a TokenIdentifier
	
	func = MetaPrototype()
	func.name = parser.tokens[posFuncName].str
	
	# now we can iterate over the "const static int" tokens
	parseMetaTypeFromTo(parser, func.metaVar, parser.i, posFuncName - 1)
	
	
	# this should either be a TokenCurlyBracketOpen or TokenSemicolon
	afterBracketClose = parser.tokens[ posBracketClose + 1 ];
	
		# got a prototype here
		# set parser to end of prototype
		parser.i = posBracketClose + 1 # from ")" jump over ";"
		
	return func
end

function readFunctionOrPrototype(parser::Parser)::Void
	# first find the ), which is there for a function and prototype
	posBracketClose = getPosOfNextTokenType(parser, TokenBracketClose)
	# next token can either be a TokenCurlyBracketOpen or TokenSemicolon,
	# so use it to determine if this is a func or proto
	afterBracketClose = parser.tokens[ posBracketClose + 1 ];
	# pretty easy, a function has a { after )
	# a prototype has a ; after )
	isFunction  = typeof(afterBracketClose) <: TokenCurlyBracketOpen
	isPrototype = typeof(afterBracketClose) <: TokenSemicolon
	# just act acordingly to what we got
	if isFunction
		metaFunc = readFunction(parser)
		push!( parser.functions, metaFunc )
	elseif isPrototype
		metaProto = readPrototype(parser)
		push!( parser.prototypes, metaProto )
	else
		# fucked up, idc about invalid syntax atm
	end
	nothing
end

function getTokenPosByTypeBetweenFromTo(parser::Parser, tokentype::DataType, from, to)
	# julia bullshit
	from = Int32(from)
	to  = Int32(to)
	# actual code
	pos = from
	while pos <= to
		if typeof(parser.tokens[ pos ]) == tokentype
			return pos
		end
		pos += 1
	end
	return -1
end

function readGlobalVar(parser::Parser)
	posSemicolon = getPosOfNextTokenType(parser, TokenSemicolon)
	
	# parser = Parser("int foo[128] = 0;")
	# assignPos = 6
	# 
	
	assignPos = getTokenPosByTypeBetweenFromTo(parser, TokenAssign, parser.i, posSemicolon)
	beforeAssign = assignPos - 1
	if assignPos == -1
		#then there was no = token, so the namePos is just posSemicolon-1
		beforeAssign = posSemicolon - 1
	end
	
	metaVar = MetaVar()
	
	# detect possible [][]
	posSquareBracketOpen = getTokenPosByTypeBetweenFromTo(parser, TokenSquareBracketOpen, parser.i, beforeAssign)
	namePos = beforeAssign
	if posSquareBracketOpen != -1
		# if we have a square bracket open, we need to fit the namePos to before it
		namePos = posSquareBracketOpen - 1
		
		# todo: and we should actually parse the [] info lol
		# e.g. [MAX_ENTITIES] becomes metaVar.dimension0 expression = TokenListFromTo(10,12)... we can be stringified later easily
		# in pure C its just replaced with the real number by preprocessor, but I need to keep this meta data to generate nice headers
		
		
		# oh well, just save the first dimension atm:
		metaVar.dimensionA_startTokenPos = posSquareBracketOpen + 1
		
		# check for 2nd dimension
		posSquareBracketClose = getPosOfNextTokenType(parser, TokenSquareBracketClose)
		if typeof(parser.tokens[ posSquareBracketClose + 1 ]) <: TokenSquareBracketOpen
			metaVar.dimensionB_startTokenPos = posSquareBracketClose + 2 # jumping over ] and [, so we point directly to start of the [$insideExpression]
		end
	end
	
	
	
	tokName = parser.tokens[ namePos ]

	#println("Skip global var stuff for var name: ", tokName);
	#todo: read dimensions in [$dim1][$dim2], also they could be defines like MAX_ENTITIES
	
	metaVar.name = tokName.str

	from = parser.i
	to = namePos - 1
	#println("parseMetaTypeFromTo(parser, $metaVar, $from, $to)", parser.tokens[from], parser.tokens[to])
	parseMetaTypeFromTo(parser, metaVar, from, to)
	
	# todo: iterate over the "const static int **" and collect the infos in metaVar
	parser.i = posSemicolon
	return metaVar
end

function run(parser::Parser)
	# implying there is a token... todo: make TokenStart
	token = parser.tokens[1]

	while true
		#print(token, "\n")
		
		# we start in global scope, that could possibly be:
		# a typedef
		# a variable declaration
		# a function
		# a function prototype
		
		
		if typeof(token) <: TokenTypedef
			advance(parser)
			gotType = readType(parser)
			#print("gotType: ", gotType, "\n")
			ident = token.str
			#print("ident: $ident\n")
		elseif typeof(token) <: TokenStatic || typeof(token) <: TokenConst || typeof(token) <: TokenIdentifier
			# here we have either a global var, a function or a function prototype
			# int foo;
			# int foo();
			# int foo() {}
			# so we look ahead to TokenSemicolon and TokenBracketOpen, to differentiate var/func first
			posSemicolon   = getPosOfNextTokenType(parser, TokenSemicolon)
			posBracketOpen = getPosOfNextTokenType(parser, TokenBracketOpen)
			#println("posSemicolon=$posSemicolon posBracketOpen=$posBracketOpen")
			
			if posBracketOpen == -1
				posBracketOpen = posSemicolon + 1 # its bullshit, just make sure the next if works, if there is no {
			end
			if posSemicolon < posBracketOpen
				# this can only be a var then
				metaVar = readGlobalVar(parser)
				push!( parser.globalVars, metaVar)
				#print("found global var: ", token, "\n")
			else
				# func or prototype
				#print("found global func or prototype: ", token, "\n")
				readFunctionOrPrototype(parser)
				#println("Got func: ", func)
				#push!( parser.functions, func )
			end
			
		elseif typeof(token) <: TokenHash
			parser.i += 2 # just skip #include "bla"
		else
			print("idk what todo with: ", token, "\n")
		end
		
		token = advance(parser)
		
		# do-while replacement, since Julia doesnt support do-whiles
		if typeof(token) == TokenEnd
			break
		end
	end
end

run(parser)




print("hai")
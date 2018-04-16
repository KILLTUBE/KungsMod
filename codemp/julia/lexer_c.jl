include("php_trim.jl")

file_get_contents(name) = String(read(name))
iswhitespace(c::Char) = UInt8(c) in UInt8[0x20, 0x09, 0x0a, 0x0D, 0x00, 0x0b]

# isOpStart is same as isOp, just without the =
# because = shall be TokenAssign, but "+=" is still normal merged op
#isOpStart(c::Char) = c in ['+', '-', '*', '/', ','     , '~', '%', '&', '|', '<', '>', '!', ',', '.', ':', '^']
isOp(     c::Char) = c in ['+', '-', '*', '/', ',', '=', '~', '%', '&', '|', '<', '>', '!', ',', '.', ':', '^']

abstract type Token end

type TokenOp <: Token
	str::String
end
type TokenNum <: Token
	str::String
end
type TokenStr <: Token
	str::String
end
type TokenChar <: Token
	str::String # for stuff like '0'
end
type TokenIdentifier <: Token
	str::String
end
type TokenSemicolon <: Token
	# nothing so far
end

# (
type TokenBracketOpen <: Token
	# nothing so far
end
# )
type TokenBracketClose <: Token
	# nothing so far
end
# [
type TokenSquareBracketOpen <: Token
	# nothing so far
end
# ]
type TokenSquareBracketClose <: Token
	# nothing so far
end
# {
type TokenCurlyBracketOpen <: Token
	# nothing so far
end
# }
type TokenCurlyBracketClose <: Token
	# nothing so far
end

type TokenEnd <: Token
	# just a meta token so we know we iterated over all tokens
end
type TokenStatic <: Token
	# for stuff like: static int foo(); etc.
end
type TokenConst <: Token
	# for stuff like: const int foo(); etc.
end
type TokenHash <: Token
	# token for # like #include #define
end
type TokenQuestionMark <: Token
	# token for ?
end
type TokenAssign <: Token
	# token for =
end

content = file_get_contents("C:\\OpenSciTech\\codemp\\cgame\\cg_main.cpp")
#content = file_get_contents("enums.cpp")

function peekNextChar()
	return content[i + 1]
end

type Parse
	i::Int32
	n::Int32
	s::String
	tokens::Vector{Token}
	curstr::String
	function Parse(s_::String)
		new(1, length(s_), s_, Vector{String}(), "")
	end
end

done(parse::Parse) = parse.i > parse.n

currentChar(parse::Parse) = parse.s[parse.i]
nextChar(parse::Parse) = parse.s[parse.i + 1]
function advance(parse::Parse)
	parse.i += 1
	
end

function isComment(parse::Parse)
	return currentChar(parse) == '/' && nextChar(parse) == '/'
end
function isMultiComment(parse::Parse)
	return currentChar(parse) == '/' && nextChar(parse) == '*'
end

function advanceTill(parse::Parse, char::Char)::Bool
	curPos = parse.i
	while curPos <= parse.n
		if parse.s[curPos] == char
			parse.i = curPos # if we found something, set pos to last index of our token
			return true
		end
		curPos += 1
	end
	# if we didnt found the char, just return false
	return false
end

function advanceTill(parse::Parse, str::String)::Bool
	# search $str from current position in parse.s
	ret = search(parse.s, str, parse.i)
	if ret.stop == -1
		return false
	end
	parse.i = ret.stop # if we found something, set pos to last index of our token
	return true
end

function pushIdentifier(parse::Parse, str::String)
	if str == "static"
		push!(parse.tokens, TokenStatic())
		return
	end
	if str == "const"
		push!(parse.tokens, TokenConst())
		return
	end
	push!(parse.tokens, TokenIdentifier(str))
end

function step(parse::Parse)
	cc = currentChar(parse)

	if isComment(parse)
		commentFrom = parse.i
		advanceTill(parse, '\n')
		commentTo = parse.i
		comment = parse.s[commentFrom:commentTo]
		#print("comment from=$commentFrom to=$commentTo comment=$comment\n")
		return
	end
	
	if isMultiComment(parse)
		commentFrom = parse.i
		advanceTill(parse, "*/")
		commentTo = parse.i
		comment = parse.s[commentFrom:commentTo]
		#print("multicomment from=$commentFrom to=$commentTo comment=$comment\n")
		return
	end
	
	#if cc in [';', '*', ',', '{', '}', '[', ']']
	#	flushString(parse) # if we have a curstr, add it, before we add this token
	#	push!(parse.tokens, string(cc))
	#	print("got operator thingy $cc\n")
	#elseif isalpha(cc)
	if isalpha(cc) || cc == '_' # identifiers either start with alpha or _, but not digits
	
		# a string literal can start with alpha or digit, but can contain _ from now on, search till end and add as token
		
		str = string(cc)
		advance(parse)
		
		while ! done(parse)
			cc = currentChar(parse)
			if isalpha(cc) || isdigit(cc) || cc == '_'
				str *= string(cc)
				advance(parse)
			else
				pushIdentifier(parse, str) # "static" or "const" e.g. will become special tokens
				parse.i -= 1 # we advanced but figured out here that its not part of literal anymore, so go back
				break
			end
		end
		
		#parse.curstr *= string(cc)
	elseif isdigit(cc)
		
		numstr = string(cc)
		advance(parse)
		
		while ! done(parse)
			cc = currentChar(parse)
			if isdigit(cc) || cc == '.'
				numstr *= string(cc)
				advance(parse)
			else
				push!(parse.tokens, TokenNum(numstr))
				#print("got numstr: $numstr\n")
				parse.i -= 1 # we advanced but figured out here that its not part of literal anymore, so go back
				return
			end
		end
	elseif cc == Char(0x22) # detect ", just because shitty syntax highlighting in Notepad++ atm for '"'
		advance(parse) # jump over current ", so we only get the actual string content
		commentFrom = parse.i
		advanceTill(parse, Char(0x22)) # now advance to end '"'
		commentTo = parse.i - 1 # -1 tho, because we dont want the last ", only string content
		cstr = parse.s[commentFrom:commentTo]
		#print("cstr from=$commentFrom to=$commentTo cstr=$cstr\n")
		push!(parse.tokens, TokenStr(cstr))
		return
	elseif cc == Char(0x27) # detect ',just because shitty syntax highlighting in Notepad++ atm for '''
		advance(parse) # jump over current ', so we only get the actual string content
		commentFrom = parse.i
		advanceTill(parse, Char(0x27)) # now advance to end '''
		commentTo = parse.i - 1 # -1 tho, because we dont want the last ", only string content
		cstr = parse.s[commentFrom:commentTo]
		#print("cstr from=$commentFrom to=$commentTo cstr=$cstr\n")
		push!(parse.tokens, TokenChar(cstr))
		return
	elseif cc == '='
		push!(parse.tokens, TokenAssign())
	elseif isOp(cc)
		opstr = string(cc)
		advance(parse)
		
		# changed this, ops are not merged now, so -= are two tokens
		# merging causes problems for stuff like **, pointer-to-pointer, custom operator? hm, i guess i keep operator merging lol
		#push!(parse.tokens, TokenOp(opstr))
		#return
		
		while ! done(parse)
			cc = currentChar(parse)
			if isOp(cc)
				opstr *= string(cc)
				#push!(parse.tokens, TokenOp(opstr))
				advance(parse)
			else
				push!(parse.tokens, TokenOp(opstr))
				#print("got op: $opstr\n")
				parse.i -= 1 # we advanced but figured out here that its not an op anymore, so go back
				return
			end
		end
	elseif cc == ';'
		push!(parse.tokens, TokenSemicolon())
	elseif cc == '('
		push!(parse.tokens, TokenBracketOpen())
	elseif cc == ')'
		push!(parse.tokens, TokenBracketClose())
	elseif cc == '['
		push!(parse.tokens, TokenSquareBracketOpen())
	elseif cc == ']'
		push!(parse.tokens, TokenSquareBracketClose())
	elseif cc == '{'
		push!(parse.tokens, TokenCurlyBracketOpen())
	elseif cc == '}'
		push!(parse.tokens, TokenCurlyBracketClose())
	elseif cc == '#'
		push!(parse.tokens, TokenHash())
	elseif cc == '?'
		push!(parse.tokens, TokenQuestionMark())
	elseif iswhitespace(cc)
		# just ignore
	else
		print("idk what to do with: $cc at ", parse.i ,"\n")
	end	
end

parse = Parse(content)

#function flushString(parse::Parse)::Bool
#	if trim(parse.curstr) == ""
#		return false
#	end
#	push!(parse.tokens, parse.curstr)
#	parse.curstr = ""
#	return true
#end

function steps(parse::Parse)
	while ! done(parse)
		step(parse)
		advance(parse)
	end
	
	push!(parse.tokens, TokenEnd())
	
	#if flushString(parse)
	#	print("add last thing: ", last(parse.tokens), "\n")
	#end

end

steps(parse)

# todo: just make TokenTypedef, TokenElse etc.?
isTypedef(   token::Token) = typeof(token) <: TokenIdentifier && token.str == "typedef"
isStruct(    token::Token) = typeof(token) <: TokenIdentifier && token.str == "struct"
isInclude(   token::Token) = typeof(token) <: TokenIdentifier && token.str == "include"
isOpStar(    token::Token) = typeof(token) <: TokenOp         && token.str == "*"        # just for pointer detection
isOpStarStar(token::Token) = typeof(token) <: TokenOp         && token.str == "**"       # just for pointer detection


# collect data of C vars while parsing over it
type MetaVar
	name::String
	vartype::DataType
	isConst::Bool
	isStatic::Bool
	numPointer::Int32 # 0 is "int foo"    1 is "int *foo"    2 is "int **foo"    etc.
	function MetaVar()
		new("unnamed", Any)
	end
end

# just to collect the data of a struct while parsing over it
type MetaStruct
	name::String
	vars::Vector{MetaVar}
	function MetaStruct()
		new("unnamed", Vector{MetaVar}())
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
	function Parser(parse::Parse)
		new(
			1,
			parse.tokens,
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

function cStringToJuliaType(string::String)
	if string == "int"       return Int32   end
	if string == "float"     return Float32 end
	if string == "void"      return Void    end
	if string == "qboolean"  return Bool    end
	if string == "char"      return Char    end
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

parser = Parser(parse)

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
			metaVar.vartype = cStringToJuliaType(token.str)
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
	
	# detect possible [][]
	posSquareBracketOpen = getTokenPosByTypeBetweenFromTo(parser, TokenSquareBracketOpen, parser.i, beforeAssign)
	namePos = beforeAssign
	if posSquareBracketOpen != -1
		# if we have a square bracket open, we need to fit the namePos to before it
		namePos = posSquareBracketOpen - 1
		
		# todo: and we should actually parse the [] info lol
		# e.g. [MAX_ENTITIES] becomes metaVar.dimension0 expression = TokenListFromTo(10,12)... we can be stringified later easily
		# in pure C its just replaced with the real number by preprocessor, but I need to keep this meta data to generate nice headers
	end
	
	
	
	tokName = parser.tokens[ namePos ]

	#println("Skip global var stuff for var name: ", tokName);
	#todo: read dimensions in [$dim1][$dim2], also they could be defines like MAX_ENTITIES
	
	metaVar = MetaVar()
	metaVar.name = tokName.str

	from = parser.i
	to = namePos - 1
	println("parseMetaTypeFromTo(parser, $metaVar, $from, $to)", parser.tokens[from], parser.tokens[to])
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
		
		
		if isTypedef(token)
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
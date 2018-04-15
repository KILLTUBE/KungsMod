include("php_trim.jl")

file_get_contents(name) = String(read(name))
iswhitespace(c::Char) = UInt8(c) in UInt8[0x20, 0x09, 0x0a, 0x0D, 0x00, 0x0b]
isOp(c::Char) = c in ['+', '-', '*', '/', ',', '=', '~', '%', '&', '|', '<', '>', '!', ',', '.']

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

content = file_get_contents("enums.cpp")

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
	if isalpha(cc)
	
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
				print("got numstr: $numstr\n")
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
				print("got op: $opstr\n")
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
	elseif iswhitespace(cc)
		# just ignore
	else
		print("idk what to do with: $cc\n")
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
	
		print("readType> got a struct...\n")
		
		curTok = advance(parser) # token identifier, e.g. "testtype_s"
		print("MakeStruct(", curTok.str, "\n")
		
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

function debug(parser::Parser)
	if (parser.i > 1)
		print("prev token> ", parser.tokens[parser.i - 1], "\n")
	end
	print("current token> ", parser.tokens[parser.i], "\n")
	# e.g. 3 tokens, 1, 2, 3, when i==2, we can show the next one
	if parser.i + 1 <= length(parser.tokens)
		print("next token> ", parser.tokens[parser.i + 1], "\n")
	end
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

function readFunctionOrPrototype(parser::Parser)::MetaFunction
	# could have bunch of specifiers, like: const static int main()
	# parse strategy here is to first find the (
	# then pos of ( minus one is the function name...
	# everything before that is const/static or an actual type, like void/int/float
	
	func = MetaFunction()
	posBracketOpen = getPosOfNextTokenType(parser, TokenBracketOpen)
	posBracketClose = getPosOfNextTokenType(parser, TokenBracketClose)
	posFuncName = posBracketOpen - 1 # prob should do checks like it should be a TokenIdentifier
	func.name = parser.tokens[posFuncName].str
	
	# now we can iterate over the "const static int" tokens
	pos = parser.i
	while pos < posFuncName
		token = parser.tokens[ pos ]
		
		if typeof(token) <: TokenIdentifier
			func.metaVar.vartype = cStringToJuliaType(token.str)
		elseif typeof(token) <: TokenStatic
			func.metaVar.isStatic = true
		elseif typeof(token) <: TokenConst
			func.metaVar.isConst = true
		elseif isOpStar(token)
			func.metaVar.numPointer += 1
		elseif isOpStarStar(token)
			func.metaVar.numPointer += 2
		else
			println("rekt @ fizzle pre func tokens stuff out", token)
		end
		
		pos += 1
	end
	
	
	# this should either be a TokenCurlyBracketOpen or TokenSemicolon
	afterBracketClose = parser.tokens[ posBracketClose + 1 ];
	
	if typeof(afterBracketClose) <: TokenCurlyBracketOpen
		# ignore all the statements in a function for now, just skip over it
		posCurlyBracketClose = getPosOfNextTokenType(parser, TokenCurlyBracketClose)
		parser.i = posCurlyBracketClose
		
	elseif typeof(afterBracketClose) <: TokenSemicolon
		# got a prototype here
		# set parser to end of prototype
		parser.i = posBracketClose + 1 # from ")" jump over ";"
	else
		# fucked up, idc about invalid syntax atm
	end
	

	
	return func
end

function getPrevTokenPosTypeFromPos(parser::Parser, tokentype::DataType, pos::Int32)

	while pos >= 1
		if typeof(parser.tokens[ pos ]) == tokentype
			return pos
		end
		pos -= 1
	end
end

function readGlobalVar(parser::Parser)
	posSemicolon = getPosOfNextTokenType(parser, TokenSemicolon)
	
	namePos = getPrevTokenPosTypeFromPos(parser, TokenIdentifier, posSemicolon)
	tokName = parser.tokens[ namePos ]

	#println("Skip global var stuff for var name: ", tokName);
	#todo: read dimensions in [$dim1][$dim2], also they could be defines like MAX_ENTITIES
	
	parser.i = posSemicolon
	
	metaVar = MetaVar()
	metaVar.name = tokName.str
	
	# todo: iterate over the "const static int **" and collect the infos in metaVar
	
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
				func = readFunctionOrPrototype(parser)
				println("Got func: ", func)
				push!( parser.functions, func )
			end
			
		else
			#print("idk what todo with: ", token, "\n")
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
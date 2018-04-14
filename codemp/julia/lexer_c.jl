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
				push!(parse.tokens, TokenIdentifier(str))
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
		
		while ! done(parse)
			cc = currentChar(parse)
			if isOp(cc)
				opstr *= string(cc)
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
isTypedef(token::Token) = typeof(token) <: TokenIdentifier && token.str == "typedef"
isStruct(token::Token) = typeof(token) <: TokenIdentifier && token.str == "struct"

# collect data of C vars while parsing over it
type MetaVar
	name::String
	vartype::DataType
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

type Parser
	i::Int32
	tokens::Vector{Token}
	structs::Vector{MetaStruct}
	function Parser(parse::Parse)
		new(1, parse.tokens, Vector{MetaStruct}())
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
	if string == "int"
		return Int32
	end
	if string == "float"
		return Float32
	end
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
			print("gotType: ", gotType, "\n")
			ident = token.str
			print("ident: $ident\n")
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
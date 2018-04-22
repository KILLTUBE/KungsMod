include("utils_file.jl")

#=
known bugs:
julia> parseC("://asd")
the operator will consume the // comment, atm i just fix the source code to have a space... 
but need to redo the whole structure, so the preprocessor is run first only
=#

iswhitespace(c::Char) = UInt8(c) in UInt8[0x20, 0x09, 0x0a, 0x0D, 0x00, 0x0b]

# isOpStart is same as isOp, just without the =
# because = shall be TokenAssign, but "+=" is still normal merged op
#isOpStart(c::Char) = c in ['+', '-', '*', '/', ','     , '~', '%', '&', '|', '<', '>', '!', ',', '.', ':', '^']
isOp(     c::Char) = c in ['+', '-', '*', '/', '=', '~', '%', '&', '|', '<', '>', '!', '.', ':', '^']

abstract type Token end

type TokenOp                 <: Token i::Int32; str::String end # everything from isOp(...) function, like TokenOp("+=")
type TokenNum                <: Token i::Int32; str::String end # 123
type TokenStr                <: Token i::Int32; str::String end # "something"
type TokenChar               <: Token i::Int32; str::String end # for stuff like '0'
type TokenIdentifier         <: Token i::Int32; str::String end # all kinds of identifiers not translated to special tokens like TokenStatic
type TokenSemicolon          <: Token i::Int32;             end # ;
type TokenBracketOpen        <: Token i::Int32;             end # (
type TokenBracketClose       <: Token i::Int32;             end # )
type TokenSquareBracketOpen  <: Token i::Int32;             end # [
type TokenSquareBracketClose <: Token i::Int32;             end # ]
type TokenCurlyBracketOpen   <: Token i::Int32;             end # {
type TokenCurlyBracketClose  <: Token i::Int32;             end # }
type TokenHash               <: Token i::Int32;             end # #
type TokenQuestionMark       <: Token i::Int32;             end # ?
type TokenAssign             <: Token i::Int32;             end # =
type TokenComma              <: Token i::Int32;             end # ,
type TokenUnsigned           <: Token i::Int32;             end # unsigned
type TokenStatic             <: Token i::Int32;             end # static
type TokenConst              <: Token i::Int32;             end # const
type TokenInclude            <: Token i::Int32;             end # include
type TokenDefine             <: Token i::Int32;             end # define
type TokenUndef              <: Token i::Int32;             end # undef
type TokenTypedef            <: Token i::Int32;             end # typedef
type TokenStruct             <: Token i::Int32;             end # struct
type TokenIf                 <: Token i::Int32;             end # if
type TokenElseIf             <: Token i::Int32;             end # elseif
type TokenElse               <: Token i::Int32;             end # else
type TokenExtern             <: Token i::Int32;             end # extern
type TokenEXTERNC            <: Token i::Int32;             end # EXTERNC
type TokenCCALL              <: Token i::Int32;             end # CCALL
type TokenQINLINE            <: Token i::Int32;             end # QINLINE
type TokenQDECL              <: Token i::Int32;             end # QDECL
type TokenEnum               <: Token i::Int32;             end # enum
type TokenNewline            <: Token i::Int32;             end # \n
type TokenEnd                <: Token i::Int32;             end # just a meta token so we know we iterated over all tokens

type Tokenizer
	i::Int32
	n::Int32
	s::String
	tokens::Vector{Token}
	curstr::String
	function Tokenizer(s_::String)
		new(1, length(s_), s_, Vector{String}(), "")
	end
end

done(tokenizer::Tokenizer) = tokenizer.i > tokenizer.n

currentChar(tokenizer::Tokenizer) = tokenizer.s[tokenizer.i]
nextChar(tokenizer::Tokenizer) = tokenizer.s[tokenizer.i + 1]
function advance(tokenizer::Tokenizer)
	tokenizer.i += 1
	
end

function isComment(tokenizer::Tokenizer)
	return currentChar(tokenizer) == '/' && nextChar(tokenizer) == '/'
end
function isMultiComment(tokenizer::Tokenizer)
	return currentChar(tokenizer) == '/' && nextChar(tokenizer) == '*'
end

function advanceTill(tokenizer::Tokenizer, char::Char)::Bool
	curPos = tokenizer.i
	while curPos <= tokenizer.n
		if tokenizer.s[curPos] == char
			tokenizer.i = curPos # if we found something, set pos to last index of our token
			return true
		end
		tokenizer.i = curPos # also set pos if we didnt find, e.g. tokenize("// asd") and advanceTill(tokenizer, '\n') isnt finding the end, but it should be ignored nonetheless
		curPos += 1
		
	end
	# if we didnt found the char, just return false
	return false
end

function advanceTill(tokenizer::Tokenizer, str::String)::Bool
	# search $str from current position in tokenizer.s
	ret = search(tokenizer.s, str, tokenizer.i)
	if ret.stop == -1
		return false
	end
	tokenizer.i = ret.stop # if we found something, set pos to last index of our token
	return true
end

function pushIdentifier(tokenizer::Tokenizer, str::String)
	if str == "unsigned"
		push!(tokenizer.tokens, TokenUnsigned(tokenizer.i))
		return
	end
	if str == "static"
		push!(tokenizer.tokens, TokenStatic(tokenizer.i))
		return
	end
	if str == "const"
		push!(tokenizer.tokens, TokenConst(tokenizer.i))
		return
	end
	if str == "include"
		push!(tokenizer.tokens, TokenInclude(tokenizer.i))
		return
	end
	if str == "define"
		push!(tokenizer.tokens, TokenDefine(tokenizer.i))
		return
	end
	if str == "undef"
		push!(tokenizer.tokens, TokenUndef(tokenizer.i))
		return
	end
	if str == "typedef"
		push!(tokenizer.tokens, TokenTypedef(tokenizer.i))
		return
	end
	if str == "struct"
		push!(tokenizer.tokens, TokenStruct(tokenizer.i))
		return
	end
	if str == "if"
		push!(tokenizer.tokens, TokenIf(tokenizer.i))
		return
	end
	if str == "elseif"
		push!(tokenizer.tokens, TokenElseIf(tokenizer.i))
		return
	end
	if str == "else"
		push!(tokenizer.tokens, TokenElse(tokenizer.i))
		return
	end
	if str == "extern"
		push!(tokenizer.tokens, TokenExtern(tokenizer.i))
		return
	end
	if str == "EXTERNC"
		push!(tokenizer.tokens, TokenEXTERNC(tokenizer.i))
		return
	end
	if str == "CCALL"
		push!(tokenizer.tokens, TokenCCALL(tokenizer.i))
		return
	end
	if str == "QINLINE"
		push!(tokenizer.tokens, TokenQINLINE(tokenizer.i))
		return
	end
	if str == "QDECL"
		push!(tokenizer.tokens, TokenQDECL(tokenizer.i))
		return
	end
	if str == "enum"
		push!(tokenizer.tokens, TokenEnum(tokenizer.i))
		return
	end
	push!(tokenizer.tokens, TokenIdentifier(tokenizer.i, str))
end

function step(tokenizer::Tokenizer)
	cc = currentChar(tokenizer)

	if isComment(tokenizer)
		commentFrom = tokenizer.i
		advanceTill(tokenizer, '\n')
		commentTo = tokenizer.i
		comment = tokenizer.s[commentFrom:commentTo]
		#print("comment from=$commentFrom to=$commentTo comment=$comment\n")
		return
	end
	
	if isMultiComment(tokenizer)
		commentFrom = tokenizer.i
		advanceTill(tokenizer, "*/")
		commentTo = tokenizer.i
		comment = tokenizer.s[commentFrom:commentTo]
		#print("multicomment from=$commentFrom to=$commentTo comment=$comment\n")
		return
	end
	
	#if cc in [';', '*', ',', '{', '}', '[', ']']
	#	flushString(tokenizer) # if we have a curstr, add it, before we add this token
	#	push!(tokenizer.tokens, string(cc))
	#	print("got operator thingy $cc\n")
	#elseif isalpha(cc)
	if isalpha(cc) || cc == '_' # identifiers either start with alpha or _, but not digits
	
		# a string literal can start with alpha or digit, but can contain _ from now on, search till end and add as token
		
		str = string(cc)
		advance(tokenizer)
		
		while ! done(tokenizer)
			cc = currentChar(tokenizer)
			if isalpha(cc) || isdigit(cc) || cc == '_'
				str *= string(cc)
				advance(tokenizer)
			else
				break
			end
		end
		
		pushIdentifier(tokenizer, str) # "static" or "const" e.g. will become special tokens
		tokenizer.i -= 1 # we advanced in while loop but figured out here that its not part of literal anymore, so go back
	elseif isdigit(cc)
		
		str = string(cc)
		advance(tokenizer)
		
		# when a token begins with 0 it can be either a normal number like 0.99 or a hex like 0xabcd
		
		if done(tokenizer)
			return
		end
		
		if currentChar(tokenizer) == 'x' || currentChar(tokenizer) == 'X'
			# read in hex values, todo: only 0-9 a-f A-F
			while ! done(tokenizer)
				cc = currentChar(tokenizer)
				if isalpha(cc) || isdigit(cc) || cc == '_'
					str *= string(cc)
					advance(tokenizer)
				else
					break
				end
			end
			push!(tokenizer.tokens, TokenNum(tokenizer.i, str)) # todo: translate 0xabcd stuff to number
			tokenizer.i -= 1 # we advanced in while loop but figured out here that its not part of literal anymore, so go back
		else
			# read in a normal number
			while ! done(tokenizer)
				cc = currentChar(tokenizer)
				if isdigit(cc) || cc == '.'
					str *= string(cc)
					advance(tokenizer)
				else
					break
				end
			end
			push!(tokenizer.tokens, TokenNum(tokenizer.i, str))
			#print("got str for digits: $str\n")
			tokenizer.i -= 1 # we advanced but figured out here that its not part of literal anymore, so go back
		end
	elseif cc == Char(0x22) # detect ", just because shitty syntax highlighting in Notepad++ atm for '"'
		advance(tokenizer) # jump over current ", so we only get the actual string content
		#commentFrom = tokenizer.i
		
		
		strFrom = tokenizer.i
		while ! done(tokenizer)
			local cc = currentChar(tokenizer)
			if cc == '\\'
				# todo: add whatever is behind this \ into str
				advance(tokenizer) # ignore whatever is after a \
			end
			
			if cc == Char(0x22) # we found the end "
				break
			end
			
			advance(tokenizer)
		end
		strTo = tokenizer.i - 1 # ignore the last "
		#advanceTill(tokenizer, Char(0x22)) # now advance to end '"'
		
		#while tokenizer.s[ tokenizer.i - 1] == '\\'
		#	#println("advance again..")
		#	tokenizer.i += 1 # advance 1 by hand, otherwise we step on the same place in endless loop
		#	advanceTill(tokenizer, Char(0x22)) # advance again if it was a \" inline escaped "
		#end
		
		
		str = tokenizer.s[strFrom:strTo]
		#print("cstr from=$commentFrom to=$commentTo cstr=$cstr\n")
		push!(tokenizer.tokens, TokenStr(tokenizer.i, str))
		return
	elseif cc == Char(0x27) # detect ',just because shitty syntax highlighting in Notepad++ atm for '''
		advance(tokenizer) # jump over current ', so we only get the actual string content
		commentFrom = tokenizer.i
		advanceTill(tokenizer, Char(0x27)) # now advance to end '''
		commentTo = tokenizer.i - 1 # -1 tho, because we dont want the last ", only string content
		cstr = tokenizer.s[commentFrom:commentTo]
		#print("cstr from=$commentFrom to=$commentTo cstr=$cstr\n")
		push!(tokenizer.tokens, TokenChar(tokenizer.i, cstr))
		return
	elseif cc == '='
		push!(tokenizer.tokens, TokenAssign(tokenizer.i))
	elseif cc == ','
		push!(tokenizer.tokens, TokenComma(tokenizer.i))
	elseif isOp(cc)
		opstr = string(cc)
		advance(tokenizer)
		
		# changed this, ops are not merged now, so -= are two tokens
		# merging causes problems for stuff like **, pointer-to-pointer, custom operator? hm, i guess i keep operator merging lol
		#push!(tokenizer.tokens, TokenOp(opstr))
		#return
		
		while ! done(tokenizer)
			cc = currentChar(tokenizer)
			if isOp(cc)
				opstr *= string(cc)
				#push!(tokenizer.tokens, TokenOp(opstr))
				advance(tokenizer)
			else
				break
			end
		end
		push!(tokenizer.tokens, TokenOp(tokenizer.i, opstr))
		#print("got op: $opstr\n")
		tokenizer.i -= 1 # we advanced but figured out here that its not an op anymore, so go back
	elseif cc == ';'
		push!(tokenizer.tokens, TokenSemicolon(tokenizer.i))
	elseif cc == '('
		push!(tokenizer.tokens, TokenBracketOpen(tokenizer.i))
	elseif cc == ')'
		push!(tokenizer.tokens, TokenBracketClose(tokenizer.i))
	elseif cc == '['
		push!(tokenizer.tokens, TokenSquareBracketOpen(tokenizer.i))
	elseif cc == ']'
		push!(tokenizer.tokens, TokenSquareBracketClose(tokenizer.i))
	elseif cc == '{'
		push!(tokenizer.tokens, TokenCurlyBracketOpen(tokenizer.i))
	elseif cc == '}'
		push!(tokenizer.tokens, TokenCurlyBracketClose(tokenizer.i))
	elseif cc == '#'
		#push!(tokenizer.tokens, TokenHash())
		# oh well, fuck it, those #define #undef #include etc. fuck up the token steam
		# there is no syntax to them, besides writing an interpreter for it i guess, which i dont want to do right now
		# so atm i just wanna parse C stuff, dont need the preprocessor tokens, just skip to end of line:
		#advanceTill(tokenizer, '\n')
		
		curPos = tokenizer.i
		#println("tokenizer.i = ", tokenizer.i)
		
		while curPos <= tokenizer.n
		
			# ignoring those filthy backslash multilines
			if curPos > 1 && tokenizer.s[curPos - 1] == '\\'
				curPos += 2 # jump over \n
				continue
			end
			if tokenizer.s[curPos] == '\n'
				tokenizer.i = curPos # if we found something, set pos to last index of our token
				return true
			end
			tokenizer.i = curPos # also set pos if we didnt find, e.g. tokenize("// asd") and advanceTill(tokenizer, '\n') isnt finding the end, but it should be ignored nonetheless
			curPos += 1
			
		end		
		
	elseif cc == '?'
		push!(tokenizer.tokens, TokenQuestionMark(tokenizer.i))
	elseif cc == '\\'
		# this is used to combine multiple lines, simply ignore i guess for now
	elseif iswhitespace(cc)
		# just ignore, but add token for \n
		
		# this was kinda just a hack to get to end of preprocessor directives, but just removing them from token stream now
		# the newline tokens cause too many troubles, i cant simply parser.i += 1 anymore
		#if cc == '\n'
		#	push!(tokenizer.tokens, TokenNewline())
		#end
	else
		print("idk what to do with: $cc at ", tokenizer.i ,"\n")
	end	
end

function steps(tokenizer::Tokenizer)
	while ! done(tokenizer)
		step(tokenizer)
		advance(tokenizer)
	end
	
	push!(tokenizer.tokens, TokenEnd(tokenizer.i))
	
	#if flushString(tokenizer)
	#	print("add last thing: ", last(tokenizer.tokens), "\n")
	#end

end

# simple function to wrap it all up
function tokenize(sourcecode::String)
	tokenizer = Tokenizer(sourcecode)
	steps(tokenizer)
	return tokenizer
end

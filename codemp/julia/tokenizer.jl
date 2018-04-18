iswhitespace(c::Char) = UInt8(c) in UInt8[0x20, 0x09, 0x0a, 0x0D, 0x00, 0x0b]

# isOpStart is same as isOp, just without the =
# because = shall be TokenAssign, but "+=" is still normal merged op
#isOpStart(c::Char) = c in ['+', '-', '*', '/', ','     , '~', '%', '&', '|', '<', '>', '!', ',', '.', ':', '^']
isOp(     c::Char) = c in ['+', '-', '*', '/', '=', '~', '%', '&', '|', '<', '>', '!', '.', ':', '^']

abstract type Token end

type TokenOp                 <: Token str::String end # everything from isOp(...) function, like TokenOp("+=")
type TokenNum                <: Token str::String end # 123
type TokenStr                <: Token str::String end # "something"
type TokenChar               <: Token str::String end # for stuff like '0'
type TokenIdentifier         <: Token str::String end # all kinds of identifiers not translated to special tokens like TokenStatic
type TokenSemicolon          <: Token             end # ;
type TokenBracketOpen        <: Token             end # (
type TokenBracketClose       <: Token             end # )
type TokenSquareBracketOpen  <: Token             end # [
type TokenSquareBracketClose <: Token             end # ]
type TokenCurlyBracketOpen   <: Token             end # {
type TokenCurlyBracketClose  <: Token             end # }
type TokenHash               <: Token             end # #
type TokenQuestionMark       <: Token             end # ?
type TokenAssign             <: Token             end # =
type TokenComma              <: Token             end # ,
type TokenUnsigned           <: Token             end # unsigned
type TokenStatic             <: Token             end # static
type TokenConst              <: Token             end # const
type TokenInclude            <: Token             end # include
type TokenDefine             <: Token             end # define
type TokenUndef              <: Token             end # undef
type TokenTypedef            <: Token             end # typedef
type TokenStruct             <: Token             end # struct
type TokenIf                 <: Token             end # if
type TokenElseIf             <: Token             end # elseif
type TokenElse               <: Token             end # else
type TokenExtern             <: Token             end # extern
type TokenEXTERNC            <: Token             end # EXTERNC
type TokenCCALL              <: Token             end # CCALL
type TokenQINLINE            <: Token             end # QINLINE
type TokenQDECL              <: Token             end # QDECL
type TokenEnum               <: Token             end # enum
type TokenNewline            <: Token             end # \n
type TokenEnd                <: Token             end # just a meta token so we know we iterated over all tokens

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
		push!(tokenizer.tokens, TokenUnsigned())
		return
	end
	if str == "static"
		push!(tokenizer.tokens, TokenStatic())
		return
	end
	if str == "const"
		push!(tokenizer.tokens, TokenConst())
		return
	end
	if str == "include"
		push!(tokenizer.tokens, TokenInclude())
		return
	end
	if str == "define"
		push!(tokenizer.tokens, TokenDefine())
		return
	end
	if str == "undef"
		push!(tokenizer.tokens, TokenUndef())
		return
	end
	if str == "typedef"
		push!(tokenizer.tokens, TokenTypedef())
		return
	end
	if str == "struct"
		push!(tokenizer.tokens, TokenStruct())
		return
	end
	if str == "if"
		push!(tokenizer.tokens, TokenIf())
		return
	end
	if str == "elseif"
		push!(tokenizer.tokens, TokenElseIf())
		return
	end
	if str == "else"
		push!(tokenizer.tokens, TokenElse())
		return
	end
	if str == "extern"
		push!(tokenizer.tokens, TokenExtern())
		return
	end
	if str == "EXTERNC"
		push!(tokenizer.tokens, TokenEXTERNC())
		return
	end
	if str == "CCALL"
		push!(tokenizer.tokens, TokenCCALL())
		return
	end
	if str == "QINLINE"
		push!(tokenizer.tokens, TokenQINLINE())
		return
	end
	if str == "QDECL"
		push!(tokenizer.tokens, TokenQDECL())
		return
	end
	if str == "enum"
		push!(tokenizer.tokens, TokenEnum())
		return
	end
	push!(tokenizer.tokens, TokenIdentifier(str))
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
			push!(tokenizer.tokens, TokenNum(str)) # todo: translate 0xabcd stuff to number
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
			push!(tokenizer.tokens, TokenNum(str))
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
		push!(tokenizer.tokens, TokenStr(str))
		return
	elseif cc == Char(0x27) # detect ',just because shitty syntax highlighting in Notepad++ atm for '''
		advance(tokenizer) # jump over current ', so we only get the actual string content
		commentFrom = tokenizer.i
		advanceTill(tokenizer, Char(0x27)) # now advance to end '''
		commentTo = tokenizer.i - 1 # -1 tho, because we dont want the last ", only string content
		cstr = tokenizer.s[commentFrom:commentTo]
		#print("cstr from=$commentFrom to=$commentTo cstr=$cstr\n")
		push!(tokenizer.tokens, TokenChar(cstr))
		return
	elseif cc == '='
		push!(tokenizer.tokens, TokenAssign())
	elseif cc == ','
		push!(tokenizer.tokens, TokenComma())
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
				push!(tokenizer.tokens, TokenOp(opstr))
				#print("got op: $opstr\n")
				tokenizer.i -= 1 # we advanced but figured out here that its not an op anymore, so go back
				return
			end
		end
	elseif cc == ';'
		push!(tokenizer.tokens, TokenSemicolon())
	elseif cc == '('
		push!(tokenizer.tokens, TokenBracketOpen())
	elseif cc == ')'
		push!(tokenizer.tokens, TokenBracketClose())
	elseif cc == '['
		push!(tokenizer.tokens, TokenSquareBracketOpen())
	elseif cc == ']'
		push!(tokenizer.tokens, TokenSquareBracketClose())
	elseif cc == '{'
		push!(tokenizer.tokens, TokenCurlyBracketOpen())
	elseif cc == '}'
		push!(tokenizer.tokens, TokenCurlyBracketClose())
	elseif cc == '#'
		#push!(tokenizer.tokens, TokenHash())
		# oh well, fuck it, those #define #undef #include etc. fuck up the token steam
		# there is no syntax to them, besides writing an interpreter for it i guess, which i dont want to do right now
		# so atm i just wanna parse C stuff, dont need the preprocessor tokens, just skip to end of line:
		advanceTill(tokenizer, '\n')
	elseif cc == '?'
		push!(tokenizer.tokens, TokenQuestionMark())
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
	
	push!(tokenizer.tokens, TokenEnd())
	
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

#
# julia> tokens = tokenize("int a, const float b, bool c").tokens
# 10-element Array{Token,1}:
#  1 = TokenIdentifier("int")
#  2 = TokenIdentifier("a")
#  3 = TokenComma()
#  4 = TokenConst()
#  5 = TokenIdentifier("float")
#  6 = TokenIdentifier("b")
#  7 = TokenComma()
#  8 = TokenIdentifier("bool")
#  9 = TokenIdentifier("c")
# 10 = TokenEnd()
#  
#  
# 
# type TokenRange
# 	parser
# 	from::Int32
# 	to::Int32
# end
#  
# tokenrange(parse, 1, 9, TokenComma)
# 
# (1,2)
# (4,6)
# (8,9)
#  
 
 
tokens = tokenize("int a, const float b, bool c, vec3_t d, int a").tokens
 
from = 1
to = length(tokens) - 1

argTo = from - 2 # just so that argTo+2==from, so the while loop has no special case for first case

while true


	argFrom = argTo + 2
	posComma = getTokenPosByTypeBetweenFromTo(tokens, TokenComma, argFrom, to) # first run: 3
	if posComma > 0
		argTo = posComma - 1
	else
		argTo = to
	end
	println("($argFrom, $argTo)")
	
	if argTo == to
		break
	end
end








function pprint(data)
  return imgui_log(string(data) * "\n")
end

function repl(select_from, select_to, replbuffer)

  if select_from < select_to
    replbuffer = substr(replbuffer, select_from, select_to)
  elseif select_from > select_to
    replbuffer = substr(replbuffer, select_to, select_from)
  end
  
  ##imgui_log("Selectfrom= ($select_from) s_to=($select_to)\n")
  #try
  #  expr, pos = parse(replbuffer, 1) # tbh this makes no sense to me yet... check E:\Julia-0.5.2\share\julia\base\parse.jl line 176
  #  #pprint(expr)
  #  ret = eval(expr)
  #  pprint(ret)
  #catch e
  #  pprint(e)
  #end
  ret = evalall(replbuffer)
  pprint(ret)
end

function substr(str, from_, to_)	
  return str[from_+1: to_]
end


function evalall(str::AbstractString)
  bstr = String(str)
  #imgui_log(bstr)
  ret = nothing
	try
		ret = ccall(:jl_parse_eval_all, Any, (Cstring, Cstring, Csize_t), "hurr.jl", bstr, sizeof(bstr))
    
		#if raise && isa(ex,Expr) && is(ex.head,:error)
		#    throw(ParseError(ex.args[1]))
		#end
		#if ex === ()
		#    raise && throw(ParseError("end of input"))
		#    ex = Expr(:error, "end of input")
		#end
	catch ex
		#print("Got error: " * string(ex.error.msg) * "\n")
		return ex
	end
	return ret
end

# include("repl.jl")
# repl("1+2; pprint(11+2)", 0, 3)
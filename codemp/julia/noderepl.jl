
function repl_node(select_start::Int32, select_end::Int32, replbuffer::Cstring)::Void
	println("Got repl_node: ", select_start, select_end, replbuffer)
	#repl(select_start, select_end, unsafe_string(replbuffer))
	return
end
cb_repl_node = cfunction(repl_node, Void, (Int32, Int32, Cstring))
set_callback_repl_node(cb_repl_node)
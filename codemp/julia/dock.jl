const appdll = lib

GetCurrentDock()                                   = ccall((:imgui_get_current_dock      , appdll), Ptr{Void}, (                                             ),                                     )
GetNewID(dock) = ccall((:imgui_get_new_id, appdll), UInt32, (Ptr{Void}, ), dock)
ResetIDs(dock) = ccall((:imgui_reset_ids, appdll), Void, (Ptr{Void}, ), dock)
DockCount() = ccall((:imgui_get_dock_count, appdll), Int, (), )
DockCloseButtonPressed(dock) = ccall((:imgui_dock_closebuttonpressed, appdll), Bool, (Ptr{Void}, ), dock)
DockCloseButtonReset(dock) = ccall((:imgui_dock_closebuttonreset, appdll), Void, (Ptr{Void}, ), dock)

function NewDock(label, opened)
	# todo: some simple way to specify pos/size etc. as "user", maybe like setnextdocksize(100,200) etc.
	pos_x = 20
	pos_y = 20
	#w, h = GetWindowSize()
	w = sdl_get_window_width()
	h = sdl_get_window_height()
	size_x = w - 40
	size_y = h - 40
	location = ""
	status = 1 # Floating
	dfrow = GetDockInfoByLabel(label)
	if dfrow != nothing
		pos_x = dfrow[:pos_x]
		pos_y = dfrow[:pos_y]
		size_x = dfrow[:size_x]
		size_y = dfrow[:size_y]
		location = dfrow[:location]
		status = dfrow[:status]
	end
	ccall((:imgui_new_dock, appdll), Ptr{Void}, (Cstring, Bool, Float32, Float32, Float32, Float32, Cstring, Int32), label, opened, pos_x, pos_y, size_x, size_y, location, status)
end

function GetDockByLabel(label)
	n = DockCount()
	for i = 0 : n - 1
		d = DockByID(i)
		if d["label"] == label
			return d
		end
		imgui_log("$i = $(d["label"])\n")
	end
end

function DockByID(id)
	str = ccall((:imgui_get_dock, appdll), Cstring, (Int32, ), id)
	if str == C_NULL
		return nothing
	end
	fullstr = unsafe_string(str)
	#free(pointer(str))
	try
		parsed = parse(fullstr)
		evaled = eval(parsed)
		return evaled
	catch ex
		imgui_log("couldnt parse dock string in DockByID(): \"$fullstr\"\n")
		return nothing
	end
end

function imgui_2()
	Button("Current dock: $(GetCurrentDock())")
	node_open = TreeNode("some tree node")
	if node_open
		TreePop()
	end
end

abstract type AbstractDock end

function label(this::AbstractDock)
	t = typeof( this )
	"implement label(this::$t) for $this"
end

function imgui(this::AbstractDock)
	t = typeof( this )
	GuiText("implement imgui(this::$t) for $this")
end

type Dock{T}
	dock::Ptr{Void}
	closed::Bool
	to_ui::Any # whatever implements label() and imgui()
	eltype::DataType
	Dock{T}(to_ui) where T = new(C_NULL, false, to_ui, T)
end

eltype(this::Dock{T}) where {T} = this.eltype
elvalue(this::Dock{T}) where {T} = this.to_ui

Base.close(this::Dock{T}) where {T} = this.closed = true
closed(this::Dock{T}) where {T} = this.closed

function onclose(this::Dock{T}) where {T}
	imgui_log("generic onclose(this::Dock{T}) for $T\n")
	close(this)
end

function Base.open(this::Dock{T}) where {T}
	this.closed = false
end

function label(this::Dock{T}) where {T}
	try
		return label(elvalue(this))
	catch ex
	end
	return string(T) # by default just give the type as label
end

function imgui(this::Dock{T}) where {T}
	try
		return imgui(elvalue(this))
	catch ex
		imgui_log("Exception: $(ex)\n")
	end
	Button("to implement: function imgui(this::$T) ... end")
end

function dock(to_ui)
	newdock = Dock{ typeof(to_ui) }(to_ui)
	# probably should implement GetLabel() for to_ui and IsOpened()
	open(newdock)
	newdock.dock = NewDock(label(newdock), true)
	push!(docks, newdock)
end


# called from C++ when outside of any BeginDock/EndDock
function imguidock()
	#return
	for (i, dock) in enumerate(docks)
		pressedclose = Bool[true];
		if BeginDock(label(dock), pressedclose, dock.dock)
			# this if content is only executed when the dock is actually rendered
			if dock.dock == C_NULL
				dock.dock = GetCurrentDock()
			end	

			try # whatever happens, we need to call EndDock() so the ImGui stack isn't messing up
				imgui(dock)
			catch ex
				pprint(ex)
			end
		end
		EndDock()

		if DockCloseButtonPressed(dock.dock)
			#imgui_log("pressedclose\n")
			onclose(dock)
			DockCloseButtonReset(dock.dock)
		end

		#if closed(dock.to_ui)
		#	splice!(docks, i)
		#end
	end

	for dock in docks
		ResetIDs(dock.dock)
	end

	# meh, dont know a way yet to delete element while iterating over it... todo ask on gitter/SO
	toclose = 0
	for (i, d) in enumerate(docks)
		if closed(d)
			imgui_log("i closed\n")
			toclose = i
			break
		end
	end
	if toclose != 0
		splice!(docks, toclose)
	end
end


type TextEditor
	closed::Bool
	buf::StringBuffer
	filename::StringBuffer
	cfunction_editcallback::Ptr{Void}
	function TextEditor(filename)
		this = new()
		this.buf = StringBuffer(4096 * 4)
		this.filename = StringBuffer(256, filename)
		#this.cfunction_editcallback = cfunction(c_editcallback, Int32, (Ptr{Void}, ))
		this.cfunction_editcallback = C_NULL
		try
			loadFile(this)
		catch e
			println("loadFile: ", e)
		end
		return this
	end
end

ImGuiInputTextFlags_CallbackAlways = 256
ImGuiInputTextFlags_AllowTabInput = 1024
ImGuiInputTextFlags_CallbackCharFilter = 512

function tostring(array)
  ret = ""
  for i in array
    if i == 0
      break
    end
    ret = ret * string(Char(i))
  end
  ret
end

function Base.convert(::Type{String}, this::StringBuffer)::String
#	return String(this.buffer)
#end
#function Base.convert(::Type{String}, this::Vector{UInt8})::String
	tmp = ""
	for i in this.buffer
		if i == 0
			break
		end
		tmp = tmp * string(Char(i))
	end
	return tmp
end

label(this::TextEditor) = String(this.filename)

function imgui(this::TextEditor)
	size = WinSize() - Float32[20,40]
	editmode = ImGuiInputTextFlags_AllowTabInput # | ImGuiInputTextFlags_CallbackCharFilter
	if this.cfunction_editcallback != C_NULL
		editmode |= ImGuiInputTextFlags_CallbackAlways
	end
	InputTextMultiline("", this.buf, size, editmode, this.cfunction_editcallback , Ptr{Void}(123))

	
	if imgui_is_item_active() && imgui_pressed_ctrl_enter()
		selection = imgui_get_selection()
		repl(selection[1], selection[2], String(this.buf))
	end
	
	PushItemWidth(max(size[1] - 145, 100))
	InputText("Filename", this.filename)
	PopItemWidth()
	SameLine()
	if Button("Save")
		imgui_log("Save $(String(this.filename))\n")
		file_put_contents(String(this.filename), String(this.buf))
	end
	SameLine()
	if Button("Load")
		imgui_log("Load $(String(this.filename))\n")
		
		loadFile(this)

	end
end

function loadFile(this::TextEditor)
	loadFile(this, String(this.filename))
end

function loadFile(this::TextEditor, filename::AbstractString)
	setstring(this.buf, file_get_contents(filename))
end

function imgui(this::Dock{TextEditor})
	imgui(elvalue(this))
end

immutable ImGuiTextEditCallbackData
	EventFlag::Int32          # One of ImGuiInputTextFlags_Callback* (Read-only) type ImGuiInputTextFlags
	Flags::Int32              # What user passed to InputText()      (Read-only) type ImGuiInputTextFlags
	UserData::Ptr{Void}       # What user passed to InputText()      (Read-only)
	ReadOnly::Bool            # Read-only mode                       (Read-only)

	# CharFilter event:
	EventChar::UInt16         # type=ImWchar Character input         # Read-write (replace character or set to zero)

	# Completion,History,Always events:
	# If you modify the buffer contents make sure you update 'BufTextLen' and set 'BufDirty' to true.

	EventKey::Int32           # type = ImGuiKey Key pressed (Up/Down/TAB)   # Read-only
	Buf::Ptr{Cchar}            # Current text buffer                         # Read-write (pointed data only, can't replace the actual pointer)
	BufTextLen::Int32         # Current text length in bytes                # Read-write
	BufSize::Int32            # Maximum text length in bytes                # Read-only
	BufDirty::Bool            # Set if you modify Buf/BufTextLen!!          # Write
	CursorPos::Int32          #                                             # Read-write
	SelectionStart::Int32     #                                             # Read-write (== to SelectionEnd when no selection)
	SelectionEnd::Int32       #                                             # Read-write
end
#SaveDocksToDatabase()
#function editcallback(state::Ptr{ImGuiTextEditCallbackData})::Int32
function editcallback(state::Ptr{Void})::Int32
	ptr = Ptr{ImGuiTextEditCallbackData}(state)
	buf = ptr[:Buf]
	if ptr[:BufTextLen] > 0
		buf[1] = 65
		ptr[:BufDirty] = true
	end
	#log("stateasd = $(ptr[:BufTextLen]) BufSize $(ptr[:BufSize])\n")
	return 0 # 0 == not eat event
end
function c_editcallback(state::Ptr{Void})	
	# kinda dont wanna throw anything in a c callback
	try
		return Base.invokelatest(editcallback, state)
	catch ex
		pprint(ex)
	end
	return Int32(0)
end


Button(text, vec2=Float32[0,0])                    = ccall((:imgui_button                , appdll), Bool, (Cstring, Ptr{Float32}                        ), text, vec2                          )
BeginDock(label, pressedclose, useThisDock=C_NULL) = ccall((:imgui_begin_dock            , appdll), Bool, (Cstring, Ptr{Bool}, Ptr{Void}                ), label, pressedclose, useThisDock    )
EndDock()                                          = ccall((:imgui_end_dock              , appdll), Void, (                                             ),                                     )
GuiText(text)                                      = ccall((:imgui_text                  , appdll), Void, (Cstring,                                     ), text                                )
GuiTextColored(color, text)                        = ccall((:imgui_text_colored          , appdll), Void, (Ptr{Float32}, Cstring                        ), color, text                         )
PushID(id)                                         = ccall((:imgui_push_id               , appdll), Void, (Cint,                                        ), id                                  )
PopID()                                            = ccall((:imgui_pop_id                , appdll), Void, (                                             ),                                     )
GuiLine(a, b, color, thickness)                    = ccall((:imgui_line                  , appdll), Void, (Ptr{Float32}, Ptr{Float32}, UInt32, Float32  ), a, b, color, thickness              )
GuiPoint(a, radius, color, num_segments)           = ccall((:imgui_point                 , appdll), Void, (Ptr{Float32}, Float32, UInt32, Int32         ), a, radius, color, num_segments      )
BeginGroup()                                       = ccall((:imgui_begin_group           , appdll), Void, (                                             ),                                     )
EndGroup()                                         = ccall((:imgui_end_group             , appdll), Void, (                                             ),                                     )
PushItemWidth(width)                               = ccall((:imgui_push_item_width       , appdll), Void, (Float32,                                     ), width                               )
PopItemWidth()                                     = ccall((:imgui_pop_item_width        , appdll), Void, (                                             ),                                     )
SameLine(pos_x=Float32(0), spacing_w=Float32(-1))  = ccall((:imgui_same_line             , appdll), Void, (Float32, Float32                             ), pos_x, spacing_w                    )
IsItemClicked()                                    = ccall((:imgui_is_item_clicked       , appdll), Bool, (                                             ),                                     )
IsItemActive()                                     = ccall((:imgui_is_item_active        , appdll), Bool, (                                             ),                                     )
IsItemHovered()                                    = ccall((:imgui_is_item_hovered       , appdll), Bool, (                                             ),                                     )
IsItemHoveredRect()                                = ccall((:imgui_is_item_hovered_rect  , appdll), Bool, (                                             ),                                     )
imgui_pressed_ctrl_enter()                         = ccall((:imgui_pressed_ctrl_enter    , appdll), Bool, (                                             ),                                     )
TreeNode(label)                                    = ccall((:imgui_tree_node             , appdll), Bool, (Cstring,                                     ), label                               )
TreePop()                                          = ccall((:imgui_tree_pop              , appdll), Void, (                                             ),                                     )
Checkbox(label, v)                                 = ccall((:imgui_checkbox              , appdll), Bool, (Cstring, Ptr{Bool}                           ), label, v                            )
DragFloat(label, v, v_speed=Float32(1), v_min=Float32(0), v_max=Float32(0)) = ccall((:imgui_drag_float  , appdll), Void, (Cstring, Ptr{Float32}, Float32, Float32, Float32  ), label, v, v_speed, v_min, v_max     )


function WinSize()
	tmp = Array{Float32}(2)
	ccall((:imgui_winsize, appdll), Void, (Ptr{Float32}, ), tmp)
	return tmp
end
function imgui_get_selection()
	selection = zeros(Int32, 2)
	ccall((:imgui_get_selection, appdll), Void, (Ptr{Int32}, Ptr{Int32}), pointer(selection, 1), pointer(selection, 2))
	return selection
end
function CursorPos()
	tmp = Array{Float32}(2)
	ccall((:imgui_cursorpos, appdll), Void, (Ptr{Float32}, ), tmp)
	return tmp
end

CursorPos(pos) = ccall((:imgui_cursorpos_set, appdll), Void, (Ptr{Float32}, ), pos)

function WinSizeContents()
	tmp = Array{Float32}(2)
	ccall((:imgui_winsizecontents, appdll), Void, (Ptr{Float32}, ), tmp)
	return tmp
end

function InputText(label, stringbuffer, flags=0, callback=C_NULL, userdata=C_NULL)
	changed = ccall((:imgui_input_text, appdll), Bool,
		(Ptr{UInt8}, Ptr{UInt8}, UInt64, Int32, Ptr{Void}, Ptr{Void}),
		label, getbuffer(stringbuffer), length(stringbuffer), flags, callback, userdata
	)
	if changed
		stringbuffer.dirty = true
	end
	return changed
end

function InputTextMultiline(label, stringbuffer, size=Float32[0,0], flags=0, callback=C_NULL, userdata=C_NULL)
	changed = ccall((:imgui_input_text_multiline, appdll), Bool,
		(Ptr{UInt8}, Ptr{UInt8}, UInt64, Ptr{Float32}, Int32, Ptr{Void}, Ptr{Void}),
		label, getbuffer(stringbuffer), length(stringbuffer), size, flags, callback, userdata
	)
	if changed
		stringbuffer.dirty = true
	end
	return changed
end





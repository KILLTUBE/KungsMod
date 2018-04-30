#importall Base

if ! isdefined(:lib)
	#const lib = pwd() * "/libwebgame.so"
	if is_windows()
		const lib = "kungsmod.dll"
	else
		const lib = "../../code/libwebgame.so"
	end
end

const appdll = lib
include("math.jl")
include("console.jl")
include("utils_file.jl")
include("pointerhackery.jl")
include("stringbuffer.jl")
include("stringbuffer.jl")
include("dock.jl")
include("explorer.jl")
include("docks.jl")
include("gui.jl")
include("gui_texteditor.jl")
include("repl.jl")
include("ctypes.jl")
include("generated/cgame.jl")
include("generated/game.jl")
include("entity.jl")
include("player.jl")
include("ghoul2.jl")

# ccall(("startChakra","mychakra.dll"), Int32, ())


set_callback_repl_node( cb             ) = ccall( (:set_callback_repl_node    , lib), Void      , (Ptr{Int64},                                    ), cb                  );
Com_Init(cmds                          ) = ccall( (:Com_Init                  , lib), Void      , (Cstring,                                       ), cmds                );
Cmd_ExecuteString(cmd                  ) = ccall( (:Cmd_ExecuteString         , lib), Void      , (Cstring,                                       ), cmd                 );
Sys_SetDefaultInstallPath(cmd          ) = ccall( (:Sys_SetDefaultInstallPath , lib), Void      , (Cstring,                                       ), cmd                 );
Sys_SetBinaryPath(cmd                  ) = ccall( (:Sys_SetBinaryPath         , lib), Cstring   , (Cstring,                                       ), cmd                 );
Sys_Milliseconds(baseTime              ) = ccall( (:Sys_Milliseconds          , lib), Int32     , (Bool,                                          ), false               );
q3_main(                               ) = ccall( (:q3_main                   , lib), Int32     , (                                               )                      );
Com_Frame(                             ) = ccall( (:Com_Frame                 , lib), Void      , (                                               )                      );
NET_Init(                              ) = ccall( (:NET_Init                  , lib), Void      , (                                               )                      );
imgui_openjk_start(                    ) = ccall( (:imgui_openjk_start        , lib), Void      , (                                               )                      );
imgui_init(                            ) = ccall( (:imgui_init                , lib), Void      , (                                               )                      );
imgui_openjk_end(                      ) = ccall( (:imgui_openjk_end          , lib), Void      , (                                               )                      );
imgui_log(msg                          ) = ccall( (:imgui_log                 , lib), Int32     , (Cstring,                                       ), msg                 );
imgui_new_frame(                       ) = ccall( ("imgui_new_frame"          , lib), Void      , (                                               )                      );
imgui_render(                          ) = ccall( ("imgui_render"             , lib), Void      , (                                               )                      );
imgui_end_frame(                       ) = ccall( ("imgui_end_frame"          , lib), Void      , (                                               )                      );
imgui_enabled(                         ) = ccall( ("imgui_enabled"            , lib), Int32     , (                                               )                      );
imgui_init_3d(                         ) = ccall( ("imgui_init"               , lib), Void      , (                                               )                      );
imgui_new_line(                        ) = ccall( ("imgui_new_line"           , lib), Void      , (                                               )                      );
imgui_is_item_active(                  ) = ccall( ("imgui_is_item_active"     , lib), Bool      , (                                               )                      );
imgui_set_mousepos(left, top           ) = ccall( ("imgui_set_mousepos"       , lib), Void      , (Int32, Int32                                   ), left , top          );
imgui_set_widthheight(width, height    ) = ccall( ("imgui_set_widthheight"    , lib), Void      , (Int32, Int32                                   ), width, height       );
imgui_set_ticks(ticks                  ) = ccall( ("imgui_set_ticks"          , lib), Void      , (Int32,                                         ), ticks               );
imgui_mouse_set_button(button, state   ) = ccall( ("imgui_mouse_set_button"   , lib), Void      , (Int32, Int32                                   ), button, state       ); # button: 0,1,2 aka left/right/middle, state: true/false
Com_BusyWait(                          ) = ccall( (:Com_BusyWait              , lib), Void      , (                                               )                      );
win_present(                           ) = ccall( (:win_present               , lib), Void      , (                                               )                      );
Sys_PlatformInit(                      ) = ccall( (:Sys_PlatformInit          , lib), Void      , (                                               )                      );
sdl_get_window_width(                  ) = ccall( ("sdl_get_window_width"     , lib), Int32     , (                                               )                      );
sdl_get_window_height(                 ) = ccall( ("sdl_get_window_height"    , lib), Int32     , (                                               )                      );
sdl_get_mouse_left(                    ) = ccall( ("sdl_get_mouse_left"       , lib), Int32     , (                                               )                      );
sdl_get_mouse_top(                     ) = ccall( ("sdl_get_mouse_top"        , lib), Int32     , (                                               )                      );
sdl_get_ticks(                         ) = ccall( ("sdl_get_ticks"            , lib), Int32     , (                                               )                      );
sdl_mouse_pressed_left(                ) = ccall( ("sdl_mouse_pressed_left"   , lib), Int32     , (                                               )                      );
sdl_mouse_pressed_right(               ) = ccall( ("sdl_mouse_pressed_right"  , lib), Int32     , (                                               )                      );
sdl_mouse_pressed_middle(              ) = ccall( ("sdl_mouse_pressed_middle" , lib), Int32     , (                                               )                      );
jl_g_entities(                         ) = ccall( (:jl_g_entities             , lib), Ptr{Int64}, (                                               )                      );
jl_g_entities_sizeof(                  ) = ccall( (:jl_g_entities_sizeof      , lib), Int32     , (                                               )                      );
jl_cg_entities(                         ) = ccall( (:jl_cg_entities             , lib), Ptr{Int64}, (                                               )                      );
jl_cg_entities_sizeof(                  ) = ccall( (:jl_cg_entities_sizeof      , lib), Int32     , (                                               )                      );


Key_GetCatcher(              ) = ccall( (:Key_GetCatcher, lib), Int32     , (                                               )                      );

const KEYCATCH_IMGUI = Int32(1 << 0)

function init()
	Sys_PlatformInit();
	Sys_Milliseconds(false); # get the initial time base
	Sys_SetBinaryPath( "" );
	Sys_SetDefaultInstallPath( "") # Sys_BinaryPath() );
	#char *startString = argsToString(argc, argv);
	Com_Init("devmap mp_toujane");

	NET_Init();

	imgui_openjk_start();
	imgui_init();
	imgui_openjk_end();
end

function mainloop()
	Com_BusyWait();
	imgui_set_ticks( sdl_get_ticks() );
	imgui_new_frame();
	Com_Frame();

	Button("lllooooolll")

	if Bool( Key_GetCatcher() & KEYCATCH_IMGUI )
		imguidock()
	end
	
	imgui_openjk_start();
	imgui_end_frame();
	imgui_openjk_end();

	win_present();
end

init()


function repl_node(select_start::Int32, select_end::Int32, replbuffer::Cstring)::Void
	println("Got repl_node: ", select_start, select_end, replbuffer)
	repl(select_start, select_end, unsafe_string(replbuffer))
	return
end
cb_repl_node = cfunction(repl_node, Void, (Int32, Int32, Cstring))
set_callback_repl_node(cb_repl_node)



function onReady()
	try
		# ready.jl stuff
		global docks = Vector{Dock}()
		testeditor = TextEditor("testeditor")
		dock(testeditor)
		global explorer = Explorer(".")
		dock(explorer)
		#dock( DockThreads() )
	catch e
		println("onReady ", e)
	end
end

onReady()

Timer(function(timer)
	Base.invokelatest(mainloop)
end, 0, 1 / 60)



if ! isdefined(:lib)
	#const lib = pwd() * "/libwebgame.so"
	if is_windows()
		const lib = "kungsmod.dll"
	else
		const lib = "../../code/libwebgame.so"
	end
end

const appdll = lib
include("stringbuffer.jl")
include("dock.jl")
#include("docks.jl")
include("gui.jl")
include("gui_texteditor.jl")

# ccall(("startChakra","mychakra.dll"), Int32, ())



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
Com_BusyWait(                          ) = ccall( (:Com_BusyWait              , lib), Void      , (                                               )                      );
imgui_new_frame(                       ) = ccall( (:imgui_new_frame           , lib), Void      , (                                               )                      );
imgui_end_frame(                       ) = ccall( (:imgui_end_frame           , lib), Void      , (                                               )                      );
win_present(                           ) = ccall( (:win_present               , lib), Void      , (                                               )                      );
Sys_PlatformInit(                      ) = ccall( (:Sys_PlatformInit          , lib), Void      , (                                               )                      );

function init()
	Sys_PlatformInit();
	Sys_Milliseconds(false); # get the initial time base
	Sys_SetBinaryPath( "" );
	Sys_SetDefaultInstallPath( "") # Sys_BinaryPath() );
	#char *startString = argsToString(argc, argv);
	Com_Init("");

	NET_Init();

	imgui_openjk_start();
	imgui_init();
	imgui_openjk_end();
end

function mainloop()

	while true
		Com_BusyWait();
		imgui_new_frame();
		Com_Frame();

		Button("lllooooolll")
		
		imgui_openjk_start();
		imgui_end_frame();
		imgui_openjk_end();

		win_present();
	end
end

init()
mainloop()


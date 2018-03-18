#============================================================================
# Copyright (C) 2013 - 2015, OpenJK contributors
#
# This file is part of the OpenJK source code.
#
# OpenJK is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#============================================================================

# Make sure the user is not executing this script directly
if(NOT InOpenJK)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InOpenJK)

if(BuildSPRdGL2)

	set(SPRDGL2RendererIncludeDirectories ${SPDir})
	set(SPRDGL2RendererIncludeDirectories
		${SharedDir}
		${SPRDGL2RendererIncludeDirectories}
		"${SPDir}/rd-gl2"
		"${GSLIncludeDirectory}"
		)

	# Modular Renderer crap (let's hope this works..)

	# Defines
	set(SPRDGL2Defines ${SharedDefines} "RENDERER" "_JK2EXE")

	# Files

	# GHOUL 2
	set(SPRDGL2G2Files
		"${SPDir}/ghoul2/G2.h"
		"${SPDir}/ghoul2/ghoul2_gore.h"
		"${SPDir}/rd-gl2/G2_API.cpp"
		"${SPDir}/rd-gl2/G2_bolts.cpp"
		"${SPDir}/rd-gl2/G2_bones.cpp"
		"${SPDir}/rd-gl2/G2_misc.cpp"
		"${SPDir}/rd-gl2/G2_surfaces.cpp"
		)
	source_group("ghoul2" FILES ${SPRDGL2G2Files})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2G2Files})

    # Transparently use either bundled or system jpeg.
    list(APPEND SPRDGL2RendererIncludeDirectories ${JPEG_INCLUDE_DIR})
    list(APPEND SPRDGL2RendererLibraries          ${JPEG_LIBRARIES})

    # Transparently use either bundled or system libpng.  Order is important --
    # libpng used zlib, so it must come before it on the linker command line.
    list(APPEND SPRDGL2RendererIncludeDirectories ${PNG_INCLUDE_DIRS})
    list(APPEND SPRDGL2RendererLibraries          ${PNG_LIBRARIES})

    # Transparently use either bundled or system zlib.
    list(APPEND SPRDGL2RendererIncludeDirectories ${ZLIB_INCLUDE_DIR})
    list(APPEND SPRDGL2RendererLibraries          ${ZLIB_LIBRARIES})

    # Transparently use our bundled minizip.
    list(APPEND SPRDGL2RendererIncludeDirectories ${MINIZIP_INCLUDE_DIRS})
    list(APPEND SPRDGL2RendererLibraries          ${MINIZIP_LIBRARIES})

    # Transparantly make use of all renderer directories
    list(APPEND SPRDGL2RendererIncludeDirectories "${SPDir}/rd-common")
    list(APPEND SPRDGL2RendererIncludeDirectories "${SPDir}/rd-gl2")

	# Misc files
	set(SPRDGL2CommonFiles
		"${SPDir}/qcommon/matcomp.cpp"
		"${SPDir}/qcommon/q_shared.cpp"
		"${SPDir}/qcommon/q_shared.h"
		"${SPDir}/qcommon/ojk_i_saved_game.h"
		"${SPDir}/qcommon/ojk_saved_game_class_archivers.h"
		"${SPDir}/qcommon/ojk_saved_game_helper.h"
		"${SPDir}/qcommon/ojk_saved_game_helper_fwd.h"
		"${SPDir}/qcommon/ojk_scope_guard.h"
		${SharedCommonFiles}
		)
	source_group("common" FILES ${SPRDGL2CommonFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2CommonFiles})

	# Misc files
	set(SPRDGL2CommonSafeFiles
		${SharedCommonSafeFiles}
		)
	source_group("common/safe" FILES ${SPRDGL2CommonSafeFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2CommonSafeFiles})

	# main files
	set(SPRDGL2MainFiles
		"${SPDir}/rd-gl2/compose_models.cpp"  
		"${SPDir}/rd-gl2/compose_models.h"
		"${SPDir}/rd-gl2/glext.h"
		"${SPDir}/rd-gl2/iqm.h"	
		"${SPDir}/rd-gl2/qgl.h"
		"${SPDir}/rd-gl2/tr_allocator.cpp"
		"${SPDir}/rd-gl2/tr_allocator.h"
		"${SPDir}/rd-gl2/tr_backend.cpp"
		"${SPDir}/rd-gl2/tr_bsp.cpp"
		"${SPDir}/rd-gl2/tr_cache.cpp"
		"${SPDir}/rd-gl2/tr_cache.h"
		"${SPDir}/rd-gl2/tr_cmds.cpp"
		"${SPDir}/rd-gl2/tr_curve.cpp"
		"${SPDir}/rd-gl2/tr_decals.cpp"
		"${SPDir}/rd-gl2/tr_extensions.cpp"
		"${SPDir}/rd-gl2/tr_extramath.cpp"
		"${SPDir}/rd-gl2/tr_extramath.h"
		"${SPDir}/rd-gl2/tr_extratypes.h"
		"${SPDir}/rd-gl2/tr_fbo.cpp"
		"${SPDir}/rd-gl2/tr_fbo.h"
		"${SPDir}/rd-gl2/tr_flares.cpp"
		"${SPDir}/rd-gl2/tr_glsl.cpp"
		"${SPDir}/rd-gl2/tr_glsl_parse.cpp"
		"${SPDir}/rd-gl2/tr_image.cpp"
		"${SPDir}/rd-gl2/tr_image_dds.cpp"
		"${SPDir}/rd-gl2/tr_imgui.cpp"
		"${SPDir}/rd-gl2/tr_init.cpp"
		"${SPDir}/rd-gl2/tr_light.cpp"
		"${SPDir}/rd-gl2/tr_local.h"
		"${SPDir}/rd-gl2/tr_main.cpp"
		"${SPDir}/rd-gl2/tr_marks.cpp"
		"${SPDir}/rd-gl2/tr_model.cpp"
		"${SPDir}/rd-gl2/tr_model_iqm.cpp"
		"${SPDir}/rd-gl2/tr_model_mdr.cpp"
		"${SPDir}/rd-gl2/tr_model_md3.cpp"
		"${SPDir}/rd-gl2/tr_model_ghoul2.cpp"
		"${SPDir}/rd-gl2/tr_postprocess.cpp"
		"${SPDir}/rd-gl2/tr_postprocess.h"
		"${SPDir}/rd-gl2/tr_scene.cpp"
		"${SPDir}/rd-gl2/tr_shade.cpp"
		"${SPDir}/rd-gl2/tr_shade_calc.cpp"
		"${SPDir}/rd-gl2/tr_shader.cpp"
		"${SPDir}/rd-gl2/tr_shadows.cpp"
		"${SPDir}/rd-gl2/tr_skin.cpp"
		"${SPDir}/rd-gl2/tr_sky.cpp"
		"${SPDir}/rd-gl2/tr_stl.cpp"
		"${SPDir}/rd-gl2/tr_stl.h"
		"${SPDir}/rd-gl2/tr_subs.cpp"
		"${SPDir}/rd-gl2/tr_surface.cpp"
		"${SPDir}/rd-gl2/tr_vbo.cpp"
		"${SPDir}/rd-gl2/tr_world.cpp"
		"${SPDir}/rd-gl2/tr_weather.cpp"
		"${SPDir}/rd-gl2/tr_weather.h"
		)
	source_group("renderer" FILES ${SPRDGL2MainFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2MainFiles})

	file(GLOB SPRDGL2GLSLFiles "${SPDir}/rd-gl2/glsl/*.glsl")
	source_group("renderer\\glsl" FILES ${SPRDGL2GLSLFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2GLSLFiles})
	
	set(SPRDGL2ImGuiOpenJKFiles  
		"${SPDir}/rd-gl2/imgui_openjk/imgui_openjk_default_docks.cpp"  
		"${SPDir}/rd-gl2/imgui_openjk/imgui_openjk_default_docks.h"
		)  
	source_group("imgui_openjk" FILES ${SPRDGL2ImGuiOpenJKFiles})  
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2ImGuiOpenJKFiles})

	set(SPRDGL2ImGuiFiles
		"${SPDir}/rd-gl2/imgui/ccall/ccall.h"
		"${SPDir}/rd-gl2/imgui/MagicFile/magicfile.cpp"
		"${SPDir}/rd-gl2/imgui/MagicFile/magicfile.h"
		"${SPDir}/rd-gl2/imgui/ffi.cpp"
		"${SPDir}/rd-gl2/imgui/imconfig.h"
		"${SPDir}/rd-gl2/imgui/imgui.cpp"
		"${SPDir}/rd-gl2/imgui/imgui.h"
		"${SPDir}/rd-gl2/imgui/imgui_api.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_api.h"
		"${SPDir}/rd-gl2/imgui/imgui_c_utils.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_c_utils.h"
		"${SPDir}/rd-gl2/imgui/imgui_default_docks.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_default_docks.h"
		"${SPDir}/rd-gl2/imgui/imgui_demo.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_dock.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_dock.h"
		"${SPDir}/rd-gl2/imgui/imgui_draw.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_fixedarea.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_fixedarea.h"
		"${SPDir}/rd-gl2/imgui/imgui_impl_idtech3_gles.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_impl_idtech3_gles.h"
		"${SPDir}/rd-gl2/imgui/imgui_internal.h"
		"${SPDir}/rd-gl2/imgui/imgui_utils.cpp"
		"${SPDir}/rd-gl2/imgui/imgui_utils.h"
		"${SPDir}/rd-gl2/imgui/include_imgui.h"
		"${SPDir}/rd-gl2/imgui/include_quakegl.h"
		"${SPDir}/rd-gl2/imgui/stb_rect_pack.h"
		"${SPDir}/rd-gl2/imgui/stb_textedit.h"
		"${SPDir}/rd-gl2/imgui/stb_truetype.h"
		)
	source_group("imgui" FILES ${SPRDGL2ImGuiFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2ImGuiFiles})

	set(SPRDGL2ImGuiDockFiles
		"${SPDir}/rd-gl2/imgui_docks/dock.cpp"
		"${SPDir}/rd-gl2/imgui_docks/dock.h"
		"${SPDir}/rd-gl2/imgui_docks/dock_console.cpp"
		"${SPDir}/rd-gl2/imgui_docks/dock_console.h"
		"${SPDir}/rd-gl2/imgui_docks/dock_julia.cpp"
		"${SPDir}/rd-gl2/imgui_docks/dock_julia.h"
		"${SPDir}/rd-gl2/imgui_docks/dock_node.cpp"
		"${SPDir}/rd-gl2/imgui_docks/dock_node.h"
		"${SPDir}/rd-gl2/imgui_docks/dock_repl.cpp"
		"${SPDir}/rd-gl2/imgui_docks/dock_repl.h"
		"${SPDir}/rd-gl2/imgui_docks/dock_skeleton.cpp"
		"${SPDir}/rd-gl2/imgui_docks/dock_skeleton.h"
		)
	source_group("imgui_docks" FILES ${SPRDGL2ImGuiDockFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2ImGuiDockFiles})

	set(SPRDGL2ImGuiOpenJKFiles
		"${SPDir}/rd-gl2/imgui_openjk/imgui_openjk_default_docks.h"
		"${SPDir}/rd-gl2/imgui_openjk/imgui_openjk_default_docks.cpp"
		"${SPDir}/rd-gl2/imgui_openjk/gluecode.h"
		"${SPDir}/rd-gl2/imgui_openjk/gluecode.cpp"
		)
	source_group("imgui_openjk" FILES ${SPRDGL2ImGuiOpenJKFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2ImGuiOpenJKFiles})

	set(SPRDGL2ImGuiDockOpenJKFiles 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_shadereditor.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_shadereditor.h" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_mapinfo.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_mapinfo.h" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_perf.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_perf.h" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_controlflow.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_controlflow.h" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_models.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_models.h" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_all.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_all.h" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_mdxm.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_mdxm.h" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_mdxa.cpp" 
		"${SPDir}/rd-gl2/imgui_docks_openjk/dock_mdxa.h" 
		) 
	source_group("imgui_docks_openjk" FILES ${SPRDGL2ImGuiDockOpenJKFiles}) 
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2ImGuiDockOpenJKFiles}) 


	set(SPRDGL2RdCommonFiles
		"${SPDir}/rd-common/mdx_format.h"
		"${SPDir}/rd-common/tr_common.h"
		"${SPDir}/rd-common/tr_font.cpp"
		"${SPDir}/rd-common/tr_font.h"
		"${SPDir}/rd-common/tr_image_load.cpp"
		"${SPDir}/rd-common/tr_image_jpg.cpp"
		"${SPDir}/rd-common/tr_image_tga.cpp"
		"${SPDir}/rd-common/tr_image_png.cpp"
		"${SPDir}/rd-common/tr_noise.cpp"
		"${SPDir}/rd-common/tr_public.h"
		"${SPDir}/rd-common/tr_types.h")
	source_group("rd-common" FILES ${SPRDGL2RdCommonFiles})
	set(SPRDGL2Files ${SPRDGL2Files} ${SPRDGL2RdCommonFiles})

	find_package(OpenGL REQUIRED)
	set(SPRDGL2RendererIncludeDirectories ${SPRDGL2RendererIncludeDirectories} ${OPENGL_INCLUDE_DIR})
	set(SPRDGL2RendererLibraries ${SPRDGL2RendererLibraries} ${OPENGL_LIBRARIES})

	source_group("renderer" FILES ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp)
	set(SPRDGL2Files ${SPRDGL2Files} ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp)
	
	set(SPRDGL2RendererIncludeDirectories ${SPRDGL2RendererIncludeDirectories} ${OpenJKLibDir})

	function(add_sp_renderer_project ProjectName Label EngineName InstallDir Component)
		add_library(${ProjectName} SHARED ${SPRDGL2Files})
		if(NOT MSVC)
			# remove "lib" prefix for .so/.dylib files
			set_target_properties(${ProjectName} PROPERTIES PREFIX "")
		endif()

		if(WIN32)
			install(TARGETS ${ProjectName}
				RUNTIME
				DESTINATION ${InstallDir}
				COMPONENT ${Component})
		else(WIN32)
			if(MakeApplicationBundles AND (BuildSPEngine))
				install(TARGETS ${ProjectName}
					LIBRARY
					DESTINATION "${InstallDir}/${EngineName}.app/Contents/MacOS/"
					COMPONENT ${Component})
			else()
				install(TARGETS ${ProjectName}
					LIBRARY
					DESTINATION ${InstallDir}
					COMPONENT ${Component})
			endif()
		endif()

		set_target_properties(${ProjectName} PROPERTIES COMPILE_DEFINITIONS "${SPRDGL2Defines}")

		# Hide symbols not explicitly marked public.
		set_property(TARGET ${ProjectName} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})

		set_target_properties(${ProjectName} PROPERTIES INCLUDE_DIRECTORIES "${SPRDGL2RendererIncludeDirectories}")
		set_target_properties(${ProjectName} PROPERTIES PROJECT_LABEL ${Label})

		target_link_libraries(${ProjectName} ${SPRDGL2RendererLibraries})
	endfunction(add_sp_renderer_project)

	if(BuildSPRdGL2)
		add_sp_renderer_project(${SPRDGL2Renderer} "SP GL2 Renderer" ${SPEngine} ${JKAInstallDir} ${JKASPClientComponent})
	endif(BuildSPRdGL2)
	
	# GLSL shader file generator
	add_executable(compact_glsl
		${SPDir}/rd-gl2/glsl/compact.cpp
		${SPDir}/rd-gl2/tr_allocator.cpp
		${SPDir}/rd-gl2/tr_allocator.h
		${SPDir}/rd-gl2/tr_glsl_parse.cpp
		)
	# set_target_properties(compact_glsl PROPERTIES COMPILE_DEFINITIONS "GLSL_BUILDTOOL")
	target_compile_definitions(compact_glsl PRIVATE "GLSL_BUILDTOOL" ${SharedDefines})
	set_target_properties(compact_glsl PROPERTIES INCLUDE_DIRECTORIES "${SPRDGL2RendererIncludeDirectories}")
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp
		COMMAND compact_glsl ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp ${SPRDGL2GLSLFiles}
		DEPENDS compact_glsl ${SPRDGL2GLSLFiles})

endif(BuildSPRdGL2)

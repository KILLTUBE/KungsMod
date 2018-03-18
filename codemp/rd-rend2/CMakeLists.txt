# Make sure the user is not executing this script directly
if(NOT InOpenJK)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InOpenJK)

set(MPRend2IncludeDirectories
	"${SharedDir}"
	"${MPDir}"
	"${MPDir}/rd-rend2"
	"${GSLIncludeDirectory}"
	)

set(MPRend2Files
	"${MPDir}/rd-rend2/iqm.h"
	"${MPDir}/rd-rend2/glext.h"
	"${MPDir}/rd-rend2/qgl.h"
	"${MPDir}/rd-rend2/G2_API.cpp"
	"${MPDir}/rd-rend2/G2_bolts.cpp"
	"${MPDir}/rd-rend2/G2_bones.cpp"
	"${MPDir}/rd-rend2/G2_misc.cpp"
	"${MPDir}/rd-rend2/G2_surfaces.cpp"
	"${MPDir}/rd-rend2/tr_allocator.cpp"
	"${MPDir}/rd-rend2/tr_allocator.h"
	"${MPDir}/rd-rend2/tr_animation.cpp"
	"${MPDir}/rd-rend2/tr_backend.cpp"
	"${MPDir}/rd-rend2/tr_bsp.cpp"
	"${MPDir}/rd-rend2/tr_cache.cpp"
	"${MPDir}/rd-rend2/tr_cache.h"
	"${MPDir}/rd-rend2/tr_cmds.cpp"
	"${MPDir}/rd-rend2/tr_curve.cpp"
	"${MPDir}/rd-rend2/tr_decals.cpp"
	"${MPDir}/rd-rend2/tr_extensions.cpp"
	"${MPDir}/rd-rend2/tr_extramath.cpp"
	"${MPDir}/rd-rend2/tr_extramath.h"
	"${MPDir}/rd-rend2/tr_extratypes.h"
	"${MPDir}/rd-rend2/tr_fbo.cpp"
	"${MPDir}/rd-rend2/tr_fbo.h"
	"${MPDir}/rd-rend2/tr_flares.cpp"
	"${MPDir}/rd-rend2/tr_ghoul2.cpp"
	"${MPDir}/rd-rend2/tr_glsl.cpp"
	"${MPDir}/rd-rend2/tr_glsl_parse.cpp"
	"${MPDir}/rd-rend2/tr_image.cpp"
	"${MPDir}/rd-rend2/tr_init.cpp"
	"${MPDir}/rd-rend2/tr_light.cpp"
	"${MPDir}/rd-rend2/tr_local.h"
	"${MPDir}/rd-rend2/tr_main.cpp"
	"${MPDir}/rd-rend2/tr_marks.cpp"
	"${MPDir}/rd-rend2/tr_mesh.cpp"
	"${MPDir}/rd-rend2/tr_model.cpp"
	"${MPDir}/rd-rend2/tr_model_iqm.cpp"
	"${MPDir}/rd-rend2/tr_postprocess.cpp"
	"${MPDir}/rd-rend2/tr_postprocess.h"
	"${MPDir}/rd-rend2/tr_scene.cpp"
	"${MPDir}/rd-rend2/tr_shade.cpp"
	"${MPDir}/rd-rend2/tr_shade_calc.cpp"
	"${MPDir}/rd-rend2/tr_shader.cpp"
	"${MPDir}/rd-rend2/tr_shadows.cpp"
	"${MPDir}/rd-rend2/tr_skin.cpp"
	"${MPDir}/rd-rend2/tr_sky.cpp"
	"${MPDir}/rd-rend2/tr_subs.cpp"
	"${MPDir}/rd-rend2/tr_surface.cpp"
	"${MPDir}/rd-rend2/tr_vbo.cpp"
	"${MPDir}/rd-rend2/tr_world.cpp"
	"${MPDir}/rd-rend2/tr_weather.cpp"
	"${MPDir}/rd-rend2/tr_weather.h"
	"${MPDir}/rd-rend2/tr_imgui.cpp"
	"${MPDir}/rd-rend2/compose_models.cpp"
	"${MPDir}/rd-rend2/compose_models.h"
	)
source_group("renderer" FILES ${MPRend2Files})

file(GLOB MPRend2GLSLFiles "${MPDir}/rd-rend2/glsl/*.glsl")
source_group("renderer\\glsl" FILES ${MPRend2GLSLFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2GLSLFiles})

set(MPRend2Ghoul2Files
	"${MPDir}/ghoul2/g2_local.h"
	"${MPDir}/ghoul2/ghoul2_shared.h"
	"${MPDir}/ghoul2/G2_gore.cpp"
	"${MPDir}/ghoul2/G2_gore.h")
source_group("ghoul2" FILES ${MPRend2Ghoul2Files})
set(MPRend2Files ${MPRend2Files} ${MPRend2Ghoul2Files})

set(MPRend2RdCommonFiles
	"${MPDir}/rd-common/mdx_format.h"
	"${MPDir}/rd-common/tr_common.h"
	"${MPDir}/rd-common/tr_font.cpp"
	"${MPDir}/rd-common/tr_font.h"
	"${MPDir}/rd-common/tr_image_load.cpp"
	"${MPDir}/rd-common/tr_image_jpg.cpp"
	"${MPDir}/rd-common/tr_image_tga.cpp"
	"${MPDir}/rd-common/tr_image_png.cpp"
	"${MPDir}/rd-common/tr_noise.cpp"
	"${MPDir}/rd-common/tr_public.h"
	"${MPDir}/rd-common/tr_types.h")
source_group("rd-common" FILES ${MPRend2RdCommonFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2RdCommonFiles})


set(MPRend2ImGuiFiles
	"${MPDir}/rd-rend2/imgui/ccall/ccall.h"
	"${MPDir}/rd-rend2/imgui/MagicFile.cpp/magicfile.cpp"
	"${MPDir}/rd-rend2/imgui/MagicFile.cpp/magicfile.h"
	"${MPDir}/rd-rend2/imgui/ffi.cpp"
	"${MPDir}/rd-rend2/imgui/imconfig.h"
	"${MPDir}/rd-rend2/imgui/imgui.cpp"
	"${MPDir}/rd-rend2/imgui/imgui.h"
	"${MPDir}/rd-rend2/imgui/imgui_api.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_api.h"
	"${MPDir}/rd-rend2/imgui/imgui_c_utils.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_c_utils.h"
	"${MPDir}/rd-rend2/imgui/imgui_default_docks.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_default_docks.h"
	"${MPDir}/rd-rend2/imgui/imgui_demo.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_dock.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_dock.h"
	"${MPDir}/rd-rend2/imgui/imgui_draw.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_fixedarea.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_fixedarea.h"
	"${MPDir}/rd-rend2/imgui/imgui_impl_idtech3_gles.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_impl_idtech3_gles.h"
	"${MPDir}/rd-rend2/imgui/imgui_internal.h"
	"${MPDir}/rd-rend2/imgui/imgui_utils.cpp"
	"${MPDir}/rd-rend2/imgui/imgui_utils.h"
	"${MPDir}/rd-rend2/imgui/include_imgui.h"
	"${MPDir}/rd-rend2/imgui/include_quakegl.h"
	"${MPDir}/rd-rend2/imgui/stb_rect_pack.h"
	"${MPDir}/rd-rend2/imgui/stb_textedit.h"
	"${MPDir}/rd-rend2/imgui/stb_truetype.h"
)
source_group("imgui" FILES ${MPRend2ImGuiFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2ImGuiFiles})


set(MPRend2ImGuiOpenJKFiles
	"${MPDir}/rd-rend2/imgui_openjk/imgui_openjk_default_docks.h"
	"${MPDir}/rd-rend2/imgui_openjk/imgui_openjk_default_docks.cpp"
	"${MPDir}/rd-rend2/imgui_openjk/gluecode.h"
	"${MPDir}/rd-rend2/imgui_openjk/gluecode.cpp"
)
source_group("imgui_openjk" FILES ${MPRend2ImGuiOpenJKFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2ImGuiOpenJKFiles})

set(MPRend2ImGuiDockFiles
	"${MPDir}/rd-rend2/imgui_docks/dock.cpp"
	"${MPDir}/rd-rend2/imgui_docks/dock.h"
	"${MPDir}/rd-rend2/imgui_docks/dock_console.cpp"
	"${MPDir}/rd-rend2/imgui_docks/dock_console.h"
	"${MPDir}/rd-rend2/imgui_docks/dock_julia.cpp"
	"${MPDir}/rd-rend2/imgui_docks/dock_julia.h"
	"${MPDir}/rd-rend2/imgui_docks/dock_node.cpp"
	"${MPDir}/rd-rend2/imgui_docks/dock_node.h"
	"${MPDir}/rd-rend2/imgui_docks/dock_repl.cpp"
	"${MPDir}/rd-rend2/imgui_docks/dock_repl.h"
	"${MPDir}/rd-rend2/imgui_docks/dock_skeleton.cpp"
	"${MPDir}/rd-rend2/imgui_docks/dock_skeleton.h"
)
source_group("imgui_docks" FILES ${MPRend2ImGuiDockFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2ImGuiDockFiles})

set(MPRend2ImGuiDockOpenJKFiles
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_shadereditor.cpp"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_shadereditor.h"
#	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_mapinfo.cpp"
#	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_mapinfo.h"
#	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_perf.cpp"
#	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_perf.h"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_controlflow.cpp"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_controlflow.h"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_models.cpp"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_models.h"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_all.cpp"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_all.h"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_mdxm.cpp"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_mdxm.h"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_mdxa.cpp"
	"${MPDir}/rd-rend2/imgui_docks_openjk/dock_mdxa.h"
)
source_group("imgui_docks_openjk" FILES ${MPRend2ImGuiDockOpenJKFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2ImGuiDockOpenJKFiles})

set(MPRend2CommonFiles
	"${MPDir}/qcommon/matcomp.cpp"
	"${MPDir}/qcommon/q_shared.cpp"
	"${SharedCommonFiles}")
source_group("common" FILES ${MPRend2CommonFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2CommonFiles})

set(MPRend2CommonSafeFiles
	${SharedCommonSafeFiles}
	)
source_group("common/safe" FILES ${MPRend2CommonSafeFiles})
set(MPRend2Files ${MPRend2Files} ${MPRend2CommonSafeFiles})

# Transparently use either bundled or system libjpeg.
list(APPEND MPRend2IncludeDirectories ${JPEG_INCLUDE_DIR})
list(APPEND MPRend2Libraries          ${JPEG_LIBRARIES})

# Transparently use either bundled or system libpng.  Order is important --
# libpng used zlib, so it must come before it on the linker command line.
list(APPEND MPRend2IncludeDirectories ${PNG_INCLUDE_DIRS})
list(APPEND MPRend2Libraries          ${PNG_LIBRARIES})

# Transparently use either bundled or system zlib.
list(APPEND MPRend2IncludeDirectories ${ZLIB_INCLUDE_DIR})
list(APPEND MPRend2Libraries          ${ZLIB_LIBRARIES})

# Transparently use our bundled minizip.
list(APPEND MPRend2IncludeDirectories ${MINIZIP_INCLUDE_DIRS})
list(APPEND MPRend2Libraries          ${MINIZIP_LIBRARIES})

find_package(OpenGL REQUIRED)
set(MPRend2IncludeDirectories ${MPRend2IncludeDirectories} ${OPENGL_INCLUDE_DIR})
set(MPRend2Libraries ${MPRend2Libraries} ${OPENGL_LIBRARIES})

source_group("renderer" FILES ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp)
set(MPRend2Files ${MPRend2Files} ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp)

set(MPRend2IncludeDirectories ${MPRend2IncludeDirectories} ${OpenJKLibDir})
add_library(${MPRend2} SHARED ${MPRend2Files})

if(NOT MSVC)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${MPRend2} PROPERTIES PREFIX "")
endif()

if(WIN32)
	install(TARGETS ${MPRend2}
		RUNTIME
		DESTINATION ${JKAInstallDir}
		COMPONENT ${JKAMPClientComponent})
else(WIN32)
	if(MakeApplicationBundles AND BuildMPEngine)
		install(TARGETS ${MPRend2}
			LIBRARY
			DESTINATION "${JKAInstallDir}/${MPEngine}.app/Contents/MacOS/"
			COMPONENT ${JKAMPClientComponent})
	else()
		install(TARGETS ${MPRend2}
			LIBRARY
			DESTINATION ${JKAInstallDir}
			COMPONENT ${JKAMPClientComponent})
	endif()
endif()

set_target_properties(${MPRend2} PROPERTIES COMPILE_DEFINITIONS "${SharedDefines}")

# Hide symbols not explicitly marked public.
set_property(TARGET ${MPRend2} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})
set_target_properties(${MPRend2} PROPERTIES INCLUDE_DIRECTORIES "${MPRend2IncludeDirectories}")
set_target_properties(${MPRend2} PROPERTIES PROJECT_LABEL "MP Rend2 Renderer")
target_link_libraries(${MPRend2} ${MPRend2Libraries})

# GLSL shader file generator
add_executable(compact_glsl
	${MPDir}/rd-rend2/glsl/compact.cpp
	${MPDir}/rd-rend2/tr_allocator.cpp
	${MPDir}/rd-rend2/tr_allocator.h
	${MPDir}/rd-rend2/tr_glsl_parse.cpp
	)
set_target_properties(compact_glsl PROPERTIES COMPILE_DEFINITIONS "GLSL_BUILDTOOL")
set_target_properties(compact_glsl PROPERTIES INCLUDE_DIRECTORIES "${MPRend2IncludeDirectories}")
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp
	COMMAND compact_glsl ${CMAKE_CURRENT_BINARY_DIR}/glsl_shaders.cpp ${MPRend2GLSLFiles}
	DEPENDS compact_glsl ${MPRend2GLSLFiles})

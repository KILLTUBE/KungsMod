#include "op_all.h"

//#include "op_cube.h"
#include "../ops/op_mesh_editor.h"
#include "../ops/op_renderer.h"
#include "../ops/op_random_shit.h"
//#include "op_timer.h"
//#include "op_logger.h"
#include "../ops/op_checkerboard.h"
#include "../ops/op_keyboard.h"
#include "../ops/op_logger.h"
#include "../ops/op_switch.h"

#include "../ops/op_craft.h"
#include "../ops/op_perspective.h"
#include "../ops/op_matrix_ortho.h"
#include "../ops/op_matrix.h"
#include "../ops/op_matrix_multiply.h"
#include "../ops/op_matrix_rotate.h"
#include "../ops/op_matrix_translate.h"
#include "../ops/op_matrix_transpose.h"
#include "../ops/op_matrix_inverse.h"
#include "../ops/op_matrix_scale.h"
#include "../ops/op_matrix_identity.h"
#include "../ops/op_matrix_shear.h"
#include "../ops/op_matrix_decompose.h"
#include "../ops/op_matrix_multiply_point.h"
#include "../ops/op_matrices.h"
#include "../ops/op_quaternion.h"
#include "../ops/op_quaternion_multiply.h"
#include "../ops/op_quaternion_inverse.h"

// JavaScript
#include "../ops/op_javascript.h"
#include "../ops/op_expression.h"
#include "../ops/op_javascript_file.h"
#include "../ops/op_tofloat.h"

#include "../ops/op_value.h"
#include "../ops/op_divide.h"
#include "../ops/op_multiply.h"
#include "../ops/op_plus.h"
#include "../ops/op_minus.h"
#include "../ops/op_sin.h"
#include "../ops/op_cos.h"
#include "../ops/op_negate.h"
#include "../ops/op_if.h"
#include "../ops/op_gl_fragment_shader.h"
#include "../ops/op_gl_vertex_shader.h"
#include "../ops/op_gl_program.h"
#include "../ops/op_gl_framebuffer.h"
#include "../ops/op_gl_buffer.h"
#include "../ops/op_gl_attrib.h"
#include "../ops/op_gl_uniform.h"
#include "../ops/op_astar.h"
#include "../ops/op_soil.h"
#include "../ops/op_file.h"
//#include "ops/op_xmodel.h"
#include "../ops/op_gl_legacy.h"
#include "../ops/op_node.h"
#include "../ops/op_axis.h"
#include "../ops/op_idtech3_player.h"
#include "../ops/op_idtech3_perspectivematrix.h"
#include "../ops/op_idtech3_refentity.h"
#include "../ops/op_idtech3_image.h"
#include "../ops/op_idtech3_image_color.h"
#include "../ops/op_idtech3_image_split.h"
#include "../ops/op_idtech3_image_split_alpha.h"
#include "../ops/op_idtech3_image_scale.h"
#include "../ops/op_idtech3_image_mix.h"
#include "../ops/op_idtech3_rmo.h"
#include "../ops/op_idtech3_shader.h"
#include "../ops/op_idtech3_shader_pbr.h"
#include "../ops/op_idtech3_mdxm.h"
#include "../ops/op_skeleton.h"
#include "../ops/op_vector3.h"
#include "../ops/op_vector4.h"
#include "../ops/op_line.h"

// FLOAT
#include "../ops/op_mapfloat.h"

// META
#include "../ops/op_prefab.h"
#include "../ops/op_prefab_input.h"
#include "../ops/op_prefab_output.h"
#include "../ops/op_scriptwrapper.h"
#include "../ops/op_nop.h"


//#include "op_helix2.h"
//#include "op_helix.h"
//#include "op_color.h"
//#include "op_value.h"
//#include "op_perspective.h"

//Op *create_op_by_name(char *name) {
//
//}


oplist_t ops_stuff[] = {
	//{ "Timer", create_timer },
	{ "OpCheckerboard"                , [] {return (Op *)new OpCheckerboard             ();}  , OPLIST_TYPE_STUFF        },
	{ "OpKeyboard"                    , [] {return (Op *)new OpKeyboard                 ();}  , OPLIST_TYPE_STUFF        },
	{ "OpLogger"                      , [] {return (Op *)new OpLogger                   ();}  , OPLIST_TYPE_STUFF        },
	{ "OpSwitch"                      , [] {return (Op *)new OpSwitch                   ();}  , OPLIST_TYPE_STUFF        },
	{ "OpCraft"                       , [] {return (Op *)new OpCraft                    ();}  , OPLIST_TYPE_STUFF        },
	{ "OpIf"                          , [] {return (Op *)new OpIf                       ();}  , OPLIST_TYPE_STUFF        },
  //{ "OpCube"                        , [] {return (Op *)new OpCube                     ();}  , OPLIST_TYPE_STUFF        }, // duktape_kung_get_buffer undefined shit
	{ "OpRandomShit"                  , [] {return (Op *)new OpRandomShit               ();}  , OPLIST_TYPE_STUFF        },
	{ "OpAStar"                       , [] {return (Op *)new OpAStar                    ();}  , OPLIST_TYPE_STUFF        },
	{ "OpFile"                        , [] {return (Op *)new OpFile                     ();}  , OPLIST_TYPE_STUFF        },
	{ "OpLine"                        , [] {return (Op *)new OpLine                     ();}  , OPLIST_TYPE_STUFF        },
	NULL
};

oplist_t ops_meta[] = {
	{ "OpPrefab"                      , [] {return (Op *)new OpPrefab                   ();}  , OPLIST_TYPE_META         },
	{ "OpPrefabInput"                 , [] {return (Op *)new OpPrefabInput              ();}  , OPLIST_TYPE_META         },
	{ "OpPrefabOutput"                , [] {return (Op *)new OpPrefabOutput             ();}  , OPLIST_TYPE_META         },
	{ "OpScriptWrapper"               , [] {return (Op *)new OpScriptWrapper            ();}  , OPLIST_TYPE_META         },
	{ "OpNop"                         , [] {return (Op *)new OpNop                      ();}  , OPLIST_TYPE_META         },
	NULL
};

oplist_t ops_javascript[] = {			          											        
	{ "OpJavaScript"                  , [] {return (Op *)new OpJavaScript               ();}  , OPLIST_TYPE_JAVASCRIPT   },
	{ "OpJavaScriptFile"              , [] {return (Op *)new OpJavaScriptFile           ();}  , OPLIST_TYPE_JAVASCRIPT   },
	{ "OpExpression"                  , [] {return (Op *)new OpExpression               ();}  , OPLIST_TYPE_JAVASCRIPT   },
	{ "OpToFloat"                     , [] {return (Op *)new OpToFloat                  ();}  , OPLIST_TYPE_JAVASCRIPT   },
	NULL
};

oplist_t ops_math[] = {
	{ "OpPerspective"                 , [] {return (Op *)new OpPerspective              ();}  , OPLIST_TYPE_MATH         },
	{ "OpOrtho"                       , [] {return (Op *)new OpOrtho                    ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrix"                      , [] {return (Op *)new OpMatrix                   ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixDecompose"             , [] {return (Op *)new OpMatrixDecompose          ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixMultiply"              , [] {return (Op *)new OpMatrixMultiply           ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixRotate"                , [] {return (Op *)new OpMatrixRotate             ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixTranslate"             , [] {return (Op *)new OpMatrixTranslate          ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixShear"                 , [] {return (Op *)new OpMatrixShear              ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixTranspose"             , [] {return (Op *)new OpMatrixTranspose          ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixInverse"               , [] {return (Op *)new OpMatrixInverse            ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixScale"                 , [] {return (Op *)new OpMatrixScale              ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixIdentity"              , [] {return (Op *)new OpMatrixIdentity           ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrixMultiplyPoint"         , [] {return (Op *)new OpMatrixMultiplyPoint      ();}  , OPLIST_TYPE_MATH         },
	{ "OpMatrices"                    , [] {return (Op *)new OpMatrices                 ();}  , OPLIST_TYPE_MATH         },
	{ "OpSkeleton"                    , [] {return (Op *)new OpSkeleton                 ();}  , OPLIST_TYPE_MATH         },
	{ "OpVector3"                     , [] {return (Op *)new OpVector3                  ();}  , OPLIST_TYPE_MATH         },
	{ "OpVector3Dot"                  , [] {return (Op *)new OpVector3Dot               ();}  , OPLIST_TYPE_MATH         },
	{ "OpVector4"                     , [] {return (Op *)new OpVector4                  ();}  , OPLIST_TYPE_MATH         },
	{ "OpQuaternion"                  , [] {return (Op *)new OpQuaternion               ();}  , OPLIST_TYPE_MATH         },
	{ "OpQuaternionMultiply"          , [] {return (Op *)new OpQuaternionMultiply       ();}  , OPLIST_TYPE_MATH         },
	{ "OpQuaternionInverse"           , [] {return (Op *)new OpQuaternionInverse        ();}  , OPLIST_TYPE_MATH         },
	NULL
};

oplist_t ops_float[] = {
	{ "OpValue"                       , [] {return (Op *)new OpValue                    ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpDivide"                      , [] {return (Op *)new OpDivide                   ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpMultiply"                    , [] {return (Op *)new OpMultiply                 ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpPlus"                        , [] {return (Op *)new OpPlus                     ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpMinus"                       , [] {return (Op *)new OpMinus                    ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpSin"                         , [] {return (Op *)new OpSin                      ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpCos"                         , [] {return (Op *)new OpCos                      ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpNegate"                      , [] {return (Op *)new OpNegate                   ();}  , OPLIST_TYPE_FLOAT        },
	{ "OpMapFloat"                    , [] {return (Op *)new OpMapFloat                 ();}  , OPLIST_TYPE_FLOAT        },
	NULL
};

oplist_t ops_opengl[] = {
	{ "OpMeshEditor"                  , [] {return (Op *)new OpMeshEditor               ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpRenderer"                    , [] {return (Op *)new OpRenderer                 ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpFragmentShader"              , [] {return (Op *)new OpFragmentShader           ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpVertexShader"                , [] {return (Op *)new OpVertexShader             ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpProgram"                     , [] {return (Op *)new OpProgram                  ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpFramebuffer"                 , [] {return (Op *)new OpFramebuffer              ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpGLBuffer"                    , [] {return (Op *)new OpGLBuffer                 ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpGLAttrib"                    , [] {return (Op *)new OpGLAttrib                 ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpGLUniform"                   , [] {return (Op *)new OpGLUniform                ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpSOIL"                        , [] {return (Op *)new OpSOIL                     ();}  , OPLIST_TYPE_OPENGL       },
//	{ "OpXModel"                      , [] {return (Op *)new OpXModel                   ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpGLLegacy"                    , [] {return (Op *)new OpGLLegacy                 ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpNode"                        , [] {return (Op *)new OpNode                     ();}  , OPLIST_TYPE_OPENGL       },
	{ "OpAxis"                        , [] {return (Op *)new OpAxis                     ();}  , OPLIST_TYPE_OPENGL       },
	NULL
};

oplist_t ops_idtech3[] = {
	{ "OpPlayer"                                , [] {return (Op *)new OpPlayer                             ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3ProjectionMatrix"               , [] {return (Op *)new OpIDTech3ProjectionMatrix            ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3ModelViewMatrix"                , [] {return (Op *)new OpIDTech3ModelViewMatrix             ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3ModelViewProjectionMatrix"      , [] {return (Op *)new OpIDTech3ModelViewProjectionMatrix   ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3RefEntity"                      , [] {return (Op *)new OpIDTech3RefEntity                   ();}  , OPLIST_TYPE_IDTECH3      },
	{ "Image"                                   , [] {return (Op *)new OpIDTech3Image                       ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3ImageColor"                     , [] {return (Op *)new OpIDTech3ImageColor                  ();}  , OPLIST_TYPE_IDTECH3      },
	{ "ImageSplit"                              , [] {return (Op *)new OpIDTech3ImageSplit                  ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3ImageSplitAlpha"                , [] {return (Op *)new OpIDTech3ImageSplitAlpha             ();}  , OPLIST_TYPE_IDTECH3      },
	{ "ImageScale"                              , [] {return (Op *)new OpIDTech3ImageScale                  ();}  , OPLIST_TYPE_IDTECH3      },
	{ "ImageMix"                                , [] {return (Op *)new OpIDTech3ImageMix                    ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3RMO"                            , [] {return (Op *)new OpIDTech3RMO                         ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3Shader"                         , [] {return (Op *)new OpIDTech3Shader                      ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpIDTech3ShaderPBR"                      , [] {return (Op *)new OpIDTech3ShaderPBR                   ();}  , OPLIST_TYPE_IDTECH3      },
	{ "OpMDXM"                                  , [] {return (Op *)new OpMDXM                               ();}  , OPLIST_TYPE_IDTECH3      },
	//{ "Helix", (Op *(*)())op_helix_new },
	//{ "Helix", create_helix },
	//{ "Color", create_color },
	NULL
};

OpMatrix           *craft_matrix_persp        = NULL;

void init_systems();

#if 0
void InitPermanentOps() {
	imgui_log("Init permanent ops...\n");

	craft_matrix_persp      = op_matrix_new();
	
	perm.add((Op *)craft_matrix_persp        );

	// please use no spaces, the scanf-read-file function would fail
	strcpy( craft_matrix_persp       ->name, "MatPersp"        );


	for (auto op : perm.all) {
		op->is_permanent = 1;
		//// every node needs to send its value all the time, because I set the values directly, so nobody keeps the update-flow running
		//if (0)
		//	op->type = OpType::OP_TYPE_DELIVERER;
		//else
		//	op->type = OpType::OP_TYPE_RECEIVER; // dont execute anything atm
	}
	
	//craft_matrix_persp->type = OpType::OP_TYPE_REQUESTER;

	init_systems();
	//perm.loadFile("perm.txt");
}


#endif
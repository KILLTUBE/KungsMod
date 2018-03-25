#include "../include_gl.h"

//#include "craft_interaction.h"

#include "../include_imgui.h"
#ifdef USE_DUKTAPE
#include <include_duktape.h>
#endif
#include "../include_console.h"

//#include "craft_faust.h"
#include "../opsys/opsys.h"
#include "../ops/op_astar.h"
#include "opsys_javascript.h"
#include "../opsys/opsys_hierarchy.h"

#if 0
int js_printf(char *msg, ...) {
	va_list argptr;
	va_start(argptr, msg);
	char buf[4096];
	vsnprintf(buf, 4096, msg, argptr);
	int ret = imgui_log("%s", buf);
	va_end(argptr);
	return ret;
}
#endif


extern double px;
extern double py;

//extern char replbuffer[4096];
//void ImStrncpy(char* dst, const char* src, int count);
#if USE_DUKTAPE
int duk_func_togglemenu(duk_context *ctx) {

	show_imgui = !show_imgui;

	if (show_imgui) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		imgui_callbacks(window);
	} else {

		// imgui.cpp line 8041
            //// Copy back to user buffer
            //if (is_editable && strcmp(edit_state.TempTextBuffer.Data, buf) != 0)
            //{

//ImGuiContext *g = ImGui::GetCurrentContext();
//auto edit_state = g->InputTextState;
//
////if (edit_state.TempTextBuffer.size())
//	if (edit_state.changed)
//            ImStrncpy(replbuffer, edit_state.TempTextBuffer.Data, /*buf_size*/4096); // no clue if it just needs strlen...
            //    value_changed = true;
            //}

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
        glfwGetCursorPos(window, &px, &py);
		glfwSetKeyCallback(window, on_key);
		glfwSetCharCallback(window, on_char);
		glfwSetMouseButtonCallback(window, on_mouse_button);
		glfwSetScrollCallback(window, on_scroll);

	}
	return 0;
}
#endif

/*

    int exclusive =
        glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
    if (action == GLFW_RELEASE) {
        return;
    }
    if (key == GLFW_KEY_BACKSPACE) {
        if (g->typing) {
            int n = strlen(g->typing_buffer);
            if (n > 0) {
                g->typing_buffer[n - 1] = '\0';
            }
        }
    }
    if (action != GLFW_PRESS) {
        return;
    }
    if (key == GLFW_KEY_ESCAPE) {
        if (g->typing) {
            g->typing = 0;
        }
        else if (exclusive) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
*/
#ifdef USE_DUKTAPE
int duk_func_ismouselocked(duk_context *ctx) {
	//int locked = glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
	//duk_push_int(ctx, locked);
	return 1;
}
int duk_func_setmouselocked(duk_context *ctx) {
	//int locked = duk_to_int(ctx, 0);
	//if (locked)
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//else
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	return 0;
}
#endif
// gnah fuckin hate it that duktape has all those filthy types internally only
//int duk_func_stacksize(duk_context *ctx) {
//	duk_hthread *thr = (duk_hthread *) ctx;
//	duk_push_int(thr->)
//	return 1;
//}



//void reload() {
//	js_eval_file_safe(ctx, "assets\\javascript\\pre_create.js");
//	js_eval_file_safe(ctx, "assets\\javascript\\lib.js");
//	js_eval_file_safe(ctx, "assets\\javascript\\lib_quake.js");
//	//js_call(ctx, "PostReload", "");
//}
//
//// I hope you are happy now you c++ name mengele
//// todo: make all api's C only...
//extern "C" void reload_c() {
//	reload();
//}
//
//int duk_func_reload(duk_context *ctx) {
//	reload();
//	return 0;
//}
#ifdef USE_DUKTAPE
int duk_func_get_block(duk_context *ctx) {
	int x = duk_to_int(ctx, 0);
	int y = duk_to_int(ctx, 1);
	int z = duk_to_int(ctx, 2);

	//int ret = get_block(x, y, z);
	//duk_push_int(ctx, ret);
	duk_push_int(ctx, 123);
	return 1;
}

int duk_func_sys_op_update(duk_context *ctx) {
	char *sysname = (char *) duk_to_string(ctx, 0);
	char *opname = (char *) duk_to_string(ctx, 1);

	int ret = 0;

	for (auto sys : systems) {
		if (!strcmp(sys->name, sysname)) {
			for (auto op : sys->all) {
				if (!strcmp(op->name, opname)) {
					op->forcereload = 1;
					op->Update();
					ret = 1;
					break;
				}
			}
		}
		
	}

	duk_push_int(ctx, ret);
	return 1;
}

int duk_func_opsystem_new(duk_context *ctx) {
	char *sysname = (char *) duk_to_string(ctx, 0);

	OpSystem *sys = new OpSystem(sysname, 0);

	duk_push_int(ctx, (int)sys);
	return 1;
}
int duk_func_opsystem_add(duk_context *ctx) {
	OpSystem *sys = (OpSystem *) duk_to_int(ctx, 0);
	Op *op = (Op *) duk_to_int(ctx, 1);

	sys->add(op);
	sys->regenerateCallGraphs();

	return 0;
}
int duk_func_op_astar_new(duk_context *ctx) {
	Op *astar = (Op *)new OpAStar();
	duk_push_int(ctx, (int)astar);
	return 1;
}
int duk_func_op_astar_add_node(duk_context *ctx) {
	OpAStar *astar = (OpAStar *) duk_to_int(ctx, 0);
	float x = duk_to_number(ctx, 1);
	float y = duk_to_number(ctx, 2);
	float z = duk_to_number(ctx, 3);
	
	astar->AddNode(x, y, z);
	return 0;
}



// in opsystem_repl.cpp
int duk_func_repl_set_text(duk_context *ctx);

//extern char repl_filename[128];
int duk_func_repl_set_filename(duk_context *ctx) {
	//char *filename = (char *)duk_to_string(ctx, 0);
	//strcpy(repl_filename, filename);
	return 0;
}

#endif


//void js_init_full() {
//	js_init();
//
//
//	struct funcis funcs[] = {
//		//{"togglemenu"                , duk_func_togglemenu              },
//		//{"ismouselocked"             , duk_func_ismouselocked           },
//		//{"setmouselocked"            , duk_func_setmouselocked          },
//		{"reload"                    , duk_func_reload                  },
//		//{"get_block"                 , duk_func_get_block               },
//		//{"sys_op_update"             , duk_func_sys_op_update           },
//		//{"opsystem_new"              , duk_func_opsystem_new            },
//		//{"opsystem_add"              , duk_func_opsystem_add            },
//		//{"op_astar_new"              , duk_func_op_astar_new            },
//		//{"op_astar_add_node"         , duk_func_op_astar_add_node       },
//		//{"repl_set_text"             , duk_func_repl_set_text           },
//		//{"repl_set_filename"         , duk_func_repl_set_filename       },
//		{NULL, NULL}
//	};
//	
//	for (int i=0; funcs[i].name; i++) {
//		js_register_function(ctx, funcs[i].name, funcs[i].func);
//	}
//	//
//	//opsystem_hierarchy_add_javascript_bindings();
//
//	js_call(ctx, "reload", "");
//}
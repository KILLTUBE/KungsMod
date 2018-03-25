#include "op.h"
#include "op_expression.h"

#ifdef USE_DUKTAPE
#include <include_duktape.h>
#endif
#include "../include_console.h"

void OpExpression::Init() {
	Op::Init();
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpExpression" );
	strcpy( default_link_inputs[0].name, ">");
	strcpy( default_link_inputs[0].val_str, "no value set");
	number_of_inputs = 1;
	number_of_outputs = 0;

	execid = 0;
	strcpy(code, "");
	isExpression = 1;
}

// as seen in tofloat op
static void init_js_code(OpExpression *op) {
#ifdef USE_DUKTAPE
	duk_push_string(ctx, op->code);
	duk_push_string(ctx, op->name);
	if (duk_pcompile(ctx, 0) != 0) {
	imgui_log("compile failed: %s\n", duk_safe_to_string(ctx, -1));
	} else {
			
		duk_push_global_object(ctx);
			
		duk_dup(ctx, -2); // 
		//duk_put_prop_string(ctx, -2, name);
		duk_put_prop_index(ctx, -2, (int)op);

		duk_pop(ctx); // pop global

		//duk_call(ctx, 0);      /* [ func ] -> [ result ] */
		//log("program result: %s\n", duk_safe_to_string(ctx, -1));
	}
	duk_pop(ctx);
#endif
}


void OpExpression::Render() {
	Op::PreRender();

	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::Text("%d", execid);

	ImGui::SetCursorPos(pos + ImVec2(40,5));
	ImGui::PushItemWidth(size.x - 50);
	ImGui::PushID(this);
	int changed = ImGui::InputText("Code", code, sizeof code);
	if (changed) {
		init_js_code(this);
	}
	ImGui::PopID();
	ImGui::PopItemWidth();
	Op::PostRender();
}

void OpExpression::Update() {
#ifdef USE_DUKTAPE
	//log("log: %s", default_link_inputs[0].val_str);
	//js_call("eval", "s", code);


	duk_push_global_object(ctx);
	//duk_get_prop_string(ctx, -1, name);
	duk_get_prop_index(ctx, -1, (int)this);
	int ret = duk_pcall(ctx, 0);
	//if (ret == 0)
	//	val = duk_get_number(ctx, -1);
	//else
	//	val = 1337.0f;
	duk_pop(ctx); // pop ret
	duk_pop(ctx); // pop global
#endif
}

void OpExpression::RenderEditor() {
	Op::RenderEditor();

}

std::string OpExpression::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "code %s",
		code
	);
	return std::string(buf);
}

void OpExpression::ReadExtraData(char *line) {
	sscanf(line, "code %[^\n]",
		&code
	);
	init_js_code(this);
}

OpExpression::OpExpression() {
	Init();
}
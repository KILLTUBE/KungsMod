#include "op.h"
#include "op_tofloat.h"

#ifdef USE_DUKTAPE
#include <include_duktape.h>
#endif
#include "../include_console.h"

void OpToFloat::InitJsCode() {
#ifdef USE_DUKTAPE
	duk_push_string(ctx, code);
	duk_push_string(ctx, name);
	if (duk_pcompile(ctx, 0) != 0) {
	imgui_log("compile failed: %s\n", duk_safe_to_string(ctx, -1));
	} else {
			
		duk_push_global_object(ctx);
			
		duk_dup(ctx, -2); // 
		//duk_put_prop_string(ctx, -2, name);
		duk_put_prop_index(ctx, -2, (int)this);

		duk_pop(ctx); // pop global

		//duk_call(ctx, 0);      /* [ func ] -> [ result ] */
		//log("program result: %s\n", duk_safe_to_string(ctx, -1));
	}
	duk_pop(ctx);
#endif
}

void OpToFloat::Init() {
	Op::Init();
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpToFloat" );
	//strcpy( default_link_inputs[0].name, ">");
	//strcpy( default_link_inputs[0].val_str, "no value set");

	InitLinkOutput(0, "#", OP_TYPE_FLOAT);

	number_of_inputs = 0;
	number_of_outputs = 1;

	strcpy(code, "");
	showtitle = 0;


}

void OpToFloat::Render() {
	Op::PreRender();

	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushItemWidth(100);
	ImGui::Text("%f", val);
	ImGui::PopItemWidth();

	ImGui::SetCursorPos(pos + ImVec2(105,5));
	ImGui::PushItemWidth(size.x - 110);
	ImGui::PushID(this);
	int changed = ImGui::InputText("", code, sizeof code);

	if (changed) {
		imgui_log("changed\n");

		InitJsCode();


	}
	ImGui::PopID();
	ImGui::PopItemWidth();
	Op::PostRender();
}

void OpToFloat::Update() {
	//log("log: %s", default_link_inputs[0].val_str);
	//js_call("eval", "s", code);

	//duk_eval_string(ctx, code);

	//duk_push_string(ctx, name);
	//int ret = duk_eval_raw(ctx, code, 0, DUK_COMPILE_EVAL | DUK_COMPILE_SAFE | DUK_COMPILE_NOSOURCE | DUK_COMPILE_STRLEN);

#ifdef USE_DUKTAPE
	duk_push_global_object(ctx);
	//duk_get_prop_string(ctx, -1, name);
	duk_get_prop_index(ctx, -1, (int)this);
	int ret = duk_pcall(ctx, 0);
	if (ret == 0)
		val = duk_get_number(ctx, -1);
	else
		val = 1337.0f;
	duk_pop(ctx); // pop ret
	duk_pop(ctx); // pop global
	default_link_outputs[0].changed++;
#endif

	//if (ret == 0)
	//	color = 0x00FF00FF;
	//else
	//	color = 0x0000FFFF;

	//log("ret: %d", ret);


	//auto *ol = default_link_outputs + 0;
	//for (auto il : *ol->inputlinks) {
	//	il->val_f = val;
	//	if (type == OpType::OP_TYPE_SENDER)
	//		il->owner->update(il->owner);
	//}


}

void OpToFloat::RenderEditor() {
	Op::RenderEditor();

}

std::string OpToFloat::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "code %s",
		code
	);
	return std::string(buf);
}

void OpToFloat::ReadExtraData(char *line) {
	sscanf(line, "code %[^\n]",
		&code
	);

	InitJsCode();
}

OpToFloat::OpToFloat() {
	Init();
}
#include "op.h"
#include "op_scriptwrapper.h"

#ifdef USE_DUKTAPE
#include <include_duktape.h>
#include <duktape/dukdebugheaders.h>
#endif

#include "../include_console.h"

void OpScriptWrapper::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	
	number_of_inputs = 3;
	InitLink(0, "F", OP_TYPE_FLOAT);
	InitLink(1, "Add", OP_TYPE_FLOAT);
	InitLink(2, "Multiply", OP_TYPE_FLOAT);
	number_of_outputs = 1;
	InitLinkOutput(0, "F", OP_TYPE_FLOAT);
	//ResizeMinimal();
	showtitle = 0;
}

void OpScriptWrapper::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	ImGui::DragFloat(name, &out);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpScriptWrapper::Update() {
	out = add + in * multiply;
	default_link_outputs[0].changed++;
}

void OpScriptWrapper::RenderEditor() {
	Op::RenderEditor();

	ImGui::Text("This: %d", javascript_this);
	ImGui::Text("Heapptr: %d", javascript_heapptr_update);

#ifdef USE_DUKTAPE
	if (ImGui::Button("call heapptr funci")) {
		duk_heaphdr *hdr = (duk_heaphdr *)javascript_heapptr_update;
		imgui_log("hdr->h_flags = %d\n", hdr->h_flags);
		imgui_log("hdr->h_next = %d\n", hdr->h_next);
		imgui_log("hdr->h_next = %d\n", hdr->h_next);
		imgui_log("hdr->h_refcount = %d\n", hdr->h_refcount);

		//duk_get_type_mask(ctx, 0);

		
		duk_push_heapptr(ctx, hdr); // method
		duk_push_heapptr(ctx, javascript_this); // this pointer
		int ret  = duk_pcall_method(ctx, 0);
		
		if (ret != DUK_EXEC_SUCCESS) {
			imgui_log("error: %s\n", duk_to_string(ctx, -1));
		}

		duk_pop(ctx);
	}
	if (ImGui::Button("get Update from this")) {
		duk_push_heapptr(ctx, javascript_this);
		duk_get_prop_string(ctx, -1, "Update");
		int ret = (int)duk_get_heapptr(ctx, -1);
		imgui_log("Update heapptr: %d\n", ret);

		duk_pop(ctx); // duk_get_prop_string
		duk_pop(ctx); // duk_push_heapptr

	}
#endif
}

//std::string OpMapFloat::WriteExtraData() {
//	char buf[1024];
//	snprintf(buf, sizeof buf, "add %f multiply %f",
//		add,
//		multiply
//	);
//	return std::string(buf);
//}
//
//void OpMapFloat::ReadExtraData(char *line) {
//	sscanf(line, "add %f multiply %f",
//		&add,
//		&multiply
//	);
//}

OpScriptWrapper::OpScriptWrapper() {
	Init();
}
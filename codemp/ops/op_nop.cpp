#include "op.h"
#include "op_nop.h"

#ifdef USE_DUKTAPE
#include <include_duktape.h>
#include <duktape/dukdebugheaders.h>
#endif
#include "../include_console.h"

void OpNop::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);

	InitLink(0, "#", OP_TYPE_FLOAT);
	InitLinkOutput(0, "#", OP_TYPE_FLOAT);
	number_of_inputs = 0;
	number_of_outputs = 0;
	//ResizeMinimal();
	showtitle = 0;
#ifdef USE_DUKTAPE
	if (javascript_heapptr_init != NULL)
	{
		duk_push_heapptr(ctx, javascript_heapptr_init); // method
		duk_push_heapptr(ctx, javascript_this); // this pointer
		int ret  = duk_pcall_method(ctx, 0);
		if (ret != DUK_EXEC_SUCCESS) {
			imgui_log("Nop::Init> error: %s\n", duk_to_string(ctx, -1));
		}
		duk_pop(ctx);
	}
#endif
}

void OpNop::Render() {
	Op::PreRender();
	
	//ImGui::SetCursorPos(pos + ImVec2(5,5));
	//ImGui::PushID(this);
	//ImGui::PushItemWidth(80);
	//ImGui::DragFloat(name, &tmp_val);
	//ImGui::PopItemWidth();
	//ImGui::PopID();

	// we can call with this==NULL, but we need at least a method
	// todo: on error... set some variable so we dont update anymore and save error message to op... so its fixable
#ifdef USE_DUKTAPE
	if (javascript_heapptr_render_canvas != NULL)
	{

		ImGui::SetCursorPos(pos + ImVec2(5,5));
		ImGui::PushItemWidth(size.x - 10);

		duk_push_heapptr(ctx, javascript_heapptr_render_canvas); // method
		duk_push_heapptr(ctx, javascript_this); // this pointer
		int ret  = duk_pcall_method(ctx, 0);
		if (ret != DUK_EXEC_SUCCESS) {
			imgui_log("Nop::RenderCanvas> error: %s\n", duk_to_string(ctx, -1));
		}
		duk_pop(ctx);

		ImGui::PopItemWidth();
	}
#endif
	Op::PostRender();
}

void OpNop::Update() {

	if (hasError) {
		return;
	}

#ifdef USE_DUKTAPE

	// we can call with this==NULL, but we need at least a method
	// todo: on error... set some variable so we dont update anymore and save error message to op... so its fixable
	if (javascript_heapptr_update == NULL)
		return;
	duk_push_heapptr(ctx, javascript_heapptr_update); // method
	duk_push_heapptr(ctx, javascript_this); // this pointer
	int ret  = duk_pcall_method(ctx, 0);
	if (ret != DUK_EXEC_SUCCESS) {
		imgui_log("Nop::Update> error: %s\n", duk_to_string(ctx, -1));
		hasError = 1;
	}
	duk_pop(ctx);
#endif
}

void OpNop::RenderEditor() {
	Op::RenderEditor();

	if (ImGui::Button("Reset Error")) {
		hasError = 0;
	}

#ifdef USE_DUKTAPE

	ImGui::Text("This: %d", javascript_this);
	ImGui::Text("Heapptr: %d", javascript_heapptr_update);
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

	
	ImGui::Text("JS Init: %d", javascript_heapptr_init);
	ImGui::Text("JS Update: %d", javascript_heapptr_update);
	ImGui::Text("JS RenderCanvas: %d", javascript_heapptr_render_canvas);
	ImGui::Text("JS RenderEditor: %d", javascript_heapptr_render_editor);

	if (javascript_this) {
		duk_heaphdr *hdr = (duk_heaphdr *)javascript_this;
		ImGui::Text("hdr javascript_this->h_flags = %d\n", hdr->h_flags);
		ImGui::Text("hdr javascript_this->h_next = %d\n", hdr->h_next);
		ImGui::Text("hdr javascript_this->h_next = %d\n", hdr->h_next);
		ImGui::Text("hdr javascript_this->h_refcount = %d\n", hdr->h_refcount);

		struct duk_hobject *opptr = (struct duk_hobject *) javascript_this;
		ImGui::Text("struct duk_hobject *opptr->userdata = %d realptr=%d\n", (int)opptr->userdata, (int)this);
	}





	if (javascript_heapptr_render_editor != NULL)
	{
		duk_push_heapptr(ctx, javascript_heapptr_render_editor); // method
		duk_push_heapptr(ctx, javascript_this); // this pointer
		int ret  = duk_pcall_method(ctx, 0);
		if (ret != DUK_EXEC_SUCCESS) {
			imgui_log("Nop::RenderEditor> error: %s\n", duk_to_string(ctx, -1));
		}
		duk_pop(ctx);
	}
#endif
}

#ifdef USE_DUKTAPE
void InitializeHeapPointer(Op *op, char *methodname, void **out_pointer) {
	// [..., this, Update || undefined]
	duk_get_prop_string(ctx, -1, methodname);
	// [..., this, Update || undefined]
	void *ret = duk_get_heapptr(ctx, -1);
	// [..., this]
	duk_pop(ctx);

#if 0
	// [..., this, OpAdd]
	js_push_global_by_name(ctx, "OpAdd");
	// [..., this, OpAdd, OpAdd.prototype]
	duk_get_prototype(ctx, -1);
	// [..., this, OpAdd]
	duk_set_prototype(ctx, -1);
	// [..., this]
	duk_pop(ctx);
#endif



	// if the Update heapptr didn't change, just do nothing
	if (*out_pointer == ret) {
		return;
	}

	// the case when we got a new Update heapptr, so we gotta: deref the old one, update heapptr, ref new heapptr
	if (ret) {

		// if we had a method before, we are decreasing refcount, so it might be freed
		if (*out_pointer)
			duk_unref_heapptr(ctx, *out_pointer);

		imgui_log("Update heapptr methodname=%s from=%d to=%d\n", methodname, *out_pointer, ret);
		*out_pointer = ret;

		
		// increment refcount for our new method
		duk_ref_heapptr(ctx, *out_pointer);

	} else {
		// when we are unable to get the Update prototype method, something is wrong... just set Update heapptr to 0, so the Op doesnt work anymore
		// and one can debug the problem
		*out_pointer = 0;
	}
}
#endif
void OpNop::UpdateDuktapeHeappointers() {
	if ( ! javascript_this)
		return;
#ifdef USE_DUKTAPE
	// [..., this]
	duk_push_heapptr(ctx, javascript_this);

	
	InitializeHeapPointer((Op *)this, "Init", &javascript_heapptr_init);
	InitializeHeapPointer((Op *)this, "Update", &javascript_heapptr_update);
	InitializeHeapPointer((Op *)this, "RenderCanvas", &javascript_heapptr_render_canvas);
	InitializeHeapPointer((Op *)this, "RenderEditor", &javascript_heapptr_render_editor);


	if (javascript_heapptr_init != NULL)
	{
		duk_push_heapptr(ctx, javascript_heapptr_init); // method
		duk_push_heapptr(ctx, javascript_this); // this pointer
		int ret  = duk_pcall_method(ctx, 0);
		if (ret != DUK_EXEC_SUCCESS) {
			imgui_log("Nop::Init> error: %s\n", duk_to_string(ctx, -1));
		}
		duk_pop(ctx);
	}


	// [...]
	duk_pop(ctx);
#endif
}

OpNop::OpNop() {
	Init();
}
#include "op.h"
#include "op_javascript_file.h"

#if USE_DUKTAPE
#include <include_duktape.h>
#endif
#include "../include_console.h"

//void file_get_contents(char *filename, char *buffer, int buffersize) {
//	FILE *f = NULL;
//	long len;
//	size_t got;
//	f = fopen(filename, "rb");
//	if (!f) {
//		imgui_log("file_get_contents(%s): cant open file\n", filename);
//		goto error;
//	}
//	if (fseek(f, 0, SEEK_END) != 0) {
//		
//		imgui_log("file_get_contents(%s): cant seek to end\n", filename);
//		goto error;
//	}
//	len = ftell(f);
//
//	if (len >= buffersize) {
//		imgui_log("file_get_contents(%s): filesize is bigger than delivered buffer (filesize=%d, buffersize=%d)\n", filename, len, buffersize);
//		goto error;
//	}
//	if (fseek(f, 0, SEEK_SET) != 0) {
//		imgui_log("file_get_contents(%s): cant seek to start\n", filename);
//		goto error;
//	}
//	got = fread(buffer, 1, len, f);
//	if (got != (size_t) len) {
//		imgui_log("file_get_contents(%s): cant read content\n", filename);
//		goto error;
//	}
//	error:
//	if (f) {
//		fclose(f);
//	}
//}

void OpJavaScriptFile::Init() {
	Op::Init();
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( default_link_inputs[0].name, ">");
	strcpy( default_link_inputs[0].val_str, "no value set");
	number_of_inputs = 0;
	number_of_outputs = 0;
}

void OpJavaScriptFile::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushItemWidth(size.x - 50);
	ImGui::PushID(this);
	ImGui::InputTextMultiline("Code", code, sizeof code, size - ImVec2(10,10));
	ImGui::PopID();
	ImGui::PopItemWidth();
	Op::PostRender();
}

void OpJavaScriptFile::Update() {
	if (call_opsystemrebuild)
		return;
	//log("log: %s", default_link_inputs[0].val_str);
#ifdef USE_DUKTAPE
	js_call(ctx, "eval", "s", code);
#endif
}

void OpJavaScriptFile::RenderEditor() {
	Op::RenderEditor();
#ifdef USE_DUKTAPE
	if (ImGui::Button("Save file")) {
		js_call(ctx, "file_put_contents", "ss", filename, code);
	}
	if (ImGui::Button("Reload file")) {
		file_get_contents(filename, code, sizeof code);
	}
	ImGui::InputText("filename", filename, sizeof filename);
	ImGui::DragInt("onlyonrebuild", &call_opsystemrebuild, 1.0f, 0, 1);
#endif
}

void OpJavaScriptFile::OnOpSystemRebuild() {
	//log("opsystem was rebuild!\n");
	// we call it either every frame or only at opsystemrebuild "event"
	//if (call_opsystemrebuild)
	//	return;
#ifdef USE_DUKTAPE
	js_call(ctx, "eval", "s", code);
#endif
}

// 0 == each frame, 1 == only on opsystemrebuild

std::string OpJavaScriptFile::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "filename %s onlyonrebuild %d",
		filename,
		call_opsystemrebuild
	);
	return std::string(buf);
}

void OpJavaScriptFile::ReadExtraData(char *line) {
	sscanf(line, "filename %s onlyonrebuild %d",
		&filename,
		&call_opsystemrebuild
	);

	//file_get_contents(filename, code, sizeof code);
}

OpJavaScriptFile::OpJavaScriptFile() {
	Init();
}
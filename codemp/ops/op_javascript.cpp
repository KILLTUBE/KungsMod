#include "op.h"
#include "op_javascript.h"

#ifdef USE_DUKTAPE
#include <include_duktape.h>
#endif

void OpJavaScript::Init() {
	Op::Init();
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpJavaScript" );
	strcpy( default_link_inputs[0].name, ">");
	strcpy( default_link_inputs[0].val_str, "no value set");
	number_of_inputs = 1;
	number_of_outputs = 0;
}

void OpJavaScript::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushItemWidth(size.x - 50);
	ImGui::PushID(this);
	ImGui::InputText("Code", code, sizeof code);
	ImGui::PopID();
	ImGui::PopItemWidth();
	Op::PostRender();
}

void OpJavaScript::Update() {
	if (cache_ingoing_connections == 0)
		return;
	//log("log: %s", default_link_inputs[0].val_str);
#ifdef USE_DUKTAPE
	js_call(ctx, "eval", "s", code);
#endif
}

void OpJavaScript::RenderEditor() {
	Op::RenderEditor();

}

std::string OpJavaScript::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "code %s",
		code
	);
	return std::string(buf);
}

void OpJavaScript::ReadExtraData(char *line) {
	sscanf(line, "code %[^\n]",
		&code
	);
}

OpJavaScript::OpJavaScript() {
	Init();
}
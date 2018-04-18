#include "op.h"
#include "op_prefab.h"
#include "../opsys/opsys.h"

#include "rd-rend2/matrix.h"

void OpPrefab::Init() {
	Op::Init();
	size = ImVec2(200, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpPrefab" );
	showtitle = 0;
	isPrefab = 1;
	subsys = NULL;
}

void OpPrefab::Render() {
	Op::PreRender();
	
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	ImGui::PushID(this);
	ImGui::PushItemWidth(80);
	if (ImGui::Button(name))
		OpSystem::SetCurrent(subsys);
	ImGui::PopItemWidth();
	ImGui::PopID();

	Op::PostRender();
}

void OpPrefab::Update() {
	int i = 0;

	if (subsys == 0) {
		return;
	}

	// first we copy over the input values
	for (auto input : subsys->prefabinputs) {
		LinkOutput *linkoutput = input->default_link_outputs + 0;
		for (auto inputlink : *linkoutput->inputlinks) {
			inputlink->val_f = default_link_inputs[i].val_f;
		}
		i++;
	}

	// then we update the subsys for the input values
	subsys->update();

	// and then we just distribute the calculated values to all outputs
	i = 0;
	for (auto output : subsys->prefaboutputs) {
		Link *link = output->default_link_inputs + 0;

		if (link->cached_backlinks->size() != 0) {
			LinkOutput *linkoutput = link->cached_backlinks->front();
		
			LinkOutput *prefablinkoutput = default_link_outputs + i;
			for (auto inputlink : *prefablinkoutput->inputlinks) {
				switch (inputlink->type) {
					case OP_TYPE_FLOAT:
						inputlink->val_f = linkoutput->val_f;
						break;
					case OP_TYPE_MATRIX:
						matcpy(inputlink->matrix, linkoutput->matrix);
						
						break;
				}
				
			}
		}
		i++;
	}
}

void OpPrefab::RenderEditor() {
	Op::RenderEditor();
	//ImGui::Text("Filename: %s", filename);
	ImGui::InputText("filename", filename, sizeof filename);
	if (ImGui::Button("Clear System")) {
		subsys->clearScene();
		delete subsys;
		subsys = NULL;
	}
	if (ImGui::Button("Load System")) {
		subsys = new OpSystem(filename, this);
		subsys->loadFile(filename);
		subsys->regenerateCallGraphs();
	}
	if (ImGui::Button("32ewReload System")) {
	}
	ImGui::Text("inputs: %d outputs: %d", number_of_inputs, number_of_outputs);
}

std::string OpPrefab::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "filename %s",
		filename
	);
	return std::string(buf);
}

void OpPrefab::ReadExtraData(char *line) {
	sscanf(line, "filename %s",
		filename
	);

	subsys = new OpSystem(filename, this);
	subsys->loadFile(subsys->name);
	subsys->regenerateCallGraphs();
	ResizeMinimal();
}

OpPrefab::OpPrefab() {
	Init();
}
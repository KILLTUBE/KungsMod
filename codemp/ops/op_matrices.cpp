#include "op.h"
#include "op_matrices.h"

#include "rd-rend2/matrix.h"

void OpMatrices::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	for (int i=0; i<16; i++) {
		InitLink(i, "Matrix", OP_TYPE_MATRIX);
	}
	InitLinkOutput(0, "Matrices", OP_TYPE_CUSTOMCLASS);
	number_of_inputs = 2;
	number_of_outputs = 1;
	ResizeMinimal();
	default_link_outputs[0].customclass = new ArrayOfMatrices();


	matrices = (ArrayOfMatrices *)default_link_outputs[0].customclass;
}

void OpMatrices::Render() {
	Op::PreRender();

	Op::PostRender();
}

void OpMatrices::Update() {
	//if ( ! DidInputsChange())
	//	return;


	matrices->SetAmount(80);

	for (int i=0; i<number_of_inputs; i++) {
		auto input = default_link_inputs + i;
	}
	float ident[16];
	mat_identity(ident);
	for (int i=0; i<61; i++) {
	
		if (i<16 && default_link_inputs[i].cached_backlinks->size()) {
			Link *input = default_link_inputs + i;
			matrices->Add(input->matrix, i);
		} else {

			matrices->Add(ident, i);
		}
	}
	default_link_outputs[0].changed++;

}

void OpMatrices::RenderEditor() {
	Op::RenderEditor();
	ImGui::DragInt("inputs", &number_of_inputs, 1.0f, 2, 16);
}

std::string OpMatrices::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "inputs %d",
		number_of_inputs
	);
	return std::string(buf);
}

void OpMatrices::OnLinkDisconnect(int id) {
	// reset matrix when we remove the link, so we cont need this std::vector shit to detect the first two "real" matrices... we just calculate all
	// multiplying by identity doesnt matters
	mat_identity(default_link_inputs[id].matrix);
}

void OpMatrices::ReadExtraData(char *line) {
	sscanf(line, "inputs %d",
		&number_of_inputs
	);
}

OpMatrices::OpMatrices() {
	Init();
}

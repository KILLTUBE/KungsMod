#include "op.h"
#include "op_skeleton.h"

#include "rd-rend2/matrix.h"

#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtx/quaternion.hpp"


typedef struct bone_s {
	int boneid;
	int parentid;
	float x;
	float y;
	float z;
	float quat_w;
	float quat_x;
	float quat_y;
	float quat_z;
	char *name;
} bone_t;


void OpSkeleton::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	for (int i=0; i<16; i++) {
		InitLink(i, "Matrix", OP_TYPE_MATRIX);
	}
	InitLinkOutput(0, "Matrices", OP_TYPE_CUSTOMCLASS);
	number_of_inputs = 0;
	number_of_outputs = 1;
	ResizeMinimal();

	default_link_outputs[0].customclass = new ArrayOfMatrices();
	matrices = (ArrayOfMatrices *)default_link_outputs[0].customclass;

// works, but need to readin models from binary now instead of .h exports	
#if 0
	for (int ii=0; ii<bonesCount; ii++) {
		int i =  recursivesortedids[ii];
		bone_t *bone = bones + i;

		skeleton[i].localPosition = glm::vec3(bone->x, bone->y, bone->z);
		skeleton[i].localRotation = glm::quat(bone->quat_w, bone->quat_x, bone->quat_y, bone->quat_z);

#if 1
		skeleton[i].localMatrix = glm::translate(skeleton[i].localPosition) * glm::toMat4(skeleton[i].localRotation);
#else
		skeleton[i].localMatrix = glm::toMat4(skeleton[i].localRotation) * glm::translate(skeleton[i].localPosition);
#endif


		if (bone->parentid == -1) {
			skeleton[i].localToWorld = skeleton[i].localMatrix;
		} else {
			Joint *parent = skeleton + bone->parentid;
#if 1
			skeleton[i].localToWorld = parent->localToWorld * skeleton[i].localMatrix;
#else 
			skeleton[i].localToWorld = skeleton[i].localMatrix * parent->localToWorld;
#endif
		}
		skeleton[i].bindpose = glm::inverse(skeleton[i].localToWorld);
	}
#endif
}

#include "../imgui/imgui_fixedarea.h"

void OpSkeleton::Render() {
	Op::PreRender();
	FixedArea fa(pos, size, 7); // remove scrollbar size from width, so no horizontal scroll bar
	ImGui::PushItemWidth(fa.GetColWidth());
	fa.SetCol( 0); ImGui::Text("x");
	fa.SetCol( 1); ImGui::Text("y");
	fa.SetCol( 2); ImGui::Text("z");
	fa.SetCol( 3); ImGui::Text("qw");
	fa.SetCol( 4); ImGui::Text("qx");
	fa.SetCol( 5); ImGui::Text("qy");
	fa.SetCol( 6); ImGui::Text("qz");

	
	//for (int i=0; i<bonesCount; i++) {
	//	Joint *joint = skeleton + i;
	//
	//	int changed = 0;
	//	fa.SetPos(i + 1,  0); changed += ImGui::FastDragValue(&joint->localPosition.x);
	//	fa.SetPos(i + 1,  1); changed += ImGui::FastDragValue(&joint->localPosition.y);
	//	fa.SetPos(i + 1,  2); changed += ImGui::FastDragValue(&joint->localPosition.z);
	//	fa.SetPos(i + 1,  3); changed += ImGui::FastDragValue(&joint->localRotation.w);
	//	fa.SetPos(i + 1,  4); changed += ImGui::FastDragValue(&joint->localRotation.x);
	//	fa.SetPos(i + 1,  5); changed += ImGui::FastDragValue(&joint->localRotation.y);
	//	fa.SetPos(i + 1,  6); changed += ImGui::FastDragValue(&joint->localRotation.z);
	//
	//}

	ImGui::PopItemWidth();	Op::PostRender();
}

void OpSkeleton::Update() {
	//if ( ! DidInputsChange())
	//	return;


	matrices->Clear();
	//for (int i=0; i<number_of_inputs; i++) {
	//	auto input = default_link_inputs + i;
	//	matrices->Add(input->matrix);
	//}

	// works, but fix model loading
#if 0

	// recalculate localtoworld for each joint, so we can multiply bindpose with it
for (int ii=0; ii<bonesCount; ii++) {
	int i =  recursivesortedids[ii];
		bone_t *bone = bones + i;
		
		
#if 1
		skeleton[i].localMatrix = glm::translate(skeleton[i].localPosition) * glm::toMat4(skeleton[i].localRotation);
#else
		skeleton[i].localMatrix = glm::toMat4(skeleton[i].localRotation) * glm::translate(skeleton[i].localPosition);
#endif


		if (bone->parentid == -1) {
			skeleton[i].localToWorld = skeleton[i].localMatrix;
		} else {
			Joint *parent = skeleton + bone->parentid;
#if 1
			skeleton[i].localToWorld = parent->localToWorld * skeleton[i].localMatrix;
#else 
			skeleton[i].localToWorld = skeleton[i].localMatrix * parent->localToWorld;
#endif
		}
	}


	matrices->SetAmount(bonesCount);
	for (int i=0; i<bonesCount; i++) {
#if 1
		glm::mat4 tmpmul = skeleton[i].bindpose * skeleton[i].localToWorld;
#else
		glm::mat4 tmpmul = skeleton[i].localToWorld * skeleton[i].bindpose;
#endif
		float *tmp = glm::value_ptr(tmpmul);
		matrices->Add(tmp, i);
	}

	default_link_outputs[0].changed++;
#endif

}

void OpSkeleton::RenderEditor() {
	Op::RenderEditor();
	ImGui::DragInt("inputs", &number_of_inputs, 1.0f, 2, 16);
}

std::string OpSkeleton::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "inputs %d",
		number_of_inputs
	);
	return std::string(buf);
}

void OpSkeleton::OnLinkDisconnect(int id) {
	// reset matrix when we remove the link, so we cont need this std::vector shit to detect the first two "real" matrices... we just calculate all
	// multiplying by identity doesnt matters
	mat_identity(default_link_inputs[id].matrix);
}

void OpSkeleton::ReadExtraData(char *line) {
	sscanf(line, "inputs %d",
		&number_of_inputs
	);
}

OpSkeleton::OpSkeleton() {
	Init();
}

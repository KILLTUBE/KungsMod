#include "../opsys/opsys.h"
#include "../rd-rend2/tr_local.h"

void op_type_image_imgui(LinkOutput *ol) {
	image_t *image = tr.images + ol->val_i;
	if (image == NULL) {
		ImGui::Text("image == NULL");
		return;
	}
	ImGui::Text("texnum=%d", image->texnum);
	ImGui::Image((ImTextureID)image->texnum, ImVec2(256,256));
}
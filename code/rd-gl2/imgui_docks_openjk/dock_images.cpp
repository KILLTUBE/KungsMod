#include "dock_images.h"
#include <include_imgui.h>
#include <client/client.h>

#include <tr_local.h>

DockImages::DockImages() {
}

const char *DockImages::label() {
	return "Images";
}

void imgui_webtech_images() {
	
	for (int i=0; i<tr.numImages; i++) {
		image_t *image = tr.images[i];
		
		ImGui::PushID(image);

		ImGui::Text("images[%d] width=%d height=%d name=%s", i, image->width, image->height, image->imgName);
		ImGui::Text("images[%d] texnum=%d", i, image->texnum);
		int bla = image->texnum;
		ImGui::DragInt("texnum", &bla);
		image->texnum = bla;
		ImGui::Image((ImTextureID)image->texnum, ImVec2(256,256));


		ImGui::Text("IMGFLAG_NONE = %d", image->flags & IMGFLAG_NONE);
		ImGui::Text("IMGFLAG_MIPMAP = %d", image->flags & IMGFLAG_MIPMAP);
		ImGui::Text("IMGFLAG_PICMIP = %d", image->flags & IMGFLAG_PICMIP);
		ImGui::Text("IMGFLAG_CUBEMAP = %d", image->flags & IMGFLAG_CUBEMAP);
		ImGui::Text("IMGFLAG_NO_COMPRESSION = %d", image->flags & IMGFLAG_NO_COMPRESSION);
		ImGui::Text("IMGFLAG_NOLIGHTSCALE = %d", image->flags & IMGFLAG_NOLIGHTSCALE);
		ImGui::Text("IMGFLAG_CLAMPTOEDGE = %d", image->flags & IMGFLAG_CLAMPTOEDGE);
		ImGui::Text("IMGFLAG_SRGB = %d", image->flags & IMGFLAG_SRGB);
		ImGui::Text("IMGFLAG_GENNORMALMAP = %d", image->flags & IMGFLAG_GENNORMALMAP);
		ImGui::Text("IMGFLAG_MUTABLE = %d", image->flags & IMGFLAG_MUTABLE);
		ImGui::Text("IMGFLAG_3D = %d", image->flags & IMGFLAG_3D);

		ImGui::PopID();
	}
}

void DockImages::imgui() {
	char headertext[256];


	

	static char filename[256] = {""};
	ImGui::InputText("filename", filename, sizeof(filename));

	if (ImGui::Button("Load filename")) {
		R_FindImageFile(filename, IMGTYPE_COLORALPHA, (imgFlags_t)(IMGFLAG_MIPMAP | IMGFLAG_PICMIP));
	}

	snprintf(headertext, sizeof headertext, "numImages: %d", tr.numImages);
	if (ImGui::CollapsingHeader(headertext)) {
		imgui_webtech_images();
	}


}
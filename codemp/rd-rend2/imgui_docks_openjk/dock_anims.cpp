#include "dock_anims.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"

DockAnims::DockAnims() {}

const char *DockAnims::label() {
	return "Anims";
}

EXTERNC  animation_t		bgHumanoidAnimations[MAX_TOTALANIMATIONS];

#include "anims_to_string.h"

namespace ImGui {
	bool DragUShort(const char *str, unsigned short *val) {
		int tmp = *val;
		bool ret = DragInt(str, &tmp);
		*val = tmp;
		return ret;
	}
	bool DragShort(const char *str, short *val) {
		int tmp = *val;
		bool ret = DragInt(str, &tmp);
		*val = tmp;
		return ret;
	}
	bool DragChar(const char *str, signed char *val) {
		int tmp = *val;
		bool ret = DragInt(str, &tmp);
		*val = tmp;
		return ret;
	}
}

#include<Shlwapi.h>


void DockAnims::imgui() {
	animation_t *anims = bgHumanoidAnimations;


	static char filter[256] = {""};
	ImGui::InputText("filter", filter, sizeof(filter));

	for (int anim_id = 0; anim_id < MAX_TOTALANIMATIONS; anim_id++) {
		animation_t *anim = anims + anim_id;

		const char *name = anims2str[anim_id];
		if (filter[0] && !Q_stristr(name, filter))
			continue;

		ImGui::PushID(anim_id);
		


		ImGui::PushItemWidth( 100/*ImGui::GetWindowWidth() / 10*/ );

		ImGui::DragUShort("firstFrame" , &anim->firstFrame ); ImGui::SameLine();
		//ImGui::DragInt("flipflop"   , &anim->flipflop   ); ImGui::SameLine();
		ImGui::DragShort("frameLerp"  , &anim->frameLerp  ); ImGui::SameLine();
		//ImGui::DragInt("initialLerp", &anim->initialLerp); ImGui::SameLine();
		ImGui::DragChar("loopFrames" , &anim->loopFrames ); ImGui::SameLine();
		ImGui::DragUShort("numFrames"  , &anim->numFrames  ); ImGui::SameLine();
		//ImGui::DragInt("reversed"   , &anim->reversed   );

		// name at last, so everything is nicely aligned below each other
		ImGui::Text("anim_id=%d name=%s", anim_id, name);  

		ImGui::PopItemWidth();

		ImGui::PopID();
	}
}


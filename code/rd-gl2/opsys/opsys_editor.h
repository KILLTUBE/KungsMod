#ifndef OPSYSTEM_EDITOR_H
#define OPSYSTEM_EDITOR_H

#include "../imgui/include_imgui.h"

class OpSystemEditor {
public:
	OpSystem *opsys;
	int showAddOpsMenu = 0;
	ImVec2 positionForNewOp;

	ImVec2 winpos; // e.g. 200,200
	ImVec2 absolutemousepos; // when mouse is at 10,10 in window, this will be 210,210
	ImVec2 relativemousepos; // this will be at 10,10 now, window coordinates
	ImVec2 mousepos; // the actual position with all the shit calculated in, final position of ops

	OpSystemEditor(OpSystem *opsys_);

	void SetupSomeValues();
	void DoBreadcrumbNavigation();

	
	int scissor_active = 0;
	ImVec2 scissor_from;
	ImVec2 scissor_to;
	void DoMouseScissoring();


	int rect_active = 0;
	ImVec2 rect_from;
	ImVec2 rect_to;
	void DoMouseRectSelection();

	void DrawLinkLines();
	void HandleLinkCreating();
	void DragAndDrop();

	ImVec2 userscrollposition;
	void HandleMiddleMouseScroll();
	void HandleCopyPaste();
	
	void DoFrame();
	void ContextMenu();
};

#endif
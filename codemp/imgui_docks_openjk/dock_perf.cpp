#if 0
#include "dock_perf.h"
#include "../imgui_docks/dock_console.h"
#include "../imgui_openjk/gluecode.h"

DockPerf::DockPerf() {}

#include "../tr_debug.h"

const char *DockPerf::label() {
	return "Perf";
}

void DockPerf::imgui() {
	if (r_perf->integer) {
		if (ImGui::Button("Disable Performance Measuring"))
			Cvar_SetInt(r_perf, 0);
	} else {
		if (ImGui::Button("Enable Performance Measuring"))
			Cvar_SetInt(r_perf, 1);
	}

	for (auto perfdata : performancelog) {
		const char *name = perfdata.first.c_str();
		int starttime = perfdata.second.starttime;
		int stoptime = perfdata.second.stoptime;
		int delta = stoptime - starttime;
		float milliseconds = (float)delta;
		const float maxTime = 1000.0 / 60.0; // 16.66ms is the absolute maximum, if a frame takes like 10ms its already in the very evil range...
		float maxPercent = (milliseconds / maxTime) * 100.0;
		ImGui::Text("%s: start=%10d stop=%10d milliseconds=%10.2f maxPercent=%10.2f", name, starttime, stoptime, milliseconds, maxPercent);
	}
}
#endif
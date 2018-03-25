#include "../opsys/opsys.h"

//#include <include_duktape.h>
#include "../imgui_docks/dock_console.h"
#include "../imgui/imgui_dock.h"

#include "../opsys/opsys_utils.h"
#include "../ops/op_prefab.h"
#include <list>
#include "../opsys/opsys_hierarchy.h"
#include "../opsys/opsys_explorer.h"
#include "../ops/op_file.h"


//#include <globals.h>

int imgui_line(ImVec2 a, ImVec2 b) {

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddLine(a, b, 0xffffffff, 2.0f);
	return 0;
}

int imgui_point(ImVec2 a, float radius = 1.0f, unsigned int color = 0xffffff) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->AddCircleFilled(a, radius, color);
	return 0;
}








void update_op_system() {

	for (auto sys : systems)
	{
		sys->update();
	}
}

void render_imgui_ops() {
	if (cursys == NULL) {
		ImGui::Text("cursys == NULL");
		return;
	}
	cursys->editor->DoFrame();
}

char opseditor_filename[64] = "perm.txt";

std::vector<std::string> files;

extern char *currentwindow;

char node_opsys_filename[256] = {"opsystem/default.opsys"};

void render_imgui_ops_editor() {

	if (cursys == NULL) {
		ImGui::Text("cursys == NULL");
		return;
	}

	//static bool show_editor;

	//ImGui::Begin("OPS editor", &show_editor);
	//ImGui::SetDockActive

	int showops = strcmp(currentwindow, "Hierarchy") != 0;

	//if (!showops) {
	//	if (selected_node) {
	//		ImGui::Text("Current Node: %s", selected_node->name.c_str());
	//
	//		ImGui::InputText("opsys", node_opsys_filename, sizeof node_opsys_filename);
	//		if (ImGui::Button("Load")) {
	//			//selected_node->opsystem = new OpSystem(node_opsys_filename, 1);
	//			//auto opsys = selected_node->opsystem;
	//			//opsys->loadFile();
	//		}
	//
	//	} else {
	//		ImGui::Text("No node selected");
	//
	//	}
	//	return;
	//}

	//if (g_dock.m_current) {
	//	//ImGui::Text("Curret Dock: %s\n", g_dock.m_current->label); // this var only gives the Dock which is rendered atm
	//	ImGui::Text("Focused Window: %s", currentwindow);
	//	ImGui::Text("Renderables: %d", cursys->renderables.size());
	//	
	//	//ImGui::IsWindowFocused
	//}

	if (ImGui::Button("Update files")) {
		
		
	}
	
	for (auto file : files) {
		if ( ImGui::Button(file.c_str()) ) {
			auto newsys = new OpSystem((char *)file.c_str(), 0);
			newsys->loadFile(newsys->name);
			newsys->regenerateCallGraphs();
		}

		ImGui::SameLine(0,5);

		ImGui::PushID(file.c_str());
		if (ImGui::Button("As Prefab")) {
			OpPrefab *prefab = new OpPrefab();
			//strcpy(prefab->filename, file.c_str());
			prefab->ReadExtraData((char *)("filename " + file).c_str());
			//prefab->pos.x = 100;
			//prefab->pos.y = 100;
			//prefab->size.x = 100;
			//prefab->size.y = 100;
			//prefab->selected = 1;
			cursys->add((Op *)prefab);
		}
		ImGui::PopID();
	}

	//ImGui::Checkbox("force_movement", (bool *)&force_movement);
	if (selected_node) {


		ImGui::InputText("node name", selected_node->name, sizeof selected_node->name);

		ImGui::InputText("filename", selected_node->opsystem.name, sizeof selected_node->opsystem.name);
		//selected_node->name.resize( strlen( selected_node->name.data() ) );
	} else {
		//ImGui::InputText("filename", opseditor_filename, sizeof opseditor_filename);
	}

	for (auto sys : systems) {
		int popstyle = 0;
		if (cursys == sys) {
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 1.0f, 1.0f));
			popstyle = 1;
		}

		ImGui::PushID(sys);
		if (ImGui::Button(sys->name))
			OpSystem::SetCurrent(sys);
		ImGui::PopID();

		if (popstyle)
			ImGui::PopStyleColor();
	}
	
	//if (ImGui::Button("Save to filename")) { cursys->saveFile(opseditor_filename); }
	//if (ImGui::Button("Load System from filename")) { cursys->loadFile(opseditor_filename); cursys->regenerateCallGraphs(); }
	ImGui::Text("cursys = %s", cursys->name);
	if (ImGui::Button("Save System")) { cursys->saveFile(cursys->name); }
	if (ImGui::Button("Load System")) { cursys->loadFile(cursys->name); cursys->regenerateCallGraphs(); }
	if (ImGui::Button("Clear System")) { cursys->clearScene(); }
	ImGui::SameLine(0, 5);
	if (ImGui::Button("Unselect all")) {
			cursys->unselectAll();
	}

	if (ImGui::Button("Regenerate Call Graphs")) {
		cursys->regenerateCallGraphs();
	}

	cursys->renderEditor();

	//ImGui::End();
}

void imgui_op_list() {
	cursys->makeOpButtons();
}

char *currentwindow = "OPS";

//#include <tab_physfs.h>

//#include <imgui_entities.h>

void render_op_system() {



	struct windows {
		std::string name;
		void (*renderimgui)();
		bool show;

	};

	struct windows wins[] = {
	
		{"OPList"        , imgui_op_list           , 1},
		{"Hierarchy"     , render_hierarchy        , 1},
		//{"Console"       , imgui_op_console        , 1},
		//{"REPL"          , imgui_op_repl2          , 1},
		{"OPS"           , render_imgui_ops        , 1},
		{"Editor"        , render_imgui_ops_editor , 1},
		//{"Explorer"      , render_explorer         , 1},
		//{"PHYSFS"        , tab_physfs              , 1},
		//{"Entities"        , imgui_entities              , 1},
		
		{"", NULL, 0}
	};
	

	struct windows *it = wins;
	for (it = wins; it->renderimgui; it++) {
		if (BeginDock(it->name.c_str(), &it->show)) {   
			//ImGui::Print(); // print docking information
			it->renderimgui();
			if (ImGui::IsWindowFocused()) {
				currentwindow = (char *)it->name.c_str();
			}
		}
		EndDock();
	}



	
	
	
}



#if 0
int main(int, char**)
{
	
	js_init_full();

    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
	glfwWindowHint(GLFW_MAXIMIZED, 1);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "tcp imgui operators", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Setup ImGui binding
    ImGui_ImplGlfw_Init(window, true);

    // Load Fonts
    // (there is a default font, this is only if you want to change it. see extra_fonts/README.txt for more details)
    //ImGuiIO& io = ImGui::GetIO();
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyClean.ttf", 13.0f);
    //io.Fonts->AddFontFromFileTTF("../../extra_fonts/ProggyTiny.ttf", 10.0f);
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

    bool show_test_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
	double frame_start = glfwGetTime();


	init_wsa();

	serverdata_t serverdata;
	strcpy(serverdata.ip, "127.0.0.1");
	strcpy(serverdata.port, "13000");
	strcpy(serverdata.ondata, "function OnData(buffer)\n{\tprintf(\"%\", buffer);\n}\n");
	serverdata.running = 0;
	serverdata.ListenSocket = INVALID_SOCKET;

	clientdata_t clientdata;
	strcpy(clientdata.ip, "127.0.0.1");
	strcpy(clientdata.port, "13000");
	strcpy(clientdata.ondata, "function OnData(buffer)\n{\tprintf(\"%\", buffer);\n}\n");
	clientdata.ConnectSocket = INVALID_SOCKET;


	generate_texture();





    // Main loop
    while (!glfwWindowShouldClose(window)) {
		double wait_time = 1.0 / (60.0);
		if(glfwGetTime() - frame_start < wait_time)
		{
		double dur = (wait_time - (glfwGetTime() - frame_start));
		Sleep((DWORD)(dur * 1000.0 + 0.5));
		}
		frame_start = glfwGetTime();

        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();

        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (show_another_window)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello");
            ImGui::End();
        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (show_test_window)
        {
            ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&show_test_window);
        }


		static bool show_client;
		ImGui::Begin("Client", &show_client);
		ImGui::Button("Client");

		ImGui::InputText("IP:", clientdata.ip, 128);
		ImGui::InputText("Port:", clientdata.port, 128);
		ImGui::Text("Socket: %d", clientdata.ConnectSocket);

		ImGui::Text("Actions:");
		
		if (clientdata.ConnectSocket != INVALID_SOCKET) {
			tcp_client_recv(&clientdata);
		}
		

		if (ImGui::Button("Connect()")) {
			tcp_client_connect(&clientdata);
		}
		ImGui::Button("Disconnect()");
		if (ImGui::Button("Send(\"test\")")) {
			tcp_client_send(&clientdata);
			console_lines.push_back("test");
		}

		ImGui::Text("Reactions:");
			
		ImGui::InputTextMultiline("OnData:", clientdata.ondata, 128);


		ImGui::End();




		static bool show_server;
		ImGui::Begin("Server", &show_server);
		ImGui::Button("Server");
		
		
		ImGui::InputText("IP:", serverdata.ip, 128);
		ImGui::InputText("Port:", serverdata.port, 128);
		ImGui::Text("Socket: %d", serverdata.ListenSocket);


		ImGui::Text("Actions:");
		
		if (ImGui::Button("Listen()")) {
			tcp_listen(&serverdata);
			imgui_log("listen\n");
		}
		// try to accept a new client every frama
		if (serverdata.running) {
			tcp_accept(&serverdata);
			tcp_server_read_all(&serverdata);
		}

		if (ImGui::Button("Disconnect()")) {
			imgui_log("disconnect\n");
		}
		ImGui::Button("Disconnect()");
		if (ImGui::Button("Send(\"test\")")) {
			console_lines.push_back("test");


		}

		ImGui::Text("Reactions:");
			
		
		ImGui::InputTextMultiline("OnData:", serverdata.ondata, 128);

		ImGui::Text("Clients:");
		server_clientdata_t *shutdown_scd = NULL;
		for (auto scd : serverdata.clientsockets) {

			ImGui::PushID(scd);

			ImGui::Text("Client: %d", scd->socket);

			ImGui::SameLine(0.0f, 5.0f);
			if (ImGui::Button("Shutdown()"))
			{
				// don't touch this stuff when iterating over it
				shutdown_scd = scd;
			}
			ImGui::SameLine(0.0f, 5.0f);
			if (ImGui::Button("Send()"))
			{
				imgui_log("send from #%ld to #%ld\n", serverdata.ListenSocket, scd->socket);
				tcp_send(scd->socket, scd->to_send, sizeof scd->to_send);
			}
			ImGui::InputText(scd->label, scd->to_send, sizeof scd->to_send);

			ImGui::PopID();
		}

		if (shutdown_scd) {
			// shutdown the connection since no more data will be sent
			int ret = shutdown(shutdown_scd->socket, SD_SEND);
			if (ret == SOCKET_ERROR) {
				imgui_log("shutdown failed with error: %d\n", WSAGetLastError());
				//closesocket(clientdata->ConnectSocket);
				//WSACleanup();
				//return 1;
			}
			serverdata.clientsockets.remove(shutdown_scd);
			free(shutdown_scd);
		}


		ImGui::End();



		

		
		ImGui::Image((ImTextureID)checkerboardid, ImVec2(100,100));


        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        //glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();

		#if 0
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
			glLoadIdentity();									// Reset The View
			glTranslatef(0.0f,0.0f,-5.0f);

			//glRotatef(xrot,1.0f,0.0f,0.0f);
			//glRotatef(yrot,0.0f,1.0f,0.0f);
			//glRotatef(zrot,0.0f,0.0f,1.0f);

			//glBindTexture(GL_TEXTURE_2D, texture[0]);
			glBindTexture(GL_TEXTURE_2D, checkerboardid);

			glBegin(GL_QUADS);
				// Front Face
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
				// Back Face
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
				// Top Face
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
				// Bottom Face
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				// Right face
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
				// Left Face
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
			glEnd();
		#endif

        glfwSwapBuffers(window);
    }
	
	ImGuiContext& g = *GImGui;
	SaveIniSettingsToDisk(g.IO.IniFilename);


    // Cleanup
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();


    return 0;
}

#endif

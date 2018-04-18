#include "../include_gl.h"
#include "../opsys/opsys_opengl.h"
#include "op.h"
#include "op_gl_framebuffer.h"
//#include "util.h"

//void make_program)(CLASSNAME *op) {
//	if (program)
//		glDeleteProgram(program);
//	GLuint program = glCreateProgram();
//	if ( ! vertexshader) {
//		imgui_log("vertexshader not set for %s\n", name);
//		goto error;
//	}
//	if ( ! fragmentshader) {
//		imgui_log("shader2 not set for %s\n", name);
//		goto error;
//	}
//	glAttachShader(program, vertexshader);
//	glAttachShader(program, fragmentshader);
//	glLinkProgram(program);
//	GLint status;
//	glGetProgramiv(program, GL_LINK_STATUS, &status);
//	if (status == GL_FALSE) {
//		GLint length;
//		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
//		GLchar *info = (GLchar *)calloc(length, sizeof(GLchar));
//		glGetProgramInfoLog(program, length, NULL, info);
//		imgui_log("glLinkProgram failed: %s\n", info);
//		free(info);
//		
//		goto error;
//	} else {
//		haserror = 0;
//	}
//	glDetachShader(program, vertexshader);
//	glDetachShader(program, fragmentshader);
//	//glDeleteShader(shader1);
//	//glDeleteShader(shader2);
//	program = program;
//	imgui_log("update program: %d\n", program);
//	return;
//error:
//	if (program)
//		glDeleteProgram(program);
//	if (program)
//		glDeleteProgram(program);
//	program = 0;
//	haserror = 1;
//}

void OpFramebuffer::Init() {
	Op::Init();
	type = OP_TYPE_DELIVERER;
	size = ImVec2(300, 30);
	pos = ImVec2(250, 300);
	strcpy( name, "OpFramebuffer" );
	
	//fragmentshader = 0;
	//vertexshader = 0;

	number_of_inputs = 2;
	InitLink(0, "Frag", OP_TYPE_FRAGMENTSHADER);
	InitLink(1, "Vert", OP_TYPE_VERTEXSHADER);
	number_of_outputs = 1;
	InitLinkOutput(0, "Prog", OP_TYPE_PROGRAM);
	
	ResizeMinimal();
}

void OpFramebuffer::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos + ImVec2(5,5));
	//ImGui::Text("%d", program);


    //ImGuiIO& io = ImGui::GetIO();
    ////static ImVec2 imagePos = ImVec2(textureX/2, textureY/2); // If mouse cursor is outside the screen, use center of image as zoom point
    //ImVec2 cursorPos = ImGui::GetCursorScreenPos();          // "cursor" is where imgui will draw the image
    //ImVec2 mousePos = io.MousePos;

    //////////////////////////////////////////////////////
    // Draw the image/texture, filling the whole window //
    //////////////////////////////////////////////////////
    //ImGui::Image(reinterpret_cast<ImTextureID>(texture), size, ImVec2(0, 0), ImVec2(1, -1));
    ImGui::Image((ImTextureID)((size_t)texture), ImVec2(100,200), ImVec2(0, 0), ImVec2(1, -1));	

	Op::PostRender();
}


//void dispatch)(CLASSNAME *op) {
//	switch(event) {
//		case OP_EVENT_CREATE:
//
//			break;
//		case OP_EVENT_DELETE:
//
//			break;
//		case OP_EVENT_RESIZE:
//
//			break;
//	}
//}


void OpFramebuffer::Update() {

	//if (fragmentshader && vertexshader && haserror==0 && program==0) {
	//	make_program)(op);
	//	default_link_outputs[0].changed++;
	//}

	//auto *ol = default_link_outputs + 0;
	//for (auto il : *ol->inputlinks) {
	//	il->opengl_id = program;
	//	//if (type == OpType::OP_TYPE_SENDER)
	//	//	il->owner->update(il->owner);
	//}
}

void OpFramebuffer::RenderEditor() {

#if 0

	Op::RenderEditor();
	//ImGui::Text("fragmentshader: %d", fragmentshader);
	//ImGui::Text("vertexshader: %d", vertexshader);
	//ImGui::Text("program: %d", program);



	







	if ( ImGui::Button("Make Framebuffer") ) {

//The Problem was that either iOS or Cocos2D (or both) can have a unique framebuffer. The handle of that unique frame buffer would be different than 0, and may be different each time.
//To solve this, I have to grab the current FBO's handle, do my custom Framebuffer stuff and then re-apply the FBO's handle after I'm done.
//Creates a variable to reference the original Frame Buffer Object
GLint oldFBO;

//Assigns the currently used FBO's handle (which is a 'GLint') to the variable 'oldFBO'
glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);

		////////////////////////////////////////////////////////////////////////
		// Create and bind framebuffer, attach a depth buffer to it           //
		// Create the texture to render to, and attach it to the framebuffer  //
		////////////////////////////////////////////////////////////////////////
		qglGenFramebuffers(1, &framebuffer);
		qglBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		qglGenRenderbuffers(1, &depthbuffer);
		qglBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);
		qglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, resx, resy);
		qglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resx, resy, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		//ES2//glDrawBuffers(1, DrawBuffers);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			imgui_log("Error in setting up the framebuffer\n");
		} else {
			imgui_log("framebuffer made successfully\n");
		}




//here is when you would create or manipulate custom framebuffers.//
//After that, You set the original FBO as the current Framebuffer
glBindFramebuffer(GL_FRAMEBUFFER, oldFBO);
	}



	if (ImGui::Button("Render Framebuffer")) {
	

//The Problem was that either iOS or Cocos2D (or both) can have a unique framebuffer. The handle of that unique frame buffer would be different than 0, and may be different each time.
//To solve this, I have to grab the current FBO's handle, do my custom Framebuffer stuff and then re-apply the FBO's handle after I'm done.
//Creates a variable to reference the original Frame Buffer Object
GLint oldFBO;

//Assigns the currently used FBO's handle (which is a 'GLint') to the variable 'oldFBO'
glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFBO);

    //if (textureX != size.x || textureY != size.y) {
        //textureX = size.x;
        //textureY = size.y;
        //cam_width = cam_height*textureX/float(textureY);
	
		GLsizei textureX = 100;
		GLsizei textureY = 200;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureX, textureY, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, textureX, textureY);





		    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0,0,textureX,textureY);

	//glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //glUseProgram(cube_program);


	
//here is when you would create or manipulate custom framebuffers.//
//After that, You set the original FBO as the current Framebuffer
qglBindFramebuffer(GL_FRAMEBUFFER, oldFBO);

    }

    //draw_cube();


#endif
}

void OpFramebuffer::OnLinkDisconnect(int id) {
	//log("disconnect id: %d\n", id);
	//switch (default_link_inputs[id].type) {
	//	case OP_TYPE_FRAGMENTSHADER:
	//		fragmentshader = 0;
	//		break;
	//	case OP_TYPE_VERTEXSHADER:
	//		vertexshader = 0;
	//		break;
	//}
}

void OpFramebuffer::OnLinkUpdate(int id) {
	//log("link changed id: %d\n", id);
	//make_program)(op);
	//switch (default_link_inputs[id].type) {
	//	case OP_TYPE_FRAGMENTSHADER:
	//		//fragmentshader = 0;
	//		break;
	//	case OP_TYPE_VERTEXSHADER:
	//		//vertexshader = 0;
	//		break;
	//}
}

OpFramebuffer::OpFramebuffer() {
	Init();
}
//#include "craftstructs.h"
#include "../include_imgui.h"
//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>

#include "op.h"
#include "op_renderer.h"

#include "../opsys/opsys.h"

void OpRenderer::Init() {

	Op::Init();
	strcpy( name, "OpRenderer" );
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	
	number_of_inputs = 9;
	InitLink(0, "BufPos", OP_TYPE_GLBUFFER );
	InitLink(1, "BufCol", OP_TYPE_GLBUFFER );
	InitLink(2, "AttPos", OP_TYPE_GLATTRIB );
	InitLink(3, "AttCol", OP_TYPE_GLATTRIB );
	InitLink(4, "Mat", OP_TYPE_MATRIX );
	InitLink(5, "Prog", OP_TYPE_PROGRAM );
	InitLink(6, "UniMat", OP_TYPE_GLUNIFORM );
	InitLink(7, "count", OP_TYPE_FLOAT ); // meh, normally int, but atm everything just works with floats... might change late or kick out int at all
	InitLink(8, "drawmode", OP_TYPE_GLDRAWMODE );
	number_of_outputs = 1;
	InitLinkOutput(0, "Mesh", OP_TYPE_MESH );

	type             = OpType::OP_TYPE_REQUESTER;
	shallDrawInScene = 1;
	isRenderer = 1;
}

void OpRenderer::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos);
	ImGui::Text("foooo");
	//ImGui::Image((ImTextureID)textureid, size/* + ImVec2(-20,-20)*/);
	//
	//ImGui::SetCursorPos(pos + ImVec2(5,5));
	//ImGui::Text("Checkboard texid=%d", textureid);
	Op::PostRender();
}


//extern std::list<Mesh *> meshes;


void OpRenderer::Update() {
}

void OpRenderer::RenderEditor() {
	Op::RenderEditor();
	//ImGui::Text("prog: %d", default_link_inputs[2].opengl_id);
	//ImGui::Text("textureid: %x", textureid);
}

std::string OpRenderer::WriteExtraData() {
	//fprintf(f, "x %f y %f z %f n %f",
	//	x,
	//	y,
	//	z,
	//	n
	//);
	return std::string("");
}

void OpRenderer::ReadExtraData(char *line) {
	//sscanf(line, "x %f y %f z %f n %f",
	//	&x,
	//	&y,
	//	&z,
	//	&n
	//);
}

std::vector<float> points;

void OpRenderer::DrawInScene() {
	

	//// Backup GL state
	//GLint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
	//GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	//GLint last_active_texture; glGetIntegerv(GL_ACTIVE_TEXTURE, &last_active_texture);
	//GLint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
	//GLint last_element_array_buffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
	//GLint last_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
	//GLint last_blend_src; glGetIntegerv(GL_BLEND_SRC, &last_blend_src);
	//GLint last_blend_dst; glGetIntegerv(GL_BLEND_DST, &last_blend_dst);
	//GLint last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb);
	//GLint last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha);
	//GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
	//GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box); 
	//GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
	//GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
	//GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
	//GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

/*
	InitLink(0, "BufPos", OP_TYPE_GLBUFFER );
	InitLink(1, "BufCol", OP_TYPE_GLBUFFER );
	InitLink(2, "AttPos", OP_TYPE_GLATTRIB );
	InitLink(3, "AttCol", OP_TYPE_GLATTRIB );
	InitLink(4, "Mat", OP_TYPE_MATRIX );
	InitLink(5, "Prog", OP_TYPE_PROGRAM );
	InitLink(6, "UniMat", OP_TYPE_GLUNIFORM );
	InitLink(7, "count", OP_TYPE_INT );
	InitLink(8, "drawmode", OP_TYPE_GLDRAWMODE );
*/

	//return;


	//if (strcmp(name, "yes"))
	//	return;


    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
    qglEnable(GL_BLEND);
    //qglBlendEquation(GL_FUNC_ADD);
    qglBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    qglDisable(GL_CULL_FACE);
    qglDisable(GL_DEPTH_TEST);
    qglEnable(GL_SCISSOR_TEST);
    //qglActiveTexture(GL_TEXTURE0);

	qglUseProgram(default_link_inputs[5].opengl_id);

	
	qglUniformMatrix4fv(default_link_inputs[6].opengl_id, 1, GL_FALSE, default_link_inputs[4].matrix);
	//glUniformMatrix4fv(default_link_inputs[6].opengl_id, 1, GL_FALSE, matrix);



	qglBindBuffer(GL_ARRAY_BUFFER, default_link_inputs[0].opengl_id);
	qglVertexAttribPointer(default_link_inputs[2].opengl_id, /*components*/4, GL_FLOAT, GL_FALSE, 0, 0); // https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object
	qglEnableVertexAttribArray(default_link_inputs[2].opengl_id);
	
	qglBindBuffer(GL_ARRAY_BUFFER, default_link_inputs[1].opengl_id);
	qglVertexAttribPointer(default_link_inputs[3].opengl_id, /*components*/4, GL_FLOAT, GL_TRUE, 0, 0);
	qglEnableVertexAttribArray(default_link_inputs[3].opengl_id);
	
	qglDrawArrays((int)default_link_inputs[8].val_f, 0, /*count*/(int)default_link_inputs[7].val_f);
	//log("count: %d\n", (int)default_link_inputs[7].val_f);
	qglDisableVertexAttribArray(default_link_inputs[2].opengl_id);
	qglDisableVertexAttribArray(default_link_inputs[3].opengl_id);




	for (auto sys : systems) {
		for (auto astar : sys->astars) {
			for (auto node : astar->nodes) {
			
			
			
				GLuint vertices = node->buffer;

				qglBindBuffer(GL_ARRAY_BUFFER, vertices);
				qglVertexAttribPointer(default_link_inputs[2].opengl_id, /*components*/3, GL_FLOAT, GL_FALSE, 0, 0); // https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object
				qglEnableVertexAttribArray(default_link_inputs[2].opengl_id);
	
				qglBindBuffer(GL_ARRAY_BUFFER, default_link_inputs[1].opengl_id);
				qglVertexAttribPointer(default_link_inputs[3].opengl_id, /*components*/4, GL_FLOAT, GL_TRUE, 0, 0);
				qglEnableVertexAttribArray(default_link_inputs[3].opengl_id);
	
				//glDrawArrays((int)default_link_inputs[8].val_f, 0, /*count*/(int)default_link_inputs[7].val_f);
				qglDrawArrays((int)default_link_inputs[8].val_f, 0, /*count*/36);
				qglDisableVertexAttribArray(default_link_inputs[2].opengl_id);
				qglDisableVertexAttribArray(default_link_inputs[3].opengl_id);
			}
		}
	}

	//glDisable(GL_DEPTH_TEST);

	if (points.size()) {
		GLuint pointbuffer;
		qglGenBuffers(1,  &pointbuffer);
		qglBindBuffer(GL_ARRAY_BUFFER, pointbuffer);
		qglBufferData(GL_ARRAY_BUFFER, points.size() * 12, (GLvoid *)points.data(), GL_STATIC_DRAW); // 3 floats = 12 bytes per point

		//qglPointSize(10);

		qglVertexAttribPointer(default_link_inputs[2].opengl_id, /*components*/3, GL_FLOAT, GL_FALSE, 0, 0); // https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object
		qglEnableVertexAttribArray(default_link_inputs[2].opengl_id);
	
		qglBindBuffer(GL_ARRAY_BUFFER, default_link_inputs[1].opengl_id);
		qglVertexAttribPointer(default_link_inputs[3].opengl_id, /*components*/4, GL_FLOAT, GL_TRUE, 0, 0);
		qglEnableVertexAttribArray(default_link_inputs[3].opengl_id);
	
		qglDrawArrays(GL_POINTS, 0, points.size());
		qglDisableVertexAttribArray(default_link_inputs[2].opengl_id);
		qglDisableVertexAttribArray(default_link_inputs[3].opengl_id);


		qglDeleteBuffers(1, &pointbuffer);
	}

    //// Restore modified GL state
    //glUseProgram(last_program);
    //glActiveTexture(last_active_texture);
    //glBindTexture(GL_TEXTURE_2D, last_texture);
    //glBindVertexArray(last_vertex_array);
    //glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
    //glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
    //glBlendFunc(last_blend_src, last_blend_dst);
    //if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    //if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    //if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    //if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
    //glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
    //glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);


	//InitLink(0, "BufPos", OP_TYPE_GLBUFFER );
	//InitLink(1, "BufCol", OP_TYPE_GLBUFFER );
	//InitLink(2, "AttPos", OP_TYPE_GLATTRIB );
	//InitLink(3, "AttCol", OP_TYPE_GLATTRIB );
	//InitLink(4, "Mat", OP_TYPE_MATRIX );
	//InitLink(5, "Prog", OP_TYPE_PROGRAM );
	//InitLink(6, "UniMat", OP_TYPE_GLUNIFORM );
	//InitLink(7, "count", OP_TYPE_INT );
	//InitLink(8, "drawmode", OP_TYPE_GLDRAWMODE );


	//return;
	
	GLuint &vertices = default_link_inputs[0].opengl_id;
	GLuint &prog = default_link_inputs[5].opengl_id;
	float *matrix = default_link_inputs[4].matrix;

	GLuint vao;
	
	
	// https://wiki.delphigl.com/index.php/Vertex_Array_Object
	// A VAO is basically the "render state" of an VBO, it will remember all the glVertexAttribPointer calls and the bound VBO's
	// So we could actually remove glBindBuffer() once we generated a VAO of it
	// TODO list... add OpVAO
	qglGenVertexArrays(1, &vao);
	qglBindVertexArray(vao);

	
	qglBindBuffer(GL_ARRAY_BUFFER, vertices);
	

	
	//glClear(/*GL_COLOR_BUFFER_BIT | */GL_DEPTH_BUFFER_BIT);
	//glBindVertexArray(vao);
	
	qglEnableVertexAttribArray(0);
	qglVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	// protect our VAO
	qglBindVertexArray(0);


	qglBindBuffer(GL_ARRAY_BUFFER, 0);



	// draw points 0-3 from the currently bound VAO with current in-use shader
	// we dont need to bind any buffer etc. because that information is all saved in our vao
	qglUseProgram(prog);

	int u_matrix = qglGetUniformLocation(prog, "u_matrix");
	if (u_matrix != -1)
		qglUniformMatrix4fv(u_matrix, 1, GL_FALSE, matrix);

	qglBindVertexArray(vao);
	qglDrawArrays(GL_TRIANGLES, 0, 3);
	
	

	// delete VAO
	qglDeleteVertexArrays(1, &vao);
}

OpRenderer::OpRenderer() {
	Init();
}
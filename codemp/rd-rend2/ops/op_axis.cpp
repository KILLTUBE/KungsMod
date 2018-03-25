#include "../include_gl.h"
#include "../include_glm.h"
//#include "craftstructs.h"
#include "../include_imgui.h"
//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>
#include "op.h"
#include "op_axis.h"
#include "../opsys/opsys.h"
#include "../imgui/imgui_fixedarea.h"
#include "../utils_opengl/debuglines.h"
#include "../include_console.h"
//#include <oglwrap.h>

void Buffer2::LoadFile(char *filename) {
	//PHYSFS_File *file_handle = PHYSFS_openRead(filename);
	//if (file_handle == NULL) {
	//	imgui_log("physfs cant open %s\n", filename);
	//	return;
	//}
	//data = (char *)malloc(PHYSFS_fileLength(file_handle));
	//length = (int)PHYSFS_fileLength(file_handle);
	//int length_read = PHYSFS_read(file_handle, data, 1, length);
	////log("Read file %s length=%d length_read=%d\n", filename, file_length, file_length_read);
	//// todo: if (length != length_read) etc.
	////if (length != length_read)
	////	__asm int 3;
	//PHYSFS_close(file_handle);
}

Buffer2::~Buffer2() {
	free(data);

}

Model::Model(char *filename) {

	char buf[512];

	snprintf(buf, sizeof buf, "meshes/%s/vertices.vec3", filename);
	bufferVertices.LoadFile(buf);
	numberOfVertices = bufferVertices.length / sizeof(float) / 3;

	snprintf(buf, sizeof buf, "meshes/%s/triangles_0.vec3", filename);
	bufferTriangles_0.LoadFile(buf);
	numberOfTriangles = bufferTriangles_0.length / sizeof(float) / 3;

	snprintf(buf, sizeof buf, "meshes/%s/boneweights.vec8", filename);
	bufferBoneweights.LoadFile(buf);

	snprintf(buf, sizeof buf, "meshes/%s/uvs.vec2", filename);
	bufferUvs.LoadFile(buf);


}


void Model::GenerateMergedData() {
	axisvertices = (axisvertex_t *) malloc(sizeof(axisvertex_t) * numberOfVertices);
	
	float *vertices = (float *)bufferVertices.data;
	float *uvs = (float *)bufferUvs.data;
	boneweight_t *boneweights = (boneweight_t *)bufferBoneweights.data;



	int boneid2sorted[61];

	//for (int i=0; i<61; i++) {
	//	// we need to iterate over the bones, so we get the real bone.boneid
	//	// the current "i" is then the the lookup value into sorted array
	//	bone_t *bone = bones + i;
	//	boneid2sorted[bone->boneid] = i;
	//}

	// swap all data into one merged data blob to upload for the GPU
	for (int i=0; i<numberOfVertices; i++) {
			
		axisvertex_t *av = axisvertices + i;
		
		av->vertexid = (float)i;

		av->x = vertices[i*3 + 0];
		av->y = vertices[i*3 + 1];
		av->z = vertices[i*3 + 2];
		
		av->u = uvs[i*2 + 0];
		av->v = uvs[i*2 + 1];
		
		//av->boneindex0 = (float)boneid2sorted[(int)boneweights[i].boneindex0];
		//av->boneindex1 = (float)boneid2sorted[(int)boneweights[i].boneindex1];
		//av->boneindex2 = (float)boneid2sorted[(int)boneweights[i].boneindex2];
		//av->boneindex3 = (float)boneid2sorted[(int)boneweights[i].boneindex3];
		av->boneindex0 = boneweights[i].boneindex0;
		av->boneindex1 = boneweights[i].boneindex1;
		av->boneindex2 = boneweights[i].boneindex2;
		av->boneindex3 = boneweights[i].boneindex3;
		
		av->boneweight0 = boneweights[i].boneweight0;
		av->boneweight1 = boneweights[i].boneweight1;
		av->boneweight2 = boneweights[i].boneweight2;
		av->boneweight3 = boneweights[i].boneweight3;
		
		if ((int)boneweights[i].boneindex0 > highestBoneID) highestBoneID = (int)boneweights[i].boneindex0;
		if ((int)boneweights[i].boneindex1 > highestBoneID) highestBoneID = (int)boneweights[i].boneindex1;
		if ((int)boneweights[i].boneindex2 > highestBoneID) highestBoneID = (int)boneweights[i].boneindex2;
		if ((int)boneweights[i].boneindex3 > highestBoneID) highestBoneID = (int)boneweights[i].boneindex3;
	}
	
}

void Model::UploadVerticesToGPU() {
	if (vertexbuffer)
		qglDeleteBuffers(1, &vertexbuffer);
	qglGenBuffers(1, &vertexbuffer);
	qglBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	qglBufferData(GL_ARRAY_BUFFER, sizeof(axisvertex_t) * numberOfVertices, (void *)axisvertices, GL_STATIC_DRAW);
	qglBindBuffer(GL_ARRAY_BUFFER, 0); // make sure nobody is fucking with our buffers
	regenerateVao = 1;
}

void Model::UploadIndicesToGPU() {
	if (indexbuffer)
		qglDeleteBuffers(1, &indexbuffer);
	qglGenBuffers(1, &indexbuffer);
	qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	qglBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * numberOfTriangles, bufferTriangles_0.data, GL_STATIC_DRAW);
	qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // make sure nobody is fucking with our buffers
	regenerateVao = 1;
}

void Model::UploadToGPU() {
	UploadVerticesToGPU();
	UploadIndicesToGPU();
}

Model::~Model() {
	if (vao)
		qglDeleteVertexArrays(1, &vao);
	if (axisvertices)
		free(axisvertices);
	if (indexbuffer)
		qglDeleteBuffers(1, &indexbuffer);
	if (vertexbuffer)
		qglDeleteBuffers(1, &vertexbuffer);
}

void checkerror(char *msg, char *file, int line) {
	char s[64];

	GLenum err = qglGetError();
	if (err == GL_NO_ERROR)
		return;
	switch( err ) {
		case GL_INVALID_ENUM:      strcpy( s, "GL_INVALID_ENUM" );      break;
		case GL_INVALID_VALUE:     strcpy( s, "GL_INVALID_VALUE" );     break;
		case GL_INVALID_OPERATION: strcpy( s, "GL_INVALID_OPERATION" ); break;
		//case GL_STACK_OVERFLOW:    strcpy( s, "GL_STACK_OVERFLOW" );    break;
		//case GL_STACK_UNDERFLOW:   strcpy( s, "GL_STACK_UNDERFLOW" );   break;
		case GL_OUT_OF_MEMORY:     strcpy( s, "GL_OUT_OF_MEMORY" );     break;
		default:
			snprintf( s, sizeof(s), "%i", err);
			break;
	}

	//log("msg %s file %s line %d gl error: %s\n", msg, file, line, s);

}

void Model::MakeVAO(GLuint program) {
	// todo: regenerate VAO when another program is linked
	if (vao && regenerateVao==0)
		return;
	regenerateVao = 0;
	// https://wiki.delphigl.com/index.php/Vertex_Array_Object
	// A VAO is basically the "render state" of an VBO, it will remember all the glVertexAttribPointer calls and the bound VBO's
	// So we could actually remove glBindBuffer() once we generated a VAO of it
	// TODO list... add OpVAO
	qglGenVertexArrays(1, &vao);
	qglBindVertexArray(vao);
	
	checkerror("", __FILE__, __LINE__);

	
	
	qglBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	
	qglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	checkerror("", __FILE__, __LINE__);
	
	//glClear(/*GL_COLOR_BUFFER_BIT | */GL_DEPTH_BUFFER_BIT);
	//glBindVertexArray(vao);
	
	int a_vertexid    = qglGetAttribLocation(program, "a_vertexid");
	int a_pos         = qglGetAttribLocation(program, "a_pos");
	int a_uv          = qglGetAttribLocation(program, "a_uv");
	int a_boneindices = qglGetAttribLocation(program, "a_boneindices");
	int a_boneweights = qglGetAttribLocation(program, "a_boneweights");

	int offset_vertexid = offsetof(axisvertex_t, vertexid);
	int offset_pos = offsetof(axisvertex_t, x);
	int offset_uv = offsetof(axisvertex_t, u);
	int offset_boneindices = offsetof(axisvertex_t, boneindex0);
	int offset_boneweights = offsetof(axisvertex_t, boneweight0);

	int stride = sizeof(axisvertex_t);
	
	checkerror("glVertexAttribPointer 1", __FILE__, __LINE__);

	//glVertexAttribPointer(GLuint index,  GLint size,  GLenum type,  GLboolean normalized,  GLsizei stride,  const GLvoid * pointer);
	qglVertexAttribPointer(a_vertexid    , 1, GL_FLOAT, GL_FALSE, sizeof(axisvertex_t), (void *)(offset_vertexid   ));
	qglVertexAttribPointer(a_pos         , 3, GL_FLOAT, GL_FALSE, sizeof(axisvertex_t), (void *)(offset_pos        ));
	qglVertexAttribPointer(a_uv          , 2, GL_FLOAT, GL_FALSE, sizeof(axisvertex_t), (void *)(offset_uv         ));
	qglVertexAttribPointer(a_boneindices , 4, GL_FLOAT, GL_FALSE, sizeof(axisvertex_t), (void *)(offset_boneindices));
	qglVertexAttribPointer(a_boneweights , 4, GL_FLOAT, GL_FALSE, sizeof(axisvertex_t), (void *)(offset_boneweights));


	qglEnableVertexAttribArray(a_vertexid);
	qglEnableVertexAttribArray(a_pos);
	qglEnableVertexAttribArray(a_uv);
	qglEnableVertexAttribArray(a_boneindices);
	qglEnableVertexAttribArray(a_boneweights);

	// protect vao
	qglBindVertexArray(0);
}

void Model::ImGuiEditor(ImVec2 pos, ImVec2 size)
{


	FixedArea fa(pos, size - ImVec2(20,0), 14); // remove scrollbar size from width, so no horizontal scroll bar
	ImGui::PushItemWidth(fa.GetColWidth());
	fa.SetCol( 0); ImGui::Text("vid");
	fa.SetCol( 1); ImGui::Text("x");
	fa.SetCol( 2); ImGui::Text("y");
	fa.SetCol( 3); ImGui::Text("z");
	fa.SetCol( 4); ImGui::Text("u");
	fa.SetCol( 5); ImGui::Text("v");
	fa.SetCol( 6); ImGui::Text("bi0");
	fa.SetCol( 7); ImGui::Text("bi1");
	fa.SetCol( 8); ImGui::Text("bi2");
	fa.SetCol( 9); ImGui::Text("bi3");
	fa.SetCol(10); ImGui::Text("bw0");
	fa.SetCol(11); ImGui::Text("bw1");
	fa.SetCol(12); ImGui::Text("bw2");
	fa.SetCol(13); ImGui::Text("bw3");

	int lines_count = numberOfVertices;
	float lines_height = ImGui::GetTextLineHeightWithSpacing(); // 20.0f;
	ImGuiListClipper clipper(lines_count, lines_height);
	//while (clipper.Step()) {
	for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i) {
	//for (int i=0; i<numberOfVertices; i++) {
		axisvertex_t *av = axisvertices + i;
#if 1
		int changed = 0;
		fa.SetPosLeft(i + 1,  0); changed += ImGui::FastDragValue(&av->vertexid);		ImGui::SameLine();
		fa.SetPosLeft(i + 1,  1); changed += ImGui::FastDragValue(&av->x);				ImGui::SameLine();
		fa.SetPosLeft(i + 1,  2); changed += ImGui::FastDragValue(&av->y);				ImGui::SameLine();
		fa.SetPosLeft(i + 1,  3); changed += ImGui::FastDragValue(&av->z);				ImGui::SameLine();
		fa.SetPosLeft(i + 1,  4); changed += ImGui::FastDragValue(&av->u);				ImGui::SameLine();
		fa.SetPosLeft(i + 1,  5); changed += ImGui::FastDragValue(&av->v);				ImGui::SameLine();
		fa.SetPosLeft(i + 1,  6); changed += ImGui::FastDragValue(&av->boneindex0);		ImGui::SameLine();
		fa.SetPosLeft(i + 1,  7); changed += ImGui::FastDragValue(&av->boneindex1);		ImGui::SameLine();
		fa.SetPosLeft(i + 1,  8); changed += ImGui::FastDragValue(&av->boneindex2);		ImGui::SameLine();
		fa.SetPosLeft(i + 1,  9); changed += ImGui::FastDragValue(&av->boneindex3);		ImGui::SameLine();
		fa.SetPosLeft(i + 1, 10); changed += ImGui::FastDragValue(&av->boneweight0);	ImGui::SameLine();
		fa.SetPosLeft(i + 1, 11); changed += ImGui::FastDragValue(&av->boneweight1);	ImGui::SameLine();
		fa.SetPosLeft(i + 1, 12); changed += ImGui::FastDragValue(&av->boneweight2);	ImGui::SameLine();
		fa.SetPosLeft(i + 1, 13); changed += ImGui::FastDragValue(&av->boneweight3);	//ImGui::SameLine();
		if (changed) {
			UploadVerticesToGPU();
		}
#else
		ImGui::Text("TEEEST %d", i);
#endif
	//}
	}
	//ImGui::SetCursorPosY(lines_height * numberOfVertices);
	ImGui::Text("fooo");

	clipper.End();
	ImGui::PopItemWidth();
}

void OpAxis::Init() {


	Op::Init();
	

	//model = new Model("pCube1");
	model = new Model("Maila_BodyComplete");

	

	model->GenerateMergedData();
	model->UploadToGPU();



	number_of_inputs = 6;
	InitLink(0, "prog", OP_TYPE_PROGRAM);
	InitLink(1, "matrix", OP_TYPE_MATRIX);
	InitLink(2, "drawcount", OP_TYPE_FLOAT);
	InitLink(3, "matrices", OP_TYPE_CUSTOMCLASS);
	InitLink(4, "tex", OP_TYPE_GLBUFFER);
	InitLink(5, "OpNode", OP_TYPE_CUSTOMCLASS); // OP_TYPE_OP maybe? so I just want the op... need just the hierarchy from OpNode
	number_of_outputs = 2;
	InitLinkOutput(0, "vertexbuffer", OP_TYPE_GLBUFFER);
	InitLinkOutput(1, "indexbuffer", OP_TYPE_GLBUFFER);




	shallDrawInScene = 1;
}

void OpAxis::Render() {
	Op::PreRender();
	ImGui::SetCursorPos(pos);


// fuck of, why i even care
// this little fuck shit burns time and its somewhat useless nonetheless

//ImGui::BeginChild("Sub1",size, false, ImGuiWindowFlags_HorizontalScrollbar);
//int lines_count = 500;
//float lines_height = ImGui::GetTextLineHeightWithSpacing(); // 20.0f;
//ImGui::Text("foooo a");
//ImGui::Text("foooo b");
////ImGuiListClipper clipper(lines_count, lines_height);
////for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
////{
////ImGui::Text("%04d: clipper", i);
////}
////clipper.End();
//model->ImGuiEditor(ImVec2(0,0), size);
//ImGui::Text("foooo a");
//ImGui::Text("foooo b");
//for (int i = 0; i < 100; i++)
//{
////ImGui::Text("%04d: scrollable region", i);
////if (goto_line && line == i)
////    ImGui::SetScrollHere();
//}
////if (goto_line && line >= 100)
////    ImGui::SetScrollHere();
//ImGui::EndChild();


	Op::PostRender();
}

void OpAxis::Update() {
}

#include "../ops/op_node.h"

NodeForOp **nodes = NULL;
glm::vec4 pos4;

glm::vec3 CalcBoneInfluence(int boneindex, float boneweight) {
	return (nodes[boneindex]->localToWorld * pos4) * boneweight;
}

void OpAxis::RenderEditor() {
	Op::RenderEditor();
	
	if (model) {
		ImGui::Text("highestBoneID: %d", model->highestBoneID);
	}

	
	if (ImGui::Button("Align Vertices to Bones")) {
		imgui_log("Owner: %s", default_link_inputs[5].cached_backlinks->back()->owner->name);
		
		OpNode *opnode = (OpNode *)default_link_inputs[5].cached_backlinks->back()->owner;
		nodes = opnode->nodes;
		NodeForOp *rootnode = opnode->node->childs[0];
		imgui_log("rootnode: %s\n", rootnode->name);

		
		float *vertices = (float *)model->bufferVertices.data;

		for (int i=0; i<model->numberOfVertices; i++) {
		
		
			axisvertex_t *av = model->axisvertices + i;
			
			float x = vertices[i*3 + 0];
			float y = vertices[i*3 + 1];
			float z = vertices[i*3 + 2];
			pos4 = glm::vec4(x, y, z, 1.0f);

			glm::vec3 pos = glm::vec3(0,0,0);
			if (av->boneweight0 != 0) { pos += CalcBoneInfluence(av->boneindex0, av->boneweight0); }
			if (av->boneweight1 != 0) { pos += CalcBoneInfluence(av->boneindex1, av->boneweight1); }
			if (av->boneweight2 != 0) { pos += CalcBoneInfluence(av->boneindex2, av->boneweight2); }
			if (av->boneweight3 != 0) { pos += CalcBoneInfluence(av->boneindex3, av->boneweight3); }

			
			av->x = pos.x;
			av->y = pos.y;
			av->z = pos.z;
		//fa.SetPosLeft(i + 1,  0); changed += ImGui::FastDragValue(&av->vertexid);		ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  1); changed += ImGui::FastDragValue(&av->x);				ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  2); changed += ImGui::FastDragValue(&av->y);				ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  3); changed += ImGui::FastDragValue(&av->z);				ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  4); changed += ImGui::FastDragValue(&av->u);				ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  5); changed += ImGui::FastDragValue(&av->v);				ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  6); changed += ImGui::FastDragValue(&av->boneindex0);		ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  7); changed += ImGui::FastDragValue(&av->boneindex1);		ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  8); changed += ImGui::FastDragValue(&av->boneindex2);		ImGui::SameLine();
		//fa.SetPosLeft(i + 1,  9); changed += ImGui::FastDragValue(&av->boneindex3);		ImGui::SameLine();
		//fa.SetPosLeft(i + 1, 10); changed += ImGui::FastDragValue(&av->boneweight0);	ImGui::SameLine();
		//fa.SetPosLeft(i + 1, 11); changed += ImGui::FastDragValue(&av->boneweight1);	ImGui::SameLine();
		//fa.SetPosLeft(i + 1, 12); changed += ImGui::FastDragValue(&av->boneweight2);	ImGui::SameLine();
		//fa.SetPosLeft(i + 1, 13); changed += ImGui::FastDragValue(&av->boneweight3);	//ImGui::SameLine();
		}
		model->UploadVerticesToGPU();

		imgui_log("asd\n");
	}

}

std::string OpAxis::WriteExtraData() {
	//fprintf(f, "x %f y %f z %f n %f",
	//	op->x,
	//	op->y,
	//	op->z,
	//	op->n
	//);
	return std::string("");
}

void OpAxis::ReadExtraData(char *line) {
	//sscanf(line, "x %f y %f z %f n %f",
	//	&op->x,
	//	&op->y,
	//	&op->z,
	//	&op->n
	//);
}



extern "C" {
	//#include <sys\sys_local.h>
	void renderer_get_mvp(float *out_mvp);
}
#include "op_matrices.h"

void OpAxis::DrawInScene() {
#if 0
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
	//glGetError(); // ignore errors before this function
	//checkerror("", __FILE__, __LINE__);

	qglUseProgram(prog);
	model->MakeVAO(prog);
	int u_matrix = qglGetUniformLocation(prog, "u_matrix");
	int u_time = qglGetUniformLocation(prog, "u_time");
	int u_bindposes = qglGetUniformLocation(prog, "u_bindposes");
	int u_texture = qglGetUniformLocation(prog, "u_texture");
	if (u_matrix != -1) {
		//float hurr[16];
		//renderer_get_mvp(hurr);
		qglUniformMatrix4fv(u_matrix, 1, GL_FALSE, inputmatrix);
		qglUniform1f(u_time, (float)Sys_Milliseconds());

		void *cc = default_link_inputs[3].customclass;
		if (cc) {
			ArrayOfMatrices *matrices = (ArrayOfMatrices *)cc;

			//for (int i=0; i<80; i++) {
			//	float *mat = matrices->matrices + i * 16; // * sizeof(float);
			//	mat_identity(mat);
			//}
			

			qglUniformMatrix4fv(u_bindposes, 80, GL_FALSE, (float *)matrices->matrices);
		}
	}
	//textureid = 1;
	//qglActiveTexture(GL_TEXTURE0);
	qglBindTexture(GL_TEXTURE_2D, tex);
	qglUniform1i(u_texture, 0);
	qglBindVertexArray(model->vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//drawcount = model->numberOfTriangles * 3;
	//glDrawElements(GL_LINES, /*138 * 3*/drawcount, GL_UNSIGNED_INT, 0);
	qglEnable(GL_CULL_FACE);
	qglEnable(GL_DEPTH_TEST);
	qglCullFace(GL_FRONT);
	qglDrawElements(GL_TRIANGLES, /*138 * 3*/drawcount, GL_UNSIGNED_INT, 0);
	qglBindVertexArray(0);
#endif
}

OpAxis::OpAxis() {
	Init();
}

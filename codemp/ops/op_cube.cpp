//#include "craftstructs.h"
#include "../include_gl.h"
#include "../include_imgui.h"

//#include "imgui_impl_glfw.h"
#include <stdio.h>
//#include "libs\glfw\include\GLFW/glfw3.h"
#include <list>

#include "op.h"
#include "op_cube.h"

#include "../include_console.h"
#include "../include_glm.h"
#include "../rd-rend2/primitives_3d.h"

//float javascript_viewmatrix[16] = {0};
/*
buf = new Int32Array(16);
for (var i=0; i<16; i++)
buf[i] = i*i;
set_viewmatrix(buf)


memory_read_int(328846048 + 4*5)	

set_viewmatrix([1,2,3,4,5,6,7,8,9,10,11])

*/
// http://wiki.duktape.org/HowtoBuffers.html

//int duk_func_set_viewmatrix       (duk_context *ctx) {
//	unsigned int size;
//	struct duk_hbufferobject *buf;
//	buf = duk_to_buffer_kung(ctx, 0, &size, DUK_BUF_MODE_DONTCARE);













void OpCube::Init() {

	Op::Init();
	strcpy( name, "OpCube" );
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
	number_of_outputs = 0;
	InitLinkOutput(0, "Buffer", OP_TYPE_GLBUFFER);

	// first i will call: new Float32Array(1024)
	// Then I will increase the refcounter for that object, so Duktape won't render the memory location useless
	// Then I put that the variable name into MeshEditor, so i can modify float* pointer
	//mesh = new Mesh();

	ResizeMinimal();
	type             = OpType::OP_TYPE_REQUESTER;
	
    qglGenBuffers(1, &default_link_outputs[0].opengl_id);
	shallDrawInScene = 1;
}

void OpCube::Render() {
	Op::PreRender();
	
	//ImGui::SetCursorPos(pos);
	//ImGui::Image((ImTextureID)textureid, size/* + ImVec2(-20,-20)*/);
	//
	//ImGui::SetCursorPos(pos + ImVec2(5,5));
	//ImGui::Text("Checkboard texid=%d", textureid);

	Op::PostRender();
}


void OpCube::Update() {



	if ( ! forcereload)
		return;

	//log("OPOPOPOP Update cube %d forcereload=%d\n", op, forcereload);
	//mesh->x = x;
	//mesh->y = y;
	//mesh->z = z;
	//mesh->n = n;
	//mesh->init(); // todo: need a way to just update data without making new buffer
	//make_cube_wireframe(data, x, y, z, n);

	auto mat = glm::make_mat4x4(default_link_inputs[0].matrix);

	kung_cube(data, x, y, z, mat);
	//buffer = gen_buffer(sizeof(data), data);


	
	qglBindBuffer(GL_ARRAY_BUFFER, default_link_outputs[0].opengl_id);
	qglBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);
	qglBindBuffer(GL_ARRAY_BUFFER, 0);



	//glBindBuffer(GL_ARRAY_BUFFER, default_link_outputs[1].opengl_id);
	//glBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);



	default_link_outputs[0].changed++;
}

void OpCube::RenderEditor() {
	Op::RenderEditor();


	//if (ImGui::Button("do shit") ) {
	//
	//
	//	duk_push_global_object(ctx);
	//	int ret = duk_get_prop_string(ctx, -1, "test");
	//	imgui_log("ret: %d", ret);
	//
	//	unsigned int size;
	//	struct duk_hbufferobject *buf;
	//	if (ret) {
	//		//buf = duk_to_buffer_kung(ctx, -1, &size, DUK_BUF_MODE_DONTCARE);
	//		//
	//		////memcpy(javascript_viewmatrix, (void *)( ((int)buf->buf) + 20 ), 16 * 4);
	//		//float *arr = (float *)( ((int)buf->buf) + 20  );
	//		////duk_hbuffer *hbuf = buf->buf;
	//		//log("buf = %d size=%d %.2f %.2f %.2f off=%d llen=%d\n", buf, size, arr[0], arr[1], arr[2], buf->offset, buf->length);
	//	} else {
	//		//log("value does not exist\n");
	//	}
	//	duk_pop(ctx); // pop the getpropstring
	//	
	//}

	//ImGui::Text("address: %x", checkImage);
	//ImGui::Text("textureid: %x", textureid);
}

std::string OpCube::WriteExtraData() {
	char buf[1024];
	snprintf(buf, sizeof buf, "x %f y %f z %f n %f",
		x,
		y,
		z,
		n
	);
	return std::string(buf);
}

void OpCube::ReadExtraData(char *line) {
	sscanf(line, "x %f y %f z %f n %f",
		&x,
		&y,
		&z,
		&n
	);
}

//#include "main_shaders.h"
/*
	program = load_program(
		"shaders/line2_vertex.glsl", "shaders/line2_fragment.glsl");
	line2_attrib.program = program;
	line2_attrib.position = glGetAttribLocation(program, "position");
	line2_attrib.color = glGetAttribLocation(program, "attr_color");
	line2_attrib.matrix = glGetUniformLocation(program, "matrix");
*/
extern "C" float player_matrix[16];

void OpCube::DrawInScene() {
	return;
#if 0
/*
	InitLink(0, "BufPos", OP_TYPE_GLBUFFER );
	InitLink(1, "BufCol", OP_TYPE_GLBUFFER );
	InitLink(2, "AttPos", OP_TYPE_GLATTRIB );
	InitLink(3, "AttCol", OP_TYPE_GLATTRIB );
	InitLink(4, "Mat", OP_TYPE_MATRIX );
	InitLink(5, "Prog", OP_TYPE_PROGRAM );
	InitLink(6, "UniMat", OP_TYPE_GLUNIFORM );
	InitLink(7, "count", OP_TYPE_FLOAT ); // meh, normally int, but atm everything just works with floats... might change late or kick out int at all
	InitLink(8, "drawmode", OP_TYPE_GLDRAWMODE );
*/

				// is set by update();
				GLuint vertices = default_link_outputs[0].opengl_id;
				
				//Attrib *a = &line2_attrib;
				Attrib *a = NULL;

				

				qglUseProgram(a->program);

				

				qglUniformMatrix4fv(a->matrix, 1, GL_FALSE, player_matrix);


				qglBindBuffer(GL_ARRAY_BUFFER, vertices);
				qglVertexAttribPointer(a->position, /*components*/3, GL_FLOAT, GL_FALSE, 0, 0); // https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object
				qglEnableVertexAttribArray(a->position);
	
				qglBindBuffer(GL_ARRAY_BUFFER, vertices); // vertices as color...
				qglVertexAttribPointer(a->color, /*components*/4, GL_FLOAT, GL_TRUE, 0, 0);
				qglEnableVertexAttribArray(a->color);
	
				//glDrawArrays((int)default_link_inputs[8].val_f, 0, /*count*/(int)default_link_inputs[7].val_f);
				qglDrawArrays((int)default_link_inputs[8].val_f, 0, /*count*/36);
				qglDisableVertexAttribArray(a->color);
				qglDisableVertexAttribArray(a->position);

	qglBindBuffer(GL_ARRAY_BUFFER, 0);
	qglUseProgram(0);
#endif
}

OpCube::OpCube() {
	Init();
}
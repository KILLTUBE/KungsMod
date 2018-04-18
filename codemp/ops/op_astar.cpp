#include "../include_gl.h"
#include <stdio.h>
#include <list>
#include "op.h"
#include "op_astar.h"
#include "../include_glm.h"
#include "../rd-rend2/primitives_3d.h"
#include "rd-rend2/matrix.h"

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


OpAStar::OpAStar() {
	Init();
}

void OpAStar::AddNode(float x, float y, float z) {
	auto node = new AstarNode();
	node->x = x;
	node->y = y;
	node->z = z;
	
    qglGenBuffers(1, &node->buffer);

	float mat[16];
	mat_identity(mat);
	
	float t_pos[16];
	float scale[16];
	float t_center[16];
	
	mat_scale(scale, 0.25f, 0.25f, 0.25f);
	mat_translate(t_pos, x, y, z);
	mat_translate(t_center, -0.5f, -0.5f, -0.5f);

	// first we scale it down to 1/4 cube size
	mat_multiply(mat, scale, mat);
	// then we center it
	mat_multiply(mat, t_center, mat);
	// and then we set it to the correct position in scene
	mat_multiply(mat, t_pos, mat);



	kung_cube(node->data, 0,0,0, glm::make_mat4(mat));
	//buffer = gen_buffer(sizeof(data), data);



    qglBindBuffer(GL_ARRAY_BUFFER, node->buffer);
    qglBufferData(GL_ARRAY_BUFFER, sizeof node->data, node->data, GL_STATIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

	nodes.push_back(node);

	isAstar = 1;
}


void OpAStar::Init() {

	Op::Init();
	strcpy( name, "OpAStar");
	size = ImVec2(256, 256);
	pos = ImVec2(250, 250);
	
	number_of_inputs = 1;
	InitLink(0, "Matrix", OP_TYPE_MATRIX );
	number_of_outputs = 0;
	InitLinkOutput(0, "Buffer", OP_TYPE_GLBUFFER);

	// first i will call: new Float32Array(1024)
	// Then I will increase the refcounter for that object, so Duktape won't render the memory location useless
	// Then I put that the variable name into MeshEditor, so i can modify float* pointer
	//mesh = new Mesh();

	ResizeMinimal();
	type = OpType::OP_TYPE_REQUESTER;
	
    qglGenBuffers(1, &default_link_outputs[0].opengl_id);
}

void OpAStar::Render() {
	Op:PreRender();
	
	//ImGui::SetCursorPos(op->pos);
	//ImGui::Image((ImTextureID)op->textureid, op->size/* + ImVec2(-20,-20)*/);
	//
	//ImGui::SetCursorPos(op->pos + ImVec2(5,5));
	//ImGui::Text("Checkboard texid=%d", op->textureid);

	Op::PostRender();
}

void OpAStar::Update() {



	if ( ! forcereload)
		return;

	//log("OPOPOPOP Update cube %d forcereload=%d\n", op, op->forcereload);
	//op->mesh->x = op->x;
	//op->mesh->y = op->y;
	//op->mesh->z = op->z;
	//op->mesh->n = op->n;
	//op->mesh->init(); // todo: need a way to just update data without making new buffer
	//make_cube_wireframe(op->data, op->x, op->y, op->z, op->n);

	auto mat = glm::make_mat4x4(default_link_inputs[0].matrix);

	kung_cube(data, x, y, z, mat);
	//buffer = gen_buffer(sizeof(data), data);



    qglBindBuffer(GL_ARRAY_BUFFER, default_link_outputs[0].opengl_id);
    qglBufferData(GL_ARRAY_BUFFER, sizeof data, data, GL_STATIC_DRAW);
    qglBindBuffer(GL_ARRAY_BUFFER, 0);
	default_link_outputs[0].changed++;
}

void OpAStar::RenderEditor() {
	Op::RenderEditor();

	static float x, y, z;
	ImGui::DragFloat("x", &x);
	ImGui::DragFloat("y", &y);
	ImGui::DragFloat("z", &z);
	if (ImGui::Button("add node") ) {
		AddNode(x, y, z);

		
	}
	int i=0;
	for (auto node : nodes) {
		ImGui::Text("node[%d] x=%.2f y=%.2f z=%.2f", i, node->x, node->y, node->z);
		i++;
	}


	//ImGui::Text("address: %x", op->checkImage);
	//ImGui::Text("textureid: %x", op->textureid);
}


std::string OpAStar::WriteExtraData() {
	char buf[128];
	snprintf(buf, sizeof buf, "x %f y %f z %f n %f",
		x,
		y,
		z,
		n
	);
	return std::string(buf);
}

void OpAStar::ReadExtraData(char *line) {
	sscanf(line, "x %f y %f z %f n %f",
		&x,
		&y,
		&z,
		&n
	);
}
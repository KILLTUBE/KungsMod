#include "op.h"
#include "op_matrix_shear.h"

#include "rd-rend2/matrix.h"

void OpMatrixShear::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	
	InitLink(0, "a", OP_TYPE_FLOAT);
	InitLink(1, "b", OP_TYPE_FLOAT);
	InitLink(2, "c", OP_TYPE_FLOAT);
	InitLink(3, "d", OP_TYPE_FLOAT);
	InitLink(4, "e", OP_TYPE_FLOAT);
	InitLink(5, "f", OP_TYPE_FLOAT);
	InitLinkOutput(0, "Matrix", OP_TYPE_MATRIX);
	number_of_inputs = 6;
	number_of_outputs = 1;
	ResizeMinimal();
}

void OpMatrixShear::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void mat_shear(float *m, float a, float b, float c, float d, float e, float f) {

    m[0] = 1; m[4] = a; m[ 8] = b; m[12] = 0;
    m[1] = c; m[5] = 1; m[ 9] = d; m[13] = 0;
    m[2] = e; m[6] = f; m[10] = 1; m[14] = 0;
    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;

	// http://stackoverflow.com/questions/12537141/how-to-shear-a-cube-in-three-js
	//matrix.set(   1,   Syx,  Szx,  0,
    //        Sxy,     1,  Szy,  0,
    //        Sxz,   Syz,   1,   0,
    //          0,     0,   0,   1  );
}

void OpMatrixShear::Update() {
	if ( ! forcereload)
		return;
	mat_shear(default_link_outputs[0].matrix, a, b, c, d, e, f);
	default_link_outputs[0].changed++;
}

void OpMatrixShear::RenderEditor() {
	Op::RenderEditor();
}

OpMatrixShear::OpMatrixShear() {
	Init();
}
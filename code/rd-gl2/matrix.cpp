#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
//#include "config.h"
#include "matrix.h"
//#include "util.h"

//#include <kung/opsys/op_all.h>
//#include <kung/include_duktape.h>

void normalize(float *x, float *y, float *z) {
    float d = sqrtf((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
    *x /= d; *y /= d; *z /= d;
}

void mat_identity(float *m) {
    m[0] = 1; m[4] = 0; m[ 8] = 0; m[12] = 0;
    m[1] = 0; m[5] = 1; m[ 9] = 0; m[13] = 0;
    m[2] = 0; m[6] = 0; m[10] = 1; m[14] = 0;
    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
}

void mat_translate(float *m, float tx, float ty, float tz) {
    m[0] = 1; m[4] = 0; m[ 8] = 0; m[12] = tx;
    m[1] = 0; m[5] = 1; m[ 9] = 0; m[13] = ty;
    m[2] = 0; m[6] = 0; m[10] = 1; m[14] = tz;
    m[3] = 0; m[7] = 0; m[11] = 0; m[15] =  1;
}
void mat_scale(float *m, float sx, float sy, float sz) {
    m[0] = sx; m[4] =  0; m[ 8] =  0; m[12] = 0;
    m[1] =  0; m[5] = sy; m[ 9] =  0; m[13] = 0;
    m[2] =  0; m[6] =  0; m[10] = sz; m[14] = 0;
    m[3] =  0; m[7] =  0; m[11] =  0; m[15] = 1;
}

void mat_rotate(float *matrix, float x, float y, float z, float angle) {
    normalize(&x, &y, &z);
    float s = sinf(angle);
    float c = cosf(angle);
    float m = 1 - c;
    matrix[0] = m * x * x + c;
    matrix[1] = m * x * y - z * s;
    matrix[2] = m * z * x + y * s;
    matrix[3] = 0;
    matrix[4] = m * x * y + z * s;
    matrix[5] = m * y * y + c;
    matrix[6] = m * y * z - x * s;
    matrix[7] = 0;
    matrix[8] = m * z * x - y * s;
    matrix[9] = m * y * z + x * s;
    matrix[10] = m * z * z + c;
    matrix[11] = 0;
    matrix[12] = 0;
    matrix[13] = 0;
    matrix[14] = 0;
    matrix[15] = 1;
}

void mat_vec_multiply(float *vector, float *a, float *b) {
    float result[4];
    for (int i = 0; i < 4; i++) {
        float total = 0;
        for (int j = 0; j < 4; j++) {
            int p = j * 4 + i;
            int q = j;
            total += a[p] * b[q];
        }
        result[i] = total;
    }
    for (int i = 0; i < 4; i++) {
        vector[i] = result[i];
    }
}

void mat_multiply(float *matrix, float *a, float *b) {
    float result[16];
    for (int c = 0; c < 4; c++) {
        for (int r = 0; r < 4; r++) {
            int index = c * 4 + r;
            float total = 0;
            for (int i = 0; i < 4; i++) {
                int p = i * 4 + r;
                int q = c * 4 + i;
                total += a[p] * b[q];
            }
            result[index] = total;
        }
    }
    for (int i = 0; i < 16; i++) {
        matrix[i] = result[i];
    }
}

void mat_apply(float *data, float *matrix, int count, int offset, int stride) {
    float vec[4] = {0, 0, 0, 1};
    for (int i = 0; i < count; i++) {
        float *d = data + offset + stride * i;
        vec[0] = *(d++); vec[1] = *(d++); vec[2] = *(d++);
        mat_vec_multiply(vec, matrix, vec);
        d = data + offset + stride * i;
        *(d++) = vec[0]; *(d++) = vec[1]; *(d++) = vec[2];
    }
}

void frustum_planes(float planes[6][4], int radius, float *matrix) {
    float znear = 0.125;
    float zfar = radius * 32 + 64;
    float *m = matrix;
    planes[0][0] = m[3] + m[0];
    planes[0][1] = m[7] + m[4];
    planes[0][2] = m[11] + m[8];
    planes[0][3] = m[15] + m[12];
    planes[1][0] = m[3] - m[0];
    planes[1][1] = m[7] - m[4];
    planes[1][2] = m[11] - m[8];
    planes[1][3] = m[15] - m[12];
    planes[2][0] = m[3] + m[1];
    planes[2][1] = m[7] + m[5];
    planes[2][2] = m[11] + m[9];
    planes[2][3] = m[15] + m[13];
    planes[3][0] = m[3] - m[1];
    planes[3][1] = m[7] - m[5];
    planes[3][2] = m[11] - m[9];
    planes[3][3] = m[15] - m[13];
    planes[4][0] = znear * m[3] + m[2];
    planes[4][1] = znear * m[7] + m[6];
    planes[4][2] = znear * m[11] + m[10];
    planes[4][3] = znear * m[15] + m[14];
    planes[5][0] = zfar * m[3] - m[2];
    planes[5][1] = zfar * m[7] - m[6];
    planes[5][2] = zfar * m[11] - m[10];
    planes[5][3] = zfar * m[15] - m[14];
}

void mat_frustum(
    float *matrix, float left, float right, float bottom,
    float top, float znear, float zfar)
{
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}

void mat_perspective(
    float *matrix, float fov, float aspect,
    float znear, float zfar)
{
    float ymax, xmax;
    ymax = znear * tanf(fov * M_PI / 360.0);
    xmax = ymax * aspect;
    mat_frustum(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

void mat_ortho(
    float *matrix,
    float left, float right, float bottom, float top, float znear, float zfar)
{
    matrix[0] = 2 / (right - left);
    matrix[1] = 0;
    matrix[2] = 0;
    matrix[3] = 0;
    matrix[4] = 0;
    matrix[5] = 2 / (top - bottom);
    matrix[6] = 0;
    matrix[7] = 0;
    matrix[8] = 0;
    matrix[9] = 0;
    matrix[10] = -2 / (zfar - znear);
    matrix[11] = 0;
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(zfar + znear) / (zfar - znear);
    matrix[15] = 1;
}

void set_matrix_2d(float *matrix, int width, int height) {
    mat_ortho(matrix, 0, width, 0, height, -1, 1);
}

void matcpy(float *dst, float *src) {
	memcpy((void *)dst, (void *)src, 16 * 4);
}


void set_matrix_3d(
    float *matrix, int width, int height,
    float x, float y, float z, float rx, float ry,
    float fov, int ortho, int radius)
{
    float a[16];
    float b[16];
    float aspect = (float)width / height;
    float znear = 0.125;
    float zfar = radius * 32 + 64;
    mat_identity(a);
    mat_translate(b, -x, -y, -z);
    mat_multiply(a, b, a);
    mat_rotate(b, cosf(rx), 0, sinf(rx), ry);
    mat_multiply(a, b, a);
    mat_rotate(b, 0, 1, 0, -rx);
    mat_multiply(a, b, a);
    if (ortho) {
        int size = ortho;
        mat_ortho(b, -size * aspect, size * aspect, -size, size, -zfar, zfar);
    }
    else {
        mat_perspective(b, fov, aspect, znear, zfar);
    }
    mat_multiply(a, b, a);
    mat_identity(matrix);
    mat_multiply(matrix, a, matrix);
}

//void set_matrix_3d_opsystem(
//    float *matrix, int width, int height,
//    float x, float y, float z, float rx, float ry,
//    float fov, int ortho, int radius)
//{
//	static int first = 1;
//	
//	static OpMatrix *ortho_result;
//	//static OpValue *ortho_width  ;
//	//static OpValue *ortho_height ;
//	//static OpValue *ortho_x      ;
//	//static OpValue *ortho_y      ;
//	//static OpValue *ortho_z      ;
//	//static OpValue *ortho_rx     ;
//	//static OpValue *ortho_ry     ;
//	//static OpValue *ortho_fov    ;
//	//static OpValue *ortho_ortho  ;
//	//static OpValue *ortho_radius ;
//
//		duk_push_global_object(ctx);
//		duk_push_number(ctx, (float)width);
//		duk_put_prop_string(ctx, -2, "width");
//		duk_push_number(ctx, (float)height);
//		duk_put_prop_string(ctx, -2, "height");
//		duk_push_number(ctx, (float)x);
//		duk_put_prop_string(ctx, -2, "x");
//		duk_push_number(ctx, (float)y);
//		duk_put_prop_string(ctx, -2, "y");
//		duk_push_number(ctx, (float)z);
//		duk_put_prop_string(ctx, -2, "z");
//		duk_push_number(ctx, (float)rx);
//		duk_put_prop_string(ctx, -2, "rx");
//		duk_push_number(ctx, (float)ry);
//		duk_put_prop_string(ctx, -2, "ry");
//		duk_push_number(ctx, (float)fov);
//		duk_put_prop_string(ctx, -2, "fov");
//		duk_push_number(ctx, (float)ortho);
//		duk_put_prop_string(ctx, -2, "ortho");
//		duk_push_number(ctx, (float)radius);
//		duk_put_prop_string(ctx, -2, "radius");
//		duk_pop(ctx);
//
//	if (first) {
//		//
//		//
//		//
//		OpSystem *sys_ortho = new OpSystem("ortho.txt", 0);
//		//	// add all values
//		ortho_result = sys_ortho->createMatrix("ret"  , 1);
//		ortho_result->type = OP_TYPE_REQUESTER;
//		//	ortho_width  = sys_ortho->createValue("width"  , 1);
//		//	ortho_height = sys_ortho->createValue("height" , 1);
//		//	ortho_x      = sys_ortho->createValue("x"      , 1);
//		//	ortho_y      = sys_ortho->createValue("y"      , 1);
//		//	ortho_z      = sys_ortho->createValue("z"      , 1);
//		//	ortho_rx     = sys_ortho->createValue("rx"     , 1);
//		//	ortho_ry     = sys_ortho->createValue("ry"     , 1);
//		//	ortho_fov    = sys_ortho->createValue("fov"    , 1);
//		//	ortho_ortho  = sys_ortho->createValue("ortho"  , 1);
//		//	ortho_radius = sys_ortho->createValue("radius" , 1);
//		//	//log("number of ops: %d", sys_ortho->all.size());
//		//
//		//	// load the system
//		OpSystem::SetCurrent(sys_ortho); // otherwise op_from_string uses the wrong system to check if a op is already added
//		sys_ortho->loadFile(sys_ortho->name);
//		//	//log("number of ops: %d", sys_ortho->all.size());
//		//
//		sys_ortho->regenerateCallGraphs();
//		//OpSystem::SetCurrent(&perm);
//		first = 0;
//	}
//	//ortho_width  ->val = (float)width;
//	//ortho_height ->val = (float)height;
//	//ortho_x      ->val = x;
//	//ortho_y      ->val = y;
//	//ortho_z      ->val = z;
//	//ortho_rx     ->val = rx;
//	//ortho_ry     ->val = ry;
//	//ortho_fov    ->val = fov;
//	//ortho_ortho  ->val = (float)ortho;
//	//ortho_radius ->val = (float)radius;
//
//
//    float a[16];
//    float b[16];
//    float aspect = (float)width / height;
//    float znear = 0.125;
//    float zfar = radius * 32 + 64;
//    mat_identity(a);
//    mat_translate(b, -x, -y, -z);
//    mat_multiply(a, b, a);
//    mat_rotate(b, cosf(rx), 0, sinf(rx), ry);
//    mat_multiply(a, b, a);
//    mat_rotate(b, 0, 1, 0, -rx);
//    //mat_multiply(a, b, a);
//
//
//
//	//if (ortho) {
//	//int size = ortho;
//	//int size = 64;
//	//craft_ortho->left = -size * aspect;
//	//craft_ortho->right = size * aspect;
//	//craft_ortho->bottom = -size;
//	//craft_ortho->top = size;
//	//craft_ortho->znear = -zfar;
//	//craft_ortho->zfar = zfar;
//
//	//craft_perspective->fov = fov;
//	//craft_perspective->aspect = aspect;
//	//craft_perspective->znear = znear;
//	//craft_perspective->zfar = zfar;
//	//craft_perspective->update(craft_perspective);
//	
//
//	if ( ! ortho) {
//		craft_matrix_persp->Request();
//		matcpy(matrix, craft_matrix_persp->matrix);
//	} else {
//		ortho_result->Request();
//		matcpy(matrix, ortho_result->matrix);
//	}
//}

void set_matrix_item(float *matrix, int width, int height, int scale) {
    float a[16];
    float b[16];
    float aspect = (float)width / height;
    float size = 64 * scale;
    float box = height / size / 2;
    float xoffset = 1 - size / width * 2;
    float yoffset = 1 - size / height * 2;
    mat_identity(a);
    mat_rotate(b, 0, 1, 0, -M_PI / 4);
    mat_multiply(a, b, a);
    mat_rotate(b, 1, 0, 0, -M_PI / 10);
    mat_multiply(a, b, a);
    mat_ortho(b, -box * aspect, box * aspect, -box, box, -1, 1);
    mat_multiply(a, b, a);
    mat_translate(b, -xoffset, -yoffset, 0);
    mat_multiply(a, b, a);
    mat_identity(matrix);
    mat_multiply(matrix, a, matrix);
}

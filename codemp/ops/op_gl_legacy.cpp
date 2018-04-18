#include "../include_gl.h"

#include "op.h"
#include "op_gl_legacy.h"


#include "rd-rend2/matrix.h"
/**/

extern float player_matrix[16];
//extern Player *player;
//extern State *s;


static void CameraFPSQuaternion_UpdateView(float pitch, float yaw, float roll, glm::vec3 eye)
{


	// * 57.2958f
  //FPS camera:  RotationX(pitch) * RotationY(yaw)
  glm::quat qPitch = glm::angleAxis(pitch , glm::vec3(1, 0, 0));
  glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
  glm::quat qRoll = glm::angleAxis(roll,glm::vec3(0,0,1));  
 
  //For a FPS camera we can omit roll
  glm::quat orientation = qPitch * qYaw;
  orientation = glm::normalize(orientation);
  glm::mat4 rotate = glm::mat4_cast(orientation);
 
  glm::mat4 translate = glm::mat4(1.0f);
  translate = glm::translate(translate, -eye);
 
  auto viewMatrix = rotate * translate;


	//glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	//glLoadMatrixf(glm::value_ptr(viewMatrix));
}

static GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
#if 0
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	//glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	//// Calculate The Aspect Ratio Of The Window
	//gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

		// Calculate The Aspect Ratio Of The Window
		///gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
		// The following code is a fancy bit of math that is eqivilant to calling:
		// gluPerspective( fieldOfView/2.0f, width/height , 0.1f, 255.0f )
		// We do it this way simply to avoid requiring glu.h
		GLfloat zNear = 0.1f;
		GLfloat zFar = 255.0f;
		GLfloat aspect = float(width)/float(height);
		GLfloat fH = tan( float(45.0f/ 360.0f * 3.14159f) ) * zNear;
		GLfloat fW = fH * aspect;
		//glFrustum( -fW, fW, -fH, fH, zNear, zFar );




	//glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	//glLoadIdentity();									// Reset The Modelview Matrix
	
	//glLoadMatrixf(player_matrix);


	
	//set_matrix_3d(player_matrix, g->width, g->height, s->x, s->y, s->z, s->rx, s->ry, g->fov, g->ortho, g->render_radius);
	float x = s->x;
	float y = s->y;
	float z = s->z;
	float rx = s->ry;
	float ry = s->ry;
	float matrix[16];

	float radius = 10;
	float fov = 65;
	float a[16];
	float b[16];
	aspect = (float)g->width / (float)g->height;
	float znear = 0.00125;
	float zfar = radius * 32 + 64;


	mat_identity(a);

	// translation
	mat_translate(b, x, y, z);
	mat_multiply(a, b, a);

	
	//mat_rotate(b, 0, 1, 0, -rx);
	//mat_multiply(a, b, a);

	//mat_rotate(b, cosf(rx), 0, sinf(rx), ry);
	//mat_multiply(a, b, a);
	//mat_rotate(b, 0, 1, 0, -rx);
	//mat_multiply(a, b, a);
	
	float persp[16];
	mat_perspective(persp, fov, aspect, znear, zfar);

	//mat_multiply(a, b, a);
	//mat_identity(matrix);
	//mat_multiply(matrix, a, matrix);



		glMatrixMode(GL_PROJECTION);	
		glLoadMatrixf(persp);

		
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glLoadMatrixf(a);

		CameraFPSQuaternion_UpdateView(-rx, 0, -ry, glm::vec3(x,y,z));
#endif
}



static int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	// glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	// //glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	// //glClearDepth(1.0f);									// Depth Buffer Setup
	// //glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	// //glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	// glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return 1;										// Initialization Went OK
}

static int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	//glDisable(GL_DEPTH_TEST);
	//glLoadIdentity();									// Reset The Current Modelview Matrix
	//glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	// glBegin(GL_TRIANGLES);								// Drawing Using Triangles
	// 	glVertex3f( 0.0f, 1.0f + 2.0f, 0.0f);					// Top
	// 	glVertex3f(-1.0f,-1.0f + 2.0f, 0.0f);					// Bottom Left
	// 	glVertex3f( 1.0f,-1.0f + 2.0f, 0.0f);					// Bottom Right
	// glEnd();											// Finished Drawing The Triangle
	//glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
	//glBegin(GL_QUADS);									// Draw A Quad
	//	glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
	//	glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
	//	glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
	//	glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
	//glEnd();											// Done Drawing The Quad
	return 1;										// Keep Going
}



void OpGLLegacy::Init() {
	Op::Init();
	size = ImVec2(256, 256);
	pos = ImVec2(250, 300);
	strcpy( name, "OpGLLegacy" );
	
	number_of_inputs = 2;
	InitLink(0, "MatMV", OP_TYPE_MATRIX );
	InitLink(1, "MatP", OP_TYPE_MATRIX );
	number_of_outputs = 0;
	ResizeMinimal();
	isGLLegacy = 1;
}

void OpGLLegacy::Render() {
	Op::PreRender();
	
	Op::PostRender();
}

void OpGLLegacy::Update() {


}

extern float global_view_matrix[16];

void OpGLLegacy::RenderLegacyCode() {
	//if (cache_ingoing_connections == 0)
	//	return;
	//log("log: %s", default_link_inputs[0].val_str);

		qglUseProgram(0);
	InitGL();
	ReSizeGLScene(800, 600);



	// 	
	// glMatrixMode(GL_MODELVIEW);
	// if (0)
	// 	glLoadMatrixf(default_link_inputs[0].matrix);
	// else
	// 	glLoadMatrixf(global_view_matrix);
	// 	
	// 
	// glMatrixMode(GL_PROJECTION);	
	// glLoadMatrixf(default_link_inputs[1].matrix);
	// 
	// //glMatrixMode(GL_MODELVIEW);	
	// 
	// DrawGLScene();

}

void OpGLLegacy::RenderEditor() {
	Op::RenderEditor();

}

OpGLLegacy::OpGLLegacy() {
	Init();
}
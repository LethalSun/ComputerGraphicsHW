#include <windows.h>
#include <gl/glut.h>
#include <math.h>
#include <vector>
#include <string>
#include "loadpng.h"

GLfloat xRot = 0.f;
GLfloat yRot = 0.f;

GLuint ID_sun;
GLuint ID_earth;
GLuint ID_moon;

GLfloat Angle_sun = 0.f;
GLfloat Angle_Revolve = 0.f;
GLfloat Angle_earth = 0.f;
GLfloat Angle_moon = 0.f;

void SetupRC()
{
	GLfloat amb[] = { 0.5f,0.5f,0.5f };
	GLfloat diff[] = { 0.7f,0.7f,0.7f };
	GLfloat lightRange[] = { 0.f, 0.f, 100.f, 100.f };
	GLfloat lightPos[] = { 0.f, 0.f, -100.f, 1.f };
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void LoadTexture(GLuint* textureID, std::string fileName)
{
	std::vector<unsigned char>image;

	unsigned int width, height, error;

	error = lodepng::decode(image, width, height, fileName);

	if (error != 0)
	{
		printf("texture load failed");
		return;
	}

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat fAspect;

	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.f, fAspect, 1.f, 2000.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunc(int val)
{
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}

void ControlKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		yRot -= 5.f;

	if (key == GLUT_KEY_DOWN)
		yRot += 5.f;

	if (key == GLUT_KEY_LEFT)
		xRot -= 5.f;

	if (key == GLUT_KEY_RIGHT)
		xRot += 5.f;


	glutPostRedisplay();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, -200.f, -800.f);
	glRotatef(50, 1, 0, 0);

	glPushMatrix();
	glTranslatef(0.f, 0.f, xRot);
	glTranslatef(0.f, yRot, 0.f);

	//sun 

	glPushMatrix();

	//rotation
	glTranslatef(0.f, 0.f, -300.f);

	glRotatef(Angle_sun, 0.f, 1.f, 0.f);
	
	
	glColor3ub(255, 255, 255);

	glBindTexture(GL_TEXTURE_2D, ID_sun);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	
	GLUquadric* sun = gluNewQuadric();
	
	gluQuadricDrawStyle(sun, GLU_FILL);
	
	glBindTexture(GL_TEXTURE_2D, ID_sun);
	
	gluQuadricTexture(sun, GL_TRUE);
	
	gluQuadricNormals(sun, GLU_SMOOTH);
	
	gluSphere(sun, 100.f, 32, 16);
	
	glPopMatrix();


	Angle_sun += 0.1f;
	if (Angle_sun > 360.f)
		Angle_sun = 0.f;

	//revolving earth

	glPushMatrix();
	glTranslatef(0.f, 0.f, -300.f);
	glRotatef(Angle_Revolve, 0.f, 1.f, 0.f);
	glTranslatef(500.f, 0.f, 0.f);
	
	glPushMatrix();
	//earth

	glRotatef(Angle_earth, 0.f, 1.f, 0.f);
	glColor3ub(255, 255, 255);
	glBindTexture(GL_TEXTURE_2D, ID_earth);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	GLUquadric* earth = gluNewQuadric();
	gluQuadricDrawStyle(earth, GLU_FILL);
	gluQuadricTexture(earth, GL_TRUE);
	gluQuadricNormals(earth, GLU_SMOOTH);
	gluSphere(earth, 20.0, 32, 16);
	glPopMatrix();

	//moon

	glRotatef(Angle_moon, 0.f, 1.f, 0.f);
	glTranslatef(50.f, 0.f, 0.f);
	glColor3ub(255, 255, 255);
	glBindTexture(GL_TEXTURE_2D, ID_moon);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	GLUquadric* moon = gluNewQuadric();
	gluQuadricDrawStyle(moon, GLU_FILL);
	gluQuadricTexture(moon, GL_TRUE);
	gluQuadricNormals(moon, GLU_SMOOTH);
	gluSphere(moon, 10.0, 32, 16);
	glPopMatrix();
	glPopMatrix();
	Angle_Revolve += 2.f;
	if (Angle_Revolve > 360.f)
		Angle_Revolve = 0.f;

	Angle_earth += 5.f;
	if (Angle_earth > 360.f)
		Angle_earth = 0.f;

	Angle_moon += 5.f;
	if (Angle_moon > 360.f)
		Angle_moon = 0.f;

	glutSwapBuffers();
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("SolarSystem");


	
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunc, 1);
	glutSpecialFunc(ControlKey);
	glutDisplayFunc(RenderScene);


	LoadTexture(&ID_sun, "2k_sun.png");
	LoadTexture(&ID_earth, "2k_earth_daymap.png");
	LoadTexture(&ID_moon, "2k_moon.png");
	SetupRC();
	glutMainLoop();

}

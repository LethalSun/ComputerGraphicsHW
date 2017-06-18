
#include <Windows.h>
#include <gl/glut.h>
#include <array>
#include <random>
#include <chrono>

GLfloat xRot = 0.f;
GLfloat yRot = 0.f;
GLfloat CubeSize = 50.f;
const int Point_Num_Cube = 8;

struct color
{
	GLubyte x;
	GLubyte y;
	GLubyte z;
};


void SetPointColor()
{
	std::array<color, 8> arr;
	auto current = std::chrono::system_clock::now();
	auto duration = current.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	std::mt19937_64 rng(millis);
	std::uniform_real_distribution<float> color(0.f, 255.f);

	int i = 0;
	for (auto point : arr)
	{
		if (i % 3 == 0)
		{
			point.x = color(rng);
			point.y = 0.f;
			point.z = 0.f;
		}
		else if (i % 3 == 1)
		{
			point.x = 0.f;
			point.y = color(rng);
			point.z = 0.f;
		}
		else
		{
			point.x = 0.f;
			point.y = 0.f;
			point.z = color(rng);
		}

	}

}

void RenderScene()
{
	std::array<color, 8> colorArray;

	colorArray[0].x = 255; colorArray[0].y = 0; colorArray[0].z = 0;
	colorArray[1].x = 0; colorArray[1].y = 255; colorArray[1].z = 0;
	colorArray[2].x = 0; colorArray[2].y = 0; colorArray[2].z = 255;
	colorArray[3].x = 255; colorArray[3].y = 255; colorArray[3].z = 0;
	colorArray[4].x = 0; colorArray[4].y = 255; colorArray[4].z = 255;
	colorArray[5].x = 255; colorArray[5].y = 0; colorArray[5].z = 255;
	colorArray[6].x = 255; colorArray[6].y = 255; colorArray[6].z = 255;
	colorArray[7].x = 0; colorArray[7].y = 0; colorArray[7].z = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	glPushMatrix();

	glRotatef(xRot, 1.f, 0.f, 0.f);
	glRotatef(yRot, 0.f, 1.f, 0.f);

	glBegin(GL_QUADS);

	glColor3ub(colorArray[0].x, colorArray[0].y, colorArray[0].z);
	glVertex3f(0.f, CubeSize, 0.f);
	glColor3ub(colorArray[1].x, colorArray[1].y, colorArray[1].z);
	glVertex3f(0.f, CubeSize, CubeSize);
	glColor3ub(colorArray[2].x, colorArray[2].y, colorArray[2].z);
	glVertex3f(CubeSize, CubeSize, CubeSize);
	glColor3ub(colorArray[4].x, colorArray[4].y, colorArray[4].z);
	glVertex3f(CubeSize, CubeSize, 0.f);
	glColor3ub(colorArray[5].x, colorArray[5].y, colorArray[5].z);
	glVertex3f(0.f, 0.f, 0.f);
	glColor3ub(colorArray[6].x, colorArray[6].y, colorArray[6].z);
	glVertex3f(CubeSize, 0.f, 0.f);
	glColor3ub(colorArray[7].x, colorArray[7].y, colorArray[7].z);
	glVertex3f(CubeSize, 0.f, CubeSize);
	glColor3ub(colorArray[3].x, colorArray[3].y, colorArray[3].z);
	glVertex3f(0.f, 0.f, CubeSize);

	glEnd();


	glBegin(GL_QUAD_STRIP);

	glColor3ub(colorArray[1].x, colorArray[1].y, colorArray[1].z);
	glVertex3f(0.f, CubeSize, CubeSize);
	glColor3ub(colorArray[3].x, colorArray[3].y, colorArray[3].z);
	glVertex3f(0.f, 0.f, CubeSize);
	glColor3ub(colorArray[2].x, colorArray[2].y, colorArray[2].z);
	glVertex3f(CubeSize, CubeSize, CubeSize);
	glColor3ub(colorArray[7].x, colorArray[7].y, colorArray[7].z);
	glVertex3f(CubeSize, 0.f, CubeSize);
	glColor3ub(colorArray[4].x, colorArray[4].y, colorArray[4].z);
	glVertex3f(CubeSize, CubeSize, 0.f);
	glColor3ub(colorArray[6].x, colorArray[6].y, colorArray[6].z);
	glVertex3f(CubeSize, 0.f, 0.f);
	glColor3ub(colorArray[0].x, colorArray[0].y, colorArray[0].z);
	glVertex3f(0.f, CubeSize, 0.f);
	glColor3ub(colorArray[5].x, colorArray[5].y, colorArray[5].z);
	glVertex3f(0.f, 0.f, 0.f);
	glColor3ub(colorArray[1].x, colorArray[1].y, colorArray[1].z);
	glVertex3f(0.f, CubeSize, CubeSize);
	glColor3ub(colorArray[3].x, colorArray[3].y, colorArray[3].z);
	glVertex3f(0.f, 0.f, CubeSize);

	glEnd();


	glPopMatrix();
	glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-100.f, 100.f, -100.f*h / w, 100.f*h / w, 100.f, -100.f);
	else
		glOrtho(-100.f*w / h, 100.f*w / h, -100.f, 100.f, 100.f, -100.f);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
}


void ControlKey(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.f;


	glutPostRedisplay();
}

int main()
{
	SetPointColor();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("ColorCube");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(ControlKey);
	SetupRC();
	glutMainLoop();
}
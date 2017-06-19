#include <Windows.h>
#include <gl/glut.h>
#include <vector>
#include <random>
#include "MyBox.h"

GLfloat window_w;
GLfloat window_h;

std::vector<MyBox*> boxes;

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.f, 0.f, 0.f);

	for (auto box : boxes)
	{
		box->Draw();
	}

	glutSwapBuffers();
}

void CheckWindow(GLfloat &rectStartX, GLfloat &rectStartY, GLsizei &rectSizeX,GLsizei &rectSizeY, GLfloat &xstep, GLfloat &ystep)
{
	if (rectStartX > window_w - rectSizeX || rectStartX < -window_w)
	{
		xstep = -xstep;
	}

	if (rectStartY > window_h - rectSizeY || rectStartY < -window_h)
	{
		ystep = -ystep;
	}

	if (rectStartX > window_w - rectSizeX)
	{
		rectStartX = window_w - rectSizeX - 1;
	}

	if (rectStartX < -window_w)
	{
		rectStartX = -window_w + 1;
	}

	if (rectStartY > window_h - rectSizeY)
	{
		rectStartY = window_h - rectSizeY - 1;
	}

	if (rectStartY < -window_h)
	{
		rectStartY = -window_h + 1;
	}
}

void CheckBoxes(MyBox* box)
{
	for (auto otherBox : boxes)
	{
		if (otherBox == box)
		{
			continue;
		}

		if (!box->isCollide(otherBox))
		{
			continue;
		}

		auto otherBoxLeft = otherBox->GetX();
		auto otherBoxRight = otherBoxLeft + otherBox->GetWidth();
		auto otherBoxBottom = otherBox->GetY();
		auto otherBoxTop = otherBoxBottom + otherBox->GetHeight();

		if (box->GetXStep() * otherBox->GetXStep() < 0)
		{
			auto xstep = box->GetXStep();
			box->SetXStep(-xstep*0.9f);
			xstep = otherBox->GetXStep();
			otherBox->SetXStep(-xstep*0.9f);
		}

		if (box->GetYStep() * otherBox->GetYStep() < 0)
		{
			auto ystep = box->GetYStep();
			box->SetYStep(-ystep*0.9f);
			ystep = otherBox->GetYStep();
			otherBox->SetYStep(-ystep*0.9f);
		}

		if (box->GetMidX() < otherBox->GetMidX())
		{
			otherBox->SetPosition(box->GetX() + box->GetWidth(), otherBox->GetY());
		}
		else
		{
			otherBox->SetPosition(box->GetX() - box->GetWidth(), otherBox->GetY());
		}

		if (box->GetMidY() < otherBox->GetMidY())
		{
			otherBox->SetPosition(otherBox->GetX(),box->GetY() + box->GetHeight());
		}
		else
		{
			otherBox->SetPosition(otherBox->GetX(), box->GetY() - box->GetHeight());
		}

	}
}


void TimerFunction(int value)
{
	for (auto box : boxes)
	{
		auto boxStartX = box->GetX();
		auto boxStartY = box->GetY();
		auto boxSizeX = box->GetWidth();
		auto boxSizeY = box->GetHeight();
		auto xstep = box->GetXStep();
		auto ystep = box->GetYStep();

		CheckBoxes(box);

		CheckWindow(boxStartX, boxStartY, boxSizeX, boxSizeY, xstep, ystep);

		box->SetXStep(xstep);
		box->SetYStep(ystep);

		boxStartX += box->GetXStep();
		boxStartY += box->GetYStep();

		box->SetPosition(boxStartX, boxStartY);
		
	}
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void SetupRC()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		window_w = 100.f;
		window_h = 100.f*h / w;
		glOrtho(-100.f, 100.f, -window_h, window_h, 1.f, -1.f);
	}
	else
	{
		window_w = 100.f*w / h;
		window_h = 100.f;
		glOrtho(-window_w, window_w, -100.f, 100.f, 1.f, -1.f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void main()
{

	boxes.emplace_back(new MyBox(-400.f, -100.f, 30.f, 30.f, 5.f, 5.f));
	boxes.emplace_back(new MyBox(400.f, -100.f, 30.f, 30.f, 5.f, 5.f));
	boxes.emplace_back(new MyBox(400.f, 100.f, 30.f, 30.f, 5.f, 5.f));
	boxes.emplace_back(new MyBox(-400.f, 100.f, 30.f, 30.f, 5.f, 5.f));

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 900);
	glutCreateWindow("OpenGLPracticalProblemRect");
	glutDisplayFunc(Render);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(1000, TimerFunction, 1);
	SetupRC();

	glutMainLoop();

	for each(auto rect in boxes)
	{
		delete rect;
	}
}
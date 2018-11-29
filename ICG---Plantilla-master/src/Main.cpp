#include "Main.h"
#include "Line.h"
#include "Quad.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "BezierCurve.h"
#include "UserInterface.h"
#include <algorithm>
#include "Windows.h"
#include <iostream>
using namespace std;

using std::vector;


string name;
GLFWwindow *gWindow;
int gWidth, gHeight;
bool gPress;
CUserInterface * userInterface;
vector <CFigure *> figures;
FigureType figureSelected;
int picked;
int clicksPerFigure = 0;

string openfilename()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Json Files(.JSON)";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

void pick(int x, int y)
{
	picked = -1;
	userInterface->hide();

	for (unsigned int i = 0; i < figures.size(); i++)
	{
		if (figures[i]->getType() == LINE || figures[i]->getType() == QUAD || figures[i]->getType() == ELLIPSE) {


			float *v1 = figures[i]->getVertex(0);
			float *v2 = figures[i]->getVertex(1);
			float max[2];
			float min[2];

			// This should be precalculated

			max[0] = MAX(v1[0], v2[0]);
			max[1] = MAX(v1[1], v2[1]);

			min[0] = MIN(v1[0], v2[0]);
			min[1] = MIN(v1[1], v2[1]);

			if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
			{
				picked = i;

				userInterface->setFigureColor(figures[picked]->getColor());
				userInterface->setFigureColorBorder(figures[picked]->getColorBorder());
				userInterface->show();

				int type = figures[picked]->getType();

				if (type == LINE)
					userInterface->setFigureType("Line");
				else if (type == QUAD)
					userInterface->setFigureType("Quad");
				else if (type == ELLIPSE) {
					userInterface->setFigureType("Ellipse");
				}

				break;
			}
		}
		else if (figures[i]->getType() == CIRCLE){


			float *v1 = figures[i]->getVertex(0);
			float *v2 = figures[i]->getVertex(1);
			float max[2];
			float min[2];

			// This should be precalculated

			if (v1[0] > v2[0]) {
				max[0] = v1[0] + (v1[0] - v2[0]);
				min[0] = v2[0];
			}
			else {
				max[0] = v2[0];
				min[0] = v1[0] - (v2[0] - v1[0]);
			}

			if (v1[1] > v2[1]) {
				max[1] = v1[1] + (v1[1] - v2[1]);
				min[1] = v2[1];
			}
			else {
				max[1] = v2[1];
				min[1] = v1[1] - (v2[1] - v1[1]);
			}

			if (x >= min[0] && x <= max[0] && y >= min[1] && y <= max[1])
			{
				picked = i;

				userInterface->setFigureColor(figures[picked]->getColor());
				userInterface->setFigureColorBorder(figures[picked]->getColorBorder());
				userInterface->show();

				
				userInterface->setFigureType("Circle");

				break;
			}

		}
		else if (figures[i]->getType() == TRIANGLE) {
			
			float *v1 = figures[i]->getVertex(0);
			float *v2 = figures[i]->getVertex(1);
			float *v3 = figures[i]->getVertex(2);

			// This should be precalculated

			float maxX = v1[0];
			float maxY = v1[1];
			float minX = v1[0];
			float minY = v1[1];

			for (int j = 0; j < figures[i]->getVertexCount(); j++) {

				float * vertex = figures[i]->getVertex(j);


				if (vertex[0] < minX) {
					minX = vertex[0];
				}

				if (vertex[1] < minY) {
					minY = vertex[1];
				}

				if (vertex[0] > maxX) {
					maxX = vertex[0];
				}
				if (vertex[1] > maxY) {
					maxY = vertex[1];
				}
			}


			if (x >= minX && x <= maxX && y >= minY && y <= maxY)
			{
				picked = i;

				userInterface->setFigureColor(figures[picked]->getColor());
				userInterface->setFigureColorBorder(figures[picked]->getColorBorder());
				userInterface->show();

				userInterface->setFigureType("Triangle");

				break;
			}

		}
		else if (figures[i]->getType() == BEZIERCURVE) {


			vector<float*> points = figures[i]->getPoints();

			float maxX = points[0][0];
			float maxY = points[0][1];
			float minX = points[0][0];
			float minY = points[0][1];

			for (int i = 0; i < points.size(); i++) {
				if (points[i][0] < minX) {
					minX = points[i][0];
				}

				if (points[i][1] < minY) {
					minY = points[i][1];
				}

				if (points[i][0] > maxX) {
					maxX = points[i][0];
				}
				if (points[i][1] > maxY) {
					maxY = points[i][1];
				}
			}

			if (x >= minX && x <= maxX && y >= minY && y <= maxY)
			{
				picked = i;

				userInterface->setFigureColor(figures[picked]->getColor());
				userInterface->show();

				userInterface->setFigureType("Bezier Curve");

				break;
			}

			
		}

		
		
	}
}

void updateUserInterface()
{
	if (picked > -1)
	{
		float * color = userInterface->getFigureColor();
		float * colorBorder = userInterface->getFigureColorBorder();
		figures[picked]->setColor(color[0], color[1], color[2]);
		figures[picked]->setColorBorder(colorBorder[0], colorBorder[1], colorBorder[2]);
	}
}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (unsigned int i = 0; i < figures.size(); i++)
		figures[i]->display();
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, gWidth, 0, gHeight, -1.0f, 1.0f);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{

		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_O:

			name = openfilename();

			cout << name << endl;

			break;


		case GLFW_KEY_P:
			figureSelected = NONE;
			userInterface->hide();
			break;

		case GLFW_KEY_L:
			figureSelected = LINE;
			userInterface->hide();
			break;

		case GLFW_KEY_Q:
			figureSelected = QUAD;
			userInterface->hide();
			break;
		case GLFW_KEY_C:
			figureSelected = CIRCLE;
			userInterface->hide();
			break;
		case GLFW_KEY_E:
			figureSelected = ELLIPSE;
			userInterface->hide();
			break;
		case GLFW_KEY_T:
			figureSelected = TRIANGLE;
			userInterface->hide();
			break;
		case GLFW_KEY_F: //rellenar figura y si esta seleccionada una curva de bezier termina de colocar puntos de control
			if (picked > -1) {
				if (figures[picked]->getFill()) {
					figures[picked]->setFill(false);
				}
				else {
					figures[picked]->setFill(true);
				}
			}
			else {
				if(figures.back()->getType() == BEZIERCURVE)
				{
					figures.back()->finishBezier();
				}
			}
			break;
		case GLFW_KEY_B: //curvas de bezier
			figureSelected = BEZIERCURVE;
			userInterface->hide();

		case GLFW_KEY_M: //mover
			if (picked > -1) {
				if (figures[picked]->getMove()) {
					figures[picked]->setMove(false);
				}
				else {
					figures[picked]->setMove(true);
				}
			}
			break;

		case GLFW_KEY_1: //traer al frente

			

			if (picked > -1) {
				vector <CFigure *> tmp;

				for (int i = 0; i < figures.size(); i++) {
					if (i == picked) continue;
					tmp.push_back(figures[i]);
				}

				tmp.push_back(figures[picked]);
				figures.clear();
				figures = tmp;

				picked = figures.size() - 1;

			}
			break;

		case GLFW_KEY_0: //traer al fondo

			if (picked > -1) {
				vector <CFigure *> tmp;

				tmp.push_back(figures[picked]);
				for (int i = 0; i < figures.size(); i++) {
					if (i == picked) continue;
					tmp.push_back(figures[i]);
				}

				figures.clear();
				figures = tmp;

				picked = 0;

			}


			break;
		case GLFW_KEY_2: //traer adelante

			if (picked > -1) {

				if (picked != figures.size() - 1) {
					iter_swap(figures.begin() + picked, figures.begin() + picked + 1);
					picked++;
				}
			}


			break;
		case GLFW_KEY_9: //traer atras

			if (picked > -1) {

				if (picked != 0) {
					iter_swap(figures.begin() + picked, figures.begin() + picked - 1);
					picked--;
				}
			}

			break;
		case GLFW_KEY_D: //eliminar figura

			if (picked > -1) {
				figures.erase(figures.begin() + picked);
				picked = -1;
			}

		}


	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{

	if (TwEventMouseButtonGLFW(button, action))
		return;

	double x, y;
	glfwGetCursorPos(gWindow, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !gPress)
	{
		float ax = float(x);
		float ay = gHeight - float(y);

		if (figureSelected == NONE)
		{
			if (picked > -1 && figures[picked]->getMove()) {
				if (figures[picked]->getType() == BEZIERCURVE) {
					figures[picked]->moveBezier(ax, ay);
				}
				else {
					figures[picked]->move(ax, ay);
				}
			}
			else {

				pick(int(ax), int(ay));
			}
		
		}
		else if (figureSelected == LINE)
		{
			CLine *line = new CLine();
			line->setVertex(0, ax, ay);
			line->setVertex(1, ax, ay);
			figures.push_back(line);

			gPress = true;
		}
		else if(figureSelected == QUAD)
		{
			CQuad *quad = new CQuad();
			quad->setVertex(0, ax, ay);
			quad->setVertex(1, ax, ay);
			figures.push_back(quad);

			gPress = true;
		}
		else if (figureSelected == CIRCLE) 
		{
			CCircle *circle = new CCircle();
			circle->setVertex(0, ax, ay);
			circle->setVertex(1, ax, ay);
			figures.push_back(circle);

			gPress = true;
		}
		else if (figureSelected == ELLIPSE) {

			CEllipse *ellipse = new CEllipse();
			ellipse->setVertex(0, ax, ay);
			ellipse->setVertex(1, ax, ay);
			figures.push_back(ellipse);

			gPress = true;
		}
		else if (figureSelected == TRIANGLE) {
			if(clicksPerFigure == 0)
			{
				CTriangle *triangle = new CTriangle();
				triangle->setVertex(0, ax, ay);
				triangle->setVertex(1, ax, ay);
				triangle->setVertex(2, ax, ay);
				figures.push_back(triangle);
				gPress = true;
			}
			else {
				if(figures.back()->getVertexCount() == 3) figures.back()->setVertex(2, ax, ay);
				clicksPerFigure = -1;
			}
		}
		else if (figureSelected == BEZIERCURVE) {


			if (!figures.empty() && figures.back()->getType() == BEZIERCURVE) 
			{
				if (figures.back()->isFinishedBezier()) {

					CBezierCurve *bezierCurve = new CBezierCurve();
					bezierCurve->addVertex(ax, ay);
					figures.push_back(bezierCurve);

				}
				else {

					figures.back()->addVertex(ax, ay);
				}

			}
			else
			{
				CBezierCurve *bezierCurve = new CBezierCurve();
				bezierCurve->addVertex(ax, ay);
				figures.push_back(bezierCurve);
				
			}

			gPress = true;

		}

	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		gPress = false;
		if(figureSelected == TRIANGLE) clicksPerFigure++;
		else clicksPerFigure = 0;
	}

}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if(figureSelected != BEZIERCURVE)
	{
		if (TwEventMousePosGLFW(int(x), int(y)))
			return;

		if (gPress)
		{
			float ax = float(x);
			float ay = gHeight - float(y);

			figures.back()->setVertex(1, ax, ay);
		}
	}

}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < figures.size(); i++)
		delete figures[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "ICG - Plantilla", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

int main(void)
{

	

	gWidth = 1200;
	gHeight = 680;
	gPress = false;
	figureSelected = LINE;
	picked = -1;

	if (!initGlfw() || !initUserInterface())
		return EXIT_FAILURE;

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	while (!glfwWindowShouldClose(gWindow))
	{
		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}
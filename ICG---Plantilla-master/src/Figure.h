#pragma once

#include "../headers/glfw3.h"
#include <vector>



using std::vector;

enum FigureType
{
	NONE,
	LINE,
	QUAD,
	CIRCLE,
	TRIANGLE,
	ELLIPSE,
	RECTANGLE,
	BEZIERCURVE
};

class CFigure
{
protected:
	float **mVertices, mColor[3];
	float mColorBorder[3];
	int mType;
	bool fill;
	bool canMove;
	int vertexCount;
	bool finishedBezier;

	vector <float *> bezierPoints;

public:
	CFigure();
	virtual ~CFigure();
	void setVertex(int id, float x, float y);
	void setColor(float r, float g, float b);
	void setColorBorder(float r, float g, float b);
	void setFill(bool value);
	void move(float ax, float ay);
	void moveBezier(float ax, float ay);
	void setMove(bool m);
	void finishBezier();
	bool isFinishedBezier();
	virtual void display() = 0;
	int getType();
	float* getVertex(int id);
	float* getColor();
	float* getColorBorder();
	bool getFill();
	bool getMove();
	int getVertexCount();
	void addVertex(float x, float y);
	vector<float*> getPoints();
};
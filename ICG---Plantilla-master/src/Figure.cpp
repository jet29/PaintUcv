#include "Figure.h"
#include <algorithm>


CFigure::CFigure()
{
	mColor[0] = mColor[1] = mColor[2] = 1.0f;
	mColorBorder[0] = mColorBorder[1] = mColorBorder[2] = 1.0f;
}

CFigure::~CFigure()
{
	delete[] mVertices;
}

void CFigure::setVertex(int id, float x, float y)
{
	mVertices[id][0] = x;
	mVertices[id][1] = y;
}

void CFigure::setColor(float r, float g, float b)
{
	mColor[0] = r;
	mColor[1] = g;
	mColor[2] = b;
}

void CFigure::setColorBorder(float r, float g, float b)
{
	mColorBorder[0] = r;
	mColorBorder[1] = g;
	mColorBorder[2] = b;
}

void CFigure::setFill(bool value) 
{
	fill = value;
}

int CFigure::getType()
{
	return mType;
}

bool CFigure::getFill() 
{
	return fill;
}

float* CFigure::getVertex(int id)
{
	return mVertices[id];
}

float* CFigure::getColor()
{
	return mColor;
}

float* CFigure::getColorBorder()
{
	return mColorBorder;
}


int CFigure::getVertexCount() {
	return vertexCount;
}

void CFigure::addVertex(float x, float y) {

	float *point = new float[2];
	point[0] = x;
	point[1] = y;
	bezierPoints.push_back(point);
}

void CFigure::finishBezier() {
	finishedBezier = true;
}

bool CFigure::isFinishedBezier() {
	return finishedBezier;
}

void CFigure::setMove(bool m) {
	canMove = m;
}
bool CFigure::getMove() {
	return canMove;
}

void CFigure::move(float ax, float ay) {

	float x = mVertices[0][0];
	float y = mVertices[0][1];

	for (int i = 0; i < vertexCount; i++) {
		mVertices[i][0] -= x;
		mVertices[i][1] -= y;
	}

	for (int i = 0; i < vertexCount; i++) {
		mVertices[i][0] += ax;
		mVertices[i][1] += ay;
	}

}


void CFigure::moveBezier(float ax, float ay) {

	float x = bezierPoints[0][0];
	float y = bezierPoints[0][1];

	int size = bezierPoints.size();

	for (int i = 0; i < size; i++) {
		bezierPoints[i][0] -= x;
		bezierPoints[i][1] -= y;
	}

	for (int i = 0; i < size; i++) {
		bezierPoints[i][0] += ax;
		bezierPoints[i][1] += ay;
	}

}

vector<float*> CFigure::getPoints() {
	return bezierPoints;
}
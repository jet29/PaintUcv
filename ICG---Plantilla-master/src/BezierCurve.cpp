#include "BezierCurve.h"
#include <algorithm>
#include <iostream>

using namespace std;

float* getBezierPoint(vector<float*> points, float t) {

	vector<float*> vect;

	for (int i = 0; i < points.size(); i++)
		vect.push_back(points[i]);

	int i = vect.size() - 1;

	while (i > 0) {
		for (int k = 0; k < i; k++) {
			float* tmp = new float[2];
			tmp[0] = vect[k + 1][0] - vect[k][0];
			tmp[1] = vect[k + 1][1] - vect[k][1];
			tmp[0] *= t;
			tmp[1] *= t;
			tmp[0] += vect[k][0];
			tmp[1] += vect[k][1];
			vect[k] = tmp;
		}
		i--;
	}

	float* answer = vect[0];

	return answer;
}

CBezierCurve::CBezierCurve()
{
	mType = BEZIERCURVE;
	vertexCount = 1;
	finishedBezier = false;
	canMove = false;
}


CBezierCurve::~CBezierCurve()
{
	bezierPoints.clear();
}


void CBezierCurve::display()
{

	glColor3fv(mColor);

	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < bezierPoints.size(); i++)
		glVertex2f(bezierPoints[i][0], bezierPoints[i][1]);

	glEnd();
	


	glBegin(GL_LINE_STRIP);

	float offset = 0.01;
	float progress = 0;
	while (progress <= 1) {
		float *point = getBezierPoint(bezierPoints, progress);
		glVertex2f(point[0], point[1]);
		progress += offset;
	}


	glEnd();
}


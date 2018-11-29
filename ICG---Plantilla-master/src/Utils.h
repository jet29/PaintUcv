#pragma once

#include "../headers/glfw3.h"

void DrawLine(float x1, float y1, float x2, float y2) {

	int dx;
	int dy;
	float m;
	int x;
	int y;
	int endx;
	int endy;


	if (x2 < x1) {

		x = x2;
		y = y2;
		endx = x1;
		endy = y1;

		dx = x1 - x2;
		dy = y1 - y2;

		m = (y1 - y2) / (x1 - x2);
	}
	else {

		x = x1;
		y = y1;
		endx = x2;
		endy = y2;

		dx = x2 - x1;
		dy = y2 - y1;

		m = (y2 - y1) / (x2 - x1);

	}


	if (y == endy) { //horizontal line

		for (x; x < endx; x++)	glVertex2i(x, y);
	}
	else {

		int d = dx - 2 * dy;
		glVertex2i(x, y);

		//if (m > 0 && m < 1) {
		if (dx > dy && dy > 0) {

			int incE = -2 * dy;
			int incNE = 2 * (dx - dy);

			while (x < endx) {

				if (d <= 0) {
					d = d + incNE;
					y++;
				}
				else {
					d = d + incE;
				}
				x++;
				glVertex2i(x, y);

			}
		}
		//else if (m >= 1) {
		else if (dy > dx && dy > 0) {

			int incN = 2 * dx;
			int incNE = 2 * (dx - dy);

			while (y < endy) {

				if (d < 0) {
					d = d + incN;
				}
				else {
					d = d + incNE;
					x++;
				}
				y++;
				glVertex2i(x, y);
			}
		}
		//else if (m < 0 && m >= -1) {
		else if (abs(dx) > abs(dy) && dy < 0) {
			int incE = -2 * dy;
			int incSE = -2 * (dy + dx);

			while (x < endx) {

				if (d <= 0) {
					d = d + incE;
				}
				else {
					d = d + incSE;
					y--;
				}
				x++;
				glVertex2i(x, y);

			}
		}
		//else if (m < -1) {
		else if (abs(dy) > abs(dx) && dy < 0) {
			int incS = -2 * dx;
			int incSE = -2 * (dx + dy);

			while (y > endy) {

				if (d > 0) {
					d = d + incS;
				}
				else {
					d = d + incSE;
					x++;
				}
				y--;
				glVertex2i(x, y);
			}

		}


	}



}
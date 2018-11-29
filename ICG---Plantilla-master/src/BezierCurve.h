#pragma once

#include "Figure.h"

class CBezierCurve : public CFigure
{
	public:
		CBezierCurve();
		~CBezierCurve();
		CBezierCurve(const CFigure*);
		void display();
		

};


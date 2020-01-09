#pragma once
class point
{
	public:
		int index;
		double x;
		double y;
		point(double x, double y,int index) :x(x), y(y),index(index) {};
		point(double x, double y):point(x,y,0) {};
		point() :point(0.0, 0.0) {};
};


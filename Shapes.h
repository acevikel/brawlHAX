#pragma once
#include <iostream>




struct Point {
	double x, y;
	Point() {}

	Point(double _x, double _y) {
		x = _x;
		y = _y;
	}

};


bool pointsOverlap(Point l1, Point r1, Point l2, Point r2)
{
	//std::cout << " L1 (" << l1.x << "," << l1.y << ") " << " R1 (" << r1.x << "," << r1.y << ") " << " L2 (" << l2.x << "," << l2.y << ") " << " R2 (" << r2.x << "," << r2.y << ") " << std::endl;
	// If one rectangle is on left side of other 
	if (l1.x > r2.x || l2.x > r1.x)
		return false;
	// If one rectangle is above other 
	if (r1.y < l2.y || r2.y < l1.y)
		return false;

	return true;
}

struct Rectanglex {
	Point lp, rp;

	Rectanglex(Point _lp, Point  _rp) {
		lp = _lp;
		rp = _rp;
	}

	void print() {
		std::cout << " L1 (" << lp.x << "," << lp.y << ") " << " R1 (" << rp.x << "," << rp.y << ") ";
	}

	bool intersects(Rectanglex other) {
		return pointsOverlap(lp, rp, other.lp, other.rp);
	}
};

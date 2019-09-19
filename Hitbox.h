#pragma once
#include "Shapes.h"
#include "Player.h"

struct Hitbox {
	double xOffset, yOffset, width, height;
	int startFrame, endFrame; // [sf, ef]

	Hitbox(double _xOffset, double _yOffset, double _width, double _height, int _startFrame, int _endFrame) {
		xOffset = _xOffset;
		yOffset = _yOffset;
		width = _width;
		height = _height;
		startFrame = _startFrame;
		endFrame = _endFrame;
	}

	Rectanglex getRectangle(double px, double py) {
		double x_center = px + xOffset;
		double y_center = py + yOffset;
		Point lp = Point(x_center - width / 2.0, y_center - height / 2.0);
		Point rp = Point(x_center + width / 2.0, y_center + height / 2.0);
		return Rectanglex(lp, rp);
	}

	bool active(int index) {
		return (startFrame <= index && endFrame >= index);
	}
};
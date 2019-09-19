#pragma once
#include <math.h>

bool isSpeedZero(double speed) {
	return -5 < speed < 5;
}

double clampSpeed(double speed, double speedLimit, double accel, bool extrapolate) {

	if (abs(speed) == speedLimit)  return speed;

	if (!isSpeedZero(speed) && extrapolate) {
		if (speed < 0) {
			speed -= accel;
		}
		else {
			speed += accel;
		}
	}

	if (speed > speedLimit) {
		speed = speedLimit;
	}
	else if (speed < -1 * speedLimit) {
		speed = -1 * speedLimit;
	}
	return speed;

}
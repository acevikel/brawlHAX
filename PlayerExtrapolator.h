#pragma once
#include "constants.h"
#include "Shapes.h"
#include "Player.h"
#include "utils.h"

struct PlayerExtrapolator {
	double xPos, yPos, xVel, yVel;
	double xAccel = X_ACCEL_PER_FRAME;
	double yAccel = Y_ACCEL_PER_FRAME;

	PlayerExtrapolator(Player player, double xVelManual, double yVelManual) {
		if (xVelManual == 0) {
			xVel = player.getXVel();
		}
		else {
			xVel = xVelManual;
			xAccel = 0;
		}

		if (yVelManual == 0) {
			yVel = player.getYVel();
		}
		else {
			yVel = yVelManual;
			yAccel = 0;
		}
		xPos = player.getX();
		yPos = player.getY();
		
	}

	void update(int steps, bool extrapolateX) {
		for (int i = 0; i < steps; ++i) {
			xPos += xVel * SPEED_CONSTANT;
			yPos += yVel * SPEED_CONSTANT;
			xVel = clampSpeed(xVel, XVEL_LIMIT, xAccel, extrapolateX);
			yVel = clampSpeed(yVel, YVEL_LIMIT, yAccel, true);
		}
	}

	Rectanglex getRectangle() {
		double x_center = xPos;
		double y_center = yPos;
		Point lp = Point(x_center - PLAYER_WIDTH / 2.0, y_center - PLAYER_HEIGHT / 2.0);
		Point rp = Point(x_center + PLAYER_WIDTH / 2.0, y_center + PLAYER_HEIGHT / 2.0);
		return Rectanglex(lp, rp);
	}
};
#pragma once
#include <vector>
#include "Hitbox.h"
#include "KeyboardInterface.h"

struct Skill {
	int delayFrames, dir;
	bool light;
	int airSkill; // 0 ground-skill 1 airskill
	int movingSkill;  //0 still-skil 1-movingskill 2-doesnt matter
	int leftSkill; //0 - leftskill 1 righskill 2 doesn't matter
	double xSpeed = 0;
	double ySpeed = 0;

	std::vector<Hitbox> mHitboxes;
	Skill(int _delayFrames, std::vector<Hitbox> hitboxes,
		int _dir, bool _light, int _airSkill, int _movingSkill, int _leftSkill) {
		delayFrames = _delayFrames;
		mHitboxes = hitboxes;
		dir = _dir;
		light = _light;
		airSkill = _airSkill;
		movingSkill = _movingSkill;
		leftSkill = _leftSkill;
	}

	int getActiveFrameSize() {
		int maxf = 0;
		for (Hitbox h : mHitboxes) {
			if (h.endFrame > maxf) {
				maxf = h.endFrame;
			}
		}
		return maxf;
		//TODO: assert maxF > 0
	}

	void execute() {
		sendAttack(dir, light);
	}

	//Whether player p can cast the skill 
	bool castableBy(Player p) {

		//attacking player can't cast
		if (p.getIsAttacking()) return false;


		int onAirStatus = p.getOnAir();
		int movingStatus = p.getIsMoving();
		//TODO: add a gravity cancel logic here 
		//moving skills can be casted when gravity cancel, vice versa is not true
		//Player can't cast ground skill if its on the air
		if (onAirStatus == 1 && airSkill == 0) return false;

		//Player can't cast air skill if on ground
		if (onAirStatus == 0 && airSkill == 1) return false;

		//cant cast wrong dir skill if it is a directional skill
		if (leftSkill != 2 && (p.getIsLeftFacing() != leftSkill)) {
			return false;
		}

		//assert moving types match if moving does matter
		if (movingSkill != 2 && movingStatus != movingSkill) {
			return false;
		}
		

		return true;

	}
};

#pragma once
#include "Skill.h"
#include <vector>

Skill getDownX() {
	int delayFrames = 18;
	std::vector<Hitbox> hitboxes = {
		Hitbox(466,63,158,108,0,2),
		Hitbox(471,33,220,120,3,4),
		Hitbox(472,13,248,126,5,7)
	};
	return Skill(delayFrames, hitboxes, 3, false, 0, 1, 0);
}


Skill getDownXL() {
	int delayFrames = 18;
	std::vector<Hitbox> hitboxes = {
		Hitbox(-466,63,158,108,0,2),
		Hitbox(-471,33,220,120,3,4),
		Hitbox(-472,13,248,126,5,7)
	};
	return Skill(delayFrames, hitboxes, 3, false, 0, 1, 1);
}

Skill getGunDOwnl() {
	int delayFrames = 13;
	std::vector<Hitbox> hitboxes = {
	Hitbox(113,166,110,110,0,4),
	Hitbox(26,184,220,120,5,9)
	};
	return Skill(delayFrames, hitboxes, 3, true, 1, 2, 2);
}

Skill getNeutralLightRightGun() {

	int delayFrames = 8;
	std::vector<Hitbox> hitboxes = {
	Hitbox(256,-13,130,120,0,2),
	Hitbox(256,-13,150,140,3,5)
	};
	return Skill(delayFrames, hitboxes, -1, true, 0, 0, 0);
}


Skill getNeutralLightLeftGun() {

	int delayFrames = 8;
	std::vector<Hitbox> hitboxes = {
	Hitbox(-256,-13,130,120,0,2),
	Hitbox(-256,-13,150,140,3,5)
	};
	return Skill(delayFrames, hitboxes, -1, true, 0, 0, 1);
}

Skill getDownLightRightGun() {

	int delayFrames = 9;
	std::vector<Hitbox> hitboxes = {
	Hitbox(170,44,142,36,0,3),
	Hitbox(144,71,200,50,0,3)
	};
	return Skill(delayFrames, hitboxes, 3, true, 0, 2, 0);
}

Skill getDownLightLeftGun() {

	int delayFrames = 9;
	std::vector<Hitbox> hitboxes = {
	Hitbox(-170,44,142,36,0,3),
	Hitbox(-144,71,200,50,0,3)
	};
	return Skill(delayFrames, hitboxes, 3, true, 0, 2, 1);
}
// int _dir, bool _light, int _airSkill, int _movingSkill, int _leftSkill


Skill getOrionSpearNair() {

	int delayFrames = 14;
	std::vector<Hitbox> hitboxes = {
	Hitbox(43,-14,300,300,0,8)
	};
	Skill s = Skill(delayFrames, hitboxes, -1, true, 1, 0, 2);
	//s.ySpeed = 6.546;
	return s;
}
// int _dir, bool _light, int _airSkill, int _movingSkill, int _leftSkill



std::vector<Skill> getSpearSkills() {
	std::vector<Skill> res = std::vector<Skill>{
		getOrionSpearNair()
	};
	return res;
}

Skill getOrionLanceSairR() {

	int delayFrames = 11;
	std::vector<Hitbox> hitboxes = {
		Hitbox(141,23,66,46,0,9),
		Hitbox(187,26,54,34,0,9),
		Hitbox(242,26,70,24,0,9),
		Hitbox(285,26,30,16,0,9)
	};
	Skill s = Skill(delayFrames, hitboxes, 2, true, 1, 1, 0);
	s.xSpeed = 6.546;
	s.ySpeed = 0.01;
	return s;
}
// int _dir, bool _light, int _airSkill, int _movingSkill, int _leftSkill

std::vector<Skill> getLanceSkills() {
	std::vector<Skill> res = std::vector<Skill>{

		getOrionLanceSairR()
	};
	return res;
}
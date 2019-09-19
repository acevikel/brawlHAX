#pragma once
#include "Skill.h"
#include "Player.h"
#include "PlayerExtrapolator.h"


boolean willHit(Skill skill, Player pAttacker, Player pDefender) {
	PlayerExtrapolator attackerExtrapolator = PlayerExtrapolator(pAttacker,skill.xSpeed,skill.ySpeed);
	attackerExtrapolator.update(skill.delayFrames, skill.movingSkill != 0);

	//interpolate defender pose get defender pos and vel at the start of the delayframes
	PlayerExtrapolator enemyExtrapolator = PlayerExtrapolator(pDefender,0,0);
	enemyExtrapolator.update(skill.delayFrames,true);

	int frameSize = skill.getActiveFrameSize();

	// loop from 0 to last downx active frame, inclusive
	for (int i = 0; i <= frameSize; ++i) {

		// update the player pose in that frame for 1 frame
		attackerExtrapolator.update(1,skill.movingSkill!=0);
		enemyExtrapolator.update(1,true);
		for (Hitbox h : skill.mHitboxes) {
			// get hitboxes active at that index
			if (h.active(i)) {
				// if hitbox is active, check whether it intersects with the player hitbox, if true return true
				Rectanglex skillRect = h.getRectangle(attackerExtrapolator.xPos,attackerExtrapolator.yPos);
				Rectanglex defenderRect = enemyExtrapolator.getRectangle();
				if (skillRect.intersects(defenderRect)) {
					skillRect.print();
					//std::cout << "SKILL RECT" << std::endl;
					defenderRect.print();
					//std::cout << "DEF RECT" << std::endl;
					return true;
				}
			}
		}
	}
	// end loop
	return false;
}
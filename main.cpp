/*TODO: 
-Add a new dir for no dir for skills
-Add references to pass classes
-Add pause button and handle the p=1 case
-Add some interface to listen keyboard inputs
-Clever method to guess speed, could be machine learning
-Add priority to skills to sort in a vector
-Time cycles
-Measure 
-Verify coords by getting mouse pos 
-Need to fix horizontal speed interpolation for player (stops the player)
-Need better vertical speed estimation
- Add a visual debugger
- Investigate the case where other player not found 
*/
#include "GameInterface.h"
#include "SkillCollections.h"
#include "Logic.h"
using namespace std;

int getKeyStatus() {
	if (GetAsyncKeyState(VK_NUMPAD0)) {
		return 0;
	}
	else if (GetAsyncKeyState(VK_NUMPAD1)) {
		return 1;
	}
	else if  (GetAsyncKeyState(VK_NUMPAD2)) {
		return 2;
	}
	else {
		return -1;
	}
}

void forceSKill(Skill skill, vector<Player> activePlayers) {
	Player myPlayer = activePlayers[0];
	if (willHit(skill, activePlayers[0], activePlayers[1])) {
		if (skill.castableBy(myPlayer)) {
			skill.execute();
			std::cout << "EXECUTED " << std::endl;
		}
	}
}


int main() {
	int procId = GetProdId("Brawlhalla.exe");
	uintptr_t moduleBase = GetModuleBaseAddress(procId, "Adobe AIR.dll");
	
	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

	uintptr_t dynamicPtrBase = moduleBase + 0x01315500;

	std::vector<unsigned int> baseOffsets = { 0x624,0x8,0x18C,0x524 };
	uintptr_t playerBaseAddr = getPlayerBase(hProcess, dynamicPtrBase, baseOffsets);



	auto activePlayers = getActivePlayers(hProcess, playerBaseAddr);
	int numActivePlayers = activePlayers.size();

	Player myPlayer = activePlayers[0];
	myPlayer.printstats();
	if (numActivePlayers > 1) {
		Player otPlayer = activePlayers[1];
	}
	
	double xDiff, yDiff;
	vector<Skill> spearSkills = getSpearSkills();
	vector<Skill> lanceSkills = getLanceSkills();
	/*
	0 -> Loop free
	1 -> Loop light
	2 -> Loop heavy
	*/
	int keyState;
	int loopState = 0;

	while (!GetAsyncKeyState(VK_END)) {

		keyState = getKeyStatus();

		if (keyState ==1) {
			std::cout << "LIGHT MODE" << std::endl;
			loopState = 1;
		}
		else if (keyState == 2) {
			std::cout << "HEAVY MODE" << std::endl;
			loopState = 2;
		}
		else if (keyState == 0) {
			std::cout << "EZ MODE" << std::endl;
			loopState = 0;
		}

		if (loopState == 1) {
			for (Skill sk : spearSkills) {
				forceSKill(sk, activePlayers);
			}
		}
		else if (loopState == 2) {
			for (Skill sk : lanceSkills) {
				forceSKill(sk, activePlayers);
			}
		}

		Sleep(100);
	}
}
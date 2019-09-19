#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>
#include "constants.h"

double readDouble(HANDLE hProc, uintptr_t ptr, unsigned int offset) {
	double res = 0;
	ReadProcessMemory(hProc, (BYTE*)ptr + offset, &res, sizeof(res), nullptr);
	return res;
}

int readInt(HANDLE hProc, uintptr_t ptr, unsigned int offset) {
	int res = 0;
	ReadProcessMemory(hProc, (BYTE*)ptr + offset, &res, sizeof(res), nullptr);
	return res;
}


class Player {
public:

	Player() {
		mHandle = 0;
		mPtr = 0;
	}
	Player(HANDLE h, uintptr_t p) {
		mHandle = h;
		mPtr = p;
	}

	bool isValid() {
		tick();
		return xPos > 5 && yPos > 5;
	}

	double getXVel() {
		xVel = readDouble(mHandle, mPtr, xVelOffset);
		return xVel;
	}

	double getYVel() {
		yVel = readDouble(mHandle, mPtr, yVelOffset);
		return yVel;
	}

	double getX() {
		xPos = readDouble(mHandle, mPtr, xPosOffset);
		return xPos;
	}

	double getY() {
		yPos = readDouble(mHandle, mPtr, yPosOffset);
		return yPos;
	}

	int getOnAir() {
		onAir = readInt(mHandle, mPtr, onAirOffset);
		return onAir;
	}

	int getIsAttacking() {
		isAttacking = readInt(mHandle, mPtr, isAttackingOffset);
		return isAttacking;
	}

	int getIsMoving() {
		isMoving = readInt(mHandle, mPtr, isMovingOffset);
		return isMoving;
	}

	int getIsLeftFacing() {
		isLeftFacing = readInt(mHandle, mPtr, leftFacingOffset);
		return isLeftFacing;
	}

	void printstats() {
		tick();
		std::cout << "BASE PTR " << std::hex << mPtr << std::endl;
		std::cout << "X_POS: " << xPos << " Y_POS: " << yPos << " X_VEL: " << xVel << " Y_VEL: " << yVel << " AIR : " << onAir << " ATK: " << isAttacking << " MOV: " << isMoving << std::endl;
		std::cout << "X_POS: " << xPos + xVel * SPEED_CONSTANT << " Y_POS: " << yPos + yVel * SPEED_CONSTANT << std::endl;
	}

	double getDiff(Player &other) {
		return abs(getX() - other.getX()) + abs(getY() - other.getY());
	}


private:
	double xPos, yPos, xVel, yVel;
	int onAir, isAttacking, isMoving, isLeftFacing;
	HANDLE mHandle;
	uintptr_t mPtr;
	int xPosOffset = 0x370; int yPosOffset = 0x368;  int xVelOffset = 0x320; int yVelOffset = 0x318; int onAirOffset = 0x58; int isAttackingOffset = 0x5C; int isMovingOffset = 0x28;
	int leftFacingOffset = 0x40;

	void tick() {
		xPos = readDouble(mHandle, mPtr, xPosOffset);
		yPos = readDouble(mHandle, mPtr, yPosOffset);
		xVel = readDouble(mHandle, mPtr, xVelOffset);
		yVel = readDouble(mHandle, mPtr, yVelOffset);
		onAir = readInt(mHandle, mPtr, onAirOffset);
		isAttacking = readInt(mHandle, mPtr, isAttackingOffset);
		isMoving = readInt(mHandle, mPtr, isMovingOffset);
		isLeftFacing = readInt(mHandle, mPtr, leftFacingOffset);

	}

};

DWORD GetProdId(const char* procName) {
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				bool res = strcmp(procEntry.szExeFile, procName);
				if (!res)
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;

}

uintptr_t GetModuleBaseAddress(DWORD procId, const char* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				bool res = strcmp(modEntry.szModule, modName);
				if (!res)
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

uintptr_t getPlayerBase(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets) {
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i) {
		ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	ReadProcessMemory(hProc, (BYTE*)addr, &addr, sizeof(addr), 0);
	return addr;
}



void readPlayerStats(HANDLE hProc, uintptr_t ptr) {
	double xpos = readDouble(hProc, ptr, 0x368);
	double ypos = readDouble(hProc, ptr, 0x370);
	std::cout << "READ PLAYER: X POS : " << xpos << " Y POS : " << ypos << std::endl;
}

void clearList(std::vector<Player> &players) {
	for (unsigned int i = 1; i < players.size(); ++i) {
		bool unique = true;
		
		for (unsigned int j = 1; j < players.size(); ++j) {
			if (i == j) continue;
			if (players[i].getDiff(players[j])<1) {
				unique = false;
			}
		}

		if (unique) {
			players[1] = players[i];
			while (players.size() > 2) {
				players.pop_back();
			}
			return;
		}


	}
}


std::vector<Player> getActivePlayers(HANDLE hProc, uintptr_t playerBase) {
	std::vector<Player> res = std::vector<Player>();
	res.push_back(Player(hProc, playerBase));
	std::vector<int> playerLocs = { -0x520,0x520,0xA40 };

	for (int i : playerLocs) {
		Player temp = Player(hProc, playerBase + i);
		if (temp.isValid()) {
			res.push_back(temp);
		}
		/*
		std::cout << "POINTER DIFF: " << i <<" POSE DIFF : " << temp.getDiff(res[0]) <<std::endl;
		temp.printstats();
		res.push_back(temp);
		*/

	}
	//clearList(res);
	std::cout << "NUMBER OF ACTIVE PLAYERS : " << res.size() << std::endl;
	return res;
}

#pragma once
#include <windows.h>

void focusToGame() {
	HWND GameWindow = FindWindow(0, "Brawlhalla.exe");
	SetForegroundWindow(GameWindow);
}

void setDirection(int offset) {
	int key = 0x25;
	key += offset;
	keybd_event(key, 0, 0, 0);
	Sleep(30);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

//    1
// 0 -1  2
//    3
void sendAttack(int dir, bool light) {
	//send dir if dir is not -1
	bool sendDir = dir != -1;
	int atkey;
	if (light) {
		atkey = 0x43;
	}
	else {
		atkey = 0x58;
	}
	int key = 0x25 + dir;

	if (sendDir) {
		keybd_event(key, 0, 0, 0);
		Sleep(10);
	}

	keybd_event(atkey, 0, 0, 0);
	Sleep(10);
	keybd_event(atkey, 0, KEYEVENTF_KEYUP, 0);

	if (sendDir) {
		Sleep(10);
		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	}
}

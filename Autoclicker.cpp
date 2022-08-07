#include <iostream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <random>

void clear() {
	std::system("cls");
	std::cout << R"(


   /$$$$$$  /$$ /$$           /$$              /$$$$$$ 
  /$$__  $$| $$|__/          | $$             /$$$_  $$
 | $$  \__/| $$ /$$  /$$$$$$$| $$   /$$      | $$$$\ $$
 | $$      | $$| $$ /$$_____/| $$  /$$/      | $$ $$ $$
 | $$      | $$| $$| $$      | $$$$$$/       | $$\ $$$$
 | $$    $$| $$| $$| $$      | $$_  $$       | $$ \ $$$
 |  $$$$$$/| $$| $$|  $$$$$$$| $$ \  $$      |  $$$$$$/
  \______/ |__/|__/ \_______/|__/  \__/       \______/ 


)" << '\n';
}


void changeToggle(int mincps, int maxcps, bool toggled) {
	clear();
	std::string isActive = "False";
	if (toggled == true) {
		isActive = "True";
	} else {
		isActive = "False";
	}
	std::string cmdtitle = "title Click 0 ^| " + isActive + " ^| " + std::to_string(mincps) + "cps ^| " + std::to_string(maxcps) + "cps";
	std::system(cmdtitle.c_str());
	std::cout << "[>] Min cps: " << mincps << '\n';
	std::cout << "[>] Max cps: " << maxcps << '\n';
	std::cout << "[>] Toggled (f9): " << isActive << '\n';
	std::cout << "\n\n[>] Hold down Left Click to go brrr..";
}


int main() {
	std::system("mode con: cols=56 lines=28");
	clear();
	int min{ 0 };
	int max{ 0 };
	bool clickerOn = false;
	std::random_device rd; 
	std::mt19937 gen(rd());

	std::system("title Click 0 ^| False ^| 0cps ^| 0cps");
	do {
		std::cout << "[>] Input min cps: ";
		std::cin >> min;
	} while (min < 0);
	do {
		std::cout << "[>] Input max cps: ";
		std::cin >> max;
	} while (max < min);
	changeToggle(min, max, clickerOn);

	int minms = 1000 / min;
	int maxms = 1000 / max;
	std::uniform_int_distribution<> distr(maxms, minms);


	while (true) {
		if (GetAsyncKeyState(VK_F9) & 1) {
			clickerOn = !clickerOn;
			changeToggle(min, max, clickerOn);
		}

		if (clickerOn && GetAsyncKeyState(VK_LBUTTON) < 0) {
			POINT cursorPos;
			GetCursorPos(&cursorPos);
			int x = cursorPos.x;
			int y = cursorPos.y;

			mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);

			int randomms = distr(gen);
			Sleep(randomms);
		}
	}

}
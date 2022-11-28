#include "Tetris.h"
#include <windows.h>

int main() {

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	std::srand(std::time(0));
	auto tetris = std::make_shared<Tetris>();
	tetris->run();
	return 0;
}
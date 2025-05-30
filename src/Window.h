#pragma once
#include <windows.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Window
{
private:
	int m_WindowLength, m_WindowWidth;
	const char* m_WindowName;
public:
	const int WinTilesNum = 40;
	Window(const int length, const int width, const char* WindowName);
	~Window();
	void PlayMusic();
	GLFWwindow* CreateGameWindow();
	void GameInit();
};

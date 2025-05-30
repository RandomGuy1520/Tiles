#include "Window.h"
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<bool> stopStartMusic(false);

void Window::PlayMusic()
{
	auto start = std::chrono::system_clock::now();
	PlaySound(TEXT("D:/VSProject/Tiles/res/music/StartMusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (!stopStartMusic)
	{
		if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() > 67)
			PlayMusic();
	}
	PlaySound(NULL, NULL, SND_FILENAME);
}

Window::Window(const int length, const int width, const char* name)
	: m_WindowLength(length), m_WindowWidth(width), m_WindowName(name) 
{
	for (int i = 0; i < 50; i++)
	{
		keybd_event(174, 0, 0, 0);
		keybd_event(174, 0, KEYEVENTF_KEYUP, 0);
	}
	for (int i = 0; i < 5; i++)
	{
		keybd_event(175, 0, 0, 0);
		keybd_event(175, 0, KEYEVENTF_KEYUP, 0);
	}
	char a;
	std::thread MusicStartThread(&Window::PlayMusic, this);
	std::cout << "Welcome to Tiles!\n欢迎来到Tiles游戏！\n\n";
	Sleep(700);
	std::cout << "In this game, whoever dominates " << WinTilesNum << " squares first WINS!\nMore rules see : \nhttps ://jtxxtilesgamerules.wixsite.com/rules\n\n在这个游戏里，谁先占领" << WinTilesNum << "个方块谁就赢！\n详细规则请见网站：\nhttps://jtxxtilesgamerules.wixsite.com/rules\n";
	Sleep(2000);
	std::cout << "\nPress ENTER to play <Press Enter> -> \n请按 ENTER 键开始游戏！<按Enter> ->";
	std::cin.get(a);
	while (a != '\n') { std::cin.get(a); }
	stopStartMusic = true;
	MusicStartThread.join();
	stopStartMusic = false;
}

Window::~Window()
{
	glfwTerminate();
}

GLFWwindow* Window::CreateGameWindow()
{
	GLFWwindow* window;
	glewInit();

	if (!glfwInit())
		std::cout << "Error Initializing GLFW!" << std::endl;

	window = glfwCreateWindow(m_WindowLength, m_WindowWidth, m_WindowName, NULL, NULL);
	glfwSetWindowPos(window, 0, 1030-m_WindowWidth);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Error Generating Window!";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
		std::cout << "Error Initializing GLEW!" << std::endl;
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	return window;
}

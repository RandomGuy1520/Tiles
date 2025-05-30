#pragma once
#include "Sprite.h"
#include "Zombie.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <windows.h>
#include <string>
#include <algorithm>

struct ScreenOne
{
	BlueScreenOneSprite Blue1Sprite;
	BlueScreenOneSprite Blue2Sprite;
	RedScreenOneSprite Red1Sprite;
	RedScreenOneSprite Red2Sprite;
	MatrixScreenOne matrix;
	ZombieScreenOne Zombie1;
	ZombieScreenOne Zombie2;
	ZombieScreenOne Zombie3;

	ZombieScreenOne Zombie4;
	ScreenOne()
		: Blue1Sprite(0, Sprite::Up, true, 7, 0), Blue2Sprite(1, Sprite::Up, false, 8, 0), Red1Sprite(2, Sprite::Down, true, 8, 9), Red2Sprite(3, Sprite::Down, false, 7, 9), 
		Zombie1(0, 0, Sprite::ZOMBIE_RIGHT), Zombie2(15, 0, Sprite::ZOMBIE_LEFT), Zombie3(0, 9, Sprite::ZOMBIE_RIGHT), Zombie4(15, 9, Sprite::ZOMBIE_LEFT)
	{} 
};
struct ScreenTwo
{
	BlueScreenTwoSprite Blue1Sprite;
	BlueScreenTwoSprite Blue2Sprite;
	RedScreenTwoSprite Red1Sprite;
	RedScreenTwoSprite Red2Sprite;
	MatrixScreenTwo matrix;
	ZombieScreenTwo Zombie1;
	ZombieScreenTwo Zombie2;
	ZombieScreenTwo Zombie3;
	ZombieScreenTwo Zombie4;
	ScreenTwo(ScreenOne& screen)
		: Red1Sprite(4, Sprite::Up, true, 7, 0), Red2Sprite(5, Sprite::Up, false, 8, 0), Blue1Sprite(6, Sprite::Down, true, 8, 9), Blue2Sprite(7, Sprite::Down, false, 7, 9),
		Zombie1(&screen.Zombie1), Zombie2(&screen.Zombie2), Zombie3(&screen.Zombie3), Zombie4(&screen.Zombie4) {}
};
struct GLTools
{
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout layout;
};
struct Inputs
{
	Sprite::Input BlueInput;
	Sprite::Input RedInput;
	bool IsSwitchUsingBlue;
	bool IsSwitchUsingRed;
};
enum Dead {None, Blue, Red, Both};

std::atomic<bool> stopGameMusic(false);
std::string to_lower(std::string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}
void PlayGameMusic()
{
	auto start = std::chrono::system_clock::now();
	PlaySound(L"D:/VSProject/Tiles/res/music/GameMusic.wav", NULL, SND_FILENAME | SND_ASYNC);
	while (!stopGameMusic)
	{
		if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() > 83)
			PlayGameMusic();
	}
	PlaySound(NULL, NULL, SND_FILENAME);
}
Inputs GetInput(GLFWwindow* window)
{
	bool IsSwitchBlue = false;
	bool IsSwitchRed = false;
	Inputs inputs;
	auto start = std::chrono::system_clock::now();
	Sprite::Input BlueInputs = Sprite::Input::None;
	Sprite::Input RedInputs = Sprite::Input::None;
	while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() < 1)
	{
		glfwPollEvents();

		// Blue Inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			BlueInputs = Sprite::Input::Up;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			BlueInputs = Sprite::Input::Left;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			BlueInputs = Sprite::Input::Down;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			BlueInputs = Sprite::Input::Right;
		}
		else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		{
			IsSwitchBlue = true;
		}
		// Red Inputs
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			RedInputs = Sprite::Input::Up;
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			RedInputs = Sprite::Input::Down;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			RedInputs = Sprite::Input::Left;
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			RedInputs = Sprite::Input::Right;
		}
		else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			IsSwitchRed = true;
		}
		if (glfwWindowShouldClose(window))
		{
			BlueInputs = Sprite::Input::Break;
			RedInputs = Sprite::Input::Break;
			break;
		}
		Sleep(2);
	}
	inputs.BlueInput = BlueInputs;
	inputs.RedInput = RedInputs;
	inputs.IsSwitchUsingBlue = IsSwitchBlue;
	inputs.IsSwitchUsingRed = IsSwitchRed;
	return inputs;
}
void Draw(ScreenOne& screen, GLTools& tools, IndexBuffer& ib, Texture& texture, const int& xCoords, const int& yCoords)
{
	// Bind And Draw Everything
	ib.Bind();
	tools.vb.SetDataSize(screen.matrix.TexturePos[xCoords][yCoords], 16 * sizeof(float));
	tools.layout.Push<float>(2);
	tools.layout.Push<float>(2);
	tools.va.AddBuffer(tools.vb, tools.layout);
	tools.va.Bind();
	tools.vb.Bind();
	texture.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

	// Reset Everything
	texture.Unbind();
	tools.vb.Reset();
	tools.layout.Reset();
}
void Draw(ScreenTwo& screen, GLTools& tools, IndexBuffer& ib, Texture& texture, const int& xCoords, const int& yCoords)
{
	// Bind And Draw Everything
	ib.Bind();
	tools.vb.SetDataSize(screen.matrix.TexturePos[xCoords][yCoords], 16 * sizeof(float));
	tools.layout.Push<float>(2);
	tools.layout.Push<float>(2);
	tools.va.AddBuffer(tools.vb, tools.layout);
	tools.va.Bind();
	tools.vb.Bind();
	texture.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

	// Reset Everything
	texture.Unbind();
	tools.vb.Reset();
	tools.layout.Reset();
}
void DrawXY(ScreenOne& screen, GLTools& tools, IndexBuffer& ib, Texture& texture, const int& LBX, const int& LBY, const int& RTX, const int& RTY)
{
	float positions[16] = {
		LBX, LBY, 0.0f, 0.0f,
		RTX, LBY, 1.0f, 0.0f,
		RTX, RTY, 1.0f, 1.0f,
		LBX, RTY, 0.0f, 1.0f
	};
	// Bind And Draw Everything
	ib.Bind();
	tools.vb.SetDataSize(positions, 16 * sizeof(float));
	tools.layout.Push<float>(2);
	tools.layout.Push<float>(2);
	tools.va.AddBuffer(tools.vb, tools.layout);
	tools.va.Bind();
	tools.vb.Bind();
	texture.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

	// Reset Everything
	texture.Unbind();
	tools.vb.Reset();
	tools.layout.Reset();
}
void DrawXY(ScreenTwo& screen, GLTools& tools, IndexBuffer& ib, Texture& texture, const int& LBX, const int& LBY, const int& RTX, const int& RTY)
{
	float positions[16] = {
		LBX, LBY, 0.0f, 0.0f,
		RTX, LBY, 1.0f, 0.0f,
		RTX, RTY, 1.0f, 1.0f,
		LBX, RTY, 0.0f, 1.0f
	};
	// Bind And Draw Everything
	ib.Bind();
	tools.vb.SetDataSize(positions, 16 * sizeof(float));
	tools.layout.Push<float>(2);
	tools.layout.Push<float>(2);
	tools.va.AddBuffer(tools.vb, tools.layout);
	tools.va.Bind();
	tools.vb.Bind();
	texture.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);

	// Reset Everything
	texture.Unbind();
	tools.vb.Reset();
	tools.layout.Reset();
}
void DrawSquareXY(ScreenOne& screen, GLTools& tools, IndexBuffer& ib, Texture& texture, const int& LBX, const int& LBY, const int SideLength)
{
	int RTX = LBX + SideLength;
	int RTY = LBY + SideLength;
	DrawXY(screen, tools, ib, texture, LBX, LBY, RTX, RTY);
}
void DrawSquareXY(ScreenTwo& screen, GLTools& tools, IndexBuffer& ib, Texture& texture, const int& LBX, const int& LBY, const int SideLength)
{
	int RTX = LBX + SideLength;
	int RTY = LBY + SideLength;
	DrawXY(screen, tools, ib, texture, LBX, LBY, RTX, RTY);
}
void DrawYouDied(ScreenOne& screen, GLTools& tools, IndexBuffer& ib, bool IsAlive, int num)
{
	if (!IsAlive)
	{
		Texture texture("D:/VSProject/Tiles/res/textures/GameEnds/YOUDIED" + std::to_string(num) + ".png");
		DrawXY(screen, tools, ib, texture, 302, 380, 302 + texture.GetWidth(), 380 + texture.GetHeight());
	}
}
void DrawYouDied(ScreenTwo& screen, GLTools& tools, IndexBuffer& ib, bool IsAlive, int num)
{
	if (!IsAlive)
	{
		Texture texture("D:/VSProject/Tiles/res/textures/GameEnds/YOUDIED" + std::to_string(num) + ".png");
		DrawXY(screen, tools, ib, texture, 1242, 380, 1242 + texture.GetWidth(), 380 + texture.GetHeight());
	}
}
std::string SwitchingNum(int digit)
{
	switch (digit)
	{
	case 0: return "Zero";
	case 1: return "One";
	case 2: return "Two";
	case 3: return "Three";
	case 4: return "Four";
	case 5: return "Five";
	case 6: return "Six";
	case 7: return "Seven";
	case 8: return "Eight";
	case 9: return "Nine";
	}
}
void DisplayTilesNum(ScreenOne& screen, GLTools& tools, IndexBuffer& ib, int TilesNum, int LBX, int LBY, int RTX, int RTY)
{
	int digit = TilesNum % 10;
	int tenth = (TilesNum - digit) / 10;
	Texture DigitTexture("D:/VSProject/Tiles/res/textures/TileNums/" + SwitchingNum(digit) + ".png");
	Texture TenthTexture("D:/VSProject/Tiles/res/textures/TileNums/" + SwitchingNum(tenth) + ".png");
	DrawXY(screen, tools, ib, TenthTexture, LBX, LBY, (RTX + LBX) / 2, RTY);
	DrawXY(screen, tools, ib, DigitTexture, (RTX + LBX) / 2, LBY, RTX, RTY);
}
void DisplayTilesNum(ScreenTwo& screen, GLTools& tools, IndexBuffer& ib, int TilesNum, int LBX, int LBY, int RTX, int RTY)
{
	int digit = TilesNum % 10;
	int tenth = (TilesNum - digit) / 10;
	Texture DigitTexture("D:/VSProject/Tiles/res/textures/TileNums/" + SwitchingNum(digit) + ".png");
	Texture TenthTexture("D:/VSProject/Tiles/res/textures/TileNums/" + SwitchingNum(tenth) + ".png");
	DrawXY(screen, tools, ib, TenthTexture, LBX, LBY, (RTX + LBX) / 2, RTY);
	DrawXY(screen, tools, ib, DigitTexture, (RTX + LBX) / 2, LBY, RTX, RTY);
}
void CheckDeath(ZombieScreenOne& zombie, Sprite& sprite)
{
	if (zombie.GetX() == sprite.GetX() && zombie.GetY() == sprite.GetY())
	{
		sprite.IsAlive = false;
		zombie.NeedToReset = true;
	}
}
void CheckDeath(ZombieScreenTwo& zombie, Sprite& sprite)
{
	if (zombie.GetX() == sprite.GetX() && zombie.GetY() == sprite.GetY())
		sprite.IsAlive = false;
}
void CheckDeath(BlueScreenOneSprite& sprite1, RedScreenOneSprite& sprite2)
{
	if (sprite1.GetX() == sprite2.GetX() && sprite1.GetY() == sprite2.GetY())
	{

		if (!sprite1.IsUsing && sprite2.IsUsing)
			sprite1.IsAlive = false;
		else if (!sprite2.IsUsing && sprite1.IsUsing)
			sprite2.IsAlive = false;
		else if (sprite1.GetY() >= 5)
			sprite1.IsAlive = false;
		else
			sprite2.IsAlive = false;
	}
}
void CheckDeath(RedScreenTwoSprite& sprite1, BlueScreenTwoSprite& sprite2)
{
	if (sprite1.GetX() == sprite2.GetX() && sprite1.GetY() == sprite2.GetY())
	{
		if (!sprite1.IsUsing && sprite2.IsUsing)
			sprite1.IsAlive = false;
		else if (!sprite2.IsUsing && sprite1.IsUsing)
			sprite2.IsAlive = false;
		else if (sprite1.GetY() >= 5)
			sprite1.IsAlive = false;
		else
			sprite2.IsAlive = false;
	}
}
Dead Death(ScreenOne& screen1, ScreenTwo& screen2, GLTools& tools1, GLTools& tools2, IndexBuffer& ib)
{
	Dead return_dead = None;

	// Check between Zombie and Sprite
	CheckDeath(screen1.Zombie1, screen1.Blue1Sprite);
	CheckDeath(screen1.Zombie1, screen1.Blue2Sprite);
	CheckDeath(screen1.Zombie1, screen1.Red1Sprite);
	CheckDeath(screen1.Zombie1, screen1.Red2Sprite);
	CheckDeath(screen1.Zombie2, screen1.Blue1Sprite);
	CheckDeath(screen1.Zombie2, screen1.Blue2Sprite);
	CheckDeath(screen1.Zombie2, screen1.Red1Sprite);
	CheckDeath(screen1.Zombie2, screen1.Red2Sprite);
	CheckDeath(screen1.Zombie3, screen1.Blue1Sprite);
	CheckDeath(screen1.Zombie3, screen1.Blue2Sprite);
	CheckDeath(screen1.Zombie3, screen1.Red1Sprite);
	CheckDeath(screen1.Zombie3, screen1.Red2Sprite);
	CheckDeath(screen1.Zombie4, screen1.Blue1Sprite);
	CheckDeath(screen1.Zombie4, screen1.Blue2Sprite);
	CheckDeath(screen1.Zombie4, screen1.Red1Sprite);
	CheckDeath(screen1.Zombie4, screen1.Red2Sprite);
	CheckDeath(screen2.Zombie1, screen2.Blue1Sprite);
	CheckDeath(screen2.Zombie1, screen2.Blue2Sprite);
	CheckDeath(screen2.Zombie1, screen2.Red1Sprite);
	CheckDeath(screen2.Zombie1, screen2.Red2Sprite);
	CheckDeath(screen2.Zombie2, screen2.Blue1Sprite);
	CheckDeath(screen2.Zombie2, screen2.Blue2Sprite);
	CheckDeath(screen2.Zombie2, screen2.Red1Sprite);
	CheckDeath(screen2.Zombie2, screen2.Red2Sprite);
	CheckDeath(screen2.Zombie3, screen2.Blue1Sprite);
	CheckDeath(screen2.Zombie3, screen2.Blue2Sprite);
	CheckDeath(screen2.Zombie3, screen2.Red1Sprite);
	CheckDeath(screen2.Zombie3, screen2.Red2Sprite);
	CheckDeath(screen2.Zombie4, screen2.Blue1Sprite);
	CheckDeath(screen2.Zombie4, screen2.Blue2Sprite);
	CheckDeath(screen2.Zombie4, screen2.Red1Sprite);
	CheckDeath(screen2.Zombie4, screen2.Red2Sprite);

	// Check between two different players
	CheckDeath(screen1.Blue1Sprite, screen1.Red1Sprite);
	CheckDeath(screen1.Blue1Sprite, screen1.Red2Sprite);
	CheckDeath(screen1.Blue2Sprite, screen1.Red1Sprite);
	CheckDeath(screen1.Blue2Sprite, screen1.Red2Sprite);
	CheckDeath(screen2.Red1Sprite, screen2.Blue1Sprite);
	CheckDeath(screen2.Red1Sprite, screen2.Blue2Sprite);
	CheckDeath(screen2.Red2Sprite, screen2.Blue1Sprite);
	CheckDeath(screen2.Red2Sprite, screen2.Blue2Sprite);

	if (!screen1.Blue1Sprite.IsAlive || !screen1.Blue2Sprite.IsAlive)
	{
		if (screen1.Blue1Sprite.DeathCountdown != 0 && screen1.Blue2Sprite.DeathCountdown != 0)
		{
			if (screen1.Blue1Sprite.IsAlive)
			{
				screen1.Blue2Sprite.DeathCountdown--;
				screen2.Blue2Sprite.DeathCountdown--;
			}
			else
			{
				screen1.Blue1Sprite.DeathCountdown--;
				screen2.Blue1Sprite.DeathCountdown--;
			}
			return_dead = Blue;
		}
		else
		{
			screen1.Blue1Sprite.IsAlive = true;
			screen1.Blue2Sprite.IsAlive = true;
			screen2.Blue1Sprite.IsAlive = true;
			screen2.Blue2Sprite.IsAlive = true;
			screen1.Blue1Sprite.DeathCountdown = 5;
			screen1.Blue2Sprite.DeathCountdown = 5;
			screen2.Blue1Sprite.DeathCountdown = 5;
			screen2.Blue2Sprite.DeathCountdown = 5;
		}
		screen1.Blue1Sprite.SetXYCoords(7, 0);
		screen1.Blue2Sprite.SetXYCoords(8, 0);
		screen2.Blue1Sprite.SetXYCoords(8, 9);
		screen2.Blue2Sprite.SetXYCoords(7, 9);
		screen1.Blue1Sprite.IsUsing = true;
		screen1.Blue2Sprite.IsUsing = false;
		screen2.Blue1Sprite.IsUsing = true;
		screen2.Blue2Sprite.IsUsing = false;
	}
	if (!screen1.Red1Sprite.IsAlive || !screen1.Red2Sprite.IsAlive)
	{
		if (screen1.Red1Sprite.DeathCountdown != 0 && screen1.Red2Sprite.DeathCountdown != 0)
		{
			if (screen1.Red1Sprite.IsAlive)
			{
				screen1.Red2Sprite.DeathCountdown--;
				screen2.Red2Sprite.DeathCountdown--;
			}
			else
			{
				screen1.Red1Sprite.DeathCountdown--;
				screen2.Red1Sprite.DeathCountdown--;
			}
			return_dead = (return_dead == Blue) ? Both : Red;
		}
		else
		{
			screen1.Red1Sprite.IsAlive = true;
			screen1.Red2Sprite.IsAlive = true;
			screen2.Red1Sprite.IsAlive = true;
			screen2.Red2Sprite.IsAlive = true;
			screen1.Red1Sprite.DeathCountdown = 5;
			screen1.Red2Sprite.DeathCountdown = 5;
			screen2.Red1Sprite.DeathCountdown = 5;
			screen2.Red2Sprite.DeathCountdown = 5;
		}
		screen1.Red1Sprite.SetXYCoords(8, 9);
		screen1.Red2Sprite.SetXYCoords(7, 9);
		screen2.Red1Sprite.SetXYCoords(7, 0);
		screen2.Red2Sprite.SetXYCoords(8, 0);
		screen1.Red1Sprite.IsUsing = true;
		screen1.Red2Sprite.IsUsing = false;
		screen2.Red1Sprite.IsUsing = true;
		screen2.Red2Sprite.IsUsing = false;
	}
	return return_dead;
}
void Move(ScreenOne& screen1, ScreenTwo& screen2, GLTools& tools1, GLTools& tools2, IndexBuffer& ib, Inputs& inputs)
{
	Dead who_died = Death(screen1, screen2, tools1, tools2, ib);
	// Blue and red is switch using check
	if (inputs.IsSwitchUsingBlue)
	{
		screen1.Blue1Sprite.SwitchUsingSprite(screen1.Blue2Sprite);
		screen2.Blue1Sprite.SwitchUsingSprite(screen2.Blue2Sprite);
	}
	if (inputs.IsSwitchUsingRed)
	{
		screen2.Red1Sprite.SwitchUsingSprite(screen2.Red2Sprite);
		screen1.Red1Sprite.SwitchUsingSprite(screen1.Red2Sprite);
	}

	// Blue Inputs
	if (inputs.BlueInput == Sprite::Input::Up)
	{
		screen1.Blue1Sprite.Direction = Sprite::Up;
		screen1.Blue2Sprite.Direction = Sprite::Up;
		screen2.Blue1Sprite.Direction = Sprite::Down;
		screen2.Blue2Sprite.Direction = Sprite::Down;
	}
	else if (inputs.BlueInput == Sprite::Input::Down)
	{
		screen1.Blue1Sprite.Direction = Sprite::Down;
		screen1.Blue2Sprite.Direction = Sprite::Down;
		screen2.Blue1Sprite.Direction = Sprite::Up;
		screen2.Blue2Sprite.Direction = Sprite::Up;
	}
	else if (inputs.BlueInput == Sprite::Input::Left)
	{
		screen1.Blue1Sprite.Direction = Sprite::Left;
		screen1.Blue2Sprite.Direction = Sprite::Left;
		screen2.Blue1Sprite.Direction = Sprite::Right;
		screen2.Blue2Sprite.Direction = Sprite::Right;
	}
	else if (inputs.BlueInput == Sprite::Input::Right)
	{
		screen1.Blue1Sprite.Direction = Sprite::Right;
		screen1.Blue2Sprite.Direction = Sprite::Right;
		screen2.Blue1Sprite.Direction = Sprite::Left;
		screen2.Blue2Sprite.Direction = Sprite::Left;
	}

	// Red Inputs
	if (inputs.RedInput == Sprite::Input::Up)
	{
		screen2.Red1Sprite.Direction = Sprite::Up;
		screen2.Red2Sprite.Direction = Sprite::Up;
		screen1.Red1Sprite.Direction = Sprite::Down;
		screen1.Red2Sprite.Direction = Sprite::Down;
	}
	else if (inputs.RedInput == Sprite::Input::Down)
	{
		screen2.Red1Sprite.Direction = Sprite::Down;
		screen2.Red2Sprite.Direction = Sprite::Down;
		screen1.Red1Sprite.Direction = Sprite::Up;
		screen1.Red2Sprite.Direction = Sprite::Up;
	}
	else if (inputs.RedInput == Sprite::Input::Left)
	{
		screen2.Red1Sprite.Direction = Sprite::Left;
		screen2.Red2Sprite.Direction = Sprite::Left;
		screen1.Red1Sprite.Direction = Sprite::Right;
		screen1.Red2Sprite.Direction = Sprite::Right;
	}
	else if (inputs.RedInput == Sprite::Input::Right)
	{
		screen2.Red1Sprite.Direction = Sprite::Right;
		screen2.Red2Sprite.Direction = Sprite::Right;
		screen1.Red1Sprite.Direction = Sprite::Left;
		screen1.Red2Sprite.Direction = Sprite::Left;
	}

	if (who_died == None || who_died == Red)
	{
		screen1.Blue1Sprite.Move(screen1.Blue1Sprite.Direction, screen1.Blue1Sprite.IsUsing);
		screen1.Blue2Sprite.Move(screen1.Blue2Sprite.Direction, screen1.Blue2Sprite.IsUsing);
		screen2.Blue1Sprite.Move(screen2.Blue1Sprite.Direction, screen2.Blue1Sprite.IsUsing);
		screen2.Blue2Sprite.Move(screen2.Blue2Sprite.Direction, screen2.Blue2Sprite.IsUsing);
	}
	if (who_died == None || who_died == Blue)
	{
		screen1.Red1Sprite.Move(screen1.Red1Sprite.Direction, screen1.Red1Sprite.IsUsing);
		screen1.Red2Sprite.Move(screen1.Red2Sprite.Direction, screen1.Red2Sprite.IsUsing);
		screen2.Red1Sprite.Move(screen2.Red1Sprite.Direction, screen2.Red1Sprite.IsUsing);
		screen2.Red2Sprite.Move(screen2.Red2Sprite.Direction, screen2.Red2Sprite.IsUsing);
	}
}

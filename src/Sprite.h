#pragma once
#include "Matrix.h"
struct TwoPlayerWhoDies
{
	bool WillFirstDie;
	bool WillSecondDie;
};

class Sprite
{
public:
	bool IsAlive = true;
	int DeathCountdown = 5;
	const enum ScreenPos {LeftScreen, RightScreen};
	const enum Input { None, Up, Down, Left, Right, Break};
	const enum SpriteType {BLUE_USING_SPRITE, RED_USING_SPRITE, BLUE_SPRITE, RED_SPRITE, ZOMBIE_LEFT, ZOMBIE_RIGHT, ZOMBIE_EATING_LEFT, ZOMBIE_EATING_RIGHT};
	const int MaxXCoords = 15;
	const int MinXCoords = 0;
	const int MaxYCoords = 9;
	const int MinYCoords = 0;
	int xCoords, yCoords;
	Sprite();
	~Sprite();
	int GetX();
	int GetY();
	void SetXCoords(int coords);
	void SetYCoords(int coords);
	void SetXYCoords(int x_coords, int y_coords);
	bool IsXOutOfScreen(int coords);
	bool IsYOutOfScreen(int coords);
	bool IsCovered(Sprite AnotherSprite);
	void Move(Input Direction, bool IsUsing);
};

class BlueScreenOneSprite : public Sprite
{
private:
	MatrixScreenOne matrix;
public:
	unsigned int m_RendererID;
	bool IsUsing;
	Input LastMove;
	Input Direction;
	BlueScreenOneSprite(unsigned int RendererID, Input Direction, bool is_using, int x_coords, int y_coords);
	~BlueScreenOneSprite();
	SpriteType GetSpriteType();
	void ChangeMatrixTexture();
	void SwitchUsingSprite(BlueScreenOneSprite& AnotherSprite);
};

class RedScreenOneSprite : public Sprite
{
private:
	MatrixScreenOne matrix;
public:
	unsigned int m_RendererID;
	bool IsUsing;
	Input LastMove;
	Input Direction;
	RedScreenOneSprite(unsigned int RendererID, Input Direction, bool is_using, int x_coords, int y_coords);
	~RedScreenOneSprite();
	SpriteType GetSpriteType();
	void ChangeMatrixTexture();
	void SwitchUsingSprite(RedScreenOneSprite& AnotherSprite);
};

class BlueScreenTwoSprite : public Sprite
{
private:
	MatrixScreenTwo matrix;
public:
	unsigned int m_RendererID;
	bool IsUsing;
	Input LastMove;
	Input Direction;
	BlueScreenTwoSprite(unsigned int RendererID, Input Direction, bool is_using, int x_coords, int y_coords);
	~BlueScreenTwoSprite();
	SpriteType GetSpriteType();
	void ChangeMatrixTexture();
	void SwitchUsingSprite(BlueScreenTwoSprite& AnotherSprite);
};

class RedScreenTwoSprite : public Sprite
{
private:
	MatrixScreenTwo matrix;
public:
	unsigned int m_RendererID;
	bool IsUsing;
	Input LastMove;
	Input Direction;
	RedScreenTwoSprite(unsigned int RendererID, Input Direction, bool is_using, int x_coords, int y_coords);
	~RedScreenTwoSprite();
	SpriteType GetSpriteType();
	void ChangeMatrixTexture();
	void SwitchUsingSprite(RedScreenTwoSprite& AnotherSprite);
};

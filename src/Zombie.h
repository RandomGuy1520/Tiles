#pragma once
#include "Matrix.h"
#include "Sprite.h"
#include "Texture.h"
#include <random>

class ZombieScreenOne : public Sprite
{
private:
	SpriteType type;
public:
	bool NeedToReset = false;
	int InitX, InitY;
	int xCoords, yCoords;
	enum Directions {EAT, UP, DOWN, LEFT, RIGHT};
	Directions Last_Direction;
	ZombieScreenOne(int x_coords, int y_coords, SpriteType sprite_type);
	~ZombieScreenOne();
	int GetX();
	int GetY();
	void Reset();
	void Move(Directions Direction);
	int randint(int start_num, int end_num);
	SpriteType GetSpriteType();
	void MakeRandomMove(MatrixScreenOne& matrix);
};

class ZombieScreenTwo : public Sprite // Union with ZombieScreenOne but 180 degree reversed
{
public:
	ZombieScreenOne* Zombie;
	enum Directions { UP, DOWN, LEFT, RIGHT };
	ZombieScreenTwo(ZombieScreenOne* zombie);
	~ZombieScreenTwo();
	int GetX();
	int GetY();
	SpriteType GetSpriteType();
	void RefreshMatrix(MatrixScreenTwo& matrix);
};

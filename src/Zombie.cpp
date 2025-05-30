#include "Zombie.h"

ZombieScreenOne::ZombieScreenOne(int x_coords, int y_coords, SpriteType sprite_type)
	: InitX(x_coords), InitY(y_coords), xCoords(x_coords), yCoords(y_coords), type(sprite_type) {}
ZombieScreenOne::~ZombieScreenOne() {}

int ZombieScreenOne::GetX()
{
	return xCoords;
}

int ZombieScreenOne::GetY()
{
	return yCoords;
}

void ZombieScreenOne::Reset()
{
	if (NeedToReset)
	{
		xCoords = InitX;
		yCoords = InitY;
	}
}

void ZombieScreenOne::Move(Directions Direction)
{
	if (Direction == UP && !IsYOutOfScreen(yCoords + 1))
		yCoords++;
	else if (Direction == DOWN && !IsYOutOfScreen(yCoords - 1))
		yCoords--;
	else if (Direction == LEFT && !IsXOutOfScreen(xCoords - 1))
		xCoords--;
	else if (Direction == RIGHT && !IsXOutOfScreen(xCoords + 1))
		xCoords++;
}

int ZombieScreenOne::randint(int start_num, int end_num)
{
	using namespace std;
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(start_num, end_num);
	return dist(mt);
}

Sprite::SpriteType ZombieScreenOne::GetSpriteType()
{
	return type;
}

void ZombieScreenOne::MakeRandomMove(MatrixScreenOne& matrix)
{
	if (matrix.GetTextureType(xCoords, yCoords) == matrix.WHITE_TEXTURE)
	{
		Directions random_direction = (Directions)(randint(1, 4)); // 1 or 2 or 3 or 4, Anything
		if (xCoords == 0 && yCoords == 0)
			random_direction = (Directions)(randint(1, 2) * 3 - 2); // 1 or 4, Up or Right
		else if (xCoords == 0 && yCoords == 9)
			random_direction = (Directions)(randint(1, 2) * 2); // 2 or 4, Down or Right
		else if (xCoords == 15 && yCoords == 0)
			random_direction = (Directions)(randint(1, 2) * 2 - 1); // 1 or 3, Up or Left
		else if (xCoords == 15 && yCoords == 9)
			random_direction = (Directions)(randint(2, 3)); // 2 or 3, Down or Left
		else if (xCoords == 0)
		{
			if (random_direction == (Directions)(3))
				random_direction = (Directions)(4); // 1 or 2 or 4, Up or Down or Right
		}
		else if (xCoords == 15)
		{
			if (random_direction == (Directions)(4))
				random_direction = (Directions)(3); // 1 or 2 or 4, Up or Down or Right
		}
		else if (yCoords == 0)
		{
			if (random_direction == (Directions)(2))
				random_direction = (Directions)(1); // 1 or 3 or 4, Up or Left or Right
		}
		else if (yCoords == 9)
		{
			if (random_direction == (Directions)(1))
				random_direction = (Directions)(2); // 1 or 2 or 4, Up or Down or Right
		}
		Last_Direction = random_direction;
		Move(random_direction);
		if (type == ZOMBIE_EATING_LEFT)
			type = ZOMBIE_LEFT;
		else if (type == ZOMBIE_EATING_RIGHT)
			type = ZOMBIE_RIGHT;
	}
	else
	{
		matrix.SetTextureType(xCoords, yCoords, matrix.WHITE_TEXTURE);
		Last_Direction = EAT;
		if (type == ZOMBIE_LEFT)
			type = ZOMBIE_EATING_LEFT;
		if (type == ZOMBIE_RIGHT)
			type = ZOMBIE_EATING_RIGHT;
	}
}

ZombieScreenTwo::ZombieScreenTwo(ZombieScreenOne* zombie)
	: Zombie(zombie) {}

ZombieScreenTwo::~ZombieScreenTwo()
{

}

int ZombieScreenTwo::GetX()
{
	return 15 - Zombie->GetX();
}

int ZombieScreenTwo::GetY()
{
	return 9 - Zombie->GetY();
}

Sprite::SpriteType ZombieScreenTwo::GetSpriteType()
{
	if (Zombie->GetSpriteType() == Sprite::ZOMBIE_EATING_LEFT)
		return ZOMBIE_EATING_RIGHT;
	else if (Zombie->GetSpriteType() == Sprite::ZOMBIE_EATING_RIGHT)
		return ZOMBIE_EATING_LEFT;
	else if (Zombie->GetSpriteType() == Sprite::ZOMBIE_LEFT)
		return ZOMBIE_RIGHT;
	else if (Zombie->GetSpriteType() == Sprite::ZOMBIE_RIGHT)
		return ZOMBIE_LEFT;
}

void ZombieScreenTwo::RefreshMatrix(MatrixScreenTwo& matrix)
{
	if (GetSpriteType() == Sprite::ZOMBIE_EATING_LEFT || GetSpriteType() == Sprite::ZOMBIE_EATING_RIGHT)
		matrix.SetTextureType(GetX(), GetY(), matrix.WHITE_TEXTURE);
}

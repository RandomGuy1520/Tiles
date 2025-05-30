#include "Sprite.h"

// All sprites

Sprite::Sprite() {}

Sprite::~Sprite() {}

void Sprite::SetXCoords(int coords)
{
	xCoords = coords;
}

void Sprite::SetYCoords(int coords)
{
	xCoords = coords;
}

void Sprite::SetXYCoords(int x_coords, int y_coords)
{
	xCoords = x_coords;
	yCoords = y_coords;
}

bool Sprite::IsXOutOfScreen(int coords)
{
	if (coords > MaxXCoords || coords < MinXCoords)
		return true;
	else
		return false;
}

bool Sprite::IsYOutOfScreen(int coords)
{
	if (coords > MaxYCoords || coords < MinYCoords)
		return true;
	else
		return false;
}

int Sprite::GetX()
{
	return xCoords;
}

int Sprite::GetY()
{
	return yCoords;
}

bool Sprite::IsCovered(Sprite AnotherSprite)
{
	if (xCoords == AnotherSprite.xCoords && yCoords == AnotherSprite.yCoords)
		return true;
	else
		return false;
}

void Sprite::Move(Input Direction, bool IsUsing)
{
	if (!IsAlive) {}
	else if (Direction == Up && !IsYOutOfScreen(yCoords + 1) && IsUsing)
		yCoords++;
	else if (Direction == Down && !IsYOutOfScreen(yCoords - 1) && IsUsing)
		yCoords--;
	else if (Direction == Left && !IsXOutOfScreen(xCoords - 1) && IsUsing)
		xCoords--;
	else if (Direction == Right && !IsXOutOfScreen(xCoords + 1) && IsUsing)
		xCoords++;
}

// Blue Screen One Sprite

BlueScreenOneSprite::BlueScreenOneSprite(unsigned int RendererID, Input input, bool is_using, int x_coords, int y_coords)
	: m_RendererID(RendererID), IsUsing(is_using), Direction(input)
{
	SetXYCoords(x_coords, y_coords);
}

BlueScreenOneSprite::~BlueScreenOneSprite() {}

Sprite::SpriteType BlueScreenOneSprite::GetSpriteType()
{
	if (IsUsing)
		return BLUE_USING_SPRITE;
	else
		return BLUE_SPRITE;
}

void BlueScreenOneSprite::ChangeMatrixTexture()
{
	matrix.SetTextureType(xCoords, yCoords, matrix.BLUE_TEXTURE);
}

void BlueScreenOneSprite::SwitchUsingSprite(BlueScreenOneSprite& AnotherSprite)
{
	bool this_sprite_is_using;

	// The three-wheel change
	this_sprite_is_using = IsUsing;
	IsUsing = AnotherSprite.IsUsing;
	AnotherSprite.IsUsing = this_sprite_is_using;
}

// Red Screen One Sprite

RedScreenOneSprite::RedScreenOneSprite(unsigned int RendererID, Input input, bool is_using, int x_coords, int y_coords)
	: m_RendererID(RendererID), IsUsing(is_using), Direction(input)
{
	SetXYCoords(x_coords, y_coords);
}

RedScreenOneSprite::~RedScreenOneSprite() {}

Sprite::SpriteType RedScreenOneSprite::GetSpriteType()
{
	if (IsUsing)
		return RED_USING_SPRITE;
	else
		return RED_SPRITE;
}

void RedScreenOneSprite::ChangeMatrixTexture()
{
	matrix.SetTextureType(xCoords, yCoords, matrix.RED_TEXTURE);

}

void RedScreenOneSprite::SwitchUsingSprite(RedScreenOneSprite& AnotherSprite)
{
	bool this_sprite_is_using;

	// The three-wheel change
	this_sprite_is_using = IsUsing;
	IsUsing = AnotherSprite.IsUsing;
	AnotherSprite.IsUsing = this_sprite_is_using;
}

// Blue Screen Two Sprite

BlueScreenTwoSprite::BlueScreenTwoSprite(unsigned int RendererID, Input input, bool is_using, int x_coords, int y_coords)
	: m_RendererID(RendererID), IsUsing(is_using), Direction(input)
{
	SetXYCoords(x_coords, y_coords);
}

BlueScreenTwoSprite::~BlueScreenTwoSprite() {}

Sprite::SpriteType BlueScreenTwoSprite::GetSpriteType()
{
	if (IsUsing)
		return BLUE_USING_SPRITE;
	else
		return BLUE_SPRITE;
}

void BlueScreenTwoSprite::ChangeMatrixTexture()
{
	matrix.SetTextureType(xCoords, yCoords, matrix.BLUE_TEXTURE);
}

void BlueScreenTwoSprite::SwitchUsingSprite(BlueScreenTwoSprite& AnotherSprite)
{
	bool this_sprite_is_using;

	// The three-wheel change
	this_sprite_is_using = IsUsing;
	IsUsing = AnotherSprite.IsUsing;
	AnotherSprite.IsUsing = this_sprite_is_using;
}

// Red Screen Two Sprite

RedScreenTwoSprite::RedScreenTwoSprite(unsigned int RendererID, Input input, bool is_using, int x_coords, int y_coords)
	: m_RendererID(RendererID), IsUsing(is_using), Direction(input)
{
	SetXYCoords(x_coords, y_coords);
}

RedScreenTwoSprite::~RedScreenTwoSprite() {}

Sprite::SpriteType RedScreenTwoSprite::GetSpriteType()
{
	if (IsUsing)
		return RED_USING_SPRITE;
	else
		return RED_SPRITE;
}

void RedScreenTwoSprite::ChangeMatrixTexture()
{
	matrix.SetTextureType(xCoords, yCoords, matrix.RED_TEXTURE);
}

void RedScreenTwoSprite::SwitchUsingSprite(RedScreenTwoSprite& AnotherSprite)
{
	bool this_sprite_is_using;

	// The three-wheel change
	this_sprite_is_using = IsUsing;
	IsUsing = AnotherSprite.IsUsing;
	AnotherSprite.IsUsing = this_sprite_is_using;
}

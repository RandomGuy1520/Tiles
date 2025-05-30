#pragma once
#include "IndexBuffer.h"
#include "Texture.h"

class MatrixScreen
{
public:
    enum TextureType { BLUE_TEXTURE, RED_TEXTURE, WHITE_TEXTURE };
    const float ppt = 50;
    float TexturePos[16][10][16];
    TextureType TextureTypes[16][10];
    void SetTextureType(int x, int y, TextureType type)
    {
        TextureTypes[x][y] = type;
    }
    TextureType GetTextureType(int x, int y)
    {
        return TextureTypes[x][y];
    }
    int CountBlueTiles()
    {
        int count = 0;
        for (int x = 0; x < 16; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                if (TextureTypes[x][y] == BLUE_TEXTURE)
                    count++;
            }
        }
        return count;
    }
    int CountRedTiles()
    {
        int count = 0;
        for (int x = 0; x < 16; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                if (TextureTypes[x][y] == RED_TEXTURE)
                    count++;
            }
        }
        return count;
    }
};
class MatrixScreenOne : public MatrixScreen
{
private:
    const float ScreenX = 90;
    const float ScreenY = 260;
public:
    MatrixScreenOne()
    {
        for (int x = 0; x < 16; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                float positions[16] = {
                    ScreenX + ppt * x  , ScreenY + ppt * y  , 0.0f, 0.0f,
                    ScreenX + ppt * (x + 1), ScreenY + ppt * y  , 1.0f, 0.0f,
                    ScreenX + ppt * (x + 1), ScreenY + ppt * (y + 1), 1.0f, 1.0f,
                    ScreenX + ppt * x  , ScreenY + ppt * (y + 1), 0.0f, 1.0f
                };
                for (int i = 0; i < 16; i++)
                {
                    TexturePos[x][y][i] = positions[i];
                }
            }
        }
        for (int x = 0; x < 16; x++)
        {
            for (int y = 0; y < 10; y++)
                SetTextureType(x, y, WHITE_TEXTURE);
        }
    }
    ~MatrixScreenOne() {}
};

class MatrixScreenTwo : public MatrixScreen
{
private:
    const float ScreenX = 1030;
    const float ScreenY = 260;
public:
    MatrixScreenTwo()
    {
        for (int x = 0; x < 16; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                float positions[16] = {
                    ScreenX + ppt * x  , ScreenY + ppt * y  , 0.0f, 0.0f,
                    ScreenX + ppt * (x + 1), ScreenY + ppt * y  , 1.0f, 0.0f,
                    ScreenX + ppt * (x + 1), ScreenY + ppt * (y + 1), 1.0f, 1.0f,
                    ScreenX + ppt * x  , ScreenY + ppt * (y + 1), 0.0f, 1.0f
                };
                for (int i = 0; i < 16; i++)
                {
                    TexturePos[x][y][i] = positions[i];
                }
            }
        }
        for (int x = 0; x < 16; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                SetTextureType(x, y, WHITE_TEXTURE);
            }
        }
    }
    ~MatrixScreenTwo() {}
};

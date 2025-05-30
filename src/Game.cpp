#include "Includes.h"

int main(void)
{
    bool IsPlaying = true;
    std::string PlayAgain;
    std::string winner = "None";
    const int WindowLength = 1920;
    const int WindowWidth = 994;
    const unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    const glm::mat4 proj = glm::ortho(0.0f, (float)WindowLength, 0.0f, (float)WindowWidth, -1.0f, 1.0f);
    Window GameWindow(WindowLength, WindowWidth, "Tiles!");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (IsPlaying)
    {
        GLFWwindow* window = GameWindow.CreateGameWindow();
        {
            ScreenOne screen1;
            ScreenTwo screen2(screen1);
            GLTools tools1;
            GLTools tools2;
            IndexBuffer ib(indices, 6);
            Shader shader("D:/VSProject/Tiles/res/shaders/Basic.shader");
            Texture BlueUsingSprite("D:/VSProject/Tiles/res/textures/Sprites/BlueUsingSprite.png");
            Texture RedUsingSprite("D:/VSProject/Tiles/res/textures/Sprites/RedUsingSprite.png");
            Texture BlueSprite("D:/VSProject/Tiles/res/textures/Sprites/BlueSprite.png");
            Texture RedSprite("D:/VSProject/Tiles/res/textures/Sprites/RedSprite.png");
            Texture BlueTexture("D:/VSProject/Tiles/res/textures/Textures/BlueTexture.png");
            Texture RedTexture("D:/VSProject/Tiles/res/textures/Textures/RedTexture.png");
            Texture WhiteTexture("D:/VSProject/Tiles/res/textures/Textures/WhiteTexture.png");
            Texture ZombieLeft("D:/VSProject/Tiles/res/textures/Zombies/ZombieLeft.png");
            Texture ZombieRight("D:/VSProject/Tiles/res/textures/Zombies/ZombieRight.png");
            Texture ZombieEatingLeft("D:/VSProject/Tiles/res/textures/Zombies/ZombieEatingLeft.png");
            Texture ZombieEatingRight("D:/VSProject/Tiles/res/textures/Zombies/ZombieEatingRight.png");
            Texture BlueWon("D:/VSProject/Tiles/res/textures/Winner/BlueWon.png");
            Texture RedWon("D:/VSProject/Tiles/res/textures/Winner/RedWon.png");
            Texture Line("D:/VSProject/Tiles/res/textures/Textures/Line.png");
            Texture Textures[] = { BlueTexture, RedTexture, WhiteTexture };
            Texture Sprites[] = { BlueUsingSprite, RedUsingSprite, BlueSprite, RedSprite, ZombieLeft, ZombieRight, ZombieEatingLeft, ZombieEatingRight };
            std::thread MusicStartThread(PlayGameMusic);
            while (true)
            {
                // Init
                shader.Bind();
                shader.SetUniformsMat4f("u_MVP", proj);
                glClear(GL_COLOR_BUFFER_BIT);

                // Draw Tiles
                for (int x = 0; x < 16; x++)
                {
                    for (int y = 0; y < 10; y++)
                    {
                        Draw(screen1, tools1, ib, Textures[screen1.matrix.GetTextureType(x, y)], x, y);
                        Draw(screen2, tools2, ib, Textures[screen2.matrix.GetTextureType(x, y)], x, y);
                    }
                }
                // Draw Background
                DrawSquareXY(screen1, tools1, ib, BlueTexture, 415, 810, 150);
                DrawSquareXY(screen2, tools2, ib, RedTexture, 1355, 810, 150);

                // Draw Sprites
                screen1.matrix.TextureTypes[screen1.Blue1Sprite.GetX()][screen1.Blue1Sprite.GetY()] = MatrixScreen::BLUE_TEXTURE;
                screen1.matrix.TextureTypes[screen1.Blue2Sprite.GetX()][screen1.Blue2Sprite.GetY()] = MatrixScreen::BLUE_TEXTURE;
                screen1.matrix.TextureTypes[screen1.Red1Sprite.GetX()][screen1.Red1Sprite.GetY()] = MatrixScreen::RED_TEXTURE;
                screen1.matrix.TextureTypes[screen1.Red2Sprite.GetX()][screen1.Red2Sprite.GetY()] = MatrixScreen::RED_TEXTURE;
                screen2.matrix.TextureTypes[screen2.Red1Sprite.GetX()][screen2.Red1Sprite.GetY()] = MatrixScreen::RED_TEXTURE;
                screen2.matrix.TextureTypes[screen2.Red2Sprite.GetX()][screen2.Red2Sprite.GetY()] = MatrixScreen::RED_TEXTURE;
                screen2.matrix.TextureTypes[screen2.Blue1Sprite.GetX()][screen2.Blue1Sprite.GetY()] = MatrixScreen::BLUE_TEXTURE;
                screen2.matrix.TextureTypes[screen2.Blue2Sprite.GetX()][screen2.Blue2Sprite.GetY()] = MatrixScreen::BLUE_TEXTURE;
                Draw(screen1, tools1, ib, Sprites[screen1.Blue1Sprite.GetSpriteType()], screen1.Blue1Sprite.GetX(), screen1.Blue1Sprite.GetY());
                Draw(screen1, tools1, ib, Sprites[screen1.Blue2Sprite.GetSpriteType()], screen1.Blue2Sprite.GetX(), screen1.Blue2Sprite.GetY());
                Draw(screen1, tools1, ib, Sprites[screen1.Red1Sprite.GetSpriteType()], screen1.Red1Sprite.GetX(), screen1.Red1Sprite.GetY());
                Draw(screen1, tools1, ib, Sprites[screen1.Red2Sprite.GetSpriteType()], screen1.Red2Sprite.GetX(), screen1.Red2Sprite.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Blue1Sprite.GetSpriteType()], screen2.Blue1Sprite.GetX(), screen2.Blue1Sprite.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Blue2Sprite.GetSpriteType()], screen2.Blue2Sprite.GetX(), screen2.Blue2Sprite.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Red1Sprite.GetSpriteType()], screen2.Red1Sprite.GetX(), screen2.Red1Sprite.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Red2Sprite.GetSpriteType()], screen2.Red2Sprite.GetX(), screen2.Red2Sprite.GetY());

                // Display Tiles Number
                DisplayTilesNum(screen1, tools1, ib, screen1.matrix.CountBlueTiles(), 382, 80, 606, 230);
                DisplayTilesNum(screen2, tools2, ib, screen1.matrix.CountRedTiles(), 1322, 80, 1546, 230);
                DrawXY(screen1, tools1, ib, Line, 0, 508, 1920, 508 + Line.GetHeight());

                // Draw Zombies
                Draw(screen1, tools1, ib, Sprites[screen1.Zombie1.GetSpriteType()], screen1.Zombie1.GetX(), screen1.Zombie1.GetY());
                Draw(screen1, tools1, ib, Sprites[screen1.Zombie2.GetSpriteType()], screen1.Zombie2.GetX(), screen1.Zombie2.GetY());
                Draw(screen1, tools1, ib, Sprites[screen1.Zombie3.GetSpriteType()], screen1.Zombie3.GetX(), screen1.Zombie3.GetY());
                Draw(screen1, tools1, ib, Sprites[screen1.Zombie4.GetSpriteType()], screen1.Zombie4.GetX(), screen1.Zombie4.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Zombie1.GetSpriteType()], screen2.Zombie1.GetX(), screen2.Zombie1.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Zombie2.GetSpriteType()], screen2.Zombie2.GetX(), screen2.Zombie2.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Zombie3.GetSpriteType()], screen2.Zombie3.GetX(), screen2.Zombie3.GetY());
                Draw(screen2, tools2, ib, Sprites[screen2.Zombie4.GetSpriteType()], screen2.Zombie4.GetX(), screen2.Zombie4.GetY());

                // Draw If Sprite Dies
                DrawYouDied(screen1, tools1, ib, screen1.Blue1Sprite.IsAlive, screen1.Blue1Sprite.DeathCountdown);
                DrawYouDied(screen1, tools1, ib, screen1.Blue2Sprite.IsAlive, screen1.Blue2Sprite.DeathCountdown);
                DrawYouDied(screen2, tools2, ib, screen2.Red1Sprite.IsAlive, screen2.Red1Sprite.DeathCountdown);
                DrawYouDied(screen2, tools2, ib, screen2.Red2Sprite.IsAlive, screen2.Red2Sprite.DeathCountdown);

                glfwSwapBuffers(window);
                glfwPollEvents();
                if (screen1.matrix.CountBlueTiles() >= GameWindow.WinTilesNum)
                {
                    winner = "Blue";
                    DrawXY(screen1, tools1, ib, BlueWon, 710, 385, 710 + BlueWon.GetWidth(), 385 + BlueWon.GetHeight());
                    PlaySound(TEXT("D:/VSProject/Tiles/res/music/WinnerMusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    glfwSwapBuffers(window);
                    glfwPollEvents();
                    break;
                }
                else if (screen1.matrix.CountRedTiles() >= GameWindow.WinTilesNum)
                {
                    winner = "Red";
                    DrawXY(screen1, tools1, ib, RedWon, 710, 385, 710 + RedWon.GetWidth(), 385 + RedWon.GetHeight());
                    PlaySound(TEXT("D:/VSProject/Tiles/res/music/WinnerMusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    glfwSwapBuffers(window);
                    glfwPollEvents();
                    Sleep(3000);
                    break;
                }

                Inputs input = GetInput(window);
                if (input.BlueInput == Sprite::Input::Break)
                    break;
                Move(screen1, screen2, tools1, tools2, ib, input);
                screen1.Zombie1.Reset();
                screen1.Zombie2.Reset();
                screen1.Zombie3.Reset();
                screen1.Zombie4.Reset();

                if (!screen1.Zombie1.NeedToReset)
                    screen1.Zombie1.MakeRandomMove(screen1.matrix); // Already Union-ed with screen2.Zombies
                if (!screen1.Zombie2.NeedToReset)
                    screen1.Zombie2.MakeRandomMove(screen1.matrix);
                if (!screen1.Zombie3.NeedToReset)
                    screen1.Zombie3.MakeRandomMove(screen1.matrix);
                if (!screen1.Zombie4.NeedToReset)
                    screen1.Zombie4.MakeRandomMove(screen1.matrix);
                screen2.Zombie1.RefreshMatrix(screen2.matrix); // Just need to refresh the matrix
                screen2.Zombie2.RefreshMatrix(screen2.matrix);
                screen2.Zombie3.RefreshMatrix(screen2.matrix);
                screen2.Zombie4.RefreshMatrix(screen2.matrix);
                screen1.Zombie1.NeedToReset = false;
                screen1.Zombie2.NeedToReset = false;
                screen1.Zombie3.NeedToReset = false;
                screen1.Zombie4.NeedToReset = false;
            }
            stopGameMusic = true;
            MusicStartThread.join();
            stopGameMusic = false;
            shader.Unbind();
            ib.Unbind();
            tools1.va.Unbind();
            tools1.vb.Unbind();
            tools2.va.Unbind();
            tools2.vb.Unbind();
        }
        glfwDestroyWindow(window);
        if (winner == "Blue")
            std::cout << "\nCongratulations, BLUE WON THE GAME!!!!\n恭喜你，蓝方赢了！！！！";
        else if (winner == "Red")
            std::cout << "\nCongratulations, RED WON THE GAME!!!!\n恭喜你，红方赢了！！！！";
        else
            std::cout << "\nGame Closed. Nobody won the game.\n游戏被关闭，没有人获胜。";
        std::cout << "\n\nDo you want to play again? Enter 'yes' play again, enter 'no' otherwise.\n你想再玩一遍吗？想的话，请输入'想'，否则输入'不想'。\n";
        std::cin >> PlayAgain;
        while (!(to_lower(PlayAgain) == "yes" || to_lower(PlayAgain) == "no" || PlayAgain == "想" || PlayAgain == "不想")) { std::cin >> PlayAgain; }
        if (to_lower(PlayAgain) == "no" || PlayAgain == "不想")
        {
            IsPlaying = false;
            std::cout << "\nWelcome to play Tiles again next time! Bye!\n欢迎下次再玩Tiles！拜拜！";
            Sleep(3000);
        }
    }
    return 0;
}

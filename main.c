/**
 * \file main.c
 * \brief Main application file of Space Type
 * \details retro-interface typing trainer and game to help boost your typing speed. This project takes its
 * inspration from Typeshala, Ztype and aims for the feels similar to retro-console space games
 * like Space Invadors.
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * \author Praharsha Adhikari <078bct061.praharsha@pcampus.edu.np>
 * \author Mukunda Dev Adhikari <078bct049.mukunda@pcampus.edu.np>
 * \author Pragalbha Acharya <078bct049.pragalbha@pcampus.edu.np>
 * \bug: No known Bug.
 */

/* -- Includes -- */
/* Including other C files and header files of this code*/
#include "spacetype_game.h"	 /*header file for game mode*/
#include "spacetype_game.c"	 /*C file for game mode*/
#include "spacetype_train.h" /*header file for train mode*/
#include "spacetype_train.c" /*C file for train mode*/
#include "spacetype_test.h"	 /*header file for test mode*/
#include "spacetype_test.c"	 /*C file for test mode*/

/**
 * @{ \name Main application variables
 */
FILE *wrongChars;		 //!< To store mispressed characters to use in customized train mode
int screenWidth;		 //!< screen width for graphical operations
int screenHeight;		 //!< screen height for graphical operations
bool exitWindow = false; //!< To govern main application loop
bool exitGame = false;	 //!< To govern game mode loop
bool sorted;			 //!< to check if the WrongChars.txt is sorted or not
/**
 * @}
 */

/**
 * @{ \name Main interface variables
 * Different textures for the main screen and hover, and other graphical components.
 */

Texture2D cockpitTexture, cockpitTextureTrain, cockpitTextureTest, cockpitTextureGame, cockpitTextureExit; //!< Main menu textures
Font retroFont, regularFont;																			   //!< Main application fonts
Texture2D qwertyTexture;																				   //!< keyboard image for tutorial screen
/**
 * @}
 */

/**
 * \brief Main function of the application
 *
 * \details Initializes Screen and audio device. Loads music, fonts
 * and textures. Plays the music, calls the respective function to draw
 * the background and menu.
 *
 */
int main()
{
	InitWindow(1366, 768, "Space Type");
	ToggleFullscreen();
	InitAudioDevice(); // Initialize audio device
	SetTargetFPS(60);

	// Loading Textures which are used in all modes throught the application
	spaceTexture = LoadTexture("resources/images/space_texture.png");
	cockpitTexture = LoadTexture("resources/images/cockpit_texture.png");
	spaceshipTexture = LoadTexture("resources/images/spaceship_texture.png");
	bulletTexture = LoadTexture("resources/images/bullet_texture.png");
	qwertyTexture = LoadTexture("resources/images/qwerty.png");
	cockpitTextureTrain = LoadTexture("resources/images/cockpit_texture_train.png");
	cockpitTextureTest = LoadTexture("resources/images/cockpit_texture_test.png");
	cockpitTextureKeyboard = LoadTexture("resources/images/cockpit_texture_keyboard.png");
	cockpitTextureGame = LoadTexture("resources/images/cockpit_texture_game.png");
	cockpitTextureExit = LoadTexture("resources/images/cockpit_texture_exit.png");
	planetTextures[0] = LoadTexture("resources/images/planet1_texture.png");
	planetTextures[1] = LoadTexture("resources/images/planet2_texture.png");
	planetTextures[2] = LoadTexture("resources/images/planet3_texture.png");
	// Loading default font for the application
	retroFont = LoadFont("resources/fonts/retro_font.otf");
	regularFont = LoadFont("resources/fonts/regular_font.otf");
	// Load background music
	music = LoadMusicStream("resources/music/country.mp3");
	PlayMusicStream(music);

	screenWidth = 1366;
	screenHeight = 768;
	scale = ((float)screenWidth) / spaceTexture.width;
	movingDown = 0;
	mover = 0.15f;

	while (!exitWindow)
	{
		UpdateMusicStream(music);
		movingDown += mover;
		movingPlanets += 0.45f;
		BeginDrawing();
		draw_background();
		draw_menu();
		DrawTextEx(retroFont, "SPACE", (Vector2){screenWidth / 2 - 170 + 5, screenHeight / 2 - 200 + 4}, 90, 1, DARKBLUE);
		DrawTextEx(retroFont, "SPACE", (Vector2){screenWidth / 2 - 170, screenHeight / 2 - 200}, 90, 1, WHITE);
		DrawTextEx(retroFont, "TYPE", (Vector2){screenWidth / 2 - 140 + 5, screenHeight / 2 - 90 + 4}, 90, 1, DARKBLUE);
		DrawTextEx(retroFont, "TYPE", (Vector2){screenWidth / 2 - 140, screenHeight / 2 - 90}, 90, 1, WHITE);
		EndDrawing();
	}
	UnloadMusicStream(music);
	CloseWindow();
	UnloadFont(retroFont);
}

/**
 * \brief Draws main menu for the application.
 *
 * \details Draws the main menu of the application by loading the cockpitTexture
 * with mouse control for navigation. Has indicators for hover and
 * mouse click calls the respective function associated with the
 * menu entry.
 */
void draw_menu()
{
	if (!sorted)
	{
		fclose(wrongChars);
		wrongChars = fopen("wrongChars.txt", "a+");
		for (int i = 0; i < 26; i++)
		{
			wrongLetters[i].character = (char)(i + 65);
			wrongLetters[i].count = 0;
		}
		while (!feof(wrongChars))
		{
			char c = fgetc(wrongChars);
			for (int i = 0; i < 26; i++)
			{
				if (c == wrongLetters[i].character)
					wrongLetters[i].count++;
			}
		}
		for (int i = 0; i < 26; i++)
		{
			for (int j = i + 1; j < 26; j++)
			{
				if (wrongLetters[i].count < wrongLetters[j].count)
				{
					struct charCount swap = wrongLetters[i];
					wrongLetters[i] = wrongLetters[j];
					wrongLetters[j] = swap;
				}
			}
		}
		sorted = true;
	}
	if ((float)GetMouseX() >= screenWidth - 50 && (float)GetMouseX() <= screenWidth - 50 + MeasureTextEx(retroFont, "☰", 50, 1).x && (float)GetMouseY() >= 5 && (float)GetMouseY() <= (5 + MeasureTextEx(retroFont, "☰", 50, 1).y))
	{
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50 + 2, -15 + 2}, 50, 1, RED);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50, -15}, 50, 1, BLUE);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50 + 2, -5 + 2}, 50, 1, RED);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50, -5}, 50, 1, BLUE);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50 + 2, 5 + 2}, 50, 1, RED);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50, 5}, 50, 1, BLUE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			EndDrawing();
			tutorial_screen();
		}
	}
	else
	{
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50 - 1, -15 - 1}, 50, 1, WHITE);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50, -15}, 50, 1, (Color){115, 147, 179, 255});
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50 - 1, -5 - 1}, 50, 1, WHITE);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50, -5}, 50, 1, (Color){115, 147, 179, 255});
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50 - 1, 5 - 1}, 50, 1, WHITE);
		DrawTextEx(retroFont, "☰", (Vector2){screenWidth - 50, 5}, 50, 1, (Color){115, 147, 179, 255});
	}
	DrawTextureEx(cockpitTexture, (Vector2){0, 0}, 0, 1, WHITE);
	if ((float)GetMouseX() >= 396 && (float)GetMouseX() <= 640 && (float)GetMouseY() >= 541 && (float)GetMouseY() <= 620)
	{
		DrawTextureEx(cockpitTextureTrain, (Vector2){0, 0}, 0, 1, WHITE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			EndDrawing();
			train();
		}
	}
	if ((float)GetMouseX() >= 735 && (float)GetMouseX() <= 960 && (float)GetMouseY() >= 540 && (float)GetMouseY() <= 600)
	{
		DrawTextureEx(cockpitTextureTest, (Vector2){0, 0}, 0, 1, WHITE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			EndDrawing();
			test();
		}
	}
	if ((float)GetMouseX() >= 275 && (float)GetMouseX() <= 575 && (float)GetMouseY() >= 660 && (float)GetMouseY() <= 750)
	{
		DrawTextureEx(cockpitTextureGame, (Vector2){0, 0}, 0, 1, WHITE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			EndDrawing();
			exitGame = false;
			game();
		}
	}
	if ((float)GetMouseX() >= 785 && (float)GetMouseX() <= 1062 && (float)GetMouseY() >= 650 && (float)GetMouseY() <= 740)
	{
		DrawTextureEx(cockpitTextureExit, (Vector2){0, 0}, 0, 1, WHITE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			exitWindow = true;
	}
}
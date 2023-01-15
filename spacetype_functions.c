/*
█▀ █▀█ ▄▀█ █▀▀ █▀▀   ▀█▀ █▄█ █▀█ █▀▀
▄█ █▀▀ █▀█ █▄▄ ██▄   ░█░ ░█░ █▀▀ ██▄
Created Library Functions
Praharsha Adhikari <078bct061.praharsha@pcampus.edu.np>
SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include <string.h>
#include "spacetype_functions.h"

/*Declaring variables start*/
char fastestWord[20], slowestWord[20], scoreString[50];
int SCORE;
float TIME = 10;
float keysPressed, rightKeysPressed, framesCounterForSession,
    framesCounterForWord, fastestWordFrames, slowestWordFrames;
bool gapMeasured, exitPause = true;
float scale, movingDown, mover;
Texture2D spaceTexture, planetTextures[3], bulletTexture, spaceshipTexture, qwertyTexture, cockpitTextureKeyboard;
/*Declaring variables end*/

/*Declaring extern variables to be used from main start*/
extern int screenWidth, screenHeight;
extern Font retroFont;
extern bool exitGame, sorted;
extern FILE* wrongChars;
/*Declaring extern variables to be used from main end*/


/**
 * remove_firstletter:
 * @word[]: the word sent to have its first letter removed
 */    
void remove_firstletter(char word[])
{
    char newWord[20];
    int i;
    for (i = 0; i < strlen(word); i++)
        newWord[i] = word[i + 1];
    strcpy(word, newWord);
}

/**
 * draw_background:
 * 
 * Draws the infinitely scrolling space background with moving planets.
 */   
void draw_background()
{
    if (movingDown >= spaceTexture.height * scale) movingDown = 0;
    // SPACE BACKGROUND
    DrawTextureEx(spaceTexture, (Vector2){0, -spaceTexture.height * scale + movingDown}, 0, scale, WHITE);
    DrawTextureEx(spaceTexture, (Vector2){0, movingDown}, 0, scale, WHITE);
    DrawTextureEx(spaceTexture, (Vector2){0, spaceTexture.height * scale + movingDown}, 0, scale, WHITE);
    // PLANETS
    DrawTextureEx(planetTextures[0], (Vector2){200 - movingDown * 1.1, -60 + movingDown * 1.1}, 0, 2, WHITE);
    DrawTextureEx(planetTextures[2], (Vector2){1350 - movingDown * 1.1, 200 + movingDown * 1.1}, 0, 2, WHITE);
    DrawTextureEx(planetTextures[1], (Vector2){-80 + movingDown * 2.2, 350 + movingDown * 1.1}, 0, 2, WHITE);
}

/**
 * reset_counter:
 * 
 * Resets all the variables that are used to calculate statistics during word practice and Game mode
 */   
void reset_counter()
{
    mover = 0.15f;
    movingDown = 0;
    strcpy(fastestWord, "NONE");
    strcpy(slowestWord, "NONE");
    strcpy(scoreString, "SCORE: 0");
    TIME = 10;
    SCORE = 0;
    gapMeasured = false;
    keysPressed = 0;
    rightKeysPressed = 0;
    framesCounterForSession = 0;
    framesCounterForWord = 0;
    fastestWordFrames = 2147483647;
    slowestWordFrames = 0;
}

/**
 * pause_screen:
 * 
 * Creates a pause menu when called. Has options to either resume the game or return back to main menu
 */   
void pause_screen()
{
    if (!exitPause)
    {
        BeginDrawing();
        DrawRectangle(0, 0, screenWidth, screenHeight + 10, (Color) {0, 0, 0, 200});
        DrawRectangleGradientV((screenWidth / 2) - 170, (screenHeight / 2) - 180, 340, 380, (Color){14, 22, 36, 225}, BLACK);
        DrawTextPro(retroFont, "PAUSED", (Vector2){(GetScreenWidth() / 2) + 4, (GetScreenHeight() / 2) - 90 + 3}, Vector2Scale(MeasureTextEx(retroFont, "letters", 50, 1), 0.5f), 0, 50, 1, RED);
        DrawTextPro(retroFont, "PAUSED", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) - 90}, Vector2Scale(MeasureTextEx(retroFont, "letters", 50, 1), 0.5f), 0, 50, 1, WHITE);
        if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "resume game", 25, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "resume game", 25, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 35 - MeasureTextEx(retroFont, "letters", 25, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 35 + MeasureTextEx(retroFont, "letters", 25, 1).y / 2))
        {
            DrawTextPro(retroFont, "resume game", (Vector2){(GetScreenWidth() / 2) + 2, (GetScreenHeight() / 2) + 40 + 1}, Vector2Scale(MeasureTextEx(retroFont, "resume game", 25, 1), 0.5f), 0, 25, 1, RED);
            DrawTextPro(retroFont, "resume game", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) + 40}, Vector2Scale(MeasureTextEx(retroFont, "resume game", 25, 1), 0.5f), 0, 25, 1, BLUE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                exitPause = true;
            }
        }
        else
        {
            DrawTextPro(retroFont, "resume game", (Vector2){(GetScreenWidth() / 2) + 2, (GetScreenHeight() / 2) + 40 + 1}, Vector2Scale(MeasureTextEx(retroFont, "resume game", 25, 1), 0.5f), 0, 25, 1, LIME);
            DrawTextPro(retroFont, "resume game", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) + 40}, Vector2Scale(MeasureTextEx(retroFont, "resume game", 25, 1), 0.5f), 0, 25, 1, WHITE);
        }

        if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "main menu", 25, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "main menu", 25, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 85 - MeasureTextEx(retroFont, "letters", 25, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 85 + MeasureTextEx(retroFont, "letters", 25, 1).y / 2))
        {
            DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2) + 2, (GetScreenHeight() / 2) + 90 + 1}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 25, 1), 0.5f), 0, 25, 1, RED);
            DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) + 90}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 25, 1), 0.5f), 0, 25, 1, BLUE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                exitGame = true;
                exitPause = true;
            }
        }
        else
        {
            DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2) + 2, (GetScreenHeight() / 2) + 90 + 1}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 25, 1), 0.5f), 0, 25, 1, LIME);
            DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) + 90}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 25, 1), 0.5f), 0, 25, 1, WHITE);
        }
    }
    EndDrawing();
}
/**
 * keyboard_highlight:
 * 
 * Highlights the key you need to press in the keyboard for Train mode
 */   
void keyboard_highlight (char a) {
DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);

    switch (a)
    {
        case 'q':
            DrawCircle(422, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'w':
            DrawCircle(468, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'e':
            DrawCircle(515, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'r':
            DrawCircle(562, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 't':
            DrawCircle(609, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'y':
            DrawCircle(653, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'u':
            DrawCircle(703, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'i':
            DrawCircle(747, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'o':
            DrawCircle(796, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'p':
            DrawCircle(841, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'a':
            DrawCircle(407, 622, 10, ColorAlpha(RED, 0.75f));
            break; 
        case 's':
            DrawCircle(457, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'd':
            DrawCircle(509, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'f':
            DrawCircle(565, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'g':
            DrawCircle(617, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'h':
            DrawCircle(666, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'j':
            DrawCircle(716, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'k':
            DrawCircle(772, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'l':
            DrawCircle(820, 622, 10, ColorAlpha(RED, 0.75f));
            break;   
        case 'z':
            DrawCircle(403, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'x':
            DrawCircle(460, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'c':
            DrawCircle(521, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'v':
            DrawCircle(578, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'b':
            DrawCircle(636, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'n':
            DrawCircle(691, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'm':
            DrawCircle(755, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        default:
            break;
    }

}

/**
 * tutorial_screen:
 * 
 * Shows the touch typing keyboard placement when Help button is pressed in main menu
 */   
void tutorial_screen() {
    bool exitTutorial = false;
    while(!exitTutorial) {
        BeginDrawing();
        draw_background();
        DrawTextEx(retroFont, "TOUCH TYPING ", (Vector2){screenWidth / 2 - 370 + 5, 60 + 4}, 90, 1, DARKBLUE);
		DrawTextEx(retroFont, "TOUCH TYPING", (Vector2){screenWidth / 2 - 370, 60}, 90, 1, WHITE);
		
        DrawTextEx(retroFont, "Here's how your finger placement should be for touch typing", (Vector2){60+2,180+1}, 30, 1, BLUE);
		DrawTextEx(retroFont, "Here's how your finger placement should be for touch typing", (Vector2){60,180}, 30, 1, WHITE);
		DrawTextureEx(qwertyTexture, (Vector2){330,(GetScreenHeight()/2 -150)},0,0.6, WHITE);
        if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 285 - MeasureTextEx(retroFont, "main menu", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 285 + MeasureTextEx(retroFont, "main menu", 30, 1).y / 2))
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 280 + 1}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, RED);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 280}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
			exitTutorial = true;
			}
		}
		else
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2 + 3), GetScreenHeight() / 2 + 280 + 2}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, LIME);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 280}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, WHITE);
		}
        // DrawTextEx(retroFont, "Put your left index finger in F and Right one in J. Then Put", (Vector2){60+2,580+1}, 30, 1, BLUE);
		// DrawTextEx(retroFont, "Put your left index finger in F and Right one in J. Then Put", (Vector2){60,580}, 30, 1, WHITE);
		// DrawTextEx(retroFont, "the fingers subsequently to have little finger in a and ;", (Vector2){60+2,620+1}, 30, 1, BLUE);
		// DrawTextEx(retroFont, "the fingers subsequently to have little finger in a and ;", (Vector2){60,620}, 30, 1, WHITE);
        EndDrawing();
    }
}
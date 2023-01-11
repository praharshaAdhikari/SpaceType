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
Texture2D spaceTexture, planetTextures[3], bulletTexture, spaceshipTexture;
/*Declaring variables end*/

/*Declaring extern variables to be used from main start*/
extern int screenWidth, screenHeight;
extern Font retroFont;
extern bool exitGame;
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

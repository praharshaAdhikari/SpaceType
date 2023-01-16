/**
 * \file spacetype_functions.c
 * \brief Created functions for this application
 * \author Praharsha Adhikari <078bct061.praharsha@pcampus.edu.np>
 * \bug No Known Bugs
*/


/* -- Includes -- */
#include <string.h>
#include "spacetype_functions.h"


/**
 * @{ \name Statistics variables
 *
 * \details variables handle counters which are associated with with 
 * statistics of Word shooter game and word train mode. 
 */
char fastestWord[20], slowestWord[20], scoreString[50];
int SCORE;
float TIME = 10;
float keysPressed, rightKeysPressed, framesCounterForSession,
    framesCounterForWord, fastestWordFrames, slowestWordFrames;
bool gapMeasured, exitPause = true;
/**
 * @}
 */

/**
 * @{ \name Background and main interface variables
 * 
 * \details handle different elements related to main interface
 * of the program like background textures, music, scale, etc
 */
float scale; //!< Image scale for the uniformity
float movingDown; //!< Variable to govern infinitely scrolling background
float mover; //!< Variable which controls the speed of the word in game mode
Music music;
Texture2D spaceTexture; //!< Space Background used in infinite scroll background
Texture2D planetTextures[3]; //!< Array of 3 different planet images to display on background
Texture2D bulletTexture; //!< Texture of Bullet used in game mode
Texture2D spaceshipTexture; //!< Texture of spaceship in game mode
Texture2D  cockpitTextureKeyboard; //!< Background Texture
/**
 * @}
 */

/**
 * @{ \name Extern variables from main
 * 
 * \details different variables initialized before needed for this portion
 */
extern int screenWidth;
extern int screenHeight;
extern Font retroFont;
extern bool exitGame, sorted;
extern FILE* wrongChars;
extern Texture2D qwertyTexture;
/**
 * @}
 */

/**
 * \brief Removes the first letter of the word sent
 * 
 * \param word[]: the word sent to have its first letter removed
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
 * \brief Draws background in all modes
 * 
 * \details  Draws the infinitely scrolling space background with moving planets.
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
 * \brief resets variables for required statistics
 * 
 * \details all the variables like score, fastestword, 
 * slowest word, etc. that are used to calculate
 * statistics during word practice and Game mode
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
 * \brief Creates a pause menu
 * 
 * \details a pause menu when called. Has options to 
 * either resume the game or return back to main menu
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
 * \brief hightlights requried letter
 * 
 * \details the key you need to press in the keyboard for Train mode
 * 
 * \param a the letter which needs to be highlighted
 */   
void keyboard_highlight (char a) {
    DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
    switch (a)
    {
        case 'q':
            DrawCircle(422, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'Q':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(422, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'w':
            DrawCircle(468, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'W':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(468, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'e':
            DrawCircle(515, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'E':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(515, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'r':
            DrawCircle(562, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'R':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(562, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 't':
            DrawCircle(609, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'T':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(609, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'y':
            DrawCircle(653, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'Y':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(653, 592, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'u':
            DrawCircle(703, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'U':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(703, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'i':
            DrawCircle(747, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'I':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(747, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'o':
            DrawCircle(796, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'O':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(796, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'p':
            DrawCircle(841, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'P':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(841, 593, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'a':
            DrawCircle(407, 622, 10, ColorAlpha(RED, 0.75f));
            break; 
        case 'A':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(407, 622, 10, ColorAlpha(RED, 0.75f));
            break; 
        case 's':
            DrawCircle(457, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'S':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(457, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'd':
            DrawCircle(509, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'D':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(509, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'f':
            DrawCircle(565, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'F':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(565, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'g':
            DrawCircle(617, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'G':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(617, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'h':
            DrawCircle(666, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'H':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(666, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'j':
            DrawCircle(716, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'J':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(716, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'k':
            DrawCircle(772, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'K':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(772, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'l':
            DrawCircle(820, 622, 10, ColorAlpha(RED, 0.75f));
            break;   
        case 'L':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(820, 622, 10, ColorAlpha(RED, 0.75f));
            break;   
        case 'z':
            DrawCircle(403, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'Z':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(403, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'x':
            DrawCircle(460, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'X':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(460, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'c':
            DrawCircle(521, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'C':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(521, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'v':
            DrawCircle(578, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'V':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(578, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'b':
            DrawCircle(636, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'B':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(636, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'n':
            DrawCircle(691, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'N':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(691, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'm':
            DrawCircle(755, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case 'M':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(755, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case ' ':
            DrawCircle(636, 706, 10, ColorAlpha(RED, 0.75f));
            break;
        case ((char)39):
            DrawCircle(935, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case ':':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(875, 622, 10, ColorAlpha(RED, 0.75f));
            break;
        case ',':
            DrawCircle(810, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case '.':
            DrawCircle(861, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        case '1':
            DrawCircle(426, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '2':
            DrawCircle(466, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '3':
            DrawCircle(506, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '4':
            DrawCircle(556, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '5':
            DrawCircle(596, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '6':
            DrawCircle(636, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '7':
            DrawCircle(676, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '8':
            DrawCircle(726, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '9':
            DrawCircle(766, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '0':
            DrawCircle(806, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '(':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(766, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case ')':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(806, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '-':
            DrawCircle(851, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '+':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(891, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '!':
            DrawCircle(1040, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(426, 568, 10, ColorAlpha(RED, 0.75f));
            break;
        case '?':
            DrawCircle(310, 660, 10, ColorAlpha(RED, 0.75f));
            DrawCircle(915, 656, 10, ColorAlpha(RED, 0.75f));
            break;
        default:
            break;
    }

}

/**
 * \brief Shows a tutorial screeen for touch typing
 * 
 * \details Shows the touch typing finger placement in keyboard
 * when Help button is pressed in main menu
 */   
void tutorial_screen() {
    bool exitTutorial = false;
    while(!exitTutorial) {
    	UpdateMusicStream(music);
        BeginDrawing();
        draw_background();
        DrawTextEx(retroFont, "TOUCH TYPING ", (Vector2){screenWidth / 2 - 375 + 5, 60 + 4}, 90, 1, DARKBLUE);
		DrawTextEx(retroFont, "TOUCH TYPING", (Vector2){screenWidth / 2 - 375, 60}, 90, 1, WHITE);
        DrawTextEx(retroFont, "Here's how your finger placement should be for touch typing.", (Vector2){70+2,220+1}, 30, 1, BLUE);
		DrawTextEx(retroFont, "Here's how your finger placement should be for touch typing.", (Vector2){70,220}, 30, 1, WHITE);
		DrawTextureEx(qwertyTexture, (Vector2){330,(GetScreenHeight()/2 - 100)},0,0.6, WHITE);
        if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 325 - MeasureTextEx(retroFont, "main menu", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 325 + MeasureTextEx(retroFont, "main menu", 30, 1).y / 2))
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 330 + 1}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, RED);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 330}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
			    exitTutorial = true;
			}
		}
		else
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2 + 3), GetScreenHeight() / 2 + 330 + 2}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, LIME);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 330}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, WHITE);
		}
        // DrawTextEx(retroFont, "Put your left index finger in F and Right one in J. Then Put", (Vector2){60+2,580+1}, 30, 1, BLUE);
		// DrawTextEx(retroFont, "Put your left index finger in F and Right one in J. Then Put", (Vector2){60,580}, 30, 1, WHITE);
		// DrawTextEx(retroFont, "the fingers subsequently to have little finger in a and ;", (Vector2){60+2,620+1}, 30, 1, BLUE);
		// DrawTextEx(retroFont, "the fingers subsequently to have little finger in a and ;", (Vector2){60,620}, 30, 1, WHITE);
        EndDrawing();
    }
}
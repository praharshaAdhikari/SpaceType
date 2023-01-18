/**
 * \file spacetype_game.c
 * \brief Word Shooter Game for Spacetype
 * \author Praharsha Adhikari <078bct061.praharsha@pcampus.edu.np>
 * \bug No known bug
*/

/* -- Includes -- */
/* Including other C files and header files of this code*/
#include "spacetype_functions.c" /*for pause_screen, reset_counter and remove_firstletter functions*/

/**
 * @{ \name Main gameplay variables
 * \details These variables handle different aspects related to the main
 * gameplay.
 */
char *words[] =
    {
        "apple", "ant", "airplane", "banana", "book", "boat", "cat", "cow", "car", "dog", "desk", "dolphin", "elephant", "egg", "earth", "fish", "flamingo", "frog", "giraffe", "goat", "grapes", "hat", "horse", "house", "igloo", "icecream", "insect", "jacket", "jaguar", "juice", "kangaroo", "kite", "key", "lion", "leopard", "lamp", "monkey", "mouse", "mango", "night", "nest", "napkin", "octopus", "ostrich", "onion", "pear", "panda", "pig", "queen", "quail", "question", "rabbit", "rhinoceros", "ring", "snake", "snail", "sock", "tiger", "taco", "table", "unicorn", "umbrella", "vase", "vegetable", "whale", "wolf", "watermelon", "xray", "xylophone", "yak", "yoyo", "zipper", "zoo"
    }; //!< List of words to choose from for the game
char word[20]; //!<word which is presented to type
char wordStored[20]; //!<stores the presented word to later compare with fastestword and slowestword
int sizeOfArray = sizeof(words) / sizeof(words[0]); //!<for calculating total number of words*/
Vector2 gap = {}; //!<Shortest distance between word and spaceship*/
Vector2 wordPos; //!<position of word as it falls down
const int fontSize = 25; //!< Fonsize declaration for uniformity of fontsize
float angle = 0; //!< Angle of word to have it fall towards player
float prevAngle = 0; //!< Angle of the spaceship
float movingPlanets = 0; //!< Denotes which planet will be on screen 
float movingDown = 0; //!< Parameters which makes space texture scroll infinitely*/
bool GAME_OVER = false; //!< boolean to check game over condition
/**
 * @}
 */

void text_mover(Vector2 *, Rectangle, Vector2, float); 

/**
 * @{ \name Bullet related variables
 * 
 * \details These variables handle different aspects related to bullet 
 * which destroys the word when it is finished being typed. 
 */
Sound shoot; //!<Audio played when bullet is used
Rectangle bulletPos; //!<Bullet Position
bool bullet = false; //!<indicates whether bullet needs to be shoot or not
float bulletAngle;  //!<Determine angle at which bullet needs to be thrown depending word position
float bulletMover = 0; //!<To indicate speed of the bullet
/**
 * @}
 */

/**
 * @{ \name Extern variables from main
 * 
 * \details different variables initialized before needed for this portion
 */
extern Music music; //!< background music
extern int screenWidth;
extern int screenHeight;
extern Font retroFont;
 /**
 * @}
 */

/**
* \brief main function for game mode
*
* \details Handles everything regarding spaceship shoot game. Resets
* variables specific to the game and general by calling
* reset_counter. Draws the graphics regarding spaceship
* falling words and bullets. Handles the gameplay mechanics
* and shows a gameover screen when required. 
*/

void game()
{
    /** Resetting in case of new game from menu */
    GAME_OVER = false;
    strcpy(word, words[GetRandomValue(0, sizeOfArray - 1)]);
    strcpy(wordStored, word);
    wordPos = (Vector2){GetRandomValue(200, screenWidth - 150), 20};
    reset_counter();
    
    /** Initialize variables and textures */
    int planet = GetRandomValue(0, 2);
    int planetPos = GetRandomValue(0, 2);
    Rectangle playerPos = {screenWidth / 2, screenHeight - 100, spaceshipTexture.width * 2, spaceshipTexture.height * 2};
    Rectangle bulletPos = {screenWidth / 2, playerPos.y - 10, bulletTexture.width * 0.2, bulletTexture.height * 0.2};
    Vector2 planetVectors[3] = {{400, -200}, {1000, -200}, {1450, 200}};
    Vector2 planetVector = planetVectors[planetPos];
    bulletTexture = LoadTexture("resources/images/bullet_texture.png");
    spaceshipTexture = LoadTexture("resources/images/spaceship_texture.png");

    shoot = LoadSound("resources/music/shoot.mp3"); // loading the spaceship shooting sound effect

    while (!exitGame)
    {
        UpdateMusicStream(music);
        movingDown += mover;  // MOVING BACKGROUND
        movingPlanets += mover;  // MOVING PLANETS
        if (IsKeyPressed(KEY_ESCAPE)) // PAUSE MENU IS SHOWN
            exitPause = false;
        if (movingDown >= spaceTexture.height * scale)
            movingDown = 0;
        
        BeginDrawing();

        // SPACE BACKGROUND
        DrawTextureEx(spaceTexture, (Vector2){0, -spaceTexture.height * scale + movingDown}, 0, scale, WHITE);
        DrawTextureEx(spaceTexture, (Vector2){0, movingDown}, 0, scale, WHITE);
        DrawTextureEx(spaceTexture, (Vector2){0, spaceTexture.height * scale + movingDown}, 0, scale, WHITE);

        // PLANETS
        if (
            (planetVector.x > -100 || planetVector.x < 1400) && (planetVector.y < 800))
        {
            // SELECTS PLANET AND ITS PATH
            switch (planetPos)
            {
            case 0:
                planetVector = (Vector2){400 - movingPlanets * 1.1, -200 + movingPlanets * 1.65};
                DrawTextureEx(planetTextures[planet], planetVector, 0, 2, WHITE);
                break;
            case 1:
                planetVector = (Vector2){1000 + movingPlanets * 0.55, -200 + movingPlanets * 3.3};
                DrawTextureEx(planetTextures[planet], planetVector, 0, 2, WHITE);
                break;
            case 2:
                planetVector = (Vector2){1450 - movingPlanets * 4.4, 200 + movingPlanets * 1.7};
                DrawTextureEx(planetTextures[planet], planetVector, 0, 2, WHITE);
                break;
            default:
                break;
            }
        }
        else
        {
            // RESETS PLANETS PROPERTIES WHEN IT GOES BEYOND THE SCREEN
            int x = planet;
            int y = planetPos;
            while (planet == x)
                planet = GetRandomValue(0, 2);
            while (planetPos == y)
                planetPos = GetRandomValue(0, 2);
            planetVector = planetVectors[planetPos];
            movingPlanets = 0;
        }

        if (!GAME_OVER)
        {
            framesCounterForSession++;
            framesCounterForWord++;
            DrawTextEx(retroFont, word, (Vector2){wordPos.x + 2, wordPos.y + 3}, fontSize, 1, RED);
            DrawTextEx(retroFont, word, wordPos, fontSize, 1, WHITE);
            angle = -((atan2(playerPos.x - wordPos.x, playerPos.y - wordPos.y)) * 57.295);
            bulletAngle = angle / 57.295;
            Rectangle playerRect = {0, 0, spaceshipTexture.width, spaceshipTexture.height};
            Vector2 playerCenter = {spaceshipTexture.width, 0};
            if (prevAngle < angle)
                prevAngle += 4;
            if (prevAngle > angle)
                prevAngle -= 4;
            DrawTexturePro(spaceshipTexture, playerRect, playerPos, playerCenter, prevAngle, WHITE);
            sprintf(scoreString, "Score : %i", SCORE);
            DrawTextEx(retroFont, scoreString, (Vector2){12, 12}, fontSize - 4, 1, GREEN);
            DrawTextEx(retroFont, scoreString, (Vector2){10, 10}, fontSize - 4, 1, WHITE);
            if (!exitPause)
                pause_screen();
            if (exitPause)
                text_mover(&wordPos, playerPos, gap, TIME);
            if (bullet && exitPause)
            {
                bulletMover += 150;
                PlaySound(shoot);
                Rectangle bulletRect = {0, 0, bulletTexture.width, bulletTexture.height};
                Vector2 bulletBottomCenter = {bulletTexture.width / 10, bulletTexture.height * 0.2};
                DrawTexturePro(bulletTexture, bulletRect, bulletPos, bulletBottomCenter, angle, WHITE);
                bulletPos.x = screenWidth / 2 + bulletMover * sinf(bulletAngle);
                bulletPos.y = playerPos.y - bulletMover * cosf(bulletAngle);
            }
            if (!gapMeasured)
            {
                gap.x = playerPos.x - wordPos.x;
                gap.y = playerPos.y - wordPos.y;
                gapMeasured = true;
            }
            // TAKING INPUT
            int key = GetKeyPressed();
            int firstLetter = ((int)word[0]) - 32;
            if (key){
                keysPressed++;
                if (key != firstLetter){
                    fprintf(wrongChars, "%c", firstLetter);
                }
            }
            if ((key == firstLetter || bullet) && exitPause)
            {
                if (key == firstLetter)
                    rightKeysPressed++;
                if (strlen(word) == 1)
                {
                    bullet = true;
                    if (bulletPos.y < wordPos.y + 10)
                    {
                        bulletMover = 0;
                        bullet = false;
                        bulletPos.x = screenWidth / 2;
                        bulletPos.y = playerPos.y - 10;
                        remove_firstletter(word);
                    }
                }
                else
                    remove_firstletter(word);
                if (strlen(word) == 0)
                {
                    // UPDATING DATA
                    if (framesCounterForWord > slowestWordFrames)
                    {
                        slowestWordFrames = framesCounterForWord;
                        strcpy(slowestWord, wordStored);
                    }
                    if (framesCounterForWord < fastestWordFrames)
                    {
                        fastestWordFrames = framesCounterForWord;
                        strcpy(fastestWord, wordStored);
                    }
                    prevAngle = angle;
                    // RESETTING
                    strcpy(word, words[GetRandomValue(0, sizeOfArray - 1)]);
                    strcpy(wordStored, word);
                    wordPos.x = GetRandomValue(200, screenWidth - 150);
                    wordPos.y = 20;
                    gapMeasured = false;
                    TIME -= (TIME < 5) ? ((TIME < 4) ? 0.1 : 0.25) : 0.5;
                    mover += (mover > 0.65) ? 0.075 : 0.05;
                    SCORE++;
                    framesCounterForWord = 0;
                }
            }
        }
        if (GAME_OVER)
        {
            mover = 0.15f;
            if (SCORE == 0)
            {
                fastestWordFrames = 0;
                if (keysPressed == 0)
                    keysPressed = 1;
            }

            // SHOWING STATS AND OPTIONS TO CONTINUE
            char sessionDurationString[50];
            char fastestWordString[50];
            char fastestTimeString[50];
            char slowestWordString[50];
            char slowestTimeString[50];
            char wpmString[50];
            char accuracyString[50];

            sprintf(sessionDurationString, "Session time : %.2f seconds", framesCounterForSession / 60);
            sprintf(fastestWordString, "Fastest Word:  | %s |", fastestWord);
            sprintf(fastestTimeString, "Time: %.2f seconds", fastestWordFrames / 60);
            sprintf(slowestWordString, "Slowest Word:  | %s |", slowestWord);
            sprintf(slowestTimeString, "Time: %.2f seconds", slowestWordFrames / 60);
            sprintf(wpmString, "Typing Speed: %d WPM", (int)(SCORE * 60 * 60 / framesCounterForSession));
            sprintf(accuracyString, "Accuracy: %.2f%%", (rightKeysPressed / keysPressed) * 100);

            DrawTextEx(retroFont, "GAME OVER", (Vector2){screenWidth / 2 - 260 + 5, screenHeight / 2 - 250 + 4}, 80, 1, DARKBLUE);
            DrawTextEx(retroFont, "GAME OVER", (Vector2){screenWidth / 2 - 260, screenHeight / 2 - 250}, 80, 1, WHITE);
            DrawTextEx(retroFont, scoreString, (Vector2){250 + 2, screenHeight / 2 - 40 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, scoreString, (Vector2){250, screenHeight / 2 - 40}, 20, 1, WHITE);
            DrawTextEx(retroFont, sessionDurationString, (Vector2){250 + 2, screenHeight / 2 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, sessionDurationString, (Vector2){250, screenHeight / 2}, 20, 1, WHITE);
            DrawTextEx(retroFont, fastestWordString, (Vector2){250 + 2, screenHeight / 2 + 40 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, fastestWordString, (Vector2){250, screenHeight / 2 + 40}, 20, 1, WHITE);
            DrawTextEx(retroFont, fastestTimeString, (Vector2){850 + 2, screenHeight / 2 + 40 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, fastestTimeString, (Vector2){850, screenHeight / 2 + 40}, 20, 1, WHITE);
            DrawTextEx(retroFont, slowestWordString, (Vector2){250 + 2, screenHeight / 2 + 80 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, slowestWordString, (Vector2){250, screenHeight / 2 + 80}, 20, 1, WHITE);
            DrawTextEx(retroFont, slowestTimeString, (Vector2){850 + 2, screenHeight / 2 + 80 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, slowestTimeString, (Vector2){850, screenHeight / 2 + 80}, 20, 1, WHITE);
            DrawTextEx(retroFont, wpmString, (Vector2){250 + 2, screenHeight / 2 + 120 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, wpmString, (Vector2){250, screenHeight / 2 + 120}, 20, 1, WHITE);
            DrawTextEx(retroFont, accuracyString, (Vector2){250 + 2, screenHeight / 2 + 160 + 1}, 20, 1, BROWN);
            DrawTextEx(retroFont, accuracyString, (Vector2){250, screenHeight / 2 + 160}, 20, 1, WHITE);

            if ((float)GetMouseX() >= (screenWidth / 2) - 300 && (float)GetMouseX() <= (screenWidth / 2) - 80 && (float)GetMouseY() >= (screenHeight / 2) + 250 && (float)GetMouseY() <= (screenHeight / 2) + 290)
            {
                DrawTextEx(retroFont, "Play Again", (Vector2){screenWidth / 2 - 300 + 3, screenHeight / 2 + 260 + 2}, 30, 1, RED);
                DrawTextEx(retroFont, "Play Again", (Vector2){screenWidth / 2 - 300, screenHeight / 2 + 260}, 30, 1, BLUE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {   
                    // NEW GAME STARTS
                    GAME_OVER = false;
                    strcpy(word, words[GetRandomValue(0, sizeOfArray - 1)]);
                    strcpy(wordStored, word);
                    wordPos.x = GetRandomValue(200, screenWidth - 150);
                    wordPos.y = 20;
                    gapMeasured = false;
                    TIME = 10;
                    SCORE = 0;
                    framesCounterForWord = 0;
                    framesCounterForSession = 0;
                    fastestWordFrames = 2147483647;
                    slowestWordFrames = 0;
                    keysPressed = 0;
                    rightKeysPressed = 0;
                    strcpy(fastestWord, "NONE");
                    strcpy(slowestWord, "NONE");
                }
            }
            else
            {
                DrawTextEx(retroFont, "Play Again", (Vector2){screenWidth / 2 - 300 + 3, screenHeight / 2 + 260 + 2}, 30, 1, LIME);
                DrawTextEx(retroFont, "Play Again", (Vector2){screenWidth / 2 - 300, screenHeight / 2 + 260}, 30, 1, WHITE);
            }
            if ((float)GetMouseX() >= (screenWidth / 2) + 80 && (float)GetMouseX() <= (screenWidth / 2) + 300 && (float)GetMouseY() >= (screenHeight / 2) + 250 && (float)GetMouseY() <= (screenHeight / 2) + 290)
            {
                DrawTextEx(retroFont, "Main Menu", (Vector2){screenWidth / 2 + 90 + 3, screenHeight / 2 + 260 + 2}, 30, 1, RED);
                DrawTextEx(retroFont, "Main Menu", (Vector2){screenWidth / 2 + 90, screenHeight / 2 + 260}, 30, 1, BLUE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    exitGame = true;
                }
            }
            else
            {
                DrawTextEx(retroFont, "Main Menu", (Vector2){screenWidth / 2 + 90 + 3, screenHeight / 2 + 260 + 2}, 30, 1, LIME);
                DrawTextEx(retroFont, "Main Menu", (Vector2){screenWidth / 2 + 90, screenHeight / 2 + 260}, 30, 1, WHITE);
            }
        }
        EndDrawing();
    }
}


/**
 * \brief  Moves the word toward the player

 * \param wordPos: Position of generated word
 * \param playerPos Position of spaceship
 * \param gap  Shortest distance between word and spaceship
 * \param time Set time for the word to hit the player
 */   

void text_mover(Vector2 *wordPos, Rectangle playerPos, Vector2 gap, float time)
{
    if ((*wordPos).y >= playerPos.y - 20)
        GAME_OVER = true;
    (*wordPos).x += (gap.x) / (time * 60);
    (*wordPos).y += (gap.y) / (time * 60);
}
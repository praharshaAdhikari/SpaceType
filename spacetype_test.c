/**
 * \file spacetype_test.c
 * \brief Test Mode of Space Type
 * \author Pragalbha Acharya <078bct060.pragalbha@pcampus.edu.np>
 * \bug No known Bug
 */

/**
 * @{ \name Passages for Test mode
 */
/**
 * \brief Passages for Test Mode
 *
 * These string contains various texts of varying
 * difficulty and types for the test mode.
 */
char text1[300] = {"Wealth, fame, power. Gold Roger, the King of the Pirates, attained everything this world has to offer. And so, many men head for the Grand Line to find the great treasure he left behind, the One Piece. The world has truly entered a Great Pirate Era!"};
char text2[381] = {"The Tale of Jiraiya the Gallant. Now it'll end a bit better, I hope. The final chapter. I'll call it: Frog at the bottom of the well drifts off into the great ocean. Just barely glorious. But glorious indeed. Now I suppose it's about time I put down my pen. Oh, right. What should I name the sequel? I wonder. Let's see: The Tale of Naruto Uzumaki. Yes, that has a nice ring to it."};
char text3[450] = {"A late 20th century trend in typing, primarily used with devices with small keyboards (such as PDAs and Smartphones) is thumbing or thumb typing. This can be accomplished using one or both thumbs. Similar to desktop keyboards and input devices, if a user overuses keys which need hard presses and/or have small and unergonomic layouts, it could cause thumb tendonitis or other repetitive strain injury."};
char text4[450] = {"Today, historians relate that, as a general rule, buying and selling securities was very much unorganized before the year 1792. Every person who owned a security faced the problem of finding interested buyers who might consider the purchase of a debt-free investment. This meant most people were somewhat slow in investing in stocks and bonds because these securities could not readily be converted into money."};
char text5[287] = {"The Master of Business Administration (MBA or M.B.A.) degree originated in the United States. The core courses in an MBA program cover various areas of business such as accounting, applied statistics, business law, finance, managerial economics, management, entrepreneurship & marketing."};
char text6[438] = {"When we talk about motivating others, the justification is the end result (either we want to avoid the pain or go towards pleasure) or what we want to get the person to do. How we achieve the end result, are our alternatives. As a manager, we need to understand the other person's justification and then come up with alternatives. We may then choose the right alternative. Typically people stop at this level of analysis and start to act."};
char text7[456] = {"A data entry clerk is a member of staff employed to enter or update data into a computer system. Data is often entered into a computer from paper documents using a keyboard. The keyboards used can often have special keys - Alt, Ctrl, Fn, Shift - multiple colors to help in the task & speed up the work. Proper ergonomics at the workstation is a common topic considered. The Data Entry Clerk may also use a mouse, and a manually-fed scanner may be involved."};
char text8[530] = {"An ever-growing number of complex rules plus hard-to-cope-with regulations are now being legislated from state to state. Key federal regulations were formulated by the FDA, FTC, and the CPSC. Each of these federal agencies serves a specific mission. One example: Laws sponsored by the Office of the Fair Debt Collection Practices prevent an agency from purposefully harassing clients in serious debt. The Fair Packaging and Labeling Act makes certain that protection from misleading packaging of goods is guaranteed to each buyer."};
char text9[400] = {"Business casual is an ambiguously defined Western dress code that is generally considered casual wear but with smart (in the sense of 'well dressed') components of a proper lounge suit from traditional informal wear, adopted for white-collar workplaces. This interpretation typically including dress shirt, necktie, & trousers, but worn with an odd-colored blazer or a sports coat instead."};
char text10[520] = {"Many touch typists also use keyboard shortcuts or hotkeys when typing on a computer. This allows them to edit their document without having to take their hands off the keyboard to use a mouse. An example of a keyboard shortcut is pressing the Ctrl key + the S key to save a document as they type, or the Ctrl key + the Z key to undo a mistake. Many experienced typists can feel or sense when they have made an error & can hit the Backspace key & make the correction with no increase in time between keystrokes."};
/**
 * @}
 */

/**
 * @{ \name Extern variables from main
 *
 * \details different variables initialized before needed for this portion
 */
extern Music music;
extern int screenWidth;
extern int screenHeight;
extern Font retroFont, regularFont;
extern Texture2D cockpitTexture, cockpitTextureKeyboard; //!< Textures for background
                                                         /**
                                                          * @}
                                                          */

/**
 * @{ \name General variables for Test process
 *
 */
bool exitTest, exitTestProcess;
char input[530] = {};
int check;
/**
 * @}
 */

/**
 * \brief main function for test mode
 *
 * \details Initializes the background texture, continues the background
 * music, draws the background and calls test_menu function
 * for further navigation
 */
void test()
{
    exitTest = false;
    while (!exitTest)
    {
        UpdateMusicStream(music);
        movingDown += mover;
		movingPlanets += 0.45f;
        BeginDrawing();
        ClearBackground(BLACK);
        draw_background();
        DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
        test_menu();
        EndDrawing();
    }
}

/**
 * \brief main menu for test screen
 *
 * \details Draws the menu for the test mode. Gives the user the option
 * to choose the difficulty that they want their test to be in.
 */
void test_menu()
{
    if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "Easy", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "Easy", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 155 - MeasureTextEx(retroFont, "Easy", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 155 + MeasureTextEx(retroFont, "Easy", 30, 1).y / 2))
    {
        DrawTextPro(retroFont, "Easy", (Vector2){(GetScreenWidth() / 2) + 2, (GetScreenHeight() / 2) - 150 + 1}, Vector2Scale(MeasureTextEx(retroFont, "Easy", 30, 1), 0.5f), 0, 30, 1, RED);
        DrawTextPro(retroFont, "Easy", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) - 150}, Vector2Scale(MeasureTextEx(retroFont, "Easy", 30, 1), 0.5f), 0, 30, 1, BLUE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            check = 1;
    }
    else
    {
        DrawTextPro(retroFont, "Easy", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) - 150}, Vector2Scale(MeasureTextEx(retroFont, "Easy", 30, 1), 0.5f), 0, 30, 1, WHITE);
    }
    if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "Intermediate", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "Intermediate", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 105 - MeasureTextEx(retroFont, "Intermediate", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 105 + MeasureTextEx(retroFont, "Intermediate", 30, 1).y / 2))
    {
        DrawTextPro(retroFont, "Intermediate", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 100 + 1}, Vector2Scale(MeasureTextEx(retroFont, "Intermediate", 30, 1), 0.5f), 0, 30, 1, RED);
        DrawTextPro(retroFont, "Intermediate", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 100}, Vector2Scale(MeasureTextEx(retroFont, "Intermediate", 30, 1), 0.5f), 0, 30, 1, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            check = 2;
    }
    else
    {
        DrawTextPro(retroFont, "Intermediate", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 100}, Vector2Scale(MeasureTextEx(retroFont, "Intermediate", 30, 1), 0.5f), 0, 30, 1, WHITE);
    }
    if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "Hard", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "Hard", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 55 - MeasureTextEx(retroFont, "hard", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 55 + MeasureTextEx(retroFont, "hard", 30, 1).y / 2))
    {
        DrawTextPro(retroFont, "hard", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 50 + 1}, Vector2Scale(MeasureTextEx(retroFont, "hard", 30, 1), 0.5f), 0, 30, 1, RED);
        DrawTextPro(retroFont, "hard", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 50}, Vector2Scale(MeasureTextEx(retroFont, "hard", 30, 1), 0.5f), 0, 30, 1, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            check = 3;
    }
    else
    {
        DrawTextPro(retroFont, "hard", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 50}, Vector2Scale(MeasureTextEx(retroFont, "hard", 30, 1), 0.5f), 0, 30, 1, WHITE);
    }
    if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "back", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "back", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 15 - MeasureTextEx(retroFont, "back", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 15 + MeasureTextEx(retroFont, "back", 30, 1).y / 2))
    {
        DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 20 + 1}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, RED);
        DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 20}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, BLUE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            exitTest = true;
        }
    }
    else
    {
        DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 20}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, WHITE);
    }

    int random;
    switch (check)
    {
    case 1:
        random = rand() % 2;
        switch (random)
        {
        case 0:
            EndDrawing();
            test_process(text1);
            break;
        case 1:
            EndDrawing();
            test_process(text2);
            break;
        default:
            break;
        }
        break;
    case 2:
        random = rand() % 4;
        switch (random)
        {
        case 0:
            EndDrawing();
            test_process(text3);
            break;
        case 1:
            EndDrawing();
            test_process(text4);
            break;
        case 2:
            EndDrawing();
            test_process(text5);
            break;
        case 3:
            EndDrawing();
            test_process(text6);
            break;
        default:
            break;
        }
        break;
    case 3:
        random = rand() % 4;
        switch (random)
        {
        case 0:
            EndDrawing();
            test_process(text7);
            break;
        case 1:
            EndDrawing();
            test_process(text8);
            break;
        case 2:
            EndDrawing();
            test_process(text9);
            break;
        case 3:
            EndDrawing();
            test_process(text10);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

/**
 * \brief Handles the typing test process
 *
 * \details This function divides the large text into smaller parts, and
 * displays it on the screen to make it easier for the user. Gets
 * the key pressed by the user, checks with the letter from the
 * text, and highlights if its correct. The second part of the text
 * only displayed once the displayed part is enterred correctly.
 * Statistics like typing speed, accuracy are shown at the end.
 *
 * \param test_text Indicates which passage is to be displayed
 */
void test_process(char test_text[])
{
    exitTestProcess = false;
    int note;
    int framescounter = 0;
    const int maxletter = strlen(test_text);
    int timecount = 0;
    int letterCount = 0;
    char lineOne[28], lineTwo[28];
    int spacePosOne, spacePosTwo;
    int i, j;
    for (i = 0; i < 23 || test_text[i] != ' '; i++){
        if (i>=26){
            for (i=26; test_text[i] != ' '; i--) lineOne[i] = '\0';
            spacePosOne = i;
            i++;
            break;
        }
        lineOne[i] = test_text[i];
        spacePosOne = i + 1;        
        if (test_text[i] == '\0') break;
    }
    lineOne[i] = ' ';
    lineOne[i+1] = '\0';
    for (i = spacePosOne, j = 0; j < 23 || test_text[i] != ' '; i++, j++){
        if (j>=26){
            for (j=26; test_text[i] != ' '; j--, i--) lineTwo[j] = '\0';
            spacePosTwo = i;
            break;
        }
        lineTwo[j] = test_text[i];
        spacePosTwo = i + 1;
        if (test_text[i] == '\0') break;
    }
    lineTwo[j] = ' ';
    lineTwo[j+1] = '\0';
    float correct_keys_pressed = 0, incorrect_keys_pressed = 0;
    int startPos = 0;

    while (!exitTestProcess)
    {
        UpdateMusicStream(music);
        movingDown += mover;
		movingPlanets += 0.45f;
        BeginDrawing();
        draw_background();
        framescounter++;
        DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
        int key = GetCharPressed();
        if (letterCount < maxletter)
        {
		    DrawTextPro(regularFont, lineOne, (Vector2){(GetScreenWidth() / 2) + 18 + 2, GetScreenHeight() / 2 - 130 + 1}, Vector2Scale(MeasureTextEx(regularFont, lineOne, 18, 1), 0.5f), 0, 18, 1, BLUE);
		    DrawTextPro(regularFont, lineOne, (Vector2){(GetScreenWidth() / 2) + 18, GetScreenHeight() / 2 - 130}, Vector2Scale(MeasureTextEx(regularFont, lineOne, 18, 1), 0.5f), 0, 18, 1, WHITE);
		    DrawTextPro(regularFont, lineTwo, (Vector2){(GetScreenWidth() / 2) + 18 + 2, GetScreenHeight() / 2 - 100 + 1}, Vector2Scale(MeasureTextEx(regularFont, lineTwo, 18, 1), 0.5f), 0, 18, 1, BLUE);
		    DrawTextPro(regularFont, lineTwo, (Vector2){(GetScreenWidth() / 2) + 18, GetScreenHeight() / 2 - 100}, Vector2Scale(MeasureTextEx(regularFont, lineTwo, 18, 1), 0.5f), 0, 18, 1, WHITE);
            keyboard_highlight(test_text[letterCount]);
            if ((letterCount) == spacePosOne && key != 0 && (char)key == test_text[letterCount])
            {
                strcpy(lineOne, lineTwo);
                startPos = spacePosOne;
                spacePosOne = spacePosTwo;
                strcpy(lineTwo, "");
                for (i = spacePosOne, j = 0; j < 23 || test_text[i] != ' '; i++, j++){
                    if (j>=26){
                        for (j=26; test_text[i] != ' '; j--, i--) lineTwo[j] = '\0';
                        spacePosTwo = i;
                        break;
                    }
                    lineTwo[j] = test_text[i];
                    spacePosTwo = i + 1;
                    if (test_text[i] == '\0') break;
                }
                lineTwo[j] = ' ';
                lineTwo[j+1] = '\0';
            }
        }
        while (key)
        {
            if ((key >= 32) && (key <= 125) && (letterCount < maxletter))
            {
                input[letterCount] = (char)key;
                if ((input[letterCount] == test_text[letterCount]))
                {
                    correct_keys_pressed++;
                    input[letterCount + 1] = '\0';
                    letterCount++;
                }
                else
                {
                    incorrect_keys_pressed++;
                    if (key >= 97 && key<=122)
                        fprintf(wrongChars, "%c", (char)(key - 32));
                    else if (key >= 65 && key <= 90)
                        fprintf(wrongChars, "%c", (char)(key));
                    input[letterCount] = '\0';
                }
            }
            key = GetCharPressed();
        }
        if (maxletter != correct_keys_pressed)
        {
            note = timecount;
            timecount++;
        }
        if (letterCount < maxletter)
        {
            DrawTextPro(regularFont, TextSubtext(input, startPos, spacePosOne), (Vector2){(GetScreenWidth() / 2) + 18+ 2, GetScreenHeight() / 2 - 130 + 1}, Vector2Scale(MeasureTextEx(regularFont, lineOne, 18, 1), 0.5f), 0, 18, 1, BLUE);
            DrawTextPro(regularFont, TextSubtext(input, startPos, spacePosOne), (Vector2){(GetScreenWidth() / 2) + 18, GetScreenHeight() / 2 - 130}, Vector2Scale(MeasureTextEx(regularFont, lineOne, 18, 1), 0.5f), 0, 18, 1, (Color){115, 147, 179, 255});
        }
        ClearBackground(BLACK);
        if (letterCount >= maxletter)
        {
            UpdateMusicStream(music);
            char sessionDurationString[50];
            char wpmString[50];
            char accuracyString[50];

            sprintf(sessionDurationString, "Session time : %.2f seconds", (float)note / 60);
            sprintf(wpmString, "Typing Speed: %d WPM", (int)(((correct_keys_pressed + incorrect_keys_pressed) / 5) / ((float)note / 3600)));
            sprintf(accuracyString, "Accuracy: %.2f%%", ((correct_keys_pressed) / (incorrect_keys_pressed + correct_keys_pressed)) * 100);

            BeginDrawing();
            draw_background();
            DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
            
			DrawTextPro(retroFont, "RESULTS", (Vector2){(GetScreenWidth() / 2 + 5), GetScreenHeight() / 2 - 250 + 4}, Vector2Scale(MeasureTextEx(retroFont, "RESULTS", 80, 1), 0.5f), 0, 80, 1, DARKBLUE);
			DrawTextPro(retroFont, "RESULTS", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 - 250}, Vector2Scale(MeasureTextEx(retroFont, "RESULTS", 80, 1), 0.5f), 0, 80, 1, WHITE);
			DrawTextPro(retroFont, sessionDurationString, (Vector2){(GetScreenWidth() / 2 + 2), GetScreenHeight() / 2 - 120 + 1}, Vector2Scale(MeasureTextEx(retroFont, sessionDurationString, 20, 1), 0.5f), 0, 20, 1, BROWN);
			DrawTextPro(retroFont, sessionDurationString, (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 - 120}, Vector2Scale(MeasureTextEx(retroFont, sessionDurationString, 20, 1), 0.5f), 0, 20, 1, WHITE);
			DrawTextPro(retroFont, wpmString, (Vector2){(GetScreenWidth() / 2 + 2), GetScreenHeight() / 2 - 80 + 1}, Vector2Scale(MeasureTextEx(retroFont, wpmString, 20, 1), 0.5f), 0, 20, 1, BROWN);
			DrawTextPro(retroFont, wpmString, (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 - 80}, Vector2Scale(MeasureTextEx(retroFont, wpmString, 20, 1), 0.5f), 0, 20, 1, WHITE);
			DrawTextPro(retroFont, accuracyString, (Vector2){(GetScreenWidth() / 2 + 2), GetScreenHeight() / 2 - 40 + 1}, Vector2Scale(MeasureTextEx(retroFont, accuracyString, 20, 1), 0.5f), 0, 20, 1, BROWN);
			DrawTextPro(retroFont, accuracyString, (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 - 40}, Vector2Scale(MeasureTextEx(retroFont, accuracyString, 20, 1), 0.5f), 0, 20, 1, WHITE);

            if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 65 - MeasureTextEx(retroFont, "main menu", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 65 + MeasureTextEx(retroFont, "main menu", 30, 1).y / 2))
            {
                DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 70 + 1}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, RED);
                DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 70}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, BLUE);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    exitTest = true;
                    exitTestProcess = true;
                }
            }
            else
            {
                DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2 + 3), GetScreenHeight() / 2 + 70 + 2}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, LIME);
                DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 70}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, WHITE);
            }
        }
        ClearBackground(BLACK);
        EndDrawing();
    }
    for (int i = 0; i < strlen(test_text); i++)
        input[i] = '\0';
    check = 0;
}

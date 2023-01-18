/**
 * \file spacetype_train.c
 * \brief Word and Letter Typing train mode
 * \author Mukunda Dev Adhikari <078bct049.mukunda@pcampus.edu.np>
 * \bug No Known Bug
*/

/**
 * @{ \name Letter Train variables
 * 
 * \details 3 character arrays to store characters of respective keyboard rows.
 */
char TopRowLetters[10] = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'};
char MiddleRowLetters[9] = {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l'};
char BottomRowLetters[7] = {'z', 'x', 'c', 'v', 'b', 'n', 'm'};
char RequiredLetter; //!< Stores letter which will be displayed in Letter Train process
/**
 * @}
 */


/**
 * @{ \name Word Train variables
 * 
 * \details List of Words from toprow, middlerow and bottomrow to choose from when selecting word
 */
char TopRowWords[][10] = {"queer", "wrought", "erode", "trope", "troupe", "youth", "utopia", "irony", "outhouse", "power"};
char MiddleRowWords[][10] = {"lad", "slade", "glass", "fade", "grade", "hall", "jade", "klaus", "lathe"};
char BottomRowWords[][10] = {"zoner", "xerox", "change", "vought", "broom", "noob", "mooncover"};
char *customizedWords[] =
	{
		"abstract", "conjecture", "elixir", "fervent", "gargantuan", "haphazard", "intrepid", "jubilant", "kinetic", "luminous", "maverick", "nocturnal", "orchid", "predator", "quagmire", "resilient", "saunter", "turbulent", "unwavering", "vortex", "whimsical", "xenon", "yellow", "zephyr", "allegory", "benevolent", "credence", "demeanor", "enigma", "fractal", "gusto", "hiatus", "intricacy", "jubilation", "kaleidoscope", "lucid", "magnitude", "nimble", "opulence", "pertinent", "quintessential", "responsive", "saturate", "tenacity", "unbridled", "volatile", "whirlwind", "xylophone", "yacht", "zodiac", "acumen", "bazaar", "clarity", "diligent", "empathy", "flourish", "graceful", "harmony", "intuition", "jovial", "klutz", "leverage", "mystique", "nostalgia", "overture", "persistence", "quirk", "radiance", "savvy", "transcend", "unison", "vivid", "whisper", "xylograph", "yearning", "zephyr", "affinity", "bucolic", "clandestine", "disparate", "embellish", "fluctuate", "glossary", "hiatus", "intrepid", "jubilant", "knick-knack", "legerdemain", "magnanimous", "nihilistic", "opulent", "provocative", "quintessence", "rhapsodic", "solitude", "tenacity", "unabashed", "versatility", "whirlwind", "xenophobe", "yen"
	};
char RequiredWord[10];
/**
 * @}
 */

/**
 * @{ \name Boolean to control different modes and screen
 *
 *  Different booleans to control training process and also to
 * indicatet which row is chosen for respective train modes
 *
 */
bool exitTrainWords, exitTrainLetters, MiddleRow, 
	TopRow, BottomRow, exitTrainProcess, letterinput, 
	exitTrain, trainMode, wordinput, exitResult;
/**
 * @}
 */


/**
 * @{ \name Extern variables from main
 * \details different variables initialized before 
 * that were needed for this portion
 */
extern Music music;
extern int screenWidth; 
extern int screenHeight;
extern Font retroFont;
extern Texture2D cockpitTexture; //!< Background Textures
extern Texture2D cockpitTextureKeyboard; //!< Background Texture
extern char wordStored[20];
/**
 * @}
 */



/**
 * \brief main function for train mode
 *
 * \details the background texture, continues the background 
 * music and calls train_menu function for further navigation
 */
void train()
{
	exitTrain = false;
	cockpitTextureKeyboard = LoadTexture("resources/images/cockpit_texture_keyboard.png");

	while (!exitTrain)
	{
		movingDown += mover;
		movingPlanets += mover + 0.3f;
		UpdateMusicStream(music);
		BeginDrawing();
		draw_background();
		DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
		train_menu();
		if (IsKeyDown(KEY_RIGHT))
			exitTrain = true;
		EndDrawing();
	}
}

/**
 * \brief main menu for train screen
 *
 * \details Draws the menu for the train mode. Gives the user the option
 * to choose between practicing letters or practicing words.
 */
void train_menu()
{
	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "letters", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "letters", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 155 - MeasureTextEx(retroFont, "letters", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 155 + MeasureTextEx(retroFont, "letters", 30, 1).y / 2))
	{
		DrawTextPro(retroFont, "letters", (Vector2){(GetScreenWidth() / 2) + 2, (GetScreenHeight() / 2) - 150 + 1}, Vector2Scale(MeasureTextEx(retroFont, "letters", 30, 1), 0.5f), 0, 30, 1, RED);
		DrawTextPro(retroFont, "letters", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) - 150}, Vector2Scale(MeasureTextEx(retroFont, "letters", 30, 1), 0.5f), 0, 30, 1, BLUE);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			EndDrawing();
			exitTrainLetters = false;
			trainMode = true; // to indicate that trainMode is letters
			mode_trainletters();
		}
	}
	else
	{
		DrawTextPro(retroFont, "letters", (Vector2){(GetScreenWidth() / 2), (GetScreenHeight() / 2) - 150}, Vector2Scale(MeasureTextEx(retroFont, "letters", 30, 1), 0.5f), 0, 30, 1, WHITE);
	}
	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "words", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "words", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 105 - MeasureTextEx(retroFont, "words", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 105 + MeasureTextEx(retroFont, "words", 30, 1).y / 2))
	{
		DrawTextPro(retroFont, "words", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 100 + 1}, Vector2Scale(MeasureTextEx(retroFont, "words", 30, 1), 0.5f), 0, 30, 1, RED);
		DrawTextPro(retroFont, "words", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 100}, Vector2Scale(MeasureTextEx(retroFont, "words", 30, 1), 0.5f), 0, 30, 1, BLUE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			EndDrawing();
			exitTrainWords = false;
			trainMode = false; // to indicate that trainMode is words
			mode_trainwords();
		}
	}
	else
	{
		DrawTextPro(retroFont, "words", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 100}, Vector2Scale(MeasureTextEx(retroFont, "words", 30, 1), 0.5f), 0, 30, 1, WHITE);
	}
	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "customized", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "customized", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 55 - MeasureTextEx(retroFont, "customized", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 55 + MeasureTextEx(retroFont, "customized", 30, 1).y / 2))
	{
		DrawTextPro(retroFont, "customized", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 50 + 1}, Vector2Scale(MeasureTextEx(retroFont, "customized", 30, 1), 0.5f), 0, 30, 1, RED);
		DrawTextPro(retroFont, "customized", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 50}, Vector2Scale(MeasureTextEx(retroFont, "customized", 30, 1), 0.5f), 0, 30, 1, BLUE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			EndDrawing();
			exitTrainWords = false;
			trainMode = false; // to indicate that trainMode is words
			customized_train();
		}
	}
	else
	{
		DrawTextPro(retroFont, "customized", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 50}, Vector2Scale(MeasureTextEx(retroFont, "customized", 30, 1), 0.5f), 0, 30, 1, WHITE);
	}
	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "back", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "back", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 15 - MeasureTextEx(retroFont, "back", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 15 + MeasureTextEx(retroFont, "back", 30, 1).y / 2))
	{
		DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 20 + 1}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, RED);
		DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 20}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, BLUE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			exitTrain = true;
		}
	}
	else
	{
		DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 20}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, WHITE);
	}
}

/**
 * \brief Letter Train sub menu 
 *
 * \details function that handles lettere practice mode. Clears all
 * boolean relatetd rows and train loops and calls the function
 * which draws selection menu for rows.
 */
void mode_trainletters()
{

	TopRow = false;
	MiddleRow = false;
	BottomRow = false;
	exitTrainProcess = false;
	while (!exitTrainLetters)
	{
		UpdateMusicStream(music);
		movingDown += mover;
		movingPlanets += mover + 0.3f;
		BeginDrawing();

		ClearBackground(BLACK);
		draw_background();
		DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
		train_select();

		EndDrawing();
	}
}

/**
 * \brief Word Train sub menu
 *
 * \details The function that handles words practice mode. Clears all
 * boolean relatetd rows and train loops and calls the train_select
 * function which draws selection menu for rows.
 */
void mode_trainwords()
{

	TopRow = false;
	MiddleRow = false;
	BottomRow = false;
	exitTrainProcess = false;
	while (!exitTrainWords)
	{
		UpdateMusicStream(music);
		movingDown += mover;
		movingPlanets += mover + 0.3f;
		BeginDrawing();
		ClearBackground(BLACK);
		draw_background();
		DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
		train_select();
		EndDrawing();
	}
}

/**
 * \brief Handles processes regarding training typing letters
 *
 * \details The function that handles resetting of variables by calling
 * reset_counter, and contains the loop which selects the new
 * letter (using select_letter) and a nested loop to check if the
 * input letter matches with the displayed one.
 */
void letter_train()
{
	reset_counter();
	exitTrainProcess = false;
	while (!exitTrainProcess)
	{
		BeginDrawing();
		select_letter();
		exitTrainProcess = false;
		letterinput = false;

		while (!letterinput)
		{
			UpdateMusicStream(music);
			char requiredtxt[2] = {0};
			movingDown += mover;
			movingPlanets += mover + 0.3f;
			sprintf(requiredtxt, "%c ", RequiredLetter);
			BeginDrawing();
			ClearBackground(BLACK);
			draw_background();
			DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
			DrawTextEx(retroFont, requiredtxt, (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2 - 100}, 30, 2, WHITE);
			keyboard_highlight(RequiredLetter); 

			int key = ((int)RequiredLetter) - 32;
			int pressed = GetKeyPressed();
			if (pressed && pressed != key)
			{
				fprintf(wrongChars, "%c", key);
				sorted = false;
			}
			if (IsKeyPressed(key))
				letterinput = true;

			if (IsKeyPressed(KEY_ESCAPE))
			{
				letterinput = true;
				exitTrainProcess = true;
			}
			EndDrawing();
		}
		EndDrawing();
	}
}

/**
 * \brief Handles processes regarding training typing words 
 *
 * \details The function that handles resetting of variables by calling
 * reset_counter, and contains the loop which selects the new
 * word (using select_word) and a nested loop which ends when
 * the user has finished enterring the word. It calls remove_firstletter
 * each time the letter input matches the letter displayed. Once
 * the user chooses to leave the train process, by pressing ESC, a
 * stats screen is displayed which shows their WPM, fastest word,
 * slowest word, etc.
 */
void word_train()
{
	reset_counter();
	exitTrainProcess = false;
	while (!exitTrainProcess)
	{
		BeginDrawing();
		select_word();
		exitTrainProcess = false;
		int textWidth;
		wordinput = false;
		strcpy(wordStored, RequiredWord);

		while (!wordinput)
		{
			UpdateMusicStream(music);
			movingDown += mover;
			movingPlanets += mover + 0.3f;
			textWidth = MeasureTextEx(retroFont, RequiredWord, 30, 2).x;
			BeginDrawing();
			framesCounterForSession++;
			framesCounterForWord++;
			ClearBackground(BLACK);
			draw_background();
			DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
			DrawTextEx(retroFont, RequiredWord, (Vector2){(GetScreenWidth() / 2) - (textWidth / 2), GetScreenHeight() / 2 - 100}, 30, 2, WHITE);
			keyboard_highlight(RequiredWord[0]); 

			int key = ((int)RequiredWord[0]) - 32;
			int pressed = GetKeyPressed();
			if (pressed)
			{
				keysPressed++;
				if (pressed != key)
					fprintf(wrongChars, "%c", key);
				sorted = false;
			}
			if (IsKeyPressed(key))
			{
				rightKeysPressed++;
				remove_firstletter(RequiredWord);
				if (strlen(RequiredWord) == 0)
				{ // UPDATING DATA
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

					SCORE++;
					wordinput = true;
					framesCounterForWord = 0;
				}
			}
			if (IsKeyPressed(KEY_ESCAPE))
			{
				wordinput = true;
				exitTrainProcess = true;
			}
			EndDrawing();
		}
		EndDrawing();
	}

	while (!exitResult)
	{
		if (SCORE == 0)
		{
			fastestWordFrames = 0;
			if (keysPressed == 0)
				keysPressed = 1;
		}
		UpdateMusicStream(music);
		char scoreString[50];
		char sessionDurationString[50];
		char fastestWordString[50];
		char fastestTimeString[50];
		char slowestWordString[50];
		char slowestTimeString[50];
		char wpmString[50];
		char accuracyString[50];

		sprintf(scoreString, "Score : %i", SCORE);
		sprintf(sessionDurationString, "Session time : %.2f seconds", framesCounterForSession / 60);
		sprintf(fastestWordString, "Fastest Word:  | %s |", fastestWord);
		sprintf(fastestTimeString, "Time: %.2f seconds", fastestWordFrames / 60);
		sprintf(slowestWordString, "Slowest Word:  | %s |", slowestWord);
		sprintf(slowestTimeString, "Time: %.2f seconds", slowestWordFrames / 60);
		sprintf(wpmString, "Typing Speed: %d WPM", (int)(SCORE * 60 * 60 / framesCounterForSession));
		sprintf(accuracyString, "Accuracy: %.2f%%", (rightKeysPressed / keysPressed) * 100);
		BeginDrawing();
		draw_background();
		DrawTextEx(retroFont, "RESULTS", (Vector2){screenWidth / 2 - 200 + 5, screenHeight / 2 - 250 + 4}, 80, 1, DARKBLUE);
		DrawTextEx(retroFont, "RESULTS", (Vector2){screenWidth / 2 - 200, screenHeight / 2 - 250}, 80, 1, WHITE);
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

		if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 255 - MeasureTextEx(retroFont, "main menu", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 255 + MeasureTextEx(retroFont, "main menu", 30, 1).y / 2))
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 260 + 1}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, RED);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 260}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				exitResult = true;
				exitTrainLetters = true;
				exitTrainWords = true;
				exitTrain = true;
			}
		}
		else
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2 + 3), GetScreenHeight() / 2 + 260 + 2}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, LIME);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 260}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, WHITE);
		}
		EndDrawing();
	}
}

/**
 * \brief Handles processes regarding cuztomized train mode
 *
 * \details This function is a child of word_train. So, it does everything
 * the word_train does but the words it provides to train you are
 * customized and contains the letters that you have typed wrong the most.
 * It is done by storing wrongly typed letters and comparing them with
 * the letters in the word that will be displayed.
 */
void customized_train()
{
	reset_counter();
	exitTrainProcess = false;

	while (!exitTrainProcess)
	{
		BeginDrawing();
		int letterPresent = 0;
		while(letterPresent < 5){ 
			strcpy(RequiredWord, customizedWords[GetRandomValue(0, (sizeof(customizedWords)/sizeof(customizedWords[0]))-1)]);
			for (int i=0; i<strlen(RequiredWord); i++){
				for (int j=0; j<8; j++){
					if ((int)wrongLetters[0].character == (int)RequiredWord[i] - 32) letterPresent++;
				}
			}
		}
		exitTrainProcess = false;
		int textWidth;
		wordinput = false;
		strcpy(wordStored, RequiredWord);

		while (!wordinput)
		{
			UpdateMusicStream(music);
			movingDown += mover;
			movingPlanets += mover + 0.3f;
			textWidth = MeasureTextEx(retroFont, RequiredWord, 30, 2).x;
			BeginDrawing();
			framesCounterForSession++;
			framesCounterForWord++;
			ClearBackground(BLACK);
			draw_background();
			DrawTextureEx(cockpitTextureKeyboard, (Vector2){0, 0}, 0, 1, WHITE);
			DrawTextEx(retroFont, RequiredWord, (Vector2){(GetScreenWidth() / 2) - (textWidth / 2), GetScreenHeight() / 2 - 100}, 30, 2, WHITE);
			keyboard_highlight(RequiredWord[0]); 

			int key = ((int)RequiredWord[0]) - 32;
			int pressed = GetKeyPressed();
			if (pressed)
			{
				keysPressed++;
				if (pressed != key)
					fprintf(wrongChars, "%c", key);
				sorted = false;
			}
			if (IsKeyPressed(key))
			{
				rightKeysPressed++;
				remove_firstletter(RequiredWord);
				if (strlen(RequiredWord) == 0)
				{ // UPDATING DATA
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

					SCORE++;
					wordinput = true;
					framesCounterForWord = 0;
				}
			}
			if (IsKeyPressed(KEY_ESCAPE))
			{
				wordinput = true;
				exitTrainProcess = true;
			}
			EndDrawing();
		}
		EndDrawing();
	}

	while (!exitResult)
	{
		if (SCORE == 0)
		{
			fastestWordFrames = 0;
			if (keysPressed == 0)
				keysPressed = 1;
		}
		UpdateMusicStream(music);
		char scoreString[50];
		char sessionDurationString[50];
		char fastestWordString[50];
		char fastestTimeString[50];
		char slowestWordString[50];
		char slowestTimeString[50];
		char wpmString[50];
		char accuracyString[50];

		sprintf(scoreString, "Score : %i", SCORE);
		sprintf(sessionDurationString, "Session time : %.2f seconds", framesCounterForSession / 60);
		sprintf(fastestWordString, "Fastest Word:  | %s |", fastestWord);
		sprintf(fastestTimeString, "Time: %.2f seconds", fastestWordFrames / 60);
		sprintf(slowestWordString, "Slowest Word:  | %s |", slowestWord);
		sprintf(slowestTimeString, "Time: %.2f seconds", slowestWordFrames / 60);
		sprintf(wpmString, "Typing Speed: %d WPM", (int)(SCORE * 60 * 60 / framesCounterForSession));
		sprintf(accuracyString, "Accuracy: %.2f%%", (rightKeysPressed / keysPressed) * 100);
		BeginDrawing();
		draw_background();
		DrawTextEx(retroFont, "RESULTS", (Vector2){screenWidth / 2 - 200 + 5, screenHeight / 2 - 250 + 4}, 80, 1, DARKBLUE);
		DrawTextEx(retroFont, "RESULTS", (Vector2){screenWidth / 2 - 200, screenHeight / 2 - 250}, 80, 1, WHITE);
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

		if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "main menu", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 255 - MeasureTextEx(retroFont, "main menu", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 255 + MeasureTextEx(retroFont, "main menu", 30, 1).y / 2))
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 260 + 1}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, RED);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 260}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				exitResult = true;
				exitTrainLetters = true;
				exitTrainWords = true;
				exitTrain = true;
			}
		}
		else
		{
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2 + 3), GetScreenHeight() / 2 + 260 + 2}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, LIME);
			DrawTextPro(retroFont, "main menu", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 260}, Vector2Scale(MeasureTextEx(retroFont, "main menu", 30, 1), 0.5f), 0, 30, 1, WHITE);
		}
		EndDrawing();
	}
}

/**
 * \brief Option menu for choosing rows for both letter mode and word mode
 *
 * \details This function generates the option menu for the user to choose
 * the rows that he wants to practice. Checkbox indicator are
 * present to indicate the rows chose. letter_train or word_train
 * are called based on the user's previous selection
 */
void train_select()
{

	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - 150) && (float)GetMouseX() <= (GetScreenWidth() / 2 - 150 + MeasureTextEx(retroFont, "top row letters", 30, 1).x) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 195) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 195 + MeasureTextEx(retroFont, "top row letters", 30, 1).y))
	{
		DrawTextEx(retroFont, "top row letters", (Vector2){(GetScreenWidth() / 2) - 150 + 2, GetScreenHeight() / 2 - 195 + 1}, 30, 1, RED);
		DrawTextEx(retroFont, "top row letters", (Vector2){(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 195}, 30, 1, BLUE);
		if (!TopRow)
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 200, 30, 30, WHITE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				TopRow = true;
				DrawRectangle(GetScreenWidth() / 2 - 210 + 5, (GetScreenHeight() / 2 - 195), 20, 20, BLUE);
			}
		}
		else
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 200, 30, 30, WHITE);
			DrawRectangle(GetScreenWidth() / 2 - 210 + 5, GetScreenHeight() / 2 - 195, 20, 20, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				TopRow = false;
			}
		}
	}
	else
	{
		DrawTextEx(retroFont, "top row letters", (Vector2){(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 195}, 30, 1, WHITE);
		if (!TopRow)
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 200, 30, 30, WHITE);
		}
		else
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 200, 30, 30, WHITE);
			DrawRectangle(GetScreenWidth() / 2 - 210 + 5, GetScreenHeight() / 2 - 195, 20, 20, BLUE);
		}
	}
	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - 150) && (float)GetMouseX() <= (GetScreenWidth() / 2 - 150 + MeasureTextEx(retroFont, "middle row letters", 30, 1).x) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 145) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 145 + MeasureTextEx(retroFont, "middle row letters", 30, 1).y))
	{
		DrawTextEx(retroFont, "middle row letters", (Vector2){(GetScreenWidth() / 2) - 150 + 2, GetScreenHeight() / 2 - 145 + 1}, 30, 1, RED);
		DrawTextEx(retroFont, "middle row letters", (Vector2){(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 145}, 30, 1, BLUE);
		if (!MiddleRow)
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 150, 30, 30, WHITE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				MiddleRow = true;
				DrawRectangle(GetScreenWidth() / 2 - 210 + 5, (GetScreenHeight() / 2 - 145), 20, 20, BLUE);
			}
		}
		else
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 150, 30, 30, WHITE);
			DrawRectangle(GetScreenWidth() / 2 - 210 + 5, GetScreenHeight() / 2 - 145, 20, 20, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				MiddleRow = false;
			}
		}
	}
	else
	{
		DrawTextEx(retroFont, "middle row letters", (Vector2){(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 145}, 30, 1, WHITE);
		if (!MiddleRow)
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 150, 30, 30, WHITE);
		}
		else
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 150, 30, 30, WHITE);
			DrawRectangle(GetScreenWidth() / 2 - 210 + 5, GetScreenHeight() / 2 - 145, 20, 20, BLUE);
		}
	}
	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - 150) && (float)GetMouseX() <= (GetScreenWidth() / 2 - 150 + MeasureTextEx(retroFont, "bottom row letters", 30, 1).x) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 95) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 95 + MeasureTextEx(retroFont, "bottom row letters", 30, 1).y))
	{
		DrawTextEx(retroFont, "bottom row letters", (Vector2){(GetScreenWidth() / 2) - 150 + 2, GetScreenHeight() / 2 - 95 + 1}, 30, 1, RED);
		DrawTextEx(retroFont, "bottom row letters", (Vector2){(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 95}, 30, 1, BLUE);
		if (!BottomRow)
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 100, 30, 30, WHITE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				BottomRow = true;
				DrawRectangle(GetScreenWidth() / 2 - 210 + 5, (GetScreenHeight() / 2 - 95), 20, 20, BLUE);
			}
		}
		else
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 100, 30, 30, WHITE);
			DrawRectangle(GetScreenWidth() / 2 - 210 + 5, GetScreenHeight() / 2 - 95, 20, 20, BLUE);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				BottomRow = false;
			}
		}
	}
	else
	{
		DrawTextEx(retroFont, "bottom row letters", (Vector2){(GetScreenWidth() / 2) - 150, GetScreenHeight() / 2 - 95}, 30, 1, WHITE);
		if (!BottomRow)
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 100, 30, 30, WHITE);
		}
		else
		{
			DrawRectangle(GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 100, 30, 30, WHITE);
			DrawRectangle(GetScreenWidth() / 2 - 210 + 5, GetScreenHeight() / 2 - 95, 20, 20, BLUE);
		}
	}
	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "start training", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "start training", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 - 10 - MeasureTextEx(retroFont, "words", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 - 10 + MeasureTextEx(retroFont, "words", 30, 1).y / 2))
	{
		DrawTextPro(retroFont, "start training", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 5 + 1}, Vector2Scale(MeasureTextEx(retroFont, "start training", 30, 1), 0.5f), 0, 30, 1, RED);
		DrawTextPro(retroFont, "start training", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 - 5}, Vector2Scale(MeasureTextEx(retroFont, "start training", 30, 1), 0.5f), 0, 30, 1, BLUE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			exitResult = false;
			if (BottomRow == false && TopRow == false && MiddleRow == false)
			{
			}
			else
			{
				EndDrawing();
				if (trainMode) // trainMode = true implies training letters
				{
					letter_train();
				}
				else if (!trainMode)
				{
					word_train();
				}
			}
		}
	}
	else
	{
		DrawTextPro(retroFont, "Start Training", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 - 5}, Vector2Scale(MeasureTextEx(retroFont, "start training", 30, 1), 0.5f), 0, 30, 1, WHITE);
	}

	if ((float)GetMouseX() >= (GetScreenWidth() / 2 - MeasureTextEx(retroFont, "back", 30, 1).x / 2) && (float)GetMouseX() <= (GetScreenWidth() / 2 + MeasureTextEx(retroFont, "back", 30, 1).x / 2) && (float)GetMouseY() >= (GetScreenHeight() / 2 + 40 - MeasureTextEx(retroFont, "words", 30, 1).y / 2) && (float)GetMouseY() <= (GetScreenHeight() / 2 + 40 + MeasureTextEx(retroFont, "words", 30, 1).y / 2))
	{
		DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 45 + 1}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, RED);
		DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2), GetScreenHeight() / 2 + 45}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, BLUE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			exitTrainLetters = true;
			exitTrainWords = true;
		}
	}
	else
	{
		DrawTextPro(retroFont, "back", (Vector2){(GetScreenWidth() / 2) + 2, GetScreenHeight() / 2 + 45}, Vector2Scale(MeasureTextEx(retroFont, "back", 30, 1), 0.5f), 0, 30, 1, WHITE);
	}
}

/**
 * \brief function which selects letter to display for letter train process
 *
 * \details letter using the the three choices, random number
 * generator and a switch case based on the choice and number
 * generated. Stores that letter in RequiredLetter.
 */
void select_letter()
{
	// Convert the three choices into binary number
	int RowChoice = 100 * MiddleRow + 10 * TopRow + 1 * BottomRow;

	// make a random number to choose a random row.
	int RandomRow = rand() % (MiddleRow + TopRow + BottomRow) + 1;

	int RandomUpperLetter, RandomMiddleLetter, RandomLowerLetter;

	/* select random number from a certain number range based on size of the respective row words array)*/
	RandomUpperLetter = rand() % 10;
	RandomMiddleLetter = rand() % 9;
	RandomLowerLetter = rand() % 7;

	switch (RowChoice)
	{
	/*lower only*/ case 1:
		RequiredLetter = BottomRowLetters[RandomLowerLetter];
		break;
	/*upper only*/ case 10:
		RequiredLetter = TopRowLetters[RandomUpperLetter];
		break;

	case 11:
		switch (RandomRow)
		{
		case 1:
			RequiredLetter = TopRowLetters[RandomUpperLetter];
			break;
		case 2:
			RequiredLetter = BottomRowLetters[RandomLowerLetter];
			break;
		}
		break;
	/*middle only*/ case 100:
		RequiredLetter = MiddleRowLetters[RandomMiddleLetter];
		break;

	case 101:
		switch (RandomRow)
		{
		case 1:
			RequiredLetter = MiddleRowLetters[RandomMiddleLetter];
			break;
		case 2:
			RequiredLetter = BottomRowLetters[RandomLowerLetter];
			break;
		}
		break;

	case 110:
		switch (RandomRow)
		{
		case 1:
			RequiredLetter = MiddleRowLetters[RandomMiddleLetter];
			break;
		case 2:
			RequiredLetter = TopRowLetters[RandomUpperLetter];
			break;
		}
		break;
		/*All the rows*/
	case 111:
		switch (RandomRow)
		{
		case 1:
			RequiredLetter = MiddleRowLetters[RandomMiddleLetter];
			break;
		case 2:
			RequiredLetter = TopRowLetters[RandomUpperLetter];
			break;
		case 3:
			RequiredLetter = BottomRowLetters[RandomLowerLetter];
			break;
		}
		break;

	default:
		break;
	}
}

/**
 * \brief function which selects words to display for word train process
 *
 * \details Selects a word using the the three choices, random number
 * generator and a switch case based on the choice and number
 * generated. Stores that word in RequiredWord.
 */
void select_word()
{
	// Convert the three choices into binary numbers for switch case.
	int RowChoice = 100 * MiddleRow + 10 * TopRow + 1 * BottomRow;

	// make a random number to choose a random row.
	int RandomRow = rand() % (MiddleRow + TopRow + BottomRow) + 1;

	int RandomUpperWord, RandomMiddleWord, RandomLowerWord;

	/* select random number from a certain number range based on size of the respective row words array)*/
	RandomUpperWord = rand() % 10;
	RandomMiddleWord = rand() % 9;
	RandomLowerWord = rand() % 7;

	switch (RowChoice)
	{
	/*lower only*/ case 1:
		strcpy(RequiredWord, BottomRowWords[RandomLowerWord]);
		break;

	/*upper only*/ case 10:
		strcpy(RequiredWord, TopRowWords[RandomUpperWord]);
		break;

	case 11:
		switch (RandomRow)
		{
		case 1:
			strcpy(RequiredWord, TopRowWords[RandomUpperWord]);
			break;
		case 2:
			strcpy(RequiredWord, BottomRowWords[RandomLowerWord]);
			break;
		}
		break;

	/*middle only*/ case 100:
		strcpy(RequiredWord, MiddleRowWords[RandomMiddleWord]);
		break;
	
	
	case 101:
		switch (RandomRow)
		{
		case 1:
			strcpy(RequiredWord, MiddleRowWords[RandomMiddleWord]);
			break;
		case 2:
			strcpy(RequiredWord, BottomRowWords[RandomLowerWord]);
			break;
		}
		break;

	case 110:
		switch (RandomRow)
		{
		case 1:
			strcpy(RequiredWord, MiddleRowWords[RandomMiddleWord]);
			break;
		case 2:
			strcpy(RequiredWord, TopRowWords[RandomUpperWord]);
			break;
		}
		break;

	case 111:
		switch (RandomRow)
		{
		case 1:
			strcpy(RequiredWord, MiddleRowWords[RandomMiddleWord]);
			break;
		case 2:
			strcpy(RequiredWord, TopRowWords[RandomUpperWord]);
			break;
		case 3:
			strcpy(RequiredWord, BottomRowWords[RandomLowerWord]);
			break;
		}
		break;
	default:
		break;
	}
}
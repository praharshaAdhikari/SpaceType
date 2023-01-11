#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <raymath.h>

void draw_background(); //funciton to draw the space background
void calculate_result(); //funciton to calculate result of each mode
void reset_counter(); //funciton to reset counter for each mode
void remove_firstletter(char word[]); //function to reset first letter for word train and game
void pause_screen(); // screen which is shown when the application is paused
struct charCount{
	char character;
	int count;
} wrongLetters[26]; // structure for wrongLetters in order of frequency
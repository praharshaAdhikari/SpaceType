
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <raymath.h>

void draw_background(); 
void reset_counter(); 
void remove_firstletter(char word[]); 
void pause_screen(); 
void tutorial_screen();
void keyboard_highlight (char a);
/** @struct charCount
 *  @brief This structure stores mistyped characters and their frequency
 *  @var charCount::character 
 *  Member 'character' contains the mistyped character
 *  @var charCount::count
 *  Member 'count' contains the the mistyped character's frequency
 */
struct charCount{
	char character;
	int count;
} wrongLetters[26]; 
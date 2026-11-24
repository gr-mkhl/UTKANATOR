#ifndef _AKINATOR_GRAPHIC_H_
#define _AKINATOR_GRAPHIC_H_

#include <raylib.h>
#include <tree.h>
#include <log.h>
#include <graphic_tools.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define YES_NO_FONT_SIZE 60
#define MENU_BUTTONS_FONT_SIZE 40
#define AKINATOR_BUTTONS_FONT_SIZE 40
#define ARRAY_SIZE(array) ((sizeof(array)) / (sizeof(array[0])))

int letters = 0;
char string[100] = {};

char name1[100] = {};
char name2[100] = {};

char buffer[256] = {};
char error_buffer[100] = {};

stack_t path_stack1 = {};
stack_t path_stack2 = {};

Texture2D not_found_duck;
Texture2D thinking_duck;
Texture2D prime_duck;
Texture2D sad_duck;
Texture2D forest;

Sound loose_sound;
Sound win_sound;
Sound click_sound;

enum menu_buttons
{
    QUIT = 0,
    PLAY = 1,
    SAVE = 2,
    LOAD = 3,
    DEF  = 4,
    COMP = 5
};

enum akinator_buttons
{
    NEXT = 0,
    YES = 1,
    NO = 2,
};

enum dc_buttons
{
    DC_BACK = 0,
    DC_NEXT = 1
};

enum sl_buttons
{
    SAVE_BUTTON = 0,
    LOAD_BUTTON = 1,
    BACK_BUTTON = 2
};

enum akinator_screens_t
{
    FIRST_SCREEN = 0,
    ADD_FIRST_ELEMENT = 1,
    QUESTION_SCREEN = 2,
    LAST_QUESTION_SCREEN = 3,
    LAST_QUESTION_SCREEN_YES = 4,
    LAST_QUESTION_SCREEN_NO1 = 5,
    LAST_QUESTION_SCREEN_NO2 = 6,
};

enum screen_status
{
    SCREEN_MENU = 0,
    SCREEN_AKINATOR = 1,
    SCREEN_LOAD = 2,
    SCREEN_SAVE = 3,
    SCREEN_DEFINITION_INPUT = 4,
    SCREEN_DEFINITION_OUTPUT = 5,
    SCREEN_COMPARISON_INPUT_FIRST = 6,
    SCREEN_COMPARISON_INPUT_SECOND = 7,
    SCREEN_COMPARISON_OUTPUT = 8,
    SCREEN_ERROR = 9
};


void StartAkinatorGraphicGame();

void InitAkinatorTexturesAndSounds();
void UninitAkinatorTexturesAndSounds();

void InitPathStacksForDefAndCompModes();
void UninitPathStacksForDefAndCompModes();

void DrawAkinatorBackground();

int  DrawDCScreen( screen_status current_screen, button_t* buttons, size_t size );
int  DrawSLScreen( screen_status current_screen, button_t* buttons, size_t size );
int  DrawAkinatorGameScreen( akinator_screens_t akinator_screen, leaf_t* current, button_t* buttons, size_t size );
void AkinatorSetButtonsVisibility( akinator_screens_t akinator_screen, button_t* buttons );
void AkinatorScreenNextButtonPushed( screen_status* current_screen, akinator_screens_t* akinator_screen, leaf_t** root, leaf_t **current );
int  DrawMenuScreen( button_t* buttons, size_t size );
void SLSetButtonsVisibility( screen_status current_screen, button_t* buttons );

void ReverseStack( stack_t* stack );
#endif

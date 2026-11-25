 #ifndef _AKINATOR_GRAPHIC_H_
#define _AKINATOR_GRAPHIC_H_

#include <raylib.h>
#include <tree.h>
#include <log.h>
#include <graphic_tools.h>

#define SW  800
#define SH 600
#define YES_NO_FONT_SIZE 60
#define MENU_BUTTONS_FONT_SIZE 40
#define AKINATOR_BUTTONS_FONT_SIZE 40
#define ARRAY_SIZE(array) ((sizeof(array)) / (sizeof(array[0])))


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
};                                                                                                                                                                                                                                    char name1[100] = {}; char name2[100] = {};

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
};                                                                                                                                                                                                                                   char buffer[256] = {}; char error_buffer[100] = {};

struct game_context_t
{
    leaf_t* root;
    leaf_t* current;

    button_t* MenuButtons;
    size_t num_MenuButtons;

    button_t* AkinatorScreenButtons;
    size_t num_AkinatorScreenButtons;

    button_t* SLScreenButtons;
    size_t num_SLScreenButtons;

    button_t* DCScreenButtons;
    size_t num_DCScreenButtons;

    button_t* back_to_menu_button;

    texture_t* AkinatorTextures;
    size_t num_AkinatorTextures;

    sound_t* AkinatorSounds;
    size_t num_AkinatorSounds;

    screen_status current_screen;
    akinator_screens_t akinator_screen;

    stack_t* path_stack1;
    stack_t* path_stack2;

    char string[100];
    int letters;
};

void InitAkinatorContext( game_context_t* AkinatorContext );
void StartAkinatorGraphicGame();
void AkinatorGameLoop( game_context_t* AkinatorContext );

void InitTexturesArray( texture_t* textures_arr, size_t array_len );
void InitSoundsArray  ( sound_t* sounds_arr, size_t array_len );

void UninitTexturesArray( texture_t* textures_arr, size_t array_len );
void UninitSoundsArray( sound_t* sounds_arr, size_t array_len );

void InitPathStacksForDefAndCompModes( stack_t* path_stack1, stack_t* path_stack2 );
void UninitPathStacksForDefAndCompModes( stack_t* path_stack1, stack_t* path_stack2 );

void DrawAkinatorBackground( texture_t background );

int  DrawDCScreen( screen_status current_screen, button_t* buttons,
                   size_t size, Sound click_sound, char* string, int* letters );
int  DrawSLScreen( screen_status current_screen, button_t* buttons,
                   size_t size, Sound click_sound, char* string, int* letters );
int  DrawAkinatorGameScreen( akinator_screens_t akinator_screen, leaf_t* current,
                            button_t* buttons, size_t size, texture_t* textures,
                            Sound click_sound, char* string, int* letters );
void AkinatorSetButtonsVisibility( akinator_screens_t akinator_screen, button_t* buttons );
void AkinatorScreenNextButtonPushed( screen_status* current_screen, akinator_screens_t* akinator_screen,
                                    leaf_t** root, leaf_t **current, char* string, int* letters );
int  DrawMenuScreen( button_t* buttons, size_t size, texture_t* textures, Sound click_sound );
void SLSetButtonsVisibility( screen_status current_screen, button_t* buttons );

void ReverseStack( stack_t* stack );

int  MenuScreenVisual( game_context_t* AkinatorContext );
void SaveModeScreen( game_context_t* AkinatorContext );
void LoadModeScreen( game_context_t* AkinatorContext );
void ErrorScreen( game_context_t* AkinatorContext );
void AkinatorScreen( game_context_t* AkinatorContext );
void ScreenCompareModeAddingFirstCharacter( game_context_t* AkinatorContext );
void ScreenCompareModeAddingSecondCharacter( game_context_t* AkinatorContext );
void ScreenCompareModeOutputResult( game_context_t* AkinatorContext );
void ScreenDefModeOutputResult( game_context_t* AkinatorContext );
void ScreenDefModeInputCharacter( game_context_t* AkinatorContext );

#endif

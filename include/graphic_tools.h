#ifndef _GRAPHIC_TOOLS_H_
#define _GRAPHIC_TOOLS_H_

#include <raylib.h>
#include <tree.h>

//TODO сделать еще один .h?
#define SW 800
#define SH 600


struct position_t
{
    int x;
    int y;
};

struct button_t
{
    const char* button_text;
    Rectangle button_rect;
    int font;
    Color common_color;
    Color mouse_on_color;
    int TextX;
    int TextY;
    bool is_mouse_on;
    bool is_invis;
};

struct texture_t
{
    Texture2D texture;
    const char* filename;
};

enum texture_id
{
    not_found_duck    = 0,
    thinking_duck     = 1,
    prime_duck        = 2,
    sad_duck          = 3,
    forest_background = 4
};

struct sound_t
{
    Sound sound;
    const char* filename;
};

enum sound_id
{
    click_sound = 0,
    win_sound   = 1,
    loose_sound = 2
};

position_t ButtonTextPosition( Rectangle button, const char* text, int font );
void       CleanInputBarBuffer( char* string, int* letters );
void       DrawButtons( button_t* buttons, size_t size, Color color );
void       DrawInputBar( int top_y, int text_font, char* output_string, int* output_str_len );
void       DrawSignature( const char* project_name );
void       DrawTextBeautiful(const char* text, int top_y, int text_font, Color color);
int        CheckButtonsStatus( button_t* buttons, size_t size, Sound click_sound );
void       SetButtonsTextPosition( button_t* buttons, size_t size );

#endif

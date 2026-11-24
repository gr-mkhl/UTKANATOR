#ifndef _GRAPHIC_TOOLS_H_
#define _GRAPHIC_TOOLS_H_

#include <raylib.h>
#include <tree.h>

extern Sound click_sound;

//TODO сделать еще один .h?
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


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


position_t ButtonTextPosition( Rectangle button, const char* text, int font );
void       DrawButtons( button_t* buttons, size_t size, Color color );
void       DrawInputBar( int top_y, int text_font, char* output_string, int* output_str_len );
void       DrawSignature( const char* project_name );
void       DrawTextBeautiful(const char* text, int top_y, int text_font, Color color);
int        CheckButtonsStatus( button_t* buttons, size_t size );
void       SetButtonsTextPosition( button_t* buttons, size_t size );

#endif

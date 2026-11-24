#include <graphic_tools.h>

position_t ButtonTextPosition( Rectangle button, const char* text, int font )
{
    int text_width = MeasureText(text, font);
    return {(int)button.x + ((int)button.width - text_width) / 2, (int)button.y + ((int)button.height - font) / 2};
}

void DrawButtons( button_t* buttons, size_t size, Color color )
{
    for (size_t i = 0; i < size; i++)
    {
        if (buttons[i].is_invis == false)
        {
            DrawRectangleRec(buttons[i].button_rect, (buttons[i].is_mouse_on == true ?  buttons[i].mouse_on_color : buttons[i].common_color));
            DrawText(buttons[i].button_text, buttons[i].TextX, buttons[i].TextY, buttons[i].font, color);
        }
    }
}

void DrawInputBar( int top_y, int text_font, char* output_string, int* output_str_len )
{
    Rectangle text_box = {0.1 * SCREEN_WIDTH, (float)top_y, 0.68 * SCREEN_WIDTH, (float)(text_font + 10)};


    int key = GetCharPressed();

    while (key > 0)
    {
        if ((key >= 32) && (key <= 125) && (*output_str_len < 99))
        {
            output_string[*output_str_len] = (char)key;
            (*output_str_len)++;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE))
    {
        (*output_str_len)--;
        if (*output_str_len < 0)
            *output_str_len = 0;
        output_string[(*output_str_len)] = '\0';
    }


    DrawRectangleRec(text_box, {0xF8, 0xED, 0xAD, 255});
    for (int i = 0; i < *output_str_len; i++)
    {
        if ((float)MeasureText(output_string + i, text_font) < text_box.width)
        {
            DrawText(output_string + i, (int)text_box.x + 5, (int)text_box.y + 5, text_font, {0xED, 0x7C, 0x30, 255});
            break;
        }
    }
    if (*output_str_len == 0)
        DrawText("type here:", (int)text_box.x + 5, (int)text_box.y + 5, text_font - 5, {0xD8, 0xCD, 0x8D, 255});
}

void DrawSignature( const char* project_name )
{
    DrawText(project_name, 10, 10, 20, GRAY);
    DrawText("by gr-mkhl", 10, 30, 20, GRAY);
}

void DrawTextBeautiful(const char* text, int top_y, int text_font, Color color) //TODO - сделать по красоте
{
    while (MeasureText(text, text_font) > 0.9 * SCREEN_WIDTH )
        text_font -= 2;
    DrawText(text, (SCREEN_WIDTH - MeasureText(text, text_font)) / 2, top_y, text_font, color);
}

int CheckButtonsStatus( button_t* buttons, size_t size )
{
    for (size_t i = 0; i < size; i++)
    {
        if (buttons[i].is_invis == false)
        {

            if (CheckCollisionPointRec(GetMousePosition(), buttons[i].button_rect))
            {
                buttons[i].is_mouse_on = true;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    PlaySound(click_sound);
                    return (int)i;
                }
            }
            else
                buttons[i].is_mouse_on = false;
        }
    }
    return -1;
}

void SetButtonsTextPosition(button_t* buttons, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        position_t text_position = ButtonTextPosition(buttons[i].button_rect, buttons[i].button_text, buttons[i].font);
        buttons[i].TextX = text_position.x;
        buttons[i].TextY = text_position.y;
    }
}

#include <graphic_akinator.h>

int main()
{
    ON_LOG(STARTLOG())
    SetTraceLogLevel(LOG_NONE);
    InitWindow(SW, SH, "Utkanator");
    SetTargetFPS(60);

    InitAudioDevice();

    StartAkinatorGraphicGame();

    CloseAudioDevice();


    ON_LOG(ENDLOG())

    return 0;
}


void StartAkinatorGraphicGame()
{

    stack_t path_stack1 = {};
    stack_t path_stack2 = {};


    button_t MenuButtons[] =
    {
        [QUIT] = {"QUIT", {SW * 0.7, SH * 0.75, SW * 0.15, 60},
                    MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [PLAY] = {"PLAY", {SW * 0.5, SH * 0.75, SW * 0.15, 60},
                    MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [SAVE] = {"SAVE", {SW * 0.3, SH * 0.75, SW * 0.15, 60},
                    MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [LOAD] = {"LOAD", {SW * 0.1, SH * 0.75, SW * 0.15, 60},
                    MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [DEF]  = {"DEFINITION", {SW * 0.18, SH * 0.87, SW * 0.27, 60},
                    MENU_BUTTONS_FONT_SIZE - 10, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [COMP]  = {"COMPARISON", {SW * 0.5, SH * 0.87, SW * 0.27, 60},
                    MENU_BUTTONS_FONT_SIZE - 10, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}}
    };

    button_t AkinatorScreenButtons[] =
    {
        [NEXT] = {"NEXT", {SW * 0.8, SH * 0.6, SW * 0.15, 60},
                    AKINATOR_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [YES]  = {"YES",  {SW * 0.2, SH * 0.6, SW * 0.25, SH * 0.25},
                    YES_NO_FONT_SIZE, GREEN, DARKGREEN},
        [NO]  =  {"NO",   {(float)(SW * 0.55), SH * 0.6, SW * 0.25, SH * 0.25},
                    YES_NO_FONT_SIZE, RED, {0xA0, 0, 0, 255}}
    };

    button_t DCScreenButtons[] =
    {
        [DC_BACK] = {"BACK", {SW * 0.35, SH * 0.8, SW * 0.30, 60},
                        60, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [DC_NEXT] = {"NEXT", {SW * 0.8, SH * 0.6, SW * 0.15, 60},
                        AKINATOR_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}}
    };

    button_t back_to_menu_button = {"BACK TO MENU", {SW * 0.23, SH * 0.8, SW * 0.54, SH * 0.13},
                            50, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}};

    texture_t AkinatorTextures[] =
    {
        [not_found_duck]    = {{}, "style/not_found_duck.png"},
        [thinking_duck]     = {{}, "style/thinking_duck.png"},
        [prime_duck]        = {{}, "style/prime_duck_no_bg.png"},
        [sad_duck]          = {{}, "style/sad_duck.png"},
        [forest_background] = {{}, "style/forest.png"}
    };

    sound_t AkinatorSounds[] =
    {
        [click_sound] = {{}, "style/clickclick.mp3"},
        [win_sound]   = {{}, "style/win_sound.mp3"},
        [loose_sound] = {{}, "style/loose_sound.mp3"}
    };

    button_t SLScreenButtons[] =
    {
        [SAVE_BUTTON] = {"SAVE", {SW * 0.8, SH * 0.4, SW * 0.15, 50}, 40,
                         {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [LOAD_BUTTON] = {"LOAD", {SW * 0.8, SH * 0.4, SW * 0.15, 50}, 40,
                         {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [BACK_BUTTON] = {"BACK", {SW * 0.35, SH * 0.6, SW * 0.30, 60}, 60,
                         {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}}
    };

    game_context_t AkinatorContext =
    {
        .root = NULL,
        .current = NULL,
        .MenuButtons = MenuButtons,
        .num_MenuButtons = ARRAY_SIZE(MenuButtons),
        .AkinatorScreenButtons = AkinatorScreenButtons,
        .num_AkinatorScreenButtons = ARRAY_SIZE(AkinatorScreenButtons),
        .SLScreenButtons = SLScreenButtons,
        .num_SLScreenButtons = ARRAY_SIZE(SLScreenButtons),
        .DCScreenButtons = DCScreenButtons,
        .num_DCScreenButtons = ARRAY_SIZE(DCScreenButtons),
        .back_to_menu_button = &back_to_menu_button,
        .AkinatorTextures = AkinatorTextures,
        .num_AkinatorTextures = ARRAY_SIZE(AkinatorTextures),
        .AkinatorSounds = AkinatorSounds,
        .num_AkinatorSounds = ARRAY_SIZE(AkinatorSounds),
        .current_screen = SCREEN_MENU,
        .akinator_screen = FIRST_SCREEN,
        .path_stack1 = &path_stack1,
        .path_stack2 = &path_stack2
    };

    InitAkinatorContext(&AkinatorContext);

    InitPathStacksForDefAndCompModes(AkinatorContext.path_stack1, AkinatorContext.path_stack2);

    AkinatorGameLoop(&AkinatorContext);


    if (AkinatorContext.root != NULL)
        DeleteLeaf(AkinatorContext.root);

    UninitPathStacksForDefAndCompModes(AkinatorContext.path_stack1, AkinatorContext.path_stack2);

    return;
}

void InitAkinatorContext( game_context_t* AkinatorContext )
{
    InitTexturesArray(AkinatorContext->AkinatorTextures,
                      AkinatorContext->num_AkinatorTextures);
    InitSoundsArray(AkinatorContext->AkinatorSounds,
                    AkinatorContext->num_AkinatorSounds);
    SetButtonsTextPosition(AkinatorContext->back_to_menu_button, 1);
    SetButtonsTextPosition(AkinatorContext->MenuButtons,
                           AkinatorContext->num_MenuButtons);
    SetButtonsTextPosition(AkinatorContext->AkinatorScreenButtons,
                           AkinatorContext->num_AkinatorScreenButtons);
    SetButtonsTextPosition(AkinatorContext->SLScreenButtons,
                           AkinatorContext->num_SLScreenButtons);
    SetButtonsTextPosition(AkinatorContext->DCScreenButtons,
                           AkinatorContext->num_DCScreenButtons);
}


void AkinatorGameLoop( game_context_t* AkinatorContext )
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawAkinatorBackground(AkinatorContext->AkinatorTextures[forest_background]);
        DrawSignature("Utkanator");

        switch (AkinatorContext->current_screen)
        {
            case SCREEN_MENU:
                if (MenuScreenVisual(AkinatorContext))
                    return;
                break;
            case SCREEN_SAVE:
                SaveModeScreen(AkinatorContext);
                break;
            case SCREEN_LOAD:
                LoadModeScreen(AkinatorContext);
                break;
            case SCREEN_DEFINITION_INPUT:
                ScreenDefModeInputCharacter(AkinatorContext);
                break;
            case SCREEN_DEFINITION_OUTPUT:
                ScreenDefModeOutputResult(AkinatorContext);
                break;
            case SCREEN_COMPARISON_OUTPUT:
                ScreenCompareModeOutputResult(AkinatorContext);
                break;
            case SCREEN_COMPARISON_INPUT_FIRST:
                ScreenCompareModeAddingFirstCharacter(AkinatorContext);
                break;
            case SCREEN_COMPARISON_INPUT_SECOND:
                ScreenCompareModeAddingSecondCharacter(AkinatorContext);
                break;
            case SCREEN_AKINATOR:
                AkinatorScreen(AkinatorContext);
                break;
            case SCREEN_ERROR:
                ErrorScreen(AkinatorContext);
                break;
            default:
                break;
        }
        EndDrawing();
    }
}

int MenuScreenVisual( game_context_t* AkinatorContext )
{
    switch (DrawMenuScreen(AkinatorContext->MenuButtons, AkinatorContext->num_MenuButtons,
        AkinatorContext->AkinatorTextures, AkinatorContext->AkinatorSounds[click_sound].sound))
    {
        case QUIT:
            if (AkinatorContext->root != NULL)
            {
                DeleteLeaf(AkinatorContext->root);
                AkinatorContext->root = NULL;
            }
            return 1;
        case PLAY:
            AkinatorContext->AkinatorScreenButtons[NEXT] =
            {
                "NEXT",
                {SW * 0.8, SH * 0.6, SW * 0.15, 60},
                AKINATOR_BUTTONS_FONT_SIZE,
                {0xF8, 0xED, 0xAD, 255},
                {0xD8, 0xCD, 0xAD, 255}
            };
            SetButtonsTextPosition(AkinatorContext->AkinatorScreenButtons, AkinatorContext->num_AkinatorScreenButtons);
            AkinatorContext->current_screen = SCREEN_AKINATOR;
            break;
        case SAVE:
            AkinatorContext->current_screen = SCREEN_SAVE;
            break;
        case LOAD:
            AkinatorContext->current_screen = SCREEN_LOAD;
            break;
        case DEF:
            AkinatorContext->current_screen = SCREEN_DEFINITION_INPUT;
            break;
        case COMP:
            AkinatorContext->current_screen = SCREEN_COMPARISON_INPUT_FIRST;
            break;
        default:
            break;
    }

    return 0;
}

void SaveModeScreen( game_context_t* AkinatorContext )
{
    int button_status = DrawSLScreen(AkinatorContext->current_screen, AkinatorContext->SLScreenButtons,
                                     AkinatorContext->num_SLScreenButtons,  AkinatorContext->AkinatorSounds[click_sound].sound,
                                     AkinatorContext->string, &AkinatorContext->letters);

    if (button_status == SAVE_BUTTON)
    {
        sprintf(buffer, "databases/%s", AkinatorContext->string);

        if (SaveTree(AkinatorContext->root, buffer) == 0)
        {
            strcpy(error_buffer, "Empty database, nothing to save");
            AkinatorContext->current_screen = SCREEN_ERROR;
            CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
            return;
        }

        AkinatorContext->current_screen = SCREEN_MENU;
        ON_LOG(LOG("Saved database to: %s", buffer))
        ON_LOG(GraphDumpTree(AkinatorContext->root);)
    }
    else if (button_status == BACK_BUTTON)
        AkinatorContext->current_screen = SCREEN_MENU;
    else
        return;

    CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
}

void LoadModeScreen( game_context_t* AkinatorContext )
{
    int button_status = DrawSLScreen(AkinatorContext->current_screen, AkinatorContext->SLScreenButtons,
                                     AkinatorContext->num_SLScreenButtons, AkinatorContext->AkinatorSounds[click_sound].sound,
                                     AkinatorContext->string, &AkinatorContext->letters);
    if (button_status == LOAD_BUTTON)
    {
        if (AkinatorContext->root != NULL)
            DeleteLeaf(AkinatorContext->root);

        sprintf(buffer, "databases/%s", AkinatorContext->string);
        AkinatorContext->root = LoadTree(buffer);
        if (AkinatorContext->root == NULL)
        {
            strcpy(error_buffer, "No such database");
            AkinatorContext->current_screen = SCREEN_ERROR;
            CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
            return;
        }
        if (FullBinaryTreeVerifier(AkinatorContext->root) == -1)
        {
            strcpy(error_buffer, "Database is corrupted. This is not full binary tree");
            AkinatorContext->current_screen = SCREEN_ERROR;
            ON_LOG(LOG("Database is corrupted. This is not full binary tree."))
            ON_LOG(GraphDumpTree(AkinatorContext->root);)
            CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
            return;
        }

        AkinatorContext->current = AkinatorContext->root;
        AkinatorContext->current_screen = SCREEN_MENU;
        ON_LOG(LOG("Loaded database from: %s", buffer))
        ON_LOG(GraphDumpTree(AkinatorContext->root);)
    }
    else if (button_status == BACK_BUTTON)
        AkinatorContext->current_screen = SCREEN_MENU;
    else
        return;

    CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
}

void ScreenDefModeInputCharacter( game_context_t* AkinatorContext )
{
    int button_status = DrawDCScreen(AkinatorContext->current_screen, AkinatorContext->DCScreenButtons,
                                     AkinatorContext->num_DCScreenButtons,
                                     AkinatorContext->AkinatorSounds[click_sound].sound,
                                     AkinatorContext->string, &AkinatorContext->letters);
    if (button_status == DC_BACK)
    {
        AkinatorContext->current_screen = SCREEN_MENU;
        CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
        return;
    }
    else if (button_status == DC_NEXT)
    {
        strcpy(name1, AkinatorContext->string);
        CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);

        StackDtor(AkinatorContext->path_stack1);
        StackInit(AkinatorContext->path_stack1, 10);

        if (AkinatorContext->root == NULL)
        {
            strcpy(error_buffer, "Empty database");
            AkinatorContext->current_screen = SCREEN_ERROR;
            return;
        }
        else if (FindNameInATree(AkinatorContext->root, name1, AkinatorContext->path_stack1) == NULL)
        {
            strcpy(error_buffer, "No such element in a base");
            AkinatorContext->current_screen = SCREEN_ERROR;
            return;
        }
        ReverseStack(AkinatorContext->path_stack1);

        AkinatorContext->current_screen = SCREEN_DEFINITION_OUTPUT;
    }
}


void ScreenDefModeOutputResult( game_context_t* AkinatorContext )
{
    int status = CheckButtonsStatus(AkinatorContext->back_to_menu_button, 1, AkinatorContext->AkinatorSounds[click_sound].sound);
    if (status == 0)
        AkinatorContext->current_screen = SCREEN_MENU;
    DrawButtons(AkinatorContext->back_to_menu_button, 1, {0xED, 0x7C, 0x30, 255});


    int value = -1;
    stack_t copy_stack = {};
    leaf_t* current_def = AkinatorContext->root;

    StackInitByCopy(AkinatorContext->path_stack1, &copy_stack);
    char temp_def_buffer[100] = {};
    int num_of_characteristics = (int)copy_stack.size;

    strcpy(buffer, name1);
    strcat(buffer, " is:");
    DrawTextBeautiful(buffer, 0.2 * SH, 50, {0xED, 0x7C, 0x30, 255});
    int string_height = (num_of_characteristics > 10 ? (int)(SH * 0.6 / num_of_characteristics) : 40);

    for (int i = 0; i < num_of_characteristics; i++)
    {
        StackPop(&copy_stack, &value);
        if (value == 0)
        {
            strcpy(temp_def_buffer, "- not ");
            strcat(temp_def_buffer, current_def->data);
            DrawTextBeautiful(temp_def_buffer, (int) (SH * 0.4 + i * string_height), string_height - 5, RED);
            current_def = current_def->right;
        }
        else if (value == 1)
        {
            strcpy(temp_def_buffer, "- ");
            strcat(temp_def_buffer, current_def->data);
            DrawTextBeautiful(temp_def_buffer, (int) (SH * 0.4 + i * string_height), string_height - 5, GREEN);
            current_def = current_def->left;
        }
    }
    StackDtor(&copy_stack);
}


void ScreenCompareModeOutputResult( game_context_t* AkinatorContext )
{
    int status = CheckButtonsStatus(AkinatorContext->back_to_menu_button,
                                    1, AkinatorContext->AkinatorSounds[click_sound].sound);
    if (status == 0)
        AkinatorContext->current_screen = SCREEN_MENU;

    DrawButtons(AkinatorContext->back_to_menu_button, 1, {0xED, 0x7C, 0x30, 255});

    leaf_t* current_def_same = AkinatorContext->root;
    leaf_t* current_def1     = AkinatorContext->root;
    leaf_t* current_def2     = AkinatorContext->root;

    stack_t copy_stack1 = {};
    stack_t copy_stack2 = {};

    StackInitByCopy(AkinatorContext->path_stack1, &copy_stack1);
    StackInitByCopy(AkinatorContext->path_stack2, &copy_stack2);

    int num_of_characts1 = (int)copy_stack1.size;
    int num_of_characts2 = (int)copy_stack2.size;

    int min_num = (num_of_characts1 > num_of_characts2 ? num_of_characts2 : num_of_characts1);

    sprintf(buffer, "%s and %s both:", name1, name2);
    DrawTextBeautiful(buffer, 0.05 * SH, 40, {0xED, 0x7C, 0x30, 255});

    int value1 = -1;
    int value2 = -1;

    int i = 0;

    StackPop(&copy_stack1, &value1);
    StackPop(&copy_stack2, &value2);

    if (value1 != value2)
        DrawTextBeautiful("(nothing same)", 0.12 * SH, 40, {0xD8, 0xCD, 0xAD, 255});
    else
    {

        while (value1 == value2 && i < min_num)
        {
            if (value1 == 0)
            {
                sprintf(buffer, "- not %s", current_def_same->data);
                DrawTextBeautiful(buffer, (int) (SH * 0.2 + i * 45), 40, RED);
                current_def_same = current_def_same->right;
            }
            else if (value1 == 1)
            {
                sprintf(buffer, "- %s", current_def_same->data);
                DrawTextBeautiful(buffer, (int) (SH * 0.2 + i * 45), 40, GREEN);
                current_def_same = current_def_same->left;
            }
            StackPop(&copy_stack1, &value1);
            StackPop(&copy_stack2, &value2);
            i++;
        }
    }

    current_def1 = current_def_same;
    current_def2 = current_def_same;


    if (strcmp(name1, name2) != 0)
    {
        sprintf(buffer, "but %s is: ", name1);
        DrawText(buffer, 0.05 * SW, (int) (SH * 0.2 + i * 45), 40, {0xED, 0x7C, 0x30, 255});
        sprintf(buffer, "but %s is: ", name2);
        DrawText(buffer, (int) (0.55 * SW), (int) (SH * 0.2 + i * 45), 40, {0xED, 0x7C, 0x30, 255});
        for (int j = i; j < num_of_characts1; j++)
        {
            if (value1 == 0)
            {
                sprintf(buffer, "- not %s", current_def1->data);
                DrawText(buffer, 0.05 * SW, (int) (SH * 0.2 + (j + 1) * 45), 40, RED);
                current_def1 = current_def1->right;
            }
            else if (value1 == 1)
            {
                sprintf(buffer, "- %s", current_def1->data);
                DrawText(buffer, 0.05 * SW, (int) (SH * 0.2 + (j + 1) * 45), 40, GREEN);
                current_def1 = current_def1->left;
            }
            StackPop(&copy_stack1, &value1);
        }
        for (int j = i; j < num_of_characts2; j++)
        {
            if (value2 == 0)
            {
                sprintf(buffer, "- not %s", current_def2->data);
                DrawText(buffer, (int) (SW * 0.55), (int) (SH * 0.2 + (j + 1) * 45), 40, RED);
                current_def2 = current_def2->right;
            }
            else if (value2 == 1)
            {
                sprintf(buffer, "- %s", current_def2->data);
                DrawText(buffer, (int) (SW * 0.55), (int) (SH * 0.2 + (j + 1) * 45), 40, GREEN);
                current_def2 = current_def2->left;
            }
            StackPop(&copy_stack2, &value2);
        }
    }

    StackDtor(&copy_stack1);
    StackDtor(&copy_stack2);
}

void ScreenCompareModeAddingFirstCharacter( game_context_t* AkinatorContext )
{
    int button_status = DrawDCScreen(AkinatorContext->current_screen, AkinatorContext->DCScreenButtons,
                                     AkinatorContext->num_DCScreenButtons,
                                     AkinatorContext->AkinatorSounds[click_sound].sound,
                                     AkinatorContext->string, &AkinatorContext->letters);
    if (button_status == DC_BACK)
    {
        AkinatorContext->current_screen = SCREEN_MENU;
        CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
        return;
    }
    else if (button_status == DC_NEXT)
    {
        strcpy(name1, AkinatorContext->string);

        CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);

        StackDtor(AkinatorContext->path_stack1);
        StackInit(AkinatorContext->path_stack1, 10);

        if (AkinatorContext->root == NULL)
        {
            strcpy(error_buffer, "Empty database");
            AkinatorContext->current_screen = SCREEN_ERROR;
            return;
        }
        else if (FindNameInATree(AkinatorContext->root, name1, AkinatorContext->path_stack1) == NULL)
        {
            strcpy(error_buffer, "No such element in a base");
            AkinatorContext->current_screen = SCREEN_ERROR;
            return;
        }
        ReverseStack(AkinatorContext->path_stack1);

        AkinatorContext->current_screen = SCREEN_COMPARISON_INPUT_SECOND;
    }
}



void AkinatorScreen( game_context_t* AkinatorContext )
{
    if (AkinatorContext->akinator_screen == LAST_QUESTION_SCREEN_NO1 ||
        AkinatorContext->akinator_screen == LAST_QUESTION_SCREEN_NO2 ||
        AkinatorContext->akinator_screen == LAST_QUESTION_SCREEN_YES)
        ;
    else if (AkinatorContext->root == NULL)
        AkinatorContext->akinator_screen = ADD_FIRST_ELEMENT;
    else if (AkinatorContext->current->left  == NULL || AkinatorContext->current->right == NULL)
        AkinatorContext->akinator_screen = LAST_QUESTION_SCREEN;
    else
        AkinatorContext->akinator_screen = QUESTION_SCREEN;

    switch (DrawAkinatorGameScreen(AkinatorContext->akinator_screen, AkinatorContext->current,
                AkinatorContext->AkinatorScreenButtons, AkinatorContext->num_AkinatorScreenButtons,
                AkinatorContext->AkinatorTextures, AkinatorContext->AkinatorSounds[click_sound].sound,
                AkinatorContext->string, &AkinatorContext->letters))
    {
        case NEXT:
            AkinatorScreenNextButtonPushed(&AkinatorContext->current_screen, &AkinatorContext->akinator_screen,
                                           &AkinatorContext->root, &AkinatorContext->current,
                                            AkinatorContext->string, &AkinatorContext->letters);
            break;
        case YES:
            if (AkinatorContext->akinator_screen == LAST_QUESTION_SCREEN)
            {
                AkinatorContext->akinator_screen = LAST_QUESTION_SCREEN_YES;
                PlaySound(AkinatorContext->AkinatorSounds[win_sound].sound);
                AkinatorContext->AkinatorScreenButtons[NEXT] =
                {"NEXT", {SW * 0.35, SH * 0.6, SW * 0.30, 60},
                    AKINATOR_BUTTONS_FONT_SIZE,
                    {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}};
                SetButtonsTextPosition(AkinatorContext->AkinatorScreenButtons,
                                        AkinatorContext->num_AkinatorScreenButtons);
            }
            else
                AkinatorContext->current = AkinatorContext->current->left;
            break;
        case NO:
            if (AkinatorContext->akinator_screen == LAST_QUESTION_SCREEN)
            {
                AkinatorContext->akinator_screen = LAST_QUESTION_SCREEN_NO1;
                PlaySound(AkinatorContext->AkinatorSounds[loose_sound].sound);
            }
            else
                AkinatorContext->current = AkinatorContext->current->right;
            break;
        default:
            break;
    }
}

void ErrorScreen( game_context_t* AkinatorContext )
{
    int status = CheckButtonsStatus(AkinatorContext->back_to_menu_button, 1,
                                    AkinatorContext->AkinatorSounds[click_sound].sound);

    if (status == 0)
        AkinatorContext->current_screen = SCREEN_MENU;
    DrawButtons(AkinatorContext->back_to_menu_button, 1, {0xED, 0x7C, 0x30, 255});
    DrawTextBeautiful(error_buffer, SH * 0.4, 60, RED);
    DrawTexturePro(AkinatorContext->AkinatorTextures[sad_duck].texture, {0, 0, 665, 682},
                    {0.7 * SW, 0, 0.3 * SW, 0.4 * SH}, {0, 0}, 0.0, RAYWHITE);
}

void ReverseStack( stack_t* stack )
{
    stack_el_t temp = 0;

    for (size_t i = 0; i < stack->size / 2; i++)
    {
        temp = stack->data[i];
        stack->data[i] = stack->data[stack->size - 1 - i];
        stack->data[stack->size - 1 - i] = temp;
    }

}

void AkinatorScreenNextButtonPushed( screen_status* current_screen, akinator_screens_t* akinator_screen,
                                     leaf_t** root, leaf_t **current, char* string, int* letters )
{
    switch (*akinator_screen)
    {
        case ADD_FIRST_ELEMENT:
            *root = InitLeaf(string);
            *current = *root;
            ON_LOG(LOG("Added first element: %s", string))
            ON_LOG(GraphDumpTree(*root);)
            CleanInputBarBuffer(string, letters);
            break;
        case LAST_QUESTION_SCREEN_YES:
            *current_screen = SCREEN_MENU;
            *akinator_screen = ADD_FIRST_ELEMENT;
            ON_LOG(LOG("Akinator guessed: %s", (*current)->data))
            ON_LOG(GraphDumpTree(*root);)
            *current = *root;
            break;
        case LAST_QUESTION_SCREEN_NO1:
            (*current)->right = InitLeaf((*current)->data);
            (*current)->left = InitLeaf(string);

            *akinator_screen = LAST_QUESTION_SCREEN_NO2;
            break;
        case LAST_QUESTION_SCREEN_NO2:
            ChangeLeafData(*current, string);
            ON_LOG(LOG("Akinator added new : %s. He is different from %s, because he is %s",
                        (*current)->left->data, (*current)->right->data, (*current)->data))
            ON_LOG(GraphDumpTree(*root);)

            CleanInputBarBuffer(string, letters);

            *current_screen = SCREEN_MENU;
            *akinator_screen = ADD_FIRST_ELEMENT;
            *current = *root;
            break;
        default:
            break;
    }
}

void DrawAkinatorBackground( texture_t background )
{
    DrawTexturePro(background.texture, {1000, 0, 4000, 1979}, {0, 0, SW, SH}, {0, 0}, 0.0, RAYWHITE);
}

int DrawDCScreen( screen_status current_screen, button_t* buttons, size_t size, Sound click_sound,
                  char* string, int* letters )
{
    int status = CheckButtonsStatus(buttons, size, click_sound);
    if (status != -1)
        return status;

    if (current_screen == SCREEN_DEFINITION_INPUT)
    {
        DrawTextBeautiful("Whose definition do you want to see?", SH * 0.4, 40, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SH * 0.6, 50, string, letters);

    }
    else if (current_screen == SCREEN_DEFINITION_OUTPUT)
        DrawTextBeautiful("He/She is ...", SH * 0.4, 40, {0xED, 0x7C, 0x30, 255});

    else if (current_screen == SCREEN_COMPARISON_INPUT_FIRST)
    {
        DrawTextBeautiful("Which characters do you want to compare?", SH * 0.4, 40, {0xED, 0x7C, 0x30, 255});
        DrawTextBeautiful("First character:", SH * 0.5, 40, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SH * 0.6, 50, string, letters);

    }
    else if (current_screen == SCREEN_COMPARISON_INPUT_SECOND)
    {
        DrawTextBeautiful("Second character:", SH * 0.5, 40, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SH * 0.6, 50, string, letters);
    }

    DrawButtons(buttons, size, {0xED, 0x7C, 0x30, 255});
    return -1;
}

int DrawSLScreen( screen_status current_screen, button_t* buttons, size_t size,
                  Sound click_sound, char* string, int* letters )
{
    SLSetButtonsVisibility(current_screen, buttons);

    int status = CheckButtonsStatus(buttons, size, click_sound);
    if (status != -1)
        return status;

    DrawButtons(buttons, size, {0xED, 0x7C, 0x30, 255});

    if (current_screen == SCREEN_LOAD)
        DrawTextBeautiful("Add filename to load database", SH * 0.3, 40, {0xED, 0x7C, 0x30, 255});
    else if (current_screen == SCREEN_SAVE)
        DrawTextBeautiful("Add filename to save database", SH * 0.3, 40, {0xED, 0x7C, 0x30, 255});
    DrawInputBar(SH * 0.4, 40, string, letters);

    return -1;
}

void SLSetButtonsVisibility( screen_status current_screen, button_t* buttons )
{
    if (current_screen == SCREEN_LOAD)
    {
        buttons[SAVE_BUTTON].is_invis = true;
        buttons[LOAD_BUTTON].is_invis = false;
    }
    else if (current_screen == SCREEN_SAVE)
    {
        buttons[SAVE_BUTTON].is_invis = false;
        buttons[LOAD_BUTTON].is_invis = true;
    }
}

int DrawAkinatorGameScreen( akinator_screens_t akinator_screen, leaf_t* current,
                            button_t* buttons, size_t size, texture_t* textures,
                            Sound click_sound, char* string, int* letters )
{
    AkinatorSetButtonsVisibility(akinator_screen, buttons);
    DrawButtons(buttons, size, {0xED, 0x7C, 0x30, 255});

    int status = CheckButtonsStatus(buttons, size, click_sound);
    if (status != -1)
        return status;


    int text_font = 50;

    if (akinator_screen == ADD_FIRST_ELEMENT)
    {
        DrawTextBeautiful("Add first character: ", SH * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SH * 0.6, text_font, string, letters);
        DrawTexturePro(textures[prime_duck].texture, {0, 0, 3548, 3688}, {0.7 * SW, 0, 0.3 * SW, 0.3 * SW},
                        {0, 0}, 0.0, RAYWHITE);
    }
    else if (akinator_screen == QUESTION_SCREEN)
    {
        sprintf(buffer, "Is your character %s?", current->data);
        DrawTextBeautiful(buffer, SH * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTexturePro(textures[thinking_duck].texture, {0, 0, 900, 900}, {0.8 * SW, 0.1 * SH, 0.2 * SW, 0.2 * SW},
                        {0, 0}, 0.0, RAYWHITE);
    }
    else if (akinator_screen == LAST_QUESTION_SCREEN)
    {
        sprintf(buffer, "Is it %s?", current->data);
        DrawTextBeautiful(buffer, SH * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTexturePro(textures[thinking_duck].texture, {0, 0, 900, 900}, {0.7 * SW, 0, 0.3 * SW, 0.4 * SH},
                        {0, 0}, 0.0, RAYWHITE);

    }
    else if (akinator_screen == LAST_QUESTION_SCREEN_YES)
    {
        DrawTextBeautiful("HE-HE-HE, It was really easy", SH * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTexturePro(textures[prime_duck].texture, {0, 0, 3548, 3688}, {0.7 * SW, 0, 0.3 * SW, 0.4 * SH},
                        {0, 0}, 0.0, RAYWHITE);

    }
    else if (akinator_screen == LAST_QUESTION_SCREEN_NO1)
    {
        DrawTextBeautiful("HMMM, I don't know him/her", SH * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTextBeautiful("What is his/her name?", SH * 0.5, text_font, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SH * 0.6, text_font, string, letters);
        DrawTexturePro(textures[not_found_duck].texture, {0, 0, 1079, 1079}, {0.7 * SW, 0, 0.3 * SW, 0.3 * SH},
                        {0, 0}, 0.0, RAYWHITE);

    }
    else if (akinator_screen == LAST_QUESTION_SCREEN_NO2)
    {
        sprintf(buffer, "How is %s different from %s? He/she is ...",
                current->left->data, current->right->data);
        DrawTextBeautiful(buffer, SH * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SH * 0.6, text_font, string, letters);
        DrawTexturePro(textures[not_found_duck].texture, {0, 0, 1079, 1079}, {0.7 * SW, 0, 0.3 * SW, 0.3 * SH},
                        {0, 0}, 0.0, RAYWHITE);
    }

    return -1;
}

void ScreenCompareModeAddingSecondCharacter( game_context_t* AkinatorContext )
{
    int button_status = DrawDCScreen(AkinatorContext->current_screen, AkinatorContext->DCScreenButtons,
                                     AkinatorContext->num_DCScreenButtons,
                                     AkinatorContext->AkinatorSounds[click_sound].sound,
                                     AkinatorContext->string, &AkinatorContext->letters);
    if (button_status == DC_BACK)
    {
        AkinatorContext->current_screen = SCREEN_MENU;
        CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);
        return;
    }
    else if (button_status == DC_NEXT)
    {
        strcpy(name2, AkinatorContext->string);

        CleanInputBarBuffer(AkinatorContext->string, &AkinatorContext->letters);

        StackDtor(AkinatorContext->path_stack2);
        StackInit(AkinatorContext->path_stack2, 10);

        if (AkinatorContext->root == NULL)
        {
            strcpy(error_buffer, "Empty database");
            AkinatorContext->current_screen = SCREEN_ERROR;
            return;
        }
        else if (FindNameInATree(AkinatorContext->root, name2, AkinatorContext->path_stack2) == NULL)
        {
            strcpy(error_buffer, "No such element in a base");
            AkinatorContext->current_screen = SCREEN_ERROR;
            return;
        }
        ReverseStack(AkinatorContext->path_stack2);

        AkinatorContext->current_screen = SCREEN_COMPARISON_OUTPUT;
    }
}

int DrawMenuScreen( button_t* buttons, size_t size, texture_t* textures, Sound click_sound )
{
    int status = CheckButtonsStatus(buttons, size, click_sound);
    if (status != -1)
        return status;

    DrawTexturePro(textures[prime_duck].texture, {0, 0, 3548, 3688}, {0.2 * SW, 0, 0.6 * SW, 0.6 * SW},
                    {0, 0}, 0.0, RAYWHITE);
    DrawButtons(buttons, size, {0xED, 0x7C, 0x30, 255});

    return -1;
}

void AkinatorSetButtonsVisibility( akinator_screens_t akinator_screen, button_t* buttons )
{
    if (akinator_screen == QUESTION_SCREEN || akinator_screen == LAST_QUESTION_SCREEN)
    {
        buttons[NEXT].is_invis = true;
        buttons[YES].is_invis = false;
        buttons[NO].is_invis = false;
    }
    else
    {
        buttons[NEXT].is_invis = false;
        buttons[YES].is_invis = true;
        buttons[NO].is_invis = true;
    }
}



void InitTexturesArray( texture_t* textures_arr, size_t array_len )
{
    for (size_t i = 0; i < array_len; i++)
        textures_arr[i].texture = LoadTexture(textures_arr[i].filename);
}

void InitSoundsArray( sound_t* sounds_arr, size_t array_len )
{
    for (size_t i = 0; i < array_len; i++)
        sounds_arr[i].sound = LoadSound(sounds_arr[i].filename);
}

void UninitTexturesArray( texture_t* textures_arr, size_t array_len )
{
    for (size_t i = 0; i < array_len; i++)
        UnloadTexture(textures_arr[i].texture);
}


void UninitSoundsArray( sound_t* sounds_arr, size_t array_len )
{
    for (size_t i = 0; i < array_len; i++)
        UnloadSound(sounds_arr[i].sound);
}

void InitPathStacksForDefAndCompModes( stack_t* path_stack1, stack_t* path_stack2 )
{
    StackInit(path_stack1, 10);
    StackInit(path_stack2, 10);
}

void UninitPathStacksForDefAndCompModes( stack_t* path_stack1, stack_t* path_stack2 )
{
    StackDtor(path_stack1);
    StackDtor(path_stack2);
}


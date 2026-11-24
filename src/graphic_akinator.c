#include <graphic_akinator.h>

int main()
{
    ON_LOG(STARTLOG())
    SetTraceLogLevel(LOG_NONE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Akinator");
    SetTargetFPS(60);

    InitAudioDevice();

    InitAkinatorTexturesAndSounds();

    InitPathStacksForDefAndCompModes();

    StartAkinatorGraphicGame();

    CloseAudioDevice();


    ON_LOG(ENDLOG())

    return 0;
}


void StartAkinatorGraphicGame()
{
    leaf_t* root = NULL;
    leaf_t* current = root;

    button_t MenuButtons[] =
    {
        [QUIT] = {"QUIT", {SCREEN_WIDTH * 0.7, SCREEN_HEIGHT * 0.75, SCREEN_WIDTH * 0.15, 60}, MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [PLAY] = {"PLAY", {SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.75, SCREEN_WIDTH * 0.15, 60}, MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [SAVE] = {"SAVE", {SCREEN_WIDTH * 0.3, SCREEN_HEIGHT * 0.75, SCREEN_WIDTH * 0.15, 60}, MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [LOAD] = {"LOAD", {SCREEN_WIDTH * 0.1, SCREEN_HEIGHT * 0.75, SCREEN_WIDTH * 0.15, 60}, MENU_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [DEF]  = {"DEFINITION", {SCREEN_WIDTH * 0.18, SCREEN_HEIGHT * 0.87, SCREEN_WIDTH * 0.27, 60}, MENU_BUTTONS_FONT_SIZE - 10, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [COMP]  = {"COMPARISON", {SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.87, SCREEN_WIDTH * 0.27, 60}, MENU_BUTTONS_FONT_SIZE - 10, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}}
    };

    button_t AkinatorScreenButtons[] =
    {
        [NEXT] = {"NEXT", {SCREEN_WIDTH * 0.8,           SCREEN_HEIGHT * 0.6, SCREEN_WIDTH * 0.15, 60}, AKINATOR_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [YES]  = {"YES",  {SCREEN_WIDTH * 0.2,           SCREEN_HEIGHT * 0.6, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.25}, YES_NO_FONT_SIZE, GREEN, DARKGREEN},
        [NO]  =  {"NO",   {(float)(SCREEN_WIDTH * 0.55), SCREEN_HEIGHT * 0.6, SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.25}, YES_NO_FONT_SIZE, RED, {0xA0, 0, 0, 255}}
    };

    button_t SLScreenButtons[] =
    {
        [SAVE_BUTTON] = {"SAVE", {SCREEN_WIDTH * 0.8, SCREEN_HEIGHT * 0.4, SCREEN_WIDTH * 0.15, 50}, 40,  {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [LOAD_BUTTON] = {"LOAD", {SCREEN_WIDTH * 0.8, SCREEN_HEIGHT * 0.4, SCREEN_WIDTH * 0.15, 50}, 40,  {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [BACK_BUTTON] = {"BACK", {SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.6, SCREEN_WIDTH * 0.30, 60}, 60, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}}
    };

    button_t DCScreenButtons[] =
    {
        [DC_BACK] = {"BACK", {SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.8, SCREEN_WIDTH * 0.30, 60}, 60, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}},
        [DC_NEXT] = {"NEXT", {SCREEN_WIDTH * 0.8, SCREEN_HEIGHT * 0.6, SCREEN_WIDTH * 0.15, 60}, AKINATOR_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}}
    };

    button_t back_button = {"BACK TO MENU", {SCREEN_WIDTH * 0.23, SCREEN_HEIGHT * 0.8, SCREEN_WIDTH * 0.54, SCREEN_HEIGHT * 0.13}, 50, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}};
    SetButtonsTextPosition(&back_button, 1);



    SetButtonsTextPosition(MenuButtons, ARRAY_SIZE(MenuButtons));
    SetButtonsTextPosition(AkinatorScreenButtons, ARRAY_SIZE(AkinatorScreenButtons));
    SetButtonsTextPosition(SLScreenButtons, ARRAY_SIZE(SLScreenButtons));
    SetButtonsTextPosition(DCScreenButtons, ARRAY_SIZE(DCScreenButtons));

    screen_status current_screen = SCREEN_MENU;
    akinator_screens_t akinator_screen = FIRST_SCREEN;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawAkinatorBackground();
        DrawSignature("Akinator");

        switch (current_screen)
        {
            case SCREEN_MENU:
                switch (DrawMenuScreen(MenuButtons, ARRAY_SIZE(MenuButtons)))
                {
                    case QUIT:
                        if (root != NULL)
                            DeleteLeaf(root);
                        return;
                    case PLAY:
                        AkinatorScreenButtons[NEXT] = {"NEXT", {SCREEN_WIDTH * 0.8, SCREEN_HEIGHT * 0.6, SCREEN_WIDTH * 0.15, 60}, AKINATOR_BUTTONS_FONT_SIZE, {0xF8, 0xED, 0xAD, 255}, {0xD8, 0xCD, 0xAD, 255}};
                        SetButtonsTextPosition(AkinatorScreenButtons, ARRAY_SIZE(AkinatorScreenButtons));
                        current_screen = SCREEN_AKINATOR;
                        break;
                    case SAVE:
                        current_screen = SCREEN_SAVE;
                        break;
                    case LOAD:
                        current_screen = SCREEN_LOAD;
                        break;
                    case DEF:
                        current_screen = SCREEN_DEFINITION_INPUT;
                        break;
                    case COMP:
                        current_screen = SCREEN_COMPARISON_INPUT_FIRST;
                        break;
                    default:
                        break;
                }
                break;

            case SCREEN_SAVE:
            {
                int button_status = DrawSLScreen(current_screen, SLScreenButtons, ARRAY_SIZE(SLScreenButtons));

                if (button_status == SAVE_BUTTON)
                {
                    strcpy(buffer, "databases/");
                    strcat(buffer, string);
                    if (SaveTree(root, buffer) == 0)
                    {
                        strcpy(error_buffer, "Empty database, nothing to save");
                        current_screen = SCREEN_ERROR;
                        break;
                    }

                    current_screen = SCREEN_MENU;
                    ON_LOG(LOG("Saved database to: %s", buffer))
                    ON_LOG(GraphDumpTree(root);)
                }
                else if (button_status == BACK_BUTTON)
                    current_screen = SCREEN_MENU;
                else
                    break;

                memset(string, 0, 100);
                letters = 0;

                break;
            }
            case SCREEN_LOAD:
            {
                int button_status = DrawSLScreen(current_screen, SLScreenButtons, ARRAY_SIZE(SLScreenButtons));
                if (button_status == LOAD_BUTTON)
                {
                    if (root != NULL)
                        DeleteLeaf(root);
                    strcpy(buffer, "databases/");
                    strcat(buffer, string);
                    root = LoadTree(buffer);
                    if (root == NULL)
                    {
                        strcpy(error_buffer, "No such database");
                        current_screen = SCREEN_ERROR;
                        break;
                    }
                    if (FullBinaryTreeVerifier(root) == -1)
                    {
                        strcpy(error_buffer, "Database is corrupted. This is not full binary tree");
                        current_screen = SCREEN_ERROR;
                        ON_LOG(LOG("Database is corrupted. This is not full binary tree."))
                        ON_LOG(GraphDumpTree(root);)
                        break;
                    }

                    current = root;
                    current_screen = SCREEN_MENU;
                    ON_LOG(LOG("Loaded database from: %s", buffer))
                    ON_LOG(GraphDumpTree(root);)
                }
                else if (button_status == BACK_BUTTON)
                    current_screen = SCREEN_MENU;
                else
                    break;

                memset(string, 0, 100);
                letters = 0;

                break;
            }
            case SCREEN_DEFINITION_INPUT:
            {
                int button_status = DrawDCScreen(current_screen, DCScreenButtons, ARRAY_SIZE(DCScreenButtons));
                if (button_status == DC_BACK)
                {
                    current_screen = SCREEN_MENU;
                    memset(string, 0, 100);
                    letters = 0;
                    break;
                }
                else if (button_status == DC_NEXT)
                {
                    strcpy(name1, string);
                    memset(string, 0, 100);
                    letters = 0;

                    StackDtor(&path_stack1);
                    StackInit(&path_stack1, 10);

                    if (root == NULL)
                    {
                        strcpy(error_buffer, "Empty database");
                        current_screen = SCREEN_ERROR;
                        break;
                    }
                    else if (FindNameInATree(root, name1, &path_stack1) == NULL)
                    {
                        strcpy(error_buffer, "No such element in a base");
                        current_screen = SCREEN_ERROR;
                        break;
                    }
                    ReverseStack(&path_stack1);

                    current_screen = SCREEN_DEFINITION_OUTPUT;
                }
                break;
            }
            case SCREEN_DEFINITION_OUTPUT:
            {
                int status = CheckButtonsStatus(&back_button, 1);
                if (status == 0)
                    current_screen = SCREEN_MENU;
                DrawButtons(&back_button, 1, {0xED, 0x7C, 0x30, 255});


                int value = -1;
                leaf_t* current_def = root;

                stack_t copy_stack = {};

                StackInitByCopy(&path_stack1, &copy_stack);

                char temp_def_buffer[100] = {};

                int num_of_characteristics = (int)copy_stack.size;
                strcpy(buffer, name1);
                strcat(buffer, " is:");
                DrawTextBeautiful(buffer, 0.2 * SCREEN_HEIGHT, 50, {0xED, 0x7C, 0x30, 255});
                int string_height = (num_of_characteristics > 10 ? (int)(SCREEN_HEIGHT * 0.6 / num_of_characteristics) : 40);

                for (int i = 0; i < num_of_characteristics; i++)
                {
                    StackPop(&copy_stack, &value);
                    if (value == 0)
                    {
                        strcpy(temp_def_buffer, "- not ");
                        strcat(temp_def_buffer, current_def->data);
                        DrawTextBeautiful(temp_def_buffer, (int) (SCREEN_HEIGHT * 0.4 + i * string_height), string_height - 5, RED);
                        current_def = current_def->right;
                    }
                    else if (value == 1)
                    {
                        strcpy(temp_def_buffer, "- ");
                        strcat(temp_def_buffer, current_def->data);
                        DrawTextBeautiful(temp_def_buffer, (int) (SCREEN_HEIGHT * 0.4 + i * string_height), string_height - 5, GREEN);
                        current_def = current_def->left;
                    }
                }
                StackDtor(&copy_stack);

                break;
            }
            case SCREEN_COMPARISON_OUTPUT:
            {
                int status = CheckButtonsStatus(&back_button, 1);
                if (status == 0)
                    current_screen = SCREEN_MENU;
                DrawButtons(&back_button, 1, {0xED, 0x7C, 0x30, 255});

                leaf_t* current_def_same = root;
                leaf_t* current_def1 = root;
                leaf_t* current_def2 = root;

                stack_t copy_stack1 = {};
                stack_t copy_stack2 = {};

                StackInitByCopy(&path_stack1, &copy_stack1);
                StackInitByCopy(&path_stack2, &copy_stack2);

                int num_of_characteristics1 = (int)copy_stack1.size;
                int num_of_characteristics2 = (int)copy_stack2.size;
                int min_num = (num_of_characteristics1 > num_of_characteristics2 ? num_of_characteristics2 : num_of_characteristics1);
                sprintf(buffer, "%s and %s both:", name1, name2);
                DrawTextBeautiful(buffer, 0.05 * SCREEN_HEIGHT, 40, {0xED, 0x7C, 0x30, 255});

                int value1 = -1;
                int value2 = -1;

                int i = 0;

                StackPop(&copy_stack1, &value1);
                StackPop(&copy_stack2, &value2);

                if (value1 != value2)
                    DrawTextBeautiful("(nothing same)", 0.12 * SCREEN_HEIGHT, 40, {0xD8, 0xCD, 0xAD, 255});
                else
                {

                    while (value1 == value2 && i < min_num)
                    {
                        if (value1 == 0)
                        {
                            sprintf(buffer, "- not %s", current_def_same->data);
                            DrawTextBeautiful(buffer, (int) (SCREEN_HEIGHT * 0.2 + i * 45), 40, RED);
                            current_def_same = current_def_same->right;
                        }
                        else if (value1 == 1)
                        {
                            sprintf(buffer, "- %s", current_def_same->data);
                            DrawTextBeautiful(buffer, (int) (SCREEN_HEIGHT * 0.2 + i * 45), 40, GREEN);
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
                    DrawText(buffer, 0.05 * SCREEN_WIDTH, (int) (SCREEN_HEIGHT * 0.2 + i * 45), 40, {0xED, 0x7C, 0x30, 255});
                    sprintf(buffer, "but %s is: ", name2);
                    DrawText(buffer, (int) (0.55 * SCREEN_WIDTH), (int) (SCREEN_HEIGHT * 0.2 + i * 45), 40, {0xED, 0x7C, 0x30, 255});
                    for (int j = i; j < num_of_characteristics1; j++)
                    {
                        if (value1 == 0)
                        {
                            sprintf(buffer, "- not %s", current_def1->data);
                            DrawText(buffer, 0, (int) (SCREEN_HEIGHT * 0.2 + (j + 1) * 45), 40, RED);
                            current_def1 = current_def1->right;
                        }
                        else if (value1 == 1)
                        {
                            sprintf(buffer, "- %s", current_def1->data);
                            DrawText(buffer, 0, (int) (SCREEN_HEIGHT * 0.2 + (j + 1) * 45), 40, GREEN);
                            current_def1 = current_def1->left;
                        }
                        StackPop(&copy_stack1, &value1);
                    }
                    for (int j = i; j < num_of_characteristics2; j++)
                    {
                        if (value2 == 0)
                        {
                            sprintf(buffer, "- not %s", current_def2->data);
                            DrawText(buffer, SCREEN_WIDTH / 2, (int) (SCREEN_HEIGHT * 0.2 + (j + 1) * 45), 40, RED);
                            current_def2 = current_def2->right;
                        }
                        else if (value2 == 1)
                        {
                            sprintf(buffer, "- %s", current_def2->data);
                            DrawText(buffer, SCREEN_WIDTH / 2, (int) (SCREEN_HEIGHT * 0.2 + (j + 1) * 45), 40, GREEN);
                            current_def2 = current_def2->left;
                        }
                        StackPop(&copy_stack2, &value2);
                    }
                }

                StackDtor(&copy_stack1);
                StackDtor(&copy_stack2);

                break;
            }
            case SCREEN_COMPARISON_INPUT_FIRST:
            {
                int button_status = DrawDCScreen(current_screen, DCScreenButtons, ARRAY_SIZE(DCScreenButtons));
                if (button_status == DC_BACK)
                {
                    current_screen = SCREEN_MENU;
                    memset(string, 0, 100);
                    letters = 0;
                    break;
                }
                else if (button_status == DC_NEXT)
                {
                    strcpy(name1, string);

                    memset(string, 0, 100);
                    letters = 0;

                    StackDtor(&path_stack1);
                    StackInit(&path_stack1, 10);

                    if (root == NULL)
                    {
                        strcpy(error_buffer, "Empty database");
                        current_screen = SCREEN_ERROR;
                        break;
                    }
                    else if (FindNameInATree(root, name1, &path_stack1) == NULL)
                    {
                        strcpy(error_buffer, "No such element in a base");
                        current_screen = SCREEN_ERROR;
                        break;
                    }
                    ReverseStack(&path_stack1);

                    current_screen = SCREEN_COMPARISON_INPUT_SECOND;
                }
                break;
            }
            case SCREEN_COMPARISON_INPUT_SECOND:
            {
                int button_status = DrawDCScreen(current_screen, DCScreenButtons, ARRAY_SIZE(DCScreenButtons));
                if (button_status == DC_BACK)
                {
                    current_screen = SCREEN_MENU;
                    memset(string, 0, 100);
                    letters = 0;
                    break;
                }
                else if (button_status == DC_NEXT)
                {
                    strcpy(name2, string);

                    memset(string, 0, 100);
                    letters = 0;

                    StackDtor(&path_stack2);
                    StackInit(&path_stack2, 10);

                    if (root == NULL)
                    {
                        strcpy(error_buffer, "Empty database");
                        current_screen = SCREEN_ERROR;
                        break;
                    }
                    else if (FindNameInATree(root, name2, &path_stack2) == NULL)
                    {
                        strcpy(error_buffer, "No such element in a base");
                        current_screen = SCREEN_ERROR;
                        break;
                    }
                    ReverseStack(&path_stack2);

                    current_screen = SCREEN_COMPARISON_OUTPUT;
                }
                break;
            }

            case SCREEN_AKINATOR:
                if (akinator_screen == LAST_QUESTION_SCREEN_NO1 || akinator_screen == LAST_QUESTION_SCREEN_NO2 || akinator_screen == LAST_QUESTION_SCREEN_YES)
                    ;
                else if (root == NULL)
                    akinator_screen = ADD_FIRST_ELEMENT;
                else
                {
                    if (current->left == NULL || current->right == NULL)
                        akinator_screen = LAST_QUESTION_SCREEN;
                    else
                        akinator_screen = QUESTION_SCREEN;

                }
                switch (DrawAkinatorGameScreen(akinator_screen, current, AkinatorScreenButtons, ARRAY_SIZE(AkinatorScreenButtons)))
                {
                    case NEXT:
                        AkinatorScreenNextButtonPushed(&current_screen, &akinator_screen, &root, &current);
                        break;
                    case YES:
                        if (akinator_screen == LAST_QUESTION_SCREEN)
                        {
                            akinator_screen = LAST_QUESTION_SCREEN_YES;
                            PlaySound(win_sound);
                            AkinatorScreenButtons[NEXT] = {"NEXT", {SCREEN_WIDTH * 0.35, SCREEN_HEIGHT * 0.6, SCREEN_WIDTH * 0.30, 60}, AKINATOR_BUTTONS_FONT_SIZE, {0xD8, 0xCD, 0xAD, 255}};
                            SetButtonsTextPosition(AkinatorScreenButtons, ARRAY_SIZE(AkinatorScreenButtons));
                        }
                        else
                            current = current->left;
                        break;
                    case NO:
                        if (akinator_screen == LAST_QUESTION_SCREEN)
                        {
                            akinator_screen = LAST_QUESTION_SCREEN_NO1;
                            PlaySound(loose_sound);
                        }
                        else
                            current = current->right;
                        break;
                    default:
                        break;
                }
                break;
            case SCREEN_ERROR:
            {
                int status = CheckButtonsStatus(&back_button, 1);
                if (status == 0)
                    current_screen = SCREEN_MENU;
                DrawButtons(&back_button, 1, {0xED, 0x7C, 0x30, 255});
                DrawTextBeautiful(error_buffer, SCREEN_HEIGHT * 0.4, 60, RED);
                DrawTexturePro(sad_duck, {0, 0, 665, 682}, {0.7 * SCREEN_WIDTH, 0, 0.3 * SCREEN_WIDTH, 0.4 * SCREEN_HEIGHT}, {0, 0}, 0.0, RAYWHITE);
                break;
            }
            default:
                break;
        }
        EndDrawing();
    }

    if (root != NULL)
        DeleteLeaf(root);

    return;
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

void AkinatorScreenNextButtonPushed( screen_status* current_screen, akinator_screens_t* akinator_screen, leaf_t** root, leaf_t **current )
{
    switch (*akinator_screen)
    {
        case ADD_FIRST_ELEMENT:
            *root = InitLeaf(string);
            *current = *root;
            ON_LOG(LOG("Added first element: %s", string))
            ON_LOG(GraphDumpTree(*root);)
            memset(string, 0, 100);
            letters = 0;
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
            memset(string, 0, 100);
            letters = 0;
            *akinator_screen = LAST_QUESTION_SCREEN_NO2;
            break;
        case LAST_QUESTION_SCREEN_NO2:
            ChangeLeafData(*current, string);
            ON_LOG(LOG("Akinator added new : %s. He is different from %s, because he is %s", (*current)->left->data, (*current)->right->data, (*current)->data))
            ON_LOG(GraphDumpTree(*root);)
            memset(string, 0, 100);
            letters = 0;
            *current_screen = SCREEN_MENU;
            *akinator_screen = ADD_FIRST_ELEMENT;
            *current = *root;
            break;
        default:
            break;
    }
};

void DrawAkinatorBackground()
{
    DrawTexturePro(forest, {1000, 0, 4000, 1979}, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, {0, 0}, 0.0, RAYWHITE);
}

int DrawDCScreen( screen_status current_screen, button_t* buttons, size_t size )
{
    int status = CheckButtonsStatus(buttons, size);
    if (status != -1)
        return status;

    if (current_screen == SCREEN_DEFINITION_INPUT)
    {
        DrawTextBeautiful("Whose definition do you want to see?", SCREEN_HEIGHT * 0.4, 40, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SCREEN_HEIGHT * 0.6, 50, string, &letters);

    }
    else if (current_screen == SCREEN_DEFINITION_OUTPUT)
        DrawTextBeautiful("He/She is ...", SCREEN_HEIGHT * 0.4, 40, {0xED, 0x7C, 0x30, 255});

    else if (current_screen == SCREEN_COMPARISON_INPUT_FIRST)
    {
        DrawTextBeautiful("Which characters do you want to compare?", SCREEN_HEIGHT * 0.4, 40, {0xED, 0x7C, 0x30, 255});
        DrawTextBeautiful("First character:", SCREEN_HEIGHT * 0.5, 40, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SCREEN_HEIGHT * 0.6, 50, string, &letters);

    }
    else if (current_screen == SCREEN_COMPARISON_INPUT_SECOND)
    {
        DrawTextBeautiful("Second character:", SCREEN_HEIGHT * 0.5, 40, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SCREEN_HEIGHT * 0.6, 50, string, &letters);
    }

    DrawButtons(buttons, size, {0xED, 0x7C, 0x30, 255});
    return -1;
}

int DrawSLScreen( screen_status current_screen, button_t* buttons, size_t size )
{
    SLSetButtonsVisibility(current_screen, buttons);

    int status = CheckButtonsStatus(buttons, size);
    if (status != -1)
        return status;

    DrawButtons(buttons, size, {0xED, 0x7C, 0x30, 255});

    if (current_screen == SCREEN_LOAD)
        DrawTextBeautiful("Add filename to load database", SCREEN_HEIGHT * 0.3, 40, {0xED, 0x7C, 0x30, 255});
    else if (current_screen == SCREEN_SAVE)
        DrawTextBeautiful("Add filename to save database", SCREEN_HEIGHT * 0.3, 40, {0xED, 0x7C, 0x30, 255});
    DrawInputBar(SCREEN_HEIGHT * 0.4, 40, string, &letters);

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

int DrawAkinatorGameScreen( akinator_screens_t akinator_screen, leaf_t* current, button_t* buttons, size_t size )
{
    AkinatorSetButtonsVisibility(akinator_screen, buttons);
    DrawButtons(buttons, size, {0xED, 0x7C, 0x30, 255});

    int status = CheckButtonsStatus(buttons, size);
    if (status != -1)
        return status;


    int text_font = 50;

    if (akinator_screen == ADD_FIRST_ELEMENT)
    {
        DrawTextBeautiful("Add first character: ", SCREEN_HEIGHT * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SCREEN_HEIGHT * 0.6, text_font, string, &letters);
        DrawTexturePro(prime_duck, {0, 0, 3548, 3688}, {0.7 * SCREEN_WIDTH, 0, 0.3 * SCREEN_WIDTH, 0.3 * SCREEN_WIDTH}, {0, 0}, 0.0, RAYWHITE);
    }
    else if (akinator_screen == QUESTION_SCREEN)
    {
        sprintf(buffer, "Is your character %s?", current->data);
        DrawTextBeautiful(buffer, SCREEN_HEIGHT * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTexturePro(thinking_duck, {0, 0, 900, 900}, {0.8 * SCREEN_WIDTH, 0.1 * SCREEN_HEIGHT, 0.2 * SCREEN_WIDTH, 0.2 * SCREEN_WIDTH}, {0, 0}, 0.0, RAYWHITE);
    }
    else if (akinator_screen == LAST_QUESTION_SCREEN)
    {
        sprintf(buffer, "Is it %s?", current->data);
        DrawTextBeautiful(buffer, SCREEN_HEIGHT * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTexturePro(thinking_duck, {0, 0, 900, 900}, {0.7 * SCREEN_WIDTH, 0, 0.3 * SCREEN_WIDTH, 0.4 * SCREEN_HEIGHT}, {0, 0}, 0.0, RAYWHITE);

    }
    else if (akinator_screen == LAST_QUESTION_SCREEN_YES)
    {
        DrawTextBeautiful("HE-HE-HE, It was really easy", SCREEN_HEIGHT * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTexturePro(prime_duck, {0, 0, 3548, 3688}, {0.7 * SCREEN_WIDTH, 0, 0.3 * SCREEN_WIDTH, 0.4 * SCREEN_HEIGHT}, {0, 0}, 0.0, RAYWHITE);

    }
    else if (akinator_screen == LAST_QUESTION_SCREEN_NO1)
    {
        DrawTextBeautiful("HMMM, I don't know him/her", SCREEN_HEIGHT * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawTextBeautiful("What is his/her name?", SCREEN_HEIGHT * 0.5, text_font, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SCREEN_HEIGHT * 0.6, text_font, string, &letters);
        DrawTexturePro(not_found_duck, {0, 0, 1079, 1079}, {0.7 * SCREEN_WIDTH, 0, 0.3 * SCREEN_WIDTH, 0.3 * SCREEN_HEIGHT}, {0, 0}, 0.0, RAYWHITE);

    }
    else if (akinator_screen == LAST_QUESTION_SCREEN_NO2)
    {
        sprintf(buffer, "How is %s different from %s? He/she is ...", current->left->data, current->right->data);
        DrawTextBeautiful(buffer, SCREEN_HEIGHT * 0.4, text_font, {0xED, 0x7C, 0x30, 255});
        DrawInputBar(SCREEN_HEIGHT * 0.6, text_font, string, &letters);
        DrawTexturePro(not_found_duck, {0, 0, 1079, 1079}, {0.7 * SCREEN_WIDTH, 0, 0.3 * SCREEN_WIDTH, 0.3 * SCREEN_HEIGHT}, {0, 0}, 0.0, RAYWHITE);
    }

    return -1;
}


int DrawMenuScreen( button_t* buttons, size_t size )
{
    int status = CheckButtonsStatus(buttons, size);
    if (status != -1)
        return status;

    DrawTexturePro(prime_duck, {0, 0, 3548, 3688}, {0.2 * SCREEN_WIDTH, 0, 0.6 * SCREEN_WIDTH, 0.6 * SCREEN_WIDTH}, {0, 0}, 0.0, RAYWHITE);
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


void InitAkinatorTexturesAndSounds()
{
    prime_duck     = LoadTexture("style/prime_duck_no_bg.png");
    not_found_duck = LoadTexture("style/not_found_duck.png");
    thinking_duck  = LoadTexture("style/thinking_duck.png");
    sad_duck       = LoadTexture("style/sad_duck.png");
    forest         = LoadTexture("style/forest.png");
    loose_sound    = LoadSound("style/loose_sound.mp3");
    click_sound          = LoadSound("style/clickclick.mp3");
    win_sound      = LoadSound("style/win_sound.mp3");
}

void UninitAkinatorTexturesAndSounds()
{
    UnloadSound(click_sound);
    UnloadSound(win_sound);
    UnloadSound(loose_sound);
    UnloadTexture(forest);
    UnloadTexture(prime_duck);
    UnloadTexture(thinking_duck);
    UnloadTexture(not_found_duck);
}

void InitPathStacksForDefAndCompModes()
{
    StackInit(&path_stack1, 10);
    StackInit(&path_stack2, 10);
}

void UninitPathStacksForDefAndCompModes()
{
    StackDtor(&path_stack1);
    StackDtor(&path_stack2);

}

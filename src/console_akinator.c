#include <akinator.h>

char buffer[256] = {};

int main()
{
    ON_LOG(STARTLOG())

    int ch = 0;
    leaf_t* database_root = NULL;
    char filename[100] = {};
    char file_path[200] = {};


    printf(MENU);
    while ((ch = getchar()) != 'q')
    {
        CleanBuffer();
        switch (ch)
        {
            case 'l':
                printf("\nPrint database name to load:\n\n");
                scanf("%s", filename); getchar(); printf("\n");
                strcpy(file_path, "databases/");
                strcat(file_path, filename);
                database_root = LoadTree(file_path);
                ON_LOG(
                if (database_root != NULL)
                    GraphDumpTree(database_root);
                )
                break;
            case 's':
                printf("\nPrint database name to save:\n\n");
                scanf("%s", filename); getchar(); printf("\n");
                strcpy(file_path, "databases/");
                strcat(file_path, filename);
                SaveTree(database_root, file_path);
                ON_LOG(LOG("Save database on root: %s", file_path))
                ON_LOG(GraphDumpTree(database_root);)
                break;
            case 'n':
                printf("\n\n--------------------------------------------\n\n");
                StartNewAkinatorSession(&database_root);
                printf("\n\n--------------------------------------------\n\n");
                break;
            default:
                printf("Invalid input\n");
                break;
        }
        printf(MENU);
    }

    if (database_root != NULL)
        DeleteLeaf(database_root);
    ON_LOG(ENDLOG())
    return 0;
}

void StartNewAkinatorSession( leaf_t** root )
{
    if (*root == NULL)
        AkinAddFirstCharacter(root);

    StartGuessingCharacter(root);
}

void AkinAddFirstCharacter( leaf_t** root )
{
    printf("My database is empty...\n\n"
           "Input first character's name to start new: \n\n");
    scanf("%255[^\n]", buffer); getchar(); printf("\n");
    *root = InitLeaf(buffer);

    #ifdef LOGGING
    LOG("Added first character: %s", buffer)
    GraphDumpTree(*root);
    #endif

    return;
}

void StartGuessingCharacter( leaf_t** root )
{
    leaf_t* current = *root;

    while (current->left != NULL && current->right != NULL)
    {
        printf("Is your character %s?\n\n", current->data);
        printf("Push [y] if I right, and [n] if I missed\n\n");
        scanf("%255[^\n]", buffer); getchar(); printf("\n");

        if (strcmp("y", buffer) == 0)
            current = current->left;
        else if (strcmp("n", buffer) == 0)
            current = current->right;
        else
            printf("Incorrect input. You play not on my rules\n\n");
    }
    GuessingFinal(current);
    #ifdef LOGGING
    GraphDumpTree(*root);
    #endif
}

void GuessingFinal( leaf_t* current )
{
    printf("I know, this is %s!\n\n", current->data);
    printf("Push [y] if I right, and [n] if I missed\n\n");
    scanf("%255[^\n]", buffer); getchar(); printf("\n");

    if (strcmp("y", buffer) == 0)
        printf("Yes. I'm always right\n\n");
    else if (strcmp("n", buffer) == 0)
        AddNewCharacter(current);
    else
        printf("Incorrect input. You play not on my rules\n\n");

}

void AddNewCharacter( leaf_t* current )
{
    printf("Hmmm...You won, I really don't know him\\her\n\n");
    printf("Let's add new character. What's his\\her name?\n\n");
    scanf("%255[^\n]", buffer); getchar(); printf("\n");
    #ifdef LOGGING
    LOG("Added new character: %s", buffer)
    #endif
    current->right = InitLeaf(current->data);
    current->left = InitLeaf(buffer);
    printf("How is %s different from %s? It is ...\n\n", buffer, current->data);
    scanf("%255[^\n]", buffer); getchar(); printf("\n");
    ChangeLeafData(current, buffer);
}

void CleanBuffer()
{
    int n = 0;

    while ((n = getchar()) != '\n' && n != EOF)
        continue;
    return;
}

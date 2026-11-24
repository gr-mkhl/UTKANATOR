#ifndef _CONSOLE_AKINATOR_H_
#define _CONSOLE_AKINATOR_H_

#include <stdio.h>
#include <tree.h>
#include <log.h>

void CleanBuffer();

void AkinAddFirstCharacter  ( leaf_t** root );
void StartGuessingCharacter ( leaf_t** root );
void StartNewAkinatorSession( leaf_t** root );
void GuessingFinal          ( leaf_t*  current );
void AddNewCharacter        ( leaf_t*  current );

#define MENU "menu:\n"                      \
                "l - load database\n"       \
                "s - save database\n"       \
                "n - start new session\n"   \
                "r - remove bench\n"        \
                "q - exit program\n"
#endif

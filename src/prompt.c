#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>

#include "action.h"
#include "state.h"

#define DIRECTORY_NAME_SIZE 256
#define DIRECTORY_PROMPT "sellect base directory: "
#define DIRECTORY_INVALID "%s is invalid directory\n"

#define ACTION_SIZE 16
#define ACTION_PROMPT "select action:\n\t[p](print whole)\n> "
#define ACTION_INVALID "{%s} is invalid action\n"

void prompt_base_folder(State* state) {
    bool is_correct = false;
    char* directory_name = (char*)malloc(256);
    char absolutePath[PATH_MAX];

    while (!is_correct) {
        printf(DIRECTORY_PROMPT);    
        scanf("%255s", directory_name);
        if (!realpath(directory_name, absolutePath)) {
            printf("realpath deosn't work\n");
            continue;
        }
        memcpy(directory_name, absolutePath, DIRECTORY_NAME_SIZE);
        DIR* dir = opendir(directory_name);
        if (dir) {
            closedir(dir);
            is_correct = true;
            state->base_folder = directory_name;
        } else {
            printf(DIRECTORY_INVALID, directory_name);
        }
    }
}


void prompt_action(State* state) {

    bool is_correct = false;
    char action_text[ACTION_SIZE];

    while (!is_correct) {
        printf(ACTION_PROMPT);
        scanf("%15s", action_text);
        if (parse_action(state, action_text)) {
            is_correct = true;
        } else {
            printf(ACTION_INVALID, action_text);
        }
    }
}

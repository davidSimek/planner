#include <stdbool.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "action.h"
#include "prompt.h"

bool parse_action(State* state, char* action_text) {
    if (action_text[0] == 'p') {
        state->action = PRINT_WHOLE;
        return true;
    }

    if (action_text[0] == 'q') {
        state->action = QUIT;
        return true;
    }

    if (action_text[0] == 'u') {
        state->action = UPDATE_BASE_DIR;
        return true;
    }

    return false;
}


void do_action(State* state) {
    switch (state->action) {
        case PRINT_WHOLE:
            print_whole(state);
            break;
        case QUIT:
            quit_program(state);
            break;
        case UPDATE_BASE_DIR:
            update_base_dir(state);
            break;
    }
}

void print_whole(State* state) {
    handle_dir(state, state->base_folder);    
}

void quit_program(State* state) {
    state->should_run = false;
}


void update_base_dir(State* state) {
    prompt_base_folder(state);
}

void handle_dir(State* state, char* dir_path) {

    printf("%d\t", state->index);
    for (int i = 0; i < state->depth; ++i) {
        printf("  ");
    }
    printf("%s (dir)\n", dir_path);
    state->index++;
    DIR* dir;
    struct dirent* entry;
    
    if ((dir = opendir(dir_path)) != NULL) {
        int count = 0;
        while ((entry = readdir(dir)) != NULL) {
            /*if (count < 2) {
                count++;
                continue;
            }*/
            if (entry->d_name[0] == '.' && entry->d_name[1] == '.' ||
                entry->d_name[0] == '.' && entry->d_name[1] == 0 ) {
                continue;
            }
            if (entry->d_type == DT_DIR) {

                char new_dir[256] = {0};
                if (strlen(entry->d_name) + strlen(dir_path) + 1 >= 256) {
                    printf("Couldn't build path (longer than 255B).\n");
                    break;
                }

                int original = strlen(dir_path);
                int extension = strlen(entry->d_name);

                memcpy(new_dir, dir_path, original);
                memcpy(&(new_dir[original]), "/", 1);
                memcpy(&(new_dir[original + 1]), entry->d_name, extension);

                state->depth++;
                handle_dir(state, new_dir);
                state->depth--;
            } else {
                state->depth++;
                handle_file(state, entry->d_name);
                state->depth--;
            }
        }
        closedir(dir);
    } else {
        printf("incorrect dir: %s\n", dir_path);
        state->index++;
    }
}

void handle_file(State* state, char* file_path) {
    printf("%d\t", state->index);
    for (int i = 0; i < state->depth; ++i) {
        printf("  ");
    }
    printf("%s (file)\n", file_path);
}

#ifndef ACTION_H
#define ACTION_H

#include <stdlib.h>

#include "state.h"

bool parse_action(State* state, char* action_text);
void do_action(State* state);


void print_whole(State* state);
void quit_program(State* state);
void update_base_dir(State* state);


void handle_dir(State* state, char* dir_path);
void handle_file(State* state, char* dir_path);

#endif

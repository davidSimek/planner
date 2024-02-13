#include <stdbool.h>

#include "state.h"
#include "action.h"
#include "prompt.h"

int main(int argc, char *argv[])
{
    State state = {
        .should_run = true,
        .base_folder = "incorrect",
        .depth = 0,
        .index = 0
    };

    prompt_base_folder(&state);

    while(state.should_run) {
        prompt_action(&state);
        do_action(&state);
    }
    return 0;
}

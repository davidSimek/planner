#ifndef STATE_H
#define STATE_H

typedef enum {
    PRINT_WHOLE,
    QUIT,
    UPDATE_BASE_DIR
} Action;

typedef struct {
    bool should_run;
    char* base_folder;
    Action action;
    int index;
    int depth;
} State;




#endif

#include "compiler.h"
#include "utils/vector.h"
#include <stdlib.h>

struct lex_process* lex_process_create(struct compile_process* compiler, struct lex_process_functions* functions, void* custom){
    struct lex_process* process = calloc(1, sizeof(struct lex_process));
    process->function = functions;
    process->tokens = vector_create(sizeof(struct token));
    process->compiler = compiler;
    process->custom = custom;
    process->pos.lineNum = 1;
    process->pos.columnNum = 1;
    return process;
}

void lex_process_free(struct lex_process* process){
    vector_free(process->tokens);
    free(process);
}

void* lex_process_custom(struct lex_process* process){
    return process->custom;
}

struct vector* lex_process_tokens(struct lex_process* process){
    return process->tokens;
}
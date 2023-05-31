#include "compiler.h"

struct lex_process* lex_process;
int lex(struct lex_process *process)
{
    process->current_expression_count = 0;
    process->parentheses_buffer = NULL;
    process->pos.filename = process->compiler->in_file.path;
    lex_process = process;
    return 0;
}
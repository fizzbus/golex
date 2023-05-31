#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags) {
    FILE* file = fopen(filename, "r");
    if(!file){
        return NULL;
    }
    FILE* out_file = NULL;
    if(filename_out){
        out_file = fopen(filename_out, "w");
        if(!out_file){
            return NULL;
        }
    }

    struct compile_process* process = calloc(1, sizeof(struct compile_process));
    process->flags = flags;
    process->in_file.f = file;
    process->out_file = out_file;
    return process;
}

char compile_process_next_char (struct lex_process* lex_process) {
    struct compile_process* compiler = lex_process->compiler;
    compiler->pos.columnNum++;
    char c = getc(compiler->in_file.f);
    if(c == '\n'){
        compiler->pos.lineNum++;
        compiler->pos.columnNum = 1;
    }
    return c;
}

char compile_process_peek_char(struct lex_process* lex_process){
    struct compile_process* compiler = lex_process->compiler;
    char c = getc(compiler->in_file.f);
    ungetc(c, compiler-> in_file.f);
    return c;
}

void compiler_process_push_char(struct lex_process* lex_process, char c){
    struct compile_process* compiler = lex_process->compiler;
    ungetc(c, compiler->in_file.f);
}
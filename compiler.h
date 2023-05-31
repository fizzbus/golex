#ifndef GOLEX_H
#define GOLEX_H

#include <stdio.h>
#include <stdbool.h>


enum {
    COMPILER_SUCCESS,
    COMPILER_FAILED_W_ERRORS
};

enum {
    LEXICAL_ANALYSIS_SUCCESS,
    LEXICAL_ANALYSIS_FAILED
};

struct position {
    int lineNum;
    int columnNum;
    const char* filename;
};

enum {
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_SYMBOL,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_COMMENT,
    TOKEN_NEWLINE
};

struct lex_process;
typedef char (*LEX_PROCESS_NEXT_CHAR)(struct lex_process* process); //abstraction of function pointers
typedef char (*LEX_PROCESS_PEEK_CHAR)(struct lex_process* process);
typedef void (*LEX_PROCESS_PUSH_CHAR)(struct lex_process* process, char c);

struct lex_process_functions {
    LEX_PROCESS_NEXT_CHAR next_char;
    LEX_PROCESS_PEEK_CHAR peek_char;
    LEX_PROCESS_PUSH_CHAR push_char;
    
};

struct lex_process {
    struct position pos;
    struct vector* tokens;
    struct compile_process* compiler;
    int current_expression_count; //count expressions within brackets
    struct bugger* parentheses_buffer; // explaing later
    struct lex_process_functions* function;;
    void* custom;
};

int lex(struct lex_process* process);

struct token{
    int type;
    int flags;
    union {
        char cval;
        const char* sval;
        unsigned int inum;
        unsigned long lnum;
        unsigned long long llnum;
        void* any;
    };

    bool whitespace; //whether there is whitespace bw tokens

    const char* bw_brasckets; // string bw brackets for debug
};

struct compile_process{
    int flags; //set for file compile options

    struct position pos;

    struct compile_process_input_file {
        FILE* f;
        const char* path;
    } in_file;

    FILE* out_file;
};

struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags);
int compile_file(const char* filename, const char* out_filename, int flags);

char compile_process_next_char (struct lex_process* lex_process);
char compile_process_peek_char(struct lex_process* lex_process);
void compiler_process_push_char(struct lex_process* lex_process, char c);

struct lex_process* lex_process_create(struct compile_process* compiler, struct lex_process_functions * functions, void* custom);
void lex_process_free(struct lex_process* process);
void* lex_process_custom(struct lex_process* process);
struct vector* lex_process_tokens(struct lex_process* process);

#endif
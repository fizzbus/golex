#include <stdio.h>
#include "utils/vector.h"
#include "compiler.h"

int main() {
    int res = compile_file("./test.c", "./test", 0);
    if(res == COMPILER_SUCCESS){
        printf("Compiled OK\n");
    }
    else if(res == COMPILER_FAILED_W_ERRORS){
        printf("Compile Failed\n");
    }
    else {
        printf("Unknown Error");
    }
    return 0;
}
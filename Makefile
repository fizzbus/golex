OBJECTS= ./build/compiler.o ./build/cprocess.o ./build/lexer.o ./build/lex_process.o ./build/utils/vector.o ./build/utils/buffer.o
INCLUDES= -I./

all:${OBJECTS}
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main

./build/compiler.o: ./compiler.c
	gcc compiler.c ${INCLUDES} -o ./build/compiler.o -g -c


./build/cprocess.o: ./cprocess.c
	gcc cprocess.c ${INCLUDES} -o ./build/cprocess.o -g -c

./build/lexer.o: ./lexer.c
	gcc lexer.c ${INCLUDES} -o ./build/lexer.o -g -c

./build/lex_process.o: ./lex_process.c
	gcc lex_process.c ${INCLUDES} -o ./build/lex_process.o -g -c

./build/utils/vector.o: ./utils/vector.c
	gcc ./utils/vector.c ${INCLUDES} -o ./build/utils/vector.o -g -c

./build/utils/buffer.o: ./utils/buffer.c
	gcc ./utils/buffer.c ${INCLUDES} -o ./build/utils/buffer.o -g -c

clean:
	rm ./main
	rm -rf ${OBJECTS}
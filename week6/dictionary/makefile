CFLAG=-Wall -g
main: main.c model_lib.c input.c Bdict.c
	gcc -o main main.c model_lib.c input.c Bdict.c -Ibt/inc -Lbt/lib -lbt -D_FILE_OFFSET_BITS=64 -lncurses

btfilecreate: btfile.c
	gcc -o btfile btfile.c -Ibt/inc -Lbt/lib -lbt -D_FILE_OFFSET_BITS=64
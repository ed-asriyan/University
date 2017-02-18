CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -ggdb -O0 -g3
OBJS := main.o matrix.o

main.exe : $(OBJS)
	$(CC) $(CFLAGS) -o main.exe $(OBJS)

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe

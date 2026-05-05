CC = gcc
CFLAGS = -Wall -Wextra -g

OBJS = parser.o runner.o main.o

grader: $(OBJS)
	$(CC) $(CFLAGS) -o grader $(OBJS)

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

code_runner.o: runner.c
	$(CC) $(CFLAGS) -c runner.c

main.o: main.c parser.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o grader
all: todo-list clear

todo-list: main.o task.o
	gcc main.o task.o -o todo-list

main.o:
	gcc -c main.c

task.o:
	gcc -c task.c

clear:
	rm *.o

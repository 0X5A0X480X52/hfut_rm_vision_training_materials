calculator: main.o math_utils.o
	gcc -Wall -g -o calculator main.o math_utils.o

main.o: ../main.c ../math_utils.h
	gcc -Wall -g -c ../main.c

math_utils.o: ../math_utils.c ../math_utils.h
	gcc -Wall -g -c ../math_utils.c

clean:
	rm -f *.o calculator
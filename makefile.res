analysis : analysis.o main_analysis.o
	gcc -o analysis  -g analysis.o main_analysis.o

analysis.o : analysis.c
	gcc -o analysis.o -g -c analysis.c -W -Wall -ansi -pedantic

main_analysis.o : main_analysis.c
	gcc -o main_analysis.o -g -c main_analysis.c -W -Wall -ansi -pedantic

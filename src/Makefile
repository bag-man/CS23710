
main: *.c *.h
	gcc main.c -o main -Wall -g -std=c99 -lm libnavigation.a

test: main
	./main -s ../data/sightings_4.txt -o ../data/observers_4.txt

gdb: main
	gdb --args main -s ../data/sightings_4.txt -o ../data/observers_4.txt


clean:
	rm main


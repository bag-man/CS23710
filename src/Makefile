main: 
	gcc main.c -o main -Wall -g -std=c99 -lm libnavigation.a

clean:
	rm main

test: main
	./main -s ../data/sightings_4.txt -o ../data/observers_4.txt

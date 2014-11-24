#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "docopt/docopt.c"

struct obersvations_ *observations;

int main(int argc, char *argv[]) {

  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sightings && !args.observers) {
    printf(" %s", args.help_message);
    return 1;
  }
  
  FILE *sightings_file = fopen(args.sightings, "r");
  FILE *observers_file = fopen(args.observers, "r");

  //read_file(sightings_file, 0);
  read_file(observers_file, 1);

  return 0;
}

void read_file(FILE *file, int type) {
  char c = 0;
  char word[6] = "XXXXXX"; //Is there a less ugly way of doing this?
  int num_lines = 0;

  while (c != EOF) {
    if(type) {
    } else {
      int date[6];
      for(int i=0; i < 6; i++) {
	c = fscanf(file, "%d", date[i]); 
	printf("%d\n", date[i]);
        exit(0);
      }
      num_lines++;

      struct observer_ observer;
      for(int i=0; i < 3; i++) {
	c = fscanf(file, "%s", observer.user_name); 
	c = fscanf(file, "%f", observer.angle); 
	c = fscanf(file, "%f", observer.distance); 
      }
      num_lines++;
      //Malloc and add new observer
    }
  } 

  if(type) {
    num_lines -= 6;
    num_lines /= 3;
  } else {
    num_lines /= 4;
  }

  printf("%d", num_lines);

  fclose(file);
}

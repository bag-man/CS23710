#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "docopt/docopt.c"

int main(int argc, char *argv[]) {

  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sightings && !args.observers) {
    printf(" %s", args.help_message);
    return 1;
  }
  
  FILE *sightings_file = fopen(args.sightings, "r");
  FILE *observers_file = fopen(args.observers, "r");

  read_file(sightings_file, 0);
  read_file(observers_file, 1);

  return 0;
}

void read_file(FILE *file, int type) {
  char c = 0;
  char word[6] = "XXXXXX"; //Is there a less ugly way of doing this?
  int num_lines = 0;

  while (c != EOF) {
    c = fscanf(file, "%s", word); 
    if(c != EOF) {
      num_lines++;
      printf("%s\n", word);    
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

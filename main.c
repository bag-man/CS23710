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

  //read_file(sightings_file, 0);
  read_file(observers_file, 1);

  return 0;
}

void read_file(FILE *file, int type) {
  char c;
  int num_lines = 0;
  int date[6];
  struct tm time;

  for(int i=0; i < 6; i++) {
    c = fscanf(file, "%d", &date[i]); 
  }

  time.tm_mday = date[0];
  time.tm_mon  = date[1];
  time.tm_year = date[2];
  time.tm_hour = date[3];
  time.tm_min  = date[4];
  time.tm_sec  = date[5];

  num_lines++; // Date line

  while (c != EOF) {
    struct observer_ record;
    for(int i=0; i < 3; i++) {
      c = fscanf(file, "%s", record.user_name); 
      c = fscanf(file, "%lf", &record.latitude); 
      c = fscanf(file, "%lf", &record.longitude); 
    }
    num_lines++;
  } num_lines++; // Instead of do..while

  printf("%d", num_lines);

  fclose(file);
}

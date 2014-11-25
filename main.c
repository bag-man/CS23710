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
  read_observations(observers_file);

  return 0;
}

void read_observations(FILE *file) {

  /* Read Date */
  int date[6];

  for(int i=0; i < 6; i++) {
    fscanf(file, "%d", &date[i]); 
  }
  
  struct tm time;
  time.tm_mday = date[0];
  time.tm_mon  = date[1];
  time.tm_year = date[2];
  time.tm_hour = date[3];
  time.tm_min  = date[4];
  time.tm_sec  = date[5];

  /* Read Records */
  struct observer_ *root;       
  struct observer_ *conductor;  

  root = malloc(sizeof(struct observer_));  
  root->next = 0; 
  conductor = root;

  char c = 0;
  while (c != EOF) {
    conductor->next = malloc(sizeof(struct observer_));  
    c = fscanf(file, "%s", conductor->user_name); 
    c = fscanf(file, "%lf", &conductor->latitude); 
    c = fscanf(file, "%lf", &conductor->longitude); 
    conductor = conductor->next; 
  } 
  conductor = root;

  while ( conductor->next != NULL ) {
      printf("%s", conductor->user_name);
      printf(" %lf", conductor->latitude);
      printf(" %lf\n", conductor->longitude);
      conductor = conductor->next;
  }

  fclose(file);
}

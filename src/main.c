#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "../docopt/docopt.c"
#include "read_files.c"
#include "calculations.c"

int main(int argc, char *argv[]) {

  /* Docopt command line usage */
  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sighting || !args.observer) {
    printf(" %s", args.help_message);
    return 1;
  }

  /* Create observation by reading the files */
  Observation *observation;
  
  FILE *sightings_file = fopen(args.sighting, "r");
  FILE *observers_file = fopen(args.observer, "r");

  observation = read_observations(observers_file);
  fclose(observers_file);

  observation->sightings = read_sightings(sightings_file, observation);
  fclose(sightings_file);

  /* Print out the date */
  printf("%d-%d-%d %d:%d:%.2d\n", 
    observation->time.tm_mday,
    observation->time.tm_mon,
    observation->time.tm_year,
    observation->time.tm_hour,
    observation->time.tm_min,
    observation->time.tm_sec
  );

  /* Calculate positions, find if in area, then print out */
  Sighting *conductor;
  conductor = observation->sightings;

  //int count = 0;
  printf("\nRaw data\n");
  printf("UID\t OLAT\t OLONG\t TYPE\t BEARNG\t RANGE\t CMLAT\t CMLONG\n");
  while(conductor->next != NULL) {
    find_position(conductor);
    find_in_area(conductor);
    print_sighting(conductor);
    conductor = conductor->next;
    //count++;
  }

  /* print averages */
  printf("\nAverages\n");
  printf("UID\t OLAT\t OLONG\t TYPE\t BEARNG\t RANGE\t CMLAT\t CMLONG");

  //find_duplicates(observation->sightings, count);

  printf("\nRaw data + Averages\n");
  printf("UID\t OLAT\t OLONG\t TYPE\t BEARNG\t RANGE\t CMLAT\t CMLONG\n");
  conductor = observation->sightings;
  while(conductor->next != NULL) {
    print_sighting(conductor);
    conductor = conductor->next;
  }
  
  return 0;

}

void print_sighting(Sighting *conductor) {

  //if(conductor->visible) {
    printf(" %p\t", conductor);
    printf(" %s\t", conductor->observer->id);
    printf(" %.3lf\t", conductor->observer->location.lat);
    printf(" %.3lf\t", conductor->observer->location.lng);
    printf(" %c\t", conductor->type);
    printf(" %.1lf\t", conductor->bearing);
    printf(" %.3lf\t", conductor->range);
    printf(" %.3lf\t", conductor->location.lat);
    printf(" %.3lf\t", conductor->location.lng);
    printf(" %p\n", conductor->next);
  //}

}

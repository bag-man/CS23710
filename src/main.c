#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "../docopt/docopt.c"
#include "read_files.c"
#include "calculations.c"

Observation *observation;

int main(int argc, char *argv[]) {

  /* Docopt command line usage */
  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sighting || !args.observer) {
    printf(" %s", args.help_message);
    return 1;
  }

  /* Read in file */
  FILE *sightings_file = fopen(args.sighting, "r");
  FILE *observers_file = fopen(args.observer, "r");
  if(!observers_file || !sightings_file) {
    printf("File path invalid\n");
    return 1;
  }

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

  /* Calculate positions, and remove mamals not in area */
  int count = 0;
  while(conductor->next != NULL) {
    find_position(conductor);
    find_in_area(conductor);
    conductor = conductor->next;
    count++;
  }

  print_sightings_list();

  find_duplicates(observation->sightings, count);

  print_sightings_list();

  return 0;

}

Observation * get_observation() {
  return observation;
}

void print_sightings_list() {
  Sighting *conductor;
  conductor = observation->sightings;
  printf("\nSightings\n");
  printf("UID\t OLAT\t OLONG\t TYPE\t BEARNG\t RANGE\t CMLAT\t CMLONG\n");
  conductor = observation->sightings;
  while(conductor->next != NULL) {
    print_sighting(conductor);
    conductor = conductor->next;
  }
} 

void print_sighting(Sighting *conductor) {

  //printf(" %p\t", conductor->prev);
  //printf(" %p\t", conductor);
  printf(" %s\t", conductor->observer->id);
  printf(" %.3lf\t", conductor->observer->location.lat);
  printf(" %.3lf\t", conductor->observer->location.lng);
  printf(" %c\t", conductor->type);
  printf(" %.1lf\t", conductor->bearing);
  printf(" %.3lf\t", conductor->range);
  printf(" %.3lf\t", conductor->location.lat);
  printf(" %.3lf\n", conductor->location.lng);
  //printf(" %p\n", conductor->next);

}

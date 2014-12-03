#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "docopt/docopt.c"
#include "read_files.c"
#include "calculations.c"

int main(int argc, char *argv[]) {

  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sighting || !args.observer) {
    printf(" %s", args.help_message);
    return 1;
  }

  Observation *root_observation;
  
  FILE *sightings_file = fopen(args.sighting, "r");
  FILE *observers_file = fopen(args.observer, "r");

  root_observation = read_observations(observers_file);
  fclose(observers_file);

  root_observation->sightings = observation_read_sightings(sightings_file, root_observation);
  fclose(sightings_file);

  Sighting *conductor;
  conductor = root_observation->sightings;

  printf("UID\t OLAT\t OLONG\t TYPE\t BEARNG\t RANGE\t CMLAT\t CMLONG\n");
  while ( conductor->next != NULL ) {
    find_position(conductor);
    print_sighting(conductor);
    conductor = conductor->next;
  }

  return 0;
}

void print_sighting(Sighting *conductor) {
 printf("%s\t", conductor->observer->id);
 printf(" %.3lf\t", conductor->observer->olat);
 printf(" %.3lf\t", conductor->observer->olong);
 printf(" %c\t", conductor->type);
 printf(" %.1lf\t", conductor->bearing);
 printf(" %.3lf\t", conductor->range);
 printf(" %.3lf\t", conductor->cmlat);
 printf(" %.3lf\n", conductor->cmlong);
}

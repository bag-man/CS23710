#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "docopt/docopt.c"
#include "read_files.c"
#include "calculations.c"

int main(int argc, char *argv[]) {

  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sightings || !args.observers) {
    printf(" %s", args.help_message);
    return 1;
  }

  Observation *root_observation;
  
  FILE *sightings_file = fopen(args.sightings, "r");
  FILE *observers_file = fopen(args.observers, "r");

  root_observation = read_observations(observers_file);
  fclose(observers_file);

  root_observation->sightings = observation_read_sightings(sightings_file, root_observation);
  fclose(sightings_file);

  Sighting *conductor;
  conductor = root_observation->sightings;

  printf("UID\t OLAT\t OLONG\t Type\t BGR\t Range\t CMLAT\t CMLONG\n");
  while ( conductor->next != NULL ) {
    printf("%s\t", conductor->observer->user_name);
    printf(" %.3lf\t", conductor->observer->latitude);
    printf(" %.3lf\t", conductor->observer->longitude);
    printf(" %c\t", conductor->mamal);
    printf(" %.1lf\t", conductor->angle);
    printf(" %.3lf\t", conductor->distance);
    find_position(conductor);
    conductor = conductor->next;
  }

  return 0;
}

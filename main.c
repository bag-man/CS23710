#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "docopt/docopt.c"
#include "read_files.c"

int main(int argc, char *argv[]) {

  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sightings && !args.observers) {
    printf(" %s", args.help_message);
    return 1;
  }
  
  FILE *sightings_file = fopen(args.sightings, "r");
  FILE *observers_file = fopen(args.observers, "r");

  read_observations(observers_file);
  read_sightings(sightings_file);

  return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include "docopt/docopt.c"

int main(int argc, char *argv[]) {
  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.sightings && !args.observers) {
    printf(" %s", args.help_message);
    return 1;
  }
  
  FILE *sightings_file = fopen(args.sightings, "r");
  FILE *observers_file = fopen(args.observers, "r");

  return 0;
}

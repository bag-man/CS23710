#include <time.h>
#include "navigation.h"
#define Location location // So that Location structs can start with a capital L

typedef struct Observer {
  char id[5];
  double olat;
  double olong;
  struct Observer *next; 
} Observer;

typedef struct Sighting {
  Observer *observer;
  char type;
  double bearing;
  double range;
  Location location;
  struct Sighting *next;
  struct Sighting *prev;
} Sighting;


typedef struct {
  struct tm time;
  Observer *observers;
  Sighting *sightings;
} Observation;

Observation * read_observations(FILE *file);
Sighting * read_signting(Observation *observation, FILE file);
void print_sighting(Sighting *conductor);

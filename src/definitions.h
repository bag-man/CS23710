#include <time.h>

typedef struct Observer {
  char id[5];
  double olat;
  double olong;
  struct Observer *next; 
} Observer;

typedef struct Location {
  double lat;
  double lng;
} Location;

typedef struct Sighting {
  Observer *observer;
  char type;
  double bearing;
  double range;
  double cmlat;
  double cmlong;
  struct Location location;
  struct Sighting *next;
} Sighting;


typedef struct {
  struct tm time;
  Observer *observers;
  Sighting *sightings;
} Observation;

Observation * read_observations(FILE *file);
Sighting * read_signting(Observation *observation, FILE file);
void print_sighting(Sighting *conductor);

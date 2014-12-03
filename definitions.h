#include <time.h>

typedef struct Observer {
  char user_name[5];
  double latitude;
  double longitude;
  struct Observer *next; 
} Observer;

typedef struct Sighting {
  Observer *observer;
  char mamal;
  double angle;
  double distance;
  struct Sighting *next;
} Sighting;


typedef struct {
  struct tm time;
  Observer *observers;
  Sighting *sightings;
} Observation;

Observation * read_observations(FILE *file);
Sighting * observation_read_signting(Observation *observation, FILE file);

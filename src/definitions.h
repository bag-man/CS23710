#include <time.h>
#include "navigation.h"
#define Location location // So that Location structs can start with a capital L

typedef struct Observer {
  char id[5];
  Location location;
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

/* main.c */
Observation * get_observation();
void print_sightings_list();
void print_sighting(Sighting *conductor);

/* read_files.c */
Observation * read_observations(FILE *file);
Sighting * read_signting(Observation *observation, FILE file);

/* calculations.c */
void find_position(Sighting *sighting); 
void find_in_area(Sighting *sighting);
void remove_sighting(Sighting *sighting);
void find_duplicates(Sighting *sighting);

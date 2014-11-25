#include <time.h>

// Observation
struct observation {
  struct tm time;
  struct observer_ *obersvers;
  struct sighting_ *sightings;
};

// Linked list of observations
struct observations {
  struct observation data;
  struct observations *next;
};

// Each observer
struct observer_ {
  char user_name[4];
  double latitude;
  double longitude;
  struct observer_ *next; // Linked list?
};

// Each sighting
struct sighting_ {
  struct observer_ observer;
  char mamal;
  double angle;
  double distance;
};

void read_observations(FILE *file);

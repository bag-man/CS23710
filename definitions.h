#include <time.h>

// Observation
struct observation_ {
  struct tm time;
  struct observer_ *observers;
  struct sighting_ *sightings;
};

// Each observer
struct observer_ {
  char user_name[5];
  double latitude;
  double longitude;
  struct observer_ *next; // Linked list?
};

// Each sighting
struct sighting_ {
  struct observer_ *observer;
  char mamal;
  double angle;
  double distance;
  struct  sighting_ *next;
};

struct observation_ read_observations(FILE *file);
struct sighting_ read_sightings(FILE *file, struct observation_ root_obs);

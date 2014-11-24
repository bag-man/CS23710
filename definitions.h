#include <time.h>

struct observations_ {
  struct tm time;
  struct observer_ *obersvers;
  struct sighting_ *sightings;
}

struct observer_ {
  char user_name[4];
  float latitude;
  float longitude;
}

struct sighting_ {
  struct observer_ observer;
  char mamal;
  float angle;
  float distance;
}

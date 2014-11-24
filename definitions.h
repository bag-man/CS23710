#include <time.h>

struct observations_ {
  struct tm time;
  struct observer_ *obersvers;
  struct sighting_ *sightings;
};

struct observer_ {
  char user_name[4];
  float latitude;
  float longitude;
};

struct sighting_ {
  struct observer_ observer;
  char mamal;
  float angle;
  float distance;
};

void read_file(FILE *file, int type);

/*
      observations[0].time.tm_mday = date[0];
      observations[0].time.tm_mon = date[1];
      observations[0].time.tm_year = date[2];
      observations[0].time.tm_hour = date[3];
      observations[0].time.tm_min = date[4];
      observations[0].time.tm_sec = date[5];
*/

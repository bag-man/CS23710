#include <math.h>
void find_position(struct sighting_ *sighting) {
  double longitude, latitude;
  latitude = sighting->observer->latitude + (sighting->distance * cos(sighting->angle)) / 60.0;
  longitude = sighting->observer->longitude + (sighting->distance * sin(sighting->angle) / cos(sighting->observer->latitude)) / 60.0;

  printf(" %.3lf\t", latitude);
  printf(" %.3lf\n", longitude);
}

void find_distance() {

}

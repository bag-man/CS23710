#include <math.h>
#include "navigation.h"
void find_position(Sighting *sighting) {
  sighting->cmlat = sighting->observer->olat + (sighting->range * cos(sighting->bearing)) / 60.0;
  sighting->cmlong = sighting->observer->olong + (sighting->range * sin(sighting->bearing) / cos(sighting->observer->olat)) / 60.0; 
}

void find_distance() {

}

#include <math.h>
#include "navigation.h"
#define M_PI 3.14159265358979323846264338327 // Wasn't defined for some reason

void find_position(Sighting *sighting) {
  double olatr = (sighting->observer->olat) * M_PI / 180.0; 
  sighting->location.lat = sighting->observer->olat + (sighting->range * cos(sighting->bearing)) / 60.0;
  sighting->location.lng = sighting->observer->olong + (sighting->range * sin(sighting->bearing) / cos(olatr)) / 60.0; 
}

/*
void find_duplicates(Sighting *sighting) {
  Sighting conductor = sighting;
  while ( conductor->next != NULL ) {
    while ( 
      conductor->location.lat + 0.02 > conductor->next->location.lat ||
      conductor->location.lat - 0.02 < conductor->next->location.lat

} 
*/


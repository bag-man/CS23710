#include <math.h>
#include "navigation.h"
#define M_PI 3.14159265358979323846264338327 // Wasn't defined for some reason

void find_position(Sighting *sighting) {
  double olatr = (sighting->observer->olat) * M_PI / 180.0; 
  sighting->location.lat = sighting->observer->olat + (sighting->range * cos(sighting->bearing)) / 60.0;
  sighting->location.lng = sighting->observer->olong + (sighting->range * sin(sighting->bearing) / cos(olatr)) / 60.0; 
}

void find_duplicates(Sighting *sighting) {
  Sighting *conductor = sighting;
  while(conductor->next != NULL) {
    Sighting *loop_conductor = conductor->next;
    while(loop_conductor != NULL) {
      printf("here");
      if(
	abs(conductor->location.lat - loop_conductor->location.lat) <= 0.02 && 
	abs(conductor->location.lng - loop_conductor->location.lng) <= 0.02
      ) {
	printf("These need to be within 0.02 to be a duplicate!\n");
	printf("%.3lf : %.3lf\n", conductor->location.lng, loop_conductor->location.lng);
	printf("%.3lf : %.3lf\n", conductor->location.lat, loop_conductor->location.lat);
      }
      loop_conductor = loop_conductor->next;
    }
    loop_conductor = sighting;
    conductor = conductor->next;
  }
} 

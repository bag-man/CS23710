#include <math.h>
#define M_PI 3.14159265358979323846264338327 // Wasn't defined in math.h for some reason

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
      double distance = great_circle(conductor->location, loop_conductor->location);
      if(distance <= 0.02) {
	printf("We have a duplicate!\n");
      } 
      loop_conductor = loop_conductor->next;
    }
    loop_conductor = sighting;
    conductor = conductor->next;
  }
} 

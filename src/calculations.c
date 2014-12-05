#include <math.h>
#define PROXIMITY 0.02
#define M_PI 3.14159265358979323846264338327 // Wasn't defined in math.h for some reason

void find_position(Sighting *sighting) {
  double olatr = (sighting->observer->olat) * M_PI / 180.0; 
  sighting->location.lat = sighting->observer->olat + (sighting->range * cos(sighting->bearing)) / 60.0;
  sighting->location.lng = sighting->observer->olong + (sighting->range * sin(sighting->bearing) / cos(olatr)) / 60.0; 
}

void find_duplicates(Sighting *sighting) {

  Observer *average_observer = malloc(sizeof(Observer));
  strcpy(average_observer->id, "AVRG");
  Sighting *conductor = sighting;

  while(conductor->next != NULL) {

    Sighting *loop_conductor = conductor->next;
    Sighting *tmp_conductor_root = conductor;
    Sighting *tmp_conductor = tmp_conductor_root;

    while(loop_conductor != NULL) {
      if(conductor->type == loop_conductor->type) {
	double distance = great_circle(conductor->location, loop_conductor->location);
	if(distance <= PROXIMITY) {
	  printf("We have a duplicate!\n");
	  // Add duplicate to temp listt
	  tmp_conductor->next = loop_conductor; // segfault
	  tmp_conductor = tmp_conductor->next;
	} 
      }
      // Add Average of temp list to sightings list
      Sighting *average_position = malloc(sizeof(Sighting));
      average_position->observer = average_observer; 
      tmp_conductor = tmp_conductor_root;
      double avg_lat, avg_lng = 0;
      int count = 0;
      while(tmp_conductor != NULL) {
	avg_lat += tmp_conductor->location.lat;
	avg_lng += tmp_conductor->location.lng;
	count++;
	tmp_conductor = tmp_conductor->next;
      }
      avg_lat /= count;
      avg_lng /= count;
      average_position->location.lat = avg_lat;
      average_position->location.lng = avg_lng;
      //print_sighting(average_position);

      loop_conductor = loop_conductor->next;
    }
    loop_conductor = sighting;
    conductor = conductor->next;
  }
} 

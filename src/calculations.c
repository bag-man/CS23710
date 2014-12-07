#include <math.h>
#define PROXIMITY 0.02
#define M_PI 3.14159265358979323846264338327 // Wasn't defined in math.h for some reason

void find_position(Sighting *sighting) {

  double olatr = (sighting->observer->olat) * M_PI / 180.0; 
  double bgr = (sighting->bearing) * M_PI / 180.0; 
  sighting->location.lat = sighting->observer->olat + (sighting->range * cos(bgr)) / 60.0;
  sighting->location.lng = sighting->observer->olong + (sighting->range * sin(bgr) / cos(olatr)) / 60.0; 

  if((sighting->location.lng < -4) || (sighting->location.lng > -5.5) || 
     (sighting->location.lat > 52.833) || (sighting->location.lat < 52)) {

    printf("This code ran!\n");
    sighting->prev->next = sighting->next;  

  }

}

void find_duplicates(Sighting *sighting, int count) {
  printf("\n");
  Sighting *sighting_list[count];

  int i = 0;
  int found[count];
  while(sighting->next != NULL) {
    sighting_list[i] = sighting;
    sighting = sighting->next;
    found[i] = 0;
    i++;
  } 

  int identifier = 1;
  for(int i = 0; i < count; i++) {
    for(int j = 0; j < count; j++) {
      if((i != j) && (sighting_list[i]->type == sighting_list[j]->type) && found[j] == 0) {
	double distance = great_circle(sighting_list[i]->location, sighting_list[j]->location);
	if(distance <= PROXIMITY) {
	  found[i] = identifier;
	  found[j] = identifier;
        }
      }
    }

    for(int i = 0; i < count; i++) {
      //printf("%d\n",found[i]);
    }

    Observer *average_observer = malloc(sizeof(Observer));
    strcpy(average_observer->id, "AVRG");

    double avg_lat = 0;
    double avg_lng = 0;
    int num_avg = 0;
    char type;
    for(int i = 0; i < count; i++) {
      if(found[i] == identifier) {
	print_sighting(sighting_list[i]);
	type = sighting_list[i]->type;
	avg_lat += sighting_list[i]->location.lat;
	avg_lng += sighting_list[i]->location.lng;
	num_avg++;
      }
    }

    if(found[i] == identifier) {
      Sighting *average_position = malloc(sizeof(Sighting));
      average_position->observer = average_observer;
      average_position->type = type;
      avg_lat /= num_avg;
      avg_lng /= num_avg;
      average_position->location.lat = avg_lat;
      average_position->location.lng = avg_lng;
      print_sighting(average_position);
      printf("\n");
    }
    identifier++;
  }
}

/*void find_duplicates(Sighting *sighting) {

  Observer *average_observer = malloc(sizeof(Observer));
  strcpy(average_observer->id, "AVRG");
  Sighting *conductor = sighting;

  while(conductor->next != NULL) { // Loop through sightings

    Sighting *loop_conductor = conductor->next;
    Sighting *tmp_conductor_root = conductor;
    Sighting *tmp_conductor = tmp_conductor_root;

    while(loop_conductor != NULL) {
      if(conductor->type == loop_conductor->type) {
	double distance = great_circle(conductor->location, loop_conductor->location);
	if(distance <= PROXIMITY) {
	  printf("We have a duplicate!\n");
	  // Add duplicate to temp list
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
	printf("%d\n", count);
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
}  */

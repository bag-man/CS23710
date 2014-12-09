#include <math.h>
#define PROXIMITY 0.02
#define M_PI 3.14159265358979323846264338327 // Wasn't defined in math.h for some reason

/* Calculate the animals position, this works fine */
void find_position(Sighting *sighting) {
  double olatr = (sighting->observer->location.lat) * M_PI / 180.0; 
  double bgr = (sighting->bearing) * M_PI / 180.0; 
  sighting->location.lat = sighting->observer->location.lat + (sighting->range * cos(bgr)) / 60.0;
  sighting->location.lng = sighting->observer->location.lng + (sighting->range * sin(bgr) / cos(olatr)) / 60.0; 
}

/* Test if sighting is in our area */
void find_in_area(Sighting *sighting) {
  if((sighting->location.lng > -4) || (sighting->location.lng < -5.5))
    remove_sighting(sighting);
  else if((sighting->location.lat > 52.833) || (sighting->location.lat < 52)) 
    remove_sighting(sighting);
}

/* remove sighting from linked list */
void remove_sighting(Sighting *sighting) {
  if(sighting->prev == NULL) {
    Observation *observation = get_observation();
    observation->sightings = sighting->next;
    observation->sightings->prev = NULL;
  } else {
    sighting->prev->next = sighting->next;
  }
}

/* This function is a mess and needs sorting out */
void find_duplicates(Sighting *sighting, int count) {
  printf("\n");
  Sighting *sighting_list[count];

  int i = 0;
  int found[count];
  /* Create Array of pointers, is this bad form? */
  while(sighting->next != NULL) {
    sighting_list[i] = sighting;
    sighting = sighting->next;
    found[i] = 0;
    i++;
  } 

  int identifier = 1;
  for(int i = 0; i < count; i++) {
    for(int j = 0; j < count; j++) {
      if((i != j) && (sighting_list[i]->type == sighting_list[j]->type) && found[j] == 0 ) { 
	double distance = great_circle(sighting_list[i]->location, sighting_list[j]->location);
	if(distance <= PROXIMITY) {
	  found[i] = identifier;
	  found[j] = identifier;
        }
      }
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
	sighting_list[i]->type = 'A';
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

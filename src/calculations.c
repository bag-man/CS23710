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

/* Remove sighting from linked list */
void remove_sighting(Sighting *sighting) {
  if(sighting->prev == NULL) {
    Observation *observation = get_observation();
    observation->sightings = sighting->next;
    observation->sightings->prev = NULL;
  } else if(sighting->next == NULL) {
    sighting->prev->next = NULL;
  } else {
    sighting->prev->next = sighting->next;
    sighting->next->prev = sighting->prev;
  }
}

/* Add sighting to linked list */
void add_sighting(Sighting *sighting) {
  Observation *observation = get_observation();
  Sighting *conductor = observation->sightings;
  while(conductor != NULL) {
    if(conductor->next == NULL) {
      break;
    } else {
      conductor = conductor->next;
    }
  }
  conductor->next = sighting; 
  sighting->prev = conductor;
  sighting->next = NULL; 
}

/* Find duplicate sightings, and create averages */
void find_duplicates(Sighting *sighting) {

  /* Count the number of sightings */
  int i = 0;
  Sighting *counter = sighting;
  while(counter != NULL) {
    i++;
    counter = counter->next;
  } 

  /* Create an array of pointers of the sightings */
  Sighting *sighting_list[i];
  int y = 0;
  while(sighting != NULL) {
    sighting_list[y] = sighting;
    sighting = sighting->next;
    y++;
  }

  /* Create and initialise an array to 0 */
  int found[i]; // This represents sets of duplicate mamals. 
  for(int x = 0; x < i; x++) {
    found[x] = 0;
  }

  int count = i; // Total number of mamals
  int identifier = 1;
  for(int i = 0; i < count; i++) {
    for(int j = 0; j < count; j++) {
      if((i != j) && (sighting_list[i]->type == sighting_list[j]->type) && found[j] == 0 ) { // Test different mamal, same species, not found
        double distance = great_circle(sighting_list[i]->location, sighting_list[j]->location);
        if(distance <= PROXIMITY) {
          found[i] = identifier;
          found[j] = identifier;
        }
      }
    }

    Observer *average_observer = malloc(sizeof(Observer));
    strcpy(average_observer->id, "AVRG"); // Create a dummy observer

    double avg_lat = 0;
    double avg_lng = 0;
    int num_avg = 0;
    char type;

    for(int i = 0; i < count; i++) {
      /* Calculate average totals */
      if(found[i] == identifier) {
type = sighting_list[i]->type;
avg_lat += sighting_list[i]->location.lat;
avg_lng += sighting_list[i]->location.lng;
sighting_list[i]->type = 'A';
num_avg++;
      }
    }

    /* Create and add the average sighting */
    if(found[i] == identifier) {
      Sighting *average_position = malloc(sizeof(Sighting));
      average_position->observer = average_observer;
      average_position->type = type;
      avg_lat /= num_avg;
      avg_lng /= num_avg;
      average_position->location.lat = avg_lat;
      average_position->location.lng = avg_lng;
      average_position->next = NULL;
      add_sighting(average_position);
    }
    identifier++;
  }
}

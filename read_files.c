#define DATEVARS 6

Observation * read_observations(FILE *file) {

  /* Read Date */
  int date[DATEVARS];

  for(int i=0; i < DATEVARS; i++) {
    fscanf(file, "%d", &date[i]); 
  }
  
  tm time;
  time.tm_mday = date[0];
  time.tm_mon  = date[1];
  time.tm_year = date[2];
  time.tm_hour = date[3];
  time.tm_min  = date[4];
  time.tm_sec  = date[5];

  /* Read Records */
  Observer *root;       
  Observer *conductor;  

  root = malloc(sizeof(Observer));  
  root->next = NULL; 
  conductor = root;

  char c = 0;
  while (c != EOF) {
    conductor->next = malloc(sizeof(Observer));  
    c = fscanf(file, "%s", conductor->user_name); 
    c = fscanf(file, "%lf", &conductor->latitude); 
    c = fscanf(file, "%lf", &conductor->longitude); 
    if(c != EOF) {
      conductor = conductor->next; 
    } else { 
      conductor->next = NULL;
    }
  } 
  conductor = root;

  Observation *observation;
  observation = malloc(sizeof(Observation));  
  observation->time = time; 
  observation->observers = root;
  return observation; 
}

Sighting * read_sightings(FILE *file, Observation *root_obs) {

  Sighting *root;       
  Sighting *conductor;  

  root = malloc(sizeof(Sighting));  
  root->next = NULL; 
  conductor = root;
  char c = 0;
  char name[5];

  while (c != EOF) {
    conductor->next = malloc(sizeof(Sighting));  

    c = fscanf(file, "%s", name); 
    Observer *cond;
    cond = root_obs->observers;

    while(cond->next != NULL) {
      if(!strcmp(name, cond->user_name)) {
	conductor->observer = cond;
	break;
      } else {
	cond = cond->next;
      }
    }

    c = fscanf(file, " %c", &conductor->mamal); 
    c = fscanf(file, "%lf", &conductor->angle); 
    c = fscanf(file, "%lf", &conductor->distance); 

    if(c != EOF) {
      conductor = conductor->next; 
    } else { 
      conductor->next = NULL;
    }
  } 
  conductor = root;

  return root;
}

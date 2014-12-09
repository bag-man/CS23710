Observation * read_observations(FILE *file) {

  struct tm time;
  fscanf(file, "%d %d %d %d %d %d",
    &time.tm_mday,
    &time.tm_mon,
    &time.tm_year,
    &time.tm_hour,
    &time.tm_min,
    &time.tm_sec
  );

  /* Read Records */
  Observer *root;       
  Observer *conductor;  

  root = malloc(sizeof(Observer));  
  root->next = NULL; 
  conductor = root;

  char c = 0;
  while(c != EOF) {
    conductor->next = malloc(sizeof(Observer));  
    c = fscanf(file, "%s %lf %lf", 
      conductor->id,
      &conductor->olat,
      &conductor->olong
    ); 
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
  conductor = root;
  char c = 0;
  char name[5];

  while(c != EOF) {
    conductor->next = malloc(sizeof(Sighting));  

    c = fscanf(file, "%s", name); 
    Observer *cond;
    cond = root_obs->observers;

    while(cond->next != NULL) {
      if(!strcmp(name, cond->id)) {
	conductor->observer = cond;
	break;
      } else {
	cond = cond->next;
      }
    }

    c = fscanf(file, " %c %lf %lf",
      &conductor->type, 
      &conductor->bearing, 
      &conductor->range
    ); 

    if(c != EOF) {
      conductor = conductor->next; 
    } else { 
      conductor->next = NULL;
    }
  } 
  conductor = root;

  return root;

}

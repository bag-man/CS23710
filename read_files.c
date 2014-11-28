struct observation_ read_observations(FILE *file) {

  /* Read Date */
  int date[6];

  for(int i=0; i < 6; i++) {
    fscanf(file, "%d", &date[i]); 
  }
  
  struct tm time;
  time.tm_mday = date[0];
  time.tm_mon  = date[1];
  time.tm_year = date[2];
  time.tm_hour = date[3];
  time.tm_min  = date[4];
  time.tm_sec  = date[5];

  /* Read Records */
  struct observer_ *root;       
  struct observer_ *conductor;  

  root = malloc(sizeof(struct observer_));  
  root->next = NULL; 
  conductor = root;

  char c = 0;
  while (c != EOF) {
    conductor->next = malloc(sizeof(struct observer_));  
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

  /* Print for debug */
  while(conductor->next != NULL) {
    printf("%s", conductor->user_name);
    printf(" %lf", conductor->latitude);
    printf(" %lf\n", conductor->longitude);
    conductor = conductor->next;
  }

  fclose(file);

  struct observation_ observation;
  observation.time = time;
  observation.observers = root;
  return observation; 
}

struct sighting_ read_sightings(FILE *file, struct observation_ root_obs) {

  struct sighting_ *root;       
  struct sighting_ *conductor;  

  root = malloc(sizeof(struct sighting_));  
  root->next = NULL; 
  conductor = root;
  char c = 0;
  char name[5];

  while (c != EOF) {
    conductor->next = malloc(sizeof(struct sighting_));  

    c = fscanf(file, "%s", name); 
    struct observer_ *cond;
    cond = root_obs.observers;

    while(cond->next != NULL) {
      if(name == cond->user_name) {
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

  /* Print for debug */
  while ( conductor->next != NULL ) {
    printf("%s", conductor->observer);
    printf(" %c", conductor->mamal);
    printf(" %lf", conductor->angle);
    printf(" %lf\n", conductor->distance);
    conductor = conductor->next;
  }

  fclose(file);
  return *root;

}


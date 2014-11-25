void read_sightings(FILE *file) {

  struct sighting_ *root;       
  struct sighting_ *conductor;  

  root = malloc(sizeof(struct sighting_));  
  root->next = 0; 
  conductor = root;
  char c = 0;

  while (c != EOF) {
    conductor->next = malloc(sizeof(struct sighting_));  

    /* Need to find and link the name of the observer */
    c = fscanf(file, "%s", conductor->name); 
    c = fscanf(file, "%c", &conductor->mamal); 
    c = fscanf(file, "%lf", &conductor->angle); 
    c = fscanf(file, "%lf", &conductor->distance); 
    conductor = conductor->next; 
  } 
  conductor = root;

  /* Print for debug */
  while ( conductor->next != NULL ) {
      printf("%s", conductor->name);
      printf(" %c", conductor->mamal);
      printf(" %lf", conductor->angle);
      printf(" %lf\n", conductor->distance);
      conductor = conductor->next;
  }

  fclose(file);

}

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
  root->next = 0; 
  conductor = root;

  char c = 0;
  while (c != EOF) {
    conductor->next = malloc(sizeof(struct observer_));  
    c = fscanf(file, "%s", conductor->user_name); 
    c = fscanf(file, "%lf", &conductor->latitude); 
    c = fscanf(file, "%lf", &conductor->longitude); 
    conductor = conductor->next; 
  } 
  conductor = root;

  /* Print for debug */
  while ( conductor->next != NULL ) {
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

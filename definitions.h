struct time {
  int hours;
  int minutes;
  int seconds;
};

struct competitor {
  /*int totalTime;
  int cycleTime;
  int swimTime;
  int runTime;*/
  int number;
  int tT_in_seconds;
  char name[30];
  struct time tT;
  struct time rT;
  struct time cT;
  struct time sT;
};


struct time seconds_to_time(int time);
void print_competitor(struct competitor comp);

/*

struct competitor find_competitor(int high);
struct competitor find_competitor(int high) {
  int found = 0;
  struct competitor result; 
  for(int i = 0; i < NUM_COMPETITORS; i++) {
    if(high) {
      if(found == 0 || times[i].tT_in_seconds > found) {
	found = times[i].tT_in_seconds;
      }
    } else {
      if(found == 0 || times[i].tT_in_seconds < found) {
	found = times[i].tT_in_seconds;
      }
    }
  }

  for(int i = 0; i < NUM_COMPETITORS; i++) {
    if(found == times[i].tT_in_seconds) {
      result = times[i];
    }
  }

  return result;
}
*/

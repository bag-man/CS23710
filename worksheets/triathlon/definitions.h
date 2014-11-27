struct time {
  int hours;
  int minutes;
  int seconds;
};

struct competitor {
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
void insertSort(struct competitor a[]);
void print_competitors();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

#define NUM_COMPETITORS 4

struct competitor times[NUM_COMPETITORS];

int main() {

  for(int i = 0; i < NUM_COMPETITORS; i++) {
    int rH, rM, rS, sH, sM, sS, cH, cM, cS, totalTime;
    char name[30];
    struct time tT, sT, rT, cT;

    printf("\nEnter competitor name: "); 
    scanf(" %s", &name);

    printf("\nEnter times for competitor %s", name);
    printf("\nEnter running time ( H M S ): ");
    scanf(" %d %d %d", &rH, &rM, &rS);

    printf("\nEnter swimming time ( H M S ): ");
    scanf(" %d %d %d", &sH, &sM, &sS);

    printf("\nEnter cycle time ( H M S ): ");
    scanf(" %d %d %d", &cH, &cM, &cS);

    rH *= 3600;
    sH *= 3600;
    cH *= 3600;

    rM *= 60;
    sM *= 60;
    cM *= 60;

    totalTime = rH + rM + rS + sH + sM + sS + cH + cM + cS;
    times[i].tT_in_seconds = totalTime;
    times[i].tT = seconds_to_time(totalTime);
    times[i].cT = seconds_to_time(cH + cM + cS);
    times[i].sT = seconds_to_time(sH + sM + sS);
    times[i].rT = seconds_to_time(rH + rM + rS);
    strcpy(times[i].name, name);
    times[i].number = i;
 
    printf("%s has a total time of %dH %dM %dS.\n", times[i].name, times[i].tT.hours, times[i].tT.minutes, times[i].tT.seconds);
  }

  print_competitors();
  insertSort(times);
  print_competitors();

  return 0;
}

struct time seconds_to_time(int totalTime) {
  struct time humanTime;
  humanTime.hours = totalTime / 60 / 60;
  humanTime.minutes = totalTime / 60 - (humanTime.hours * 60);
  humanTime.seconds = totalTime - ((humanTime.minutes * 60) + (humanTime.hours * 60 * 60));  
  return humanTime;
}

void print_competitors() {
  printf("\nNAME \tcompetitor \tcycle time \tswim time \trun time \ttotal time\n");
  printf("=====================================================================================\n");
  for(int i = 0; i < NUM_COMPETITORS; i++) {
    print_competitor(times[i]);
  }

}

void print_competitor(struct competitor comp) {
  printf("%s\t  %8d\t  %dH %dM %dS\t %dH %dM %dS\t %dH %dM %dS\t %dH %dM %dS\n", comp.name, comp.number,
    comp.cT.hours, comp.cT.minutes, comp.cT.seconds,
    comp.sT.hours, comp.sT.minutes, comp.sT.seconds,
    comp.rT.hours, comp.rT.minutes, comp.rT.seconds,
    comp.tT.hours, comp.tT.minutes, comp.tT.seconds
  );
}

void insertSort(struct competitor a[]) {
  int i, j;
  struct competitor index;
  for (i = 1; i < NUM_COMPETITORS; ++i) {
    index = a[i];
    for (j = i; j > 0 && a[j-1].tT_in_seconds > index.tT_in_seconds; j--)
      a[j] = a[j-1];
    a[j] = index;
  }
}

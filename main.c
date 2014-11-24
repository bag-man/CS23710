#include <stdio.h>
#include <stdlib.h>
#include "docopt/docopt.c"

int main(int argc, char *argv[]) {
  DocoptArgs args = docopt(argc, argv, 1, "0.1");
  if(!args.cetacean && !args.observer) {
    printf(args.help_message);
    return 1;
  }

  return 0;
}

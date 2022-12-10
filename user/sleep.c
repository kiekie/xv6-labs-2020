#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    write(1, "error: empty input\n", 19);
    exit(0);
  }

  int tick = atoi(argv[1]);
  if (tick == 0) {
    write(1, "error: invalid input\n", 21);
  } else {
    sleep(tick);
  }
  exit(0);
}


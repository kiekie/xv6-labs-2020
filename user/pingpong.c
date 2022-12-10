
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int fds[2], status;
  char buf[100];

  // create a pipe, with two FDs in fds[0], fds[1].
  pipe(fds);

  int pid = fork();
  if (pid == 0) {
    read(fds[0], buf, sizeof(buf));
    printf("%d: received ping\n", getpid());
    write(fds[1], "b", 1);
    // close(fds[1]);
  } else {
    write(fds[1], "b", 1);
    wait(&status);
    read(fds[0], buf, sizeof(buf));
    printf("%d: received pong\n", getpid());
  }
  exit(0);
}

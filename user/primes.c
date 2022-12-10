#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int SIZE = 34;
  int bufSent[SIZE];

  //init bufsent
  for(int i = 0; i < SIZE; i++) {
    bufSent[i] = i + 2;
  }

  int sentLength = SIZE;

  for (int p = 0; p < 17; p++) {
    int fds[2], bufRev[SIZE];
    int bytesRead, numRead, status, pid;
    // create a pipe, with two FDs in fds[0], fds[1].
    pipe(fds);

    pid = fork();

    if (pid == 0) {
      bytesRead = read(fds[0], bufRev, sizeof(bufRev));
      numRead = bytesRead / sizeof(int);
      /*
      printf("%d, read %d nums\n", getpid(), numRead);
      for (int i = 0; i < numRead; i++) {
        printf("%d,", bufRev[i]);
      }
      */
      // last process
      if(numRead == 0) {
        break;
      }
      int firstNumber = bufRev[0];
      printf("prime %d\n", firstNumber);

      sentLength = 0;
      for (int i = 0; i < numRead; i++) {
        if( bufRev[i] % firstNumber != 0) {
            bufSent[sentLength++] =  bufRev[i];
        }
      }
      if (sentLength == 0) {
        close(fds[1]);
        break;
      }
    } else {
      write(fds[1], bufSent, sentLength * sizeof(int));
      wait(&status);
      close(fds[1]);
      break;
    }
  }
  exit(0);
}
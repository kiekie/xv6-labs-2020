#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"


int
main(int argc, char *argv[])
{
  char buf[100];
  int status;

  if(argc < 2) {
    fprintf(2, "usage: xargs [command]\n");
    exit(1);
  }

  while(gets(buf, sizeof(buf))) {
    if (buf[0] == '\0')
      break;
    int argvStart = 1;
    if (argc > 3 && strcmp(argv[1], "-n") == 0 && strcmp(argv[2], "1") == 0) {
      argvStart = 3;
    }
    int argSize = argc - argvStart + 1;  // add one argument
    int j = 0;
    char** execArgv = (char**)malloc(sizeof(char*)*(argSize)); // enough space
    for (int i = argvStart; i < argc; i++) {
        execArgv[j++] = argv[i];
    }
    execArgv[j] = (char*)malloc(sizeof(char) * (strlen(buf)+1));
    memcpy(execArgv[j], buf, strlen(buf) + 1);

    /*
    printf("PARENT ");
    for(int k = 0; k < argSize; k++)
      printf("%s ", execArgv[k]);
    printf("PARENT\n");
    */

    int pid = fork();
    if(pid == 0) { // child
      exec(argv[1], execArgv);
      exit(1);     // never reach
    } else {
      wait(&status);
    }
  }

  exit(0);
}

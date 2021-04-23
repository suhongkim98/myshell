#include <stdio.h>
#include "background.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "execute.h"

void backgroundExec(char* token[]){
   int pid;
   int fd_bg;
   if((pid = fork()) == 0) {
      fd_bg = open("/dev/null", O_RDONLY);
      dup2(fd_bg, STDOUT_FILENO); // 출력을 버린다.
      execute(token); // 명령어 백그라운드로 실행
      exit(0); 
   } else if(pid < 0) {
      printf("fork error in backgroundExec\n");
      exit(1);
   } 
}

#include <stdio.h>
#include <string.h>
#include "main.h"
#include <stdlib.h>
#include "execute.h"
#include <unistd.h>

int main()
{
    char buf[256];
    char *arg[MAXARG];
    char *s;
    char *save;
    int argi;
    static const char delim[] = " \t\n";
    int pid, status;

    while(1) {
       printf("myshell$ ");
       gets(buf);
       argi = 0;
       s = strtok_r(buf, delim, &save);
       while(s) {
          arg[argi++] = s;
          s = strtok_r(NULL, delim, &save);
       }
       arg[argi] = (char *)0;//문자열 분리 완료
       
       if (!strcmp(arg[0], "quit"))
           break;

        if((pid = fork()) == -1) {
            //자식 생성 실패
            perror("fork failed");
        } else if(pid != 0) {
            //부모
            pid = wait(&status);
        } else {
            //자식
            execute(arg);
        }
    }
    exit(0);
    return 0;
}


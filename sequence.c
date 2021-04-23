#include <stdio.h>
#include "sequence.h"
#include <unistd.h>
#include <sys/wait.h>
#include "execute.h"

void sequenceExec(char *token[], int idx)
{
    // ;를 만나면 ; 이전과 이후 명령어 실행

    int pid1, pid2;
    int status;
    token[idx] = (char *)0; // ;는 NULL로 만든다.

    if ((pid1 = fork()) == -1) // 프로세스 생성
    {
        //자식 생성 실패
        perror("fork failed");
    }
    else if (pid1 == 0)
    {
        // 자식은 실행
        execute(token);
    }
    else
    {
        //부모는 기다려리
        wait(&status);
    }
    if ((pid2 = fork()) == -1) // 프로세스 생성
    {
        //자식 생성 실패
        perror("fork failed");
    }
    else if (pid2 != 0)
    {
        execute(token + idx + 1); // ; 이후, ;가 3개 이상이라면 이 안에서 또 ;를 나누어 재귀로 처리한다.
    }
    else
    {
        //부모는 기다려리
        wait(&status);
    }
}

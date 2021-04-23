#include <stdio.h>
#include "pipeline.h"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "execute.h"
#include <stdlib.h>

void pipelineExec(char* token[], int idx){
    int fd[2];
    int front;
    int back;
    token[idx] = (char *)0; // | 자리에 NULL 삽입

    if(pipe(fd) == -1) {
        // 파이프 생성
        perror("error pipe in pipelineExec");
        exit(1);
    }

    if((front = fork()) == 0) {
        dup2(fd[1], STDOUT_FILENO); // 출력을 파이프라인 출력으로 연결
        
        close(fd[0]);
        close(fd[1]);

        execute(token); // 앞 명령어 실행
    }

    if((back = fork()) == 0) {
        dup2(fd[0], STDIN_FILENO); // 입력을 파이프라인 입력으로 연결

        close(fd[0]);
        close(fd[1]);

        execute(token + idx + 1); // | 이후 명령어 실행
    }
}

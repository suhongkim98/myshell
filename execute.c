#include <stdio.h>
#include "execute.h"
#include "background.h"
#include "redirect.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "pipeline.h"
#include "sequence.h"

void execute(char *arg[]) // 해당 프로세스의 프로세스 이미지 교체하는 함수
{
    int i;
    int flag; // flag++라면 자식프로세스에서 exec를 호출하겠다는 의미이다.
    char buf[256];

    if (!strcmp(arg[0], "cd")) /*작업 디렉토리 변경*/
    {
        chdir(arg[1]); // 작업 디렉토리 변경
    }
    else if (!strcmp(arg[0], "pwd")) /*현재 경로 출력*/
    {
        getcwd(buf, sizeof(buf)); //현재 경로
        printf("%s\n", buf);
    }
    else
    {
        flag = 0;
        for (i = 0; arg[i] != (char *)0; i++)
        {
            if (!strcmp(arg[i], ";")) // **명령어 순차적 실행**
            {
                flag++;
                sequenceExec(arg, i);
            }
            if (!strcmp(arg[i], "|")) { /*파이프라인 처리*/
                flag++;
                pipelineExec(arg, i);
            }
            if (!strcmp(arg[i], "&")) /*백그라운드 실행*/
            {
                flag++;        
                arg[i] = NULL;       // &가 위치한 자리를 null로 만들어준다.
                backgroundExec(arg); // 자식프로세스를 생성해서  백그라운드 처리
            }
            if (!strcmp(arg[i], ">") || !strcmp(arg[i], "<") || !strcmp(arg[i], ">>")) /*입출력 재지정*/
            {
                redirect(arg, i); // 리다이렉트
            }
        }
        if (!flag)
        { // 기타 명령어 실행
            execvp(arg[0], arg);
            exit(1); // 실행했으니 자식종료
        }
    }
}

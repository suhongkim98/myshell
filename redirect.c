#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
void redirect(char* token[], int index) {
   char* to = token[index+1]; //다음파일을 가리킨다
   int to_fd;
   int i;
   if(!strcmp(token[index], ">")) { // 매개변수로 넘어온 값이 >라면 출력 재지정
      to_fd = open(to, O_WRONLY | O_CREAT | O_TRUNC, 0641);
      if(to_fd < 0) {
         printf("open error in redirect \n");
         exit(1);
      }
      dup2(to_fd, STDOUT_FILENO); // 출력 재지정, 다음 파일을 가리키도록
      token[index] = NULL; // >는 NULL로 교체
   } else if(!strcmp(token[index], "<")) { // 매개변수로 넘어온 값이 <라면 입력 재지정
      to_fd = open(to, O_RDONLY, 0641); // read전용
      if(to_fd < 0){
         printf("open error in redirect \n");
         exit(1);
      }
      dup2(to_fd, STDIN_FILENO); // 입력 재지정
      token[index] = NULL;
   } else if(!strcmp(token[index], ">>")) { // 출력 재지정, append
      to_fd = open(to, O_RDWR | O_CREAT | O_APPEND, 0641); // O_APPEND를 줌으로써 append
      if(to_fd < 0){
         printf("open error in redirect \n");
         exit(1);
      }
      dup2(to_fd, STDOUT_FILENO); // 출력 재지정
      token[index] = NULL;
   }
   //명령어 실행은 부모가 해라
}

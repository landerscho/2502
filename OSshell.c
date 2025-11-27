#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_CMD_LEN 1024
#define MAX_ARG_LEN 64

int main() {
    char cmd[MAX_CMD_LEN];       
    char *argv[MAX_ARG_LEN];     
    char *token;
    int status;

    while (1) {
        printf("myshell> "); 
        
        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL) break;
      
        cmd[strcspn(cmd, "\n")] = '\0';

        if (strcmp(cmd, "exit") == 0) break;

        // 문자열 파싱 (공백 기준 토큰 분리)
        int i = 0;
        token = strtok(cmd, " ");
        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL;

        // 빈 명령어 입력 다시 돌아가야 함
        if (argv[0] == NULL) continue;

        // 생성
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork error");
        } 
        else if (pid == 0) {
            if (execvp(argv[0], argv) < 0) {
                perror("command not found");
                exit(1);
            }
        } 
        else {
            wait(&status);
        }
    }
    return 0;
}

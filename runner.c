#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "test.h"

void build_cmd(char *dest, Test *t)
{
    char *pos = strstr(t->cmd, "{program}");

    if (!pos)
    {
        strcpy(dest, t->cmd);
        return;
    }

    int prefix = pos - t->cmd;

    strncpy(dest, t->cmd, prefix);
    dest[prefix] = '\0';

    strcat(dest, t->program);
    strcat(dest, pos + strlen("{program}"));
}

int run(char *cmd, char *input, char *output)
{
    int in_pipe[2]; // Parent -> Child
    int out_pipe[2]; // Child -> Parent

    pipe(in_pipe);
    pipe(out_pipe);

    int pid = fork();

    // Child Process
    if (pid == 0)
    {
        dup2(in_pipe[0], STDIN_FILENO);
        dup2(out_pipe[1], STDOUT_FILENO);
        dup2(out_pipe[1], STDERR_FILENO);

        close(in_pipe[0]);
        close(in_pipe[1]);
        close(out_pipe[0]);
        close(out_pipe[1]);
        
        execl("/bin/sh", "sh", "-c", cmd, NULL);

        perror("execl() Failed.");
        exit(1);
    }

    // Parent Process
    close(in_pipe[0]);
    close(out_pipe[1]);

    if (input)
        write(in_pipe[1], input, strlen(input));
    close(in_pipe[1]);

    int n;
    int size = 0;
    while ((n = read(out_pipe[0], output + size, 4096 - size - 1)) > 0)
        size += n;
    output[size] = '\0';

    close(out_pipe[0]);

    int status;
    waitpid(pid, &status, 0);
    return status;
}
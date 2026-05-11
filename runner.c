#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "runner.h"

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

RunData run(char *cmd, char *input)
{
    RunData data;
    memset(&data, 0, sizeof(data));

    int in_pipe[2]; // Parent -> Child
    int out_pipe[2]; // Child -> Parent

    if (pipe(in_pipe) < 0 || pipe(out_pipe) < 0)
    {
        perror("pipe() failed");
        strcpy(data.output, "pipe() failed\n");
        data.crashed = 1;
        return data;
    }

    int pid = fork();

    if (pid < 0) {
        perror("fork() failed");
        strcpy(data.output, "fork() failed\n");
        data.crashed = 1;
        return data;
    }

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

    int status;
    int runtime = 0;

    while (1)
    {
        pid_t done = waitpid(pid, &status, WNOHANG);

        if (done == pid)
            break;
        
        sleep(1);
        runtime++;

        if (runtime >= 10)
        {
            kill(pid, SIGKILL);
            data.timed_out = 1;
            waitpid(pid, &status, 0);
            strcat(data.output, "TIMEOUT");
            close(out_pipe[0]);
            return data;
        }
    }

    int n;
    int size = 0;
    while ((n = read(out_pipe[0], data.output + size, 4096 - size - 1)) > 0)
        size += n;
    data.output[size] = '\0';

    close(out_pipe[0]);

    if (WIFSIGNALED(status))
    {
        data.crashed = 1;
        char msg[128];
        snprintf(msg, sizeof(msg), "CRASHED: Signal %d", WTERMSIG(status));
        // output already has crash messages written to stderr, which is captured by it
        strcat(data.output, msg);
    }

    if (WIFEXITED(status))
        data.exit_status = WEXITSTATUS(status);

    return data;
}
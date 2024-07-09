#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = { "ls", "-l", NULL };
    char *envp[] = { "USER=guest", "PATH=/tmp", NULL };

    printf("This program is about to run ls command using execve()\n");

    // execve() function to execute the "ls" command with an array of arguments and a custom environment
    execve("/bin/ls", args, envp);

    printf("This line will not be printed if execve() runs successfully\n");

    return 0;
}

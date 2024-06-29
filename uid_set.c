#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <new-uid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    uid_t new_uid = atoi(argv[1]);

    if (setuid(new_uid) == -1) {
        perror("setuid");
        exit(EXIT_FAILURE);
    }

    printf("Successfully changed UID to %d\n", new_uid);
    printf("Current UID: %d\n", getuid());

    return 0;
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    printf("User id: %d\n", getuid());
    printf("User effective id: %d\n", geteuid());

    FILE* file = fopen("secret.txt", "r+");
    if (file != NULL) {
        if (fclose(file) != 0) {
            perror("The file wasn't closed");
        }
    } else {
        perror("File opening is impossible");
    }

    if (setuid(getuid()) != 0) {
        perror("Error trying to set effective id");
    }


    printf("User id: %d\n", getuid());
    printf("User effective id: %d\n", geteuid());

    file = fopen("secret.txt", "r+");
    if (file != NULL) {
        if (fclose(file) != 0) {
            perror("The file wasn't closed");
        }
    } else {
        perror("File opening is impossible");
    }

    return 0;
}


#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SOCKET_PATH "socket.sock"

int main(int argc, char *argv[]) {

    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("Socket creating error");
        return -1;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);

    if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Connection error");
        return -1;
    }

    char buf[100];
    memset(buf, 0, sizeof(buf));
    int rc = read(STDIN_FILENO, buf, sizeof(buf));
    while(rc > 0) {
        int written_bytes = write(fd, buf, rc);
        if(written_bytes == -1){
            perror("Error while writting");
            return -1;
        }
        while(written_bytes < rc) {
            rc -= written_bytes;
            written_bytes += write(fd, buf+written_bytes, rc);
        }

        rc = read(STDIN_FILENO, buf, sizeof(buf));
    }
    close(fd);

    return 0;
}

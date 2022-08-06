#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int main() {
    int fd;
    if ((fd = open("/dev/urandom", O_RDONLY)) < 0) {
        printf("error on open\n");
        return -1;
    }

    unsigned char buf[sizeof(size_t)];
    if (read(fd, buf, sizeof(buf)) != sizeof(buf)) {
        printf("error on read\n");
        close(fd);
        return -1;
    }
    close(fd);

    size_t rd = *((size_t *)buf);
    printf("random: %lu, %lx\n", rd, rd);

    return 0;
}
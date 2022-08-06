#include <unistd.h>
#include <stdio.h>

#define failure ((char *)(-1))

int main() {

    char *base;
    if ((base = (char *)sbrk(0)) == failure) {
        printf("error on sbrk\n");
        return -1;
    }

    
}
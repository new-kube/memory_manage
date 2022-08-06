// for debug ptmalloc one by one.

#include <iostream>
#include "../malloc-2.8.3.h"


int main() {
    char *p;
    if ((p = (char *)dlmalloc(100)) == nullptr) {
        std::cout << "error on dlmalloc" << std::endl;
        return -1;
    }

    std::cout << "dlmalloc succeed" << std::endl;
    return 0;
}
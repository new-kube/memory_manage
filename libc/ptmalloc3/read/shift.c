
#include <stdio.h>

// 逻辑位移、算术位移
//  逻辑位移，左移尾部填充为0、右移头部填充0。会出现，大数左移出现负数的情况。负数右移出现正数。
//  算术位移，符号位不变，其他维和逻辑位移一致。

int main(int argc, char ** argv) {

    int a = 65;  // 有符号整型 0100 0001
    unsigned int b = 65; // 无符号整型 0100 0001
    a <<= 1; // 1000 0010  130 
    b >>= 1; //0010 0000  32
    char c = 127; // 0111 1111
    c <<= 3; // 1111 1000 -8  逻辑左移
    char d = 127; // 0111 1111
    d >>= 3; // 0000 1111 15
    char e = -8; // 内存以补码为1111 1000存储  源码为1000 1000 反码为1111 0111
    e >>= 3; // -1 补码1111 1111 源码 1000 0001 反码1111 1110  原码的算术右移
    printf("%d %d\n", a, b); // 130 32
    printf("%d %d\n", c, d); // -8  15
    printf("%d\n", e); // -1
    
    // 不同的平台，是算术位移还是逻辑位移，并不相同。
    return 0;
}
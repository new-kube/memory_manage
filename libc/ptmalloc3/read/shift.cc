
#include <stdio.h>
#include <string>
#include <iostream>

// 逻辑位移、算术位移
//  逻辑位移，左移尾部填充为0、右移头部填充0。会出现，大数左移出现负数的情况。负数右移出现正数。
//  算术位移，符号位不变，其他位和逻辑位移一致。

/* isolate the least set bit of a bitmap */
#define least_bit(x)         ((x) & -(x))

/* mask with all bits to left of least bit of x on */
#define left_bits(x)         ((x<<1) | -(x<<1))

/* mask with all bits to left of or equal to least bit of x on */
#define same_or_left_bits(x) ((x) | -(x))


std::string print_bit(void *data, size_t dlen);

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

    int x = 2;
    int lb = least_bit(x);
    int lbs = left_bits(x);
    int slb = same_or_left_bits(x);

    printf("least_bit(%d) = %d\n", x, lb);
    printf("left_bits(%d) = %d\n", x, lbs);
    printf("same_or_left_bits(%d) = %d\n", x, slb);
    
    // 不同的平台，是算术位移还是逻辑位移，并不相同。

    // 内存中二进制位呈现。
    int y = 7;
    int z = -7;

    y = 2;
    z = -2;

    std::string sy = print_bit(&y, sizeof(y));
    std::string sz = print_bit(&z, sizeof(z));

    std::cout << "y =  " << y << ", octct = " << sy << std::endl;
    std::cout << "z = " << z << ", octct = " << sz << std::endl;

    return 0;
}

std::string print_char(char data) {
    unsigned char v = 1;
    int bit;
    char bytes[9];
    char sbit;
    for (int i = 0; i < 8; i++) {
        bit = data & (v << (7 - i));
        sbit = '0';
        if (bit > 0)
            sbit = '1';
        
        bytes[i] = sbit;
    }
    bytes[8] = 0;

    return std::string(bytes);
}

std::string print_bit(void *data, size_t dlen) {
    char *p = (char *)data;
    std::string ret;
    for (int i = dlen - 1; i >= 0; i--) {
        ret += print_char(p[i]);
    }
    return ret;
}


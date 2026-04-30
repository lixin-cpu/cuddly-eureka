#include <stdio.h>

int input() {
    int n;
    scanf("%d", &n);
    return n;
}

int main() {
    printf("Hello, World!\n");
    printf("请输入：");
    int num = input();  
    printf("你输入了：%d\n", num);
    return 0;
}
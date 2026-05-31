#include "c_d.h"

int main()
{
    int mod;
    printf("请选择功能：\n1. 压缩文件\n2. 解压文件\n输入数字: ");
    scanf("%d", &mod);
    if (mod == 1) {
        ziptext();
    } else if (mod == 2) {
        unziptext();
    } else {
        printf("无效数字\n");
    }
    return 0;
}
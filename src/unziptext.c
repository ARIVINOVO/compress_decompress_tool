#include "c_d.h"

int unziptext()
{
    char filename[50];
    printf("输入压缩文件名:");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) 
    {
        perror("");
        return -1;
    }
    int all_chars, n;
    if (fread(&all_chars, 4, 1, fp) != 1 || fread(&n, 4, 1, fp) != 1)
    {
        printf("文件错误");
        return -1;
    }
    
    statistics *weight = malloc(n * sizeof(statistics));
    for (int i = 0; i < n; i++) 
    {
        unsigned char ch;
        int freq;
        if (fread(&ch, 1, 1, fp) != 1 || fread(&freq, 4, 1, fp) != 1) 
        {
            printf("频率表读取失败\n");
            free(weight);
            fclose(fp);
            return -1;
        }
        weight[i].ch = ch;
        weight[i].frequency = freq;
    }
    huffnode *huff = malloc((2 * n - 1) * sizeof(huffnode));
    make_huffman(huff, weight, n);
    printf("输入解压后文件名:");
    scanf("%s", filename);
    FILE *fp1 = fopen(filename, "wb");
    if (!fp1) 
    {
        perror("");
        free(weight); free(huff); fclose(fp);
        return -1;
    }
    int root = 2*n - 2;
    BitReader br;
    init_bit_reader(&br, fp);

    int cur = root;
    int decoded_count = 0;
    while (decoded_count < all_chars) 
    {
        int bit = read_bit(&br);
        if (bit == -1) 
        {
            printf("已提前结束\n");
            break;
        }
        if (bit == 0)
            cur = huff[cur].left;
        else
            cur = huff[cur].right;
        printf("%d ", cur);
        if (huff[cur].left == -1 && huff[cur].right == -1) 
        {
            fwrite(&huff[cur].data, 1, 1, fp1);
            decoded_count++;
            cur = root;
        }
    }
    free(weight);
    free(huff);
    fclose(fp);
    fclose(fp1);
    return 0;
}
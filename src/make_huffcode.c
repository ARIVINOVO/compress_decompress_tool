#include "c_d.h"

void make_huffcode(huffnode *huff, huffcode *huff_code, int n)
{
    int i,f,c;
    huffcode hu;
    for ( i = 0; i < n; i++)
    {
        hu.start = n;
        c = i;
        f = huff[i].parent;
        while (f != -1)
        {
            if (huff[f].left == c)
                hu.cd[hu.start--] = '0';
            else{
                hu.cd[hu.start--] = '1';
            }
            c = f;
            f = huff[f].parent;
        }
        hu.start++;
        hu.ch = huff[i].data;
        huff_code[i] = hu;
    }
    
}
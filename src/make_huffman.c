#include "c_d.h"

void make_huffman(huffnode *huff, statistics *weight , int n)
{
    int i, k, min1, min2, lnode,rnode;
    for ( i = 0; i < 2*n-1; i++)
    {
        if (i<n)
        {
            huff[i].freq = weight[i].frequency;
            huff[i].data = weight[i].ch;
        }else{
            huff[i].freq = 0;
        }
        huff[i].left = -1;
        huff[i].parent = -1;
        huff[i].right = -1;
    }
    for ( i = n; i < 2*n-1; i++)
    {
        min1 = 99999;
        min2 = min1;
        lnode = -1;
        rnode = -1;
        for ( k = 0; k < i; k++)
        {
            if (huff[k].parent == -1)
            {
                if (huff[k].freq < min1)
                {
                    min2 = min1;
                    rnode = lnode;
                    min1 = huff[k].freq;
                    lnode = k;
                }else if (huff[k].freq < min2){
                    min2 = huff[k].freq;
                    rnode = k;
                }
                
            }
            
        }
        huff[i].freq = huff[lnode].freq + huff[rnode].freq;
        huff[i].left = lnode;
        huff[i].right = rnode;
        huff[lnode].parent = huff[rnode].parent = i;
    }
    
}
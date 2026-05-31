#include "c_d.h"

void st_frequency(FILE *fp, statistics *frequcy)
{
    if (fp == NULL)
    {
        perror("open file error");
        return;
    }

    for (int i = 0; i < 256; i++) {
        frequcy[i].ch = i;
        frequcy[i].frequency = 0;
    }

    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        frequcy[c].frequency++;
    }
    return;
}

statistics* getweight(statistics *frequcy , int *n)
{
    for (int k=0; k < 256; k++)
    {
        if (frequcy[k].frequency != 0)
            (*n)++;
    }
    //statistics weight[*n];
    statistics *weight = malloc((*n) * sizeof(statistics));
    int j=0,k=0;
    while (j<256)
    {
        if (frequcy[j].frequency == 0)
        {
            j++;
        }else{
            weight[k].ch = frequcy[j].ch;
            weight[k].frequency = frequcy[j].frequency;
            k++;
            j++;
        }
    }
    return weight;
}
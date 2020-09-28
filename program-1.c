#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STAT_VOL 20

char *getstr(void)    /* ввод строки (с очисткой памяти) */
{
    int len = sizeof(char) * STAT_VOL;
    size_t newstrlen;
    int position = 0;
    char *str = malloc(sizeof(char) * STAT_VOL);
    if (!str)
    {
        printf("memory allocation error!");
        exit(-1);
    }

    while ( fgets(str + position, STAT_VOL, stdin) )
    {
        newstrlen = strlen(str);
        if (str[newstrlen - 1] != '\n')
        {
            position = newstrlen;
            len += sizeof(char) * STAT_VOL;
            str = realloc(str, len);
            if (!str)
            {
                printf("memory reallocation error!");
                exit(-1);
            }
        }
        else
        {
            str[newstrlen - 1] = '\0';
            return str;
        }
    }

    free(str);

    return NULL;
}

void bubblesort(char **arrofstr, int numberofelem)    /* самая простая сортировка пузырьком */
{
    char *temp = NULL;
    int i; int j;
    for(i=1;i<numberofelem;++i)
    {
        for(j=1;j<numberofelem;++j)
        {
            if(strcmp(arrofstr[j], arrofstr[j-1])<0)    /* меняет местами указатели на строки в массиве указателей */
            {
                temp = arrofstr[j];
                arrofstr[j] = arrofstr[j-1];
                arrofstr[j-1] = temp;
            }
        }
    }
}

void outstr(char **arrofstr, int numberofelem)    /* вывод строк */
{
    int currentelem = 0;
    while(currentelem < numberofelem)
    {
        printf("%s\n", arrofstr[currentelem]);
        free(arrofstr[currentelem]);
        ++currentelem;
    }
}

int main() {    /* main (getstr X n); sort; output; free */
    int part = 0; int amountofstr = 0;
    char *str = NULL;
    char **arrofstr = (char**)malloc(sizeof(char*) * STAT_VOL);
    if (!arrofstr)
    {
        printf("memory reallocation error!");
        exit(-1);
    }
    while((str=getstr()))
    {
        if((part+1)%STAT_VOL == 0)
        {
            arrofstr = realloc(arrofstr, sizeof(char*) * (part + STAT_VOL));
            if(!arrofstr)
            {
                printf("memory reallocation error!");
                exit(-1);
            }
        }
        arrofstr[part++] = str;
	++amountofstr;
    }
    bubblesort(arrofstr, amountofstr);    /* сортировка и вывод */
    outstr(arrofstr, amountofstr);
    free(arrofstr);
    return 0;
}

/* based  */

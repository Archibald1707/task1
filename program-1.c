#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getstr(void)    /* ввод строки (с очисткой памяти) */
{
    int len = sizeof(char) * 20;
    size_t newStringLength;
    int position = 0;
    char *str = malloc(sizeof(char) * 20);
    if (!str)
    {
        printf("memory allocation error!");
        exit(-1);
    }

    while ( fgets(str + position, 20, stdin) )
    {
        newStringLength = strlen(str);
        if (str[newStringLength - 1] != '\n')
        {
            position = newStringLength;
            len += sizeof(char) * 20;
            str = realloc(str, len);
            if (!str)
            {
                printf("memory reallocation error!");
                exit(-1);
            }
        }
        else
        {
            str[newStringLength - 1] = '\0';
            return str;
        }
    }

    free(str);

    return NULL;
}

void bubbleSort(char **arrayOfString, int numberOfElem)    /* самая простая сортировка пузырьком */
{
    char *temp = NULL;
    int i; int j;
    for(i=1;i<numberOfElem;++i)
    {
        for(j=1;j<numberOfElem;++j)
        {
            if(strcmp(arrayOfString[j], arrayOfString[j-1])<0)    /* меняет местами указатели на строки в массиве указателей */
            {
                temp = arrayOfString[j];
                arrayOfString[j] = arrayOfString[j-1];
                arrayOfString[j-1] = temp;
            }
        }
    }
}

void outstr(char **arrayOfString, int numberOfElem)    /* вывод строк */
{
    int currentElement = 0;
    while(currentElement<numberOfElem)
    {
        printf("%s\n", arrayOfString[currentElement]);
        free(arrayOfString[currentElement]);
        ++currentElement;
    }
}

int main() {    /* main (getstr X n); sort; output; free */
    int partOfSize = 0; int amountOfString = 0;
    char *str = NULL;
    char **arrayOfString = (char**)malloc(sizeof(char*) * 20);
    if (!arrayOfString)
    {
        printf("memory reallocation error!");
        exit(-1);
    }
    while((str=getstr()))
    {
        if((partOfSize+1)%20 == 0)
        {
	  arrayOfString = realloc(arrayOfString, sizeof(char*) * (partOfSize + 20));
            if(!arrayOfString)
            {
                printf("memory reallocation error!");
                exit(-1);
            }
        }
        arrayOfString[partOfSize++] = str;
	++amountOfString;
    }
    bubbleSort(arrayOfString, amountOfString);    /* сортировка и вывод */
    outstr(arrayOfString, amountOfString);
    free(arrayOfString);
    return 0;
}

/* based  */
